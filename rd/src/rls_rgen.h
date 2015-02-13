//============================================================================
// @author      : weijingqi (weijingqi@baidu.com)
// @file        : rls_rgen.h
// @date        : 15 May 2012,13:51:55
// @copyright   : 2011 Baidu.com, Inc. All Rights Reserved
// @encoding    : 
// @version     : 
// @brief       : 推荐列表生成 
//============================================================================

#ifndef _RLS_RGEN_H
#define _RLS_RGEN_H
#include "rls_def.h"
#include "rls.h"
#include "rls_rstrategy.h"
#include "rls_ral.h"
#include "macro.h"
#include "rls_struct.h"
#include "rls_dictseeker.h"
#include "rls_uscgetter.h"
#include "redis.h"

namespace rls{
    class RGen{
    public:
        /**
         *@brief:构造函数
         */
        RGen();

        /**
         *@brief:虚构函数
         */
        ~RGen();

        /**
         *@brief:生成简单的列表，[随机算法]
         *@param[in]:ch_name,频道名字
         *@param[out]:song_list,结果列表
         *@param[in]:max_len,列表的最大长度 
         *@param[in]:user_data,用户的数据
         *@param[out]:r_song_len,结果列表的长度
         *@return:函数执行状态返回值
         */
        int gen_simple_list(const char* ch_name,
                            Song_item_t* song_list, uint max_len, 
                            const r_userdata_t &user_data, uint &r_song_len);

        /**
         *@brief:生成推荐列表
         *@param[in]:ch_name,频道名字
         *@param[in]:baiduid, cookieid
         *@param[in]:uid,用户id
         *@param[in]:is_public,是否是公用频道
         *@param[in]:is_login,是否是登录用户
         *@param[out]:song_list,结果列表
         *@param[in]:max_len,列表的最大长度
         *@param[in]:user_data,用户行为数据
         *@param[out]:r_song_len,结果列表的长度
         *@param[in]:pool, 线程的内存池
         *@return:函数执行状态返回值
         */
        int gen_recommend_list(const char* ch_name, uint baiduid, uint uid, 
                               Song_item_t* song_list, uint max_len, 
                               uint &r_song_len, const r_userdata_t &user_data,
                               bool is_public, bool is_login, bsl::mempool &pool, int rf);

        /**
         *@brief:生成红心频道的播放列表
         *@param[in]:items,所有收藏的歌曲列表
         *@param[in]:len_items,收藏歌曲的长度
         *@param[out]:r_song_list, 结果歌曲列表
         *@param[out]:r_song_len,结果的长度
         *@return:函数执行的状态
         */
        int gen_lovesong_list(Item_bean* items, uint len_items, Song_item_t* r_song_list, 
                                uint max_len, uint &r_song_len);
        
        /**
         *@brief:生成标签频道列表
         *@param[out]:r_song_list,结果歌曲列表
         *@param[in]:max_len,最大的结果歌曲列表长度
         *@param[out]:r_song_len, 结果列表的长度
         *@param[in]:user_data, 用户的数据
         *@param[in]:tag_word,标签的名字
         *@param[in]:usc_getter,数据获取
         *@return:函数执行状态的结果
         */
        int gen_tag_list(Song_item_t* r_song_list, uint max_len, 
                         uint &r_song_len, const r_userdata_t &user_data,
                         char* tag_word, UscGetter *usc_getter);
        
        /**
        *@brief:生成多源列表融合的列表
        *@param[in]:ch_name,频道名字
        *@param[in]:baiduid, cookieid
        *@param[in]:uid,用户id
        *@param[in]:is_public,是否是公用频道
        *@param[in]:is_login,是否是登录用户
        *@param[out]:song_list,结果列表
        *@param[in]:max_len,列表的最大长度
        *@param[in]:user_data,用户行为数据
        *@param[out]:r_song_len,结果列表的长度
        *@param[in]:pool, 线程的内存池
        *@param[in&out]:instant, 是否是新用户(采用即时策略)
        *@return:函数执行状态返回值
        */
        int gen_fuse_list(char* ch_name, uint baiduid, uint uid, 
                               Song_item_t* song_list, uint max_len, 
                               uint &r_song_len, const r_userdata_t &user_data,
                               bool is_public, bool is_login, bsl::mempool &pool, int rf, bool &instant);


        /**
        *@brief:生成即时策略频道列表
        *@param[in]:ch_name,频道名字
        *@param[in]:baiduid, cookieid
        *@param[in]:uid,用户id
        *@param[in]:is_public,是否是公用频道
        *@param[in]:is_login,是否是登录用户
        *@param[out]:song_list,结果列表
        *@param[in]:max_len,列表的最大长度
        *@param[in]:user_data,用户行为数据
        *@param[out]:r_song_len,结果列表的长度
        *@param[in]:pool, 
        *@return:函数执行状态返回值
        */
        int gen_instant_list(const char* ch_name, uint baiduid, uint uid,
                                 Song_item_t* r_song_list, uint max_len,
                                 uint &r_song_len, const r_userdata_t &user_data, 
                                 bool is_login, int rf);
        /**
        *@brief:生成新用户私人频道列表
        *@param[in]:ch_name,频道名字
        *@param[in]:baiduid, cookieid
        *@param[in]:uid,用户id
        *@param[in]:is_public,是否是公用频道
        *@param[in]:is_login,是否是登录用户
        *@param[out]:song_list,结果列表
        *@param[in]:max_len,列表的最大长度
        *@param[in]:user_data,用户行为数据
        *@param[out]:r_song_len,结果列表的长度
        *@param[in]:pool, 
        *@return:函数执行状态返回值
        */
        int gen_newuser_private_list(const char* ch_name, uint baiduid, uint uid,
                                 Song_item_t* r_song_list, uint max_len,
                                 uint &r_song_len, const r_userdata_t &user_data, 
                                 bool is_login, int rf);


        /**
        *@brief:生成多源列表融合的列表
        *@param[in]:ch_name,频道名字
        *@param[out]:song_list,结果列表
        *@param[out]:r_song_len,结果列表的长度
        *@param[in]:filter_dict, 过滤词典
        *@return:函数执行状态返回值
        */
        int _spread_sond(const char *ch_name, Song_item_t* song_list, 
                           uint &song_list_len, uint umax, const sodict_build_t* filter_dict);

        /**
        *@brief:插入音乐人推广歌曲
        *@param[in]:ch_name,频道名字
        *@param[out]:song_list,结果列表
        *@param[out]:song_list_len,结果列表的长度
        *@param[in]:filter_dict, 过滤词典
        *@param[in]:max_len, 结果列表最大长度
        *@return:函数执行状态返回值
        */
        int _insert_yyr_song(const char *ch_name, Song_item_t* song_list,
                           uint &song_list_len, uint max_len,
                           const sodict_build_t* filter_dict);

        /**
         * @Synopsis  gen_y_list 生成百度音乐人歌曲列表
         *
         * @Param ch_name 频道名字
         * @Param baiduid 百度id
         * @Param uid 用户id
         * @Param r_song_list 结果列表
         * @Param max_len 列表最大长度
         * @Param r_song_len 结果列表长度
         * @Param user_data 用户数据
         * @Param is_login 是否登陆
         * @Param pool 内存
         * @Param rf
         *
         * @Returns 0正确，其它失败
         */
        int gen_y_list(const char* ch_name, uint baiduid, uint uid,
                                 Song_item_t* r_song_list, uint max_len, uint &r_song_len, 
                                 const y_user_data_t &user_data,
                                 bool is_login, bsl::mempool &pool, int rf);

    private:
        /*推荐策略*/
        RStrategy* _rstrategy;
        /*算法*/
        RAl* _ral;

        /*数据字典查询*/
        DictSeeker* _dict_seeker;
    };
}
#endif /* _RLS_RGEN_H */

