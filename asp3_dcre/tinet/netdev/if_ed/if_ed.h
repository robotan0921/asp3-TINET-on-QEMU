/*
 *  TINET (TCP/IP Protocol Stack)
 * 
 *  Copyright (C) 2001-2009 by Dep. of Computer Science and Engineering
 *                   Tomakomai National College of Technology, JAPAN
 *
 *  �嵭����Ԥϡ��ʲ��� (1)��(4) �ξ�狼��Free Software Foundation 
 *  �ˤ�äƸ�ɽ����Ƥ��� GNU General Public License �� Version 2 �˵�
 *  �Ҥ���Ƥ���������������˸¤ꡤ�ܥ��եȥ��������ܥ��եȥ�����
 *  ����Ѥ�����Τ�ޤࡥ�ʲ�Ʊ���ˤ���ѡ�ʣ�������ѡ������ۡʰʲ���
 *  ���ѤȸƤ֡ˤ��뤳�Ȥ�̵���ǵ������롥
 *  (1) �ܥ��եȥ������򥽡��������ɤη������Ѥ�����ˤϡ��嵭������
 *      ��ɽ�����������Ѿ�浪��Ӳ�����̵�ݾڵ��꤬�����Τޤޤη��ǥ���
 *      ����������˴ޤޤ�Ƥ��뤳�ȡ�
 *  (2) �ܥ��եȥ������򡤥饤�֥������ʤɡ�¾�Υ��եȥ�������ȯ�˻�
 *      �ѤǤ�����Ǻ����ۤ�����ˤϡ������ۤ�ȼ���ɥ�����ȡ�����
 *      �ԥޥ˥奢��ʤɡˤˡ��嵭�����ɽ�����������Ѿ�浪��Ӳ���
 *      ��̵�ݾڵ����Ǻܤ��뤳�ȡ�
 *  (3) �ܥ��եȥ������򡤵�����Ȥ߹���ʤɡ�¾�Υ��եȥ�������ȯ�˻�
 *      �ѤǤ��ʤ����Ǻ����ۤ�����ˤϡ����ξ������������ȡ�
 *    (a) �����ۤ�ȼ���ɥ�����ȡ����Ѽԥޥ˥奢��ʤɡˤˡ��嵭����
 *        �ɽ�����������Ѿ�浪��Ӳ�����̵�ݾڵ����Ǻܤ��뤳�ȡ�
 *  (4) �ܥ��եȥ����������Ѥˤ��ľ��Ū�ޤ��ϴ���Ū�������뤤���ʤ�»
 *      ������⡤�嵭����Ԥ����TOPPERS�ץ������Ȥ����դ��뤳�ȡ�
 *
 *  �ܥ��եȥ������ϡ�̵�ݾڤ��󶡤���Ƥ����ΤǤ��롥�嵭����Ԥ�
 *  ���TOPPERS�ץ������Ȥϡ��ܥ��եȥ������˴ؤ��ơ�����Ŭ�Ѳ�ǽ����
 *  �ޤ�ơ������ʤ��ݾڤ�Ԥ�ʤ����ޤ����ܥ��եȥ����������Ѥˤ��ľ
 *  ��Ū�ޤ��ϴ���Ū�������������ʤ�»���˴ؤ��Ƥ⡤������Ǥ�����ʤ���
 * 
 *  @(#) $Id: if_ed.h,v 1.5 2009/12/24 05:46:31 abe Exp abe $
 */

/*
 * Copyright (C) 1993, David Greenman. This software may be used, modified,
 *   copied, distributed, and sold, in both source and binary form provided
 *   that the above copyright and these terms are retained. Under no
 *   circumstances is the author responsible for the proper functioning
 *   of this software, nor does the author assume any responsibility
 *   for damages incurred with its use.
 */

#ifndef _IF_ED_H_
#define _IF_ED_H_

/*
 *  NIC ������ޥ���
 */

#define IF_ETHER_NIC_GET_SOFTC()	ed_get_softc()
#define IF_ETHER_NIC_WATCHDOG(i)	ed_watchdog(i)
#define IF_ETHER_NIC_PROBE(i)		ed_probe(i)
#define IF_ETHER_NIC_INIT(i)		ed_init(i)
#define IF_ETHER_NIC_READ(i)		ed_read(i)
#define IF_ETHER_NIC_RESET(i)		ed_reset(i)
#define IF_ETHER_NIC_START(i,o)		ed_start(i,o)

#define T_IF_ETHER_NIC_SOFTC		struct t_ed_softc

/* IPv6 �ط� */

#define IF_ETHER_NIC_IN6_IFID(i,a)	get_mac6_ifid(i,a)	/* ���󥿥ե��������̻Ҥ�����		*/
#define IF_ETHER_NIC_ADDMULTI(s)	ed_addmulti(s)		/* �ޥ�����㥹�ȥ��ɥ쥹����Ͽ		*/

#if !defined(TOPPERS_MACRO_ONLY) && !defined(_MACRO_ONLY)

/*
 *  ��������
 */

#ifndef T_IF_SOFTC_DEFINED

typedef struct t_if_softc T_IF_SOFTC;

#define T_IF_SOFTC_DEFINED

#endif	/* of #ifndef T_IF_SOFTC_DEFINED */

#ifndef T_NET_BUF_DEFINED

typedef struct t_net_buf T_NET_BUF;

#define T_NET_BUF_DEFINED

#endif	/* of #ifndef T_NET_BUF_DEFINED */

/*
 *  �ؿ�
 */

extern T_IF_SOFTC *ed_get_softc(void);
extern void ed_watchdog(T_IF_SOFTC *ic);
extern void ed_probe(T_IF_SOFTC *ic);
extern void ed_init(T_IF_SOFTC *ic);
extern void ed_reset(T_IF_SOFTC *ic);
extern T_NET_BUF *ed_read(T_IF_SOFTC *ic);
extern void ed_start(T_IF_SOFTC *ic, T_NET_BUF *output);
extern ER ed_addmulti(T_IF_SOFTC *ic);
extern void if_ed_handler(void);

#endif /* #if !defined(TOPPERS_MACRO_ONLY) && !defined(_MACRO_ONLY) */

#endif	/* of #ifndef _IF_ED_H_ */
