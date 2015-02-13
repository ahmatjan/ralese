/**
 * @file rls_dictseeker.h
 * @Synopsis  rls字典数据查找
 * @author sparkwen
 * @version 1.0.0
 * @date 2013-10-11
 */
#ifndef _RLS_DICTSEEKER_H
#define _RLS_DICTSEEKER_H
#include "rls.h"
#include "rls_def.h"
#include "macro.h"
#include "dao.h"
#include "rls_struct.h"
#include "mcCache.h"

namespace rls{
    class DictSeeker{
    public:
        /*构造函数*/
        DictSeeker();

        /*虚构函数*/
        ~DictSeeker();

        /**
         *@brief:查找公用频道的关联歌曲
         *@param[in]:itemid, itemid
         *@param[in]:ch_sign,频道标识, 频道名或者all计算标识
         *@param[in]:p,返回的歌曲列表的开始指针
         *@param[in]:len, 返回的歌曲列表的长度
         *@return:SUCCESS,成功,FAIL失败,NOEXIST不存在
         */
        int seek_public_song_song(uint itemid, uint ch_sign, 
                                              Song_item_t** p, int &len);        

        /**
         *@brief:获得频道的信息
         *@param[in]:频道名字的签名
         *@return:NULL 不存在，频道信息结构体指针
         */
        ch_info_t* get_ch_info(uint ch_sign);

        /**
         *@brief:判断频道是否存在
         *@param[in]:ch_name,频道名字
         *@return:true,存在,false,不存在
         */
        bool has_ch(const char *ch_name);

        /**
         *@brief, 查找是否存在song tag pair 
         *[in]
         *song_id, 歌曲id
         *tag_id, 标签id
         *@return, true,存在,false,不存在
         */
        bool has_song_tag(uint song_id, uint tag_id);

        /**
         *@brief:查找关联歌曲
         *@param[in]:itemid, itemid
         *@param[in]:p,返回的歌曲列表的开始指针
         *@param[in]:len, 返回的歌曲列表的长度
         *@return:SUCCESS,成功,FAIL失败,NOEXIST不存在
         */
        int seek_song_song(uint itemid, Song_item_t** p, int &len);

        /**
         *@brief:查找关联歌手
         *@param[in]:itemid, artist id
         *@param[in]:p,返回的关联歌手列表的开始指针
         *@param[in]:len, 返回的关联歌手列表的长度
         *@return:SUCCESS,成功,FAIL失败,NOEXIST不存在
         */
        int seek_singer_singer(uint itemid, Singer_item_t** p, int &len);

 
        /**
         *@brief:查找判断试探歌曲
         *@param[in]:itemid, itemid
         *@param[in]:ch_name, ch_name
         *@return:指向试探歌曲的指针维度
         */
        int* judge_detect_song(uint itemid, const char* ch_name);
        
        
        /**
         *@brief:查找公用频道的歌手关联歌曲
         *@param[in]:itemid, itemid
         *@param[in]:ch_sign,频道标识, 频道名或者all计算标识
         *@param[in]:p,返回的歌曲列表的开始指针
         *@param[in]:len, 返回的歌曲列表的长度
         *@return:SUCCESS,成功,FAIL失败,NOEXIST不存在
         */
        int seek_public_singer_song(uint itemid, uint ch_sign, 
                                                Song_item_t** p, int &len);

        /**
         *@brief:查找歌手关联歌曲
         *@param[in]:itemid, itemid
         *@param[in]:p,返回的歌曲列表的开始指针
         *@param[in]:len, 返回的歌曲列表的长度
         *@return:SUCCESS,成功,FAIL失败,NOEXIST不存在
         */
        int seek_singer_song(uint itemid, Song_item_t** p, int &len);

        /**
         *@brief:查找频道歌曲的权值
         *@param[in]:songid,
         *@param[in]:ch_name
         *@return:>=0,成功,<0失败
         */
        int get_channel_song_weight(uint songid, const char* ch_name);

        /**
         *@brief:获得歌曲的基本信息
         *@param[in]:itemid,itemid
         *@return:歌曲信息
         */
        Song_brief_t* get_song_brief(uint itemid);

        /**
         *@brief:过滤歌曲
         *@param[in]:dict,过滤字典
         *@param[in]:songid,要过滤的歌曲id
         *return: True,存在， False 不存在
         */
        bool filt_song(const sodict_build_t* dict, uint songid);

        /**
         *@brief:填充过滤字典
         *@param[in]:user_data,用户行为数据
         *@param[out]:filter_dict
         *@return: 0 成功
         */
        int fill_filter_dict(const r_userdata_t &user_data, sodict_build_t* filter_dict);

        /**
         *@brief:填充过滤字典
         *@param[in]:user_data,用户行为数据
         *@param[out]:filter_dict
         *@return: 0 成功
         */
        int fill_hate_dict(const r_userdata_t &user_data, sodict_build_t* filter_dict);

        /**
         * @Synopsis  get_singer_id 获取歌曲的歌手id
         *
         * @Param itemid 歌曲id
         *
         * @Returns 歌手id
         */
        uint get_singer_id(uint itemid);
        
        /**
         * @Synopsis  get_rand_top 从插播表中查插入歌曲
         *
         * @Param insertid 歌曲id
         * @Param ch_name 频道名
         * @Param filter_dict 过滤扁
         *
         * @Returns 歌手id
         */
        int get_rand_top(uint &insertid, char* ch_name, sodict_build_t* filter_dict);   

        /**
         * @Synopsis  get_rand_detect 从试探歌曲列表中查找插入歌曲
         *
         * @Param detectid 歌曲id
         * @Param dim 维度
         * @Param cla 类号
         * @Param ch_name 频道名
         * @Param filter_dict 过滤字典
         *
         * @Returns 歌曲id
         */
        int get_rand_detect(uint &detectid, int dim, int cla, char* ch_name, const sodict_build_t *filter_dict);
                
        /**
         * @Synopsis  seek_feature_pos 查找特征歌曲位置
         *
         * @Param itemid 歌曲id
         *
         * @Returns >= 0成功， < 0失败
         */
        int seek_feature_pos(uint itemid);
        
        /**
         * @Synopsis  seek_lrmodel_pos 查找lr模型的权值
         *
         * @Param itemid 歌曲id
         * @Param lr_weight_pos 列表中的偏移值
         * @Param lr_label_num 标签数目
         *
         * @Returns   
         */
        int seek_lrmodel_pos(uint itemid, uint& lr_weight_pos, uint& lr_label_num);

        int fill_y_filter_dict(const y_user_data_t &user_data, sodict_build_t* filter_dict);

        int fill_y_hate_dict(const y_user_data_t &user_data, sodict_build_t* filter_dict);
    };
}


#endif /* _RLS_DICTSEEKER_H */

