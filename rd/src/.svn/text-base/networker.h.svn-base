/**
 * =====================================================================================
 *
 *	Filename:  networker.h
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

#ifndef _NETWORKER_H_
#define _NETWORKER_H_


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
 * @date 12/01/2009 10:42:17 AM
 * @company Baidu Inc.
 * ==============================================================================
 */
void *networker(void *arg);

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
int get_request(int fd, int handle, Svr_thread_data_t & data, char *usrname, uint *uid, uint *baiduid);

/**
 * @function : 将请求数据提交给处理线程
 * @param
 * 	data 请求数据结构
 * 	uid 用户id
 * @return 0:ok; <0; error
 */
int put_request(Svr_thread_data_t& data, uint uid, uint baiduid);

#endif /* _NETWORKER_H_ */
