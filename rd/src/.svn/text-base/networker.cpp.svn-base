/**
 * =====================================================================================
 *
 *	Filename:  networker.cpp
 *
 *	Description:  header file for networker.cpp
 *
 *	Version:  1.0
 *  Created: 2011-5-26
 *	Revision:  none
 *	Compiler:  gcc
 *
 *	Author:  zhangjunying, zhangjunying@baidu.com
 *	Company:  baidu.com Inc.
 *
 * =====================================================================================
 */

#include "rls.h"
#include "ul_sign.h"
#include "networker.h"
#include "nshead.h"
#include "mc_pack_rp.h"
#include "rls_def.h"
#include "common.h"
#include <time.h>

using namespace idl;

/**
 * ===================  FUNCTION networker ==============================
 * @brief thread function for net working
 * 			接受网络请求，包装成内部数据结构，发送给处理线程进行处理
 *
 * @param [in] arg all the parameter
 * @param [out]
 *
 * @return  void
 * @retval errno
 *
 * @author zhangjunying, zhangjunying@baidu.com
 * @company Baidu Inc.
 * ==============================================================================
 */
void *networker(void *arg){
	///thread index
	int tindex = (int)(long)arg;

	bool bKeepAlive, bRet;
	int handle, fd;
	//	struct timeval s, e;
	int ret;
	Svr_thread_data_t a_thread_data;
	char usrname[MAX_USRNAME_LEN]; /**< usr name */
	uint32_t uid;
    uint baiduid;
    //植入随机种子
    srand((unsigned)time(NULL));
	ret = com_openlog_r();
	if (ret < 0){
		printf("open log in the %dth networker thread fail, exit.\n", tindex);
		myExit(-1);
	}
	DEBUG_LOG("networker open log success, use ul_log");
	// Wait for requests
	while (g_svr_pool.is_run()){
		try{
			bKeepAlive = true;
			usrname[0] = 0;
			uid = 0;
            baiduid = 0;
			if ((bRet = g_svr_pool.fetch_item(&handle, &fd)) != 0){
				usleep(GET_REQUEST_USLEEP);
				goto SESSION_EXIT;
			}
			TRACE_LOG("networker:begin to handle the request");
			ret = get_request(fd, handle, a_thread_data, usrname, &uid, &baiduid);
			if (0 != ret){
				//返回前端其他类别错误
				WARNING_LOG("send response[errno] to client failed");
				g_svr_pool.reset_item(handle, false);
				goto SESSION_EXIT;
			}
			else{
				ret = put_request(a_thread_data, uid, baiduid);    
				if (0 != ret){
					FATAL_LOG("put request failed. user=[%s], uid=[%d]",usrname,uid);
					g_svr_pool.reset_item(handle, false);
					goto SESSION_EXIT;
				}
			}

		} catch (...){
			WARNING_LOG("networker catch exception");
			g_svr_pool.reset_item(handle, false);
		}

		SESSION_EXIT:
		TRACE_LOG("echild:end handle request");
	}

	TRACE_LOG("~~~~~~~~~~~~~~~~ependingpool stop~~~~~~~~~~~~~~~~~~~");
	com_closelog_r();
	return NULL;
}

/**
 * @brief : read request from socket fd.
 *
 * @param [in] fd : socket
 * @param [out] request : head+mcpack, content read from fd
 *
 * @return int
 * @retval errno
 *      - 0 : success
 *      - other : failure
 *
 * @author zhangjunying
 *
 */
int get_request(int fd, int handle, Svr_thread_data_t & data, char *usrname, uint *uid, uint *baiduid){
	int ret;
	nshead_t& head = data.head;
	char *buf=data.buf;
	bsl::xcompool pool;
	bsl::ResourcePool rp;
	mc_pack_t * pack;
    uint temp_baiduid;
	TRACE_LOG("begin: read request from client, fd: %d", fd);
	ret = nshead_read(fd, &head, buf, DEFAULT_MCPACK_LEN, g_config.rtimeout
			* 1000);
	if (0 != ret)
	{
		WARNING_LOG("read request error[errno:%d]", ret);
		return -1;
	}
	pack = mc_pack_open_r_rp(buf, DEFAULT_MCPACK_LEN, &rp);
	char tbuf[DEFAULT_MCPACK_LEN];
    char baiduid_str[MAX_BAIDUID_LEN];
	ret = mc_pack_pack2text(pack, tbuf, DEFAULT_MCPACK_LEN, 1);
	DEBUG_LOG("\trequest::data<--> %s", tbuf);
    cmd* aCmd = cmd::create(&pool);
    aCmd->load(pack);
    strncpy(usrname,aCmd->username(0),MAX_USRNAME_LEN);
    usrname[MAX_USRNAME_LEN-1]=0;
    *uid = aCmd->uid();
    snprintf(baiduid_str, MAX_BAIDUID_LEN, "%s", aCmd->baiduid());
    if(NULL == baiduid || (int)strlen(baiduid_str) != BAIDUID_LEN){
        *baiduid = 0;
        snprintf(baiduid_str, MAX_BAIDUID_LEN, "%s", "");
    }
    else{
        ret = create_baiduid(baiduid_str, temp_baiduid);
        if(ret != 0){
            *baiduid = 0;
        }
        else{
            *baiduid = temp_baiduid;
        }
    }
    data.fd = fd;
    data.handle = handle;
    TRACE_LOG("end: read request success from client, fd: %d", fd);
    DEBUG_LOG("READ DATA:");
    DEBUG_LOG("\trequest::head<-->\n"
              "\t[id:%d],\n"
              "\t[version:%d],\n"
              "\t[log id:%d],\n"
              "\t[provider:%s],\n"
              "\t[magic num:%u],\n"
              "\t[reserved:%d],\n"
              "\t[body length:%d]\n"
              "\t[usrname:%s]\n"
              "\t[uid:%d]\n"
              "\t[baiduid_str:%s]\n"
              "\t[baiduid:%u]",
              head.id,
              head.version,
              head.log_id,
              head.provider,
              head.magic_num,
              head.reserved,
              head.body_len,
              usrname,
              *uid,
              baiduid_str,
              *baiduid);
	return 0;
}

/**
 * @function : 将请求数据提交给处理线程
 * @param
 * 	data 请求数据结构
 * 	usrname 用户名
 * @return 0:ok; <0; error
 */
int put_request(Svr_thread_data_t& data, uint uid, uint baiduid){
    int index;
    int other_index;
    if(uid > 0){//登录用户
        index = uid % g_config.work_threadnum;    
    }
    else if(baiduid > 0){//cookie用户
        index = baiduid % g_config.work_threadnum;
    }
    else{//uid和baiduid都取不到
        index = rand() % g_config.work_threadnum;
    }
    DEBUG_LOG("put_request, [uid:%u][baiduid:%u][index:%d]", uid, baiduid, index);
	ul_pthread_mutex_lock(&(td[index].write_mutex));
    if(td[index].svr_data->size() > DEFAULT_BUF_LEN){//这个线程的队列已经满了,随机选一个
        //释放上一个的锁
        ul_pthread_mutex_unlock(&(td[index].write_mutex));
        other_index = rand() % g_config.work_threadnum;
        ul_pthread_mutex_lock(&(td[other_index].write_mutex));
        if(td[other_index].svr_data->size() > DEFAULT_BUF_LEN){
            WARNING_LOG("The thread buffer for handle this request is full, default size[%d], index[%d]", 
                        DEFAULT_BUF_LEN, other_index);
            ul_pthread_mutex_unlock(&(td[other_index].write_mutex));
            return -4;//队列满了
        }
        //插入到其它的队列
        td[other_index].svr_data->push(data);
        ul_pthread_mutex_unlock(&(td[other_index].write_mutex));
    }
    else{//正常情况下插入当前队列
        td[index].svr_data->push(data);
        ul_pthread_mutex_unlock(&(td[index].write_mutex));
    }
	return 0;
}

