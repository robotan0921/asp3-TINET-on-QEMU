/*
 * このファイルは tecsgen により自動生成されました
 * このファイルを編集して使用することは、意図されていません
 */
#ifndef GLOBAL_TECSGEN_H
#define GLOBAL_TECSGEN_H


/* import_C により import されるヘッダ #_IMP_# */
#include "tecs_kernel.h"
#include "syssvc/serial.h"
#include "t_syslog.h"
#include "gr_peach.h"
#include "rza1.h"
#include "scif.h"
/**/

#ifndef TOPPERS_MACRO_ONLY

 extern void tSerialPortMain_CB_initialize();
 extern void tSysLog_CB_initialize();
 extern void tSCIF_CB_initialize();

#define INITIALIZE_TECS() \
 	tSerialPortMain_CB_initialize();\
 	tSysLog_CB_initialize();\
 	tSCIF_CB_initialize();\
/* INITIALIZE_TECS terminator */

#define INITIALZE_TECSGEN() INITIALIZE_TECS()  /* for backward compatibility */

/* Descriptor for dynamic join */
#define Descriptor( signature_global_name )  DynDesc__ ## signature_global_name

#endif /* TOPPERS_MACRO_ONLY */

#define SIOSendReady   ((const uint_t)1)
#define SIOReceiveReady ((const uint_t)2)
#define DefaultTaskStackSize ((const size_t)4096)
#define LogTaskStackSize ((const size_t)4096)
#define BannerTargetName ((const char*)"GR-PEACH")
#define BannerCopyrightNotice ((const char*)"")

#endif /* GLOBAL_TECSGEN_H */
