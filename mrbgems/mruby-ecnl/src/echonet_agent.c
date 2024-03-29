/*
 *  TOPPERS ECHONET Lite Communication Middleware
 * 
 *  Copyright (C) 2015-2016 Cores Co., Ltd. Japan
 * 
 *  上記著作権者は，以下の(1)～(4)の条件を満たす場合に限り，本ソフトウェ
 *  ア（本ソフトウェアを改変したものを含む．以下同じ）を使用・複製・改
 *  変・再配布（以下，利用と呼ぶ）することを無償で許諾する．
 *  (1) 本ソフトウェアをソースコードの形で利用する場合には，上記の著作
 *      権表示，この利用条件および下記の無保証規定が，そのままの形でソー
 *      スコード中に含まれていること．
 *  (2) 本ソフトウェアを，ライブラリ形式など，他のソフトウェア開発に使
 *      用できる形で再配布する場合には，再配布に伴うドキュメント（利用
 *      者マニュアルなど）に，上記の著作権表示，この利用条件および下記
 *      の無保証規定を掲載すること．
 *  (3) 本ソフトウェアを，機器に組み込むなど，他のソフトウェア開発に使
 *      用できない形で再配布する場合には，次のいずれかの条件を満たすこ
 *      と．
 *    (a) 再配布に伴うドキュメント（利用者マニュアルなど）に，上記の著
 *        作権表示，この利用条件および下記の無保証規定を掲載すること．
 *    (b) 再配布の形態を，別に定める方法によって，TOPPERSプロジェクトに
 *        報告すること．
 *  (4) 本ソフトウェアの利用により直接的または間接的に生じるいかなる損
 *      害からも，上記著作権者およびTOPPERSプロジェクトを免責すること．
 *      また，本ソフトウェアのユーザまたはエンドユーザからのいかなる理
 *      由に基づく請求からも，上記著作権者およびTOPPERSプロジェクトを
 *      免責すること．
 * 
 *  本ソフトウェアは，無保証で提供されているものである．上記著作権者お
 *  よびTOPPERSプロジェクトは，本ソフトウェアに関して，特定の使用目的
 *  に対する適合性も含めて，いかなる保証も行わない．また，本ソフトウェ
 *  アの利用により直接的または間接的に生じたいかなる損害に関しても，そ
 *  の責任を負わない．
 * 
 */

/*
 *		ECHONET Lite 動的生成ノード
 */

#include <mruby.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#ifdef _MSC_VER
#include <assert.h>
#endif
#include "echonet_task.h"
#include "echonet_dbg.h"

static ER ecn_agent_proc_get_device_list(ecnl_svc_task_t *svc, ecn_agent_t *agent, ECN_FBS_ID req);
static ER ecn_agent_proc_get_device_info(ecnl_svc_task_t *svc, ecn_agent_t *agent, ECN_FBS_ID req);
static void ecn_node_send_set_prop_map(ecnl_svc_task_t *svc, ecn_node_agent_t *node);
static void ecn_node_send_get_prop_map(ecnl_svc_task_t *svc, ecn_node_agent_t *node);
static void ecn_node_send_anno_prop_map(ecnl_svc_task_t *svc, ecn_node_agent_t *node);
static void ecn_node_timeout_on_start(ecnl_svc_task_t *svc, ecn_node_agent_t *node);
static void ecn_node_next_proc_on_set_prpmap_wait(ecnl_svc_task_t *svc, ecn_node_agent_t *node, ecn_obj_t *sobj);
static void ecn_node_timeout_on_set_prpmap_wait(ecnl_svc_task_t *svc, ecn_node_agent_t *node);
static void ecn_node_next_proc_on_get_prpmap_wait(ecnl_svc_task_t *svc, ecn_node_agent_t *node, ecn_obj_t *sobj);
static void ecn_node_timeout_on_get_prpmap_wait(ecnl_svc_task_t *svc, ecn_node_agent_t *node);
static void ecn_node_next_proc_on_anno_prpmap_wait(ecnl_svc_task_t *svc, ecn_node_agent_t *node, ecn_obj_t *sobj);
static void ecn_node_timeout_on_anno_prpmap_wait(ecnl_svc_task_t *svc, ecn_node_agent_t *node);

int ecn_agent_eprpset(ecnl_svc_task_t *svc, const EPRPINIB *item, const void *src, int size, bool_t *anno);
int ecn_agent_eprpget(ecnl_svc_task_t *svc, const EPRPINIB *item, void *dst, int size);

static ecn_agent_queue_t *cast_queue(ecn_obj_t *obj)
{
	return (ecn_agent_queue_t *)((intptr_t)obj - offsetof(ecn_agent_buffer_t, cnt.obj));
}

static ecn_obj_t *cast_obj(ecn_agent_queue_t *queue)
{
	return (ecn_obj_t *)((intptr_t)queue + offsetof(ecn_agent_buffer_t, cnt.obj));
}

static ecn_node_agent_t *cast_node(const EOBJCB *eobj)
{
	return (ecn_node_agent_t *)((intptr_t)eobj - offsetof(ecn_node_agent_t, node.eobj));
}

static ecn_obj_t *cast_obj2(const EOBJINIB *inib)
{
	return (ecn_obj_t *)((intptr_t)inib - offsetof(ecn_obj_t, inib));
}

static ecn_agent_t *cast_agent(const EPRPINIB *inib)
{
	return (ecn_agent_t *)((intptr_t)inib - offsetof(ecn_agent_t, eprpinib));
}

#define loc_cpu()
#define unl_cpu()

ER get_buf(ecn_agent_t *agent, ecn_agent_buffer_t **buf)
{
	ER ret = E_OK;

	loc_cpu();

	if (agent->blkpos < TNUM_AEOBJID) {
		*buf = &agent->blockes[agent->blkpos++];
	}
	else if (agent->free == NULL) {
		ret = E_TMOUT;
	}
	else{
		*buf = agent->free;
		agent->free = agent->free->hdr.free;
	}

	unl_cpu();

	return ret;
}

ER rel_buf(ecn_agent_t *agent, ecn_agent_buffer_t *buf)
{
	if ((buf < &agent->blockes[0]) || (buf >= &agent->blockes[TNUM_AEOBJID]))
		return E_PAR;

	if ((((intptr_t)buf - (intptr_t)&agent->blockes[0]) % sizeof(ecn_agent_buffer_t)) != 0)
		return E_PAR;

	loc_cpu();

	if (agent->free == NULL) {
		agent->free = buf;
		agent->free->hdr.free = NULL;
	}
	else {
		ecn_agent_buffer_t *next = agent->free;
		agent->free = buf;
		agent->free->hdr.free = next;
	}

	unl_cpu();

	return E_OK;
}

/*
 *  キューの初期化
 *
 *  p_queueにはキューヘッダを指定する．
 */
static void
ecn_agent_queue_init(ecn_agent_queue_t *p_queue)
{
#ifdef _DEBUG
	p_queue->p_parent = p_queue;
#endif
	p_queue->p_prev = p_queue;
	p_queue->p_next = p_queue;
}

/*
 *  キューの前エントリへの挿入
 *
 *  p_queueの前にp_entryを挿入する．p_queueにキューヘッダを指定した場
 *  合には，キューの末尾にp_entryを挿入することになる．
 */
static void
ecn_agent_queue_add(ecn_agent_queue_t *p_queue, ecn_agent_queue_t *p_entry)
{
#ifdef _DEBUG
	assert((p_queue->p_parent == p_queue) && (p_entry->p_parent == NULL));
	p_entry->p_parent = p_queue;
#endif
	p_entry->p_prev = p_queue->p_prev;
	p_entry->p_next = p_queue;
	p_queue->p_prev->p_next = p_entry;
	p_queue->p_prev = p_entry;
}

/*
 *  エントリの削除
 *
 *  p_entryをキューから削除する．
 */
static void
ecn_agent_queue_remove(ecn_agent_queue_t *p_queue, ecn_agent_queue_t *p_entry)
{
#ifdef _DEBUG
	assert((p_queue->p_parent == p_queue) && (p_entry->p_parent == p_queue));
	p_entry->p_parent = NULL;
#endif
	p_entry->p_prev->p_next = p_entry->p_next;
	p_entry->p_next->p_prev = p_entry->p_prev;
}

ecn_node_t *ecn_agent_find_node(ecnl_svc_task_t *svc, ECN_ENOD_ID enodid)
{
	ecn_agent_t *agent = &svc->agent;
	ecn_agent_queue_t *queue = agent->nodes.p_next;
#ifdef _DEBUG
	assert(queue->p_parent == &agent->nodes);
#endif
	for (; queue != &agent->nodes; queue = queue->p_next) {
		ecn_node_t *node = (ecn_node_t *)cast_obj(queue);
		if(node->enodId == enodid)
			return node;
	}

	return NULL;
}

ecn_node_agent_t *ecn_agent_find_node2(ecnl_svc_task_t *svc, const EOBJCB *pk_eobj)
{
	ecn_agent_t *agent = &svc->agent;
	ecn_agent_queue_t *queue;

	if(pk_eobj == NULL)
		return NULL;

	queue = agent->nodes.p_next;
#ifdef _DEBUG
	assert(queue->p_parent == &agent->nodes);
#endif
	for (; queue != &agent->nodes; queue = queue->p_next) {
		ecn_node_agent_t *node = (ecn_node_agent_t *)cast_obj(queue);
		if(&node->node.eobj == pk_eobj)
			return node;
	}

	return NULL;
}

ecn_obj_t *ecn_agent_find_eobj(const EOBJCB *pk_nod, T_ECN_EOJ eoj)
{
	ecn_agent_queue_t *devices = &cast_node(pk_nod)->node.devices;
	ecn_agent_queue_t *queue = devices->p_next;
#ifdef _DEBUG
	assert(queue->p_parent == devices);
#endif
	for (; queue != devices; queue = queue->p_next) {
		ecn_obj_t *obj = cast_obj(queue);
		if (obj->inib.eojx1 != eoj.eojx1)
			continue;
		if (obj->inib.eojx2 != eoj.eojx2)
			continue;
		if (obj->inib.eojx3 != eoj.eojx3)
			continue;

		return obj;
	}

	return NULL;
}

ecn_obj_t *ecn_agent_find_obj2(ecn_node_agent_t *pk_nod, const EOBJINIB *pk_obj)
{
	ecn_agent_queue_t *devices = &pk_nod->node.devices;
	ecn_agent_queue_t *queue = devices->p_next;
#ifdef _DEBUG
	assert(queue->p_parent == devices);
#endif
	for (; queue != devices; queue = queue->p_next) {
		ecn_obj_t *obj = cast_obj(queue);
		if (&obj->inib == pk_obj)
			return obj;
	}

	return NULL;
}

ID ecn_agent_get_eobj(const EOBJINIB *pk_obj)
{
	return cast_obj2(pk_obj)->eobjId;
}

const EOBJINIB *ecn_agent_next_eobj(const EOBJCB *pk_nod, const EOBJINIB *pk_obj)
{
	ecn_agent_queue_t *devices = &cast_node(pk_nod)->node.devices;
	ecn_obj_t *device = (ecn_obj_t *)pk_obj->exinf;
	ecn_agent_queue_t *queue = cast_queue(device);
#ifdef _DEBUG
	assert(queue->p_parent == devices);
#endif
	if (queue == devices)
		return NULL;

	return &cast_obj(queue->p_next)->inib;
}

bool_t ecn_agent_get_eoj_enodid(ecnl_svc_task_t *svc, ID eobjid, T_ECN_EOJ *eoj, ECN_ENOD_ID *enodid)
{
	ecn_agent_t *agent = &svc->agent;
	ecn_agent_buffer_t *buf;
	int i = eobjid;

	/* オブジェクトIDから実体を取得 */
	i -= (svc->tmax_eobjid + 1);
	if ((i < 0)
		|| (i >= (sizeof(agent->blockes) / sizeof(agent->blockes[0])))){
		return false;
	}

	buf = &agent->blockes[i];
	if(buf->cnt.obj.eobjId != eobjid)
		return false;

	/* オブジェクトのEOJをコピー */
	memcpy(eoj, &buf->cnt.obj.inib.eojx1, sizeof(*eoj));

	/* 所属するノードのオブジェクトIDを取得 */
	if(buf->cnt.obj.inib.enodid == 0)
		i = buf->cnt.obj.eobjId;
	else
		i = buf->cnt.obj.inib.enodid;

	i -= (svc->tmax_eobjid + 1);
	if ((i < 0)
		|| (i >= (sizeof(agent->blockes) / sizeof(agent->blockes[0])))){
		return false;
	}

	/* ノードIDを取得 */
	buf = &agent->blockes[i];
	*enodid = buf->cnt.node.node.enodId;

	return true;
}

void ecn_agent_set_epc_to_prop_map(uint8_t epc, uint8_t *propMap)
{
	int i, j;
	if ((epc & 0x80) != 0)
		return;
	i = epc & 0xF;
	j = (epc >> 4) - 8;
	propMap[i] |= (1 << j);
}

bool_t ecn_agent_contains_epc_in_prop_map(uint8_t epc, uint8_t *propMap)
{
	int i, j;
	if ((epc & 0x80) != 0)
		return false;
	i = epc & 0xF;
	j = (epc >> 4) - 8;
	return (propMap[i] & (1 << j)) != 0;
}

void ecn_agent_init(ecnl_svc_task_t *svc)
{
	svc->agent.eprpinib.eprpcd = 0x00;					/* プロパティコード */
	svc->agent.eprpinib.eprpatr = EPC_RULE_SET | EPC_RULE_GET;		/* プロパティ属性 */
	svc->agent.eprpinib.eprpsz = 255;					/* プロパティのサイズ */
	svc->agent.eprpinib.exinf = (intptr_t)&svc->agent;	/* プロパティの拡張情報 */
	svc->agent.eprpinib.eprpset = ecn_agent_eprpset;	/* プロパティの設定関数 */
	svc->agent.eprpinib.eprpget = ecn_agent_eprpget;	/* プロパティの取得関数 */

	svc->agent.peprpinib = &svc->agent.eprpinib;

	ecn_agent_queue_init(&svc->agent.nodes);
}

ecn_node_agent_t *ecn_agent_create_node(ecnl_svc_task_t *svc, ecn_agent_t *agent, T_EDATA *esv)
{
	mrb_state *mrb = svc->mrb;
	ecn_agent_buffer_t *result = NULL;
	ecn_node_agent_t *node;
	uint8_t epc;
	uint8_t pdc;
	uint8_t edt[256];
	T_ENUM_EPC enm;
	ER ret;
	T_ECN_EOJ *eoj, *end;

	// プロパティ通知か取得応答で、
	switch (esv->hdr.edata.esv) {
	case ESV_GET_RES:
	case ESV_GET_SNA:
	case ESV_INF:
		break;
	default:
		return NULL;
	}

	// ノードプロファイル宛の場合
	eoj = &esv->hdr.edata.seoj;
	if ((eoj->eojx1 != EOJ_X1_PROFILE) || (eoj->eojx2 != EOJ_X2_NODE_PROFILE)
		|| (eoj->eojx3 != 0x01))
		return NULL;

	ret = ecn_itr_ini(&enm, esv);
	if(ret != E_OK){
		ECN_DBG_PUT("ecn_itr_ini");
	}

	while (ecn_itr_nxt(mrb, &enm, &epc, &pdc, &edt) == E_OK) {
		switch (epc) {
		// インスタンスリスト通知の場合
		case 0xD5:
		// 自ノードインスタンスリストＳ通知の場合
		case 0xD6:
			// サイズが合わない場合
			if (pdc != (1 + edt[0] * sizeof(T_ECN_EOJ)))
				return NULL;

			ret = get_buf(agent, &result);
			if(ret != E_OK){
				ECN_DBG_PUT("get_buf");
				return NULL;
			}

			memset(result, 0, sizeof(*result));
			node = &result->cnt.node;
			node->node.enodId = ((T_ECN_FST_BLK *)esv)->hdr.sender.id;
			node->node.base.svc = svc;
			node->node.base.eobjId = svc->tmax_eobjid + 1 + (((intptr_t)result - (intptr_t)agent->blockes) / sizeof(agent->blockes[0]));
			node->node.base.inib.enodid = 0;
			node->node.base.inib.eobjatr = EOBJ_SYNC_REMOTE_NODE;
			node->node.base.inib.exinf = (intptr_t)node;
			node->node.base.inib.eojx1 = eoj->eojx1;
			node->node.base.inib.eojx2 = eoj->eojx2;
			node->node.base.inib.eojx3 = eoj->eojx3;
			node->node.base.inib.eprp = &agent->peprpinib;
			node->node.base.inib.eprpcnt = 0;
			ecn_agent_set_epc_to_prop_map(0xD5, node->node.base.pmapGet);
			ecn_agent_set_epc_to_prop_map(0xD6, node->node.base.pmapGet);
			ecn_agent_set_epc_to_prop_map(0x9D, node->node.base.pmapGet);
			ecn_agent_set_epc_to_prop_map(0x9E, node->node.base.pmapGet);
			ecn_agent_set_epc_to_prop_map(0x9F, node->node.base.pmapGet);
			ecn_agent_queue_init(&node->node.devices);
			node->node.eobj.profile = &node->node.base.inib;
			node->node.eobj.eobjs = NULL;
			node->node.eobj.eobjcnt = pdc / 3;
			node->state = ecn_node_state_idle;
			node->timer = TMO_FEVR;

			end = (T_ECN_EOJ *)&edt[pdc];
			for (eoj = (T_ECN_EOJ *)&edt[1]; eoj < end; eoj++) {
				ecn_device_t *device;
				ecn_agent_buffer_t *obj;

				ret  = get_buf(agent, &obj);
				if(ret != E_OK){
					ECN_DBG_PUT("get_buf");
					return NULL;
				}

				memset(obj, 0, sizeof(*obj));
				device = &obj->cnt.device;
				device->node = &node->node;
				device->base.svc = svc;
				device->base.eobjId = svc->tmax_eobjid + 1 + (((intptr_t)obj - (intptr_t)agent->blockes) / sizeof(agent->blockes[0]));
				device->base.inib.eobjatr = EOBJ_DEVICE;
				device->base.inib.enodid = node->node.base.eobjId;
				device->base.inib.exinf = (intptr_t)device;
				device->base.inib.eojx1 = eoj->eojx1;
				device->base.inib.eojx2 = eoj->eojx2;
				device->base.inib.eojx3 = eoj->eojx3;
				device->base.inib.eprp = &agent->peprpinib;
				device->base.inib.eprpcnt = 0;
				ecn_agent_set_epc_to_prop_map(0x9D, device->base.pmapGet);
				ecn_agent_set_epc_to_prop_map(0x9E, device->base.pmapGet);
				ecn_agent_set_epc_to_prop_map(0x9F, device->base.pmapGet);

				ecn_agent_queue_add(&node->node.devices, &obj->hdr.queue);
			}
			break;
		default:
			continue;
		}
		break;
	}

	if (result == NULL)
		return NULL;

	ecn_agent_queue_add(&agent->nodes, &result->hdr.queue);

	return node;
}

static ER ecn_agent_proc_get_device_list(ecnl_svc_task_t *svc, ecn_agent_t *agent, ECN_FBS_ID req)
{
	mrb_state *mrb = svc->mrb;
	ER ret;
	ECN_FBS_ID res;
	ecn_inm_get_device_list_req_t msg;
	ECN_FBS_SSIZE_T len;
	ecn_agent_buffer_t *pos, *end = &agent->blockes[TNUM_AEOBJID];
	ecn_inm_get_device_item_t item;
	int i, j;

	ret = _ecn_fbs_get_data(mrb, req, &msg, sizeof(msg), &len);
	if (ret != E_OK) {
		return ret;
	}

	ret = _ecn_tsk_cre_res_fbs(svc, req, ECN_INM_GET_DEVICE_LIST_RES, &res);
	if (ret != E_OK) {
		return ret;
	}

	ret = _ecn_fbs_add_data_ex(mrb, res, &msg.requestid, sizeof(((ecn_inm_get_device_list_res_t *)0)->requestid));
	if (ret != E_OK) {
		_ecn_fbs_del(mrb, res);
		return ret;
	}

	for (i = 0; i < svc->tnum_enodid; i++) {
		const EOBJCB *enod = &svc->eobjcb_table[i];
		for (j = 0; j < enod->eobjcnt; j++) {
			const EOBJINIB *eobj = enod->eobjs[i];
			item.eobjid = echonet_svctask_get_eobjid(svc, eobj);
			item.enodid = eobj->enodid;
			item.state = true;
			item.eojx1 = eobj->eojx1;
			item.eojx2 = eobj->eojx2;
			item.eojx3 = eobj->eojx3;
			item.addrid = (i == 0) ? ENOD_LOCAL_ID : (ENOD_REMOTE_ID + i);

			ret = _ecn_fbs_add_data_ex(mrb, res, &item, sizeof(item));
			if (ret != E_OK) {
				_ecn_fbs_del(mrb, res);
				return ret;
			}
		}
	}

	for (pos = &agent->blockes[0]; pos < end; pos++){
		if(pos->cnt.obj.eobjId == 0)
			continue;

		item.eobjid = pos->cnt.obj.eobjId;
		item.enodid = pos->cnt.obj.inib.enodid;
		item.state = (pos->cnt.obj.pmapFlag & (PMAP_FLAG_SET | PMAP_FLAG_GET | PMAP_FLAG_ANNO))
			== (PMAP_FLAG_SET | PMAP_FLAG_GET | PMAP_FLAG_ANNO);
		item.eojx1 = pos->cnt.obj.inib.eojx1;
		item.eojx2 = pos->cnt.obj.inib.eojx2;
		item.eojx3 = pos->cnt.obj.inib.eojx3;

		if(pos->cnt.device.node != NULL)
			item.addrid = pos->cnt.device.node->enodId;
		else
			item.addrid = pos->cnt.node.node.enodId;

		ret = _ecn_fbs_add_data_ex(mrb, res, &item, sizeof(item));
		if (ret != E_OK) {
			_ecn_fbs_del(mrb, res);
			return ret;
		}
	}

	ret = ecn_fbs_enqueue(res.ptr->hdr.target.mbxid, res.ptr);
	if (ret != E_OK) {
		_ecn_fbs_del(mrb, res);
		return ret;
	}

	return E_OK;
}

static ER ecn_agent_proc_get_device_info(ecnl_svc_task_t *svc, ecn_agent_t *agent, ECN_FBS_ID req)
{
	mrb_state *mrb = svc->mrb;
	ER ret;
	ECN_FBS_ID res;
	ecn_inm_get_device_info_req_t msg;
	ecn_inm_get_device_info_res_t rmsg;
	ECN_FBS_SSIZE_T len;

	ret = _ecn_fbs_get_data(mrb, req, &msg, sizeof(msg), &len);
	if (ret != E_OK) {
		return ret;
	}

	memset(&rmsg, 0, sizeof(rmsg));

	if (msg.eobjid <= svc->tmax_eobjid) {
		const EOBJINIB *eobj = echonet_svctask_get_eobjinib(svc, msg.eobjid);
		int i;

		rmsg.requestid = msg.requestid;
		rmsg.eobjid = msg.eobjid;
		for (i = 0; i < eobj->eprpcnt; i++) {
			uint8_t epc = eobj->eprp[i]->eprpcd;
			ecn_agent_set_epc_to_prop_map(epc, rmsg.pmapSet);
			ecn_agent_set_epc_to_prop_map(epc, rmsg.pmapGet);
			ecn_agent_set_epc_to_prop_map(epc, rmsg.pmapAnno);
		}
		rmsg.eprpcnt = eobj->eprpcnt;
	}
	else {
		int eobjId;
		ecn_agent_buffer_t *pos;

		eobjId = msg.eobjid - svc->tmax_eobjid - 1;
		pos = &agent->blockes[eobjId];

		rmsg.requestid = msg.requestid;
		rmsg.eobjid = pos->cnt.obj.eobjId;
		memcpy(rmsg.pmapSet, pos->cnt.obj.pmapSet, sizeof(rmsg.pmapSet));
		memcpy(rmsg.pmapGet, pos->cnt.obj.pmapGet, sizeof(rmsg.pmapGet));
		memcpy(rmsg.pmapAnno, pos->cnt.obj.pmapAnno, sizeof(rmsg.pmapAnno));
		rmsg.eprpcnt = pos->cnt.obj.eprpcnt;
	}

	ret = _ecn_tsk_cre_res_fbs(svc, req, ECN_INM_GET_DEVICE_INFO_RES, &res);
	if (ret != E_OK) {
		return ret;
	}

	ret = _ecn_fbs_add_data_ex(mrb, res, &rmsg, sizeof(rmsg));
	if (ret != E_OK) {
		_ecn_fbs_del(mrb, res);
		return ret;
	}

	ret = ecn_fbs_enqueue(res.ptr->hdr.target.mbxid, res.ptr);
	if (ret != E_OK) {
		_ecn_fbs_del(mrb, res);
		return ret;
	}

	return E_OK;
}

TMO ecn_agent_get_timer(ecnl_svc_task_t *svc)

{
	TMO timer = TMO_FEVR, temp;
	ecn_agent_t *agent = &svc->agent;
	ecn_node_agent_t *node;
	ecn_agent_queue_t *queue;

	queue = &agent->nodes;
	for (;;) {
		queue = queue->p_next;
#ifdef _DEBUG
		assert(queue->p_parent == &agent->nodes);
#endif
		if(&agent->nodes == queue)
			break;

		node = (ecn_node_agent_t *)cast_obj(queue);
		temp = node->timer;
		if (temp != TMO_FEVR) {
			if ((timer == TMO_FEVR) || (temp < timer)) {
				timer = temp;
			}
		}
	}

	return timer;
}

void ecn_agent_progress(ecnl_svc_task_t *svc, TMO interval)
{
	ecn_agent_t *agent = &svc->agent;
	ecn_node_agent_t *node;
	ecn_agent_queue_t *queue;

	queue = &agent->nodes;
	for (;;) {
		queue = queue->p_next;
#ifdef _DEBUG
		assert(queue->p_parent == &agent->nodes);
#endif
		if(&agent->nodes == queue)
			break;

		node = (ecn_node_agent_t *)cast_obj(queue);
		if (node->timer == TMO_FEVR)
			continue;

		node->timer -= interval;
		if (node->timer <= 0) {
			node->timer = 0;
		}
	}
}

void ecn_agent_timeout(ecnl_svc_task_t *svc)

{
	ecn_agent_t *agent = &svc->agent;
	ecn_node_agent_t *node;
	ecn_agent_queue_t *queue;

	queue = &agent->nodes;
	for (;;) {
		queue = queue->p_next;
#ifdef _DEBUG
		assert(queue->p_parent == &agent->nodes);
#endif
		if(&agent->nodes == queue)
			break;

		node = (ecn_node_agent_t *)cast_obj(queue);
		if (node->timer != 0)
			continue;

		switch (node->state) {
		case ecn_node_state_start:
			ecn_node_timeout_on_start(svc, node);
			break;
		case ecn_node_state_set_prpmap_wait:
			ecn_node_timeout_on_set_prpmap_wait(svc, node);
			break;
		case ecn_node_state_get_prpmap_wait:
			ecn_node_timeout_on_get_prpmap_wait(svc, node);
			break;
		case ecn_node_state_anno_prpmap_wait:
			ecn_node_timeout_on_anno_prpmap_wait(svc, node);
			break;
		case ecn_node_state_fault:
			ecn_node_timeout_on_start(svc, node);
			break;
		default:
#ifdef _DEBUG
			assert(0);
#endif
			break;
		}
	}
}

bool_t ecn_agent_proc_int_msg(ecnl_svc_task_t *svc, ECN_FBS_ID fbs, uint8_t cmd)
{
	ecn_agent_t *agent = &svc->agent;

	switch(cmd)
	{
	case ECN_INM_GET_DEVICE_LIST_REQ:
		ecn_agent_proc_get_device_list(svc, agent, fbs);
		break;
	case ECN_INM_GET_DEVICE_INFO_REQ:
		ecn_agent_proc_get_device_info(svc, agent, fbs);
		break;
	default:
		return false;
	}

	return true;
}

void ecn_agent_proc_ecn_msg(ecnl_svc_task_t *svc, const EOBJCB **ppk_snod, const EOBJINIB **ppk_sobj, T_EDATA *esv)
{
	ecn_agent_t *agent = &svc->agent;
	ecn_node_agent_t *snod;
	ecn_obj_t *sobj;

	/* 静的に定義された送信元の場合 */
	if ((*ppk_snod != NULL) && (*ppk_snod)->eobjs != NULL) {
		/* 処理しない */
		return;
	}

	snod = ecn_agent_find_node2(svc, *ppk_snod);

	/* 送信元を知らなかったら */
	if (snod == NULL) {
		/* 送信元のノード情報を新規に作成 */
		snod = ecn_agent_create_node(svc, agent, esv);
		if (snod == NULL)
			return;
	}

	sobj = ecn_agent_find_obj2(snod, *ppk_sobj);

	/* ノードプロファイルの場合 */
	if ((esv->hdr.edata.seoj.eojx1 == EOJ_X1_PROFILE)
		&& (esv->hdr.edata.seoj.eojx2 == EOJ_X2_NODE_PROFILE)) {
		sobj = &snod->node.base;
	}
	/* 機器オブジェクトの場合 */
	else {
		sobj = ecn_agent_find_eobj(&snod->node.eobj, esv->hdr.edata.seoj);
	}

	*ppk_snod = &snod->node.eobj;
	*ppk_sobj = &sobj->inib;

	agent->current_node = snod;
	agent->msg_proced = false;
}

void ecn_agent_proc_ecn_msg_end(ecnl_svc_task_t *svc)

{
	ecn_agent_t *agent = &svc->agent;
	ecn_node_agent_t *node = agent->current_node;
	ecn_obj_t *sobj;

	if(node == NULL)
		return;

	sobj = node->current;
	if(sobj == NULL)
		return;

	if (agent->msg_proced) {
		switch (node->state) {
		case ecn_node_state_set_prpmap_wait:
			ecn_node_next_proc_on_set_prpmap_wait(svc, node, sobj);
			break;
		case ecn_node_state_get_prpmap_wait:
			ecn_node_next_proc_on_get_prpmap_wait(svc, node, sobj);
			break;
		case ecn_node_state_anno_prpmap_wait:
			ecn_node_next_proc_on_anno_prpmap_wait(svc, node, sobj);
			break;
		}
	}
}

static void ecn_node_send_set_prop_map(ecnl_svc_task_t *svc, ecn_node_agent_t *node)
{
	T_EDATA *esv;
	ecn_obj_t *obj = node->current;

	// プロパティ値読み出し要求
	ecn_esv_get(svc, &esv, obj->eobjId, 0x9E);
	ecn_snd_esv(svc, esv);

	node->state = ecn_node_state_set_prpmap_wait;
	node->timer = (TMO)5000;
}

static void ecn_node_send_get_prop_map(ecnl_svc_task_t *svc, ecn_node_agent_t *node)
{
	T_EDATA *esv;
	ecn_obj_t *obj = node->current;

	// プロパティ値読み出し要求
	ecn_esv_get(svc, &esv, obj->eobjId, 0x9F);
	ecn_snd_esv(svc, esv);

	node->state = ecn_node_state_get_prpmap_wait;
	node->timer = (TMO)5000;
}

static void ecn_node_send_anno_prop_map(ecnl_svc_task_t *svc, ecn_node_agent_t *node)
{
	T_EDATA *esv;
	ecn_obj_t *obj = node->current;

	// プロパティ値読み出し要求
	ecn_esv_get(svc, &esv, obj->eobjId, 0x9D);
	ecn_snd_esv(svc, esv);

	node->state = ecn_node_state_anno_prpmap_wait;
	node->timer = (TMO)5000;
}

static void ecn_node_next_obj(ecn_node_agent_t *node)
{
	ecn_obj_t *obj = node->current;
	ecn_agent_queue_t *queue;
	ecn_device_t *device;

	/* objが指定されていない場合 */
	if(obj == NULL){
		/* このノードを返す */
		node->current = &node->node.base;
		return;
	}
	/* ノードの場合 */
	else if((obj->inib.eojx1 == EOJ_X1_PROFILE) && (obj->inib.eojx2 == EOJ_X2_NODE_PROFILE)){
		node = (ecn_node_agent_t *)obj;

		/* 配下の機器を返す */
		queue = node->node.devices.p_next;
		device = (ecn_device_t *)cast_obj(queue);
	}
	/* 機器の場合 */
	else{
		/* 次の機器を返す */
		node = (ecn_node_agent_t *)((ecn_device_t *)obj)->node;
		queue = cast_queue(obj)->p_next;
		device = (ecn_device_t *)cast_obj(queue);
	}

	/* その機器が末尾だった場合 */
	if(&node->node.devices == queue){
		node->current = NULL;
	}
	else {
		node->current = &device->base;
	}
}

static void ecn_node_timeout_on_start(ecnl_svc_task_t *svc, ecn_node_agent_t *node)
{
	for (;;) {
		ecn_obj_t *obj = node->current;
		if (obj == NULL) {
			node->state = ecn_node_state_idle;
			node->timer = TMO_FEVR;
			return;
		}

		if((obj->pmapFlag & PMAP_FLAG_SET) == 0){
			ecn_node_send_set_prop_map(svc, node);
			break;
		}
		else if((obj->pmapFlag & PMAP_FLAG_GET) == 0){
			ecn_node_send_get_prop_map(svc, node);
			break;
		}
		else if((obj->pmapFlag & PMAP_FLAG_ANNO) == 0){
			ecn_node_send_anno_prop_map(svc, node);
			break;
		}
		else{
			ecn_node_next_obj(node);
		}
	}
}

static void ecn_node_next_proc_on_set_prpmap_wait(ecnl_svc_task_t *svc, ecn_node_agent_t *node, ecn_obj_t *sobj)
{
	if((sobj->pmapFlag & PMAP_FLAG_GET) == 0){
		ecn_node_send_get_prop_map(svc, node);
	}
	else if((sobj->pmapFlag & PMAP_FLAG_ANNO) == 0){
		ecn_node_send_anno_prop_map(svc, node);
	}
	else if((sobj->pmapFlag & PMAP_FLAG_SET) == 0){
		ecn_node_send_set_prop_map(svc, node);
	}
	else{
		ecn_node_next_obj(node);
		ecn_node_timeout_on_start(svc, node);
	}
}

static void ecn_node_timeout_on_set_prpmap_wait(ecnl_svc_task_t *svc, ecn_node_agent_t *node)
{
	ecn_obj_t *obj = node->current;
	if(obj == NULL){
		node->state = ecn_node_state_idle;
		node->timer = TMO_FEVR;
		return;
	}

	node->retry++;
	if(node->retry < 3){
		ecn_node_next_proc_on_set_prpmap_wait(svc, node, obj);
	}
	else{
		node->retry = 0;
		node->state = ecn_node_state_fault;
		node->timer = TMO_FEVR;
	}
}

static void ecn_node_next_proc_on_get_prpmap_wait(ecnl_svc_task_t *svc, ecn_node_agent_t *node, ecn_obj_t *sobj)
{
	if((sobj->pmapFlag & PMAP_FLAG_ANNO) == 0){
		ecn_node_send_anno_prop_map(svc, node);
	}
	else if((sobj->pmapFlag & PMAP_FLAG_SET) == 0){
		ecn_node_send_set_prop_map(svc, node);
	}
	else if((sobj->pmapFlag & PMAP_FLAG_GET) == 0){
		ecn_node_send_get_prop_map(svc, node);
	}
	else{
		ecn_node_next_obj(node);
		ecn_node_timeout_on_start(svc, node);
	}
}

static void ecn_node_timeout_on_get_prpmap_wait(ecnl_svc_task_t *svc, ecn_node_agent_t *node)
{
	ecn_obj_t *obj = node->current;
	if(obj == NULL){
		node->state = ecn_node_state_idle;
		node->timer = TMO_FEVR;
		return;
	}

	ecn_node_next_proc_on_get_prpmap_wait(svc, node, obj);
}

static void ecn_node_next_proc_on_anno_prpmap_wait(ecnl_svc_task_t *svc, ecn_node_agent_t *node, ecn_obj_t *sobj)
{
	if((sobj->pmapFlag & PMAP_FLAG_SET) == 0){
		ecn_node_send_set_prop_map(svc, node);
	}
	else if((sobj->pmapFlag & PMAP_FLAG_GET) == 0){
		ecn_node_send_get_prop_map(svc, node);
	}
	else if((sobj->pmapFlag & PMAP_FLAG_ANNO) == 0){
		ecn_node_send_anno_prop_map(svc, node);
	}
	else{
		ecn_node_next_obj(node);
		ecn_node_timeout_on_start(svc, node);
	}
}

static void ecn_node_timeout_on_anno_prpmap_wait(ecnl_svc_task_t *svc, ecn_node_agent_t *node)
{
	ecn_obj_t *obj = node->current;
	if(obj == NULL){
		node->state = ecn_node_state_idle;
		node->timer = TMO_FEVR;
		return;
	}

	ecn_node_next_proc_on_anno_prpmap_wait(svc, node, obj);
}

const EPRPINIB *ecn_agent_get_property(const EOBJINIB *fp_obj, uint8_t fa_epc, const EPRPINIB *item)
{
	ecn_obj_t *obj = cast_obj2(fp_obj);
	bool_t has = false;

	/* ノードの場合はインスタンスリスト通知と自ノードインスタンスリストＳ通知を必須で受け取る */
	if ((fp_obj->enodid == 0) && ((fa_epc == 0xD5) || (fa_epc == 0xD6)))
		has = true;
	else if (ecn_agent_contains_epc_in_prop_map(fa_epc, obj->pmapGet))
		has = true;
	else if (ecn_agent_contains_epc_in_prop_map(fa_epc, obj->pmapSet))
		has = true;
	else if (ecn_agent_contains_epc_in_prop_map(fa_epc, obj->pmapAnno))
		has = true;

	if(!has)
		return NULL;

	((EPRPINIB *)item)->eprpcd = fa_epc;
	((EPRPINIB *)item)->exinf = (intptr_t)fp_obj;

	return item;
}

int ecn_agent_eprpget(ecnl_svc_task_t *svc, const EPRPINIB *item, void *dst, int size)
{
	return 0;
}

int ecn_agent_eprpset(ecnl_svc_task_t *svc, const EPRPINIB *item, const void *src, int size, bool_t *anno)
{
	ecn_agent_t *agent = cast_agent(item);
	ecn_node_agent_t *node = agent->current_node;
	const uint8_t *edt = (const uint8_t *)src;
	ecn_obj_t *sobj = cast_obj2((const EOBJINIB *)item->exinf);
	uint8_t eprpcnt;
	int i;

	switch (item->eprpcd) {
	/* インスタンスリスト通知の場合 */
	case 0xD5:
	/* 自ノードインスタンスリストＳ通知の場合 */
	case 0xD6:
		if ((node != NULL) && (node->state == ecn_node_state_idle)) {
			ecn_agent_queue_t *devices = &node->node.devices;
			ecn_agent_queue_t *queue = devices->p_next;
#ifdef _DEBUG
			assert(queue->p_parent == devices);
#endif
			for (; queue != devices; queue = queue->p_next) {
				ecn_obj_t *obj = cast_obj(queue);
				obj->pmapFlag = 0;
			}
			node->node.base.pmapFlag = 0;
			node->state = ecn_node_state_start;
			node->timer = (TMO)1000;
			node->current = sobj;
		}
		break;
	/* 通知プロパティマップの場合 */
	case 0x9D:
		eprpcnt = edt[0];

		if (eprpcnt < 16) {
			/* サイズチェック */
			if (eprpcnt + 1 != size)
				return 0;

			for (i = 1; i < size; i++)
				ecn_agent_set_epc_to_prop_map(edt[i], sobj->pmapAnno);
		}
		else {
			/* サイズチェック */
			if (size != 17)
				return 0;

			memcpy(sobj->pmapAnno, &edt[1], 16);
		}
		sobj->eprpcnt = eprpcnt;
		sobj->pmapFlag |= PMAP_FLAG_ANNO;
		break;
	/* SETプロパティマップの場合 */
	case 0x9E:
		eprpcnt = edt[0];

		if (eprpcnt < 16) {
			/* サイズチェック */
			if (eprpcnt + 1 != size)
				return 0;

			for (i = 1; i < size; i++)
				ecn_agent_set_epc_to_prop_map(edt[i], sobj->pmapSet);
		}
		else {
			/* サイズチェック */
			if (size != 17)
				return 0;

			memcpy(sobj->pmapSet, &edt[1], 16);
		}
		sobj->eprpcnt = eprpcnt;
		sobj->pmapFlag |= PMAP_FLAG_SET;
		break;
	/* GETプロパティマップの場合 */
	case 0x9F:
		eprpcnt = edt[0];

		if (eprpcnt < 16) {
			/* サイズチェック */
			if (eprpcnt + 1 != size)
				return 0;

			for (i = 1; i < size; i++)
				ecn_agent_set_epc_to_prop_map(edt[i], sobj->pmapGet);
		}
		else {
			/* サイズチェック */
			if (size != 17)
				return 0;

			memcpy(sobj->pmapGet, &edt[1], 16);
		}
		sobj->eprpcnt = eprpcnt;
		sobj->pmapFlag |= PMAP_FLAG_GET;
		break;
	default:
		svc->forward_esv = true;
		return 0;
	}

	agent->msg_proced = true;

	return size;
}

ER ecn_agent_get_device_list(ecnl_svc_task_t *svc, T_ECN_FBS_QUEUE *sender, int requestid, ECN_FBS_ID *pk_req)
{
	mrb_state *mrb = svc->mrb;
	ER a_ret;
	ECN_FBS_ID req;

	a_ret = _ecn_tsk_cre_req_fbs(svc, sender, ECN_INM_GET_DEVICE_LIST_REQ, &req);
	if (a_ret != E_OK) {
		return a_ret;
	}

	a_ret = _ecn_fbs_add_data_ex(mrb, req, &requestid, sizeof(((ecn_inm_get_device_list_req_t *)0)->requestid));
	if (a_ret != E_OK) {
		_ecn_fbs_del(mrb, req);
		return a_ret;
	}

	*pk_req = req;

	return E_OK;
}

ER ecn_agent_get_device_info(ecnl_svc_task_t *svc, T_ECN_FBS_QUEUE *sender, int requestid, ID eobjid, ECN_FBS_ID *pk_req)
{
	mrb_state *mrb = svc->mrb;
	ER a_ret;
	ECN_FBS_ID req;

	a_ret = _ecn_tsk_cre_req_fbs(svc, sender, ECN_INM_GET_DEVICE_INFO_REQ, &req);
	if (a_ret != E_OK) {
		return a_ret;
	}

	a_ret = _ecn_fbs_add_data_ex(mrb, req, &requestid, sizeof(((ecn_inm_get_device_info_req_t *)0)->requestid));
	if (a_ret != E_OK) {
		_ecn_fbs_del(mrb, req);
		return a_ret;
	}

	a_ret = _ecn_fbs_add_data_ex(mrb, req, &eobjid, sizeof(((ecn_inm_get_device_info_req_t *)0)->eobjid));
	if (a_ret != E_OK) {
		_ecn_fbs_del(mrb, req);
		return a_ret;
	}

	*pk_req = req;

	return E_OK;
}
