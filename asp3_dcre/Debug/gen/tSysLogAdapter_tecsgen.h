/*
 * このファイルは tecsgen により自動生成されました
 * このファイルを編集して使用することは、意図されていません
 */
#ifndef tSysLogAdapter_TECSGEN_H
#define tSysLogAdapter_TECSGEN_H

/*
 * celltype          :  tSysLogAdapter
 * global name       :  tSysLogAdapter
 * idx_is_id(actual) :  no(no)
 * singleton         :  yes
 * has_CB            :  false
 * has_INIB          :  false
 * rom               :  yes
 * CB initializer    :  no
 */

/* グローバルヘッダ #_IGH_# */
#include "global_tecsgen.h"

/* シグニチャヘッダ #_ISH_# */
#include "sSysLog_tecsgen.h"

#ifndef TOPPERS_MACRO_ONLY

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
/* セル CB (ダミー)型宣言 #_CCDP_# */
typedef struct tag_tSysLogAdapter_CB {
    int  dummy;
} tSysLogAdapter_CB;
/* シングルトンセル CB プロトタイプ宣言 #_SCP_# */


/* セルタイプのIDX型 #_CTIX_# */
typedef int   tSysLogAdapter_IDX;
#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* TOPPERS_MACRO_ONLY */

/* 最適化のため参照するセルタイプの CB 型の定義を取込む #_ICT_# */
#ifndef  TOPPERS_CB_TYPE_ONLY
#define  tSysLogAdapter_CB_TYPE_ONLY
#define TOPPERS_CB_TYPE_ONLY
#endif  /* TOPPERS_CB_TYPE_ONLY */
#include "tSysLog_tecsgen.h"
#ifdef  tSysLogAdapter_CB_TYPE_ONLY
#undef TOPPERS_CB_TYPE_ONLY
#endif /* tSysLogAdapter_CB_TYPE_ONLY */
#ifndef TOPPERS_CB_TYPE_ONLY


/* セルCBを得るマクロ #_GCB_# */
#define tSysLogAdapter_GET_CELLCB(idx) ((void *)0)
 /* 呼び口関数マクロ #_CPM_# */
#define tSysLogAdapter_cSysLog_write( priority, p_syslog ) \
	  tSysLog_eSysLog_write( \
	    (priority), (p_syslog) )
#define tSysLogAdapter_cSysLog_read( p_syslog ) \
	  tSysLog_eSysLog_read( \
	    (p_syslog) )
#define tSysLogAdapter_cSysLog_mask( logMask, lowMask ) \
	  tSysLog_eSysLog_mask( \
	    (logMask), (lowMask) )
#define tSysLogAdapter_cSysLog_refer( pk_rlog ) \
	  tSysLog_eSysLog_refer( \
	    (pk_rlog) )
#define tSysLogAdapter_cSysLog_flush( ) \
	  tSysLog_eSysLog_flush( \
	    )

#endif /* TOPPERS_CB_TYPE_ONLY */

#ifndef TOPPERS_MACRO_ONLY

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* TOPPERS_MACRO_ONLY */

#ifndef TOPPERS_CB_TYPE_ONLY


/* セルCBを得るマクロ(短縮形) #_GCBA_# */
#define GET_CELLCB(idx)  tSysLogAdapter_GET_CELLCB(idx)

/* CELLCB 型(短縮形) #_CCT_# */
#define CELLCB	tSysLogAdapter_CB

/* セルタイプのIDX型(短縮形) #_CTIXA_# */
#define CELLIDX	tSysLogAdapter_IDX

/* 呼び口関数マクロ（短縮形）#_CPMA_# */
#define cSysLog_write( priority, p_syslog ) \
                      tSysLogAdapter_cSysLog_write( priority, p_syslog )
#define cSysLog_read( p_syslog ) \
                      tSysLogAdapter_cSysLog_read( p_syslog )
#define cSysLog_mask( logMask, lowMask ) \
                      tSysLogAdapter_cSysLog_mask( logMask, lowMask )
#define cSysLog_refer( pk_rlog ) \
                      tSysLogAdapter_cSysLog_refer( pk_rlog )
#define cSysLog_flush( ) \
                      tSysLogAdapter_cSysLog_flush( )

/* CB 初期化マクロ #_CIM_# */
#endif /* TOPPERS_CB_TYPE_ONLY */

#ifndef TOPPERS_MACRO_ONLY

#endif /* TOPPERS_MACRO_ONLY */

#endif /* tSysLogAdapter_TECSGENH */
