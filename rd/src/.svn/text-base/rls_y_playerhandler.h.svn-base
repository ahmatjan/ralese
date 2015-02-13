/**
 * @file rls_y_playerhandler.h
 * @Synopsis  处理百度音乐人播放请求
 * @author wensaiping, wensaiping@baidu.com
 * @version 1.0.0
 * @date 2013-11-14
 */

#ifndef _RLS_Y_PLAYERHANDLER_H
#define _RLS_Y_PLAYERHANDLER_H
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

namespace rls{
    class YPlayerHandler{

    public:

        /**
         * @Synopsis  YPlayerHandler 构造函数
         */
        YPlayerHandler();

        /**
         * @Synopsis  ~YPlayerHandler 析构函数
         */
        ~YPlayerHandler();

        /**
         * @Synopsis  handle_playlist_cmd 处理播放列表
         *
         * @Param u_buf 用户请求缓存
         *
         * @Returns 0成功，其它返回相应执行状态
         */
        int handle_playlist_cmd(const User_worker_buf& u_buf);
        
        
        /**
         * @Synopsis  handle_playaction_cmd 处理播放
         *
         * @Param u_buf 用户请求缓存
         *
         * @Returns 0成功 其它返回相应执行状态
         */
        int handle_playaction_cmd(const User_worker_buf& u_buf);

    private:
        /**
         * @Synopsis  _pack_song_arr 将歌曲列表结果打包
         *
         * @Param song_list 歌曲列表 
         * @Param song_len 歌曲列表长度
         * @Param mcpack_arr mc数组
         *
         * @Returns 0成功 其它失败
         */
        int _pack_song_arr(const Song_item_t* song_list, int song_len, 
                           mc_pack_t* mcpack_arr);

        /**
         * @Synopsis  _is_bad_need_regen 负向反馈计算，是否需要重新生成列表
         *
         * @Param uid 用户id
         * @Param is_login 是否登陆
         * @Param ch_name 频道名
         *
         * @Returns true需要重建，false不需要重建
         */
        bool _is_bad_need_regen(uint uid, bool is_login, char * ch_name = "");

        /**
         * @Synopsis  _handle_user_behavior 处理百度音乐人实时行为
         *
         * @Param baiduid 百度id
         * @Param baiduid_str 百度id字符串
         * @Param uid 用户id
         * @Param item_id 歌曲或歌手id
         * @Param type 行为类型
         * @Param ch_name 频道名
         * @Param need_update 是否需要更新
         * @Param is_login 是否登陆
         * @Param need_real 是否需要实时处理, 非实时处理频道
         * @Param pool 内存管理 
         * @Param rf rf值
         *
         * @Returns 0成功，其它失败
         */
        int _handle_user_behavior(uint baiduid, const char* baiduid_str, uint uid, uint item_id, 
                                        int type, char* ch_name, bool &need_update,
                                        bool is_login, bool need_real, bsl::mempool &pool, int rf);

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


#endif /* _RLS_Y_PLAYERHANDLER_H */

