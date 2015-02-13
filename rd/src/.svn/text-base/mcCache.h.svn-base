/**
 * =====================================================================================
 *
 *  Filename:  mcCache.h
 *
 *  Description:  header file for mcCache.cpp
 *
 *  Version:  1.0
 *  Created: 2013-3-19
 *  Revision:  none
 *  Compiler:  gcc
 *
 *  Author:  wensaiping@baidu.com
 *  Company:  baidu.com Inc.
 *
 * =====================================================================================
 */

#ifndef _MCCACHE_H_
#define _MCCACHE_H_

#include "ul_log.h"
#include "ul_conf.h"
#include "bsl/pool.h"
#include "rls.h"
#include "macro.h"
#include "dao.h"
#include "rls_struct.h"
#include "rls_instant.h"
#include "rls_uscgetter.h"
#include "rls_dictseeker.h"
//#include "McClient.h"
#include "ne_mcclient.h"

/***
 *cache头,用于区分存储于不同内容的cache
 */

/* *cache存储数据 */
//试听历史,
#define LISTEN_HISTORY "lh"
//coookie试听历史
#define CO_LISTEN_HISTORY "clh"
//用户行为下一首
#define ACTION_NEXT "an"
//cookie用户行为下一首
#define CO_ACTION_NEXT "can"
//用户行为上一首
#define ACTION_PREVIOUS "ap"
//cookie用户行为上一首
#define CO_ACTION_PREVIOUS "cap"

//用户音乐盒完整试听
#define ACTION_BOX_HISTORY "abh"
//cookie用户音乐盒完整试听
#define CO_ACTION_BOX_HISTORY "cabh"
//用户音乐盒搜索歌曲
#define ACTION_BOX_SEARCH "abs"
//cookie用户音乐盒搜索歌曲
#define CO_ACTION_BOX_SEARCH "cabs"

//音乐盒行为
#define BOX_ACTION "ba"
//cookie用户音乐盒行为
#define CO_BOX_ACTION "cba"

//用户喜欢歌曲
#define USC_LOVE_SONG "ls"
//cookie用户喜欢歌曲
#define CO_LOVE_SONG "cls"
//用户不喜欢歌曲
#define USC_HATE_SONG "hs"
//cookie用户不喜欢歌曲
#define CO_HATE_SONG "chs"
//用户云收藏歌曲
#define USC_CLOUD_SONG "ucs"
//用户算法列表
#define RAL_LIST "rl"
//用户标签列表
#define TAG_LIST "tl"
//百度音乐人用户行为
#define Y_USER_BEHAVIOR "yub"
//百度音乐人cookie行为
#define CO_Y_USER_BEHAVIOR "cyub"

/* **实时更新cache数据*/
//登陆用户播放列表
#define PLAY_LIST "pl"
//cookie用户播放列表
#define CO_PLAY_LIST "cpl"
//登陆用户即时模型
#define INSTANT_MODEL "im"
//cookie用户即时模型
#define CO_INSTANT_MODEL "cim"
//登陆用户负向行为统计
#define NEGATION_RECORD "nr"
//cookie用户负向行为统计
#define CO_NEGATION_RECORD "cnr"

#define USER_INSTATNT_BEHAVIOR "uib"

/**
 * @brief, 获取cookie用户行为
 * @in,  id baiduid签名
 * @out, buf_size buf最大值
 * @out, p 输出buf
 * @return, 数据长度，>=0为成功, -1失败为失败
 */
int mcc_get_co_behavior(uint id, Action_bean* p, int buf_size = MAX_ACTION_ITEM_NUM);

/**
 * @brief, 根据用户行为type获取cookie用户行为
 * @in,  id baiduid签名
  * @in, type 行为type类型
 * @out, buf_size buf最大值
 * @out, p 输出buf
 * @return, 数据长度，>=0为成功, -1失败为失败
 */
int mcc_get_co_user_real_behavior_by_type(uint id, Action_bean* p, enum DB_USER_BEHAVIOR_TYPE type, int buf_size = MAX_ACTION_NUM_PER_TYPE);


/**
 * @brief, 获了音乐盒cookie行为
 * @in,  id baiduid签名
 * @out, buf_size buf最大值
 * @out, p 输出buf
 * @return, 数据长度，>=0为成功, -1失败为失败
 */
int mcc_get_co_box_action(uint id, Action_bean* p, int buf_size = MAX_BOX_ACTION_NUM);

/**
 * @brief, 获了音乐盒cookie行为
 * @in,  id uid
 * @out, buf_size buf最大值
 * @out, p 输出buf
 * @return, 数据长度，>=0为成功, -1失败为失败
 */
int mcc_get_box_action(uint id, Action_bean* p, int buf_size = MAX_BOX_ACTION_NUM);

/**
 * @brief, 获取用户行为
 * @in,  id 用户名签名
 * @out, buf_size buf最大值
 * @out, p 输出buf
 * @return, 数据长度，>=0为成功, -1失败为失败
 */
int mcc_get_behavior(uint id, Action_bean* p, int buf_size = MAX_ACTION_ITEM_NUM);

/**
 * @brief, 根据用户行为type获取用户行为
 * @in,  id 用户名签名
  * @in, type 行为type类型
 * @out, buf_size buf最大值
 * @out, p 输出buf
 * @return, 数据长度，>=0为成功, -1失败为失败
 */
int mcc_get_user_real_behavior_by_type(uint id, Action_bean* p, enum DB_USER_BEHAVIOR_TYPE type, int buf_size = MAX_ACTION_NUM_PER_TYPE);


/**
 * @brief, 增加用户行为
 * @in,  id 用户名签名
 * @in, type 行为type类型
 * @out, ch_name
 * @return, 数据长度，>=0为成功, -1失败为失败
 */
int mcc_add_user_real_behavior(uint id, uint itemid, enum DIANTAI_USER_BEHAVIOR_TYPE type, const char* ch_name);


/**
 * @brief, 增加cookie用户行为
 * @in,  id baiduid
 * @in, baiduid_str
 * @in, type 行为type类型
 * @out, ch_name
 * @return, 数据长度，>=0为成功, -1失败为失败
 */
int mcc_add_co_user_real_behavior(uint id, const char* baiduid_str, uint itemid, enum DIANTAI_USER_BEHAVIOR_TYPE type, const char* ch_name);

/**
 * @brief, 获取试听历史
 * @in,  id 用户名签名
 * @out, buf_size buf最大值
 * @out, p 输出buf
 * @return, 数据长度，>=0为成功, -1失败为失败
 */
int mcc_get_listen_history(uint id, Item_bean* p, int buf_size = MAX_LISTENED_ITEM_NUM);

/**
 * @brief, 获取cookie试听历史
 * @in,  id baiduid签名
 * @out, buf_size buf最大值
 * @out, p 输出buf
 * @return, 数据长度，>=0为成功, -1失败为失败
 */
int mcc_get_co_listen_history(uint id, Item_bean* p, int buf_size = MAX_LISTENED_ITEM_NUM);

/**
 * @brief, 添加cookie试听历史
 * @in, id baiduid签名
 * @in, baiduid_str 原始baiduid字符串
 * @in, item_id 歌曲id
 * @in, ch_name 频道名
 * @return, 0成功, -1失败
 */
int mcc_add_co_listen_history(uint id, const char* baiduid_str, uint itemid, const char* ch_name);

/**
 * @brief, 添加试听历史
 * @in, id 用户名签名
 * @in, item_id 歌曲id
 * @in, ch_name 频道名
 * @return, 0成功, -1失败
 */
int mcc_add_listen_history(uint id, uint itemid, const char* ch_name);

/**
 * @brief, 获取用户的数据
 * @in, id,用户id
 * @in, usc_getter, 获取用户数据对象
 * @out, user_data, 用户数据
 * @return:函数执行情况返回值
 */
int mcc_get_user_data(UscGetter &usc_getter, uint id, r_userdata_t &user_data);


/**
 * @brief, 获取用户的数据
 * @in, id,用户id
 * @out, user_data, 用户数据
 * @return:函数执行情况返回值
 */
int mcc_get_co_user_data(uint id, r_userdata_t &user_data);

/**
 *@brief:获取即时行为的用户的数据
 *@in, id
 *@in, ch_name
 *@in, usc_getter, 用户中用数据对象
 *@param[out]:i_user_data, 用户数据
 *@return:函数执行情况返回值
 */
int mcc_get_instant_user_data(UscGetter &usc_getter, uint id, i_userdata_t &i_user_data, char * ch_name);

/**
 *@brief:获取即时行为的用户的数据
 *@in, id
 *@in, ch_name
 *@param[out]:i_user_data, 用户数据
 *@return:函数执行情况返回值
 */
int mcc_get_co_instant_user_data(uint id, i_userdata_t &i_user_data, char * ch_name);

/**
 * @brief, 获取用户喜好数据
 * @in, id, 用户id
 * @in, usc_getter, 获取用户数据对象
 * @in, type, 用户中心数据类型
 * @out, items, 用户中心数据结果
 * @out, len_items, 用户中心数据长度
 * @out, buf_size, buf长度
 * @return:函数执行情况返回值
 */
int mcc_get_usc_data(UscGetter &usc_getter, Item_bean *items, uint &len_items, enum DB_PREF_TYPE type, uint id, uint buf_size = MAX_PREF_ITEM_NUM);

/**
 * @brief, 获取cookie用户喜好数据
 * @in, id, 用户id
 * @in, type, 用户中心数据类型
 * @out, items, 用户中心数据结果
 * @out, len_items, 用户中心数据长度
 * @out, buf_size, buf长度
 * @return:函数执行情况返回值
 */
int mcc_get_co_pref_data(Item_bean *p, uint &len_items, enum DB_PREF_TYPE type, uint id, uint buf_size = MAX_PREF_ITEM_NUM);

/**
 *@brief:是否是私人频道新用户
 *@param[in]:uid
 *@param[in]:ch_name, 频道名
 *@param[out]:true 为成功，false为失败
 */
bool mcc_is_new_private_user(char *ch_name, uint uid);

/**
 *@brief：登陆用户建立即时用户模型
 *@param[in]:instant_model, 即时用户模型
 *@param[in]:i_user_data，即时喜好数据
 *@param[in]:ch_name, 频道名
 *@param[in]:uid
 *@param[out]:返回用户模型长度（1）
 */
int mcc_get_instant_user_model(instant_model_t& instant_model, i_userdata_t i_user_data, const char* ch_name, uint id); 

/**
 *@brief：cookie用户建立即时用户模型
 *@param[in]:instant_model, 即时用户模型
 *@param[in]:i_user_data，即时喜好数据
 *@param[in]:ch_name, 频道名
 *@param[in]:uid
 *@param[out]:返回用户模型长度（1）
 */
int mcc_get_co_instant_user_model(instant_model_t& instant_model, i_userdata_t i_user_data, const char* ch_name, uint id);

/**
 *@brief：更新用户即时兴趣模型
 *@param[in]:instant_model, 即时用户模型
 *@param[in]:ch_name, 频道名
 *@param[in]:id
 *@param[in]:type 歌曲处理类型（加心，60s等）
 *@param[in]:song_id 歌曲id
 *@param[out]:返回0 为成功，-1为失败
 */
int mcc_update_instant_user_model(instant_model_t& instant_model, const char* ch_name, uint id, int type, int song_id);

/**
 *@brief：更新cookie用户即时兴趣模型
 *@param[in]:instant_model, 即时用户模型
 *@param[in]:ch_name, 频道名
 *@param[in]:id
 *@param[in]:type 歌曲处理类型（加心，60s等）
 *@param[in]:song_id 歌曲id
 *@param[out]:返回0 为成功，-1为失败
 */
int mcc_update_co_instant_user_model(instant_model_t& instant_model, const char* ch_name, uint id, int type, int song_id);

/**
 *@brief:更新cookie用户电台喜好数据
 *@param[in]:id,百度id
 *@param[in]:itemid, 数据id
 *@param[in]:type, 喜好类型
 *@param[in]:del_flag,是否删除数据
 *@return:0 成功, -1失败
 */
int mcc_update_co_pref_data(uint id, const char* baiduid_str, uint itemid, enum DB_PREF_TYPE type, 
                    enum DB_DEL_TYPE del_flag, const char* ch_name);


/**
 *@brief:更新用户电台喜好数据
 *@param[in]:id,百度uid
 *@param[in]:type, 喜好类型
  *@param[in]:ch_name
 *@return:0 成功, -1失败
 */
int mcc_update_pref_data(uint id, enum DB_PREF_TYPE type, const char* ch_name);

/**
 *@brief:获得登陆用户的频道的推荐列表
 *@param[in]:id,可以是baidid和登录用户的passportid
 *@param[in]:ch_name,频道名字
 *@param[out]:p,歌曲的列表
 *@param[out]:len, 歌曲列表长度
 *@return:>=0 成功,返回数据长度 -1失败 
 */
int mcc_get_ch_list(uint id, const char* ch_name, Song_item_t* p, int len = MAX_USER_LIST_LEN);

/**
 *@brief:获得cookie的频道的推荐列表
 *@param[in]:id,可以是baidid和登录用户的passportid
 *@param[in]:ch_name,频道名字
 *@param[out]:p,歌曲的列表
 *@param[out]:len, 歌曲列表长度
 *@return:>=0 成功,返回数据长度 -1失败 
 */
int mcc_get_co_ch_list(uint id, const char* ch_name, Song_item_t* p, int len = MAX_USER_LIST_LEN);

/**
 *@brief:更新推荐列表
 *@param[in]:id,登录用户的passportid
 *@param[in]:ch_name,频道名字
 *@param[out]:p,歌曲的列表
 *@param[out]:len, 歌曲列表长度
 *@return: 0 成功, -1失败 
 */
int mcc_update_ch_list(uint id, const char* ch_name, Song_item_t* p, int len);

/**
 *@brief:更新推荐列表
 *@param[in]:id,baiduid
 *@param[in]:ch_name,频道名字
 *@param[out]:p,歌曲的列表
 *@param[out]:len, 歌曲列表长度
 *@return: 0 成功, -1失败 
 */
int mcc_update_co_ch_list(uint id, const char* ch_name, Song_item_t* p, int len);

/**
 *@brief:行为统计记录
 *@param[in]:uid,用户id
 *@param[in]:ch_name,频道标识
 *@param[in]:record,
 */
 int mcc_get_action_record(uint uid, const char* ch_name, action_record_t* record);


/**
 *@brief:行为统计记录
 *@param[in]:id,用户id
 *@param[in]:ch_name,频道标识
 *@param[in]:record,
 */
 int mcc_get_co_action_record(uint id, const char* ch_name, action_record_t* record);

 /**
 *@brief:更新行为统计记录
 *@param[in]:id,用户id
 *@param[in]:ch_name,频道标识
 *@param[in]:record,
 */
 int mcc_update_action_record(uint id, const char* ch_name, action_record_t* record);

 /**
 *@brief:更新行为统计记录
 *@param[in]:id,用户id
 *@param[in]:ch_name,频道标识
 *@param[in]:record,
 */
 int mcc_update_co_action_record(uint id, const char* ch_name, action_record_t* record);

 /**
 *@brief:是否是新用户
 *@param[in]:id, uid或者baiduid
 *@param[in]:type, 1 登录 2 未登录
 *@param[out]:is_new,是否是新用户 0 不是 1 是
 */
int mcc_is_new_user(uint id, int type, int &is_new);

/**
 * @brief, 从缓存中读取ral数据
 * @in, uid 用户id
 * @in, ch_name 频道名
 * @in, r_type 列表类型
 * @out, p 数据buf
 * @in, buf_size 缓存大小
 * @in, source 歌曲列表的来源
 * @retrun >=0 成功,返回数据长度 -1失败
 */
int mcc_get_ral_list(uint uid, char * ch_name, int r_type, Song_item_t * p, int source, int buf_size = CF_LIST_MAX_LEN);


/**
 * @brief, 从缓存中读取用户标签数据
 * @in, uid 用户id
 * @out, p 数据buf
 * @in, buf_size 缓存大小
 * @retrun >=0 成功,返回数据长度 -1失败
 */
int mcc_get_tag_list(uint uid, User_tag_t * p, int buf_size = USER_TAG_NUM); 


/**
 * 或许历史分页数据
 * uid 用户id(用户名的签名)
 * type 物体类型
 * p_beans 物体数据的buf,由外部初始化
 * bean_len 数据buf的长度
 *
 * return >=0 成功并返回获取数据的长度 -1失败
 *
*/
int mcc_get_history_page(unsigned int uid, Item_bean *p_benas, int start_no, int page_len, int src);

/**
 * 获取历史总数
 * retrun >=0 成功,返回数据长度 -1失败
 */
int mcc_get_listen_total_num(uint uid, int src);

/**
 * @Synopsis  mcc_get_user_instant_behavior 判断用庐的即时数据状态
 *
 * @Param id 用户id uid或baiduid
 * @Param song_id 歌曲id
 * @Param is_exist 是否存在,当结果返回
 *
 * @Returns 0为成功
 */
int mcc_get_user_instant_behavior(uint id, uint song_id, bool &is_exist);

/**
 * @Synopsis  mcc_update_user_instant_behavior 更新user_instant_behavior
 *
 * @Param id 用户id
 * @Param song_id 歌曲id
 * @Param type 行为类型
 *
 * @Returns   
 */
int mcc_update_user_instant_behavior(uint id, uint song_id, int type);

/**
 * @Synopsis  mcc_get_y_user_behavior 获取登陆用户音乐人行为
 *
 * @Param p 输出buf
 * @Param id 用户id
 * @Param buf_size buf长度
 *
 * @Returns <0失败，>=0成功，列表长度
 */
int mcc_get_y_user_behavior(Action_bean* p, uint id, int buf_size);

/**
 * @Synopsis  mcc_get_co_y_user_behavior 获取非登陆用户音乐人行为
 *
 * @Param p 输出buf
 * @Param id 用户id
 * @Param buf_size buf最大长度
 *
 * @Returns <0失败，>=0成功，列表长度
 */
int mcc_get_co_y_user_behavior(Action_bean* p, uint id, int buf_size);

/**
 * @Synopsis  mcc_get_y_user_data 获取登陆用户的百度音乐人行为数据
 *
 * @Param id 用户id
 * @Param user_data 用户数据
 *
 * @Returns   
 */
int mcc_get_y_user_data(uint id, y_user_data_t &user_data);

/**
 * @Synopsis  mcc_get_co_y_user_data 获取非登陆用户的百度音乐人行为数据
 *
 * @Param id 用户id 
 * @Param user_data 用户数据
 *
 * @Returns   
 */
int mcc_get_co_y_user_data(uint id, y_user_data_t &user_data);

/**
 * @Synopsis  mcc_add_y_user_behavior 增加登陆用户百度音乐人行为
 *
 * @Param id 用户id(uid/baiduid)
 * @Param itemid 歌曲或歌手id
 * @Param type 用户行为类型
 * @Param ch_name 频道名
 *
 * @Returns   
 */
int mcc_add_y_user_behavior(uint id, uint itemid, int type, const char* ch_name);

/**
 * @Synopsis  mcc_add_co_y_user_behavior 增加非登陆用户百度音乐人行为
 *
 * @Param id 用户id(uid/baiduid)
 * @Param baiduid_str 百度id字符串
 * @Param itemid 歌曲或歌曲id
 * @Param type 行为
 * @Param ch_name 频道名字
 *
 * @Returns   
 */
int mcc_add_co_y_user_behavior(uint id, const char *baiduid_str, uint itemid, int type, const char* ch_name);

/**
 * @Synopsis  mcc_get_redis_sign 获取redis中存的用户推荐列表当前sign
 *
 * @Param key_pre key前缀
 *
 * @Returns  
 */
int mcc_get_redis_sign(uint uid, const char* ch_name, const char *list_tag, const char *field, char *sign, uint &sign_len);

/**
 * @Synopsis  mcc_set_redis_sign redis中存用户推荐列表当前sign
 *
 * @Param uid
 * @Param ch_name
 * @Param sign  sign值
 *
 * @Returns  
 */
int mcc_update_redis_sign(uint uid, const char *ch_name, const char *list_tag, const char *field, const char *sign);

/**
 * @Synopsis  mcc_update_behavior_cnt 更新用户行为次数统计表
 *
 * @Param baiduid cookie id
 * @Param uid 用户id
 * @Param is_login 是否登陆
 * @Param soid 歌曲id
 * @Param baidu_str cookie字符串
 *
 * @Returns 0成功，其它失败
 */
int mcc_update_behavior_cnt(uint baiduid, uint uid, bool is_login, uint soid, const char* baidu_str);

#endif /* _MCCACHE_H_ */
