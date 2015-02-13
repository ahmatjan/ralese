//============================================================================
// @author      : weijingqi (weijingqi@baidu.com)
// @file        : rls_ral.h
// @date        : 13 May 2012,11:40:05
// @copyright   : 2011 Baidu.com, Inc. All Rights Reserved
// @encoding    : 
// @version     : 
// @brief       : 推荐算法 
//============================================================================

#ifndef _RLS_RAL_H
#define _RLS_RAL_H
#include "rls_def.h"
#include "rls.h"
#include "dao.h"
#include "macro.h"
#include "bsl/pool.h"
#include "rls_struct.h"
#include "rls_dictseeker.h"
#include "rls_instant.h"

namespace rls{
    class RAl{
    public:
        /**
         *@brief:构造函数
         */
        RAl();
        /**
         *@brief:虚构函数
         */
        ~RAl();

        /**
         *@brief:获取随机列表
         *@param[in]:song_list,歌曲全局列表 
         *@param[in]:song_len,全局列表的长度
         *@param[out]:r_song_list,结果歌曲列表
         *@param[out]: r_song_len, 结果列表的长度
         *@param[out]: max_len, 最大的结果列表长度
         *@param[in]:filter_dict,过滤字典
         *@return:函数执行情况返回值
         */
        int get_randomlist(const song_id_t* song_list, uint song_len, 
                           Song_item_t* r_song_list, uint &r_song_len, 
                           uint max_len, const sodict_build_t* filter_dict);

		/**
         *@brief:融合非私人频道的新用户列表
         *@param[in]:ldac_list, redis ldac列表 
         *@param[in]:bpr_list, redis bpr列表 
         *@param[in]:instant_list,lr列表
         *@param[out]:r_song_list,待融合的列表
         *@return:融合后列表长度
         */
        int gen_newuser_fuselist(Song_item_t *ldac_list, Song_item_t *bpr_list, Song_item_t *instant_list,
                                    uint ldac_list_len, uint bpr_list_len, uint instant_list_len, Song_item_t *r_song_list,
                                    uint &r_song_len, uint max_len);

		/**
         *@brief:融合随便听听的列表
         *@param[in]:redis_list, redis random list列表 
         *@param[in]:itemsim_list
         *@param[out]:r_song_list,待融合的列表
         *@return:融合后列表长度
         */
        int gen_recommend_fuselist(Song_item_t *itemsim_list, Song_item_t* redis_list,
                                    uint itemsim_list_len, uint redis_list_len, Song_item_t *r_song_list,
                                    uint &r_song_len, uint max_len);

		/**
         *@brief:融合公共频道的列表
         *@param[in]:redis_list, redis列表 
         *@param[in]:instant_list,lr列表
         *@param[out]:r_song_list,待融合的列表
         *@return:融合后列表长度
         */
        int gen_public_fuselist(Song_item_t *redis_list, Song_item_t *instant_list,
                                    uint redis_list_len, uint instant_list_len, Song_item_t *r_song_list,
                                    uint &r_song_len, uint max_len);

        /**
         *@brief:获取随机列表,但是加上了简单的策略处理
         *@param[in]:song_list,歌曲全局列表 
         *@param[in]:song_len,全局列表的长度
         *@param[out]:r_song_list,结果歌曲列表
         *@param[out]: r_song_len, 结果列表的长度
         *@param[out]: max_len, 最大的结果列表长度
         *@param[in]:filter_dict,过滤字典
         *@return:函数执行情况返回值
         */
        int get_simplelist(const song_id_t* song_list, uint song_len, 
                           Song_item_t* r_song_list, uint &r_song_len, 
                           uint max_len, const sodict_build_t* filter_dict);
        
        /**
         *@brief:将歌曲按权重排序
         *@param[in/out]:song_list,歌曲
         *@param[in]:song_list_len,歌曲长度
         *@return:执行结果状态返回值
         */
        int sort_songlist(Song_item_t* song_list, int song_list_len);

        /**
         *@brief:用拉链归并算法生成推荐结果,针对公用频道
         *@param[in]:user_data,用户行为数据
         *@param[in]:ch_name,频道名字
         *@param[in]:filter_dict,需要过滤的歌曲字典
         *@param[in]:is_public,true，使用公用频道数据,false,使用所有数据
         *@param[in]:max_len,最大的结果长度
         *@param[out]:r_len,推荐结果长度
         *@param[out]:topNList,推荐结果列表
         *@param[in]:pool,线程的内存池
         *@return:FAIL SUCCESS
         */
        int gen_indexmerge_rlist(const r_userdata_t &user_data, const char* ch_name,
                                 const sodict_build_t* filter_dict, bool is_public, 
                                 uint max_len, uint &r_len, 
                                 Song_item_t* topNList, bsl::mempool &pool);

         /**
         * @brief, 融合列表，并用户模型调权
         * [in]
         * uid, 用户id
         * ch_name, 频道名
         * filter_dict, 需要过滤的歌曲字典
         * max_len, 最大的结果长度
         * f_list, 待融合的数据结构
         * utag_list, 用户标签列表
         * tag_len, 用户标签长度
         * pool, 线程的内存池
         * [out]
         * r_len, 推荐结果长度
         * r_song_list, 推荐结果列表
         * @return:FAIL SUCCESS
         */
        int gen_fuse_rlist(uint uid, const char* ch_name,const sodict_build_t* filter_dict,
                           uint max_len,uint &r_len, Song_item_t* r_song_list, 
                           fuse_list_t * f_list, 
                           User_tag_t * utag_list, int tag_len,
                           const r_userdata_t &user_data,
                           bsl::mempool &pool); 

        /**
         * 从相关歌曲中topn的随机抽取一个
         * [in]
         * p_song_song 相关歌曲
         * song_song_len 相关歌曲长度
         * u_buf 用户命令buf
         * filt_dict 过滤字典
         * return not null 成功 null失败
         */
        Song_item_t* song_topN_rand(Song_item_t *p_song_song, int song_song_len,
                                         bsl::mempool &pool , sodict_build_t *filt_dict);

        /**
         * @brief, 生成即时行为建模列表
         * [in]
         * song_list, 歌曲列表
         * song_len, 歌曲列表长度
         * filter_dict, 需要过滤的歌曲字典
         * max_len, 最大的结果长度
         * instant_model, 即时兴趣模型 
         * need_detect, 是否需要试探
         * ch_name, 频道名
         * [out]
         * r_song_len, 推荐结果长度
         * r_song_list, 推荐结果列表
         * @return:FAIL SUCCESS
         */
        int get_instantlist(const song_id_t* song_list, uint song_len, 
                           Song_item_t* r_song_list, uint &r_song_len, 
                           const r_userdata_t &user_data,
                           uint max_len, const sodict_build_t* filter_dict, 
                           char * ch_name);

        /**
         * @brief, 公用列表融合方法
         * [in]
         * f_list, 需要融合的列表集
         * f_use_list_len, 需要融合的列表个数 
         * max_len, 融合后列表歌曲最大长度
         * r_song_len, 融合后歌曲列表长度
         * r_song_list, 融合后歌曲列表
         * @return: r_song_len 融合后列表长度
         */
        int gen_common_fuselist(fuse_list_t *f_list, uint fuse_list_len, uint max_len, Song_item_t *r_song_list, uint &r_song_len, const sodict_build_t* filter_dict = NULL);

        /**
         * @brief, 生成公用融合列表map
         * [in]
         * f_list, 需要融合的列表集
         * f_use_list_len, 需要融合的列表个数 
         * max_len, 融合后列表歌曲最大长度
         * filter_dict, 过滤字典
         * list_map, 生成的map
         * @return: r_song_len 融合后列表长度
         */
        int gen_map_for_common_fuselist(fuse_list_t *f_list, uint fuse_list_len, uint max_len, uint fuse_list_song_num, const sodict_build_t* filter_dict, bsl::hashmap<uint, Song_item_t> &list_map);

        /**
         * @brief, 获取融合后列表top N
         * [in]
         * list_map, 融合后列表map
         * r_song_len, 结果列表长度
         * r_song_list, 结果歌曲列表
         * @return: r_song_len 列表长度
         */
        int get_topn_from_map(const bsl::hashmap<uint, Song_item_t> &list_map, Song_item_t *r_song_list, uint &r_song_len, uint max_len);
        /**
         * @Synopsis  get_y_list 生成音乐人频道钟表
         *
         * @Param song_list 歌曲列表
         * @Param song_len 歌曲列表长度
         * @Param r_song_list 结果列表
         * @Param r_song_len 结果列表长度
         * @Param user_data 用户数据
         * @Param max_len 需求最大长度
         * @Param filter_dict 过滤词典
         * @Param ch_name 频道名
         *
         * @Returns   
         */
        int get_y_list(const song_id_t* song_list, uint song_len,
                         Song_item_t* r_song_list, uint &r_song_len,
                         const y_user_data_t &user_data,
                         uint max_len, const sodict_build_t* filter_dict,
                         char * ch_name);
        
    private:
        
        /**
         *@brief:设置跳过降权处理
         *@param[in]:user_data,用户行为数据
         *@param[out]:deweight_singer, 降权歌手的字典,key为歌手id
         *@param[out]:de_weight,降权变量
         *@return: FAIL, SUCCESS
         */
        int _set_de_weight(const r_userdata_t &user_data,
                            bsl::hashmap<int, int> &deweight_singer, de_weight_t &de_weight);

        
        /**
         *@brief:建立喜欢索引
         *@param[in]: pref,喜欢列表
         *@param[in]:len_ref,喜欢列表长度
         *@param[in]:db_type, 喜好类型
         *@param[in]:max_time,最新的行为时间
         *@param[in/out]:lookup,列表字典
         *@param[out]:p_index,拉链索引结构
         *@param[out]:index_size,拉链的索引个数
         *@return:FAIL, SUCCESS
         */
        int _pref_indexweight(const Item_bean *p_ref, int len_ref,
                              enum DB_PREF_TYPE db_type, time_t max_time,
                              sodict_build_t* lookup_dict, Index_type_t* p_index, 
                              int& index_size);

        /**
         *@brief:计算喜欢的权重
         *@param[in]:type,喜欢类型
         *@param[in]:time,发生的时间
         *@param[in]:max_time,最近的行为时间
         *@return:权重
         */
        int RAl::_cal_index_weight_pref(enum DB_PREF_TYPE type, int num);     
        
        /**
         *@brief:将行为数据放入到拉链索引中
         *@param[in]:action,行为数据列表
         *@param[in]:len_action,行为数据列表的长度
         *@param[in]:max_time,行为发生的最大时间
         *@param[in/out]:lookup_dict, 拉链的字典
         *@param[out]:p_index,拉链结构
         *@param[out]:index_size,拉链长度
         *@return:FAILL, SUCCESS
         */
        int _action_indexweight(const Action_bean* action, int len_action,
                                 time_t max_time, sodict_build_t* lookup_dict,
                                         Index_type_t* p_index, int& index_size);

        /**
         *@brief:将试听历史数据放入到拉链索引中
         *@param[in]:listenhistory,试听历史数据
         *@param[in]:len_listenhistory,分析的试听历史数据的长度
         *@param[in]:max_time,行为发生的最大时间
         *@param[in/out]:lookup_dict, 拉链的字典
         *@param[out]:p_index,拉链结构
         *@param[out]:index_size,拉链长度
         *@return:FAILL, SUCCESS
         */
        int _fmlisten_indexweight(const Item_bean* listenhistory, int len_listenhistory,
                                  time_t max_time, sodict_build_t* lookup_dict,
                                  Index_type_t* p_index, int& index_size);
        

        /**
         *@brief:计算行为的权重
         *@param[in]:type,行为类型
         *@param[in]:time,行为发生的时间
         *@param[in]:max_time,行为发生的最大时间
         *@return:权重
         */
        int _cal_index_weight_behavior(enum DB_USER_BEHAVIOR_TYPE type, const time_t time,
                                       const time_t max_time);

        
        /**
         *@brief:获得最小的节点
         *@param[in]:拉链
         *@param[in]:index_len,拉链长度
         *@param[out]:dest_songid，输出的歌曲id
         *@param[out]:dest_weight,输出的权重
         *@param[out]:dest_cnt, 输出个个数
         *@param[out]:dest_source, 输出数据来源
         *@param[out]:dest_index 最大的权值的p_index索引号
         *@return:-1 没有了， 1 负权重, 0 正权重
         */
        int _pop_min_weight(Index_type_t* p_index, int index_len, 
                            uint& dest_songid, int& dest_weight, 
                            int &dest_cnt, uint &dest_source, uint &dest_index);


        /**
         *@brief:降权处理
         *@param[in/out]:需要处理的歌曲
         *@param[in]:de_weight,降权结构体
         *@param[in]:deweight_singer,需要降权的歌手的字典
         *@return:void
         */
        void _pass_deweight(Song_item_t* p_song, const de_weight_t &de_weight,
                            const bsl::hashmap<int, int> &deweight_singer);
        
        
        /**
         *@brief:提权处理
         *@param[in/out]:p_song,歌曲
         *@return:void
         */
        void _pass_upweight(Song_item_t* p_song);    

        /**
         * @Synopsis  _gen_feature_weight 生成用户特征向量
         *
         * @Param user_data 用户数据
         * @Param score_v 评分向量
         * @Param normal_v 归一化后的向量
         *
         * @Returns   
         */
        int _gen_feature_weight(const r_userdata_t &user_data, std::vector<int> &score_v, std::vector<int> &normal_v);   
        
        /*字典数据查询*/
        DictSeeker* _dict_seeker;
    };
}


#endif /* _RLS_RAL_H */

