/* cfg1_out.c */
#define TOPPERS_CFG1_OUT
#include "kernel/kernel_int.h"
#include "gr_peach.h"
#include "target_timer.h"
#include "sample1n.h"
#include "tTask_tecsgen.h"
#include "tISR_tecsgen.h"
#include "tInitializeRoutine_tecsgen.h"
#include "tTerminateRoutine_tecsgen.h"
#include "sample1.h"
#include <itron.h>
#include <tinet_defs.h>
#include <tinet_config.h>
#include <net/if.h>
#include <net/if_ppp.h>
#include <net/if_loop.h>
#include <net/ethernet.h>
#include <net/if_arp.h>
#include <net/net.h>
#include <net/net_buf.h>
#include <net/net_timer.h>
#include <net/ppp_var.h>
#include <net/ether_var.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/ip6.h>
#include <netinet/ip_var.h>
#include <netinet/tcp.h>
#include <netinet/tcp_timer.h>
#include <netinet/tcp_var.h>
#include <netinet/udp_var.h>
#include <netinet6/in6.h>
#include <netinet6/ip6_var.h>
#include "device.h"
#include "tinet_target_config.h"
#include "sample1n.h"

#ifdef INT64_MAX
  typedef int64_t signed_t;
  typedef uint64_t unsigned_t;
#else
  typedef int32_t signed_t;
  typedef uint32_t unsigned_t;
#endif

#include "target_cfg1_out.h"
#include <limits.h>

const uint32_t TOPPERS_magic_number = 0x12345678;
const uint32_t TOPPERS_sizeof_signed_t = sizeof(signed_t);

const unsigned_t TOPPERS_cfg_CHAR_BIT = (unsigned_t)(CHAR_BIT);
const signed_t TOPPERS_cfg_SCHAR_MAX = (signed_t)(SCHAR_MAX);
const signed_t TOPPERS_cfg_SCHAR_MIN = (signed_t)(SCHAR_MIN);
const unsigned_t TOPPERS_cfg_UCHAR_MAX = (unsigned_t)(UCHAR_MAX);
const signed_t TOPPERS_cfg_CHAR_MAX = (signed_t)(CHAR_MAX);
const signed_t TOPPERS_cfg_CHAR_MIN = (signed_t)(CHAR_MIN);
const signed_t TOPPERS_cfg_SHRT_MAX = (signed_t)(SHRT_MAX);
const signed_t TOPPERS_cfg_SHRT_MIN = (signed_t)(SHRT_MIN);
const unsigned_t TOPPERS_cfg_USHRT_MAX = (unsigned_t)(USHRT_MAX);
const signed_t TOPPERS_cfg_INT_MAX = (signed_t)(INT_MAX);
const signed_t TOPPERS_cfg_INT_MIN = (signed_t)(INT_MIN);
const unsigned_t TOPPERS_cfg_UINT_MAX = (unsigned_t)(UINT_MAX);
const signed_t TOPPERS_cfg_LONG_MAX = (signed_t)(LONG_MAX);
const signed_t TOPPERS_cfg_LONG_MIN = (signed_t)(LONG_MIN);
const unsigned_t TOPPERS_cfg_ULONG_MAX = (unsigned_t)(ULONG_MAX);
const unsigned_t TOPPERS_cfg_TA_HLNG = (unsigned_t)(TA_HLNG);
const unsigned_t TOPPERS_cfg_TA_TFIFO = (unsigned_t)(TA_TFIFO);
const unsigned_t TOPPERS_cfg_TA_WSGL = (unsigned_t)(TA_WSGL);
const unsigned_t TOPPERS_cfg_NUM_IPV4ADDR_STR_BUFF = (unsigned_t)(NUM_IPV4ADDR_STR_BUFF);
const unsigned_t TOPPERS_cfg_NUM_IPV6ADDR_STR_BUFF = (unsigned_t)(NUM_IPV6ADDR_STR_BUFF);
const unsigned_t TOPPERS_cfg_NUM_MACADDR_STR_BUFF = (unsigned_t)(NUM_MACADDR_STR_BUFF);
const unsigned_t TOPPERS_cfg_TMO_IP4_FRAG_GET_NET_BUF = (unsigned_t)(TMO_IP4_FRAG_GET_NET_BUF);
const unsigned_t TOPPERS_cfg_TMO_IP6_FRAG_GET_NET_BUF = (unsigned_t)(TMO_IP6_FRAG_GET_NET_BUF);
const unsigned_t TOPPERS_cfg_TMO_PPP_GET_NET_BUF = (unsigned_t)(TMO_PPP_GET_NET_BUF);
const unsigned_t TOPPERS_cfg_TMO_ARP_GET_NET_BUF = (unsigned_t)(TMO_ARP_GET_NET_BUF);
const unsigned_t TOPPERS_cfg_TMO_TCP_GET_NET_BUF = (unsigned_t)(TMO_TCP_GET_NET_BUF);
const unsigned_t TOPPERS_cfg_TMO_TCP_OUTPUT = (unsigned_t)(TMO_TCP_OUTPUT);
const unsigned_t TOPPERS_cfg_TMO_UDP_OUTPUT = (unsigned_t)(TMO_UDP_OUTPUT);
const unsigned_t TOPPERS_cfg_TMO_ICMP_OUTPUT = (unsigned_t)(TMO_ICMP_OUTPUT);
const unsigned_t TOPPERS_cfg_TMO_ND6_NS_OUTPUT = (unsigned_t)(TMO_ND6_NS_OUTPUT);
const unsigned_t TOPPERS_cfg_TMO_ND6_NA_OUTPUT = (unsigned_t)(TMO_ND6_NA_OUTPUT);
const unsigned_t TOPPERS_cfg_TMO_ND6_RS_OUTPUT = (unsigned_t)(TMO_ND6_RS_OUTPUT);
const unsigned_t TOPPERS_cfg_TMO_ARP_OUTPUT = (unsigned_t)(TMO_ARP_OUTPUT);
const unsigned_t TOPPERS_cfg_TMO_ND6_RTR_SOL_DELAY = (unsigned_t)(TMO_ND6_RTR_SOL_DELAY);
const unsigned_t TOPPERS_cfg_TMO_ND6_RTR_SOL_INTERVAL = (unsigned_t)(TMO_ND6_RTR_SOL_INTERVAL);
const unsigned_t TOPPERS_cfg_TMO_IN_REDIRECT = (unsigned_t)(TMO_IN_REDIRECT);
const unsigned_t TOPPERS_cfg_TCP_OUT_TASK_STACK_SIZE = (unsigned_t)(TCP_OUT_TASK_STACK_SIZE);
const unsigned_t TOPPERS_cfg_UDP_OUT_TASK_STACK_SIZE = (unsigned_t)(UDP_OUT_TASK_STACK_SIZE);
const unsigned_t TOPPERS_cfg_PPP_INPUT_STACK_SIZE = (unsigned_t)(PPP_INPUT_STACK_SIZE);
const unsigned_t TOPPERS_cfg_PPP_OUTPUT_STACK_SIZE = (unsigned_t)(PPP_OUTPUT_STACK_SIZE);
const unsigned_t TOPPERS_cfg_ETHER_INPUT_STACK_SIZE = (unsigned_t)(ETHER_INPUT_STACK_SIZE);
const unsigned_t TOPPERS_cfg_ETHER_OUTPUT_STACK_SIZE = (unsigned_t)(ETHER_OUTPUT_STACK_SIZE);
const unsigned_t TOPPERS_cfg_LOOP_INPUT_STACK_SIZE = (unsigned_t)(LOOP_INPUT_STACK_SIZE);
const unsigned_t TOPPERS_cfg_LOOP_OUTPUT_STACK_SIZE = (unsigned_t)(LOOP_OUTPUT_STACK_SIZE);
const unsigned_t TOPPERS_cfg_NET_TIMER_STACK_SIZE = (unsigned_t)(NET_TIMER_STACK_SIZE);
const unsigned_t TOPPERS_cfg_TCP_OUT_TASK_PRIORITY = (unsigned_t)(TCP_OUT_TASK_PRIORITY);
const unsigned_t TOPPERS_cfg_UDP_OUT_TASK_PRIORITY = (unsigned_t)(UDP_OUT_TASK_PRIORITY);
const unsigned_t TOPPERS_cfg_PPP_INPUT_PRIORITY = (unsigned_t)(PPP_INPUT_PRIORITY);
const unsigned_t TOPPERS_cfg_PPP_OUTPUT_PRIORITY = (unsigned_t)(PPP_OUTPUT_PRIORITY);
const unsigned_t TOPPERS_cfg_ETHER_INPUT_PRIORITY = (unsigned_t)(ETHER_INPUT_PRIORITY);
const unsigned_t TOPPERS_cfg_ETHER_OUTPUT_PRIORITY = (unsigned_t)(ETHER_OUTPUT_PRIORITY);
const unsigned_t TOPPERS_cfg_LOOP_INPUT_PRIORITY = (unsigned_t)(LOOP_INPUT_PRIORITY);
const unsigned_t TOPPERS_cfg_LOOP_OUTPUT_PRIORITY = (unsigned_t)(LOOP_OUTPUT_PRIORITY);
const unsigned_t TOPPERS_cfg_NET_TIMER_PRIORITY = (unsigned_t)(NET_TIMER_PRIORITY);
const unsigned_t TOPPERS_cfg_NUM_DTQ_UDP_RCVQ = (unsigned_t)(NUM_DTQ_UDP_RCVQ);
const unsigned_t TOPPERS_cfg_NUM_DTQ_UDP_OUTPUT = (unsigned_t)(NUM_DTQ_UDP_OUTPUT);
const unsigned_t TOPPERS_cfg_NUM_DTQ_PPP_OUTPUT = (unsigned_t)(NUM_DTQ_PPP_OUTPUT);
const unsigned_t TOPPERS_cfg_NUM_DTQ_ETHER_OUTPUT = (unsigned_t)(NUM_DTQ_ETHER_OUTPUT);
const unsigned_t TOPPERS_cfg_NUM_DTQ_LOOP_INPUT = (unsigned_t)(NUM_DTQ_LOOP_INPUT);
const unsigned_t TOPPERS_cfg_NUM_DTQ_LOOP_OUTPUT = (unsigned_t)(NUM_DTQ_LOOP_OUTPUT);
const unsigned_t TOPPERS_cfg_TCP_REP_FLG_DYNAMIC = (unsigned_t)(TCP_REP_FLG_DYNAMIC);
const unsigned_t TOPPERS_cfg_TCP_REP_FLG_VALID = (unsigned_t)(TCP_REP_FLG_VALID);
const unsigned_t TOPPERS_cfg_TCP_CEP_FLG_ACK_NOW = (unsigned_t)(TCP_CEP_FLG_ACK_NOW);
const unsigned_t TOPPERS_cfg_TCP_CEP_FLG_DEL_ACK = (unsigned_t)(TCP_CEP_FLG_DEL_ACK);
const unsigned_t TOPPERS_cfg_TCP_CEP_FLG_SENT_FIN = (unsigned_t)(TCP_CEP_FLG_SENT_FIN);
const unsigned_t TOPPERS_cfg_TCP_CEP_FLG_NEED_SYN = (unsigned_t)(TCP_CEP_FLG_NEED_SYN);
const unsigned_t TOPPERS_cfg_TCP_CEP_FLG_NEED_FIN = (unsigned_t)(TCP_CEP_FLG_NEED_FIN);
const unsigned_t TOPPERS_cfg_TCP_CEP_FLG_FORCE = (unsigned_t)(TCP_CEP_FLG_FORCE);
const unsigned_t TOPPERS_cfg_TCP_CEP_FLG_NO_PUSH = (unsigned_t)(TCP_CEP_FLG_NO_PUSH);
const unsigned_t TOPPERS_cfg_TCP_CEP_FLG_NO_DELAY = (unsigned_t)(TCP_CEP_FLG_NO_DELAY);
const unsigned_t TOPPERS_cfg_TCP_CEP_FLG_FORCE_CLEAR = (unsigned_t)(TCP_CEP_FLG_FORCE_CLEAR);
const unsigned_t TOPPERS_cfg_TCP_CEP_FLG_POST_OUTPUT = (unsigned_t)(TCP_CEP_FLG_POST_OUTPUT);
const unsigned_t TOPPERS_cfg_TCP_CEP_FLG_RESERVE_OUTPUT = (unsigned_t)(TCP_CEP_FLG_RESERVE_OUTPUT);
const unsigned_t TOPPERS_cfg_TCP_CEP_FLG_DYNAMIC = (unsigned_t)(TCP_CEP_FLG_DYNAMIC);
const unsigned_t TOPPERS_cfg_TCP_CEP_FLG_VALID = (unsigned_t)(TCP_CEP_FLG_VALID);
const unsigned_t TOPPERS_cfg_TCP_CEP_FLG_CLOSE_AFTER_OUTPUT = (unsigned_t)(TCP_CEP_FLG_CLOSE_AFTER_OUTPUT);
const unsigned_t TOPPERS_cfg_TCP_CEP_FLG_RESTORE_NEXT_OUTPUT = (unsigned_t)(TCP_CEP_FLG_RESTORE_NEXT_OUTPUT);
const unsigned_t TOPPERS_cfg_TCP_CEP_FLG_WBCS_NBUF_REQ = (unsigned_t)(TCP_CEP_FLG_WBCS_NBUF_REQ);
const unsigned_t TOPPERS_cfg_TCP_CEP_FLG_WBCS_MASK = (unsigned_t)(TCP_CEP_FLG_WBCS_MASK);
const unsigned_t TOPPERS_cfg_TCP_CEP_FLG_WBCS_FREE = (unsigned_t)(TCP_CEP_FLG_WBCS_FREE);
const unsigned_t TOPPERS_cfg_TCP_CEP_FLG_WBCS_WOPEN_PEND = (unsigned_t)(TCP_CEP_FLG_WBCS_WOPEN_PEND);
const unsigned_t TOPPERS_cfg_TCP_CEP_FLG_WBCS_NBUF_PEND = (unsigned_t)(TCP_CEP_FLG_WBCS_NBUF_PEND);
const unsigned_t TOPPERS_cfg_TCP_CEP_FLG_WBCS_NBUF_RSVD = (unsigned_t)(TCP_CEP_FLG_WBCS_NBUF_RSVD);
const unsigned_t TOPPERS_cfg_TCP_CEP_FLG_WBCS_NBUF_READY = (unsigned_t)(TCP_CEP_FLG_WBCS_NBUF_READY);
const unsigned_t TOPPERS_cfg_TCP_CEP_FLG_WBCS_SEND_READY = (unsigned_t)(TCP_CEP_FLG_WBCS_SEND_READY);
const unsigned_t TOPPERS_cfg_TCP_CEP_FLG_WBCS_SENT = (unsigned_t)(TCP_CEP_FLG_WBCS_SENT);
const unsigned_t TOPPERS_cfg_TCP_CEP_FLG_WBCS_ACKED = (unsigned_t)(TCP_CEP_FLG_WBCS_ACKED);
const unsigned_t TOPPERS_cfg_TCP_CEP_EVT_ESTABLISHED = (unsigned_t)(TCP_CEP_EVT_ESTABLISHED);
const unsigned_t TOPPERS_cfg_TCP_CEP_EVT_CLOSED = (unsigned_t)(TCP_CEP_EVT_CLOSED);
const unsigned_t TOPPERS_cfg_TCP_CEP_EVT_SWBUF_READY = (unsigned_t)(TCP_CEP_EVT_SWBUF_READY);
const unsigned_t TOPPERS_cfg_TCP_CEP_EVT_RWBUF_READY = (unsigned_t)(TCP_CEP_EVT_RWBUF_READY);
const unsigned_t TOPPERS_cfg_TCP_CEP_EVT_ALL = (unsigned_t)(TCP_CEP_EVT_ALL);
#if defined(USE_EXTERNAL_ID)
const signed_t TOPPERS_cfg_USE_EXTERNAL_ID = (signed_t)(true);
#endif
#if defined(SIL_ENDIAN_BIG)
const signed_t TOPPERS_cfg_SIL_ENDIAN_BIG = (signed_t)(true);
#endif
#if defined(SIL_ENDIAN_LITTLE)
const signed_t TOPPERS_cfg_SIL_ENDIAN_LITTLE = (signed_t)(true);
#endif
const unsigned_t TOPPERS_cfg_TA_NULL = (unsigned_t)(TA_NULL);
const unsigned_t TOPPERS_cfg_TA_ACT = (unsigned_t)(TA_ACT);
const unsigned_t TOPPERS_cfg_TA_NOACTQUE = (unsigned_t)(TA_NOACTQUE);
const unsigned_t TOPPERS_cfg_TA_TPRI = (unsigned_t)(TA_TPRI);
const unsigned_t TOPPERS_cfg_TA_WMUL = (unsigned_t)(TA_WMUL);
const unsigned_t TOPPERS_cfg_TA_CLR = (unsigned_t)(TA_CLR);
const unsigned_t TOPPERS_cfg_TA_CEILING = (unsigned_t)(TA_CEILING);
const unsigned_t TOPPERS_cfg_TA_STA = (unsigned_t)(TA_STA);
const unsigned_t TOPPERS_cfg_TA_NONKERNEL = (unsigned_t)(TA_NONKERNEL);
const unsigned_t TOPPERS_cfg_TA_ENAINT = (unsigned_t)(TA_ENAINT);
const unsigned_t TOPPERS_cfg_TA_EDGE = (unsigned_t)(TA_EDGE);
const unsigned_t TOPPERS_cfg_TNFY_HANDLER = (unsigned_t)(TNFY_HANDLER);
const unsigned_t TOPPERS_cfg_TNFY_SETVAR = (unsigned_t)(TNFY_SETVAR);
const unsigned_t TOPPERS_cfg_TNFY_INCVAR = (unsigned_t)(TNFY_INCVAR);
const unsigned_t TOPPERS_cfg_TNFY_ACTTSK = (unsigned_t)(TNFY_ACTTSK);
const unsigned_t TOPPERS_cfg_TNFY_WUPTSK = (unsigned_t)(TNFY_WUPTSK);
const unsigned_t TOPPERS_cfg_TNFY_SIGSEM = (unsigned_t)(TNFY_SIGSEM);
const unsigned_t TOPPERS_cfg_TNFY_SETFLG = (unsigned_t)(TNFY_SETFLG);
const unsigned_t TOPPERS_cfg_TNFY_SNDDTQ = (unsigned_t)(TNFY_SNDDTQ);
const unsigned_t TOPPERS_cfg_TENFY_SETVAR = (unsigned_t)(TENFY_SETVAR);
const unsigned_t TOPPERS_cfg_TENFY_INCVAR = (unsigned_t)(TENFY_INCVAR);
const unsigned_t TOPPERS_cfg_TENFY_ACTTSK = (unsigned_t)(TENFY_ACTTSK);
const unsigned_t TOPPERS_cfg_TENFY_WUPTSK = (unsigned_t)(TENFY_WUPTSK);
const unsigned_t TOPPERS_cfg_TENFY_SIGSEM = (unsigned_t)(TENFY_SIGSEM);
const unsigned_t TOPPERS_cfg_TENFY_SETFLG = (unsigned_t)(TENFY_SETFLG);
const unsigned_t TOPPERS_cfg_TENFY_SNDDTQ = (unsigned_t)(TENFY_SNDDTQ);
const signed_t TOPPERS_cfg_TMIN_TPRI = (signed_t)(TMIN_TPRI);
const signed_t TOPPERS_cfg_TMAX_TPRI = (signed_t)(TMAX_TPRI);
const signed_t TOPPERS_cfg_TMIN_DPRI = (signed_t)(TMIN_DPRI);
const signed_t TOPPERS_cfg_TMAX_DPRI = (signed_t)(TMAX_DPRI);
const signed_t TOPPERS_cfg_TMIN_ISRPRI = (signed_t)(TMIN_ISRPRI);
const signed_t TOPPERS_cfg_TMAX_ISRPRI = (signed_t)(TMAX_ISRPRI);
const unsigned_t TOPPERS_cfg_TBIT_FLGPTN = (unsigned_t)(TBIT_FLGPTN);
const unsigned_t TOPPERS_cfg_TMAX_MAXSEM = (unsigned_t)(TMAX_MAXSEM);
const unsigned_t TOPPERS_cfg_TMAX_RELTIM = (unsigned_t)(TMAX_RELTIM);
const signed_t TOPPERS_cfg_TMIN_INTPRI = (signed_t)(TMIN_INTPRI);
const signed_t TOPPERS_cfg_TMAX_INTPRI = (signed_t)(TMAX_INTPRI);
const signed_t TOPPERS_cfg_TMIN_TSKID = (signed_t)(TMIN_TSKID);
const signed_t TOPPERS_cfg_TMIN_SEMID = (signed_t)(TMIN_SEMID);
const signed_t TOPPERS_cfg_TMIN_FLGID = (signed_t)(TMIN_FLGID);
const signed_t TOPPERS_cfg_TMIN_DTQID = (signed_t)(TMIN_DTQID);
const signed_t TOPPERS_cfg_TMIN_PDQID = (signed_t)(TMIN_PDQID);
const signed_t TOPPERS_cfg_TMIN_MTXID = (signed_t)(TMIN_MTXID);
const signed_t TOPPERS_cfg_TMIN_MPFID = (signed_t)(TMIN_MPFID);
const signed_t TOPPERS_cfg_TMIN_CYCID = (signed_t)(TMIN_CYCID);
const signed_t TOPPERS_cfg_TMIN_ALMID = (signed_t)(TMIN_ALMID);
#if defined(USE_TSKINICTXB)
const signed_t TOPPERS_cfg_USE_TSKINICTXB = (signed_t)(true);
#endif
#if defined(OMIT_INITIALIZE_INTERRUPT)
const signed_t TOPPERS_cfg_OMIT_INITIALIZE_INTERRUPT = (signed_t)(true);
#endif
#if defined(USE_INHINIB_TABLE)
const signed_t TOPPERS_cfg_USE_INHINIB_TABLE = (signed_t)(true);
#endif
#if defined(USE_INTINIB_TABLE)
const signed_t TOPPERS_cfg_USE_INTINIB_TABLE = (signed_t)(true);
#endif
#if defined(OMIT_INITIALIZE_EXCEPTION)
const signed_t TOPPERS_cfg_OMIT_INITIALIZE_EXCEPTION = (signed_t)(true);
#endif
#if defined(DEFAULT_ISTK)
const unsigned_t TOPPERS_cfg_DEFAULT_ISTK = (unsigned_t)(DEFAULT_ISTK);
#endif
#if defined(TARGET_TSKATR)
const unsigned_t TOPPERS_cfg_TARGET_TSKATR = (unsigned_t)(TARGET_TSKATR);
#else
const unsigned_t TOPPERS_cfg_TARGET_TSKATR = (unsigned_t)(0);
#endif
#if defined(TARGET_INTATR)
const unsigned_t TOPPERS_cfg_TARGET_INTATR = (unsigned_t)(TARGET_INTATR);
#else
const unsigned_t TOPPERS_cfg_TARGET_INTATR = (unsigned_t)(0);
#endif
#if defined(TARGET_INHATR)
const unsigned_t TOPPERS_cfg_TARGET_INHATR = (unsigned_t)(TARGET_INHATR);
#else
const unsigned_t TOPPERS_cfg_TARGET_INHATR = (unsigned_t)(0);
#endif
#if defined(TARGET_ISRATR)
const unsigned_t TOPPERS_cfg_TARGET_ISRATR = (unsigned_t)(TARGET_ISRATR);
#else
const unsigned_t TOPPERS_cfg_TARGET_ISRATR = (unsigned_t)(0);
#endif
#if defined(TARGET_EXCATR)
const unsigned_t TOPPERS_cfg_TARGET_EXCATR = (unsigned_t)(TARGET_EXCATR);
#else
const unsigned_t TOPPERS_cfg_TARGET_EXCATR = (unsigned_t)(0);
#endif
#if defined(TARGET_MIN_STKSZ)
const unsigned_t TOPPERS_cfg_TARGET_MIN_STKSZ = (unsigned_t)(TARGET_MIN_STKSZ);
#else
const unsigned_t TOPPERS_cfg_TARGET_MIN_STKSZ = (unsigned_t)(1);
#endif
#if defined(TARGET_MIN_ISTKSZ)
const unsigned_t TOPPERS_cfg_TARGET_MIN_ISTKSZ = (unsigned_t)(TARGET_MIN_ISTKSZ);
#else
const unsigned_t TOPPERS_cfg_TARGET_MIN_ISTKSZ = (unsigned_t)(1);
#endif
#if defined(CHECK_STKSZ_ALIGN)
const unsigned_t TOPPERS_cfg_CHECK_STKSZ_ALIGN = (unsigned_t)(CHECK_STKSZ_ALIGN);
#else
const unsigned_t TOPPERS_cfg_CHECK_STKSZ_ALIGN = (unsigned_t)(1);
#endif
#if defined(CHECK_INTPTR_ALIGN)
const unsigned_t TOPPERS_cfg_CHECK_INTPTR_ALIGN = (unsigned_t)(CHECK_INTPTR_ALIGN);
#else
const unsigned_t TOPPERS_cfg_CHECK_INTPTR_ALIGN = (unsigned_t)(1);
#endif
#if defined(CHECK_INTPTR_NONNULL)
const signed_t TOPPERS_cfg_CHECK_INTPTR_NONNULL = (signed_t)(true);
#endif
#if defined(CHECK_FUNC_ALIGN)
const unsigned_t TOPPERS_cfg_CHECK_FUNC_ALIGN = (unsigned_t)(CHECK_FUNC_ALIGN);
#else
const unsigned_t TOPPERS_cfg_CHECK_FUNC_ALIGN = (unsigned_t)(1);
#endif
#if defined(CHECK_FUNC_NONNULL)
const signed_t TOPPERS_cfg_CHECK_FUNC_NONNULL = (signed_t)(true);
#endif
#if defined(CHECK_STACK_ALIGN)
const unsigned_t TOPPERS_cfg_CHECK_STACK_ALIGN = (unsigned_t)(CHECK_STACK_ALIGN);
#else
const unsigned_t TOPPERS_cfg_CHECK_STACK_ALIGN = (unsigned_t)(1);
#endif
#if defined(CHECK_STACK_NONNULL)
const signed_t TOPPERS_cfg_CHECK_STACK_NONNULL = (signed_t)(true);
#endif
#if defined(CHECK_MPF_ALIGN)
const unsigned_t TOPPERS_cfg_CHECK_MPF_ALIGN = (unsigned_t)(CHECK_MPF_ALIGN);
#else
const unsigned_t TOPPERS_cfg_CHECK_MPF_ALIGN = (unsigned_t)(1);
#endif
#if defined(CHECK_MPF_NONNULL)
const signed_t TOPPERS_cfg_CHECK_MPF_NONNULL = (signed_t)(true);
#endif
#if defined(CHECK_MB_ALIGN)
const unsigned_t TOPPERS_cfg_CHECK_MB_ALIGN = (unsigned_t)(CHECK_MB_ALIGN);
#else
const unsigned_t TOPPERS_cfg_CHECK_MB_ALIGN = (unsigned_t)(1);
#endif
const unsigned_t TOPPERS_cfg_sizeof_void_ptr = (unsigned_t)(sizeof(void*));
const unsigned_t TOPPERS_cfg_sizeof_uint_t = (unsigned_t)(sizeof(uint_t));
const unsigned_t TOPPERS_cfg_sizeof_size_t = (unsigned_t)(sizeof(size_t));
const unsigned_t TOPPERS_cfg_sizeof_intptr_t = (unsigned_t)(sizeof(intptr_t));
const unsigned_t TOPPERS_cfg_sizeof_ID = (unsigned_t)(sizeof(ID));
const unsigned_t TOPPERS_cfg_sizeof_FP = (unsigned_t)(sizeof(FP));
const unsigned_t TOPPERS_cfg_sizeof_INTNO = (unsigned_t)(sizeof(INTNO));
const unsigned_t TOPPERS_cfg_sizeof_INHNO = (unsigned_t)(sizeof(INHNO));
const unsigned_t TOPPERS_cfg_sizeof_EXCNO = (unsigned_t)(sizeof(EXCNO));
const unsigned_t TOPPERS_cfg_sizeof_TASK = (unsigned_t)(sizeof(TASK));
const unsigned_t TOPPERS_cfg_sizeof_TMEHDR = (unsigned_t)(sizeof(TMEHDR));
const unsigned_t TOPPERS_cfg_sizeof_ISR = (unsigned_t)(sizeof(ISR));
const unsigned_t TOPPERS_cfg_sizeof_INTHDR = (unsigned_t)(sizeof(INTHDR));
const unsigned_t TOPPERS_cfg_sizeof_EXCHDR = (unsigned_t)(sizeof(EXCHDR));
const unsigned_t TOPPERS_cfg_sizeof_INIRTN = (unsigned_t)(sizeof(INIRTN));
const unsigned_t TOPPERS_cfg_sizeof_TERRTN = (unsigned_t)(sizeof(TERRTN));
const unsigned_t TOPPERS_cfg_sizeof_NFYHDR = (unsigned_t)(sizeof(NFYHDR));
const unsigned_t TOPPERS_cfg_sizeof_TINIB = (unsigned_t)(sizeof(TINIB));
const unsigned_t TOPPERS_cfg_offsetof_TINIB_tskatr = (unsigned_t)(offsetof(TINIB,tskatr));
const unsigned_t TOPPERS_cfg_offsetof_TINIB_exinf = (unsigned_t)(offsetof(TINIB,exinf));
const unsigned_t TOPPERS_cfg_offsetof_TINIB_task = (unsigned_t)(offsetof(TINIB,task));
const unsigned_t TOPPERS_cfg_offsetof_TINIB_ipriority = (unsigned_t)(offsetof(TINIB,ipriority));
#if !defined(USE_TSKINICTXB)
const unsigned_t TOPPERS_cfg_offsetof_TINIB_stksz = (unsigned_t)(offsetof(TINIB,stksz));
#endif
#if !defined(USE_TSKINICTXB)
const unsigned_t TOPPERS_cfg_offsetof_TINIB_stk = (unsigned_t)(offsetof(TINIB,stk));
#endif
const unsigned_t TOPPERS_cfg_sizeof_SEMINIB = (unsigned_t)(sizeof(SEMINIB));
const unsigned_t TOPPERS_cfg_offsetof_SEMINIB_sematr = (unsigned_t)(offsetof(SEMINIB,sematr));
const unsigned_t TOPPERS_cfg_offsetof_SEMINIB_isemcnt = (unsigned_t)(offsetof(SEMINIB,isemcnt));
const unsigned_t TOPPERS_cfg_offsetof_SEMINIB_maxsem = (unsigned_t)(offsetof(SEMINIB,maxsem));
const unsigned_t TOPPERS_cfg_sizeof_FLGPTN = (unsigned_t)(sizeof(FLGPTN));
const unsigned_t TOPPERS_cfg_sizeof_FLGINIB = (unsigned_t)(sizeof(FLGINIB));
const unsigned_t TOPPERS_cfg_offsetof_FLGINIB_flgatr = (unsigned_t)(offsetof(FLGINIB,flgatr));
const unsigned_t TOPPERS_cfg_offsetof_FLGINIB_iflgptn = (unsigned_t)(offsetof(FLGINIB,iflgptn));
const unsigned_t TOPPERS_cfg_sizeof_DTQINIB = (unsigned_t)(sizeof(DTQINIB));
const unsigned_t TOPPERS_cfg_offsetof_DTQINIB_dtqatr = (unsigned_t)(offsetof(DTQINIB,dtqatr));
const unsigned_t TOPPERS_cfg_offsetof_DTQINIB_dtqcnt = (unsigned_t)(offsetof(DTQINIB,dtqcnt));
const unsigned_t TOPPERS_cfg_offsetof_DTQINIB_p_dtqmb = (unsigned_t)(offsetof(DTQINIB,p_dtqmb));
const unsigned_t TOPPERS_cfg_sizeof_PDQINIB = (unsigned_t)(sizeof(PDQINIB));
const unsigned_t TOPPERS_cfg_offsetof_PDQINIB_pdqatr = (unsigned_t)(offsetof(PDQINIB,pdqatr));
const unsigned_t TOPPERS_cfg_offsetof_PDQINIB_pdqcnt = (unsigned_t)(offsetof(PDQINIB,pdqcnt));
const unsigned_t TOPPERS_cfg_offsetof_PDQINIB_maxdpri = (unsigned_t)(offsetof(PDQINIB,maxdpri));
const unsigned_t TOPPERS_cfg_offsetof_PDQINIB_p_pdqmb = (unsigned_t)(offsetof(PDQINIB,p_pdqmb));
const unsigned_t TOPPERS_cfg_sizeof_MTXINIB = (unsigned_t)(sizeof(MTXINIB));
const unsigned_t TOPPERS_cfg_offsetof_MTXINIB_mtxatr = (unsigned_t)(offsetof(MTXINIB,mtxatr));
const unsigned_t TOPPERS_cfg_offsetof_MTXINIB_ceilpri = (unsigned_t)(offsetof(MTXINIB,ceilpri));
const unsigned_t TOPPERS_cfg_sizeof_MPFINIB = (unsigned_t)(sizeof(MPFINIB));
const unsigned_t TOPPERS_cfg_offsetof_MPFINIB_mpfatr = (unsigned_t)(offsetof(MPFINIB,mpfatr));
const unsigned_t TOPPERS_cfg_offsetof_MPFINIB_blkcnt = (unsigned_t)(offsetof(MPFINIB,blkcnt));
const unsigned_t TOPPERS_cfg_offsetof_MPFINIB_blksz = (unsigned_t)(offsetof(MPFINIB,blksz));
const unsigned_t TOPPERS_cfg_offsetof_MPFINIB_mpf = (unsigned_t)(offsetof(MPFINIB,mpf));
const unsigned_t TOPPERS_cfg_offsetof_MPFINIB_p_mpfmb = (unsigned_t)(offsetof(MPFINIB,p_mpfmb));
const unsigned_t TOPPERS_cfg_sizeof_CYCINIB = (unsigned_t)(sizeof(CYCINIB));
const unsigned_t TOPPERS_cfg_offsetof_CYCINIB_cycatr = (unsigned_t)(offsetof(CYCINIB,cycatr));
const unsigned_t TOPPERS_cfg_offsetof_CYCINIB_exinf = (unsigned_t)(offsetof(CYCINIB,exinf));
const unsigned_t TOPPERS_cfg_offsetof_CYCINIB_nfyhdr = (unsigned_t)(offsetof(CYCINIB,nfyhdr));
const unsigned_t TOPPERS_cfg_offsetof_CYCINIB_cyctim = (unsigned_t)(offsetof(CYCINIB,cyctim));
const unsigned_t TOPPERS_cfg_offsetof_CYCINIB_cycphs = (unsigned_t)(offsetof(CYCINIB,cycphs));
const unsigned_t TOPPERS_cfg_sizeof_ALMINIB = (unsigned_t)(sizeof(ALMINIB));
const unsigned_t TOPPERS_cfg_offsetof_ALMINIB_almatr = (unsigned_t)(offsetof(ALMINIB,almatr));
const unsigned_t TOPPERS_cfg_offsetof_ALMINIB_exinf = (unsigned_t)(offsetof(ALMINIB,exinf));
const unsigned_t TOPPERS_cfg_offsetof_ALMINIB_nfyhdr = (unsigned_t)(offsetof(ALMINIB,nfyhdr));
const unsigned_t TOPPERS_cfg_sizeof_ISRINIB = (unsigned_t)(sizeof(ISRINIB));
const unsigned_t TOPPERS_cfg_offsetof_ISRINIB_isratr = (unsigned_t)(offsetof(ISRINIB,isratr));
const unsigned_t TOPPERS_cfg_offsetof_ISRINIB_exinf = (unsigned_t)(offsetof(ISRINIB,exinf));
const unsigned_t TOPPERS_cfg_offsetof_ISRINIB_p_isr_queue = (unsigned_t)(offsetof(ISRINIB,p_isr_queue));
const unsigned_t TOPPERS_cfg_offsetof_ISRINIB_isr = (unsigned_t)(offsetof(ISRINIB,isr));
const unsigned_t TOPPERS_cfg_offsetof_ISRINIB_isrpri = (unsigned_t)(offsetof(ISRINIB,isrpri));
#if !defined(OMIT_INITIALIZE_INTERRUPT)
const unsigned_t TOPPERS_cfg_sizeof_INHINIB = (unsigned_t)(sizeof(INHINIB));
#endif
#if !defined(OMIT_INITIALIZE_INTERRUPT)
const unsigned_t TOPPERS_cfg_offset_INHINIB_inhno = (unsigned_t)(offsetof(INHINIB,inhno));
#endif
#if !defined(OMIT_INITIALIZE_INTERRUPT)
const unsigned_t TOPPERS_cfg_offset_INHINIB_inhatr = (unsigned_t)(offsetof(INHINIB,inhatr));
#endif
#if !defined(OMIT_INITIALIZE_INTERRUPT)
const unsigned_t TOPPERS_cfg_offset_INHINIB_int_entry = (unsigned_t)(offsetof(INHINIB,int_entry));
#endif
#if !defined(OMIT_INITIALIZE_INTERRUPT)
const unsigned_t TOPPERS_cfg_sizeof_INTINIB = (unsigned_t)(sizeof(INTINIB));
#endif
#if !defined(OMIT_INITIALIZE_INTERRUPT)
const unsigned_t TOPPERS_cfg_offset_INTINIB_intno = (unsigned_t)(offsetof(INTINIB,intno));
#endif
#if !defined(OMIT_INITIALIZE_INTERRUPT)
const unsigned_t TOPPERS_cfg_offset_INTINIB_intatr = (unsigned_t)(offsetof(INTINIB,intatr));
#endif
#if !defined(OMIT_INITIALIZE_INTERRUPT)
const unsigned_t TOPPERS_cfg_offset_INTINIB_intpri = (unsigned_t)(offsetof(INTINIB,intpri));
#endif
#if !defined(OMIT_INITIALIZE_EXCEPTION)
const unsigned_t TOPPERS_cfg_sizeof_EXCINIB = (unsigned_t)(sizeof(EXCINIB));
#endif
#if !defined(OMIT_INITIALIZE_EXCEPTION)
const unsigned_t TOPPERS_cfg_offset_EXCINIB_excno = (unsigned_t)(offsetof(EXCINIB,excno));
#endif
#if !defined(OMIT_INITIALIZE_EXCEPTION)
const unsigned_t TOPPERS_cfg_offset_EXCINIB_excatr = (unsigned_t)(offsetof(EXCINIB,excatr));
#endif
#if !defined(OMIT_INITIALIZE_EXCEPTION)
const unsigned_t TOPPERS_cfg_offset_EXCINIB_exc_entry = (unsigned_t)(offsetof(EXCINIB,exc_entry));
#endif
#if defined(TARGET_RZA1H)
const signed_t TOPPERS_cfg_TARGET_RZA1H = (signed_t)(true);
#endif
#if defined(TARGET_RZA1L)
const signed_t TOPPERS_cfg_TARGET_RZA1L = (signed_t)(true);
#endif
const unsigned_t TOPPERS_cfg_TA_NEGEDGE = (unsigned_t)(TA_NEGEDGE);
const unsigned_t TOPPERS_cfg_TA_POSEDGE = (unsigned_t)(TA_POSEDGE);
const unsigned_t TOPPERS_cfg_TA_BOTHEDGE = (unsigned_t)(TA_BOTHEDGE);
const unsigned_t TOPPERS_cfg_INTNO_IRQ0 = (unsigned_t)(INTNO_IRQ0);
const unsigned_t TOPPERS_cfg_INTNO_IRQ7 = (unsigned_t)(INTNO_IRQ7);
const unsigned_t TOPPERS_cfg_TARGET_ARCH_ARM = (unsigned_t)(__TARGET_ARCH_ARM);
#if defined(USE_INTCFG_TABLE)
const signed_t TOPPERS_cfg_USE_INTCFG_TABLE = (signed_t)(true);
#endif
const unsigned_t TOPPERS_cfg_sizeof_TCB = (unsigned_t)(sizeof(TCB));
const unsigned_t TOPPERS_cfg_offsetof_TCB_p_tinib = (unsigned_t)(offsetof(TCB,p_tinib));
const unsigned_t TOPPERS_cfg_offsetof_TCB_sp = (unsigned_t)(offsetof(TCB,tskctxb.sp));
const unsigned_t TOPPERS_cfg_offsetof_TCB_pc = (unsigned_t)(offsetof(TCB,tskctxb.pc));
const unsigned_t TOPPERS_cfg_offsetof_T_EXCINF_cpsr = (unsigned_t)(offsetof(T_EXCINF,cpsr));


#line 10 "../arch/arm_gcc/rza1/chip_timer.cfg"
const unsigned_t TOPPERS_cfg_static_api_1 = 1;
#line 10 "../arch/arm_gcc/rza1/chip_timer.cfg"
const unsigned_t TOPPERS_cfg_valueof_iniatr_1 = (unsigned_t)(TA_NULL);

#line 11 "../arch/arm_gcc/rza1/chip_timer.cfg"
const unsigned_t TOPPERS_cfg_static_api_2 = 2;
#line 11 "../arch/arm_gcc/rza1/chip_timer.cfg"
const unsigned_t TOPPERS_cfg_valueof_teratr_2 = (unsigned_t)(TA_NULL);

#line 12 "../arch/arm_gcc/rza1/chip_timer.cfg"
const unsigned_t TOPPERS_cfg_static_api_3 = 3;
#line 12 "../arch/arm_gcc/rza1/chip_timer.cfg"
const unsigned_t TOPPERS_cfg_valueof_intno_3 = (unsigned_t)(INTNO_TIMER);
#line 12 "../arch/arm_gcc/rza1/chip_timer.cfg"
const unsigned_t TOPPERS_cfg_valueof_intatr_3 = (unsigned_t)(TA_ENAINT|INTATR_TIMER);
#line 12 "../arch/arm_gcc/rza1/chip_timer.cfg"
const signed_t TOPPERS_cfg_valueof_intpri_3 = (signed_t)(INTPRI_TIMER);

#line 13 "../arch/arm_gcc/rza1/chip_timer.cfg"
const unsigned_t TOPPERS_cfg_static_api_4 = 4;
#line 13 "../arch/arm_gcc/rza1/chip_timer.cfg"
const unsigned_t TOPPERS_cfg_valueof_inhno_4 = (unsigned_t)(INHNO_TIMER);
#line 13 "../arch/arm_gcc/rza1/chip_timer.cfg"
const unsigned_t TOPPERS_cfg_valueof_inhatr_4 = (unsigned_t)(TA_NULL);

#ifdef TOPPERS_SUPPORT_OVRHDR

#line 19 "../arch/arm_gcc/rza1/chip_timer.cfg"
const unsigned_t TOPPERS_cfg_static_api_5 = 5;
#line 19 "../arch/arm_gcc/rza1/chip_timer.cfg"
const unsigned_t TOPPERS_cfg_valueof_iniatr_5 = (unsigned_t)(TA_NULL);

#line 20 "../arch/arm_gcc/rza1/chip_timer.cfg"
const unsigned_t TOPPERS_cfg_static_api_6 = 6;
#line 20 "../arch/arm_gcc/rza1/chip_timer.cfg"
const unsigned_t TOPPERS_cfg_valueof_teratr_6 = (unsigned_t)(TA_NULL);

#line 21 "../arch/arm_gcc/rza1/chip_timer.cfg"
const unsigned_t TOPPERS_cfg_static_api_7 = 7;
#line 21 "../arch/arm_gcc/rza1/chip_timer.cfg"
const unsigned_t TOPPERS_cfg_valueof_intno_7 = (unsigned_t)(INTNO_OVRTIMER);
#line 21 "../arch/arm_gcc/rza1/chip_timer.cfg"
const unsigned_t TOPPERS_cfg_valueof_intatr_7 = (unsigned_t)(TA_ENAINT|INTATR_OVRTIMER);
#line 21 "../arch/arm_gcc/rza1/chip_timer.cfg"
const signed_t TOPPERS_cfg_valueof_intpri_7 = (signed_t)(INTPRI_OVRTIMER);

#line 22 "../arch/arm_gcc/rza1/chip_timer.cfg"
const unsigned_t TOPPERS_cfg_static_api_8 = 8;
#line 22 "../arch/arm_gcc/rza1/chip_timer.cfg"
const unsigned_t TOPPERS_cfg_valueof_inhno_8 = (unsigned_t)(INHNO_OVRTIMER);
#line 22 "../arch/arm_gcc/rza1/chip_timer.cfg"
const unsigned_t TOPPERS_cfg_valueof_inhatr_8 = (unsigned_t)(TA_NULL);

#endif

#line 2 "./gen/tecsgen.cfg"
const unsigned_t TOPPERS_cfg_static_api_9 = 9;
#define TSKID_tTask_LogTask_Task	(<>)
#line 2 "./gen/tecsgen.cfg"
const unsigned_t TOPPERS_cfg_valueof_tskatr_9 = (unsigned_t)(TA_ACT);
#line 2 "./gen/tecsgen.cfg"
const signed_t TOPPERS_cfg_valueof_itskpri_9 = (signed_t)(3);
#line 2 "./gen/tecsgen.cfg"
const unsigned_t TOPPERS_cfg_valueof_stksz_9 = (unsigned_t)(4096);

#line 3 "./gen/tecsgen.cfg"
const unsigned_t TOPPERS_cfg_static_api_10 = 10;
#define SEMID_tSemaphore_SerialPort1_ReceiveSemaphore	(<>)
#line 3 "./gen/tecsgen.cfg"
const unsigned_t TOPPERS_cfg_valueof_sematr_10 = (unsigned_t)(TA_NULL);
#line 3 "./gen/tecsgen.cfg"
const unsigned_t TOPPERS_cfg_valueof_isemcnt_10 = (unsigned_t)(0);
#line 3 "./gen/tecsgen.cfg"
const unsigned_t TOPPERS_cfg_valueof_maxsem_10 = (unsigned_t)(1);

#line 4 "./gen/tecsgen.cfg"
const unsigned_t TOPPERS_cfg_static_api_11 = 11;
#define SEMID_tSemaphore_SerialPort1_SendSemaphore	(<>)
#line 4 "./gen/tecsgen.cfg"
const unsigned_t TOPPERS_cfg_valueof_sematr_11 = (unsigned_t)(TA_NULL);
#line 4 "./gen/tecsgen.cfg"
const unsigned_t TOPPERS_cfg_valueof_isemcnt_11 = (unsigned_t)(1);
#line 4 "./gen/tecsgen.cfg"
const unsigned_t TOPPERS_cfg_valueof_maxsem_11 = (unsigned_t)(1);

#line 5 "./gen/tecsgen.cfg"
const unsigned_t TOPPERS_cfg_static_api_12 = 12;
#line 5 "./gen/tecsgen.cfg"
const unsigned_t TOPPERS_cfg_valueof_intno_12 = (unsigned_t)(INTNO_SCIF2_RXI);
#line 5 "./gen/tecsgen.cfg"
const unsigned_t TOPPERS_cfg_valueof_intatr_12 = (unsigned_t)(TA_NULL);
#line 5 "./gen/tecsgen.cfg"
const signed_t TOPPERS_cfg_valueof_intpri_12 = (signed_t)(-4);

#line 6 "./gen/tecsgen.cfg"
const unsigned_t TOPPERS_cfg_static_api_13 = 13;
#line 6 "./gen/tecsgen.cfg"
const unsigned_t TOPPERS_cfg_valueof_intno_13 = (unsigned_t)(INTNO_SCIF2_TXI);
#line 6 "./gen/tecsgen.cfg"
const unsigned_t TOPPERS_cfg_valueof_intatr_13 = (unsigned_t)(TA_NULL);
#line 6 "./gen/tecsgen.cfg"
const signed_t TOPPERS_cfg_valueof_intpri_13 = (signed_t)(-4);

#line 8 "./gen/tecsgen.cfg"
const unsigned_t TOPPERS_cfg_static_api_14 = 14;
#define ISRID_tISR_SIOPortTarget1_RxISRInstance	(<>)
#line 8 "./gen/tecsgen.cfg"
const unsigned_t TOPPERS_cfg_valueof_isratr_14 = (unsigned_t)(TA_NULL);
#line 8 "./gen/tecsgen.cfg"
const unsigned_t TOPPERS_cfg_valueof_intno_14 = (unsigned_t)(INTNO_SCIF2_RXI);
#line 8 "./gen/tecsgen.cfg"
const signed_t TOPPERS_cfg_valueof_isrpri_14 = (signed_t)(1);

#line 9 "./gen/tecsgen.cfg"
const unsigned_t TOPPERS_cfg_static_api_15 = 15;
#define ISRID_tISR_SIOPortTarget1_TxISRInstance	(<>)
#line 9 "./gen/tecsgen.cfg"
const unsigned_t TOPPERS_cfg_valueof_isratr_15 = (unsigned_t)(TA_NULL);
#line 9 "./gen/tecsgen.cfg"
const unsigned_t TOPPERS_cfg_valueof_intno_15 = (unsigned_t)(INTNO_SCIF2_TXI);
#line 9 "./gen/tecsgen.cfg"
const signed_t TOPPERS_cfg_valueof_isrpri_15 = (signed_t)(1);

#line 11 "./gen/tecsgen.cfg"
const unsigned_t TOPPERS_cfg_static_api_16 = 16;
#line 11 "./gen/tecsgen.cfg"
const unsigned_t TOPPERS_cfg_valueof_iniatr_16 = (unsigned_t)(TA_NULL);

#line 13 "./gen/tecsgen.cfg"
const unsigned_t TOPPERS_cfg_static_api_17 = 17;
#line 13 "./gen/tecsgen.cfg"
const unsigned_t TOPPERS_cfg_valueof_teratr_17 = (unsigned_t)(TA_NULL);

#line 9 "../sample/sample1.cfg"
const unsigned_t TOPPERS_cfg_static_api_18 = 18;
#define TASK1	(<>)
#line 9 "../sample/sample1.cfg"
const unsigned_t TOPPERS_cfg_valueof_tskatr_18 = (unsigned_t)(TA_NULL);
#line 9 "../sample/sample1.cfg"
const signed_t TOPPERS_cfg_valueof_itskpri_18 = (signed_t)(MID_PRIORITY);
#line 9 "../sample/sample1.cfg"
const unsigned_t TOPPERS_cfg_valueof_stksz_18 = (unsigned_t)(STACK_SIZE);

#line 10 "../sample/sample1.cfg"
const unsigned_t TOPPERS_cfg_static_api_19 = 19;
#define TASK2	(<>)
#line 10 "../sample/sample1.cfg"
const unsigned_t TOPPERS_cfg_valueof_tskatr_19 = (unsigned_t)(TA_NULL);
#line 10 "../sample/sample1.cfg"
const signed_t TOPPERS_cfg_valueof_itskpri_19 = (signed_t)(MID_PRIORITY);
#line 10 "../sample/sample1.cfg"
const unsigned_t TOPPERS_cfg_valueof_stksz_19 = (unsigned_t)(STACK_SIZE);

#line 11 "../sample/sample1.cfg"
const unsigned_t TOPPERS_cfg_static_api_20 = 20;
#define MAIN_TASK	(<>)
#line 11 "../sample/sample1.cfg"
const unsigned_t TOPPERS_cfg_valueof_tskatr_20 = (unsigned_t)(TA_ACT);
#line 11 "../sample/sample1.cfg"
const signed_t TOPPERS_cfg_valueof_itskpri_20 = (signed_t)(MAIN_PRIORITY);
#line 11 "../sample/sample1.cfg"
const unsigned_t TOPPERS_cfg_valueof_stksz_20 = (unsigned_t)(STACK_SIZE);

#line 12 "../sample/sample1.cfg"
const unsigned_t TOPPERS_cfg_static_api_21 = 21;
#define EXC_TASK	(<>)
#line 12 "../sample/sample1.cfg"
const unsigned_t TOPPERS_cfg_valueof_tskatr_21 = (unsigned_t)(TA_NULL);
#line 12 "../sample/sample1.cfg"
const signed_t TOPPERS_cfg_valueof_itskpri_21 = (signed_t)(EXC_PRIORITY);
#line 12 "../sample/sample1.cfg"
const unsigned_t TOPPERS_cfg_valueof_stksz_21 = (unsigned_t)(STACK_SIZE);

#line 13 "../sample/sample1.cfg"
const unsigned_t TOPPERS_cfg_static_api_22 = 22;
#line 13 "../sample/sample1.cfg"
const unsigned_t TOPPERS_cfg_valueof_notsk_22 = (unsigned_t)(3);

#line 14 "../sample/sample1.cfg"
const unsigned_t TOPPERS_cfg_static_api_23 = 23;
#define CYCHDR1	(<>)
#line 14 "../sample/sample1.cfg"
const unsigned_t TOPPERS_cfg_valueof_cycatr_23 = (unsigned_t)(TA_NULL);
#line 14 "../sample/sample1.cfg"
const unsigned_t TOPPERS_cfg_valueof_nfymode_23 = (unsigned_t)(TNFY_HANDLER);
#line 14 "../sample/sample1.cfg"
const unsigned_t TOPPERS_cfg_valueof_cyctim_23 = (unsigned_t)(2000000);
#line 14 "../sample/sample1.cfg"
const unsigned_t TOPPERS_cfg_valueof_cycphs_23 = (unsigned_t)(0);

#line 15 "../sample/sample1.cfg"
const unsigned_t TOPPERS_cfg_static_api_24 = 24;
#line 15 "../sample/sample1.cfg"
const unsigned_t TOPPERS_cfg_valueof_noalm_24 = (unsigned_t)(1);

#ifdef INTNO1

#line 17 "../sample/sample1.cfg"
const unsigned_t TOPPERS_cfg_static_api_25 = 25;
#line 17 "../sample/sample1.cfg"
const unsigned_t TOPPERS_cfg_valueof_intno_25 = (unsigned_t)(INTNO1);
#line 17 "../sample/sample1.cfg"
const unsigned_t TOPPERS_cfg_valueof_intatr_25 = (unsigned_t)(INTNO1_INTATR);
#line 17 "../sample/sample1.cfg"
const signed_t TOPPERS_cfg_valueof_intpri_25 = (signed_t)(INTNO1_INTPRI);

#line 18 "../sample/sample1.cfg"
const unsigned_t TOPPERS_cfg_static_api_26 = 26;
#define INTNO1_ISR	(<>)
#line 18 "../sample/sample1.cfg"
const unsigned_t TOPPERS_cfg_valueof_isratr_26 = (unsigned_t)(TA_NULL);
#line 18 "../sample/sample1.cfg"
const unsigned_t TOPPERS_cfg_valueof_intno_26 = (unsigned_t)(INTNO1);
#line 18 "../sample/sample1.cfg"
const signed_t TOPPERS_cfg_valueof_isrpri_26 = (signed_t)(1);

#endif

#ifdef CPUEXC1

#line 21 "../sample/sample1.cfg"
const unsigned_t TOPPERS_cfg_static_api_27 = 27;
#line 21 "../sample/sample1.cfg"
const unsigned_t TOPPERS_cfg_valueof_excno_27 = (unsigned_t)(CPUEXC1);
#line 21 "../sample/sample1.cfg"
const unsigned_t TOPPERS_cfg_valueof_excatr_27 = (unsigned_t)(TA_NULL);

#endif

#line 23 "../sample/sample1.cfg"
const unsigned_t TOPPERS_cfg_static_api_28 = 28;
#line 23 "../sample/sample1.cfg"
const unsigned_t TOPPERS_cfg_valueof_kmmsz_28 = (unsigned_t)(KMM_SIZE);

#ifdef SUPPORT_ETHER

#line 50 "../tinet/netdev/if_mbed/nic_asp.cfg"
const unsigned_t TOPPERS_cfg_static_api_29 = 29;
#define IF_MBED_PHY_TASK	(<>)
#line 50 "../tinet/netdev/if_mbed/nic_asp.cfg"
const unsigned_t TOPPERS_cfg_valueof_tskatr_29 = (unsigned_t)(TA_ACT);
#line 50 "../tinet/netdev/if_mbed/nic_asp.cfg"
const signed_t TOPPERS_cfg_valueof_itskpri_29 = (signed_t)(IF_MBED_PHY_PRIORITY);
#line 50 "../tinet/netdev/if_mbed/nic_asp.cfg"
const unsigned_t TOPPERS_cfg_valueof_stksz_29 = (unsigned_t)(IF_MBED_PHY_STACK_SIZE);

#line 54 "../tinet/netdev/if_mbed/nic_asp.cfg"
const unsigned_t TOPPERS_cfg_static_api_30 = 30;
#line 54 "../tinet/netdev/if_mbed/nic_asp.cfg"
const unsigned_t TOPPERS_cfg_valueof_inhno_30 = (unsigned_t)(INHNO_IF_MBED);
#line 54 "../tinet/netdev/if_mbed/nic_asp.cfg"
const unsigned_t TOPPERS_cfg_valueof_inhatr_30 = (unsigned_t)(TA_NULL);

#line 55 "../tinet/netdev/if_mbed/nic_asp.cfg"
const unsigned_t TOPPERS_cfg_static_api_31 = 31;
#line 55 "../tinet/netdev/if_mbed/nic_asp.cfg"
const unsigned_t TOPPERS_cfg_valueof_intno_31 = (unsigned_t)(INTNO_IF_MBED);
#line 55 "../tinet/netdev/if_mbed/nic_asp.cfg"
const unsigned_t TOPPERS_cfg_valueof_intatr_31 = (unsigned_t)(INTATR_IF_MBED);
#line 55 "../tinet/netdev/if_mbed/nic_asp.cfg"
const signed_t TOPPERS_cfg_valueof_intpri_31 = (signed_t)(INTPRI_IF_MBED);

#line 59 "../tinet/netdev/if_mbed/nic_asp.cfg"
const unsigned_t TOPPERS_cfg_static_api_32 = 32;
#define SEM_IF_MBED_SBUF_READY	(<>)
#line 59 "../tinet/netdev/if_mbed/nic_asp.cfg"
const unsigned_t TOPPERS_cfg_valueof_sematr_32 = (unsigned_t)(TA_TPRI);
#line 59 "../tinet/netdev/if_mbed/nic_asp.cfg"
const unsigned_t TOPPERS_cfg_valueof_isemcnt_32 = (unsigned_t)(NUM_IF_MBED_TXBUF);
#line 59 "../tinet/netdev/if_mbed/nic_asp.cfg"
const unsigned_t TOPPERS_cfg_valueof_maxsem_32 = (unsigned_t)(NUM_IF_MBED_TXBUF);

#line 60 "../tinet/netdev/if_mbed/nic_asp.cfg"
const unsigned_t TOPPERS_cfg_static_api_33 = 33;
#define SEM_IF_MBED_RBUF_READY	(<>)
#line 60 "../tinet/netdev/if_mbed/nic_asp.cfg"
const unsigned_t TOPPERS_cfg_valueof_sematr_33 = (unsigned_t)(TA_TPRI);
#line 60 "../tinet/netdev/if_mbed/nic_asp.cfg"
const unsigned_t TOPPERS_cfg_valueof_isemcnt_33 = (unsigned_t)(0);
#line 60 "../tinet/netdev/if_mbed/nic_asp.cfg"
const unsigned_t TOPPERS_cfg_valueof_maxsem_33 = (unsigned_t)(NUM_IF_MBED_RXBUF);

#endif

#line 42 "../tinet/net/net.cfg"
const unsigned_t TOPPERS_cfg_static_api_34 = 34;
#define NET_TIMER_TASK	(<>)
#line 42 "../tinet/net/net.cfg"
const unsigned_t TOPPERS_cfg_valueof_tskatr_34 = (unsigned_t)(TA_NULL);
#line 42 "../tinet/net/net.cfg"
const signed_t TOPPERS_cfg_valueof_itskpri_34 = (signed_t)(NET_TIMER_PRIORITY);
#line 42 "../tinet/net/net.cfg"
const unsigned_t TOPPERS_cfg_valueof_stksz_34 = (unsigned_t)(NET_TIMER_STACK_SIZE);

#line 51 "../tinet/net/net.cfg"
const unsigned_t TOPPERS_cfg_static_api_35 = 35;
#define NET_TIMER_HANDLER	(<>)
#line 51 "../tinet/net/net.cfg"
const unsigned_t TOPPERS_cfg_valueof_cycatr_35 = (unsigned_t)(TA_STA);
#line 51 "../tinet/net/net.cfg"
const unsigned_t TOPPERS_cfg_valueof_nfymode_35 = (unsigned_t)(TNFY_HANDLER);
#line 51 "../tinet/net/net.cfg"
const unsigned_t TOPPERS_cfg_valueof_cyctim_35 = (unsigned_t)(NET_TIMER_CYCLE);
#line 51 "../tinet/net/net.cfg"
const unsigned_t TOPPERS_cfg_valueof_cycphs_35 = (unsigned_t)(1);

#line 60 "../tinet/net/net.cfg"
const unsigned_t TOPPERS_cfg_static_api_36 = 36;
#define SEM_CALL_OUT_LOCK	(<>)
#line 60 "../tinet/net/net.cfg"
const unsigned_t TOPPERS_cfg_valueof_sematr_36 = (unsigned_t)(TA_TPRI);
#line 60 "../tinet/net/net.cfg"
const unsigned_t TOPPERS_cfg_valueof_isemcnt_36 = (unsigned_t)(1);
#line 60 "../tinet/net/net.cfg"
const unsigned_t TOPPERS_cfg_valueof_maxsem_36 = (unsigned_t)(1);

#line 61 "../tinet/net/net.cfg"
const unsigned_t TOPPERS_cfg_static_api_37 = 37;
#define SEM_CALL_OUT_TIMEOUT	(<>)
#line 61 "../tinet/net/net.cfg"
const unsigned_t TOPPERS_cfg_valueof_sematr_37 = (unsigned_t)(TA_TPRI);
#line 61 "../tinet/net/net.cfg"
const unsigned_t TOPPERS_cfg_valueof_isemcnt_37 = (unsigned_t)(0);
#line 61 "../tinet/net/net.cfg"
const unsigned_t TOPPERS_cfg_valueof_maxsem_37 = (unsigned_t)(NUM_NET_CALLOUT);

#line 65 "../tinet/net/net.cfg"
const unsigned_t TOPPERS_cfg_static_api_38 = 38;
#define SEM_IP2STR_BUFF_LOCK	(<>)
#line 65 "../tinet/net/net.cfg"
const unsigned_t TOPPERS_cfg_valueof_sematr_38 = (unsigned_t)(TA_TPRI);
#line 65 "../tinet/net/net.cfg"
const unsigned_t TOPPERS_cfg_valueof_isemcnt_38 = (unsigned_t)(1);
#line 65 "../tinet/net/net.cfg"
const unsigned_t TOPPERS_cfg_valueof_maxsem_38 = (unsigned_t)(1);

#if defined(NUM_MPF_NET_BUF_CSEG) && NUM_MPF_NET_BUF_CSEG > 0

#line 49 "../tinet/net/net_asp.cfg"
const unsigned_t TOPPERS_cfg_static_api_39 = 39;
#define MPF_NET_BUF_CSEG	(<>)
#line 49 "../tinet/net/net_asp.cfg"
const unsigned_t TOPPERS_cfg_valueof_mpfatr_39 = (unsigned_t)(TA_TFIFO);
#line 49 "../tinet/net/net_asp.cfg"
const unsigned_t TOPPERS_cfg_valueof_blkcnt_39 = (unsigned_t)(NUM_MPF_NET_BUF_CSEG);
#line 49 "../tinet/net/net_asp.cfg"
const unsigned_t TOPPERS_cfg_valueof_blksz_39 = (unsigned_t)(sizeof(T_NET_BUF_CSEG));

#endif

#if defined(NUM_MPF_NET_BUF_64) && NUM_MPF_NET_BUF_64 > 0

#line 57 "../tinet/net/net_asp.cfg"
const unsigned_t TOPPERS_cfg_static_api_40 = 40;
#define MPF_NET_BUF_64	(<>)
#line 57 "../tinet/net/net_asp.cfg"
const unsigned_t TOPPERS_cfg_valueof_mpfatr_40 = (unsigned_t)(TA_TFIFO);
#line 57 "../tinet/net/net_asp.cfg"
const unsigned_t TOPPERS_cfg_valueof_blkcnt_40 = (unsigned_t)(NUM_MPF_NET_BUF_64);
#line 57 "../tinet/net/net_asp.cfg"
const unsigned_t TOPPERS_cfg_valueof_blksz_40 = (unsigned_t)(sizeof(T_NET_BUF_64));

#endif

#if defined(NUM_MPF_NET_BUF_128) && NUM_MPF_NET_BUF_128 > 0

#line 64 "../tinet/net/net_asp.cfg"
const unsigned_t TOPPERS_cfg_static_api_41 = 41;
#define MPF_NET_BUF_128	(<>)
#line 64 "../tinet/net/net_asp.cfg"
const unsigned_t TOPPERS_cfg_valueof_mpfatr_41 = (unsigned_t)(TA_TFIFO);
#line 64 "../tinet/net/net_asp.cfg"
const unsigned_t TOPPERS_cfg_valueof_blkcnt_41 = (unsigned_t)(NUM_MPF_NET_BUF_128);
#line 64 "../tinet/net/net_asp.cfg"
const unsigned_t TOPPERS_cfg_valueof_blksz_41 = (unsigned_t)(sizeof(T_NET_BUF_128));

#endif

#if defined(NUM_MPF_NET_BUF_256) && NUM_MPF_NET_BUF_256 > 0

#line 72 "../tinet/net/net_asp.cfg"
const unsigned_t TOPPERS_cfg_static_api_42 = 42;
#define MPF_NET_BUF_256	(<>)
#line 72 "../tinet/net/net_asp.cfg"
const unsigned_t TOPPERS_cfg_valueof_mpfatr_42 = (unsigned_t)(TA_TFIFO);
#line 72 "../tinet/net/net_asp.cfg"
const unsigned_t TOPPERS_cfg_valueof_blkcnt_42 = (unsigned_t)(NUM_MPF_NET_BUF_256);
#line 72 "../tinet/net/net_asp.cfg"
const unsigned_t TOPPERS_cfg_valueof_blksz_42 = (unsigned_t)(sizeof(T_NET_BUF_256));

#endif

#if defined(NUM_MPF_NET_BUF_512) && NUM_MPF_NET_BUF_512 > 0

#line 80 "../tinet/net/net_asp.cfg"
const unsigned_t TOPPERS_cfg_static_api_43 = 43;
#define MPF_NET_BUF_512	(<>)
#line 80 "../tinet/net/net_asp.cfg"
const unsigned_t TOPPERS_cfg_valueof_mpfatr_43 = (unsigned_t)(TA_TFIFO);
#line 80 "../tinet/net/net_asp.cfg"
const unsigned_t TOPPERS_cfg_valueof_blkcnt_43 = (unsigned_t)(NUM_MPF_NET_BUF_512);
#line 80 "../tinet/net/net_asp.cfg"
const unsigned_t TOPPERS_cfg_valueof_blksz_43 = (unsigned_t)(sizeof(T_NET_BUF_512));

#endif

#if defined(NUM_MPF_NET_BUF_IP_MSS) && NUM_MPF_NET_BUF_IP_MSS > 0

#line 88 "../tinet/net/net_asp.cfg"
const unsigned_t TOPPERS_cfg_static_api_44 = 44;
#define MPF_NET_BUF_IP_MSS	(<>)
#line 88 "../tinet/net/net_asp.cfg"
const unsigned_t TOPPERS_cfg_valueof_mpfatr_44 = (unsigned_t)(TA_TFIFO);
#line 88 "../tinet/net/net_asp.cfg"
const unsigned_t TOPPERS_cfg_valueof_blkcnt_44 = (unsigned_t)(NUM_MPF_NET_BUF_IP_MSS);
#line 88 "../tinet/net/net_asp.cfg"
const unsigned_t TOPPERS_cfg_valueof_blksz_44 = (unsigned_t)(sizeof(T_NET_BUF_IP_MSS));

#endif

#if defined(NUM_MPF_NET_BUF_1024) && NUM_MPF_NET_BUF_1024 > 0

#line 96 "../tinet/net/net_asp.cfg"
const unsigned_t TOPPERS_cfg_static_api_45 = 45;
#define MPF_NET_BUF_1024	(<>)
#line 96 "../tinet/net/net_asp.cfg"
const unsigned_t TOPPERS_cfg_valueof_mpfatr_45 = (unsigned_t)(TA_TFIFO);
#line 96 "../tinet/net/net_asp.cfg"
const unsigned_t TOPPERS_cfg_valueof_blkcnt_45 = (unsigned_t)(NUM_MPF_NET_BUF_1024);
#line 96 "../tinet/net/net_asp.cfg"
const unsigned_t TOPPERS_cfg_valueof_blksz_45 = (unsigned_t)(sizeof(T_NET_BUF_1024));

#endif

#if defined(NUM_MPF_NET_BUF_IPV6_MMTU) && NUM_MPF_NET_BUF_IPV6_MMTU > 0

#line 104 "../tinet/net/net_asp.cfg"
const unsigned_t TOPPERS_cfg_static_api_46 = 46;
#define MPF_NET_BUF_IPV6_MMTU	(<>)
#line 104 "../tinet/net/net_asp.cfg"
const unsigned_t TOPPERS_cfg_valueof_mpfatr_46 = (unsigned_t)(TA_TFIFO);
#line 104 "../tinet/net/net_asp.cfg"
const unsigned_t TOPPERS_cfg_valueof_blkcnt_46 = (unsigned_t)(NUM_MPF_NET_BUF_IPV6_MMTU);
#line 104 "../tinet/net/net_asp.cfg"
const unsigned_t TOPPERS_cfg_valueof_blksz_46 = (unsigned_t)(sizeof(T_NET_BUF_IPV6_MMTU));

#endif

#if defined(NUM_MPF_NET_BUF_IF_PDU) && NUM_MPF_NET_BUF_IF_PDU > 0

#line 112 "../tinet/net/net_asp.cfg"
const unsigned_t TOPPERS_cfg_static_api_47 = 47;
#define MPF_NET_BUF_IF_PDU	(<>)
#line 112 "../tinet/net/net_asp.cfg"
const unsigned_t TOPPERS_cfg_valueof_mpfatr_47 = (unsigned_t)(TA_TFIFO);
#line 112 "../tinet/net/net_asp.cfg"
const unsigned_t TOPPERS_cfg_valueof_blkcnt_47 = (unsigned_t)(NUM_MPF_NET_BUF_IF_PDU);
#line 112 "../tinet/net/net_asp.cfg"
const unsigned_t TOPPERS_cfg_valueof_blksz_47 = (unsigned_t)(sizeof(T_NET_BUF_IF_PDU));

#endif

#if defined(NUM_MPF_NET_BUF4_REASSM) && NUM_MPF_NET_BUF4_REASSM > 0

#line 120 "../tinet/net/net_asp.cfg"
const unsigned_t TOPPERS_cfg_static_api_48 = 48;
#define MPF_NET_BUF_REASSM	(<>)
#line 120 "../tinet/net/net_asp.cfg"
const unsigned_t TOPPERS_cfg_valueof_mpfatr_48 = (unsigned_t)(TA_TFIFO);
#line 120 "../tinet/net/net_asp.cfg"
const unsigned_t TOPPERS_cfg_valueof_blkcnt_48 = (unsigned_t)(NUM_MPF_NET_BUF4_REASSM);
#line 120 "../tinet/net/net_asp.cfg"
const unsigned_t TOPPERS_cfg_valueof_blksz_48 = (unsigned_t)(sizeof(T_NET_BUF4_REASSM));

#endif

#if defined(NUM_MPF_NET_BUF6_REASSM) && NUM_MPF_NET_BUF6_REASSM > 0

#line 128 "../tinet/net/net_asp.cfg"
const unsigned_t TOPPERS_cfg_static_api_49 = 49;
#define MPF_NET_BUF_REASSM	(<>)
#line 128 "../tinet/net/net_asp.cfg"
const unsigned_t TOPPERS_cfg_valueof_mpfatr_49 = (unsigned_t)(TA_TFIFO);
#line 128 "../tinet/net/net_asp.cfg"
const unsigned_t TOPPERS_cfg_valueof_blkcnt_49 = (unsigned_t)(NUM_MPF_NET_BUF6_REASSM);
#line 128 "../tinet/net/net_asp.cfg"
const unsigned_t TOPPERS_cfg_valueof_blksz_49 = (unsigned_t)(sizeof(T_NET_BUF6_REASSM));

#endif

#if defined(NUM_MPF_NET_BUF6_65536) && NUM_MPF_NET_BUF6_65536 > 0

#line 136 "../tinet/net/net_asp.cfg"
const unsigned_t TOPPERS_cfg_static_api_50 = 50;
#define MPF_NET_BUF6_65536	(<>)
#line 136 "../tinet/net/net_asp.cfg"
const unsigned_t TOPPERS_cfg_valueof_mpfatr_50 = (unsigned_t)(TA_TFIFO);
#line 136 "../tinet/net/net_asp.cfg"
const unsigned_t TOPPERS_cfg_valueof_blkcnt_50 = (unsigned_t)(NUM_MPF_NET_BUF6_65536);
#line 136 "../tinet/net/net_asp.cfg"
const unsigned_t TOPPERS_cfg_valueof_blksz_50 = (unsigned_t)(sizeof(T_NET_BUF6_65536));

#endif

#ifdef SUPPORT_ETHER

#line 40 "../tinet/net/ethernet.cfg"
const unsigned_t TOPPERS_cfg_static_api_51 = 51;
#define ETHER_OUTPUT_TASK	(<>)
#line 40 "../tinet/net/ethernet.cfg"
const unsigned_t TOPPERS_cfg_valueof_tskatr_51 = (unsigned_t)(TA_HLNG);
#line 40 "../tinet/net/ethernet.cfg"
const signed_t TOPPERS_cfg_valueof_itskpri_51 = (signed_t)(ETHER_OUTPUT_PRIORITY);
#line 40 "../tinet/net/ethernet.cfg"
const unsigned_t TOPPERS_cfg_valueof_stksz_51 = (unsigned_t)(ETHER_OUTPUT_STACK_SIZE);

#line 41 "../tinet/net/ethernet.cfg"
const unsigned_t TOPPERS_cfg_static_api_52 = 52;
#define ETHER_INPUT_TASK	(<>)
#line 41 "../tinet/net/ethernet.cfg"
const unsigned_t TOPPERS_cfg_valueof_tskatr_52 = (unsigned_t)(TA_HLNG|TA_ACT);
#line 41 "../tinet/net/ethernet.cfg"
const signed_t TOPPERS_cfg_valueof_itskpri_52 = (signed_t)(ETHER_INPUT_PRIORITY);
#line 41 "../tinet/net/ethernet.cfg"
const unsigned_t TOPPERS_cfg_valueof_stksz_52 = (unsigned_t)(ETHER_INPUT_STACK_SIZE);

#line 43 "../tinet/net/ethernet.cfg"
const unsigned_t TOPPERS_cfg_static_api_53 = 53;
#define DTQ_ETHER_OUTPUT	(<>)
#line 43 "../tinet/net/ethernet.cfg"
const unsigned_t TOPPERS_cfg_valueof_dtqatr_53 = (unsigned_t)(TA_TFIFO);
#line 43 "../tinet/net/ethernet.cfg"
const unsigned_t TOPPERS_cfg_valueof_dtqcnt_53 = (unsigned_t)(NUM_DTQ_ETHER_OUTPUT);

#line 47 "../tinet/net/ethernet.cfg"
const unsigned_t TOPPERS_cfg_static_api_54 = 54;
#define SEM_MAC2STR_BUFF_LOCK	(<>)
#line 47 "../tinet/net/ethernet.cfg"
const unsigned_t TOPPERS_cfg_valueof_sematr_54 = (unsigned_t)(TA_TPRI);
#line 47 "../tinet/net/ethernet.cfg"
const unsigned_t TOPPERS_cfg_valueof_isemcnt_54 = (unsigned_t)(1);
#line 47 "../tinet/net/ethernet.cfg"
const unsigned_t TOPPERS_cfg_valueof_maxsem_54 = (unsigned_t)(1);

#endif

#ifdef SUPPORT_ETHER

#line 42 "../tinet/netinet/if_ether.cfg"
const unsigned_t TOPPERS_cfg_static_api_55 = 55;
#define SEM_ARP_CACHE_LOCK	(<>)
#line 42 "../tinet/netinet/if_ether.cfg"
const unsigned_t TOPPERS_cfg_valueof_sematr_55 = (unsigned_t)(TA_TPRI);
#line 42 "../tinet/netinet/if_ether.cfg"
const unsigned_t TOPPERS_cfg_valueof_isemcnt_55 = (unsigned_t)(1);
#line 42 "../tinet/netinet/if_ether.cfg"
const unsigned_t TOPPERS_cfg_valueof_maxsem_55 = (unsigned_t)(1);

#endif

#if defined(SUPPORT_INET4)

#ifdef IP4_CFG_FRAGMENT

#line 44 "../tinet/netinet/ip.cfg"
const unsigned_t TOPPERS_cfg_static_api_56 = 56;
#define SEM_IP4_FRAG_QUEUE	(<>)
#line 44 "../tinet/netinet/ip.cfg"
const unsigned_t TOPPERS_cfg_valueof_sematr_56 = (unsigned_t)(TA_TPRI);
#line 44 "../tinet/netinet/ip.cfg"
const unsigned_t TOPPERS_cfg_valueof_isemcnt_56 = (unsigned_t)(1);
#line 44 "../tinet/netinet/ip.cfg"
const unsigned_t TOPPERS_cfg_valueof_maxsem_56 = (unsigned_t)(1);

#endif

#if NUM_REDIRECT_ROUTE_ENTRY > 0

#line 52 "../tinet/netinet/ip.cfg"
const unsigned_t TOPPERS_cfg_static_api_57 = 57;
#define SEM_IN_ROUTING_TBL	(<>)
#line 52 "../tinet/netinet/ip.cfg"
const unsigned_t TOPPERS_cfg_valueof_sematr_57 = (unsigned_t)(TA_TPRI);
#line 52 "../tinet/netinet/ip.cfg"
const unsigned_t TOPPERS_cfg_valueof_isemcnt_57 = (unsigned_t)(1);
#line 52 "../tinet/netinet/ip.cfg"
const unsigned_t TOPPERS_cfg_valueof_maxsem_57 = (unsigned_t)(1);

#endif

#endif

#ifdef SUPPORT_TCP

#line 42 "../tinet/netinet/tcp.cfg"
const unsigned_t TOPPERS_cfg_static_api_58 = 58;
#define TCP_OUTPUT_TASK	(<>)
#line 42 "../tinet/netinet/tcp.cfg"
const unsigned_t TOPPERS_cfg_valueof_tskatr_58 = (unsigned_t)(TA_HLNG);
#line 42 "../tinet/netinet/tcp.cfg"
const signed_t TOPPERS_cfg_valueof_itskpri_58 = (signed_t)(TCP_OUT_TASK_PRIORITY);
#line 42 "../tinet/netinet/tcp.cfg"
const unsigned_t TOPPERS_cfg_valueof_stksz_58 = (unsigned_t)(TCP_OUT_TASK_STACK_SIZE);

#line 53 "../tinet/netinet/tcp.cfg"
const unsigned_t TOPPERS_cfg_static_api_59 = 59;
#define SEM_TCP_POST_OUTPUT	(<>)
#line 53 "../tinet/netinet/tcp.cfg"
const unsigned_t TOPPERS_cfg_valueof_sematr_59 = (unsigned_t)(TA_TPRI);
#line 53 "../tinet/netinet/tcp.cfg"
const unsigned_t TOPPERS_cfg_valueof_isemcnt_59 = (unsigned_t)(0);
#line 53 "../tinet/netinet/tcp.cfg"
const unsigned_t TOPPERS_cfg_valueof_maxsem_59 = (unsigned_t)(1);

#line 54 "../tinet/netinet/tcp.cfg"
const unsigned_t TOPPERS_cfg_static_api_60 = 60;
#define SEM_TCP_CEP	(<>)
#line 54 "../tinet/netinet/tcp.cfg"
const unsigned_t TOPPERS_cfg_valueof_sematr_60 = (unsigned_t)(TA_TPRI);
#line 54 "../tinet/netinet/tcp.cfg"
const unsigned_t TOPPERS_cfg_valueof_isemcnt_60 = (unsigned_t)(1);
#line 54 "../tinet/netinet/tcp.cfg"
const unsigned_t TOPPERS_cfg_valueof_maxsem_60 = (unsigned_t)(1);

#ifdef TCP_CFG_TRACE

#line 57 "../tinet/netinet/tcp.cfg"
const unsigned_t TOPPERS_cfg_static_api_61 = 61;
#define SEM_TCP_TRACE	(<>)
#line 57 "../tinet/netinet/tcp.cfg"
const unsigned_t TOPPERS_cfg_valueof_sematr_61 = (unsigned_t)(TA_TPRI);
#line 57 "../tinet/netinet/tcp.cfg"
const unsigned_t TOPPERS_cfg_valueof_isemcnt_61 = (unsigned_t)(1);
#line 57 "../tinet/netinet/tcp.cfg"
const unsigned_t TOPPERS_cfg_valueof_maxsem_61 = (unsigned_t)(1);

#endif

#endif

#ifdef SUPPORT_UDP

#ifdef UDP_CFG_NON_BLOCKING

#line 46 "../tinet/netinet/udp.cfg"
const unsigned_t TOPPERS_cfg_static_api_62 = 62;
#define UDP_OUTPUT_TASK	(<>)
#line 46 "../tinet/netinet/udp.cfg"
const unsigned_t TOPPERS_cfg_valueof_tskatr_62 = (unsigned_t)(TA_HLNG);
#line 46 "../tinet/netinet/udp.cfg"
const signed_t TOPPERS_cfg_valueof_itskpri_62 = (signed_t)(UDP_OUT_TASK_PRIORITY);
#line 46 "../tinet/netinet/udp.cfg"
const unsigned_t TOPPERS_cfg_valueof_stksz_62 = (unsigned_t)(UDP_OUT_TASK_STACK_SIZE);

#line 57 "../tinet/netinet/udp.cfg"
const unsigned_t TOPPERS_cfg_static_api_63 = 63;
#define SEM_UDP_POST_OUTPUT	(<>)
#line 57 "../tinet/netinet/udp.cfg"
const unsigned_t TOPPERS_cfg_valueof_sematr_63 = (unsigned_t)(TA_TPRI);
#line 57 "../tinet/netinet/udp.cfg"
const unsigned_t TOPPERS_cfg_valueof_isemcnt_63 = (unsigned_t)(0);
#line 57 "../tinet/netinet/udp.cfg"
const unsigned_t TOPPERS_cfg_valueof_maxsem_63 = (unsigned_t)(1);

#endif

#line 61 "../tinet/netinet/udp.cfg"
const unsigned_t TOPPERS_cfg_static_api_64 = 64;
#define SEM_UDP_CEP	(<>)
#line 61 "../tinet/netinet/udp.cfg"
const unsigned_t TOPPERS_cfg_valueof_sematr_64 = (unsigned_t)(TA_TPRI);
#line 61 "../tinet/netinet/udp.cfg"
const unsigned_t TOPPERS_cfg_valueof_isemcnt_64 = (unsigned_t)(1);
#line 61 "../tinet/netinet/udp.cfg"
const unsigned_t TOPPERS_cfg_valueof_maxsem_64 = (unsigned_t)(1);

#endif

#ifdef SUPPORT_INET6

#line 42 "../tinet/netinet6/ip6.cfg"
const unsigned_t TOPPERS_cfg_static_api_65 = 65;
#define SEM_ND6_CACHE	(<>)
#line 42 "../tinet/netinet6/ip6.cfg"
const unsigned_t TOPPERS_cfg_valueof_sematr_65 = (unsigned_t)(TA_TPRI);
#line 42 "../tinet/netinet6/ip6.cfg"
const unsigned_t TOPPERS_cfg_valueof_isemcnt_65 = (unsigned_t)(1);
#line 42 "../tinet/netinet6/ip6.cfg"
const unsigned_t TOPPERS_cfg_valueof_maxsem_65 = (unsigned_t)(1);

#if NUM_ND6_DEF_RTR_ENTRY > 0

#line 48 "../tinet/netinet6/ip6.cfg"
const unsigned_t TOPPERS_cfg_static_api_66 = 66;
#define SEM_ND6_DEFRTRLIST	(<>)
#line 48 "../tinet/netinet6/ip6.cfg"
const unsigned_t TOPPERS_cfg_valueof_sematr_66 = (unsigned_t)(TA_TPRI);
#line 48 "../tinet/netinet6/ip6.cfg"
const unsigned_t TOPPERS_cfg_valueof_isemcnt_66 = (unsigned_t)(1);
#line 48 "../tinet/netinet6/ip6.cfg"
const unsigned_t TOPPERS_cfg_valueof_maxsem_66 = (unsigned_t)(1);

#endif

#ifdef IP6_CFG_FRAGMENT

#line 56 "../tinet/netinet6/ip6.cfg"
const unsigned_t TOPPERS_cfg_static_api_67 = 67;
#define SEM_IP6_FRAG_QUEUE	(<>)
#line 56 "../tinet/netinet6/ip6.cfg"
const unsigned_t TOPPERS_cfg_valueof_sematr_67 = (unsigned_t)(TA_TPRI);
#line 56 "../tinet/netinet6/ip6.cfg"
const unsigned_t TOPPERS_cfg_valueof_isemcnt_67 = (unsigned_t)(1);
#line 56 "../tinet/netinet6/ip6.cfg"
const unsigned_t TOPPERS_cfg_valueof_maxsem_67 = (unsigned_t)(1);

#endif

#if NUM_REDIRECT_ROUTE_ENTRY > 0

#line 64 "../tinet/netinet6/ip6.cfg"
const unsigned_t TOPPERS_cfg_static_api_68 = 68;
#define SEM_IN_ROUTING_TBL	(<>)
#line 64 "../tinet/netinet6/ip6.cfg"
const unsigned_t TOPPERS_cfg_valueof_sematr_68 = (unsigned_t)(TA_TPRI);
#line 64 "../tinet/netinet6/ip6.cfg"
const unsigned_t TOPPERS_cfg_valueof_isemcnt_68 = (unsigned_t)(1);
#line 64 "../tinet/netinet6/ip6.cfg"
const unsigned_t TOPPERS_cfg_valueof_maxsem_68 = (unsigned_t)(1);

#endif

#endif

#ifdef SUPPORT_INET4

#line 44 "../sample/tinet_sample1n.cfg"
const unsigned_t TOPPERS_cfg_static_api_69 = 69;
#define TCP_REPID	(<>)
#line 44 "../sample/tinet_sample1n.cfg"
const unsigned_t TOPPERS_cfg_valueof_tcp4_repatr_69 = (unsigned_t)(0);

#endif

#ifdef SUPPORT_INET6

#line 50 "../sample/tinet_sample1n.cfg"
const unsigned_t TOPPERS_cfg_static_api_70 = 70;
#define TCP_REPID	(<>)
#line 50 "../sample/tinet_sample1n.cfg"
const unsigned_t TOPPERS_cfg_valueof_tcp6_repatr_70 = (unsigned_t)(0);

#endif

#ifdef SUPPORT_INET4

#line 58 "../sample/tinet_sample1n.cfg"
const unsigned_t TOPPERS_cfg_static_api_71 = 71;
#define TCP_CEPID	(<>)
#line 58 "../sample/tinet_sample1n.cfg"
const unsigned_t TOPPERS_cfg_valueof_tcp4_cepatr_71 = (unsigned_t)(0);

#endif

#ifdef SUPPORT_INET6

#line 71 "../sample/tinet_sample1n.cfg"
const unsigned_t TOPPERS_cfg_static_api_72 = 72;
#define TCP_CEPID	(<>)
#line 71 "../sample/tinet_sample1n.cfg"
const unsigned_t TOPPERS_cfg_valueof_tcp6_cepatr_72 = (unsigned_t)(0);

#endif

#line 21 "../sample/sample1n.cfg"
const unsigned_t TOPPERS_cfg_static_api_73 = 73;
#define SEM_TCP_SYSLOG	(<>)
#line 21 "../sample/sample1n.cfg"
const unsigned_t TOPPERS_cfg_valueof_sematr_73 = (unsigned_t)(TA_TPRI);
#line 21 "../sample/sample1n.cfg"
const unsigned_t TOPPERS_cfg_valueof_isemcnt_73 = (unsigned_t)(1);
#line 21 "../sample/sample1n.cfg"
const unsigned_t TOPPERS_cfg_valueof_maxsem_73 = (unsigned_t)(1);

#line 22 "../sample/sample1n.cfg"
const unsigned_t TOPPERS_cfg_static_api_74 = 74;
#define SEM_NET_SEND	(<>)
#line 22 "../sample/sample1n.cfg"
const unsigned_t TOPPERS_cfg_valueof_sematr_74 = (unsigned_t)(TA_TPRI);
#line 22 "../sample/sample1n.cfg"
const unsigned_t TOPPERS_cfg_valueof_isemcnt_74 = (unsigned_t)(1);
#line 22 "../sample/sample1n.cfg"
const unsigned_t TOPPERS_cfg_valueof_maxsem_74 = (unsigned_t)(1);

