/*
 * このファイルは tecsgen により自動生成されました
 * このファイルを編集して使用することは、意図されていません
 */
#include "tSCIF_tecsgen.h"
#include "tSCIF_factory.h"

/* 受け口ディスクリプタ型 #_EDT_# */
/* eSIOPort : omitted by entry port optimize */

/* eiRxISR */
struct tag_tSCIF_eiRxISR_DES {
    const struct tag_siHandlerBody_VMT *vmt;
    tSCIF_IDX  idx;
};

/* eiTxISR */
struct tag_tSCIF_eiTxISR_DES {
    const struct tag_siHandlerBody_VMT *vmt;
    tSCIF_IDX  idx;
};

/* 受け口スケルトン関数 #_EPSF_# */
/* eSIOPort : omitted by entry port optimize */
/* eiRxISR */
void           tSCIF_eiRxISR_main_skel( const struct tag_siHandlerBody_VDES *epd)
{
    struct tag_tSCIF_eiRxISR_DES *lepd
        = (struct tag_tSCIF_eiRxISR_DES *)epd;
    tSCIF_eiRxISR_main( lepd->idx );
}
/* eiTxISR */
void           tSCIF_eiTxISR_main_skel( const struct tag_siHandlerBody_VDES *epd)
{
    struct tag_tSCIF_eiTxISR_DES *lepd
        = (struct tag_tSCIF_eiTxISR_DES *)epd;
    tSCIF_eiTxISR_main( lepd->idx );
}

/* 受け口スケルトン関数テーブル #_EPSFT_# */
/* eSIOPort : omitted by entry port optimize */
/* eiRxISR */
const struct tag_siHandlerBody_VMT tSCIF_eiRxISR_MT_ = {
    tSCIF_eiRxISR_main_skel,
};
/* eiTxISR */
const struct tag_siHandlerBody_VMT tSCIF_eiTxISR_MT_ = {
    tSCIF_eiTxISR_main_skel,
};

/* 呼び口の参照する受け口ディスクリプタ(実際の型と相違した定義) #_CPEPD_# */

/* 呼び口配列 #_CPA_# */

/* 属性・変数の配列 #_AVAI_# */
/* セル INIB #_INIB_# */
tSCIF_INIB tSCIF_INIB_tab[] = {
    /* cell: tSCIF_CB_tab[0]:  SIOPortTarget1_SCIF id=1 */
    {
        /* call port #_CP_# */ 
        /* entry port #_EP_# */ 
        /* attribute(RO) */ 
        SCIF2_BASE,                              /* baseAddress */
        115200,                                  /* baudRate */
    },
};

/* セル CB #_CB_# */
struct tag_tSCIF_CB tSCIF_CB_tab[1];
/* 受け口ディスクリプタ #_EPD_# */
/* eSIOPort : omitted by entry port optimize */
extern const struct tag_tSCIF_eiRxISR_DES SIOPortTarget1_SCIF_eiRxISR_des;
const struct tag_tSCIF_eiRxISR_DES SIOPortTarget1_SCIF_eiRxISR_des = {
    &tSCIF_eiRxISR_MT_,
    &tSCIF_CB_tab[0],     /* CB */
};
extern const struct tag_tSCIF_eiTxISR_DES SIOPortTarget1_SCIF_eiTxISR_des;
const struct tag_tSCIF_eiTxISR_DES SIOPortTarget1_SCIF_eiTxISR_des = {
    &tSCIF_eiTxISR_MT_,
    &tSCIF_CB_tab[0],     /* CB */
};
/* CB 初期化コード #_CIC_# */
void
tSCIF_CB_initialize()
{
    tSCIF_CB	*p_cb;
    int		i;
    FOREACH_CELL(i,p_cb)
        SET_CB_INIB_POINTER(i,p_cb)
        INITIALIZE_CB(p_cb)
    END_FOREACH_CELL
}
