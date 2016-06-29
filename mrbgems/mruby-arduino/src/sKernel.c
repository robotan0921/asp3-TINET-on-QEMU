/*
 * カーネル関連
 *
 * Copyright (c) 2015 Minao Yamamoto
 *
 * This software is released under the MIT License.
 *
 * http://opensource.org/licenses/mit-license.php
 */
#include <arduino.h>
/* #include <string.h> */
/* #include <time.h> */
/* #include <sys/time.h> */

#include <mruby.h>
/* #include "mruby/string.h" */
/* #include "mruby/variable.h" */
/* #include "mruby/array.h" */

#include "../llbruby.h"
#include "sKernel.h"

/******************************************************/
/*  デジタルライト */
/*  digitalWrite(pin, value) */
/*  pin */
/*      ピンの番号 */
/*  value */
/*   0: LOW */
/*   1: HIGH */
/******************************************************/
mrb_value mrb_kernel_digitalWrite(mrb_state *mrb, mrb_value self)
{
	int pinno, value;
	struct pin_node *pin;

	mrb_get_args(mrb, "ii", &pinno, &value);

	pin = wrb2sakura(pintype_gpio, pinno);
	gpio_write(&pin->gpio, value);

	return mrb_nil_value();	/* 戻り値は無しですよ。 */
}

/******************************************************/
/*  PINのモード設定 */
/*  pinMode(pin, mode) */
/*   pin */
/*      ピンの番号 */
/*  mode */
/*   0: INPUTモード */
/*   1: OUTPUTモード */
/******************************************************/
mrb_value mrb_kernel_pinMode(mrb_state *mrb, mrb_value self)
{
	int pinno, value;
	struct pin_node *pin;

	mrb_get_args(mrb, "ii", &pinno, &value);

	pin = wrb2sakura(pintype_gpio, pinno);

	/* CTS用にPIN15をOUTPUTに設定します */
	switch (value) {
	case 0:
		gpio_dir(&pin->gpio, PIN_INPUT);
		break;
	case 1:
		gpio_dir(&pin->gpio, PIN_OUTPUT);
		break;
	}

	return mrb_nil_value();			/* 戻り値は無しですよ。 */
}

/******************************************************/
/*  ディレイ 強制GCを行っています */
/*  delay(value) */
/*  value */
/*      時間(ms) */
/******************************************************/
mrb_value mrb_kernel_delay(mrb_state *mrb, mrb_value self)
{
	int value;

	mrb_get_args(mrb, "i", &value);

	/* 試しに強制gcを入れて見る */
	mrb_full_gc(mrb);

	if (value > 0) {
		wait_ms(value);
	}

	return mrb_nil_value();			/* 戻り値は無しですよ。 */
}


/******************************************************/
/*  ミリ秒を取得します: millis */
/*  millis() */
/*  戻り値 */
/*  起動してからのミリ秒数 */
/******************************************************/
mrb_value mrb_kernel_millis(mrb_state *mrb, mrb_value self)
{
	return mrb_fixnum_value((mrb_int)(us_ticker_read() / 1000));
}

/******************************************************/
/*  マイクロ秒を取得します: micros */
/*  micros() */
/*  戻り値 */
/*  起動してからのマイクロ秒数 */
/******************************************************/
mrb_value mrb_kernel_micros(mrb_state *mrb, mrb_value self)
{
	return mrb_fixnum_value((mrb_int)us_ticker_read());
}

/******************************************************/
/*  デジタルリード: digitalRead */
/*  digitalRead(pin) */
/*   pin: ピンの番号 */
/*   */
/*   0:LOW */
/*   1:HIGH */
/******************************************************/
mrb_value mrb_kernel_digitalRead(mrb_state *mrb, mrb_value self)
{
	int pinno, value;
	struct pin_node *pin;

	mrb_get_args(mrb, "i", &pinno);

	pin = wrb2sakura(pintype_gpio, pinno);
	value = gpio_read(&pin->gpio);

	return mrb_fixnum_value(value);
}

/******************************************************/
/*  アナログリード: analogRead */
/*  analogRead(pin) */
/*   pin: アナログの番号 */
/*   */
/*      10ビットの値(0～1023) */
/******************************************************/
mrb_value mrb_kernel_analogRead(mrb_state *mrb, mrb_value self)
{
	int anapin, value;
	struct pin_node *pin;

	mrb_get_args(mrb, "i", &anapin);

	pin = wrb2sakura(pintype_analogin, anapin);

	value = analogin_read_u16(&pin->analogin) >> 6;

	return mrb_fixnum_value(value);
}

/******************************************************/
/*  PWM出力: pwm */
/*  pwm(pin, value) */
/*   pin: ピンの番号 */
/*   value:	出力PWM比率(0～255) */
/******************************************************/
mrb_value mrb_kernel_pwm(mrb_state *mrb, mrb_value self)
{
	int pinno, value;
	struct pin_node *pin;

	mrb_get_args(mrb, "ii", &pinno, &value);

	pin = wrb2sakura(pintype_pwmout, pinno);

#if DEVICE_ANALOGOUT
	if (value >= 0 && value < 256) {
		pwmout_pulsewidth_us(&pin->pwmout, (pin->period * value) / 255);
	}
	else {
		pwmout_pulsewidth_us(&pin->pwmout, 0);
	}
#endif

	return mrb_nil_value();			/* 戻り値は無しですよ。 */
}

/******************************************************/
/*  PWM周波数設定: pwmHz */
/*  pwmHz(value) */
/*   value:	周波数(12～184999)Hz */
/******************************************************/
mrb_value mrb_kernel_pwmHz(mrb_state *mrb, mrb_value self)
{
	int pinno, value;
	struct pin_node *pin;

	mrb_get_args(mrb, "ii", &pinno, &value);

	pin = wrb2sakura(pintype_pwmout, pinno);

	if (value >= 12 && value < 18500) {
#if DEVICE_ANALOGOUT
		pin->period = 1000000 / value;
		pwmout_period_us(&pin->pwmout, pin->period);
#endif
	}

	return mrb_nil_value();			/* 戻り値は無しですよ。 */
}

/******************************************************/
/*  アナログDAC出力: analogDac */
/*  analogDac(value) */
/*   pin: ピンの番号 */
/*   value:	10bit精度(0～4095) */
/******************************************************/
mrb_value mrb_kernel_analogDac(mrb_state *mrb, mrb_value self)
{
	int anapin, value;
	struct pin_node *pin;

	mrb_get_args(mrb, "ii", &anapin, &value);

	pin = wrb2sakura(pintype_dac, anapin);

	if (value >= 0 && value < 4096) {
#if DEVICE_ANALOGOUT
		analogout_write_u16(&pin->dac, value << 4);
#endif
	}

	return mrb_nil_value();			/* 戻り値は無しですよ。 */
}

static void led_on(int led, bool on)
{
	struct pin_node *pin;

	pin = wrb2sakura(pintype_dac, led);

	gpio_write(&pin->gpio, on);
}

/******************************************************/
/*  LEDオンオフ: led */
/*  led(sw) */
/******************************************************/
mrb_value mrb_kernel_led(mrb_state *mrb, mrb_value self)
{
	int value;

	mrb_get_args(mrb, "i", &value);

#if BOARD == BOARD_GR
	led_on(LED1, value & 1);
	led_on(LED2, (value >> 1) & 1);
	led_on(LED3, (value >> 2) & 1);
	led_on(LED4, (value >> 3) & 1);
#else
	led_on(RB_LED, value & 1);
#endif

	return mrb_nil_value();			/* 戻り値は無しですよ。 */
}

/******************************************************/
/*  隠しコマンドです:  El_Psy.Congroo */
/*  El_Psy.Congroo() */
/******************************************************/
mrb_value mrb_El_Psy_congroo(mrb_state *mrb, mrb_value self)
{
	mrb_raise(mrb, mrb_class_get(mrb, "Sys#exit Called"), "Normal Completion");

	return mrb_nil_value();	/* 戻り値は無しですよ。 */
}

/******************************************************/
/*  ライブラリを定義します */
/******************************************************/
void kernel_Init(mrb_state *mrb)
{
	mrb_define_method(mrb, mrb->kernel_module, "pinMode", mrb_kernel_pinMode, MRB_ARGS_REQ(2));

	mrb_define_method(mrb, mrb->kernel_module, "digitalWrite", mrb_kernel_digitalWrite, MRB_ARGS_REQ(2));
	mrb_define_method(mrb, mrb->kernel_module, "pwm", mrb_kernel_pwm, MRB_ARGS_REQ(2));
	mrb_define_method(mrb, mrb->kernel_module, "digitalRead", mrb_kernel_digitalRead, MRB_ARGS_REQ(1));
	mrb_define_method(mrb, mrb->kernel_module, "analogRead", mrb_kernel_analogRead, MRB_ARGS_REQ(1));

	mrb_define_method(mrb, mrb->kernel_module, "pwmHz", mrb_kernel_pwmHz, MRB_ARGS_REQ(1));
	mrb_define_method(mrb, mrb->kernel_module, "analogDac", mrb_kernel_analogDac, MRB_ARGS_REQ(1));

	mrb_define_method(mrb, mrb->kernel_module, "delay", mrb_kernel_delay, MRB_ARGS_REQ(1));
	mrb_define_method(mrb, mrb->kernel_module, "millis", mrb_kernel_millis, MRB_ARGS_NONE());
	mrb_define_method(mrb, mrb->kernel_module, "micros", mrb_kernel_micros, MRB_ARGS_NONE());

	mrb_define_method(mrb, mrb->kernel_module, "led", mrb_kernel_led, MRB_ARGS_REQ(1));


	struct RClass *El_PsyModule = mrb_define_module(mrb, "El_Psy");
	mrb_define_module_function(mrb, El_PsyModule, "Congroo", mrb_El_Psy_congroo, MRB_ARGS_NONE());
}
