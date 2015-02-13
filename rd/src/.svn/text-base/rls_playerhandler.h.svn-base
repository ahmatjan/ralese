//============================================================================
// @author      : weijingqi (weijingqi@baidu.com)
// @file        : rls_playerhandler.h
// @date        : 13 May 2012,11:27:53
// @copyright   : 2011 Baidu.com, Inc. All Rights Reserved
// @encoding    : 
// @version     : 
// @brief       : 处理播放请求 
//============================================================================

#ifndef _RLS_PLAYERHANDLER_H
#define _RLS_PLAYERHANDLER_H
#include "rls_def.h"
#include "idl/rls2.idl.h"
#include "common.h"
#include "rls.h"
#include "macro.h"
#include "rls_struct.h"
#include "rls_dictseeker.h"
#include "rls_rgen.h"
#include "rls_rstrategy.h"
#include "rls_ral.h"
#include "rls_uscgetter.h"
#include "mcCache.h"
#include "redis.h"

namespace rls{
    class PlayerHandler{
    public:
        /**
         *@brief:构造函数
         */
        PlayerHandler();
        /**
         *@brief:虚构函数
         */
        ~PlayerHandler();
        /**
         *@brief:处理获取播放列表
         *@param[in]:u_buf, 用户请求缓存
         */
        int handle_playlist_cmd(const User_worker_buf& u_buf);
        
        /**
         *@brief:处理播放行为的请求
         *@param[in]:u_buf,用户缓存
         *@return:函数执行状态返回值
         */
        int handle_playaction_cmd(const User_worker_buf& u_buf);

        /**
         *@brief:处理冷启动请求
         *@param[in]:u_buf,用户缓存
         *@return:函数执行状态返回值
         */
        int handle_csreq_cmd(const User_worker_buf& u_buf);

    private:
        /**
         *@brief:将歌曲列表结果打包
         *@param[in]:song_list,歌曲列表
         *@param[in]:song_len,歌曲列表长度
         *@param[in]:mcpack_arr,mc数组
         *@param[in]:songlove_ids,喜欢的歌曲的id
         *@return:函数执行情况返回值
         */
        int _pack_song_arr(const Song_item_t* song_list, int song_len, 
                           mc_pack_t* mcpack_arr, const bsl::hashmap<uint, uint> songlove_ids);

        /**
         *@brief:从redis中获取sign值，判断是否和memcached中存的上一次的sign值是否相同
         *@param[in]:uid
         *@param[in]:ch_name 
         *@return:true,需要重新生成，false不需要重新生成
         */
        bool _is_redis_rlist_sign_changed(uint uid, const char *ch_name, const char *list_tag, const char *field);

        /**
         *@brief:负向反馈是否需要重新生成列表的机制
         *@param[in]:uid,用户id
         *@param[in]:is_login,是否登陆
         *@param[in]:ch_name
         *@return:true,需要重新生成，false不需要重新生成
         */
        bool _is_bad_need_regen(uint uid, bool is_login, char * ch_name = "");


        /**
         *@brief:处理上一首
         *@param[in]:baiduid,百度id
         *@param[in]:baiduid_str,百度id字符串
         *@param[in]:uid,用户id
         *@param[in]:item_id
         *@param[in]:ch_name,频道名字
         *@param[in]:need_update,是否需要更新前端播放列表
         *@param[in]:is_public,是否是公用频道
         *@param[in]:is_login,是否是登录用户
         *@param[in]:need_real,是否需要实时处理
         *@param[in]:pool,线程内存池
         *@param[in]:rf,来源标识
         *@return:函数执行状态返回值
         */
        int _handle_pre_song(uint baiduid, const char* baiduid_str, uint uid, uint item_id, 
                             char* ch_name, bool &need_update, 
                             bool is_public, bool is_login, 
                             bool need_real, bsl::mempool &pool, int rf);

        /**
         *@brief:处理下一首
         *@param[in]:baiduid,百度id
         *@param[in]:baiduid_str,百度id字符串
         *@param[in]:uid,用户id
         *@param[in]:item_id
         *@param[in]:ch_name,频道名字
         *@param[in]:need_update,是否需要更新前端播放列表
         *@param[in]:is_public,是否是公用频道
         *@param[in]:is_login,是否是登录用户
         *@param[in]:need_real,是否需要实时处理
         *@param[in]:pool,线程内存池
         *@param[in]:rf,来源标识
         *[in]:instant,是否是即时频道
         *@return:函数执行状态返回值
         */
        int _handle_next_song(uint baiduid, const char* baiduid_str, uint uid, uint item_id, 
                             char* ch_name, bool &need_update, 
                             bool is_public, bool is_login, 
                              bool need_real, bsl::mempool &pool,
                              int rf); 


        /**
         *@brief:处理播放完事
         *@param[in]:baiduid,百度id
         *@param[in]:baiduid_str,百度id字符串
         *@param[in]:uid,用户id
         *@param[in]:item_id
         *@param[in]:ch_name,频道名字
         *@param[in]:need_update,是否需要更新前端播放列表
         *@param[in]:is_public,是否是公用频道
         *@param[in]:is_login,是否是登录用户
         *@param[in]:need_real,是否需要实时处理
         *@param[in]:pool,线程内存池
         *@param[in]:rf,来源标识
         *@return:函数执行状态返回值
         */
        int _handle_complete_song(uint baiduid, const char* baiduid_str, uint uid, uint item_id, 
                                  char* ch_name, bool &need_update, 
                                  bool is_public, bool is_login, 
                                  bool need_real, bsl::mempool &pool, 
                                  int rf); 

        /**
         *@brief:处理加心歌曲
         *@param[in]:baiduid,百度id
         *@param[in]:baiduid_str,百度id字符串
         *@param[in]:uid,用户id
         *@param[in]:item_id
         *@param[in]:ch_name,频道名字
         *@param[in]:need_update,是否需要更新前端播放列表
         *@param[in]:is_public,是否是公用频道
         *@param[in]:is_login,是否是登录用户
         *@param[in]:need_real,是否需要实时处理
         *@param[in]:pool,线程内存池
         *@param[in]:user_data,用户行为数据
         *@param[in]:rf,来源标识
         *@return:函数执行状态返回值
         */
        int _handle_love_song(uint baiduid, const char* baiduid_str, uint uid, uint item_id, 
                              char* ch_name, bool &need_update, 
                              bool is_public, bool is_login, 
                              bool need_real, bsl::mempool &pool, 
                              const r_userdata_t &user_data, int rf); 

        /**
         *@brief:处理垃圾桶歌曲
         *@param[in]:baiduid,百度id
         *@param[in]:baiduid_str,百度id字符串
         *@param[in]:uid,用户id
         *@param[in]:item_id
         *@param[in]:ch_name,频道名字
         *@param[in]:need_update,是否需要更新前端播放列表
         *@param[in]:is_public,是否是公用频道
         *@param[in]:is_login,是否是登录用户
         *@param[in]:need_real,是否需要实时处理
         *@param[in]:pool,线程内存池
         *@param[in]:rf,来源标识
         *@return:函数执行状态返回值
         */
        int _handle_hate_song(uint baiduid, const char* baiduid_str, uint uid, uint item_id, 
                              char* ch_name, bool &need_update, 
                              bool is_public, bool is_login, 
                              bool need_real, bsl::mempool &pool,
                              int rf); 


        /**
         *@brief:处理取消喜欢
         *@param[in]:baiduid,百度id
         *@param[in]:baiduid_str,百度id字符串
         *@param[in]:uid,用户id
         *@param[in]:item_id
         *@param[in]:ch_name,频道名字
         *@param[in]:need_update,是否需要更新前端播放列表
         *@param[in]:is_public,是否是公用频道
         *@param[in]:is_login,是否是登录用户
         *@param[in]:need_real,是否需要实时处理
         *@param[in]:pool,线程内存池
         *@param[in]:rf,来源标识
         *@return:函数执行状态返回值
         */
        int _handle_cancel(uint baiduid, const char* baiduid_str, uint uid, uint item_id, 
                           char* ch_name, bool &need_update, 
                           bool is_public, bool is_login, 
                           bool need_real, bsl::mempool &pool,
                           int rf); 


        /**
         *@brief:刷新当前即时兴趣列表
         *@param[in]:baiduid,百度id
         *@param[in]:uid,用户id
         *@param[in]:ch_name,频道名字
         *@param[in]:is_login,是否是登录用户
         *@param[in]:rf,来源标识
         *@return:函数执行状态返回值
         */
        int _reflash_instant_list(uint baiduid, uint uid, 
                                         char* ch_name, bool is_login, int rf, instant_model_t instant_model);

        /**
         * 每一条播放行为往bigpipe里打日志
         *
         */
        int PlayerHandler::bigpipe_send_action_message(uint uid, uint song_id, int type, const char* ch_name);

        /**
         * 将BPR行为发到bigpipe
         *
         */
        int PlayerHandler::bigpipe_send_bpr_message(uint uid, const char *pack_item_ids, int type, const char* ch_name);

        /*列表生成器*/
        RGen* _rgen;
        
        /*推荐策略*/
        RStrategy* _rstrategy;

        /*字典数据查询*/
        DictSeeker* _dict_seeker;

        /*算法*/
        RAl* _ral;

        /*从用户中心获取数据*/
        UscGetter* _usc_getter;
    };
}


#endif /* _RLS_PLAYERHANDLER_H */

