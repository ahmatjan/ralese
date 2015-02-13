//============================================================================
// @author      : weijingqi (weijingqi@baidu.com)
// @file        : rls_queryhandler.h
// @date        : 13 May 2012,11:17:57
// @copyright   : 2011 Baidu.com, Inc. All Rights Reserved
// @encoding    : 
// @version     : 
// @brief       : 处理查询类的请求 
//============================================================================

#ifndef _RLS_QUERYHANDLER_H
#define _RLS_QUERYHANDLER_H
#include "rls_def.h"
#include "rls_dictseeker.h"
#include "idl/rls2.idl.h"
#include "common.h"
#include "rls.h"
#include "macro.h"
#include "rls_struct.h"
#include "rls_uscgetter.h"
namespace rls{
    class QueryHandler{
    public:
        /**
         *@brief:构造函数
         */
        QueryHandler();
        /**
         *@brief:虚构函数
         */
        ~QueryHandler();
        /**
         *@brief:处理频道列表查询指令
         *@param[in]:u_buf,用户指令缓存
         *@return:函数执行状态返回值
         */
        int handle_channellist_cmd(const User_worker_buf& u_buf);
        
        /**
         *@brief:处理冷启动歌手列表指令
         *@param[in]:u_buf,用户指令缓存
         *@return:函数执行状态返回值         
         */
        int handle_cssingerlist_cmd(const User_worker_buf& u_buf);

        /**
         *@brief:处理新用户判断指令
         *@param[in]:u_buf,用户指令缓存
         *@return:函数执行状态返回值         
         */
        int handle_newuser_cmd(const User_worker_buf& u_buf);

        /**
         *@brief:处理标签查询指令
         *@param[in]:u_buf,用户指令缓存
         *@return:函数执行状态返回值
         */
        int handle_utag_cmd(const User_worker_buf& u_buf);
        

        int handle_tic_cmd(const User_worker_buf& u_buf);
    private:
        /**
         *@brief:将频道信息打包
         *@param[in]:ch_info_list,大频道列表
         *@param[in]:len, 频道列表的长度
         *@param[in]:cate_name,频道分类的名字
         *@param[out]:mcpack_arr,频道pack
         *@return:函数执行结果状态
         */
        int _pack_ch_arr(const ch_info_t* ch_info_list, 
                         int len, mc_pack_t* mcpack_arr, const char* cate_name);

        int _pack_personal_ch_arr(const ch_info_t* ch_info_list, int len,
            mc_pack_t* mcpack_arr, const User_worker_buf& u_buf);

        /*字典数据查询*/
        DictSeeker* _dict_seeker;

        /*用户中心数据获取*/
        UscGetter* _usc_getter;
    };
}


#endif /* _RLS_QUERYHANDLER_H */

