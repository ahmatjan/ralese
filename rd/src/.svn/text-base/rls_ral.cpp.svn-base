/*=============================================================================
#     FileName: rls_ral.cpp
#         Desc: 推荐算法
#       Author: wensaiping
#        Email: wensaiping@baidu.com
#     HomePage:
#      Version: 1.0.1
#   LastChange: 2013-08-06 14:19:20
#      History:
=============================================================================*/
#include "rls_ral.h"
#include <algorithm>
#include <time.h>
#include "bsl/map.h"
#include "topn.h"
#include "rls_instant.h"

namespace rls{
    /**
    * 歌曲权重比较函数
    */
    inline bool song_item_weight_cmp(Song_item_t* const &a, Song_item_t* const &b){
        return a->weight > b->weight;
    }

    /**
    * ===================  FUNCTION list_cmp ==============================
    * @brief 根据成功率对选出来的结果进行快排
    * return true a排b前，false a排b后
    * ===========================================================================
    */
    bool list_cmp(Song_item_t a, Song_item_t b){
        return a.weight > b.weight;
    }

    /**
    * 歌手权重比较函数
    */
    inline bool singer_item_weight_cmp(Singer_item_t* const &a, Singer_item_t* const &b){
        return a->weight > b->weight;
    }

    /**
    * 列表权重比较函数
    */
    bool list_item_weight_cmp(Song_item_t const &a, Song_item_t const &b){
        return a.weight > b.weight;
    }

    RAl::RAl(){
        _dict_seeker = new DictSeeker();
        //植入随机种子
        srand((unsigned)time(NULL));
    }

    RAl::~RAl(){
        if(NULL != _dict_seeker){
            delete _dict_seeker;
        }
    }

    int RAl::sort_songlist(Song_item_t* song_list, int song_list_len){
        std::sort(song_list, song_list + song_list_len, list_cmp);
        return SUCCESS;
    }

    int RAl::get_randomlist(const song_id_t* song_list, uint song_len,
                            Song_item_t* r_song_list, uint &r_song_len,
                            uint max_len, const sodict_build_t* filter_dict)
    {
        if(NULL == song_list || NULL == r_song_list){
            WARNING_LOG("wrong param in get_randomlist");
            return FAIL;
        }
        if(song_len <= 0){
            WARNING_LOG("song list len <= 0");
            return FAIL;
        }
        int ret;
        //全局列表比需要的小
        if(song_len < max_len){
            int temp_len = 0;
            for(uint i = 0; i < song_len; i++){
                //过滤
                if(_dict_seeker->filt_song(filter_dict, song_list[i].sid)){
                    continue;
                }
                r_song_list[temp_len].song_id = song_list[i].sid;
                r_song_list[temp_len].weight = 0;
                temp_len++;
            }
            //乱序
            std::random_shuffle(r_song_list, r_song_list+temp_len);
            r_song_len = temp_len;
        }
        else{
            bsl::hashmap<uint, uint> rdata;
            rdata.create(max_len);
            uint value;
            uint r = 0;
            if(max_len > MAX_USER_LIST_LEN){
                max_len = MAX_USER_LIST_LEN;
            }
            int index_list[MAX_USER_LIST_LEN];
            int loop_len = max_len * 3;
            uint random_len = 0;
            for(int i = 0; i < loop_len; i++){
                r = rand() % song_len;
                ret = rdata.get(r, &value);
                if(ret == bsl::HASH_NOEXIST){
                    rdata.set(r, 0);
                    //过滤
                    if(_dict_seeker->filt_song(filter_dict, song_list[r].sid)){
                        continue;
                    }
                    index_list[random_len] = r;
                    random_len++;
                    if(random_len >= max_len){
                        break;
                    }
                }
            }
            int index = 0;
            for(int i = 0; i < random_len; i++){
                index = index_list[i];
                r_song_list[i].song_id = song_list[index].sid;
                r_song_list[i].weight = 0;
            }
            r_song_len = random_len;
            rdata.destroy();
        }
        return SUCCESS;
    }

    int RAl::get_simplelist(const song_id_t* song_list, uint song_len,
                            Song_item_t* r_song_list, uint &r_song_len,
                            uint max_len, const sodict_build_t* filter_dict)
    {
        if(NULL == song_list || NULL == r_song_list){
            WARNING_LOG("wrong param in get_randomlist");
            return FAIL;
        }
        if(song_len <= 0){
            WARNING_LOG("song list len <= 0");
            return FAIL;
        }
        int ret;
        //全局列表比需要的小
        if(song_len < max_len){
            int temp_len = 0;
            for(uint i = 0; i < song_len; i++){
                //过滤
                if(_dict_seeker->filt_song(filter_dict, song_list[i].sid)){
                    continue;
                }
                r_song_list[temp_len].song_id = song_list[i].sid;
                r_song_list[temp_len].weight = 0;
                r_song_list[temp_len].source = DEFAULT_SOURCE;
                temp_len++;
            }
            //乱序
            std::random_shuffle(r_song_list, r_song_list+temp_len);
            r_song_len = temp_len;
        }
        else{
            bsl::hashmap<uint, uint> rdata;
            rdata.create(max_len);
            uint value;
            uint r = 0;
            if(max_len > MAX_USER_LIST_LEN){
                max_len = MAX_USER_LIST_LEN;
            }
            int index_list[MAX_USER_LIST_LEN];
            int loop_len = max_len * 3;
            uint random_len = 0;
            for(int i = 0; i < loop_len; i++){
                r = rand() % song_len;
                ret = rdata.get(r, &value);
                if(ret == bsl::HASH_NOEXIST){
                    rdata.set(r, 0);
                    //过滤
                    if(_dict_seeker->filt_song(filter_dict, song_list[r].sid)){
                        continue;
                    }
                    index_list[random_len] = r;
                    random_len++;
                    if(random_len >= max_len){
                        break;
                    }
                }
            }
            int index = 0;
            //把PV高的歌曲排在前面
            for(int i = 0; i < random_len; i++){
                index = index_list[i];
                r_song_list[i].song_id = song_list[index].sid;
                r_song_list[i].weight = 0;
                r_song_list[i].source = DEFAULT_SOURCE;
            }
            r_song_len = random_len;
            rdata.destroy();
        }
        return SUCCESS;
    }

    int RAl::gen_indexmerge_rlist(const r_userdata_t &user_data, const char* ch_name,
                                  const sodict_build_t* filter_dict,
                                  bool is_public, uint max_len,
                                  uint &r_len, Song_item_t* topNList,
                                  bsl::mempool &pool)
    {
        //检测参数
        if(NULL == ch_name || NULL == filter_dict){
            WARNING_LOG("wrong param in gen_indexmerge_rlist");
            return FAIL;
        }
        r_len = 0;
        int ret;
        sodict_build_t* lookup_dict = odb_creat(FILT_DICT_HASH);
        if (NULL == lookup_dict){
            WARNING_LOG("creat odict faild");
            return FAIL;
        }
        int len_all = MAX_ANALYS_LEN * ANALYS_CLASS_NUM;
        //建议用户行为的item索引
        Index_type_t* p_index = NULL;
        if (len_all > 0){
            p_index = (Index_type_t*) (pool.malloc((sizeof(Index_type_t))*len_all));
            if (!p_index){
                if (NULL != lookup_dict){
                    odb_destroy(lookup_dict);
                }
                WARNING_LOG("failed to malloc action buf[%zd]", sizeof(Index_type_t) * len_all);
                return FAIL;
            }
        }
        else{
            WARNING_LOG("user has not action data");
            if (NULL != lookup_dict){
                odb_destroy(lookup_dict);
            }
            return FAIL;
        }
        //计算行为权重,去重,权值合并
        int index_size=0;
        time_t max_time = user_data.maxtime_all;
        //分析长度
        int analys_len = 0 ;
        analys_len = user_data.len_songlove > MAX_ANALYS_LEN ? MAX_ANALYS_LEN : user_data.len_songlove;
        this->_pref_indexweight(user_data.songlove, analys_len, DB_SONGLOVE,
                                user_data.maxtime_songlove, lookup_dict, p_index, index_size);

        analys_len = user_data.len_songhate > MAX_ANALYS_LEN ? MAX_ANALYS_LEN : user_data.len_songhate;
        this->_pref_indexweight(user_data.songhate, analys_len, DB_SONGHATE,
                                user_data.maxtime_songhate, lookup_dict, p_index, index_size);

        analys_len = user_data.len_songcloud > MAX_ANALYS_LEN ? MAX_ANALYS_LEN : user_data.len_songcloud;
        this->_pref_indexweight(user_data.songcloud, analys_len, DB_SONGCLOUD,
                                user_data.maxtime_songcloud, lookup_dict, p_index, index_size);

        analys_len = user_data.len_action > MAX_ANALYS_LEN ? MAX_ANALYS_LEN : user_data.len_action;
        this->_action_indexweight(user_data.action, analys_len, user_data.maxtime_action,
                                  lookup_dict, p_index, index_size);

        analys_len = user_data.len_listenhistory > MAX_ANALYS_LEN ? MAX_ANALYS_LEN : user_data.len_listenhistory;
        this->_fmlisten_indexweight(user_data.listenhistory, analys_len, user_data.maxtime_listenhistory,
                                    lookup_dict, p_index, index_size);

        if(index_size <= 0){
            r_len = 0;
            WARNING_LOG("index size is 0, not recommend");
            if (NULL != p_index){
                pool.free(p_index, (sizeof(Index_type_t))*len_all);
            }
            if (NULL != lookup_dict){
                odb_destroy(lookup_dict);
            }
            return SUCCESS;
        }
        //查找index的相关歌曲
        ret = 0;
        char temp_name[MAX_CHNAME_LEN];
        snprintf(temp_name, MAX_CHNAME_LEN, "%s", ch_name);
        uint ch_sign = creat_sign32(temp_name);
        //有效的兴趣点的个数
        int valid_index_size = 0;
        for(int i = 0; i < index_size; ++i){
#ifdef _DEBUG_TIME
            DEBUG_LOG("p_index,itemid:%u,type:%d, weight:%d", p_index[i].itemid,
                      p_index[i].type, p_index[i].weight);
#endif
            p_index[i].index = 0;
            if(p_index[i].type == ITEM_TYPE_SONG){
                ret = _dict_seeker->seek_public_song_song(p_index[i].itemid, ch_sign,
                                                          &(p_index[i].pos), p_index[i].len);
            }
            else if(p_index[i].type == ITEM_TYPE_SINGER){
                ret = _dict_seeker->seek_public_singer_song(p_index[i].itemid, ch_sign,
                                                            &(p_index[i].pos), p_index[i].len);
            }
            else{
                ret = FAIL;
            }
            if(SUCCESS != ret){
                p_index[i].pos = NULL;
                p_index[i].index = 0;
                p_index[i].len =0;
                p_index[i].weight = 0;
                p_index[i].itemid = 0;
            }
            else{
                if(p_index[i].weight > g_config.good_pref_score){
                    valid_index_size++;
                }
            }
        }
        //计算降权
        de_weight_t de_weight;
        bsl::hashmap<int, int> deweight_singer;
        deweight_singer.create(10);
        this->_set_de_weight(user_data, deweight_singer, de_weight);
        //合并列表
        ret = 0;
        uint len_topNlist = 0;
        //控制推荐数量，避免兴趣点少导致结果过于集中
        uint max_rlen = max_len > VALID_RELATION_SONG_NUM * valid_index_size ? VALID_RELATION_SONG_NUM * valid_index_size : max_len;
        //有效点的歌曲数控制<索引号，计数>
        bsl::hashmap<uint, int> valid_num_map;
        //歌曲与index的对应关系
        bsl::hashmap<uint, uint> song_index_map;
        valid_num_map.create(max_rlen);
        song_index_map.create(index_size * VALID_RELATION_SONG_NUM);
        int tmp_value = 0;
        while(len_topNlist<max_rlen){
            int weight=0;
            int cnt=0;
            uint source = DEFAULT_SOURCE;
            uint song_id=0;
            uint tmp_index = 0;
            ret = this->_pop_min_weight(p_index, index_size, song_id, weight, cnt, source, tmp_index);
            weight = weight > MAX_WEIGHT ? MAX_WEIGHT : weight;
            if(-1 == ret){
                break;
            }
            if(weight <= 0){
                continue;
            }

            if(_dict_seeker->filt_song(filter_dict, song_id)){
                continue;
            }

            int valid_ret = -1;
            valid_ret = valid_num_map.get(tmp_index, &tmp_value);
            if(valid_ret == bsl::HASH_EXIST && tmp_value > VALID_RELATION_SONG_NUM){
                DEBUG_LOG("the index[%d] have song enough > %d.", tmp_index, VALID_RELATION_SONG_NUM);
                continue;
            }
            song_index_map.set(song_id, tmp_index);
            if(0 == ret){
                weight = g_config.WConf.good_weight_table[weight][MAX_PERCENT*cnt/index_size];
                topNList[len_topNlist].song_id = song_id;
                topNList[len_topNlist].weight = weight;
                topNList[len_topNlist].source = source;
                this->_pass_deweight(topNList+len_topNlist, de_weight, deweight_singer);
                this->_pass_upweight(topNList+len_topNlist);
                if(valid_ret == bsl::HASH_EXIST){
                    tmp_value++;
                    valid_num_map.set(tmp_index, tmp_value);
                }
                else{
                    valid_num_map.set(tmp_index, 1);
                }
                ++len_topNlist;
            }
            else if(1 == ret){
                weight = g_config.WConf.bad_weight_table[weight];
                topNList[len_topNlist].song_id = song_id;
                topNList[len_topNlist].weight = weight;
                topNList[len_topNlist].source = source;
                this->_pass_deweight(topNList+len_topNlist, de_weight, deweight_singer);
                this->_pass_upweight(topNList+len_topNlist);
                if(valid_ret == bsl::HASH_EXIST){
                    tmp_value++;
                    valid_num_map.set(tmp_index, tmp_value);
                }
                else{
                    valid_num_map.set(tmp_index, 1);
                }
                ++len_topNlist;
            }
        }
        //构建小顶堆
#ifdef _DEBUG_TIME
        for(int i = 0; i < len_topNlist; i++){
            DEBUG_LOG("make_heap before: position[%d], song_id[%d], weight[%d]", i, topNList[i].song_id, topNList[i].weight);
        }
#endif
        std::make_heap(topNList, topNList + len_topNlist, list_item_weight_cmp);
#ifdef _DEBUG_TIME
        for(int i = 0; i < len_topNlist; i++){
            DEBUG_LOG("make_heap after: position[%d], song_id[%d], weight[%d]", i, topNList[i].song_id, topNList[i].weight);
        }
#endif
        while(ret != -1 && max_rlen > 0){
            Song_item_t inner_item;
            inner_item.song_id = 0;
            inner_item.weight = 0;
            int weight=0;
            uint source = DEFAULT_SOURCE;
            int cnt=0;
            uint song_id=0;
            uint tmp_index = 0;
            ret = this->_pop_min_weight(p_index, index_size, song_id, weight, cnt, source, tmp_index);
            weight = weight > MAX_WEIGHT ? MAX_WEIGHT : weight;
            if(-1 == ret){
                break;
            }
            if(weight <= 0){
                continue;
            }
            if(_dict_seeker->filt_song(filter_dict, song_id)){
                continue;
            }
            song_index_map.set(song_id, tmp_index);
            int valid_ret = -1;
            valid_ret = valid_num_map.get(tmp_index, &tmp_value);
            if(valid_ret == bsl::HASH_EXIST && tmp_value > VALID_RELATION_SONG_NUM){
                DEBUG_LOG("the index[%d] have song enough > %d.", tmp_index, VALID_RELATION_SONG_NUM);
                continue;
            }

            if(0 == ret){
                weight = g_config.WConf.good_weight_table[weight][MAX_PERCENT*cnt/index_size];
                inner_item.song_id = song_id;
                inner_item.weight = weight;
                inner_item.source = source;
                this->_pass_deweight(&inner_item, de_weight, deweight_singer);
                this->_pass_upweight(&inner_item);
                Song_item_t pop_item;
                if(topN_put_out(topNList, len_topNlist, inner_item, list_item_weight_cmp, pop_item)){
                    //push对象value++
                    if(valid_ret == bsl::HASH_EXIST){
                        tmp_value++;
                        valid_num_map.set(tmp_index, tmp_value);
                    }
                    else{
                        valid_num_map.set(tmp_index, 1);
                    }
                    //pop对象的value--
                    song_index_map.get(pop_item.song_id, &tmp_index);
                    valid_ret = valid_num_map.get(tmp_index, &tmp_value);
                    if(valid_ret == bsl::HASH_EXIST){
                        tmp_value --;
                        valid_num_map.set(tmp_index, tmp_value);
                    }
                    else{
                        WARNING_LOG("top N error");
                    }
                }
            }
            else if(1 == ret){
                weight = g_config.WConf.bad_weight_table[weight];
                inner_item.song_id = song_id;
                inner_item.weight = weight;
                inner_item.source = source;
                this->_pass_deweight(&inner_item, de_weight, deweight_singer);
                this->_pass_upweight(&inner_item);
                Song_item_t pop_item;
                if(topN_put_out(topNList, len_topNlist, inner_item, list_item_weight_cmp, pop_item)){
                    //push对象value++
                    if(valid_ret == bsl::HASH_EXIST){
                        tmp_value++;
                        valid_num_map.set(tmp_index, tmp_value);
                    }
                    else{
                        valid_num_map.set(tmp_index, 1);
                    }
                    //pop对象的value--
                    song_index_map.get(pop_item.song_id, &tmp_index);
                    valid_ret = valid_num_map.get(tmp_index, &tmp_value);
                    if(valid_ret == bsl::HASH_EXIST){
                        tmp_value --;
                        valid_num_map.set(tmp_index, tmp_value);
                    }
                    else{
                        WARNING_LOG("top N error");
                    }
                }
            }
        }
        //推荐结果个数
        r_len = len_topNlist;
        if (NULL != p_index){
            pool.free(p_index, (sizeof(Index_type_t))*len_all);
        }
        if (NULL != lookup_dict){
            odb_destroy(lookup_dict);
        }
        deweight_singer.destroy();
        valid_num_map.destroy();
        song_index_map.destroy();
        DEBUG_LOG("gen_indexmerge_rlist finish, r_len:%d", r_len);
        return SUCCESS;
    }

    int RAl::_set_de_weight(const r_userdata_t &user_data,
                            bsl::hashmap<int, int> &deweight_singer, de_weight_t &de_weight)
    {
        de_weight.de_pv = false;
        de_weight.de_year = false;
        de_weight.de_lan = false;
        int next_song_total = 0;
        Song_brief_t* p_next_brief = NULL;
        bsl::hashmap<int, int> singer_de_map;
        singer_de_map.create(10);
        bsl::hashmap<int, int> lan_de_map;
        lan_de_map.create(10);
        bsl::hashmap<int, int> pv_de_map;
        pv_de_map.create(10);
        bsl::hashmap<int, int> year_de_map;
        year_de_map.create(10);
        int value;
        int i;
        int ret;
        int key;
        int listen_value;
        const Action_bean* action = user_data.action;
        int len_action = user_data.len_action;
        const Item_bean* songhate = user_data.songhate;
        int len_songhate = user_data.len_songhate;
        const Item_bean* p_listenhistory = user_data.listenhistory;
        int len_listenhistory = user_data.len_listenhistory;

        //跳过歌曲
        for(i = 0;i<len_action;i++){
            if(action[i].type == DB_NEXT_SONG){
                p_next_brief = _dict_seeker->get_song_brief(action[i].itemid);
                if(NULL == p_next_brief){
                    continue;
                }
                next_song_total++;
                //歌手统计
                ret = singer_de_map.get(p_next_brief->singer_id, &value);
                if(ret == bsl::HASH_NOEXIST){
                    singer_de_map.set(p_next_brief->singer_id, 1);
                }
                else{
                    singer_de_map.set(p_next_brief->singer_id, value+1, bsl::HASH_OVERWRITE);
                }
                //语言统计
                ret = lan_de_map.get(p_next_brief->lang, &value);
                if(ret == bsl::HASH_NOEXIST){
                    lan_de_map.set(p_next_brief->lang, 1);
                }
                else{
                    lan_de_map.set(p_next_brief->lang, value+1, bsl::HASH_OVERWRITE);
                }
                //PV统计
                ret = pv_de_map.get(p_next_brief->pv, &value);
                if(ret == bsl::HASH_NOEXIST){
                    pv_de_map.set(p_next_brief->pv, 1);
                }
                else{
                    pv_de_map.set(p_next_brief->pv, value+1, bsl::HASH_OVERWRITE);
                }
                //年代统计
                ret = year_de_map.get(p_next_brief->year, &value);
                if(ret == bsl::HASH_NOEXIST){
                    year_de_map.set(p_next_brief->year, 1);
                }
                else{
                    year_de_map.set(p_next_brief->year, value+1, bsl::HASH_OVERWRITE);
                }
            }
        }
        //垃圾桶歌曲
        for(i = 0;i<len_songhate;i++){
            p_next_brief = _dict_seeker->get_song_brief(songhate[i].itemid);
            if(NULL == p_next_brief){
                continue;
            }
            next_song_total++;
            //歌手统计
            ret = singer_de_map.get(p_next_brief->singer_id, &value);
            if(ret == bsl::HASH_NOEXIST){
                singer_de_map.set(p_next_brief->singer_id, 1);
            }
            else{
                singer_de_map.set(p_next_brief->singer_id, value+1, bsl::HASH_OVERWRITE);
            }
            //语言统计
            ret = lan_de_map.get(p_next_brief->lang, &value);
            if(ret == bsl::HASH_NOEXIST){
                lan_de_map.set(p_next_brief->lang, 1);
            }
            else{
                lan_de_map.set(p_next_brief->lang, value+1, bsl::HASH_OVERWRITE);
            }
            //PV统计
            ret = pv_de_map.get(p_next_brief->pv, &value);
            if(ret == bsl::HASH_NOEXIST){
                pv_de_map.set(p_next_brief->pv, 1);
            }
            else{
                pv_de_map.set(p_next_brief->pv, value+1, bsl::HASH_OVERWRITE);
            }
            //年代统计
            ret = year_de_map.get(p_next_brief->year, &value);
            if(ret == bsl::HASH_NOEXIST){
                year_de_map.set(p_next_brief->year, 1);
            }
            else{
                year_de_map.set(p_next_brief->year, value+1, bsl::HASH_OVERWRITE);
            }
        }
        //统计试听历史的数据
        bsl::hashmap<int, int> lan_listen_map;
        lan_listen_map.create(10);
        bsl::hashmap<int, int> pv_listen_map;
        pv_listen_map.create(10);
        bsl::hashmap<int, int> year_listen_map;
        year_listen_map.create(10);

        uint listen_total = 0;
        Song_brief_t* p_listen_brief = NULL;
        for(i = 0; i < len_listenhistory; i++){
            p_listen_brief = _dict_seeker->get_song_brief(p_listenhistory[i].itemid);
            if(NULL == p_listen_brief){
                continue;
            }
            listen_total++;
            ret = lan_listen_map.get(p_listen_brief->lang, &value);
            if(ret == bsl::HASH_NOEXIST){
                lan_listen_map.set(p_listen_brief->lang, 1);
            }
            else{
                lan_listen_map.set(p_listen_brief->lang, value+1, bsl::HASH_OVERWRITE);
            }
            ret = pv_listen_map.get(p_listen_brief->pv, &value);
            if(ret == bsl::HASH_NOEXIST){
                pv_listen_map.set(p_listen_brief->pv, 1);
            }
            else{
                pv_listen_map.set(p_listen_brief->pv, value+1, bsl::HASH_OVERWRITE);
            }

            ret = year_listen_map.get(p_listen_brief->year, &value);
            if(ret == bsl::HASH_NOEXIST){
                year_listen_map.set(p_listen_brief->year, 1);
            }
            else{
                year_listen_map.set(p_listen_brief->year, value+1, bsl::HASH_OVERWRITE);
            }
        }
        //降权的歌手
        if(next_song_total > 0){
            for(bsl::hashmap<int, int>::iterator map_iter = singer_de_map.begin();
                map_iter != singer_de_map.end(); map_iter++){
                    if(map_iter->second > g_config.next_singerde_part){
                        deweight_singer.set(map_iter->first, 0);
                    }
                }
        }
        int diff_value, temp_value;
        //判断降权语言
        if(next_song_total > 0){
            value = 0;
            diff_value = 0;
            for(bsl::hashmap<int, int>::iterator map_iter = lan_de_map.begin();
                map_iter != lan_de_map.end(); map_iter++){
                    key = map_iter->first;
                    if(key == INT_NONE){
                        continue;
                    }
                    value = map_iter->second;
                    ret = lan_listen_map.get(key, &listen_value);
                    if(ret == bsl::HASH_EXIST){
                        temp_value = value*100/next_song_total - listen_value*100/listen_total;
                        if(temp_value > g_config.next_lande_part && temp_value > diff_value){
                            de_weight.de_lan = true;
                            de_weight.lan = key;
                            diff_value = temp_value;
                        }
                    }
                }
        }

        //判断PV降权
        if(next_song_total > 0){
            value = 0;
            diff_value = 0;
            for(bsl::hashmap<int, int>::iterator map_iter = pv_de_map.begin();
                map_iter != pv_de_map.end(); map_iter++){
                    key = map_iter->first;
                    if(key == INT_NONE){
                        continue;
                    }
                    value = map_iter->second;
                    ret = pv_listen_map.get(key, &listen_value);
                    if(ret == bsl::HASH_EXIST){
                        temp_value = value*100/next_song_total - listen_value*100/listen_total;
                        if(temp_value > g_config.next_pvde_part && temp_value > diff_value){
                            de_weight.de_pv = true;
                            de_weight.pv = key;
                            diff_value = temp_value;
                        }
                    }
                }
        }

        //判断年代降权
        if(next_song_total > 0){
            value = 0;
            diff_value = 0;
            for(bsl::hashmap<int, int>::iterator map_iter = year_de_map.begin();
                map_iter != year_de_map.end(); map_iter++){
                    key = map_iter->first;
                    if(key == INT_NONE){
                        continue;
                    }
                    value = map_iter->second;
                    ret = pv_listen_map.get(key, &listen_value);
                    if(ret == bsl::HASH_EXIST){
                        temp_value = value*100/next_song_total - listen_value*100/listen_total;
                        if(temp_value > g_config.next_yearde_part && temp_value > diff_value){
                            de_weight.de_year = true;
                            de_weight.year = key;
                            diff_value = temp_value;
                        }
                    }
                }
        }

        singer_de_map.destroy();
        lan_de_map.destroy();
        pv_de_map.destroy();
        year_de_map.destroy();
        lan_listen_map.destroy();
        pv_listen_map.destroy();
        year_listen_map.destroy();
#ifdef _DEBUG_TIME
        DEBUG_LOG("set_de_weight, singer_cnt:%d, [de_lan:%d,lan:%d], [de_pv:%d,lan:%d], [de_year:%d, year:%d]",
                  deweight_singer.size(), de_weight.de_lan, de_weight.lan,
                  de_weight.de_pv, de_weight.pv,
                  de_weight.de_year, de_weight.year);
#endif
        return SUCCESS;
    }

    int RAl::_pref_indexweight(const Item_bean *p_ref, int len_ref,
                               enum DB_PREF_TYPE db_type, time_t max_time,
                               sodict_build_t* lookup_dict, Index_type_t* p_index,
                               int& index_size)
    {
        if (NULL == p_ref || len_ref <= 0 || NULL == lookup_dict || NULL == p_index){
            WARNING_LOG("wrong param in _pref_indexweight");
            return -1;
        }
        int i;
        sodict_snode_t node;
        int tmp_weight;
        int item_type = 0;
        int ret = 0;
        switch (db_type) {
            case DB_SONGLOVE:
            case DB_SONGCLOUD:
            case DB_SONGHATE:
            item_type = ITEM_TYPE_SONG;
            break;
            case DB_SINGERLOVE:
            case DB_SINGERHATE:
            item_type = ITEM_TYPE_SINGER;
            break;
            default:
            break;
        }
        tmp_weight=0;
        //计算 weight
        for (i = 0; i < len_ref; i++){
            node.sign1 = p_ref[i].itemid;
            node.sign2 = item_type;
            ret = odb_seek(lookup_dict, &node);
            if (ret == ODB_SEEK_OK){//已经出现过
                tmp_weight = this->_cal_index_weight_pref(db_type, i);
                //权重累加
                tmp_weight = tmp_weight + p_index[node.cuint1].weight;
                if(tmp_weight > MAX_INDEX_WEIGHT){
                    tmp_weight = MAX_INDEX_WEIGHT;
                }
                else if(tmp_weight < MIN_INDEX_WEIGHT){
                    tmp_weight =  MIN_INDEX_WEIGHT;
                }
                p_index[node.cuint1].weight = tmp_weight;
            }
            else{
                p_index[index_size].itemid = p_ref[i].itemid;
                p_index[index_size].type = item_type;
                p_index[index_size].weight = this->_cal_index_weight_pref(db_type, i);
                node.cuint1 = index_size;
                node.cuint2 = 0;
                if (odb_add(lookup_dict,&node,1) == ODB_ADD_ERROR){
                    WARNING_LOG("add the node info into dict failed");
                }
                ++index_size;
            }
        }
        return 0;
    }

    int RAl::_cal_index_weight_pref(enum DB_PREF_TYPE type, int num)
    {
        if (num < 0){
            num = 0;
        }
        if (num >= MAX_NUM){
            num = MAX_NUM - 1;
        }
        Weight_Conf_t& wconf = g_config.WConf;
        int weight = 0;
        int action_love_hate = 1;
        switch (type){
            case DB_SONGLOVE:
            weight=static_cast<int>(wconf.fm_heartso_w * wconf.num_w[num]);
            break;
            case DB_SONGHATE:
            action_love_hate = -1;
            weight=static_cast<int>(wconf.fm_hateso_w * wconf.num_w[num]);
            break;
            case DB_SONGCLOUD:
            weight=static_cast<int>(wconf.fm_cloudso_w * wconf.num_w[num]);
            break;
            default:
            weight=0;
            break;
        }
        if(weight == 0){
            if(action_love_hate > 0){
                weight = 1;
            }
            else if(action_love_hate < 0){
                weight = -1;
            }
        }
        return weight;
    }

    int RAl::_action_indexweight(const Action_bean* action, int len_action,
                                 time_t max_time, sodict_build_t* lookup_dict,
                                 Index_type_t* p_index, int& index_size)
    {
        if (NULL == action || len_action <= 0 || NULL == lookup_dict || NULL == p_index){
            WARNING_LOG("wrong param in action_indexweight");
            return -1;
        }
        int i;
        sodict_snode_t node;
        int tmp_weight;
        int item_type = 0;
        //计算action weight
        int ret = 0;
        item_type = ITEM_TYPE_SONG;//都是歌曲
        enum DB_USER_BEHAVIOR_TYPE db_type_behavior;
        for (i = 0; i < len_action; i++){
            db_type_behavior = (enum DB_USER_BEHAVIOR_TYPE) action[i].type;
            node.sign1 = action[i].itemid;
            node.sign2 = item_type;
            ret = odb_seek(lookup_dict, &node);
            if (ret == ODB_SEEK_OK){
                tmp_weight  = this->_cal_index_weight_behavior(db_type_behavior, action[i].date, max_time);
                //权重累加
                tmp_weight = tmp_weight + p_index[node.cuint1].weight;
                if(tmp_weight > MAX_INDEX_WEIGHT){
                    tmp_weight = MAX_INDEX_WEIGHT;
                }
                else if(tmp_weight < MIN_INDEX_WEIGHT){
                    tmp_weight =  MIN_INDEX_WEIGHT;
                }
                p_index[node.cuint1].weight = tmp_weight;
            }
            else{
                p_index[index_size].itemid = action[i].itemid;
                p_index[index_size].type = item_type;
                p_index[index_size].weight = this->_cal_index_weight_behavior(db_type_behavior,
                                                                              action[i].date, max_time);
                node.cuint1 = index_size;
                node.cuint2 = 0;
                if (odb_add(lookup_dict, &node, 1) == ODB_ADD_ERROR){
                    WARNING_LOG("add the node info into dict failed");
                }
                ++index_size;
            }
        }
        return 0;
    }


    int RAl::_fmlisten_indexweight(const Item_bean* listenhistory, int len_listenhistory,
                                   time_t max_time, sodict_build_t* lookup_dict,
                                   Index_type_t* p_index, int& index_size)
    {
        if (NULL == listenhistory || len_listenhistory <= 0 || NULL == lookup_dict || NULL == p_index){
            WARNING_LOG("wrong param in action_indexweight");
            return -1;
        }
        int i;
        sodict_snode_t node;
        int tmp_weight;
        int item_type = 0;
        //计算action weight
        int ret = 0;
        item_type = ITEM_TYPE_SONG;//都是歌曲
        for (i = 0; i < len_listenhistory; i++){
            node.sign1 = listenhistory[i].itemid;
            node.sign2 = item_type;
            ret = odb_seek(lookup_dict, &node);
            if (ret == ODB_SEEK_OK){
                tmp_weight  = this->_cal_index_weight_behavior(DB_FM_LISTENEND_TYPE, listenhistory[i].date, max_time);
                //权重累加
                tmp_weight = tmp_weight + p_index[node.cuint1].weight;
                if(tmp_weight > MAX_INDEX_WEIGHT){
                    tmp_weight = MAX_INDEX_WEIGHT;
                }
                else if(tmp_weight < MIN_INDEX_WEIGHT){
                    tmp_weight =  MIN_INDEX_WEIGHT;
                }
                p_index[node.cuint1].weight = tmp_weight;
            }
            else{
                p_index[index_size].itemid = listenhistory[i].itemid;
                p_index[index_size].type = item_type;
                p_index[index_size].weight = this->_cal_index_weight_behavior(DB_FM_LISTENEND_TYPE,
                                                                              listenhistory[i].date, max_time);
                node.cuint1 = index_size;
                node.cuint2 = 0;
                if (odb_add(lookup_dict, &node, 1) == ODB_ADD_ERROR){
                    WARNING_LOG("add the node info into dict failed");
                }
                #ifdef _DEBUG_TIME
                DEBUG_LOG("_fmlisten_indexweight, [itemid:%u][type:%d][weight:%d]",
                          p_index[index_size].itemid, p_index[index_size].type, p_index[index_size].weight);
                #endif
                ++index_size;
            }
        }
        return 0;
    }

    int RAl::_cal_index_weight_behavior(enum DB_USER_BEHAVIOR_TYPE type, const time_t time,
                                        const time_t max_time)
    {
        int days = (max_time - time)/86400;
        if (days < 0){
            days = 0;
        }
        if(days >= MAX_DAY){
            days = MAX_DAY - 1;
        }
        Weight_Conf_t& wconf = g_config.WConf;
        int weight = 0;
        //正向反馈还是负向反馈
        int action_love_hate = 1;
        switch (type){
            case DB_SEARCH_SONG:
            weight=static_cast<int>(wconf.mb_searchso_w * wconf.day_w[days]);
            break;
            case DB_BOX_COMPLETE_TYPE:
            weight=static_cast<int>(wconf.mb_listenend_w * wconf.day_w[days]);
            break;
            case DB_NEXT_SONG:
            action_love_hate = -1;
            weight=static_cast<int>(wconf.fm_jumpso_w * wconf.day_w[days]);
            break;
            case DB_PRE_SONG:
            weight=static_cast<int>(wconf.fm_jumpprior_w * wconf.day_w[days]);
            break;
            case DB_FM_LISTENEND_TYPE:
            weight=static_cast<int>(wconf.fm_listenend_w * wconf.day_w[days]);
            break;
            default:
            weight=0;
            break;
        }
        //使反馈起到作用,最小为1或者-1
        if(weight == 0){
            if(action_love_hate > 0){
                weight = 1;
            }
            else if(action_love_hate < 0){
                weight = -1;
            }
        }
        return weight;
    }

    /**
    * 拉链合并中，提取最小的节点并计算权重
    * [in]
    * p_index 拉链结构数组
    * index_len 拉链个数
    * dest_songid 取出的最小的songid
    * dest_weight 取出的歌曲权重和
    * dest_cnt 取出的歌曲的重复次数
    * dest_source 取出的歌曲的来源
    * dest_index 最大的权值的p_index索引号
    * return 0 全是正的, 1 含有负值, -1 到达尾部
    */
    int RAl::_pop_min_weight(Index_type_t* p_index, int index_len,
                             uint& dest_songid, int& dest_weight,
                             int &dest_cnt, uint &dest_source, uint &dest_index)
    {
        if (index_len <= 0 || !p_index){
            WARNING_LOG("wrong param in _pop_min_weight");
            return -1;
        }
        //内部调用，假设传入都是正确的
        uint min_songid = UINT_MAX;
        bool has_nagtive;
        long weight = 0;
        int max_weight = 0;
        uint index_num = 0;
        uint source = DEFAULT_SOURCE;
        int curr_weight = 0;
        int cnt = 1;
        int done_index_cnt=0,i=0;
        for (i = 0; i < index_len; ++i){
            if(NULL == p_index[i].pos || p_index[i].index >= p_index[i].len){
                done_index_cnt++;
                continue;
            }
            //需要体现出正负反馈
            curr_weight = p_index[i].pos[p_index[i].index].weight * p_index[i].weight/MAX_PERCENT;
            if(curr_weight == 0){
                if(p_index[i].weight > 0){
                    curr_weight = 1;
                }
                else if(p_index[i].weight < 0){
                    curr_weight = -1;
                }
            }
            if (p_index[i].pos[p_index[i].index].song_id < min_songid){
                //找到更小的
                min_songid = p_index[i].pos[p_index[i].index].song_id;
                source = p_index[i].pos[p_index[i].index].source;
                weight = curr_weight;
                max_weight = curr_weight;
                index_num = i;
                cnt = 1;
                has_nagtive = p_index[i].weight < 0;
            }
            else if (p_index[i].pos[p_index[i].index].song_id == min_songid){
                //找到相同的
                weight += curr_weight;
                source |= p_index[i].pos[p_index[i].index].source;
                //更新index_num和最大值
                if(max_weight < curr_weight){
                    max_weight = curr_weight;
                    index_num = i;
                }
                cnt++;
                has_nagtive = has_nagtive || p_index[i].weight < 0;
            }
        }
        if(index_len == done_index_cnt){
            //all done.
            return -1;
        }
        //多个出现的，则取平均
        dest_weight = (int)(weight);
        dest_weight = dest_weight > MAX_WEIGHT? MAX_WEIGHT:dest_weight;
        dest_cnt = cnt;
        dest_songid = min_songid;
        dest_source = source;
        dest_index = index_num;
        for (i = 0; i < index_len; ++i){
            if(NULL == p_index[i].pos || p_index[i].index >= p_index[i].len){
                continue;
            }
            if(p_index[i].pos[p_index[i].index].song_id == min_songid){
                p_index[i].index++;
#ifdef _DEBUG_TIME
                DEBUG_LOG("_pop_min_weight,indexid[%u]indexweight[%d][songid:%u][weight:%d][cnt:%d][has_nagtive:%d][index_num:%d]",
                          p_index[i].itemid, p_index[i].weight, dest_songid,
                          dest_weight, dest_cnt, has_nagtive, dest_index);
#endif
            }
        }
        if(has_nagtive){
            return 1;
        }

        return 0;
    }

    void RAl::_pass_deweight(Song_item_t* p_song, const de_weight_t &de_weight,
                             const bsl::hashmap<int, int> &deweight_singer)
    {
        if(NULL == p_song){
            WARNING_LOG("wrong param");
            return;
        }
        const Song_brief_t* p_brief = _dict_seeker->get_song_brief(p_song->song_id);
        if(NULL == p_brief){
            //WARNING_LOG("pass_deweight faild for null Song_brief_t");
            return;
        }
        int value;
#ifdef _DEBUG_TIME
        DEBUG_LOG("start pass_deweight,[songid:%u][weight:%d]", p_song->song_id, p_song->weight);
#endif
        if(deweight_singer.get(p_brief->singer_id, &value) == bsl::HASH_EXIST){
            p_song->weight = p_song->weight * JUMP_DEWEIGHT_PERCENT /MAX_PERCENT;
        }
        if(de_weight.de_lan){
            if(p_brief->lang == de_weight.lan){
                p_song->weight = p_song->weight * JUMP_DEWEIGHT_PERCENT /MAX_PERCENT;
            }
        }
        if(de_weight.de_pv){
            if(p_brief->pv == de_weight.pv){
                p_song->weight = p_song->weight * JUMP_DEWEIGHT_PERCENT /MAX_PERCENT;
            }
        }
        if(de_weight.de_year){
            if(p_brief->year == de_weight.year){
                p_song->weight = p_song->weight * JUMP_DEWEIGHT_PERCENT /MAX_PERCENT;
            }
        }
#ifdef _DEBUG_TIME
        DEBUG_LOG("finish pass_deweight,[songid:%u][weight:%d]", p_song->song_id, p_song->weight);
#endif
    }

    void RAl::_pass_upweight(Song_item_t* p_song){
        if(NULL == p_song){
            WARNING_LOG("wrong param");
            return;
        }
        const Song_brief_t* p_brief = _dict_seeker->get_song_brief(p_song->song_id);
        if(NULL == p_brief){
            //WARNING_LOG("pass_upweight faild for null Song_brief_t");
            return;
        }
        //高PV提权
        int curr_score;
        if(p_brief->pv == FIRST_PV_FLAG || p_brief->pv == SECOND_PV_FLAG || p_brief->pv == THIRD_PV_FLAG){
            if(p_song->weight == 0){
                curr_score = BASE_SCORE;
            }
            else{
                curr_score = p_song->weight;
            }
            p_song->weight = curr_score * (MAX_PERCENT + g_config.high_pv_upweight) / MAX_PERCENT;
        }
#ifdef _DEBUG_TIME
        DEBUG_LOG("finish pass_upweight,[songid:%u][weight:%d]", p_song->song_id, p_song->weight);
#endif
    }

    /**
    * 从相关歌曲中topn的随机抽取一个
    * [in]
    * p_song_song 相关歌曲
    * song_song_len 相关歌曲长度
    * u_buf 用户命令buf
    *  filt_dict 过滤字典
    *
    * return not null 成功 null失败
    */
    Song_item_t* RAl::song_topN_rand(Song_item_t *p_song_song, int song_song_len,
                                     bsl::mempool &pool , sodict_build_t *filt_dict)
    {
        if(p_song_song == NULL || song_song_len <=0){
            WARNING_LOG("p_song_song[%p] == NULL || song_song_len[%d] <= 0", p_song_song, song_song_len);
            return NULL;
        }
        int rand_index,i;
        int heap_len = song_song_len > SONG_RAND_TOPN ? SONG_RAND_TOPN : song_song_len;
        int heap_size = 0;
        //相关歌曲的top20-rand-1
        Song_item_t** p_heap_buf = (Song_item_t**)(pool.malloc(sizeof(Song_item_t*) * heap_len));
        if (!p_heap_buf){
            FATAL_LOG("faild to alloc mem for topN heap");
            return NULL;
        }
        bzero(p_heap_buf, sizeof(Song_item_t*) * heap_len);

        for (i = 0; heap_size < heap_len && i < song_song_len; ++i){
            if(!_dict_seeker->filt_song(filt_dict,p_song_song[i].song_id)){
                p_heap_buf[heap_size++] = p_song_song + i;
            }
        }
        std::make_heap(p_heap_buf, p_heap_buf + heap_size, song_item_weight_cmp);
        for (; i < song_song_len; ++i){
            if(!_dict_seeker->filt_song(filt_dict,p_song_song[i].song_id)){
                topN_put(p_heap_buf, heap_size, p_song_song + i, song_item_weight_cmp);
            }
        }
        rand_index = (int) ((double) heap_size * rand() / (RAND_MAX + 1.0));
        Song_item_t* p_rand_res1 = p_heap_buf[rand_index];
        pool.free(p_heap_buf, sizeof(Song_item_t*) * heap_len);
        return p_rand_res1;
    }

    /**
    *  融合推荐列表
    *  [in]
    *  uid
    *  ch_name 频道名
    *  filter_dict过滤字典
    *  max_len 返回列表的最大长度
    *  r_len推荐列表的长度
    *  r_song_list推荐列表
    *  f_list 待融合的列表
    *  pool 内存池
    */
    int RAl::gen_fuse_rlist(uint uid, const char* ch_name,
                            const sodict_build_t* filter_dict,
                            uint max_len,
                            uint &r_len, Song_item_t* r_song_list, fuse_list_t *f_list,
                            User_tag_t * utag_list, int tag_len,
                            const r_userdata_t &user_data,
                            bsl::mempool &pool)
    {
        struct timeval s;
        struct timeval e;
        gettimeofday(&s, NULL);
        int ret = 0;
        //获取长尾好歌歌曲列表
        int tail_list_len = 0;
        Song_item_t * tail_list = (Song_item_t *) pool.malloc(sizeof(Song_item_t) * CF_LIST_MAX_LEN);
        //特征歌曲评分数据
        std::vector<int> score_v(FEATURE_SONG_NUM, 0);
        std::vector<int> normal_v(FEATURE_SONG_NUM, 0);
#ifdef _DEBUG_TIME
        DEBUG_LOG("instant ch_name[%s], score_v begin:", ch_name);
        for(int i = 0; i < FEATURE_SONG_NUM; ++i){
            DEBUG_LOG("instant score_v begin: pos[%d], weight[%d], normal_v[%d]", i, score_v[i], normal_v[i]);
        }
#endif
        _gen_feature_weight(user_data, score_v, normal_v);
#ifdef _DEBUG_TIME
        DEBUG_LOG("instant ch_name[%s], score_v end:", ch_name);
        for(int i = 0; i < FEATURE_SONG_NUM; ++i){
            DEBUG_LOG("instant score_v end: pos[%d], weight[%d], normal_v[%d]", i, score_v[i], normal_v[i]);
        }
#endif
        double lr_weight = 0;
        uint song_id = 0;
        uint lr_weight_pos = 0;
        uint lr_label_num = 0;
        double lr_predict_weight = 0;
        int pos = 0;
        tail_song_t tail_item;
        for(uint i = 0; i < RAN_TAIL_NUM; ++i){
            pos = rand() % p_global.max_tail_song_list_len;
            song_id = p_global.tail_song_list[pos].song_id;
            //过滤
            if(_dict_seeker->filt_song(filter_dict, song_id)){
                continue;
            }
            lr_weight = 0;
            ret = _dict_seeker->seek_lrmodel_pos(song_id, lr_weight_pos, lr_label_num);
            if(ret < 0){
                TRACE_LOG("song_id[%d] no lrmodel", song_id);
                continue;
            }
            if(lr_weight_pos + FEATURE_NUM > p_global.max_lrweight_list_len){
                WARNING_LOG("wrong lr_weight_pos[%u], song_id[%u]", lr_weight_pos, song_id);
                continue;
            }
            for(int j = 0; j < FEATURE_SONG_NUM; ++j){
                lr_weight += p_global.lrweight_list[lr_weight_pos + normal_v[j]];
            }
            lr_predict_weight = 1./(1 + exp(-lr_weight)) * 1000000;
            if(lr_predict_weight > p_global.tail_song_list[pos].weight){
                tail_list[tail_list_len].song_id = song_id;
                tail_list[tail_list_len].source = TAIL_SOURCE;
                tail_list[tail_list_len].weight = 0; //不使用权值, 不彼此排序
                tail_list_len++;
            }
        }
#ifdef _DEBUG_TIME
        DEBUG_LOG("private list uid[%d], got tail song len[%d]", uid, tail_list_len);
        for(int i = 0; i < tail_list_len; i++){
            DEBUG_LOG("tail tail_list [position:%d][song_id:%d][weight:%d][source:%d]", i, tail_list[i].song_id, tail_list[i].weight, tail_list[i].source);
        }
#endif

        //整合三个列表
        uint max_rlen = max_len;//列表长度限制
        //uint fuse_list_song_num = (FUSE_LIST_NUM-1)*CF_LIST_MAX_LEN + max_len;
        uint fuse_list_song_num = 0;//所有列表歌曲总数
        for(uint i = 0; i < FUSE_LIST_NUM; i ++){
            fuse_list_song_num += f_list->fuse_list_len[i];
        }
        bsl::hashmap <uint, Song_item_t>list_map;
        list_map.create(fuse_list_song_num);
        gen_map_for_common_fuselist(f_list, FUSE_LIST_NUM, max_len,
                fuse_list_song_num, filter_dict, list_map);

        /*
        Song_item_t *tmp_item = (Song_item_t *) pool.malloc(sizeof(Song_item_t));
        for(int i = 0; i < FUSE_LIST_NUM; i++){
            //j循环遍历当前列表，v表示valid位置
            int v = 0;
            for(int j = 0; j < f_list->fuse_list_len[i]; j++){
                //过滤
                if(_dict_seeker->filt_song(filter_dict, f_list->fuse_list[i][j].song_id)){
                    continue;
                }
                if(list_map.get(f_list->fuse_list[i][j].song_id, tmp_item)==bsl::HASH_EXIST){
                    if(tmp_item->weight < (g_config.fuse_rate * f_list->fuse_list_weight[i])/(1+v)){
                        tmp_item->weight = (g_config.fuse_rate * f_list->fuse_list_weight[i]/(1+v));
                    }
                    tmp_item->source |= f_list->fuse_list[i][j].source;
                }
                else{
                    tmp_item->weight =(g_config.fuse_rate * f_list->fuse_list_weight[i]/(1+v));
                    tmp_item->source = f_list->fuse_list[i][j].source;
                }
                v++;
                tmp_item->song_id = f_list->fuse_list[i][j].song_id;
                list_map.set(tmp_item->song_id,*tmp_item, 1);
            }
        }
        */

        /***长尾歌曲，暂不加入
        int v = 0;
        for(int j = 0; j < tail_list_len; j++){
            if(list_map.get(tail_list[j].song_id, tmp_item)==bsl::HASH_EXIST){
                if(tmp_item->weight < g_config.fuse_rate/(1+v)){
                    tmp_item->weight = g_config.fuse_rate/(1+v);
                }
                tmp_item->source |= tail_list[j].source;
            }
            else{
                tmp_item->weight = g_config.fuse_rate/(1+v);
                tmp_item->source |= tail_list[j].source;
            }
            v++;
            tmp_item->song_id = tail_list[j].song_id;
            list_map.set(tmp_item->song_id,*tmp_item, 1);
        }
        */

        //用户模型调权
#ifdef _DEBUG_TIME
        DEBUG_LOG("private list before um change weight");
        int tmp_i = 0;
        for(bsl::hashmap <uint, Song_item_t>::iterator iter =  list_map.begin(); iter !=list_map.end(); iter++ ){
            tmp_i++;
            DEBUG_LOG("the list is [position:%d][song_id:%d][weight:%d][source:%d]", tmp_i, iter->second.song_id, iter->second.weight, iter->second.source);
        }
#endif
        if(tag_len > 0){
            uint tmp_song_id = 0;
            uint tmp_source = 0;
            int tmp_weight = 0;
            for(bsl::hashmap <uint, Song_item_t>::iterator iter =  list_map.begin(); iter !=list_map.end(); iter++ ){
                tmp_source = iter->second.source;
                //判断是否有用户模型来源
                if ((tmp_source & USERMODELLIST_SOURCE) != 0){
                    continue;
                }
                tmp_song_id = iter->second.song_id;
                tmp_weight = MAX_UTAG_WEIGHT;
                for(int i = 0; i < tag_len; i++){
                    if(_dict_seeker->has_song_tag(tmp_song_id, utag_list[i].tag_id)){
                        tmp_weight += (utag_list[i].tag_weight * g_config.um_change_weight)/MAX_UTAG_WEIGHT;
#ifdef _DEBUG_TIME
                        DEBUG_LOG("a song tag, song_id[%d], weight[%d], tag_id[%d], tmp_weight[%d], tag_weight[%d]",
                                  tmp_song_id, iter->second.weight, utag_list[i].tag_id, tmp_weight, utag_list[i].tag_weight);
#endif
                    }
                }
                //是否需要标记用户模型调权
                if (tmp_weight == MAX_UTAG_WEIGHT){
                    continue;
                }
                iter->second.source |= USERMODEL_SOURCE;
                iter->second.weight = (iter->second.weight * tmp_weight)/MAX_UTAG_WEIGHT;
            }
        }
        else{
            WARNING_LOG("tag list len[%d] <= 0, no need to um change weight", tag_len);
        }
#ifdef _DEBUG_TIME
        DEBUG_LOG("private list after um change weight");
        tmp_i = 0;
        for(bsl::hashmap <uint, Song_item_t>::iterator iter =  list_map.begin(); iter !=list_map.end(); iter++ ){
            tmp_i++;
            DEBUG_LOG("the list is [position:%d][song_id:%d][weight:%d][source:%d]", tmp_i, iter->second.song_id, iter->second.weight, iter->second.source);
        }
#endif

        //取top N
        get_topn_from_map(list_map, r_song_list, r_len, max_len);
        /*r_len = 0;
        bsl::hashmap <uint, Song_item_t>::iterator iter =  list_map.begin();
        while(r_len < max_len){
            for( ; iter !=list_map.end() && r_len < max_len; iter++){
                r_song_list[r_len]= iter->second;
                r_len ++;
            }
            if(iter == list_map.end()){
                break;
            }
        }
        std::make_heap(r_song_list, r_song_list + r_len, list_item_weight_cmp);
        for( ; iter !=list_map.end(); iter++){
            topN_put(r_song_list, r_len, iter->second, list_item_weight_cmp);
        }
        //权值归一
        if (r_len > 0){
            //sort 融合后的列表
            sort_songlist(r_song_list, r_len);
            //由1/10,将权值映射为0-100
            int tmp_middle = r_song_list[r_len/10].weight;
            if (tmp_middle <= 0){
                tmp_middle = 1;
            }
            for(uint i = 0; i < r_len; i++){
                float tmp_weight = (float(r_song_list[i].weight))/tmp_middle;
                r_song_list[i].weight = int (100*tanh(tmp_weight));
            }
        }*/
        //释放空间返回
        //pool.free(tmp_item,sizeof(Song_item_t));
        pool.free(tail_list, sizeof(Song_item_t) * CF_LIST_MAX_LEN);
        list_map.destroy();
        return r_len;
    }

    int RAl::gen_newuser_fuselist(Song_item_t *ldac_list, Song_item_t* bpr_list, Song_item_t *instant_list,
                                    uint ldac_list_len, uint bpr_list_len, uint instant_list_len, Song_item_t *r_song_list,
                                    uint &r_song_len, uint max_len){
        if(NULL == ldac_list && NULL == instant_list && NULL == bpr_list){
            WARNING_LOG("wrong param in gen_newuser_fuselist");
            return FAIL;
        }

        fuse_list_t* f_list= (fuse_list_t*) malloc(sizeof(fuse_list_t));
        if(NULL == f_list){
            WARNING_LOG("malloc for f_list fail");
            return FAIL;
        }

        f_list->fuse_list_weight[0] = 1;
        f_list->fuse_list[0] = ldac_list;
        f_list->fuse_list_len[0] = ldac_list_len;
        f_list->fuse_list_weight[1] = 1;
        f_list->fuse_list[1] = instant_list;
        f_list->fuse_list_len[1] = instant_list_len;
        f_list->fuse_list_weight[2] = 1;
        f_list->fuse_list[2] = bpr_list;
        f_list->fuse_list_len[2] = bpr_list_len;

        gen_common_fuselist(f_list, 2, max_len, r_song_list, r_song_len);
        if(r_song_len > 0){
            for(uint i = 0; i < r_song_len; i ++){
                r_song_list[i].source |= NEWUSER_SOURCE;
            }
        }

        free(f_list);
        return r_song_len;
    }

    int RAl::gen_recommend_fuselist(Song_item_t *itemsim_list, Song_item_t* redis_list,
                                    uint itemsim_list_len, uint redis_list_len, Song_item_t *r_song_list,
                                    uint &r_song_len, uint max_len){
        if(NULL == redis_list && NULL == itemsim_list){
            WARNING_LOG("wrong param in gen_recommend_fuselist");
            return FAIL;
        }

        fuse_list_t* f_list= (fuse_list_t*) malloc(sizeof(fuse_list_t));
        if(NULL == f_list){
            WARNING_LOG("malloc for f_list fail");
            return FAIL;
        }

        f_list->fuse_list_weight[0] = 1;
        f_list->fuse_list[0] = itemsim_list;
        f_list->fuse_list_len[0] = itemsim_list_len;
        f_list->fuse_list_weight[1] = 1;
        f_list->fuse_list[1] = redis_list;
        f_list->fuse_list_len[1] = redis_list_len;

        gen_common_fuselist(f_list, 2, max_len, r_song_list, r_song_len);

        free(f_list);
        return r_song_len;
    }

    int RAl::gen_public_fuselist(Song_item_t *redis_list, Song_item_t *instant_list,
                                    uint redis_list_len, uint instant_list_len, Song_item_t *r_song_list,
                                    uint &r_song_len, uint max_len){
        if(NULL == redis_list && NULL == instant_list){
            WARNING_LOG("redis_list and instant_list are null both");
            return 0;
        }

        fuse_list_t* f_list= (fuse_list_t*) malloc(sizeof(fuse_list_t));
        if(NULL == f_list){
            WARNING_LOG("malloc for f_list fail");
            return FAIL;
        }

        f_list->fuse_list_weight[0] = 1;
        f_list->fuse_list[0] = redis_list;
        f_list->fuse_list_len[0] = redis_list_len;
        f_list->fuse_list_weight[1] = 1;
        f_list->fuse_list[1] = instant_list;
        f_list->fuse_list_len[1] = instant_list_len;

        gen_common_fuselist(f_list, 2, max_len, r_song_list, r_song_len);

        free(f_list);
        return r_song_len;
    }

    int RAl::gen_common_fuselist(fuse_list_t *f_list, uint fuse_list_len, uint max_len, Song_item_t *r_song_list, uint &r_song_len, const sodict_build_t* filter_dict){
        if(NULL == f_list || fuse_list_len <= 0){
            WARNING_LOG("wrong param in common_fuselist");
            return FAIL;
        }

        uint fuse_list_song_num = 0;//所有列表歌曲总数
        for(uint i = 0; i < fuse_list_len; i ++){
            fuse_list_song_num += f_list->fuse_list_len[i];
        }

        bsl::hashmap <uint, Song_item_t> list_map;
        list_map.create(fuse_list_song_num);
        gen_map_for_common_fuselist(f_list, fuse_list_len, max_len,
                fuse_list_song_num, filter_dict, list_map);
        if(list_map.size() <= 0){
            list_map.destroy();
            return FAIL;
        }

        get_topn_from_map(list_map, r_song_list, r_song_len, max_len);
        list_map.destroy();
        return r_song_len;
    }

    int RAl::gen_map_for_common_fuselist(fuse_list_t *f_list, uint fuse_list_len,
            uint max_len, uint fuse_list_song_num, const sodict_build_t* filter_dict,
            bsl::hashmap <uint, Song_item_t> &list_map){
        if(NULL == f_list){
            WARNING_LOG("wrong params");
            return FAIL;
        }

        struct timeval s;
        struct timeval e;
        gettimeofday(&s,NULL);

        int weights[fuse_list_len];
        uint i, j;
        weights[0] = f_list->fuse_list_weight[0];
        for(i = 1; i < fuse_list_len; i ++){
            weights[i] = f_list->fuse_list_weight[i] + weights[i - 1];
        }

        Song_item_t *tmp_list = NULL;
        uint tmp_list_len = 0;
        for(i = 0; i < fuse_list_len; i ++){
            tmp_list = f_list->fuse_list[i];
            tmp_list_len = f_list->fuse_list_len[i];
            if(tmp_list_len <= 0){
                continue;
            }

            tmp_list[0].weight = tmp_list_len;
            for(j = 1; j < tmp_list_len; j ++){
                tmp_list[j].weight = tmp_list[j - 1].weight + tmp_list_len / (j + 1);
            }
        }

        float rand_list_weight = 0.0;
        float rand_song_weight = 0.0;
        uint rand_list_index = 0;
        uint loop_time = max_len > fuse_list_song_num ? (fuse_list_song_num * 30) : (max_len * 30);
        Song_item_t *tmp_item = (Song_item_t *)malloc(sizeof(Song_item_t));
        for(i = 0; i < loop_time; i ++){
            rand_list_weight = weights[fuse_list_len - 1] * (rand() / (RAND_MAX + 1.0));

            for(j = 0; j < fuse_list_len; j ++){
                if(weights[j] > rand_list_weight){
                    rand_list_index = j;
                    break;
                }
            }


            tmp_list = f_list->fuse_list[rand_list_index];
            tmp_list_len = f_list->fuse_list_len[rand_list_index];

            if(tmp_list_len <= 0){
                continue;
            }

            rand_song_weight = tmp_list[tmp_list_len - 1].weight * (rand() / (RAND_MAX + 1.0));

            for(j = 0; j < tmp_list_len; j ++){
                if(tmp_list[j].weight > rand_song_weight){
                    if(_dict_seeker->filt_song(filter_dict, tmp_list[j].song_id)){
                        continue;
                    }

                    if(list_map.get(tmp_list[j].song_id, tmp_item) == bsl::HASH_EXIST){
                        tmp_item->weight ++;
                        tmp_item->source |= tmp_list[j].source;
                    }else{
                        tmp_item->weight = 1;
                        tmp_item->source = tmp_list[j].source;
                    }

                    tmp_item->song_id = tmp_list[j].song_id;
                    list_map.set(tmp_item->song_id, *tmp_item, 1);

                    break;
                }
            }
        }

        if(NULL != tmp_item){
            free(tmp_item);
        }

        gettimeofday(&e, NULL);
        NOTICE_LOG("gen list_map cost[%d], list_len is [%d]", TIMEMSECDIFF(s, e), fuse_list_len);
        return SUCCESS;
    }

    int RAl::get_topn_from_map(const bsl::hashmap<uint, Song_item_t> &list_map, Song_item_t *r_song_list, uint &r_song_len, uint max_len){
        if(NULL == r_song_list || list_map.size() == 0){
            WARNING_LOG("wrong params in get_topn");
            return 0;
        }

        r_song_len = 0;
        bsl::hashmap <uint, Song_item_t>::const_iterator iter = list_map.begin();
        if(r_song_len < max_len){
            for(; iter != list_map.end() && r_song_len < max_len; iter ++){
                r_song_list[r_song_len] = iter->second;
                r_song_len ++;
            }
        }

        std::make_heap(r_song_list, r_song_list + r_song_len, list_item_weight_cmp);
        for(; iter != list_map.end(); iter ++){
            topN_put(r_song_list, r_song_len, iter->second, list_item_weight_cmp);
        }

        if(r_song_len > 0){
            sort_songlist(r_song_list, r_song_len);
            //由1/10,将权值映射为0-100
            int tmp_middle = r_song_list[r_song_len/10].weight;
            if (tmp_middle <= 0){
                tmp_middle = 1;
            }
            for(uint i = 0; i < r_song_len; i++){
                float tmp_weight = (float(r_song_list[i].weight))/tmp_middle;
                r_song_list[i].weight = int (100*tanh(tmp_weight));
            }
        }

        return r_song_len;
    }

    int RAl::get_instantlist(const song_id_t* song_list, uint song_len,
                             Song_item_t* r_song_list, uint &r_song_len,
                             const r_userdata_t &user_data,
                             uint max_len, const sodict_build_t* filter_dict,
                             char * ch_name)
    {
        if(NULL == song_list || NULL == r_song_list){
            WARNING_LOG("wrong param in get_randomlist");
            return FAIL;
        }
        if(song_len <= 0){
            WARNING_LOG("song list len <= 0");
            return FAIL;
        }
        NOTICE_LOG("begin to gen instant list, ch_name[%s]", ch_name);

        int ret = 0;

        //特征歌曲评分数据
        std::vector<int> score_v(FEATURE_SONG_NUM, 0);
        std::vector<int> normal_v(FEATURE_SONG_NUM, 0);
#ifdef _DEBUG_TIME
        DEBUG_LOG("instant ch_name[%s], score_v begin:", ch_name);
        for(int i = 0; i < FEATURE_SONG_NUM; ++i){
            DEBUG_LOG("instant score_v begin: pos[%d], weight[%d], normal_v[%d]", i, score_v[i], normal_v[i]);
        }
#endif
        _gen_feature_weight(user_data, score_v, normal_v);
#ifdef _DEBUG_TIME
        DEBUG_LOG("instant ch_name[%s], score_v end:", ch_name);
        for(int i = 0; i < FEATURE_SONG_NUM; ++i){
            DEBUG_LOG("instant score_v end: pos[%d], weight[%d], normal_v[%d]", i, score_v[i], normal_v[i]);
        }
#endif

        //即时列表
        Song_item_t i_song_list[MAX_INSTANT_LIST_LEN];
        uint i_song_len = 0;
        uint loop_len = 3;
        bsl::hashmap<uint, uint> rdata;
        rdata.create(max_len); //去重字典
        uint value;
        uint r = 0;
        uint step = ceil((song_len * 1.0)/MAX_INSTANT_LIST_LEN);
        uint list_area = 0;
        for(uint i = 0; i < song_len && i < MAX_INSTANT_LIST_LEN; ++i){
            for(uint j = 0; j < loop_len; ++j){
                list_area = (step * (i + 1)) > song_len ? song_len : (step * (i + 1));
                r = rand() % list_area;
                ret = rdata.get(r, &value);
                if(ret == bsl::HASH_NOEXIST){
                    rdata.set(r, 0);
                    //过滤
                    if(_dict_seeker->filt_song(filter_dict, song_list[r].sid)){
                        continue;
                    }
                    i_song_list[i_song_len].song_id = song_list[r].sid;
                    i_song_list[i_song_len].source = INSTANT_SOURCE;
                    i_song_list[i_song_len].weight = 0;
                    i_song_len++;
                    break;
                }
            }
        }
        rdata.destroy();
        //填充pcpr权值
        double lr_weight = 0;
        uint song_id = 0;
        uint lr_weight_pos = 0;
        uint lr_label_num = 0;
        double lr_predict_weight = 0;
        double lr_confidence = 0;
        for(uint i = 0; i < i_song_len; ++i){
            lr_weight = 0;
            song_id = i_song_list[i].song_id;
            ret = _dict_seeker->seek_lrmodel_pos(song_id, lr_weight_pos, lr_label_num);
            if(ret < 0){
                TRACE_LOG("song_id[%d] no lrmodel", song_id);
                continue;
            }
            if(lr_weight_pos + FEATURE_NUM > p_global.max_lrweight_list_len){
                WARNING_LOG("wrong lr_weight_pos[%u], song_id[%u]", lr_weight_pos, song_id);
                continue;
            }
            for(int j = 0; j < FEATURE_SONG_NUM; ++j){
                lr_weight += p_global.lrweight_list[lr_weight_pos + normal_v[j]];
            }
            lr_predict_weight = 1./(1 + exp(-lr_weight));
            lr_confidence = (lr_label_num * 1.0)/PCPR_CONFIDENCE > 1 ? 1 : (lr_label_num * 1.0)/PCPR_CONFIDENCE;
            i_song_list[i].weight = (int) (lr_predict_weight * 10000 * lr_confidence);
        }

#ifdef _DEBUG_TIME
        for(int i = 0; i < i_song_len; i ++){
            DEBUG_LOG("the instant oringal: position[%d], songid[%d], weight[%d], source[%d]", \
                      i, i_song_list[i].song_id, i_song_list[i].weight, i_song_list[i].source);
        }
#endif
        //按照权重排序
        this->sort_songlist(i_song_list, i_song_len);
        if(i_song_len < max_len){
            r_song_len = i_song_len;
            memcpy(r_song_list, i_song_list, sizeof(Song_item_t) * r_song_len);
        }
        else{
            r_song_len = max_len;
            memcpy(r_song_list, i_song_list, sizeof(Song_item_t) * r_song_len);
        }
        return SUCCESS;
    }


    int RAl::_gen_feature_weight(const r_userdata_t &user_data, std::vector<int> &score_v, std::vector<int> &normal_v){
        int pos = 0;
#ifdef _DEBUG_TIME
        DEBUG_LOG("instant ch_name, score_v begin.");
        for(int i = 0; i < FEATURE_SONG_NUM; ++i){
            DEBUG_LOG("instant score_v begin: pos[%d], weight[%d], normal_v[%d]", i, score_v[i], normal_v[i]);
        }
#endif
        //用户中心加心歌曲
        for(int i = 0; i < user_data.len_songlove; ++i){
            pos = _dict_seeker->seek_feature_pos(user_data.songlove[i].itemid);
            if(pos >= FEATURE_SONG_NUM || pos < 0){
                continue;
            }
            score_v[pos] += g_config.WConf.fm_heartso_w;
        }
        //垃圾桶歌曲
        for(int i = 0; i < user_data.len_songhate; ++i){
            pos = _dict_seeker->seek_feature_pos(user_data.songhate[i].itemid);
            if(pos >= FEATURE_SONG_NUM || pos < 0){
                continue;
            }
            score_v[pos] += g_config.WConf.fm_hateso_w;
        }
        //云收藏歌曲
        for(int i = 0; i < user_data.len_songcloud; ++i){
            pos = _dict_seeker->seek_feature_pos(user_data.songcloud[i].itemid);
            if(pos >= FEATURE_SONG_NUM || pos < 0){
                continue;
            }
            score_v[pos] += g_config.WConf.fm_cloudso_w;
        }
        //试听历史
        for(int i = 0; i < user_data.len_listenhistory; ++i){
            pos = _dict_seeker->seek_feature_pos(user_data.listenhistory[i].itemid);
            if(pos >= FEATURE_SONG_NUM || pos < 0){
                continue;
            }
            score_v[pos] += g_config.WConf.fm_listenend_w;
        }
        //试听行为(包括在电台的行为和在百度音乐的行为)
        enum DB_USER_BEHAVIOR_TYPE db_type_behavior;
        for(int i = 0; i < user_data.len_action; ++i){
            pos = _dict_seeker->seek_feature_pos(user_data.action[i].itemid);
            if(pos >= FEATURE_SONG_NUM || pos < 0){
                continue;
            }
            db_type_behavior = (enum DB_USER_BEHAVIOR_TYPE) user_data.action[i].type;
            switch (db_type_behavior){
                case DB_SEARCH_SONG:
                    score_v[pos] += g_config.WConf.mb_searchso_w;
                    break;
                case DB_BOX_COMPLETE_TYPE:
                    score_v[pos] += g_config.WConf.mb_listenend_w;
                    break;
                case DB_NEXT_SONG:
                    score_v[pos] += g_config.WConf.fm_jumpso_w;
                    break;
                case DB_PRE_SONG:
                    score_v[pos] += g_config.WConf.fm_jumpprior_w;
                    break;
                default:
                    break;
            }
        }
        for(int i = 0; i < FEATURE_SONG_NUM; ++i){
            if(score_v[i] > 0){
                normal_v[i] = 3 * i;
            }
            else if(score_v[i] < 0){
                normal_v[i] = 3 * i + 1;
            }
            else{
                normal_v[i] = 3 * i + 2;
            }
        }
#ifdef _DEBUG_TIME
        DEBUG_LOG("instant ch_name, score_v end.");
        for(int i = 0; i < FEATURE_SONG_NUM; ++i){
            DEBUG_LOG("instant score_v end: pos[%d], weight[%d], normal_v[%d]", i, score_v[i], normal_v[i]);
        }
#endif
        return SUCCESS;
    }


    int RAl::get_y_list(const song_id_t* song_list, uint song_len,
                             Song_item_t* r_song_list, uint &r_song_len,
                             const y_user_data_t &user_data,
                             uint max_len, const sodict_build_t* filter_dict,
                             char * ch_name)
    {
        if(NULL == song_list || NULL == r_song_list){
            WARNING_LOG("wrong param in get_y_list");
            return FAIL;
        }
        if(song_len <= 0){
            WARNING_LOG("song list len <= 0");
            return FAIL;
        }
        NOTICE_LOG("begin to gen y list, ch_name[%s]", ch_name);

        int ret = 0;

        //即时列表
        Song_item_t i_song_list[MAX_INSTANT_LIST_LEN];
        uint i_song_len = 0;
        uint loop_len = 3;
        bsl::hashmap<uint, uint> rdata;
        rdata.create(max_len); //去重字典
        uint value;
        uint r = 0;
        uint step = ceil((song_len * 1.0)/MAX_INSTANT_LIST_LEN);
        uint list_area = 0;
        for(uint i = 0; i < song_len && i < MAX_INSTANT_LIST_LEN; ++i){
            for(uint j = 0; j < loop_len; ++j){
                list_area = (step * (i + 1)) > song_len ? song_len : (step * (i + 1));
                r = rand() % list_area;
                ret = rdata.get(r, &value);
                if(ret == bsl::HASH_NOEXIST){
                    rdata.set(r, 0);
                    //过滤
                    if(_dict_seeker->filt_song(filter_dict, song_list[r].sid)){
                        continue;
                    }
                    i_song_list[i_song_len].song_id = song_list[r].sid;
                    i_song_list[i_song_len].source = 0;
                    i_song_list[i_song_len].weight = 0;
                    i_song_len++;
                    break;
                }
            }
        }
        rdata.destroy();

#ifdef _DEBUG_TIME
        for(int i = 0; i < i_song_len; i ++){
            DEBUG_LOG("the instant oringal: position[%d], songid[%d], weight[%d], source[%d]", \
                      i, i_song_list[i].song_id, i_song_list[i].weight, i_song_list[i].source);
        }
#endif

        if(i_song_len < max_len){
            r_song_len = i_song_len;
            memcpy(r_song_list, i_song_list, sizeof(Song_item_t) * r_song_len);
        }
        else{
            r_song_len = max_len;
            memcpy(r_song_list, i_song_list, sizeof(Song_item_t) * r_song_len);
        }
        return SUCCESS;
    }
}

