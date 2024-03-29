/*
 *  TOPPERS ECHONET Lite Communication Middleware
 * 
 *  Copyright (C) 2014-2016 Cores Co., Ltd. Japan
 * 
 *  上記著作権者は，以下の(1)～(4)の条件を満たす場合に限り，本ソフトウェ
 *  ア（本ソフトウェアを改変したものを含む．以下同じ）を使用・複製・改
 *  変・再配布（以下，利用と呼ぶ）することを無償で許諾する．
 *  (1) 本ソフトウェアをソースコードの形で利用する場合には，上記の著作
 *      権表示，この利用条件および下記の無保証規定が，そのままの形でソー
 *      スコード中に含まれていること．
 *  (2) 本ソフトウェアを，ライブラリ形式など，他のソフトウェア開発に使
 *      用できる形で再配布する場合には，再配布に伴うドキュメント（利用
 *      者マニュアルなど）に，上記の著作権表示，この利用条件および下記
 *      の無保証規定を掲載すること．
 *  (3) 本ソフトウェアを，機器に組み込むなど，他のソフトウェア開発に使
 *      用できない形で再配布する場合には，次のいずれかの条件を満たすこ
 *      と．
 *    (a) 再配布に伴うドキュメント（利用者マニュアルなど）に，上記の著
 *        作権表示，この利用条件および下記の無保証規定を掲載すること．
 *    (b) 再配布の形態を，別に定める方法によって，TOPPERSプロジェクトに
 *        報告すること．
 *  (4) 本ソフトウェアの利用により直接的または間接的に生じるいかなる損
 *      害からも，上記著作権者およびTOPPERSプロジェクトを免責すること．
 *      また，本ソフトウェアのユーザまたはエンドユーザからのいかなる理
 *      由に基づく請求からも，上記著作権者およびTOPPERSプロジェクトを
 *      免責すること．
 * 
 *  本ソフトウェアは，無保証で提供されているものである．上記著作権者お
 *  よびTOPPERSプロジェクトは，本ソフトウェアに関して，特定の使用目的
 *  に対する適合性も含めて，いかなる保証も行わない．また，本ソフトウェ
 *  アの利用により直接的または間接的に生じたいかなる損害に関しても，そ
 *  の責任を負わない．
 * 
 */

#ifndef ECHONET_H
#define ECHONET_H

#include <stddef.h>
#include <stdint.h>
#include <mruby.h>

#include "echonet_class.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef TOPPERS_T_STDDEF_H
typedef char			bool_t;		/* 真偽値 */

typedef signed int		int_t;		/* 自然なサイズの符号付き整数 */
typedef unsigned int	uint_t;		/* 自然なサイズの符号無し整数 */

typedef int_t			ER;			/* エラーコード */
typedef int_t			ID;			/* オブジェクトのID番号 */
typedef uint_t			ATR;		/* オブジェクトの属性 */
typedef int_t			TMO;		/* タイムアウト指定 */

#ifndef NULL
#define NULL		0			/* 無効ポインタ */
#endif /* NULL */

#ifndef true
#define true		1			/* 真 */
#endif /* true */

#ifndef false
#define false		0			/* 偽 */
#endif /* false */

#define E_OK		0			/* 正常終了 */

#define E_SYS		(-5)		/* システムエラー */
#define E_PAR		(-17)		/* パラメータエラー */
#define E_NOMEM		(-33)		/* メモリ不足 */
#define E_OBJ		(-41)		/* オブジェクト状態エラー */
#define E_NOEXS		(-42)		/* オブジェクト未生成 */
#define E_TMOUT		(-50)		/* ポーリング失敗またはタイムアウト */
#define E_BOVR		(-58)		/* バッファオーバーフロー */
#define E_BRK		(-100)		/* ユーザーによる中断 */

#define TMO_FEVR	(-1)		/* 永久待ち */
#endif

#define EOBJ_NULL 0x00
#define EOBJ_LOCAL_NODE 0x01			/* 自ノード */
#define EOBJ_SYNC_REMOTE_NODE 0x02		/* 他ノード */
#define EOBJ_ASYNC_REMOTE_NODE 0x04		/* 他ノード（非同期） */
#define EOBJ_DEVICE 0x08				/* 機器オブジェクト */

#define EPC_NONE 0x00
#define EPC_RULE_SET 0x01				/* アクセスルール Set */
#define EPC_RULE_GET 0x02				/* アクセスルール Get */
#define EPC_RULE_ANNO 0x04				/* アクセスルール Anno */
#define EPC_ANNOUNCE 0x40				/* 状態変化時通知 */
#define EPC_VARIABLE 0x80				/* 可変長データ */

typedef enum _echonet_enod_id
{
	ENOD_NOT_MATCH_ID	= -1,
	ENOD_MULTICAST_ID	= 0,			/* マルチキャストアドレスID */
	ENOD_LOCAL_ID		= 1,			/* 自ノードアドレスID */
	ENOD_API_ID			= 2,			/* APIアドレスID */
	ENOD_REMOTE_ID		= 3,			/* 他ノードアドレスID */
} ECN_ENOD_ID;

/* ECHONET Lite規格 */
typedef enum
{
	ECN_EDH1_ECHONET_LITE	=	0x10
} ECN_EHD1_ECL_VERSION;

/* 電文形式1/2 */
typedef enum
{
	ECN_EDH2_FORMAT_1 = 0x81,	/* 電文形式1 */
	ECN_EDH2_FORMAT_2 = 0x82	/* 電文形式2 */
} ECN_EHD2_FORMAT;

/* ECHONET Liteサービスコード */
typedef enum _echonet_service_code
{
	ESV_NOP				=	0,		/* (機能指定なし)							*/
	ESV_SET_I			=	0x60,	/* プロパティ値書き込み要求（応答不要）		*/
	ESV_SET_C			=	0x61,	/* プロパティ値書き込み要求（応答要）		*/
	ESV_GET				=	0x62,	/* プロパティ値読み出し要求					*/
	ESV_INF_REQ			=	0x63,	/* プロパティ値通知要求						*/
	ESV_SET_GET			=	0x6E,	/* プロパティ値書き込み・読み出し要求		*/
	ESV_SET_RES			=	0x71,	/* プロパティ値書き込み応答					*/
	ESV_GET_RES			=	0x72,	/* プロパティ値読み出し応答					*/
	ESV_INF				=	0x73,	/* プロパティ値通知							*/
	ESV_INFC			=	0x74,	/* プロパティ値通知（応答要）				*/
	ESV_INFC_RES		=	0x7A,	/* プロパティ値通知応答						*/
	ESV_SET_GET_RES		=	0x7E,	/* プロパティ値書き込み・読み出し応答		*/
	ESV_SET_I_SNA		=	0x50,	/* プロパティ値書き込み要求不可応答			*/
	ESV_SET_C_SNA		=	0x51,	/* プロパティ値書き込み要求不可応答			*/
	ESV_GET_SNA			=	0x52,	/* プロパティ値読み出し不可応答				*/
	ESV_INF_SNA			=	0x53,	/* プロパティ値通知不可応答					*/
	ESV_SET_GET_SNA		=	0x5E	/* プロパティ値書き込み・読み出し不可応答	*/
} ECN_SRV_CODE;

#ifdef __CA850__
#pragma pack(1)
#elif __RX
#pragma pack
#elif _MSC_VER
#pragma pack(push, 1)
#endif
#ifndef __GNUC__
#define __attribute__(x)
#endif // !__GNUC__

/*
 *  ECHONET Lite電文ヘッダー
 */
typedef struct
{
	uint8_t	ehd1;		/* ECHONET Lite電文ヘッダー1 ECN_EHD1_ECL_VERSION */
	uint8_t	ehd2;		/* ECHONET Lite電文ヘッダー2 ECN_EHD2_FORMAT */
	uint16_t	tid;	/* トランザクションID */
} __attribute__((packed)) T_ECN_HDR;

/*
 *  ECHONET Liteオブジェクトコード
 */
typedef struct
{
	uint8_t	eojx1;		/* クラスグループコード */
	uint8_t	eojx2;		/* クラスコード */
	uint8_t	eojx3;		/* インスタンスコード */
} __attribute__((packed)) T_ECN_EOJ;

/*
 *  ECHONET Liteデータヘッダー
 */
typedef struct
{
	T_ECN_EOJ	seoj;	/* 送信元ECHONET Liteオブジェクト指定 */
	T_ECN_EOJ	deoj;	/* 相手先ECHONET Liteオブジェクト指定 */
	uint8_t	esv;		/* ECHONET Liteサービス (ECN_SRV_CODE) */
	uint8_t	opc;		/* 処理プロパティ数 */
} __attribute__((packed)) T_ECN_EDATA_BODY;

/*
 *  ECHONET Liteプロパティ
 */
typedef struct
{
	uint8_t	epc;		/* ECHONET Liteプロパティコード */
	uint8_t	pdc;		/* EDTのバイト数 */
	/*void	*p_edt;*/	/* プロパティ値データ */
} __attribute__((packed)) T_ECN_PRP;

/*
 *  ECHONET Liteデータ
 */
typedef struct
{
	T_ECN_HDR			ecn_hdr;
	T_ECN_EDATA_BODY	edata;
	T_ECN_PRP			ecn_prp;
} __attribute__((packed)) T_ECN_EDT_HDR;

/*
 *  ECHONET Lite 電文
 */
typedef struct echonet_object_data
{
	uint8_t _private1[192 - sizeof(int)];
	int trn_pos;
	T_ECN_EDT_HDR hdr;
	uint8_t _private2[64 - sizeof(T_ECN_EDT_HDR)];
} __attribute__((packed)) T_EDATA;

#ifdef __CA850__
#pragma pack(8)
#elif __RX
#pragma unpack
#elif _MSC_VER
#pragma pack(pop)
#endif

/*
 *  応答電文解析イテレーター
 */
typedef struct echonet_epc_enumerator
{
	T_EDATA *pk_esv;
	uint8_t count;			/* 今読み取り中のブロックにあるプロパティ総数 */
	uint8_t got_ct;			/* 今読み取り中のブロックで、読み取った数 */
	uint8_t next_blk_ct;	/* 後続ブロック数 */
	uint8_t is_eof;			/* 終端に達した時、非0 */
	int cur;
} T_ENUM_EPC;

typedef struct echonet_property_initialization_block EPRPINIB;

typedef struct ecnl_svc_task ecnl_svc_task_t;

/*
 * ECHONET Lite プロパティの設定関数
 */
typedef int (EPRP_SETTER)(ecnl_svc_task_t *svc, const EPRPINIB *item, const void *src, int size, bool_t *anno);

/*
 * ECHONET Lite プロパティの取得関数
 */
typedef int (EPRP_GETTER)(ecnl_svc_task_t *svc, const EPRPINIB *item, void *dst, int size);

/*
 *  ECHONET Lite プロパティ初期化ブロック
 */
struct echonet_property_initialization_block
{
	uint8_t		eprpcd;			/* ECHONET Lite プロパティコード */
	ATR			eprpatr;		/* ECHONET Lite プロパティ属性 */
	uint8_t		eprpsz;			/* ECHONET Lite プロパティのサイズ */
	intptr_t	exinf;			/* ECHONET Lite プロパティの拡張情報 */
	EPRP_SETTER	*eprpset;		/* ECHONET Lite プロパティの設定関数 */
	EPRP_GETTER	*eprpget;		/* ECHONET Lite プロパティの取得関数 */
};

#define TMIN_EOBJID		1		/* ECHONET Lite オブジェクトIDの最小値 */

/*
 *  ECHONET Lite オブジェクト初期化ブロック
 */
typedef struct echonet_object_initialization_block
{
	ATR			eobjatr;		/* ECHONET Lite オブジェクト属性 */
	ID			enodid;			/* ECHONET Lite ノードプロファイルオブジェクトID */
	intptr_t	exinf;			/* ECHONET Lite オブジェクトの拡張情報 */
	uint8_t		eojx1;			/* ECHONET Lite オブジェクトのクラスグループコード */
	uint8_t		eojx2;			/* ECHONET Lite オブジェクトのクラスコード */
	uint8_t		eojx3;			/* ECHONET Lite オブジェクトのインスタンスコード */
	const EPRPINIB **eprp;		/* ECHONET Lite プロパティ初期化ブロック */
	uint_t		eprpcnt;		/* ECHONET Lite プロパティ初期化ブロック数 */
} EOBJINIB;

/*
 *  ECHONET Lite ノード管理ブロック
 */
typedef struct echonet_object_control_block
{
	const EOBJINIB *profile;	/* ECHONET Lite ノードプロファイルへのポインタ */
	const EOBJINIB **eobjs;		/* ECHONET Lite オブジェクトリストへのポインタ */
	uint_t		eobjcnt;		/* ECHONET Lite オブジェクト数 */
} EOBJCB;

/*
 *  ECHONET Lite ノードと通信レイヤーアドレスの対応情報ブロックの定義
 */
typedef struct echonet_node_address_block
{
	bool_t		inuse;			/* 使用状況 */
	mrb_value	lcladdr;		/* 通信レイヤーアドレス */
} ENODADRB;

/*
 *  ECHONET Lite オブジェクト機能の初期化
 */
extern void initialize_echonet_object(void);

typedef EOBJINIB T_REOBJ;

typedef EPRPINIB T_RPRP;

typedef ENODADRB T_ENOD_ADDR;

/*
 * ECHONET Liteサービス処理開始
 */
ER ecn_sta_svc(ecnl_svc_task_t *svc);

/*
 * ECHONETオブジェクト参照
 */
ER ecn_ref_eobj(ecnl_svc_task_t *svc, ID eobjid, T_REOBJ *pk_eobj);

/*
 * ECHONETプロパティ参照
 */
ER ecn_ref_eprp(ecnl_svc_task_t *svc, ID eobjid, uint8_t epc, T_RPRP *pk_eprp);

/*
 * プロパティ値書き込み要求（応答不要）電文作成
 */
ER ecn_esv_seti(ecnl_svc_task_t *svc, T_EDATA **ppk_esv, ID eobjid, uint8_t epc, uint8_t pdc, const void *p_edt);

/*
 * プロパティ値書き込み要求（応答要）電文作成
 */
ER ecn_esv_setc(ecnl_svc_task_t *svc, T_EDATA **ppk_esv, ID eobjid, uint8_t epc, uint8_t pdc, const void *p_edt);

/*
 * プロパティ値読み出し要求電文作成
 */
ER ecn_esv_get(ecnl_svc_task_t *svc, T_EDATA **ppk_esv, ID eobjid, uint8_t epc);

/*
 * プロパティ値通知要求電文作成
 */
ER ecn_esv_inf_req(ecnl_svc_task_t *svc, T_EDATA **ppk_esv, ID eobjid, uint8_t epc);

/*
 * プロパティ値書き込み・読み出し要求電文作成
 */
ER ecn_esv_set_get(ecnl_svc_task_t *svc, T_EDATA **ppk_esv, ID eobjid, uint8_t epc, uint8_t pdc, const void *p_edt);

/*
 * プロパティ値書き込み・読み出し要求電文折り返し指定
 */
ER ecn_trn_set_get(mrb_state *mrb, T_EDATA *pk_esv, int *p_trn_pos);

/*
 * プロパティ値書き込み・読み出し要求電文終了指定
 */
ER ecn_end_set_get(mrb_state *mrb, T_EDATA *pk_esv, int trn_pos);

/*
 * プロパティ値通知（応答要）電文作成
 */
ER ecn_esv_infc(ecnl_svc_task_t *svc, T_EDATA **ppk_esv, ID eobjid, ID seobjid, uint8_t sepc);

/*
 * 要求電文へのプロパティ指定追加
 */
ER ecn_add_epc(mrb_state *mrb, T_EDATA *pk_esv, uint8_t epc);

/*
 * 要求電文へのプロパティデータ追加
 */
ER ecn_add_edt(mrb_state *mrb, T_EDATA *pk_esv, uint8_t epc, uint8_t pdc, const void *p_edt);

/*
 * 要求電文の送信
 */
ER ecn_snd_esv(ecnl_svc_task_t *svc, T_EDATA *pk_esv);

/*
 * 応答電文の受信ポーリング
 */
ER ecn_prcv_esv(ecnl_svc_task_t *svc, T_EDATA **ppk_esv);

/*
 * 応答電文の破棄
 */
ER ecn_rel_esv(mrb_state *mrb, T_EDATA *pk_esv);

/*
 * 応答電文の送信元ノードを取得する
 */
ID ecn_get_enod(ecnl_svc_task_t *svc, T_EDATA *pk_esv);

/*
 * 応答電文の送信元機器オブジェクトを取得する
 */
ID ecn_get_eobj(ecnl_svc_task_t *svc, T_EDATA *pk_esv);

/*
 * 応答電文解析イテレーター初期化
 */
ER ecn_itr_ini(T_ENUM_EPC *pk_itr, T_EDATA *pk_esv);

/*
 * 応答電文解析イテレーターインクリメント
 */
ER ecn_itr_nxt(mrb_state *mrb, T_ENUM_EPC *pk_itr, uint8_t *p_epc, uint8_t *p_pdc, void *p_edt);

/*
 * 応答電文待ちの割り込み送信
 */
ER ecn_brk_wai(ecnl_svc_task_t *svc, const void *p_dat, int datsz);

/*
 * 割り込みデータの取得
 */
ER ecn_get_brk_dat(mrb_state *mrb, T_EDATA *pk_esv, void *p_buf, int bufsz, int *p_datsz);

/*
 * データ設定関数
 */
int ecn_data_prop_set(ecnl_svc_task_t *svc, const EPRPINIB *item, const void *src, int size, bool_t *anno);

/*
 * データ取得関数
 */
int ecn_data_prop_get(ecnl_svc_task_t *svc, const EPRPINIB *item, void *dst, int size);

#ifdef __cplusplus
}
#endif

#endif // ECHONET_H
