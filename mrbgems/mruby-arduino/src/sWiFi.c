/*
 * ESP-WROOM-02関連
 *
 * Copyright (c) 2015 Minao Yamamoto
 *
 * This software is released under the MIT License.
 *
 * http://opensource.org/licenses/mit-license.php
 */
#include <arduino.h>
#include <string.h>

#include <mruby.h>
#include <mruby/string.h>

#include "../llbruby.h"
#include "sKernel.h"

extern serial_t *serial[];

#define  WIFI_SERIAL	3
#define  WIFI_BAUDRATE	115200
#define  WIFI_CTS		15

unsigned char WiFiData[256];
int WiFiRecvOutlNum = -1;	/* ESP8266からの受信を出力するシリアル番号: -1の場合は出力しない。 */


/******************************************************/
/*  OK 0d0a か ERROR 0d0aが来るまで WiFiData[]に読むか、 */
/*  指定されたシリアルポートに出力します */
/******************************************************/
void getData()
{
	char f[16];
	unsigned long times;
	int c;
	int okt = 0;
	int ert = 0;
	struct pin_node *pin = wrb2sakura(pintype_gpio, WIFI_CTS);

	/* DEBUG_PRINT("getData", a); */

	/* 受信バッファを空にします */
	gpio_write(&pin->gpio, 0);	/* 送信許可 */
	while (serial_readable(serial[WIFI_SERIAL])) {
		serial_getc(serial[WIFI_SERIAL]);
		wait_ms(0);
	}

	WiFiData[0] = 0;
	for (int i = 0; i < 255; i++) {

		gpio_write(&pin->gpio, 0);	/* 送信許可 */

		times = us_ticker_read() / 1000;
		while (!serial_readable(serial[WIFI_SERIAL])) {
			/* 1000ms 待つ */
			if ((us_ticker_read() / 1000) - times > 10000) {
				DEBUG_PRINT("WiFi get Data", "Time OUT");
				WiFiData[i + 1] = 0;
				return;
			}

			/* DEBUG_PRINT("getData","DATA Waiting"); */
		}
		gpio_write(&pin->gpio, 1);	/* 送信許可しない */

		c = serial_getc(serial[WIFI_SERIAL]);

		/* 指定のシリアルポートに出す設定であれば、受信値を出力します */
		if (WiFiRecvOutlNum >= 0) {
			serial_putc(serial[WiFiRecvOutlNum], (unsigned char)c);
		}

		WiFiData[i] = c;
		/* DEBUG_PRINT("c",c); */

		if (c == 'O') {
			okt++;
			ert++;
		}
		else if (c == 'K') {
			okt++;
		}
		else if (c == 0x0d) {
			ert++;
			okt++;
		}
		else if (c == 0x0a) {
			ert++;
			okt++;
			if (okt == 4 || ert == 7) {
				WiFiData[i + 1] = 0;
				break;
			}
			else {
				ert = 0;
				okt = 0;
			}
		}
		else if (c == 'E' || c == 'R') {
			ert++;
		}
		else {
			okt = 0;
			ert = 0;
		}
	}
	gpio_write(&pin->gpio, 0);	/* 送信許可 */
}

/******************************************************/
/*  ステーションモードの設定: WiFi.cwmode */
/*   WiFi.cwmode(mode) */
/*   mode: 1:Station, 2:SoftAP, 3:Station + SoftAP */
/******************************************************/
mrb_value mrb_wifi_Cwmode(mrb_state *mrb, mrb_value self)
{
	int	mode;
	char str[32];

	mrb_get_args(mrb, "i", &mode);

	sprintf(str, "AT+CWMODE=%d", mode);
	serial_println(serial[WIFI_SERIAL], str);

	/* OK 0d0a か ERROR 0d0aが来るまで WiFiData[]に読か、指定されたシリアルポートに出力します */
	getData();

	return mrb_str_new_cstr(mrb, (const char*)WiFiData);
}

/******************************************************/
/*  コマンド応答のシリアル出力設定: WiFi.recive */
/*   WiFi.recive( mode[,serialNumber] ) */
/*   mode: 0:出力しない, 1:出力する */
/*   serialNumber: 出力先のシリアル番号 */
/******************************************************/
mrb_value mrb_wifi_Sout(mrb_state *mrb, mrb_value self)
{
	int mode;
	int num = -1;

	int n = mrb_get_args(mrb, "i|i", &mode, &num);

	if (mode == 0) {
		WiFiRecvOutlNum = -1;
	}
	else {
		if (n >= 2) {
			if (num >= 0) {
				WiFiRecvOutlNum = num;
			}
		}
	}
	return mrb_nil_value();			/* 戻り値は無しですよ。 */
}

/******************************************************/
/*  ATコマンドの送信: WiFi.at */
/*   WiFi.at( command[, mode] ) */
/*   commnad: ATコマンド内容 */
/*   mode: 0:'AT+'を自動追加する、1:'AT+'を自動追加しない */
/******************************************************/
mrb_value mrb_wifi_at(mrb_state *mrb, mrb_value self)
{
	mrb_value text;
	int mode = 0;

	int n = mrb_get_args(mrb, "S|i", &text, &mode);

	char *s = RSTRING_PTR(text);
	int len = RSTRING_LEN(text);

	if (n <= 1 || mode == 0) {
		serial_print(serial[WIFI_SERIAL], "AT+");
	}

	for (int i = 0; i < 254; i++) {
		if (i >= len) { break; }
		WiFiData[i] = s[i];
	}
	WiFiData[len] = 0;

	serial_println(serial[WIFI_SERIAL], (const char*)WiFiData);
	/* DEBUG_PRINT("WiFi.at",(const char*)WiFiData); */

	/* OK 0d0a か ERROR 0d0aが来るまで WiFiData[]に読か、指定されたシリアルポートに出力します */
	getData();

	return mrb_str_new_cstr(mrb, (const char*)WiFiData);
}

/******************************************************/
/*  WiFi接続します: WiFi.cwjap */
/*   WiFi.cwjap(SSID,Passwd) */
/*   SSID: WiFiのSSID */
/*   Passwd: パスワード */
/******************************************************/
mrb_value mrb_wifi_Cwjap(mrb_state *mrb, mrb_value self)
{
	mrb_value ssid;
	mrb_value passwd;

	mrb_get_args(mrb, "SS", &ssid, &passwd);

	char *s = RSTRING_PTR(ssid);
	int slen = RSTRING_LEN(ssid);

	char *p = RSTRING_PTR(passwd);
	int plen = RSTRING_LEN(passwd);

	serial_print(serial[WIFI_SERIAL], "AT+CWJAP=");
	WiFiData[0] = 0x22;		/* -> " */
	WiFiData[1] = 0;
	serial_print(serial[WIFI_SERIAL], (const char*)WiFiData);

	for (int i = 0; i < 254; i++) {
		if (i >= slen) { break; }
		WiFiData[i] = s[i];
	}
	WiFiData[slen] = 0;
	serial_print(serial[WIFI_SERIAL], (const char*)WiFiData);

	WiFiData[0] = 0x22;		/* -> " */
	WiFiData[1] = 0x2C;		/* -> , */
	WiFiData[2] = 0x22;		/* -> " */
	WiFiData[3] = 0;
	serial_print(serial[WIFI_SERIAL], (const char*)WiFiData);

	for (int i = 0; i < 254; i++) {
		if (i >= plen) { break; }
		WiFiData[i] = p[i];
	}
	WiFiData[plen] = 0;
	serial_print(serial[WIFI_SERIAL], (const char*)WiFiData);

	WiFiData[0] = 0x22;		/* -> " */
	WiFiData[1] = 0;
	serial_println(serial[WIFI_SERIAL], (const char*)WiFiData);

	/* OK 0d0a か ERROR 0d0aが来るまで WiFiData[]に読か、指定されたシリアルポートに出力します */
	getData();

	return mrb_str_new_cstr(mrb, (const char*)WiFiData);
}

/******************************************************/
/*  IPアドレスとMACアドレスの表示: WiFi.cifsr */
/*   WiFi.cwjap() */
/******************************************************/
mrb_value mrb_wifi_Cifsr(mrb_state *mrb, mrb_value self)
{
	serial_println(serial[WIFI_SERIAL], "AT+CIFSR");

	/* OK 0d0a か ERROR 0d0aが来るまで WiFiData[]に読か、指定されたシリアルポートに出力します */
	getData();

	return mrb_str_new_cstr(mrb, (const char*)WiFiData);
}

/******************************************************/
/*  ライブラリを定義します */
/******************************************************/
void esp8266_Init(mrb_state *mrb)
{
	struct pin_node *pin = wrb2sakura(pintype_gpio, WIFI_CTS);
	PinName txpin, rxpin;

	WiFiRecvOutlNum = -1;

	/* CTS用にPIN15をOUTPUTに設定します */
	gpio_dir(&pin->gpio, PIN_OUTPUT);
	gpio_write(&pin->gpio, 1);

	/* WiFiのシリアル3を設定 */
	/* シリアル通信の初期化をします */
	if (serial[WIFI_SERIAL] != 0) {
		serial_free(serial[WIFI_SERIAL]);
		wait_ms(50);
		free(serial[WIFI_SERIAL]);
	}
	serial[WIFI_SERIAL] = calloc(1, sizeof(serial_t));
	portToPins(SCI_SCI6B, &txpin, &rxpin);
	serial_init(serial[WIFI_SERIAL], txpin, rxpin);
	serial_baud(serial[WIFI_SERIAL], WIFI_BAUDRATE);

	/* ECHOオフコマンドを送信する */
	serial_println(serial[WIFI_SERIAL], "ATE0");

	getData();	/* OK 0d0a か ERROR 0d0aが来るまで WiFiData[]に読む */


	struct RClass *wifiModule = mrb_define_module(mrb, "WiFi");

	mrb_define_module_function(mrb, wifiModule, "at", mrb_wifi_at, MRB_ARGS_REQ(1) | MRB_ARGS_OPT(1));
	mrb_define_module_function(mrb, wifiModule, "sout", mrb_wifi_Sout, MRB_ARGS_REQ(1) | MRB_ARGS_OPT(1));
	mrb_define_module_function(mrb, wifiModule, "cwmode", mrb_wifi_Cwmode, MRB_ARGS_REQ(1));
	mrb_define_module_function(mrb, wifiModule, "cwjap", mrb_wifi_Cwjap, MRB_ARGS_REQ(2));
	mrb_define_module_function(mrb, wifiModule, "cifsr", mrb_wifi_Cifsr, MRB_ARGS_NONE());


	/* mrb_define_module_function(mrb, pancakeModule, "clear", mrb_pancake_Clear, MRB_ARGS_REQ(1)); */
	/* mrb_define_module_function(mrb, pancakeModule, "line", mrb_pancake_Line, MRB_ARGS_REQ(5)); */
	/* mrb_define_module_function(mrb, pancakeModule, "circle", mrb_pancake_Circle, MRB_ARGS_REQ(4)); */
	/* mrb_define_module_function(mrb, pancakeModule, "stamp", mrb_pancake_Stamp, MRB_ARGS_REQ(4)); */
	/* mrb_define_module_function(mrb, pancakeModule, "stamp1", mrb_pancake_Stamp1, MRB_ARGS_REQ(4)); */
	/* mrb_define_module_function(mrb, pancakeModule, "image", mrb_pancake_Image, MRB_ARGS_REQ(1)); */
	/* mrb_define_module_function(mrb, pancakeModule, "video", mrb_pancake_Video, MRB_ARGS_REQ(1)); */
	/* mrb_define_module_function(mrb, pancakeModule, "sound", mrb_pancake_Sound, MRB_ARGS_REQ(8)); */
	/* mrb_define_module_function(mrb, pancakeModule, "sound1", mrb_pancake_Sound1, MRB_ARGS_REQ(3)); */
	/* mrb_define_module_function(mrb, pancakeModule, "reset", mrb_pancake_Reset, MRB_ARGS_NONE()); */
	/* mrb_define_module_function(mrb, pancakeModule, "out", mrb_pancake_Out, MRB_ARGS_REQ(1)); */

	/* struct RClass *spriteModule = mrb_define_module(mrb, "Sprite"); */
	/* mrb_define_module_function(mrb, spriteModule, "start", mrb_pancake_Start, MRB_ARGS_REQ(1)); */
	/* mrb_define_module_function(mrb, spriteModule, "create", mrb_pancake_Create, MRB_ARGS_REQ(2)); */
	/* mrb_define_module_function(mrb, spriteModule, "move", mrb_pancake_Move, MRB_ARGS_REQ(3)); */
	/* mrb_define_module_function(mrb, spriteModule, "flip", mrb_pancake_Flip, MRB_ARGS_REQ(2)); */
	/* mrb_define_module_function(mrb, spriteModule, "rotate", mrb_pancake_Rotate, MRB_ARGS_REQ(2)); */
	/* mrb_define_module_function(mrb, spriteModule, "user", mrb_pancake_User, MRB_ARGS_REQ(3)); */

	/* struct RClass *musicModule = mrb_define_module(mrb, "Music"); */
	/* mrb_define_module_function(mrb, musicModule, "score", mrb_pancake_Score, MRB_ARGS_REQ(4)); */
	/* mrb_define_module_function(mrb, musicModule, "play", mrb_pancake_Play, MRB_ARGS_REQ(1)); */
}
