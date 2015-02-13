//============================================================================
// @author      : weijingqi (weijingqi@baidu.com)
// @file        : rls_rstrategy.h
// @date        : 13 May 2012,11:44:14
// @copyright   : 2011 Baidu.com, Inc. All Rights Reserved
// @encoding    : 
// @version     : 
// @brief       : 推荐策略 
//============================================================================

#ifndef _RLS_RSTRATEGY_H
#define _RLS_RSTRATEGY_H
#include "rls_def.h"
#include "rls.h"
#include "macro.h"
#include "rls_struct.h"
#include "rls_dictseeker.h"
#include "rls_ral.h"
#include "dao.h"

namespace rls{
    class RStrategy{
    public:
        /**
         *@brief:构造函数
         */
        RStrategy();
        
        /**
         *@brief: 虚构函数
         */
        ~RStrategy();

        
        /**
         *@brief:对列表进行重排序,保证M首歌区中,不出现N个相同歌手的歌.
         *@param[in]:p_userlist,输入的歌曲列表
         *@param[in]:userlist_len,用户歌曲列表的长度
         *@param[in]:M,区间长度
         *@param[in]:N,最多的重复个数
         *@param[in]:need_sort, 是否需要先排序
         *@return:FAIL SUCCESS
         */
        int arrange_user_list(Song_item_t *p_userlist, int userlist_len,int M, int N, bool need_sort = true);

        /**
         *@brief:对列表进行重排序,保证M首歌区中,不出现N个相同歌手的歌.
         *@param[in]:p_userlist,输入的歌曲列表   
         *@param[in]:userlist_len,用户歌曲列表的长度
         *@param[in]:hate_singer_len,过滤垃圾桶歌曲数
         *@param[in]:pass_singer_len,过滤跳过数
         *@param[in]:filter_len, 过滤长度
         *@param[in]:user_data, 用户数据
         *@return:FAIL SUCCESS
         */
        int filter_user_list(Song_item_t *p_userlist, unsigned int& userlist_len, 
                int hate_singer_len, int pass_singer_len, 
                int filter_len, const r_userdata_t &user_data);

        /**
         *@brief:重定义歌曲列表权值
         *@param[in]:p_userlist,输入的歌曲列表
         *@param[in]:userlist_len,用户歌曲列表的长度
         *@return:FAIL SUCCESS
         */
        int define_list_weight(Song_item_t *p_userlist, int userlist_len);

        /**
         *@brief:歌曲列表平滑
         *@param[in]:p_userlist,输入的歌曲列表
         *@param[in]:userlist_len,用户歌曲列表的长度
         *@param[in]:M,平滑区间
         *@param[in]:L,平滑剔除长度
         *@param[in]:N,平滑次数 
         *@return:FAIL SUCCESS
         */
        int smooth_list(Song_item_t *p_userlist, int userlist_len, int M, int L, int N);


        /**
         * @Synopsis  tire_list 疲劳度处理列表
         *
         * @Param p_userlist 输入 歌曲列表
         * @Param userlist_len 列表长度
         * @Param uid 用户id
         * @Param baiduid cookie id
         * @Param is_login 是否登陆
         *
         * @Returns   
         */
        int tire_list(Song_item_t *p_userlist, int userlist_len, uint uid, uint baiduid, bool is_login);
    private:
        /*字典数据查询*/
        DictSeeker* _dict_seeker;
        /*算法*/
        RAl* _ral;
    };
}

#endif /* _RLS_RSTRATEGY_H */

