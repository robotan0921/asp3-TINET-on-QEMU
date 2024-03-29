/*
 *  TINET (TCP/IP Protocol Stack)
 * 
 *  Copyright (C) 2001-2009 by Dep. of Computer Science and Engineering
 *                   Tomakomai National College of Technology, JAPAN
 *
 *  上記著作権者は，以下の (1)～(4) の条件か，Free Software Foundation 
 *  によって公表されている GNU General Public License の Version 2 に記
 *  述されている条件を満たす場合に限り，本ソフトウェア（本ソフトウェア
 *  を改変したものを含む．以下同じ）を使用・複製・改変・再配布（以下，
 *  利用と呼ぶ）することを無償で許諾する．
 *  (1) 本ソフトウェアをソースコードの形で利用する場合には，上記の著作
 *      権表示，この利用条件および下記の無保証規定が，そのままの形でソー
 *      スコード中に含まれていること．
 *  (2) 本ソフトウェアを，ライブラリ形式など，他のソフトウェア開発に使
 *      用できる形で再配布する場合には，再配布に伴うドキュメント（利用
 *      者マニュアルなど）に，上記の著作権表示，この利用条件および下記
 *      の無保証規定を掲載すること．
 *  (3) 本ソフトウェアを，機器に組み込むなど，他のソフトウェア開発に使
 *      用できない形で再配布する場合には，次の条件を満たすこと．
 *    (a) 再配布に伴うドキュメント（利用者マニュアルなど）に，上記の著
 *        作権表示，この利用条件および下記の無保証規定を掲載すること．
 *  (4) 本ソフトウェアの利用により直接的または間接的に生じるいかなる損
 *      害からも，上記著作権者およびTOPPERSプロジェクトを免責すること．
 *
 *  本ソフトウェアは，無保証で提供されているものである．上記著作権者お
 *  よびTOPPERSプロジェクトは，本ソフトウェアに関して，その適用可能性も
 *  含めて，いかなる保証も行わない．また，本ソフトウェアの利用により直
 *  接的または間接的に生じたいかなる損害に関しても，その責任を負わない．
 * 
 *  @(#) $Id: udp_echo_srv.c 971 2016-06-21 14:57:36Z coas-nagasima $
 */

/* 
 *  UDP ECHO サーバ
 */

#include <string.h>

#ifdef TARGET_KERNEL_ASP

#include <kernel.h>
#include <sil.h>
#include <t_syslog.h>
#include "kernel_cfg.h"

#endif	/* of #ifdef TARGET_KERNEL_ASP */

#ifdef TARGET_KERNEL_JSP

#include <t_services.h>
#include "kernel_id.h"
#include "tinet_id.h"

#endif	/* of #ifdef TARGET_KERNEL_JSP */

#include <tinet_defs.h>
#include <tinet_config.h>

#include <net/net.h>
#include <net/net_timer.h>

#include <netinet/in.h>
#include <netinet/in_itron.h>

#include <netapp/netapp.h>
#include <netapp/netapp_var.h>
#include <netapp/echo.h>

#ifdef USE_UDP_ECHO_SRV

/*
 *  受信タイムアウト
 */

#define RCV_TMOUT	TMO_FEVR
//#define RCV_TMOUT	(30*ULONG_C(1000))

#define BUF_SIZE	2048

static char	echo_rcv_buf[BUF_SIZE];
static T_IPEP	dst;

#ifdef USE_UDP_CALL_BACK

/*
 *  コールバック関数
 */

ER
callback_udp_echo_srv (ID cepid, FN fncd, void *p_parblk)
{
	ER_UINT	len;
	SYSTIM	now;

	if ((len = UDP_RCV_DAT(cepid, &dst, echo_rcv_buf, sizeof(echo_rcv_buf), TMO_FEVR)) >= 0) {
		echo_rcv_buf[len] = '\0';
		get_tim(&now);
		syslog(LOG_NOTICE, "[UES:%02d UCB] received,   %6ld, from: %s.%d,\n"
		                   "                                 msg: '%s'",
		                   cepid, now / SYSTIM_HZ, IP2STR(NULL, &dst.ipaddr), dst.portno, echo_rcv_buf);
		if (len > 0) {
			len = UDP_SND_DAT(cepid, &dst, echo_rcv_buf, len, TMO_FEVR);
			get_tim(&now);
			if (len >= 0)
				syslog(LOG_NOTICE, "[UES:%02d UCB] sent,       %6ld, len: %d",
				                   cepid, now / SYSTIM_HZ, len);
			else
				syslog(LOG_NOTICE, "[UES:%02d UCB] send error, %6ld: %s",
				                   cepid, now / SYSTIM_HZ, itron_strerror(len));
			}
		len = E_OK;
		}
	else {
		get_tim(&now);
		syslog(LOG_NOTICE, "[UES:%02d UCB] recv error, %6ld: %s",
		                   cepid, now / SYSTIM_HZ, itron_strerror(len));
		}

	return len;
	}

#else	/* of #ifdef USE_UDP_CALL_BACK */

#ifdef USE_UDP_NON_BLOCKING

/*
 *  変数
 */

static ER_UINT		nblk_len;

/*
 *  ノンブロッキングコールのコールバック関数
 */

ER
callback_nblk_udp_echo_srv (ID cepid, FN fncd, void *p_parblk)
{
	SYSTIM	now;

	get_tim(&now);
	nblk_len = *(ER_UINT*)p_parblk;
	if (nblk_len < 0) {	/* 0 以下の場合は、エラーコード */
		syslog(LOG_NOTICE, "[UES:%02d CBR] error,      %6ld: %s, fncd: %s",
		                   cepid, now / SYSTIM_HZ, itron_strerror(nblk_len), in_strtfn(fncd));
		}
	else if (fncd == TFN_UDP_RCV_DAT) {
		echo_rcv_buf[nblk_len] = '\0';
		syslog(LOG_NOTICE, "[UES:%02d CBR] received,   %6ld, from: %s.%d,\n"
		                   "                                 msg: '%s'",
		                   cepid, now / SYSTIM_HZ, IP2STR(NULL, &dst.ipaddr), dst.portno, echo_rcv_buf);
		}
	syscall(wup_tsk(UDP_ECHO_SRV_TASK));
	return E_OK;
	}

/*
 *  UDP ECHO サーバ
 */

ER
udp_echo_srv (ID cepid)
{
	ER	error;
	SYSTIM	now;

	if ((error = UDP_RCV_DAT(cepid, &dst, echo_rcv_buf, sizeof(echo_rcv_buf), TMO_NBLK)) != E_WBLK) {
		get_tim(&now);
		syslog(LOG_NOTICE, "[UES:%02d RCV] recv error, %6ld: %s", cepid, now / SYSTIM_HZ, itron_strerror(error));
		return error;
		}

	syscall(slp_tsk());
	if (nblk_len < 0)
		error = nblk_len;
	else {
		if ((error = UDP_SND_DAT(cepid, &dst, echo_rcv_buf, nblk_len, TMO_NBLK)) != E_WBLK) {
			get_tim(&now);
			syslog(LOG_NOTICE, "[UES:%02d SND] send error, %6ld: %s",
			                   cepid, now / SYSTIM_HZ, itron_strerror(error));
			return error;
			}

		syscall(slp_tsk());
		if (nblk_len < 0)
			error = nblk_len;
		else {
			get_tim(&now);
			syslog(LOG_NOTICE, "[UES:%02d SND] sent,       %6ld, len: %d", cepid, now / SYSTIM_HZ, nblk_len);
			error = E_OK;
			}
		}

	return error;
	}

#else	/* of #ifdef USE_UDP_NON_BLOCKING */

/*
 *  UDP ECHO サーバ
 */

ER
udp_echo_srv (ID cepid)
{
	ER_UINT	len;
	SYSTIM	now;

	if ((len = UDP_RCV_DAT(cepid, &dst, echo_rcv_buf, sizeof(echo_rcv_buf), RCV_TMOUT)) >= 0) {
		get_tim(&now);
		echo_rcv_buf[len] = '\0';
		syslog(LOG_NOTICE, "[UES:%02d RCV] received,   %6ld, from: %s.%d,\n"
		                   "                                 msg: '%s'",
		                   cepid, now / SYSTIM_HZ, IP2STR(NULL, &dst.ipaddr), dst.portno, echo_rcv_buf);
		if (len > 0) {
			len = UDP_SND_DAT(cepid, &dst, echo_rcv_buf, len, TMO_FEVR);
			get_tim(&now);
			if (len >= 0)
				syslog(LOG_NOTICE, "[UES:%02d SND] sent,       %6ld, len: %d",
				                   cepid, now / SYSTIM_HZ, (uint16_t)len);
			else
				syslog(LOG_NOTICE, "[UES:%02d SND] send error, %6ld: %s",
				                   cepid, now / SYSTIM_HZ, itron_strerror(len));
			}
		}
	else {
		get_tim(&now);
		syslog(LOG_NOTICE, "[UES:%02d RCV] recv error, %6ld: %s", cepid, now / SYSTIM_HZ, itron_strerror(len));
		}

	return len >= 0 || len == E_TMOUT ? E_OK : len;
	}

#endif	/* of #ifdef USE_UDP_NON_BLOCKING */

/*
 *  UDP ECHO サーバタスク
 */

#ifdef USE_UDP_EXTENTIONS

void
udp_echo_srv_task (intptr_t exinf)
{
	ID		tskid, cepid;
	ER		error;
	T_UDP_CCEP	ccep;

	get_tid(&tskid);
	syslog(LOG_NOTICE, "[UDP ECHO SRV:%d,%d] started.", tskid, (ID)exinf);
	while (true) {

		syscall(slp_tsk());

		ccep.cepatr = UINT_C(0);
		ccep.myaddr.portno = UINT_C(7);

#if defined(SUPPORT_INET4)
		ccep.myaddr.ipaddr = IPV4_ADDRANY;
#endif

#if defined(SUPPORT_INET6)
		memcpy(&ccep.myaddr.ipaddr, &ipv6_addrany, sizeof(T_IN6_ADDR));
#endif

#ifdef USE_UDP_NON_BLOCKING
		ccep.callback = (FP)callback_nblk_udp_echo_srv;
#else
		ccep.callback = NULL;
#endif

		if ((error = alloc_udp_cep(&cepid, tskid, &ccep)) != E_OK) {
			syslog(LOG_NOTICE, "[UES:%02d TSK] CEP create error: %s", cepid, itron_strerror(error));
			continue;
			}

		while (error == E_OK) {
			if ((error = udp_echo_srv(cepid)) != E_OK) {
				if ((error = free_udp_cep(cepid, !(error == E_NOEXS || error == E_DLT))) != E_OK)
					syslog(LOG_NOTICE, "[UEC:%02d TSK] CEP delete error: %s", cepid, itron_strerror(error));
				break;
				}
			}

		}
	slp_tsk();
	}

#else	/* of #ifdef USE_UDP_EXTENTIONS */

void
udp_echo_srv_task (intptr_t exinf)
{
	ID	tskid;
	ER	error = E_OK;

	get_tid(&tskid);
	syslog(LOG_NOTICE, "[UDP ECHO SRV:%d,%d] started.", tskid, (ID)exinf);
	while (error == E_OK) {
		error = udp_echo_srv((ID)exinf);
		}
	slp_tsk();
	}

#endif	/* of #ifdef USE_UDP_EXTENTIONS */

#endif	/* of #ifdef USE_UDP_CALL_BACK */

#endif	/* of #ifdef USE_UDP_ECHO_SRV */
