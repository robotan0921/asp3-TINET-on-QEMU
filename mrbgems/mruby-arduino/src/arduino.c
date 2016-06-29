#include <arduino.h>
#include <string.h>

#include <mruby.h>
#include <mruby/irep.h>
#include <mruby/string.h>
#include <mruby/variable.h>
#include <mruby/error.h>
#include <mruby/array.h>

#include "../llbruby.h"
#include "sKernel.h"
#include "sSys.h"
#include "sSerial.h"
#include "sMem.h"
#include "sI2c.h"
#include "sServo.h"
#include "sSdCard.h"
#include "sRtc.h"

//バージョンのセット
volatile char	ProgVer[] = {WRBB_VERSION};

char RubyFilename[64];

void mrb_mruby_arduino_gem_init(mrb_state *mrb)
{
	arduino_init();

	kernel_Init(mrb);	/* カーネル関連メソッドの設定 */
	sys_Init(mrb);		/* システム関連メソッドの設定 */
	serial_Init(mrb);	/* シリアル通信関連メソッドの設定 */
	mem_Init(mrb);		/* ファイル関連メソッドの設定 */
	i2c_Init(mrb);		/* I2C関連メソッドの設定 */
	servo_Init(mrb);	/* サーボ関連メソッドの設定 */

#if REALTIMECLOCK
	rtc_Init(mrb);		/* RTC関連メソッドの設定 */
#endif

#if FIRMWARE == JAM
	pancake_Init(mrb);		/* PanCake関連メソッドの設定 */
#endif

#if BOARD == BOARD_GR || FIRMWARE == SDBT || FIRMWARE == SDWF
	sdcard_Init(mrb);		/* SDカード関連メソッドの設定 */
#endif

#if FIRMWARE == SDWF
	esp8266_Init(mrb);		/* WiFi関連メソッドの設定 */
#endif
}

void mrb_mruby_arduino_gem_final(mrb_state *mrb)
{

}
