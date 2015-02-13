/**
 * =====================================================================================
 *
 *  Filename:  redis.h
 *
 *  Description:  header file for redis.cpp
 *
 *  Version:  1.0
 *  Created: 2013-12-24
 *  Revision:  none
 *  Compiler:  gcc
 *
 *  Author:  zhaojiangwei@baidu.com
 *  Company:  baidu.com Inc.
 *
 * =====================================================================================
 */

#ifndef _REDIS_H_
#define _REDIS_H_

#include "ul_log.h"
#include "ul_conf.h"
#include "rls.h"
#include "macro.h"
#include "rls_dictseeker.h"
#include "redis_client.h"

/**
 * @Synopsis  get_redis_ulikesongs 获取redis中存的用户喜欢歌曲列表
 *
 * @Param key reids-key
 * @Param field 
 * @Param redis_list 结果list
 * @Param max_len 列表最大长度
 * @Param list_len 最终列表长度
 * @Param redis_source 算法来源
 * @Param filter_dict 过滤字典
 *
 * @Returns  
 */
int get_redis_ulikesongs(uint uid, Item_bean* redis_list, int &list_len);

/**
 * @Synopsis  get_redis_rlist 获取redis中存的用户推荐列表
 *
 * @Param key reids-key
 * @Param field 
 * @Param redis_list 结果list
 * @Param max_len 列表最大长度
 * @Param list_len 最终列表长度
 * @Param redis_source 算法来源
 * @Param filter_dict 过滤字典
 *
 * @Returns  
 */
int get_redis_rlist(uint uid, const char *ch_name, const char *list_tag, const char *field, Song_item_t* redis_list,
        uint max_len, uint &list_len, uint redis_source, const sodict_build_t* filter_dict);

/**
 * @Synopsis  get_redis_rlist_sign 获取redis中存的用户推荐列表的sign值
 *
 * @Param[in] uid
 * @Param[in] field 
 * @Param[in] ch_name
 * @Param[out] redis_sign
 * @Param[out] dest_redis_sign_len
 *
 * @Returns FAIL/SUCCESS 
 */
int get_redis_sign(uint uid, const char *ch_name, const char *list_tag, const char *field, char *redis_sign, uint &dest_redis_sign_len);

/**
 * @Synopsis  redis_get_random_list 获取redis中存的随机推荐列表
 *
 * @Param key reids-key
 * @Param field 
 * @Param redis_list 结果list
 * @Param max_len 列表最大长度
 * @Param list_len 最终列表长度
 * @Param filter_dict 过滤字典
 *
 * @Returns  
 */
int redis_get_random_list(Song_item_t* redis_list, uint max_len, uint &list_len, const sodict_build_t* filter_dict);
#endif /*_REDIS_H_*/
