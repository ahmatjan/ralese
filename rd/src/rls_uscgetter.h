//============================================================================
// @author      : weijingqi (weijingqi@baidu.com)
// @file        : rls_uscgetter.h
// @date        : 25 May 2012,14:19:53
// @copyright   : 2011 Baidu.com, Inc. All Rights Reserved
// @encoding    : 
// @version     : 
// @brief       : 数据中心用户数据获取
//============================================================================

#ifndef _RLS_USCGETTER_H
#define _RLS_USCGETTER_H
#include "rls_struct.h"
#include "rls.h"
#include "rls_def.h"
#include "dao.h"
#include "macro.h"

namespace rls{
    class UscGetter{
    public:
        /**
         *@brief:构造函数
         */
        UscGetter();
        /**
         *@brief:虚构函数
         */
        ~UscGetter();
        
        /**
         *@brief:获得喜好数据
         *@param[out]:items, 返回的item列表
         *@param[out]:len_items, 返回的item的个数
         *@param[out]:total, 总数
         *@param[in]:max_len_items, 最大的列表长度
         *@param[in]:need_len,需要的列表的长度
         *@param[in]:start,开始的item
         *@param[in]:uid,用户id
         *@param[in]:need_mtime, true,需要时间戳，false,不需要时间戳
         *@return:函数执行状态返回值
         */
        int get_prefdata(Item_bean* items, uint &len_items,
                         uint &total, uint max_len_items, 
                         uint need_len, const uint start, 
                         uint uid, bool need_mtime,
                         enum DB_PREF_TYPE type);
        
        /**
         *@brief:获得所有喜好数据的统计
         *param[out]:len_songlove,喜好歌曲数
         *param[out]:len_songhate,讨厌歌曲数
         *param[out]:len_singerlove,喜好歌手数
         *param[out]:len_singerhate,讨厌歌手数
         *param[in]:uid,用户id
         */
        int get_allprefcnt(uint &len_songlove, uint &len_songhate,
                                      uint &len_singerlove, uint &len_singerhate,
                                      uint uid);

        /**
         *@brief:获取标签下的歌曲数据
         *@param[out]:tagsong,标签下歌曲数据
         *@param[out]:len_tagsong,结果长度
         *@param[in]:tag_word,标签词
         *@param[in]:max_len,最大的结果长度
         *@return:还在状态返回值
         */
        int get_tagsong(song_id_t* tagsong, uint &len_tagsong,
                        char* tag_word, uint max_len);
    };
}


#endif /* _RLS_USCGETTER_H */

