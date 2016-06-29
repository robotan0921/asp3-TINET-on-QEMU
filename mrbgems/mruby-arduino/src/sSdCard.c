/*
 * SDカード関連
 *
 * Copyright (c) 2015 Minao Yamamoto
 *
 * This software is released under the MIT License.
 *
 * http://opensource.org/licenses/mit-license.php
 */
#include <arduino.h>

#include "mruby.h"
#include "mruby/string.h"
/* #include "sdmmc.h" */

SDMMC MicroSD;

File *Sd0;			/* コマンド用 */
File *Sd1;			/* コマンド用 */

/******************************************************/
/*  openしたファイルから1バイト読み込みます: SD.read */
/*  SD.read( number ) */
/*   number: ファイル番号 0 または 1 */
/*  戻り値 */
/*  0x00～0xFFが返る。ファイルの最後だったら-1が返る。 */
/******************************************************/
mrb_value mrb_sdcard_read(mrb_state *mrb, mrb_value self)
{
	int	num;

	mrb_get_args(mrb, "i", &num);

	int dat = -1;
	if (num == 0) {
		dat = file_read(Sd0);
	}
	else if (num == 1) {
		dat = file_read(Sd1);
	}

	return mrb_fixnum_value(dat);
}

/******************************************************/
/*  openしたファイルバイナリデータを書き込む: SD.write */
/*  SD.write( number, buf, len ) */
/*   number: ファイル番号 0 または 1 */
/*   buf: 書き込むデータ */
/*   len: 書き込むデータサイズ */
/*  戻り値 */
/*  実際に書いたバイト数 */
/******************************************************/
mrb_value mrb_sdcard_write(mrb_state *mrb, mrb_value self)
{
	int	num, len;
	mrb_value value;
	char	*str;

	mrb_get_args(mrb, "iSi", &num, &value, &len);

	str = RSTRING_PTR(value);


	int ret = 0;
	if (num == 0) {
		ret = file_write(Sd0, (unsigned char*)str, len);
	}
	else if (num == 1) {
		ret = file_write(Sd1, (unsigned char*)str, len);
	}

	return mrb_fixnum_value(ret);
}

/******************************************************/
/*  ファイルをオープンします: SD.open */
/*  SD.open( number, filename[, mode] ) */
/*   number: ファイル番号 0 または 1 */
/*   filename: ファイル名(8.3形式) */
/*   mode: 0:Read, 1:Append, 2:New Create */
/*  戻り値 */
/*  成功: 番号, 失敗: -1 */
/******************************************************/
mrb_value mrb_sdcard_open(mrb_state *mrb, mrb_value self)
{
	int	num;
	int mode;
	mrb_value value;
	char	*str;

	int n = mrb_get_args(mrb, "iS|i", &num, &value, &mode);

	str = RSTRING_PTR(value);

	if (n < 3) {
		mode = 0;
	}

	if (mode == 2) {
		/* 新規書き込み */
		if (SDMMC_exists(&MicroSD, str) == true) {
			SDMMC_remove(&MicroSD, str);
		}
	}

	int ret = -1;
	if (num == 0) {
		if (mode == 1 || mode == 2) {
			if (Sd0 = SDMMC_open(&MicroSD, str, FILE_WRITE)) {
				ret = num;
			}
		}
		else {
			if (Sd0 = SDMMC_open(&MicroSD, str, FILE_READ)) {
				ret = num;
			}
		}
	}
	else if (num == 1) {
		if (mode == 1 || mode == 2) {
			if (Sd1 = SDMMC_open(&MicroSD, str, FILE_WRITE)) {
				ret = num;
			}
		}
		else {
			if (Sd1 = SDMMC_open(&MicroSD, str, FILE_READ)) {
				ret = num;
			}
		}
	}

	return mrb_fixnum_value(ret);
}

/******************************************************/
/*  ファイルをクローズします: SD.close */
/*  SD.close( number ) */
/*   number: ファイル番号 0 または 1 */
/******************************************************/
mrb_value mrb_sdcard_close(mrb_state *mrb, mrb_value self)
{
	int	num;

	mrb_get_args(mrb, "i", &num);

	if (num == 0) {
		/* Sd0.flush(); */
		file_close(Sd0);
	}
	else if (num == 1) {
		/* Sd1.flush(); */
		file_close(Sd1);
	}

	return mrb_nil_value();			/* 戻り値は無しですよ。 */
}

/******************************************************/
/*  openしたファイルの読み出し位置を移動する: SD.seek */
/*  SD.seek( number, byte ) */
/*   number: ファイル番号 0 または 1 */
/*   byte: seekするバイト数(-1)でファイルの最後に移動する */
/*  戻り値 */
/*  成功: 1, 失敗: 0 */
/******************************************************/
mrb_value mrb_sdcard_seek(mrb_state *mrb, mrb_value self)
{
	int	num;
	int size;
	int ret = 0;

	mrb_get_args(mrb, "ii", &num, &size);

	if (num == 0) {
		if (size == -1) {
			if (file_seek(Sd0, file_size(Sd0))) {
				ret = 1;
			}
		}
		else {
			if (file_seek(Sd0, size)) {
				ret = 1;
			}
		}
	}
	else if (num == 1) {
		if (size == -1) {
			if (file_seek(Sd1, file_size(Sd1))) {
				ret = 1;
			}
		}
		else {
			if (file_seek(Sd1, size)) {
				ret = 1;
			}
		}
	}
	return mrb_fixnum_value(ret);
}

/******************************************************/
/* ファイルが存在するかどうか調べる: SD.exists */
/*  SD.exists( filename ) */
/*   filename: 調べるファイル名 */
/**/
/*  戻り値 */
/*  存在する: 1, 存在しない: 0 */
/******************************************************/
mrb_value mrb_sdcard_exists(mrb_state *mrb, mrb_value self)
{
	mrb_value value;
	char	*str;
	int ret = 0;

	int n = mrb_get_args(mrb, "S", &value);

	str = RSTRING_PTR(value);

	if (SDMMC_exists(&MicroSD, str) == true) {
		ret = 1;
	}

	return mrb_fixnum_value(ret);
}

/******************************************************/
/*  ディレクトリを作成する: SD.mkdir */
/*  SD.mkdir( dirname ) */
/*   dirname: 作成するディレクトリ名 */
/**/
/*  戻り値 */
/*  成功: 1, 失敗: 0 */
/******************************************************/
mrb_value mrb_sdcard_mkdir(mrb_state *mrb, mrb_value self)
{
	mrb_value value;
	char	*str;
	int ret = 0;

	int n = mrb_get_args(mrb, "S", &value);

	str = RSTRING_PTR(value);

	if (SDMMC_mkdir(&MicroSD, str) == true) {
		ret = 1;
	}

	return mrb_fixnum_value(ret);
}

/******************************************************/
/*  ファイルを削除する: SD.remove */
/*  SD.remove( filename ) */
/*   filename: 削除するファイル名 */
/**/
/*  戻り値 */
/*  成功: 1, 失敗: 0 */
/******************************************************/
mrb_value mrb_sdcard_remove(mrb_state *mrb, mrb_value self)
{
	mrb_value value;
	char	*str;
	int ret = 0;

	int n = mrb_get_args(mrb, "S", &value);

	str = RSTRING_PTR(value);

	if (SDMMC_remove(&MicroSD, str) == true) {
		ret = 1;
	}

	return mrb_fixnum_value(ret);
}

/******************************************************/
/*  ファイル名を変更する: SD.rename */
/*  SD.rename( oldfilename, newfilename ) */
/*   oldfilename: 旧ファイル名 */
/*   newfilename: 新しいファイル名 */
/**/
/*  戻り値 */
/*  成功: 1, 失敗: 0 */
/******************************************************/
mrb_value mrb_sdcard_rename(mrb_state *mrb, mrb_value self)
{
	mrb_value value1, value2;
	char	*str1;
	char	*str2;
	int ret = 0;

	int n = mrb_get_args(mrb, "SS", &value1, &value2);

	str1 = RSTRING_PTR(value1);
	str2 = RSTRING_PTR(value2);

	if (SDMMC_rename(&MicroSD, str1, str2) == true) {
		ret = 1;
	}

	return mrb_fixnum_value(ret);
}

/******************************************************/
/*  ディレクトリを削除する: SD.rmdir */
/*  SD.rmdir( dirname ) */
/*   dirname: 削除するディレクトリ名 */
/**/
/*  戻り値 */
/*  成功: 1, 失敗: 0 */
/******************************************************/
mrb_value mrb_sdcard_rmdir(mrb_state *mrb, mrb_value self)
{
	mrb_value value;
	char	*str;
	int ret = 0;

	int n = mrb_get_args(mrb, "S", &value);

	str = RSTRING_PTR(value);

	if (SDMMC_rmdir(&MicroSD, str) == true) {
		ret = 1;
	}

	return mrb_fixnum_value(ret);
}

//**************************************************
// openしたファイルの書き込みをフラッシュします: SD.flush
//	SD.flush( number )
//	number: ファイル番号 0 または 1
//**************************************************
mrb_value mrb_sdcard_flush(mrb_state *mrb, mrb_value self)
{
	int	num;

	mrb_get_args(mrb, "i", &num);

	if (num == 0) {
		file_flush(Sd0);
	}
	else if (num == 1) {
		file_flush(Sd1);
	}

	return mrb_nil_value();			//戻り値は無しですよ。
}

//**************************************************
// openしたファイルのサイズを取得します: SD.size
//	SD.size( number )
//	number: ファイル番号 0 または 1
//
// 戻り値
//	ファイルサイズ
//**************************************************
mrb_value mrb_sdcard_size(mrb_state *mrb, mrb_value self)
{
	int	num;
	mrb_int ret = 0;

	mrb_get_args(mrb, "i", &num);

	if (num == 0) {
		ret = file_size(Sd0);
	}
	else if (num == 1) {
		ret = file_size(Sd1);
	}

	return mrb_fixnum_value(ret);
}

//**************************************************
// openしたファイルのseek位置を取得します: SD.position
//	SD.position( number )
//	number: ファイル番号 0 または 1
//
// 戻り値
//	シーク位置
//**************************************************
mrb_value mrb_sdcard_position(mrb_state *mrb, mrb_value self)
{
	int	num;
	mrb_int ret = 0;

	mrb_get_args(mrb, "i", &num);

	if (num == 0) {
		ret = file_position(Sd0);
	}
	else if (num == 1) {
		ret = file_position(Sd1);
	}

	return mrb_fixnum_value(ret);
}

/******************************************************/
/*  ライブラリを定義します */
/******************************************************/
void sdcard_Init(mrb_state *mrb)
{
	/* SDカードライブラリを初期化します */
	SDMMC_begin(&MicroSD);
	Sd0 = SDMMC_open(&MicroSD, NULL, 0);			/* コマンド用 */
	Sd1 = SDMMC_open(&MicroSD, NULL, 0);			/* コマンド用 */

	struct RClass *sdcardModule = mrb_define_module(mrb, "SD");

	mrb_define_module_function(mrb, sdcardModule, "exists", mrb_sdcard_exists, MRB_ARGS_REQ(1));
	mrb_define_module_function(mrb, sdcardModule, "mkdir", mrb_sdcard_mkdir, MRB_ARGS_REQ(1));
	mrb_define_module_function(mrb, sdcardModule, "remove", mrb_sdcard_remove, MRB_ARGS_REQ(1));
	mrb_define_module_function(mrb, sdcardModule, "rename", mrb_sdcard_rename, MRB_ARGS_REQ(2));
	mrb_define_module_function(mrb, sdcardModule, "rmdir", mrb_sdcard_rmdir, MRB_ARGS_REQ(1));

	mrb_define_module_function(mrb, sdcardModule, "open", mrb_sdcard_open, MRB_ARGS_REQ(2) | MRB_ARGS_OPT(1));
	mrb_define_module_function(mrb, sdcardModule, "close", mrb_sdcard_close, MRB_ARGS_REQ(1));
	mrb_define_module_function(mrb, sdcardModule, "read", mrb_sdcard_read, MRB_ARGS_REQ(1));
	mrb_define_module_function(mrb, sdcardModule, "seek", mrb_sdcard_seek, MRB_ARGS_REQ(2));
	mrb_define_module_function(mrb, sdcardModule, "write", mrb_sdcard_write, MRB_ARGS_REQ(3));
	mrb_define_module_function(mrb, sdcardModule, "flush", mrb_sdcard_flush, MRB_ARGS_REQ(1));
	mrb_define_module_function(mrb, sdcardModule, "size", mrb_sdcard_size, MRB_ARGS_REQ(1));
	mrb_define_module_function(mrb, sdcardModule, "position", mrb_sdcard_position, MRB_ARGS_REQ(1));
}
