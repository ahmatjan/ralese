/**
 * =====================================================================================
 *
 *	Filename:  dao.h
 *
 *	Description:  header file for dao.cpp
 *
 *	Version:  1.0
 *  Created: 2011-6-6
 *	Revision:  none
 *	Compiler:  gcc
 *
 *	Author:  zhangjunying, zhangjunying@baidu.com
 *	Company:  baidu.com Inc.
 *
 * =====================================================================================
 */

#ifndef _DAO_H_
#define _DAO_H_

#include<time.h>
#include "bsl/pool.h"
#include "myclient_include.h"
#include "ub.h"
#include "macro.h"
#include "rls.h"

#define SECONDS_OF_DAY 86400
//ddbs重试次数
#define TRY_TIME 3

/**< item bean from db */
typedef struct _item_bean_t
{
	unsigned long itemid;/**< item id */
    char ch_name[MAX_CHNAME_LEN];
    int pref_type; //喜好类型
	time_t date;/**< date time in unix */
} Item_bean;

/**< listen num from db */
typedef struct _listen_num_t
{
	unsigned int total;/**< total num*/
} Listen_num;

/**< pref num from db */
typedef struct _pref_num_t
{
    unsigned int total;/**< total num*/
} Pref_num;

/**
 * 用户行为数据结构体
 */
typedef struct _action_bean_t
{
	unsigned int itemid;/**< 歌曲id*/
	int type;/**< 类型*/
    char ch_name[MAX_CHNAME_LEN];
	time_t date; /**< 行为发生的日期*/
} Action_bean;


/**
 * @brief, 查询用户行为数据
 * @in, uid 用户id(用户名的签名)
 * @in type 查找用户行为type值
 * @in, bean_len 数据buf的最大长度
 * @out, p_beans 数据的buf,由外部初始化
 * @return, >=0成功并返回获取数据的长度 -1失败
 *
 */
int db_get_user_real_behavior(unsigned int uid, Action_bean*p_benas, enum DB_USER_BEHAVIOR_TYPE type, int bean_len = MAX_ACTION_NUM_PER_TYPE);

/**
 * @brief, 查询用户行为数据
 * @in, baiduid baiduid签名
 * @in type 查找用户行为type值
 * @in, bean_len 数据buf的最大长度
 * @out, p_beans 数据的buf,由外部初始化
 * @return, >=0成功并返回获取数据的长度 -1失败
 *
 */
int db_get_co_user_real_behavior(unsigned int baiduid, Action_bean*p_benas, enum DB_USER_BEHAVIOR_TYPE type, int bean_len = MAX_ACTION_NUM_PER_TYPE);


/**
 * 查询用户收听历史数据
 * uid 用户id(用户名的签名)
 * p_beans 数据的buf,由外部初始化
 * bean_len 数据buf的长度
 * t_date 起始时间,默认为0，查取所有时间的数据
 * return >=0 成功并返回获取数据的长度 -1失败
 *
 */
int db_get_listen_history(unsigned int uid, Item_bean *p_benas, int bean_len = MAX_LISTENED_ITEM_NUM);

/**
 * 查询用户收听总数
 * uid 用户id(用户名的签名)
 *
 * return >=0 成功并返回获取数据的长度 -1失败
 *
 */
int db_get_listen_history_num(unsigned int uid, int src);


/**
 *获取试听历史分页数据
*/
int db_get_history_page(unsigned int uid, Item_bean *p_beans, 
                          int start_no, int page_len, int src);

/**
 * 插入用户收听数据
 * uid 用户id(用户名的签名)
 * soid 歌曲id
 *
 * return 0 成功  -1失败
 *
 */
int db_add_listen_history(unsigned int uid, uint soid, const char* ch_name = "");

/**
 * 插入用户行为数据
 * uid 用户id(用户名的签名)
 * soid 歌曲id
 * type行为类型
 * return 0 成功  -1失败
 */
int db_add_user_real_behavior(unsigned int uid, uint soid,
                          enum DB_USER_BEHAVIOR_TYPE type, const char* ch_name = "");

/**
 *@brief:获取 cookie试听数据
 *@param[in]:baiduid, 百度 id
 *@param[out]:p ,行为数据
 *@param[in]:buf_size,最大个数
 * retrun >=0 成功,返回数据长度 -1失败
 */
int db_get_co_listen_history(uint baiduid, Item_bean* p, int buf_size = MAX_LISTENED_ITEM_NUM);


/**
 *@brief:获取 cookie喜好数据
 *@param[in]:baiduid, 百度 id
 *@param[out]:p ,行为数据
 *@param[in]:type,喜好类型
 *@param[in]:buf_size, 最大个数
 * m_date 起始时间,默认为0，查取所有时间的数据
 * retrun >=0 成功,返回数据长度 -1失败
 */
int db_get_co_pref_data(uint baiduid, enum DB_PREF_TYPE type,
		Item_bean* p, int buf_size = MAX_PREF_ITEM_NUM);


/**
 *@brief:添加电台试听历史
 *@param[in]:baiduid,百度id
 *@param[in]:baiduid_str,百度id字符串
 *@param[in]:itemid, 数据id
 *@param[in]:ch_name,频道名字
 *@return:0 成功, -1失败
 */
int db_add_co_listen_history(uint baiduid, const char* baiduid_str, uint itemid, const char* ch_name);

/**
 *@brief:添加电台喜好数据
 *@param[in]:baiduid,百度id
 *@param[in]:baiduid_str,百度id字符串
 *@param[in]:itemid, 数据id
 *@param[in]:type, 喜好类型
 *@param[in]:ch_name,频道
 *@param[in]:del_flag,是否删除数据
 *@return:0 成功, -1失败
 */
int db_update_co_pref(uint baiduid, const char* baiduid_str, uint itemid,
                         enum DB_PREF_TYPE type, enum DB_DEL_TYPE del_flag, const char* ch_name);

/**
 *@brief:添加用户行为数据
 *@param[in]:baiduid,百度id
 *@param[in]:baiduid_str,百度id字符串
 *@param[in]:itemid, 数据id
 *@param[in]:type, 行为类型
 *@param[in]:ch_name,频道名字
 *@return:0 成功, -1失败
 */
int db_add_co_user_real_behavior(uint baiduid, const char* baiduid_str, uint itemid, 
 
                           enum DB_USER_BEHAVIOR_TYPE type, const char* ch_name);
/**
 *@brief:判断是否有试听历史
 *@param[in]:uid,用户id
 *@param[out]:has_history,true有历史 false没有试听历史
 */
int db_has_listen_history(uint uid, bool &has_histroy);


/**
 *@brief:判断是否有试听历史
 *@param[in]:baiduid,baiduid
 *@param[out]:has_history,true有历史 false没有试听历史
 */
int db_has_co_listen_history(uint baiduid, bool &has_histroy);

/**
 * @brief:查询ral列表数据
 * @param[in]uid 用户id(用户名的签名)
 * @param[in]ch_name 频道名
 * @param[in]r_type 列表类型
 * @param[in]cf_list 数据的buf,由外部初始化
 * @param[in]max_len 数据buf的长度
 * @param[in]source 列表来源
 * return >=0 成功并返回获取数据的长度 -1失败
 *
 */
int db_get_ral_list(unsigned int uid, const char *ch_name, uint r_type, Song_item_t* cf_list, int source, uint max_len);

/**
 * 查询用户标签数据
 * uid 用户id(用户名的签名)
 * user_tag 数据的buf,由外部初始化
 * max 数据buf的长度
 *
 * return >=0 成功并返回获取数据的长度 -1失败
 */
int db_get_user_tags(unsigned int uid, User_tag_t* user_tag, uint max_len);

/**
 * 查询音乐盒用户行为数据
 * uid 用户id(用户名的签名)
 * p_beans 数据的buf,由外部初始化
 * bean_len 数据buf的长度
 * return >=0 成功并返回获取数据的长度 -1失败
 *
 */
int db_get_user_behavior(unsigned int uid, Action_bean* p_benas, int bean_len = MAX_BOX_ACTION_NUM);


/**
 * 查询音乐盒cookie用户行为数据
 * uid 用户id(用户名的签名)
 * p_beans 数据的buf,由外部初始化
 * bean_len 数据buf的长度
 * return >=0 成功并返回获取数据的长度 -1失败
 *
 */
int db_get_co_user_behavior(unsigned int uid, Action_bean* p_benas, int bean_len = MAX_BOX_ACTION_NUM);

/**
 * @Synopsis  db_get_y_user_behavior 获取登陆用户百度音乐人行为
 *
 * @Param uid 用户id
 * @Param p_benas 缓存数据
 * @Param bean_len 请求数据长度
 *
 * @Returns >=0 成功并返回获取数据的长度 -1失败
 */
int db_get_y_user_behavior(unsigned int uid, Action_bean *p_benas, int bean_len);

/**
 * @Synopsis  db_get_co_y_user_behavior 获取非登陆用户百度音乐人行为
 *
 * @Param baiduid 百度id
 * @Param p_benas 缓存数据
 * @Param bean_len 请求数据长度
 *
 * @Returns  >=0 成功并返回获取数据的长度 -1失败
 */
int db_get_co_y_user_behavior(unsigned int baiduid, Action_bean *p_benas, int bean_len);

/**
 * @Synopsis  db_add_co_y_user_behavior 添加非登陆用户的百度音乐人行为
 *
 * @Param baiduid 百度id
 * @Param baiduid_str 百度id字符串
 * @Param soid 歌曲或歌手id
 * @Param type 行为类型
 * @Param ch_name 频道名
 *
 * @Returns   
 */
int db_add_co_y_user_behavior(unsigned int baiduid, const char* baiduid_str, uint soid,
    int type, const char* ch_name);

/**
 * @Synopsis  db_add_y_user_behavior 添加登陆用户百度音乐人行为
 *
 * @Param uid 用户id
 * @Param soid 歌曲或歌手id
 * @Param type 行为类型
 * @Param ch_name 频道名
 *
 * @Returns   
 */
int db_add_y_user_behavior(unsigned int uid, uint soid,
    int type, const char* ch_name);


/**
 * @Synopsis  db_update_user_behavior_cnt 更新登陆用户行为统计
 *
 * @Param uid 用户id
 * @Param soid 歌曲id
 *
 * @Returns <0失败, >=0成功
 */
int db_update_user_behavior_cnt(uint uid, uint soid);


/**
 * @Synopsis  db_update_co_user_behavior_cnt 更新非登陆用户行为统计
 *
 * @Param baiduid cooikie id
 * @Param soid 歌曲id
 * @Param baidu_str cookie字符串
 *
 * @Returns   
 */
int db_update_co_user_behavior_cnt(uint baiduid, uint soid, const char* baidu_str);


/**
 * @Synopsis  db_get_user_behavior_cnt 查找登陆用户的歌曲行为统计
 *
 * @Param uid 用户id
 * @Param song_set 歌曲集
 * @Param user_cnt_map 用户数据字典
 *
 * @Returns <0失败, >=0 成功
 */
int db_get_user_behavior_cnt(uint uid, const char* song_set, std::map<int, user_cnt_t> &user_cnt_map);

/**
 * @Synopsis  db_get_co_user_behavior_cnt 查找非登陆用户的歌曲行为统计
 *
 * @Param baiduid cookie id
 * @Param song_set 歌曲集
 * @Param user_cnt_map 用户数据字典
 *
 * @Returns <0失败, >=0 成功
 */
int db_get_co_user_behavior_cnt(uint baiduid, const char* song_set, std::map<int, user_cnt_t> &user_cnt_map);

#endif /* _DAO_H_ */
