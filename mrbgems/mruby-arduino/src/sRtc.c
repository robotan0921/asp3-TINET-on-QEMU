/*
 * RTC関連
 *
 * Copyright (c) 2015 Minao Yamamoto
 *
 * This software is released under the MIT License.
 *
 * http://opensource.org/licenses/mit-license.php
 */
#include <arduino.h>
/* #include <rtc.h> */

#include <mruby.h>
#include <mruby/array.h>

#include "../llbruby.h"
#include "sKernel.h"

/******************************************************/
/*  RTCの時計を取得します: Rtc.getDateTime */
/*   Rtc.getDateTime() */
/**/
/*   戻り値は以下のとおり */
/*   Year, Month, Day, Hour, Minute, Second */
/*   Year: 年 */
/*   Month: 月 */
/*   Day: 日 */
/*   Hour: 時 */
/*   Minute: 分 */
/*   Second: 秒 */
/*   @note        この関数の前にbeginを呼ばなくても、内部でbeginを呼び出すので心配ない */
/*   @note        内蔵RTCはBCDで値を扱うが、このライブラリはBCD→intへ変換するので気にしなくてよい */
/*   @note        24時間制である */
/*   @warning     RX63Nでは西暦20xx年代を想定しているため年は2桁しか意味を持たない。内部で2000を足している。 */
/******************************************************/
mrb_value mrb_rtc_getDateTime(mrb_state *mrb, mrb_value self)
{
	mrb_value arv[6];
	time_t rtc = rtc_read();
	struct tm *time = localtime(&rtc);

	arv[0] = mrb_fixnum_value(time->tm_year + 1900);
	arv[1] = mrb_fixnum_value(time->tm_mon + 1);
	arv[2] = mrb_fixnum_value(time->tm_mday);
	arv[3] = mrb_fixnum_value(time->tm_hour);
	arv[4] = mrb_fixnum_value(time->tm_min);
	arv[5] = mrb_fixnum_value(time->tm_sec);

	return mrb_ary_new_from_values(mrb, 6, arv);
}

/******************************************************/
/*  RTCの時計をセットします: Rtc.setDateTime */
/*   Rtc.setDateTime( Year, Month, Day, Hour, Minute, Second ) */
/*   Year: 年　0-99 */
/*   Month: 月 1-12 */
/*   Day: 日 0-3 */
/*   Hour: 時 0-23 */
/*   Minute: 分 0-59 */
/*   Second: 秒 0-59 */
/**/
/*   戻り値は以下のとおり */
/*   0: 失敗 */
/*   1: 成功 */
/**/
/*  @note        この関数の前にbeginを呼ばなくても、内部でbeginを呼び出すので心配ない */
/*  @note        内蔵RTCはBCDで値を扱うが、このライブラリはint→BCDへ変換するので気にしなくてよい */
/*  @note        24時間制である */
/*  @warning     RX63Nでは西暦20xx年代を想定しているため、年は2桁しか意味を持たない */
/******************************************************/
mrb_value mrb_rtc_setDateTime(mrb_state *mrb, mrb_value self)
{
	struct tm time;
	int ret = 0;

	mrb_get_args(mrb, "iiiiii", &time.tm_year, &time.tm_mon, &time.tm_mday, &time.tm_hour, &time.tm_min, &time.tm_sec);

	time.tm_year -= 1900;
	time.tm_mon -= 1;

	rtc_write(mktime(&time));
	ret = 1;

	return mrb_fixnum_value(ret);
}


/******************************************************/
/*  RTCを起動します: Rtc.begin */
/*   Rtc.begin() */
/**/
/*  戻り値は以下のとおり */
/*   0: 起動失敗 */
/*   1: 起動成功 */
/*   2: RTCは既に起動していた(成功) */
/******************************************************/
mrb_value mrb_rtc_begin(mrb_state *mrb, mrb_value self)
{
	if(rtc_isenabled())
		return mrb_fixnum_value(2);

	rtc_init();

	return mrb_fixnum_value(rtc_isenabled());
}

/******************************************************/
/*  ライブラリを定義します */
/******************************************************/
void rtc_Init(mrb_state *mrb)
{
	struct RClass *rtcModule = mrb_define_module(mrb, "Rtc");

	mrb_define_module_function(mrb, rtcModule, "begin", mrb_rtc_begin, MRB_ARGS_NONE());
	mrb_define_module_function(mrb, rtcModule, "setDateTime", mrb_rtc_setDateTime, MRB_ARGS_REQ(6));
	mrb_define_module_function(mrb, rtcModule, "getDateTime", mrb_rtc_getDateTime, MRB_ARGS_NONE());
}
