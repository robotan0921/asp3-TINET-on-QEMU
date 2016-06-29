/*
 * このファイルは tecsgen により自動生成されました
 * このファイルを編集して使用することは、意図されていません
 */
#include "tInterruptRequest_tecsgen.h"
#include "tInterruptRequest_factory.h"

/* 受け口ディスクリプタ型 #_EDT_# */
/* eInterruptRequest : omitted by entry port optimize */

/* 受け口スケルトン関数 #_EPSF_# */
/* eInterruptRequest : omitted by entry port optimize */

/* 受け口スケルトン関数テーブル #_EPSFT_# */
/* eInterruptRequest : omitted by entry port optimize */

/* 呼び口の参照する受け口ディスクリプタ(実際の型と相違した定義) #_CPEPD_# */


/* 呼び口配列 #_CPA_# */


/* 属性・変数の配列 #_AVAI_# */
/* セル INIB #_INIB_# */
tInterruptRequest_INIB tInterruptRequest_INIB_tab[] = {
    /* cell: tInterruptRequest_CB_tab[0]:  SIOPortTarget1_RxInterruptRequest id=1 */
    {
        /* entry port #_EP_# */ 
        /* attribute(RO) */ 
        INTNO_SCIF2_RXI,                         /* interruptNumber */
    },
    /* cell: tInterruptRequest_CB_tab[1]:  SIOPortTarget1_TxInterruptRequest id=2 */
    {
        /* entry port #_EP_# */ 
        /* attribute(RO) */ 
        INTNO_SCIF2_TXI,                         /* interruptNumber */
    },
};

/* 受け口ディスクリプタ #_EPD_# */
/* eInterruptRequest : omitted by entry port optimize */
/* eInterruptRequest : omitted by entry port optimize */
