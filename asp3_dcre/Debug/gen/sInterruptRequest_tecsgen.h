/*
 * このファイルは tecsgen により自動生成されました
 * このファイルを編集して使用することは、意図されていません
 */
#ifndef sInterruptRequest_TECSGEN_H
#define sInterruptRequest_TECSGEN_H

/*
 * signature   :  sInterruptRequest
 * global name :  sInterruptRequest
 * context     :  task
 */

#ifndef TOPPERS_MACRO_ONLY

/* シグニチャディスクリプタ #_SD_# */
struct tag_sInterruptRequest_VDES {
    struct tag_sInterruptRequest_VMT *VMT;
};

/* シグニチャ関数テーブル #_SFT_# */
struct tag_sInterruptRequest_VMT {
    ER             (*disable__T)( const struct tag_sInterruptRequest_VDES *edp );
    ER             (*enable__T)( const struct tag_sInterruptRequest_VDES *edp );
};

/* シグニチャディスクリプタ(動的結合用) #_SDES_# */
typedef struct { struct tag_sInterruptRequest_VDES *vdes; } Descriptor( sInterruptRequest );
#endif /* TOPPERS_MACRO_ONLY */

/* function id */
#define	FUNCID_SINTERRUPTREQUEST_DISABLE       (1)
#define	FUNCID_SINTERRUPTREQUEST_ENABLE        (2)

#endif /* sInterruptRequest_TECSGEN_H */
