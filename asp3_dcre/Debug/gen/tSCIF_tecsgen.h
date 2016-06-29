/*
 * このファイルは tecsgen により自動生成されました
 * このファイルを編集して使用することは、意図されていません
 */
#ifndef tSCIF_TECSGEN_H
#define tSCIF_TECSGEN_H

/*
 * celltype          :  tSCIF
 * global name       :  tSCIF
 * idx_is_id(actual) :  no(no)
 * singleton         :  no
 * has_CB            :  true
 * has_INIB          :  true
 * rom               :  yes
 * CB initializer    :  yes
 */

/* グローバルヘッダ #_IGH_# */
#include "global_tecsgen.h"

/* シグニチャヘッダ #_ISH_# */
#include "sSIOPort_tecsgen.h"
#include "siSIOCBR_tecsgen.h"
#include "siHandlerBody_tecsgen.h"

#ifndef TOPPERS_MACRO_ONLY

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
/* セル INIB 型宣言 #_CIP_# */
typedef const struct tag_tSCIF_INIB {
    /* call port #_TCP_# */ 
    /* call port #_NEP_# */ 
    /* attribute(RO) #_ATO_# */ 
    uintptr_t      baseAddress;
    uint32_t       baudRate;
}  tSCIF_INIB;
/* セル CB 型宣言 #_CCTPA_# */
typedef struct tag_tSCIF_CB {
    tSCIF_INIB  *_inib;
    /* var #_VA_# */ 
    bool_t         initialized;
}  tSCIF_CB;
extern tSCIF_CB  tSCIF_CB_tab[];

/* セルタイプのIDX型 #_CTIX_# */
typedef struct tag_tSCIF_CB *tSCIF_IDX;

/* 受け口関数プロトタイプ宣言 #_EPP_# */
/* sSIOPort */
void         tSCIF_eSIOPort_open(tSCIF_IDX idx);
void         tSCIF_eSIOPort_close(tSCIF_IDX idx);
bool_t       tSCIF_eSIOPort_putChar(tSCIF_IDX idx, char c);
int_t        tSCIF_eSIOPort_getChar(tSCIF_IDX idx);
void         tSCIF_eSIOPort_enableCBR(tSCIF_IDX idx, uint_t cbrtn);
void         tSCIF_eSIOPort_disableCBR(tSCIF_IDX idx, uint_t cbrtn);
/* siHandlerBody */
void         tSCIF_eiRxISR_main(tSCIF_IDX idx);
/* siHandlerBody */
void         tSCIF_eiTxISR_main(tSCIF_IDX idx);
#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* TOPPERS_MACRO_ONLY */

/* 最適化のため参照するセルタイプの CB 型の定義を取込む #_ICT_# */
#ifndef  TOPPERS_CB_TYPE_ONLY
#define  tSCIF_CB_TYPE_ONLY
#define TOPPERS_CB_TYPE_ONLY
#endif  /* TOPPERS_CB_TYPE_ONLY */
#include "tSIOPortGRPeachMain_tecsgen.h"
#ifdef  tSCIF_CB_TYPE_ONLY
#undef TOPPERS_CB_TYPE_ONLY
#endif /* tSCIF_CB_TYPE_ONLY */
#ifndef TOPPERS_CB_TYPE_ONLY

#define tSCIF_ID_BASE               (1)  /* ID のベース  #_NIDB_# */
#define tSCIF_N_CELL                (1)  /* セルの個数  #_NCEL_# */

/* IDXの正当性チェックマクロ #_CVI_# */
#define tSCIF_VALID_IDX(IDX) (1)


/* セルCBを得るマクロ #_GCB_# */
#define tSCIF_GET_CELLCB(idx) (idx)

/* 属性アクセスマクロ #_AAM_# */
#define tSCIF_ATTR_baseAddress( p_that )	((p_that)->_inib->baseAddress)
#define tSCIF_ATTR_baudRate( p_that )	((p_that)->_inib->baudRate)

#define tSCIF_GET_baseAddress(p_that)	((p_that)->_inib->baseAddress)
#define tSCIF_GET_baudRate(p_that)	((p_that)->_inib->baudRate)


/* var アクセスマクロ #_VAM_# */
#define tSCIF_VAR_initialized(p_that)	((p_that)->initialized)

#define tSCIF_GET_initialized(p_that)	((p_that)->initialized)
#define tSCIF_SET_initialized(p_that,val)	((p_that)->initialized=(val))

 /* 呼び口関数マクロ #_CPM_# */
#define tSCIF_ciSIOCBR_readySend( p_that ) \
	  tSIOPortGRPeachMain_eiSIOCBR_readySend( \
	   (tSIOPortGRPeachMain_IDX)0 )
#define tSCIF_ciSIOCBR_readyReceive( p_that ) \
	  tSIOPortGRPeachMain_eiSIOCBR_readyReceive( \
	   (tSIOPortGRPeachMain_IDX)0 )

#endif /* TOPPERS_CB_TYPE_ONLY */

#ifndef TOPPERS_MACRO_ONLY

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* 受け口スケルトン関数プロトタイプ宣言（VMT不要最適化により参照するもの） #_EPSP_# */
/* eiRxISR */
void           tSCIF_eiRxISR_main_skel( const struct tag_siHandlerBody_VDES *epd);
/* eiTxISR */
void           tSCIF_eiTxISR_main_skel( const struct tag_siHandlerBody_VDES *epd);

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* TOPPERS_MACRO_ONLY */

#ifndef TOPPERS_CB_TYPE_ONLY

/* IDXの正当性チェックマクロ（短縮形） #_CVIA_# */
#define VALID_IDX(IDX)  tSCIF_VALID_IDX(IDX)


/* セルCBを得るマクロ(短縮形) #_GCBA_# */
#define GET_CELLCB(idx)  tSCIF_GET_CELLCB(idx)

/* CELLCB 型(短縮形) #_CCT_# */
#define CELLCB	tSCIF_CB

/* セルタイプのIDX型(短縮形) #_CTIXA_# */
#define CELLIDX	tSCIF_IDX


/* 属性アクセスマクロ(短縮形) #_AAMA_# */
#define ATTR_baseAddress     tSCIF_ATTR_baseAddress( p_cellcb )
#define ATTR_baudRate        tSCIF_ATTR_baudRate( p_cellcb )


/* var アクセスマクロ(短縮形) #_VAMA_# */
#define VAR_initialized      tSCIF_VAR_initialized( p_cellcb )

/* 呼び口関数マクロ（短縮形）#_CPMA_# */
#define ciSIOCBR_readySend( ) \
                      ((void)p_cellcb, tSCIF_ciSIOCBR_readySend( p_cellcb ))
#define ciSIOCBR_readyReceive( ) \
                      ((void)p_cellcb, tSCIF_ciSIOCBR_readyReceive( p_cellcb ))


/* 受け口関数マクロ（短縮形） #_EPM_# */
#define eSIOPort_open    tSCIF_eSIOPort_open
#define eSIOPort_close   tSCIF_eSIOPort_close
#define eSIOPort_putChar tSCIF_eSIOPort_putChar
#define eSIOPort_getChar tSCIF_eSIOPort_getChar
#define eSIOPort_enableCBR tSCIF_eSIOPort_enableCBR
#define eSIOPort_disableCBR tSCIF_eSIOPort_disableCBR
#define eiRxISR_main     tSCIF_eiRxISR_main
#define eiTxISR_main     tSCIF_eiTxISR_main

/* イテレータコード (FOREACH_CELL)の生成 #_FEC_# */
#define FOREACH_CELL(i,p_cb)   \
    for( (i) = 0; (i) < tSCIF_N_CELL; (i)++ ){ \
       (p_cb) = &tSCIF_CB_tab[i];

#define END_FOREACH_CELL   }

/* CB 初期化マクロ #_CIM_# */
#define INITIALIZE_CB(p_that)\
	(p_that)->initialized = false;
#define SET_CB_INIB_POINTER(i,p_that)\
	(p_that)->_inib = &tSCIF_INIB_tab[(i)];

#endif /* TOPPERS_CB_TYPE_ONLY */

#ifndef TOPPERS_MACRO_ONLY

#endif /* TOPPERS_MACRO_ONLY */

#endif /* tSCIF_TECSGENH */
