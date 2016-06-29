/*
 * このファイルは tecsgen により自動生成されました
 * このファイルを編集して使用することは、意図されていません
 */
#ifndef tSIOPortGRPeachMain_TECSGEN_H
#define tSIOPortGRPeachMain_TECSGEN_H

/*
 * celltype          :  tSIOPortGRPeachMain
 * global name       :  tSIOPortGRPeachMain
 * idx_is_id(actual) :  no(no)
 * singleton         :  no
 * has_CB            :  false
 * has_INIB          :  false
 * rom               :  yes
 * CB initializer    :  no
 */

/* グローバルヘッダ #_IGH_# */
#include "global_tecsgen.h"

/* シグニチャヘッダ #_ISH_# */
#include "sSIOPort_tecsgen.h"
#include "siSIOCBR_tecsgen.h"
#include "sInterruptRequest_tecsgen.h"

#ifndef TOPPERS_MACRO_ONLY

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
/* セル CB (ダミー)型宣言 #_CCDP_# */
typedef struct tag_tSIOPortGRPeachMain_CB {
    int  dummy;
} tSIOPortGRPeachMain_CB;
extern tSIOPortGRPeachMain_CB  tSIOPortGRPeachMain_CB_tab[];

/* セルタイプのIDX型 #_CTIX_# */
typedef int   tSIOPortGRPeachMain_IDX;

/* 受け口関数プロトタイプ宣言 #_EPP_# */
/* sSIOPort */
Inline void         tSIOPortGRPeachMain_eSIOPort_open(tSIOPortGRPeachMain_IDX idx);
Inline void         tSIOPortGRPeachMain_eSIOPort_close(tSIOPortGRPeachMain_IDX idx);
Inline bool_t       tSIOPortGRPeachMain_eSIOPort_putChar(tSIOPortGRPeachMain_IDX idx, char c);
Inline int_t        tSIOPortGRPeachMain_eSIOPort_getChar(tSIOPortGRPeachMain_IDX idx);
Inline void         tSIOPortGRPeachMain_eSIOPort_enableCBR(tSIOPortGRPeachMain_IDX idx, uint_t cbrtn);
Inline void         tSIOPortGRPeachMain_eSIOPort_disableCBR(tSIOPortGRPeachMain_IDX idx, uint_t cbrtn);
/* siSIOCBR */
Inline void         tSIOPortGRPeachMain_eiSIOCBR_readySend(tSIOPortGRPeachMain_IDX idx);
Inline void         tSIOPortGRPeachMain_eiSIOCBR_readyReceive(tSIOPortGRPeachMain_IDX idx);
#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* TOPPERS_MACRO_ONLY */

/* 最適化のため参照するセルタイプの CB 型の定義を取込む #_ICT_# */
#ifndef  TOPPERS_CB_TYPE_ONLY
#define  tSIOPortGRPeachMain_CB_TYPE_ONLY
#define TOPPERS_CB_TYPE_ONLY
#endif  /* TOPPERS_CB_TYPE_ONLY */
#include "tSerialPortMain_tecsgen.h"
#include "tSCIF_tecsgen.h"
#include "tInterruptRequest_tecsgen.h"
#ifdef  tSIOPortGRPeachMain_CB_TYPE_ONLY
#undef TOPPERS_CB_TYPE_ONLY
#endif /* tSIOPortGRPeachMain_CB_TYPE_ONLY */
#define tSIOPortGRPeachMain_ID_BASE        (1)  /* ID のベース  #_NIDB_# */
#define tSIOPortGRPeachMain_N_CELL        (1)  /* セルの個数  #_NCEL_# */

/* IDXの正当性チェックマクロ #_CVI_# */
#define tSIOPortGRPeachMain_VALID_IDX(IDX) (1)

/* optional 呼び口をテストするマクロ #_TOCP_# */
#define tSIOPortGRPeachMain_is_ciSIOCBR_joined(p_that) \
	  (1)

/* セルCBを得るマクロ #_GCB_# */
#define tSIOPortGRPeachMain_GET_CELLCB(idx) ((void *)0)
 /* 呼び口関数マクロ #_CPM_# */
#define tSIOPortGRPeachMain_ciSIOCBR_readySend( p_that ) \
	  tSerialPortMain_eiSIOCBR_readySend( \
	   &tSerialPortMain_CB_tab[0] )
#define tSIOPortGRPeachMain_ciSIOCBR_readyReceive( p_that ) \
	  tSerialPortMain_eiSIOCBR_readyReceive( \
	   &tSerialPortMain_CB_tab[0] )
#define tSIOPortGRPeachMain_cSIOPort_open( p_that ) \
	  tSCIF_eSIOPort_open( \
	   &tSCIF_CB_tab[0] )
#define tSIOPortGRPeachMain_cSIOPort_close( p_that ) \
	  tSCIF_eSIOPort_close( \
	   &tSCIF_CB_tab[0] )
#define tSIOPortGRPeachMain_cSIOPort_putChar( p_that, c ) \
	  tSCIF_eSIOPort_putChar( \
	   &tSCIF_CB_tab[0], (c) )
#define tSIOPortGRPeachMain_cSIOPort_getChar( p_that ) \
	  tSCIF_eSIOPort_getChar( \
	   &tSCIF_CB_tab[0] )
#define tSIOPortGRPeachMain_cSIOPort_enableCBR( p_that, cbrtn ) \
	  tSCIF_eSIOPort_enableCBR( \
	   &tSCIF_CB_tab[0], (cbrtn) )
#define tSIOPortGRPeachMain_cSIOPort_disableCBR( p_that, cbrtn ) \
	  tSCIF_eSIOPort_disableCBR( \
	   &tSCIF_CB_tab[0], (cbrtn) )
#define tSIOPortGRPeachMain_cRxInterruptRequest_disable( p_that ) \
	  tInterruptRequest_eInterruptRequest_disable( \
	   &tInterruptRequest_CB_tab[0] )
#define tSIOPortGRPeachMain_cRxInterruptRequest_enable( p_that ) \
	  tInterruptRequest_eInterruptRequest_enable( \
	   &tInterruptRequest_CB_tab[0] )
#define tSIOPortGRPeachMain_cTxInterruptRequest_disable( p_that ) \
	  tInterruptRequest_eInterruptRequest_disable( \
	   &tInterruptRequest_CB_tab[1] )
#define tSIOPortGRPeachMain_cTxInterruptRequest_enable( p_that ) \
	  tInterruptRequest_eInterruptRequest_enable( \
	   &tInterruptRequest_CB_tab[1] )

#ifndef TOPPERS_MACRO_ONLY

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* 受け口スケルトン関数プロトタイプ宣言（VMT不要最適化により参照するもの） #_EPSP_# */

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* TOPPERS_MACRO_ONLY */

/* IDXの正当性チェックマクロ（短縮形） #_CVIA_# */
#define VALID_IDX(IDX)  tSIOPortGRPeachMain_VALID_IDX(IDX)


/* セルCBを得るマクロ(短縮形) #_GCBA_# */
#define GET_CELLCB(idx)  tSIOPortGRPeachMain_GET_CELLCB(idx)

/* CELLCB 型(短縮形) #_CCT_# */
#define CELLCB	tSIOPortGRPeachMain_CB

/* セルタイプのIDX型(短縮形) #_CTIXA_# */
#define CELLIDX	tSIOPortGRPeachMain_IDX

/* 呼び口関数マクロ（短縮形）#_CPMA_# */
#define ciSIOCBR_readySend( ) \
                      ((void)p_cellcb, tSIOPortGRPeachMain_ciSIOCBR_readySend( p_cellcb ))
#define ciSIOCBR_readyReceive( ) \
                      ((void)p_cellcb, tSIOPortGRPeachMain_ciSIOCBR_readyReceive( p_cellcb ))
#define cSIOPort_open( ) \
                      ((void)p_cellcb, tSIOPortGRPeachMain_cSIOPort_open( p_cellcb ))
#define cSIOPort_close( ) \
                      ((void)p_cellcb, tSIOPortGRPeachMain_cSIOPort_close( p_cellcb ))
#define cSIOPort_putChar( c ) \
                      ((void)p_cellcb, tSIOPortGRPeachMain_cSIOPort_putChar( p_cellcb, c ))
#define cSIOPort_getChar( ) \
                      ((void)p_cellcb, tSIOPortGRPeachMain_cSIOPort_getChar( p_cellcb ))
#define cSIOPort_enableCBR( cbrtn ) \
                      ((void)p_cellcb, tSIOPortGRPeachMain_cSIOPort_enableCBR( p_cellcb, cbrtn ))
#define cSIOPort_disableCBR( cbrtn ) \
                      ((void)p_cellcb, tSIOPortGRPeachMain_cSIOPort_disableCBR( p_cellcb, cbrtn ))
#define cRxInterruptRequest_disable( ) \
                      ((void)p_cellcb, tSIOPortGRPeachMain_cRxInterruptRequest_disable( p_cellcb ))
#define cRxInterruptRequest_enable( ) \
                      ((void)p_cellcb, tSIOPortGRPeachMain_cRxInterruptRequest_enable( p_cellcb ))
#define cTxInterruptRequest_disable( ) \
                      ((void)p_cellcb, tSIOPortGRPeachMain_cTxInterruptRequest_disable( p_cellcb ))
#define cTxInterruptRequest_enable( ) \
                      ((void)p_cellcb, tSIOPortGRPeachMain_cTxInterruptRequest_enable( p_cellcb ))

/* optional 呼び口をテストするマクロ（短縮形） #_TOCPA_# */
#define is_ciSIOCBR_joined()\
		tSIOPortGRPeachMain_is_ciSIOCBR_joined(p_cellcb)

/* 受け口関数マクロ（短縮形） #_EPM_# */
#define eSIOPort_open    tSIOPortGRPeachMain_eSIOPort_open
#define eSIOPort_close   tSIOPortGRPeachMain_eSIOPort_close
#define eSIOPort_putChar tSIOPortGRPeachMain_eSIOPort_putChar
#define eSIOPort_getChar tSIOPortGRPeachMain_eSIOPort_getChar
#define eSIOPort_enableCBR tSIOPortGRPeachMain_eSIOPort_enableCBR
#define eSIOPort_disableCBR tSIOPortGRPeachMain_eSIOPort_disableCBR
#define eiSIOCBR_readySend tSIOPortGRPeachMain_eiSIOCBR_readySend
#define eiSIOCBR_readyReceive tSIOPortGRPeachMain_eiSIOCBR_readyReceive

/* イテレータコード (FOREACH_CELL)の生成(CB,INIB は存在しない) #_NFEC_# */
#define FOREACH_CELL(i,p_cb)   \
    for((i)=0;(i)<0;(i)++){

#define END_FOREACH_CELL   }

/* CB 初期化マクロ #_CIM_# */
#ifndef TOPPERS_MACRO_ONLY

/* inline ヘッダの include #_INL_# */
#include "tSIOPortGRPeachMain_inline.h"

#endif /* TOPPERS_MACRO_ONLY */

#ifdef TOPPERS_CB_TYPE_ONLY

/* inline のための undef #_UDF_# */
#undef VALID_IDX
#undef GET_CELLCB
#undef CELLCB
#undef CELLIDX
#undef tSIOPortGRPeachMain_IDX
#undef FOREACH_CELL
#undef END_FOREACH_CELL
#undef INITIALIZE_CB
#undef SET_CB_INIB_POINTER
#undef is_ciSIOCBR_joined
#undef tSIOPortGRPeachMain_ciSIOCBR_readySend
#undef ciSIOCBR_readySend
#undef tSIOPortGRPeachMain_ciSIOCBR_readyReceive
#undef ciSIOCBR_readyReceive
#undef tSIOPortGRPeachMain_cSIOPort_open
#undef cSIOPort_open
#undef tSIOPortGRPeachMain_cSIOPort_close
#undef cSIOPort_close
#undef tSIOPortGRPeachMain_cSIOPort_putChar
#undef cSIOPort_putChar
#undef tSIOPortGRPeachMain_cSIOPort_getChar
#undef cSIOPort_getChar
#undef tSIOPortGRPeachMain_cSIOPort_enableCBR
#undef cSIOPort_enableCBR
#undef tSIOPortGRPeachMain_cSIOPort_disableCBR
#undef cSIOPort_disableCBR
#undef tSIOPortGRPeachMain_cRxInterruptRequest_disable
#undef cRxInterruptRequest_disable
#undef tSIOPortGRPeachMain_cRxInterruptRequest_enable
#undef cRxInterruptRequest_enable
#undef tSIOPortGRPeachMain_cTxInterruptRequest_disable
#undef cTxInterruptRequest_disable
#undef tSIOPortGRPeachMain_cTxInterruptRequest_enable
#undef cTxInterruptRequest_enable
#undef eSIOPort_open
#undef eSIOPort_close
#undef eSIOPort_putChar
#undef eSIOPort_getChar
#undef eSIOPort_enableCBR
#undef eSIOPort_disableCBR
#undef eiSIOCBR_readySend
#undef eiSIOCBR_readyReceive
#endif /* TOPPERS_CB_TYPE_ONLY */

#endif /* tSIOPortGRPeachMain_TECSGENH */
