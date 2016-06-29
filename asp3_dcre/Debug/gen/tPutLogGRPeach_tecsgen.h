/*
 * このファイルは tecsgen により自動生成されました
 * このファイルを編集して使用することは、意図されていません
 */
#ifndef tPutLogGRPeach_TECSGEN_H
#define tPutLogGRPeach_TECSGEN_H

/*
 * celltype          :  tPutLogGRPeach
 * global name       :  tPutLogGRPeach
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
#include "sPutLog_tecsgen.h"
#include "sSIOPort_tecsgen.h"

#ifndef TOPPERS_MACRO_ONLY

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
/* セル CB (ダミー)型宣言 #_CCDP_# */
typedef struct tag_tPutLogGRPeach_CB {
    int  dummy;
} tPutLogGRPeach_CB;
/* シングルトンセル CB プロトタイプ宣言 #_SCP_# */


/* セルタイプのIDX型 #_CTIX_# */
typedef int   tPutLogGRPeach_IDX;

/* 受け口関数プロトタイプ宣言 #_EPP_# */
/* sPutLog */
void         tPutLogGRPeach_ePutLog_putChar( char c);
#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* TOPPERS_MACRO_ONLY */

/* 最適化のため参照するセルタイプの CB 型の定義を取込む #_ICT_# */
#ifndef  TOPPERS_CB_TYPE_ONLY
#define  tPutLogGRPeach_CB_TYPE_ONLY
#define TOPPERS_CB_TYPE_ONLY
#endif  /* TOPPERS_CB_TYPE_ONLY */
#include "tSIOPortGRPeachMain_tecsgen.h"
#ifdef  tPutLogGRPeach_CB_TYPE_ONLY
#undef TOPPERS_CB_TYPE_ONLY
#endif /* tPutLogGRPeach_CB_TYPE_ONLY */
#ifndef TOPPERS_CB_TYPE_ONLY


/* セルCBを得るマクロ #_GCB_# */
#define tPutLogGRPeach_GET_CELLCB(idx) ((void *)0)
 /* 呼び口関数マクロ #_CPM_# */
#define tPutLogGRPeach_cSIOPort_open( ) \
	  tSIOPortGRPeachMain_eSIOPort_open( \
	   (tSIOPortGRPeachMain_IDX)0 )
#define tPutLogGRPeach_cSIOPort_close( ) \
	  tSIOPortGRPeachMain_eSIOPort_close( \
	   (tSIOPortGRPeachMain_IDX)0 )
#define tPutLogGRPeach_cSIOPort_putChar( c ) \
	  tSIOPortGRPeachMain_eSIOPort_putChar( \
	   (tSIOPortGRPeachMain_IDX)0, (c) )
#define tPutLogGRPeach_cSIOPort_getChar( ) \
	  tSIOPortGRPeachMain_eSIOPort_getChar( \
	   (tSIOPortGRPeachMain_IDX)0 )
#define tPutLogGRPeach_cSIOPort_enableCBR( cbrtn ) \
	  tSIOPortGRPeachMain_eSIOPort_enableCBR( \
	   (tSIOPortGRPeachMain_IDX)0, (cbrtn) )
#define tPutLogGRPeach_cSIOPort_disableCBR( cbrtn ) \
	  tSIOPortGRPeachMain_eSIOPort_disableCBR( \
	   (tSIOPortGRPeachMain_IDX)0, (cbrtn) )

#endif /* TOPPERS_CB_TYPE_ONLY */

#ifndef TOPPERS_MACRO_ONLY

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* 受け口スケルトン関数プロトタイプ宣言（VMT不要最適化により参照するもの） #_EPSP_# */

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* TOPPERS_MACRO_ONLY */

#ifndef TOPPERS_CB_TYPE_ONLY


/* セルCBを得るマクロ(短縮形) #_GCBA_# */
#define GET_CELLCB(idx)  tPutLogGRPeach_GET_CELLCB(idx)

/* CELLCB 型(短縮形) #_CCT_# */
#define CELLCB	tPutLogGRPeach_CB

/* セルタイプのIDX型(短縮形) #_CTIXA_# */
#define CELLIDX	tPutLogGRPeach_IDX

/* 呼び口関数マクロ（短縮形）#_CPMA_# */
#define cSIOPort_open( ) \
                      tPutLogGRPeach_cSIOPort_open( )
#define cSIOPort_close( ) \
                      tPutLogGRPeach_cSIOPort_close( )
#define cSIOPort_putChar( c ) \
                      tPutLogGRPeach_cSIOPort_putChar( c )
#define cSIOPort_getChar( ) \
                      tPutLogGRPeach_cSIOPort_getChar( )
#define cSIOPort_enableCBR( cbrtn ) \
                      tPutLogGRPeach_cSIOPort_enableCBR( cbrtn )
#define cSIOPort_disableCBR( cbrtn ) \
                      tPutLogGRPeach_cSIOPort_disableCBR( cbrtn )


/* 受け口関数マクロ（短縮形） #_EPM_# */
#define ePutLog_putChar  tPutLogGRPeach_ePutLog_putChar

/* CB 初期化マクロ #_CIM_# */
#endif /* TOPPERS_CB_TYPE_ONLY */

#ifndef TOPPERS_MACRO_ONLY

#endif /* TOPPERS_MACRO_ONLY */

#endif /* tPutLogGRPeach_TECSGENH */
