/*=============================================================================
#     FileName: rls_rgen.cpp
#         Desc: 推荐列表生成
#       Author: wensaiping
#        Email: wensaiping@baidu.com
#     HomePage:
#      Version: 1.0.1
#   LastChange: 2013-08-06 13:47:57
#      History:
=============================================================================*/
#include "rls_rgen.h"
#include "ul_sign.h"
#include "mcCache.h"

namespace rls{

    RGen::RGen(){
        _ral = new RAl();
        _rstrategy = new RStrategy();
    }

    RGen::~RGen(){
        if(NULL != _ral){
            delete _ral;
        }
        if(NULL != _rstrategy){
            delete _rstrategy;
        }
    }

    int RGen::gen_simple_list(const char* ch_name,Song_item_t* r_song_list,
                              uint max_len, const r_userdata_t &user_data, uint &r_song_len)
    {
        if(NULL == ch_name || NULL == r_song_list || max_len <= 0){
            WARNING_LOG("wrong param in gen_simple_colist");
            return FAIL;
        }
        int ret;
        sodict_snode_t node;
        char ch_name_temp[MAX_CHNAME_LEN];
        r_song_len = 0;
        sodict_build_t* filter_dict = odb_creat(FILT_DICT_HASH);
        if (!filter_dict){
            WARNING_LOG("creat odict faild");
            return -1;
        }
        //填充过滤歌曲
        _dict_seeker->fill_hate_dict(user_data, filter_dict);
        snprintf(ch_name_temp, MAX_CHNAME_LEN, "%s", ch_name);
        uint ch_sign = creat_sign32(ch_name_temp);
        node.sign1 = ch_sign;
        node.sign2 = CHANNEL_SONG_DICT;
        ret = odb_seek_search(p_global.bigDict, &node);
        if (ret == ODB_SEEK_ERROR){
            WARNING_LOG("seek bigDict faild[ret:%d][sign1:%u][sign2:%u]", ret, node.sign1, node.sign2);
            if (filter_dict){
                odb_destroy(filter_dict);
            }
            return FAIL;
        }
        if (ret == ODB_SEEK_FAIL){
                TRACE_LOG("no matching found in bigDict[ret:%d][sign1:%u][sign2:%u]", ret, node.sign1,
                          node.sign2);
            if (filter_dict){
                odb_destroy(filter_dict);
            }
            return NOEXIST;
        }
        if (node.cuint1 + node.cuint2 > p_global.max_chsonglist_len){
            WARNING_LOG("bad pos[%u] len[%u] for song-song buf. max len[%u]",
                        node.cuint1, node.cuint2, p_global.max_chsonglist_len);
            if (filter_dict){
                odb_destroy(filter_dict);
            }
            return FAIL;
        }
        song_id_t* chsong_list = p_global.ch_song_list + node.cuint1;
        uint32_t chsong_len = node.cuint2;
        ret = _ral->get_simplelist(chsong_list, chsong_len,
                                   r_song_list, r_song_len, max_len, filter_dict);
        if(ret == FAIL){
            WARNING_LOG("get_simplelist fail");
            if (filter_dict){
                odb_destroy(filter_dict);
            }
            return FAIL;
        }
        //按照权重排序
        _ral->sort_songlist(r_song_list, r_song_len);
        //插入推广歌曲
        this->_spread_sond(ch_name, r_song_list, r_song_len, max_len, filter_dict);
        if (filter_dict){
            odb_destroy(filter_dict);
        }
        return SUCCESS;
    }

    int RGen::gen_tag_list(Song_item_t* r_song_list, uint max_len,
                           uint &r_song_len, const r_userdata_t &user_data,
                           char* tag_word, UscGetter *usc_getter){
        if(NULL == r_song_list || NULL == tag_word){
            WARNING_LOG("null parameter");
            return FAIL;
        }
        int ret;
        r_song_len = 0;
        sodict_build_t* filter_dict = odb_creat(FILT_DICT_HASH);
        if (!filter_dict){
            WARNING_LOG("creat odict faild");
            return -1;
        }
        //填充过滤歌曲
        _dict_seeker->fill_hate_dict(user_data, filter_dict);
        //获得标签歌曲
        song_id_t tagsong[MAX_USER_LIST_LEN];
        uint len_tagsong = 0;
        ret = usc_getter->get_tagsong(tagsong, len_tagsong, tag_word, max_len);
        if(ret != 0 || len_tagsong == 0){
            WARNING_LOG("get tag song fail");
            if(filter_dict){
                odb_destroy(filter_dict);
            }
            return FAIL;
        }
        ret = _ral->get_simplelist(tagsong, len_tagsong,
                                   r_song_list, r_song_len,
                                   max_len, filter_dict);
        if(ret != SUCCESS){
            WARNING_LOG("get_simplelist fail");
            if(filter_dict){
                odb_destroy(filter_dict);
            }
            return FAIL;
        }
        //按照权重排序
        _ral->sort_songlist(r_song_list, r_song_len);
        if (filter_dict){
            odb_destroy(filter_dict);
        }
        return SUCCESS;
    }

    int RGen::gen_lovesong_list(Item_bean* items, uint len_items, Song_item_t* r_song_list,
                                uint max_len, uint &r_song_len)
    {
        if(NULL == items || NULL == r_song_list || max_len <= 0){
            WARNING_LOG("wrong param in gen_simple_colist");
            return FAIL;
        }
        //乱序
        std::random_shuffle(items, items + len_items);
        uint i;
        for(i = 0; i < len_items && i < max_len; i++){
            r_song_list[i].song_id = items[i].itemid;
            r_song_list[i].weight = 0;
            r_song_list[i].source = DEFAULT_SOURCE;
        }
        r_song_len = i;
        return SUCCESS;
    }

    int RGen::gen_recommend_list(const char* ch_name, uint baiduid, uint uid,
                                 Song_item_t* r_song_list, uint max_len,
                                 uint &r_song_len, const r_userdata_t &user_data,
                                 bool is_public, bool is_login, bsl::mempool &pool, int rf)
    {
        if(NULL == ch_name || NULL == r_song_list){
            WARNING_LOG("wrong param");
            return FAIL;
        }
        int ret = -1;
        sodict_build_t* filter_dict = odb_creat(FILT_DICT_HASH);
        if (!filter_dict){
            WARNING_LOG("creat odict faild");
            return -1;
        }
        //填充过滤歌曲
        _dict_seeker->fill_filter_dict(user_data, filter_dict);
        char ch_name_temp[MAX_CHNAME_LEN];
        snprintf(ch_name_temp, MAX_CHNAME_LEN, "%s", ch_name);
        //结果列表长度
        r_song_len = 0;

        DEBUG_LOG("start gen_indexmerge_rlist");
        Song_item_t instant_list[MAX_USER_LIST_LEN];
        uint instant_list_len = 0;
        /*ret = _ral->gen_indexmerge_rlist(user_data, ch_name,
                                         filter_dict, is_public,
                                         max_len, r_song_len,
                                         r_song_list, pool);*/
        ret = _ral->gen_indexmerge_rlist(user_data, ch_name,
                                         filter_dict, is_public,
                                         max_len, instant_list_len,
                                         instant_list, pool);
        if(ret != SUCCESS){
            //r_song_len = 0;
            instant_list_len = 0;
            WARNING_LOG("gen_indexmerge_rlist fail");
        }
        //DEBUG_LOG("end gen_indexmerge_rlist, r_len:%d", r_song_len);
        DEBUG_LOG("end gen_indexmerge_rlist, r_len:%d", instant_list_len);


        //gen random list
        Song_item_t redis_random_list[MAX_USER_LIST_LEN];
        uint redis_random_list_len = 0;
        ret = redis_get_random_list(redis_random_list, MAX_USER_LIST_LEN, redis_random_list_len, filter_dict);
        if(ret <= 0){
            redis_random_list_len = 0;
            NOTICE_LOG("get random list fail in suibiantingting, count[%d]", ret);
        }

        ret = _ral->gen_recommend_fuselist(instant_list, redis_random_list,
                instant_list_len, redis_random_list_len, r_song_list,
                r_song_len, max_len);
        if(ret <= 0){
            WARNING_LOG("gen_recommend_fuselist fail");
        }


        bsl::hashmap<uint, uint> result_ids;
        result_ids.create(MAX_USER_LIST_LEN);
        for(uint i = 0; i < r_song_len; i++){
            result_ids.set(r_song_list[i].song_id, i);
        }

        //推荐结果不够多,随机补充
        uint random_rlen;
        sodict_snode_t node;
        if(r_song_len < max_len){
            node.sign1 = creat_sign32(ch_name_temp);
            node.sign2 = CHANNEL_SONG_DICT;
            ret = odb_seek_search(p_global.bigDict, &node);
            if (ret == ODB_SEEK_ERROR){
                WARNING_LOG("seek bigDict faild[ret:%d][sign1:%u][sign2:%u]", ret,
                            node.sign1, node.sign2);
                goto END_RANDOM;
            }
            if (ret == ODB_SEEK_FAIL){
                TRACE_LOG("no matching found in bigDict[ret:%d][sign1:%u][sign2:%u]", ret,
                          node.sign1, node.sign2);
                goto END_RANDOM;
            }
            if (node.cuint1 + node.cuint2 > p_global.max_chsonglist_len){
                WARNING_LOG("bad pos[%u] len[%u] for song-song buf. max len[%u]",
                            node.cuint1, node.cuint2, p_global.max_chsonglist_len);
                goto END_RANDOM;
            }
            song_id_t* chsong_list = p_global.ch_song_list + node.cuint1;
            uint32_t chsong_len = node.cuint2;
            Song_item_t random_list[MAX_USER_LIST_LEN];
            uint random_need_len = max_len + EXTEND_RANDOM_LEN - r_song_len;
            random_need_len = random_need_len > MAX_USER_LIST_LEN ? MAX_USER_LIST_LEN : random_need_len;
            ret = _ral->get_simplelist(chsong_list, chsong_len, random_list, random_rlen,
                                       random_need_len, filter_dict);
            if(ret == FAIL){
                WARNING_LOG("get_randomlist fail");
                goto END_RANDOM;
            }
            uint value;
            //加入随机补充，需要去重
            for(uint i = 0; i < random_rlen && r_song_len < max_len; i++){
                if(result_ids.get(random_list[i].song_id, &value) == bsl::HASH_NOEXIST){
                    r_song_list[r_song_len] = random_list[i];
                    r_song_len++;
                    result_ids.set(random_list[i].song_id, r_song_len);
                }
            }
        }
    END_RANDOM:
        //插入歌曲
        uint insertid;
        ret = _dict_seeker->get_rand_top(insertid, ch_name_temp, filter_dict);
        if(ret == SUCCESS){
            //后面处理
            uint value;
            if(result_ids.get(insertid, &value) == bsl::HASH_NOEXIST){
                Song_item_t temp_song_list[MAX_USER_LIST_LEN];
                temp_song_list[0].song_id = insertid;
                temp_song_list[0].weight = MAX_WEIGHT;
                temp_song_list[0].source = DEFAULT_SOURCE;
                //直接拷贝处理
                int cpy_len = r_song_len;
                if(r_song_len > (MAX_USER_LIST_LEN - 1)){
                    cpy_len = MAX_USER_LIST_LEN - 1;
                }
                memcpy(temp_song_list+1, r_song_list, sizeof(Song_item_t) * cpy_len);
                r_song_len = 1 + cpy_len;
                memcpy(r_song_list, temp_song_list, sizeof(Song_item_t) * r_song_len);
            }
        }
        else{
            WARNING_LOG("get_rand_top fail");
        }
        //策略处理
        //歌手打散
        _rstrategy->arrange_user_list(r_song_list, r_song_len,
                                      g_config.singer_scatter_m, g_config.singer_scatter_n);
        //过滤最近的不喜欢的歌手
        _rstrategy->filter_user_list(r_song_list, r_song_len,
                                     g_config.hate_singer_len, g_config.pass_singer_len, g_config.filter_len, user_data);
        //插入音乐人歌曲
        this->_insert_yyr_song(ch_name, r_song_list, r_song_len, max_len, filter_dict);

        //插入推广歌曲
        this->_spread_sond(ch_name, r_song_list, r_song_len, max_len, filter_dict);
        //重定义权值
        _rstrategy->define_list_weight(r_song_list, r_song_len);

        if (filter_dict){
            odb_destroy(filter_dict);
        }
        result_ids.destroy();
        //更新缓存
        snprintf(ch_name_temp, MAX_CHNAME_LEN, "%s$$%d", ch_name, rf);
        uint ca_sign = creat_sign32(ch_name_temp);
        uint id = is_login ? uid : baiduid;
        if(is_login){
            mcc_update_ch_list(id, ch_name, r_song_list, r_song_len);
        }
        else{
            mcc_update_co_ch_list(id, ch_name, r_song_list, r_song_len);
        }
        DEBUG_LOG("finish gen_recommend_list, id:%u, r_song_len:%d", id, r_song_len);
        return SUCCESS;
    }

    int RGen::gen_fuse_list(char* ch_name, uint baiduid, uint uid,
                                 Song_item_t* r_song_list, uint max_len,
                                 uint &r_song_len, const r_userdata_t &user_data,
                                 bool is_public, bool is_login, bsl::mempool &pool, int rf, bool &is_new)
    {
        if(NULL == ch_name || NULL == r_song_list){
            WARNING_LOG("wrong param");
            return FAIL;
        }

        //生成关联列表
        sodict_build_t* filter_dict = odb_creat(FILT_DICT_HASH);
        if (!filter_dict){
            WARNING_LOG("creat odict faild");
            return -1;
        }
        //填充过滤歌曲
        _dict_seeker->fill_filter_dict(user_data, filter_dict);

        int ret = -1;
        bool has_list = false;
        is_new = false;

        //初始化待融合数据
        fuse_list_t* f_list= (fuse_list_t*) pool.malloc(sizeof(fuse_list_t));
        if(NULL == f_list){
            if (filter_dict){
                odb_destroy(filter_dict);
            }

            WARNING_LOG("failed to malloc f_list fail[%d]", sizeof(fuse_list_t));
            return -1;
        }
        //其它列表
        bsl::hashmap<int, fuse_init>::iterator iter = p_global.user_list_pair.begin();
        for(int i = 1;\
            i < FUSE_LIST_NUM && iter != p_global.user_list_pair.end(); \
            i++, iter++)
        {
            f_list->fuse_list_weight[i] = iter->second.rate;
            f_list->fuse_list_type[i] = iter->first;
            int r_source = iter->second.source;
            //获取列表
            f_list->fuse_list[i] = (Song_item_t *) pool.malloc(sizeof(Song_item_t) * CF_LIST_MAX_LEN);
            if(f_list->fuse_list[i] == NULL){
                WARNING_LOG("failed to malloc db list buf[%zd]", sizeof(Song_item_t) * CF_LIST_MAX_LEN);
                //free f_list
                for(int i = 1; i < FUSE_LIST_NUM; i++){
                    if(NULL != f_list->fuse_list[i]){
                        pool.free(f_list->fuse_list[i], sizeof(Song_item_t) * CF_LIST_MAX_LEN);
                    }
                }
                if(NULL != f_list){
                    pool.free(f_list, sizeof(fuse_list_t));
                }

                if (filter_dict){
                    odb_destroy(filter_dict);
                }
                return -1;
            }

            if(r_source == LDAC_SOURCE){
                ret = get_redis_rlist(uid, ch_name, LDAC_REDIS_TAG, REDIS_LIST_FIELD, f_list->fuse_list[i], CF_LIST_MAX_LEN, f_list->fuse_list_len[i], r_source, filter_dict);
            }else if(r_source == BPR_SOURCE){
                ret = get_redis_rlist(uid, ch_name, BPR_REDIS_TAG, REDIS_LIST_FIELD, f_list->fuse_list[i], CF_LIST_MAX_LEN, f_list->fuse_list_len[i], r_source, filter_dict);
            }else if(r_source == RANDOM_SOURCE){
                ret = redis_get_random_list(f_list->fuse_list[i], CF_LIST_MAX_LEN, f_list->fuse_list_len[i], filter_dict);
            }else{
                ret= mcc_get_ral_list(uid, ch_name, f_list->fuse_list_type[i], f_list->fuse_list[i], r_source, CF_LIST_MAX_LEN);
            }

            if(ret < 0){
                WARNING_LOG("db get db list fail");
                f_list->fuse_list_len[i] = 0;
            }
            else{
                f_list->fuse_list_len[i] = ret;
            }

            if(f_list->fuse_list_len[i] > 0){
                has_list = true;
            }
        }

        //试听历史小于50且无算法列表，新用户处理
        if(!has_list && user_data.len_listenhistory < NEW_USER_HISTORY_NUM){
            is_new = true;
            //free f_list
            for(int i = 1; i < FUSE_LIST_NUM; i++){
                if(NULL != f_list->fuse_list[i]){
                    pool.free(f_list->fuse_list[i], sizeof(Song_item_t) * CF_LIST_MAX_LEN);
                }
            }
            if(NULL != f_list){
                pool.free(f_list, sizeof(fuse_list_t));
            }

            if (filter_dict){
                odb_destroy(filter_dict);
            }
            NOTICE_LOG("find a private new user baiduid[%u], uid[%u]", baiduid, uid);
            return SUCCESS;
        }

        char ch_name_temp[MAX_CHNAME_LEN];
        int tag_len = -1;
        r_song_len = 0;
        DEBUG_LOG("start gen_indexmerge_rlist");
        ret = _ral->gen_indexmerge_rlist(user_data, ch_name,
                                         filter_dict, is_public,
                                         max_len, r_song_len,
                                         r_song_list, pool);
        if(ret != SUCCESS){
            r_song_len = 0;
            WARNING_LOG("gen_indexmerge_rlist fail");
        }
        DEBUG_LOG("end gen_indexmerge_rlist, r_len:%d", r_song_len);
        //第0个列表置为关联列表
        f_list->fuse_list_weight[0] = g_config.original_weight;
        f_list->fuse_list[0] = r_song_list;
        f_list->fuse_list_len[0] = r_song_len;

        //获取用户模型标签
        User_tag_t user_tag_list[USER_TAG_LEN];
        //int tag_len = -1;
        tag_len = mcc_get_tag_list(uid, user_tag_list, USER_TAG_NUM);
        if (tag_len <= 0){
            WARNING_LOG("get user tag fail[%d]", tag_len);
            tag_len = 0;
        }
        ret = _ral->gen_fuse_rlist(uid, ch_name, filter_dict, max_len,
                                   r_song_len, r_song_list, f_list,
                                   user_tag_list, tag_len, user_data, pool);
        if(ret < 0){
            WARNING_LOG("gen_fuse_rlist fail");
        }
        //free f_list
        for(int i = 1; i < FUSE_LIST_NUM; i++){
            if(NULL != f_list->fuse_list[i]){
                pool.free(f_list->fuse_list[i], sizeof(Song_item_t) * CF_LIST_MAX_LEN);
            }
        }
        if(NULL != f_list){
            pool.free(f_list, sizeof(fuse_list_t));
        }
#ifdef _DEBUG_TIME
        for(uint i = 0; i < r_song_len; i++){
            DEBUG_LOG("the fuse list is:, position[%u], song_id[%u], weight[%d], source[%d]",
                      i, r_song_list[i].song_id, r_song_list[i].weight, r_song_list[i].source);
        }
        DEBUG_LOG("---fuse list end.");
#endif

        //推荐结果不够多 i love cici =.=
        bsl::hashmap<uint, uint> result_ids;
        result_ids.create(MAX_USER_LIST_LEN);
        for(uint i = 0; i < r_song_len; i++){
            result_ids.set(r_song_list[i].song_id, i);
        }
        snprintf(ch_name_temp, MAX_CHNAME_LEN, "%s", ch_name);
        uint random_rlen;
        sodict_snode_t node;
        if(r_song_len < max_len){
            node.sign1 = creat_sign32(ch_name_temp);
            node.sign2 = CHANNEL_SONG_DICT;
            ret = odb_seek_search(p_global.bigDict, &node);
            if (ret == ODB_SEEK_ERROR){
                WARNING_LOG("seek bigDict faild[ret:%d][sign1:%u][sign2:%u]", ret,
                            node.sign1, node.sign2);
                goto END_RANDOM;
            }
            if (ret == ODB_SEEK_FAIL){
                TRACE_LOG("no matching found in bigDict[ret:%d][sign1:%u][sign2:%u]", ret,
                          node.sign1, node.sign2);
                goto END_RANDOM;
            }
            if (node.cuint1 + node.cuint2 > p_global.max_chsonglist_len){
                WARNING_LOG("bad pos[%u] len[%u] for song-song buf. max len[%u]",
                            node.cuint1, node.cuint2, p_global.max_chsonglist_len);
                goto END_RANDOM;
            }
            song_id_t* chsong_list = p_global.ch_song_list + node.cuint1;
            uint32_t chsong_len = node.cuint2;
            Song_item_t random_list[MAX_USER_LIST_LEN];
            uint random_need_len = max_len + EXTEND_RANDOM_LEN - r_song_len;
            random_need_len = random_need_len > MAX_USER_LIST_LEN ? MAX_USER_LIST_LEN : random_need_len;
            ret = _ral->get_simplelist(chsong_list, chsong_len, random_list, random_rlen,
                                       random_need_len, filter_dict);
            if(ret == FAIL){
                WARNING_LOG("get_randomlist fail");
                goto END_RANDOM;
            }
            uint value;
            //加入随机补充，需要去重
            for(uint i = 0; i < random_rlen && r_song_len < max_len; i++){
                if(result_ids.get(random_list[i].song_id, &value) == bsl::HASH_NOEXIST){
                    r_song_list[r_song_len] = random_list[i];
                    r_song_len++;
                    result_ids.set(random_list[i].song_id, r_song_len);
                }
            }
        }
    END_RANDOM:
        //策略处理
        //歌手打散
        _rstrategy->arrange_user_list(r_song_list, r_song_len,
                                      g_config.singer_scatter_m, g_config.singer_scatter_n);
        //过滤最近的不喜欢的歌手
        _rstrategy->filter_user_list(r_song_list, r_song_len,
                                     g_config.hate_singer_len, g_config.pass_singer_len, g_config.filter_len, user_data);
        //插入推广歌曲
        this->_spread_sond(ch_name, r_song_list, r_song_len, max_len, filter_dict);
        //疲劳度处理
        _rstrategy->tire_list(r_song_list, r_song_len, uid, baiduid, is_login);
        //重定义权值
        _rstrategy->define_list_weight(r_song_list, r_song_len);
        if (filter_dict){
            odb_destroy(filter_dict);
        }
        result_ids.destroy();
        //更新缓存
        snprintf(ch_name_temp, MAX_CHNAME_LEN, "%s$$%d", ch_name, rf);
        uint id = is_login ? uid : baiduid;
        if(is_login){
            mcc_update_ch_list(id, ch_name, r_song_list, r_song_len);
        }
        else{
            mcc_update_co_ch_list(id, ch_name, r_song_list, r_song_len);
        }
        DEBUG_LOG("finish gen_recommend_list, id:%u, r_song_len:%d", id, r_song_len);
        return SUCCESS;
    }

    int RGen::gen_instant_list(const char* ch_name, uint baiduid, uint uid,
                                 Song_item_t* r_song_list, uint max_len,
                                 uint &r_song_len, const r_userdata_t &user_data,
                                 bool is_login, int rf)
    {
        if(NULL == ch_name || NULL == r_song_list){
            WARNING_LOG("wrong param");
            return FAIL;
        }
        int ret = -1;
        //填充过滤歌曲
        sodict_build_t* filter_dict = odb_creat(FILT_DICT_HASH);
        if (!filter_dict){
            WARNING_LOG("creat odict faild");
            return -1;
        }
        _dict_seeker->fill_filter_dict(user_data, filter_dict);

        //获取频道歌曲列表
        sodict_snode_t node;
        char ch_name_temp[MAX_CHNAME_LEN];
        snprintf(ch_name_temp, MAX_CHNAME_LEN, "%s", ch_name);
        uint ch_sign = creat_sign32(ch_name_temp);
        node.sign1 = ch_sign;
        node.sign2 = CHANNEL_SONG_DICT;
        ret = odb_seek_search(p_global.bigDict, &node);
        if (ret == ODB_SEEK_ERROR){
            WARNING_LOG("seek bigDict faild[ret:%d][sign1:%u][sign2:%u]", ret, node.sign1, node.sign2);
            if (filter_dict){
                odb_destroy(filter_dict);
            }
            return FAIL;
        }
        if (ret == ODB_SEEK_FAIL){
            TRACE_LOG("no matching found in bigDict[ret:%d][sign1:%u][sign2:%u]", ret, node.sign1,
                      node.sign2);
            if (filter_dict){
                odb_destroy(filter_dict);
            }
            return NOEXIST;
        }
        if (node.cuint1 + node.cuint2 > p_global.max_chsonglist_len){
            WARNING_LOG("bad pos[%u] len[%u] for song-song buf. max len[%u]",
                        node.cuint1, node.cuint2, p_global.max_chsonglist_len);
            if (filter_dict){
                odb_destroy(filter_dict);
            }
            return FAIL;
        }
        song_id_t* chsong_list = p_global.ch_song_list + node.cuint1;
        uint32_t chsong_len = node.cuint2;

        //gen instant list
        Song_item_t instant_list[MAX_USER_LIST_LEN];
        uint instant_list_len = 0;
        ret = _ral->get_instantlist(chsong_list, chsong_len,
                                    instant_list, instant_list_len, user_data, max_len, filter_dict, ch_name_temp);
        if(ret == FAIL){
            WARNING_LOG("gen_instantlist fail");
            if (filter_dict){
                odb_destroy(filter_dict);
            }
            return FAIL;
        }else{
            NOTICE_LOG("instant list len is [%d]", instant_list_len);
        }
        //end gen instant list

        uint id = is_login ? uid : baiduid;
        if(strcmp(ch_name, CH_HUAYU_NAME) == 0){
            Song_item_t redis_ldac_list[MAX_USER_LIST_LEN];
            uint redis_ldac_list_len = 0;
            ret = get_redis_rlist(uid, ch_name, LDAC_REDIS_TAG, REDIS_LIST_FIELD, redis_ldac_list, CF_LIST_MAX_LEN, redis_ldac_list_len, rls::LDAC_SOURCE, filter_dict);

            if(ret != SUCCESS || redis_ldac_list_len <= 0){
                WARNING_LOG("gen_redis_ldac_list for [%s] fail, uid[%u]", ch_name, id);
                if(instant_list_len > 0){
                    r_song_len = instant_list_len;
                    memcpy(r_song_list, instant_list, sizeof(Song_item_t) * r_song_len);
                }
            }else{
                NOTICE_LOG("uid[%d] public [%s] redis_ldac_list_len is [%u]", id, ch_name, redis_ldac_list_len);

                if(instant_list_len <= 0){
                    r_song_len = redis_ldac_list_len;
                    memcpy(r_song_list, redis_ldac_list, sizeof(Song_item_t) * r_song_len);
                }else{
                    //fuse list
                    ret = _ral->gen_public_fuselist(redis_ldac_list, instant_list,
                            redis_ldac_list_len, instant_list_len, r_song_list,
                            r_song_len, max_len);

                    if(ret <= 0){
                        WARNING_LOG("gen_huayu_fuselist fail, uid[%u]", id);
                    }
                }
            }
        }else if(instant_list_len > 0){
            r_song_len = instant_list_len;
            memcpy(r_song_list, instant_list, sizeof(Song_item_t) * r_song_len);
        }

        NOTICE_LOG("user[%u] public ch r_song_list_len is [%d]", id, r_song_len);

        //歌曲不足时，由频道歌曲补充
        uint random_rlen;
        if(r_song_len < MIN_USER_LIST_LEN && r_song_len < max_len){
            bsl::hashmap<uint, uint> result_ids;
            result_ids.create(MAX_USER_LIST_LEN);
            for(uint i = 0; i < r_song_len; i++){
                result_ids.set(r_song_list[i].song_id, i);
            }
            sodict_build_t* hate_filter_dict = odb_creat(FILT_DICT_HASH);
            if (!hate_filter_dict){
                WARNING_LOG("creat odict faild");
                if (filter_dict){
                    odb_destroy(filter_dict);
                }
                result_ids.destroy();
                return -1;
            }
            _dict_seeker->fill_hate_dict(user_data, hate_filter_dict);

            Song_item_t random_list[MAX_USER_LIST_LEN];
            uint random_need_len = max_len + EXTEND_RANDOM_LEN - r_song_len;
            random_need_len = random_need_len > MAX_USER_LIST_LEN ? MAX_USER_LIST_LEN : random_need_len;
            ret = _ral->get_simplelist(chsong_list, chsong_len, random_list, random_rlen,
                                       random_need_len, hate_filter_dict);
            if(ret == FAIL){
                WARNING_LOG("get_randomlist fail");
                if(hate_filter_dict){
                    odb_destroy(hate_filter_dict);
                }
                result_ids.destroy();
                goto END_RANDOM;
            }
            uint value;
            //加入随机补充，需要去重
            for(uint i = 0; i < random_rlen && r_song_len < max_len; i++){
                if(result_ids.get(random_list[i].song_id, &value) == bsl::HASH_NOEXIST){
                    r_song_list[r_song_len] = random_list[i];
                    r_song_list[r_song_len].weight = 0;
                    r_song_list[r_song_len].source |= INSTANT_SOURCE;
                    r_song_len++;
                    result_ids.set(random_list[i].song_id, r_song_len);
                }
            }
            if(hate_filter_dict){
                odb_destroy(hate_filter_dict);
            }
            result_ids.destroy();
        }
    END_RANDOM:
        //权重排序与歌手打散
        _rstrategy->arrange_user_list(r_song_list, r_song_len,
                                      g_config.singer_scatter_m, g_config.singer_scatter_n);
        //过滤最近的不喜欢的歌手
        _rstrategy->filter_user_list(r_song_list, r_song_len,
                                     g_config.hate_singer_len, g_config.pass_singer_len, g_config.filter_len, user_data);

        //插入音乐人歌曲
        this->_insert_yyr_song(ch_name, r_song_list, r_song_len, max_len, filter_dict);

        //插入推广歌曲
        this->_spread_sond(ch_name, r_song_list, r_song_len, max_len, filter_dict);
        _rstrategy->tire_list(r_song_list, r_song_len, uid, baiduid, is_login);
        //重定义权值
        _rstrategy->define_list_weight(r_song_list, r_song_len);

        if (filter_dict){
            odb_destroy(filter_dict);
        }
        //更新缓存
        snprintf(ch_name_temp, MAX_CHNAME_LEN, "%s$$%d", ch_name, rf);
        uint ca_sign = creat_sign32(ch_name_temp);
        if(is_login){
            mcc_update_ch_list(id, ch_name, r_song_list, r_song_len);
        }
        else{
            mcc_update_co_ch_list(id, ch_name, r_song_list, r_song_len);
        }
        return SUCCESS;
    }

    int RGen::gen_newuser_private_list(const char* ch_name, uint baiduid, uint uid,
                                 Song_item_t* r_song_list, uint max_len,
                                 uint &r_song_len, const r_userdata_t &user_data,
                                 bool is_login, int rf)
    {
        if(NULL == ch_name || NULL == r_song_list){
            WARNING_LOG("wrong param");
            return FAIL;
        }
        int ret = -1;
        //填充过滤歌曲
        sodict_build_t* filter_dict = odb_creat(FILT_DICT_HASH);
        if (!filter_dict){
            WARNING_LOG("creat odict faild");
            return -1;
        }
        _dict_seeker->fill_filter_dict(user_data, filter_dict);

        //获取频道歌曲列表
        sodict_snode_t node;
        char ch_name_temp[MAX_CHNAME_LEN];
        snprintf(ch_name_temp, MAX_CHNAME_LEN, "%s", ch_name);
        uint ch_sign = creat_sign32(ch_name_temp);
        node.sign1 = ch_sign;
        node.sign2 = CHANNEL_SONG_DICT;
        ret = odb_seek_search(p_global.bigDict, &node);
        if (ret == ODB_SEEK_ERROR){
            WARNING_LOG("seek bigDict faild[ret:%d][sign1:%u][sign2:%u]", ret, node.sign1, node.sign2);
            if (filter_dict){
                odb_destroy(filter_dict);
            }
            return FAIL;
        }
        if (ret == ODB_SEEK_FAIL){
            TRACE_LOG("no matching found in bigDict[ret:%d][sign1:%u][sign2:%u]", ret, node.sign1,
                      node.sign2);
            if (filter_dict){
                odb_destroy(filter_dict);
            }
            return NOEXIST;
        }
        if (node.cuint1 + node.cuint2 > p_global.max_chsonglist_len){
            WARNING_LOG("bad pos[%u] len[%u] for song-song buf. max len[%u]",
                        node.cuint1, node.cuint2, p_global.max_chsonglist_len);
            if (filter_dict){
                odb_destroy(filter_dict);
            }
            return FAIL;
        }
        song_id_t* chsong_list = p_global.ch_song_list + node.cuint1;
        uint32_t chsong_len = node.cuint2;

        //gen instant list
        Song_item_t instant_list[MAX_USER_LIST_LEN];
        uint instant_list_len = 0;
        ret = _ral->get_instantlist(chsong_list, chsong_len,
                                    instant_list, instant_list_len, user_data, max_len, filter_dict, ch_name_temp);
        if(ret == FAIL){
            WARNING_LOG("gen_instantlist fail");
            /*if (filter_dict){
                odb_destroy(filter_dict);
            }
            return FAIL;
            */
        }
        //end instant

        //gen ldac redis list
        Song_item_t redis_ldac_list[MAX_USER_LIST_LEN];
        uint redis_ldac_list_len = 0;
        ret = get_redis_rlist(uid, ch_name, LDAC_REDIS_TAG, REDIS_LIST_FIELD, redis_ldac_list, CF_LIST_MAX_LEN, redis_ldac_list_len, rls::LDAC_SOURCE, filter_dict);
        if(ret != SUCCESS){
            WARNING_LOG("newuser gen_redis_ldac_list fail uid:[%u]", uid);
        }else{
            NOTICE_LOG("newuser [%u] gen redis ldac success, length is [%d]", uid, redis_ldac_list_len);
        }
        //end ldac redis

        //gen bpr redis list
        Song_item_t redis_bpr_list[MAX_USER_LIST_LEN];
        uint redis_bpr_list_len = 0;
        ret = get_redis_rlist(uid, ch_name, BPR_REDIS_TAG, REDIS_LIST_FIELD, redis_bpr_list, CF_LIST_MAX_LEN, redis_bpr_list_len, rls::BPR_SOURCE, filter_dict);
        if(ret != SUCCESS){
            WARNING_LOG("newuser gen_redis_bpr_list fail uid:[%u]", uid);
        }else{
            NOTICE_LOG("newuser [%u] gen redis bpr success, length is [%d]", uid, redis_bpr_list_len);
        }
        //end bpr redis

        //fuse list
        ret = _ral->gen_newuser_fuselist(redis_ldac_list, redis_bpr_list, instant_list,
                                    redis_ldac_list_len, redis_bpr_list_len, instant_list_len, r_song_list,
                                    r_song_len, max_len);
        if(ret <= 0){
            WARNING_LOG("gen_newuser_fuselist fail uid:[%u]", uid);
        }
        //end fuse

        //歌曲不足时，由频道歌曲补充
        uint random_rlen;
        if(r_song_len < MIN_USER_LIST_LEN && r_song_len < max_len){
            bsl::hashmap<uint, uint> result_ids;
            result_ids.create(MAX_USER_LIST_LEN);
            for(uint i = 0; i < r_song_len; i++){
                result_ids.set(r_song_list[i].song_id, i);

            }

            sodict_build_t* hate_filter_dict = odb_creat(FILT_DICT_HASH);
            if (!hate_filter_dict){
                WARNING_LOG("creat odict faild");
                if (filter_dict){
                    odb_destroy(filter_dict);
                }
                result_ids.destroy();
                return -1;
            }
            _dict_seeker->fill_hate_dict(user_data, hate_filter_dict);

            Song_item_t random_list[MAX_USER_LIST_LEN];
            uint random_need_len = max_len + EXTEND_RANDOM_LEN - r_song_len;
            random_need_len = random_need_len > MAX_USER_LIST_LEN ? MAX_USER_LIST_LEN : random_need_len;
            ret = _ral->get_simplelist(chsong_list, chsong_len, random_list, random_rlen,
                                       random_need_len, hate_filter_dict);
            if(ret == FAIL){
                WARNING_LOG("get_randomlist fail");
                if(hate_filter_dict){
                    odb_destroy(hate_filter_dict);
                }
                result_ids.destroy();
                goto END_RANDOM;
            }
            uint value;
            //加入随机补充，需要去重
            for(uint i = 0; i < random_rlen && r_song_len < max_len; i++){
                if(result_ids.get(random_list[i].song_id, &value) == bsl::HASH_NOEXIST){
                    r_song_list[r_song_len] = random_list[i];
                    r_song_list[r_song_len].weight = 0;
                    r_song_list[r_song_len].source |= INSTANT_SOURCE;
                    r_song_list[r_song_len].source |= NEWUSER_SOURCE;
                    r_song_len++;
                    result_ids.set(random_list[i].song_id, r_song_len);
                }
            }
            if(hate_filter_dict){
                odb_destroy(hate_filter_dict);
            }
            result_ids.destroy();
        }
    END_RANDOM:
        //权重排序与歌手打散
        _rstrategy->arrange_user_list(r_song_list, r_song_len,
                                      g_config.singer_scatter_m, g_config.singer_scatter_n);
        //过滤最近的不喜欢的歌手
        _rstrategy->filter_user_list(r_song_list, r_song_len,
                                     g_config.hate_singer_len, g_config.pass_singer_len, g_config.filter_len, user_data);

        //插入推广歌曲
        this->_spread_sond(ch_name, r_song_list, r_song_len, max_len, filter_dict);
        _rstrategy->tire_list(r_song_list, r_song_len, uid, baiduid, is_login);
        //重定义权值
        _rstrategy->define_list_weight(r_song_list, r_song_len);

        if (filter_dict){
            odb_destroy(filter_dict);
        }
        //更新缓存
        snprintf(ch_name_temp, MAX_CHNAME_LEN, "%s$$%d", ch_name, rf);
        uint id = is_login ? uid : baiduid;
        if(is_login){
            mcc_update_ch_list(id, ch_name, r_song_list, r_song_len);
        }
        else{
            mcc_update_co_ch_list(id, ch_name, r_song_list, r_song_len);
        }
        return SUCCESS;
    }

    int RGen::_insert_yyr_song(const char *ch_name, Song_item_t* song_list,
                           uint &song_list_len, uint max_len,
                           const sodict_build_t* filter_dict)
    {
        if(NULL == ch_name || NULL == song_list || song_list_len > max_len){
            WARNING_LOG("ch_name or song_list is NULL");
            return FAIL;
        }
        if(song_list_len < 0){
            WARNING_LOG("song_list_len[%d] < 0 ", song_list_len);
            return FAIL;
        }
        if(0 == song_list_len){
            return SUCCESS;
        }

        if(p_global.yyr_chsong_dict == NULL){
            return FAIL;
        }

        int ret;
        sodict_snode_t node;
        char ch_name_temp[MAX_CHNAME_LEN];
        snprintf(ch_name_temp, MAX_CHNAME_LEN, "%s", ch_name);
        uint ch_sign = creat_sign32(ch_name_temp);
        node.sign1 = ch_sign;
        node.sign2 = 0;

        ret = odb_seek_search(p_global.yyr_chsong_dict, &node);
        if(ret == ODB_SEEK_ERROR){
            WARNING_LOG("seek yyr chsong dict faild[ret:%d][sign1:%u][sign2:%u]", ret, node.sign1, node.sign2);
            return FAIL;
        }
        if(ret == ODB_SEEK_FAIL){
            TRACE_LOG("no matching found in yyr chsong dict [ret:%d][sign1:%u][sign2:%u]", ret, node.sign1,
                    node.sign2);
            return NOEXIST;
        }

        if(node.cuint1 + node.cuint2 > p_global.max_yyrchsonglist_len || node.cuint2 == 0){
            WARNING_LOG("bad pos[%u] len[%u] for yyr-chsong-list buf. max len[%u]",
                    node.cuint1, node.cuint2, p_global.max_yyrchsonglist_len);
            return FAIL;
        }

        const uint64_t* yyr_chsong_list = p_global.yyrchsong_list + node.cuint1;
        uint32_t yyr_len = node.cuint2;

        bsl::hashmap<uint, uint> rdata;
        rdata.create(song_list_len);
        for(int i = 0; i < song_list_len; i++){
            rdata.set(song_list[i].song_id, 0);
        }

        int max_random_len = 50;
        int t_slist_len = 0;
        uint t_slist[max_random_len];
        for(int i = 0; i < max_random_len && i < yyr_len; i ++){
            t_slist[i] = (uint)yyr_chsong_list[i];
            t_slist_len ++;
        }

        std::random_shuffle(t_slist, t_slist + t_slist_len);

        int insert_pos = 10;
        int step = 10;
        int cpy_len = 0;
        uint value = 0;
        Song_item_t temp_song_list[max_len];
        uint song_id;
        for(int i = 0; i < t_slist_len; i++ ){
            if(insert_pos >= max_len || insert_pos > song_list_len){
                break;
            }

            song_id = t_slist[i];
            if(_dict_seeker->filt_song(filter_dict, song_id)){
                continue;
            }

            ret = rdata.get(song_id, &value);
            if(ret == bsl::HASH_NOEXIST){
                if(song_list_len >= max_len){
                    cpy_len = song_list_len - insert_pos - 1;
                }else{
                    cpy_len = song_list_len - insert_pos;
                }

                memcpy(temp_song_list, song_list, sizeof(Song_item_t) * song_list_len);
                song_list[insert_pos].song_id = song_id;
                song_list[insert_pos].weight = 0;
                song_list[insert_pos].source = YYR_SOURCE;
                memcpy(song_list + insert_pos + 1, temp_song_list + insert_pos, sizeof(Song_item_t) * cpy_len);

                rdata.set(song_id, 0);
                song_list_len = insert_pos + cpy_len;
                song_list_len ++;
                insert_pos += step;
            }
        }

        rdata.destroy();
        return SUCCESS;
    }

    int RGen::_spread_sond(const char *ch_name, Song_item_t* song_list,
                           uint &song_list_len, uint umax,
                           const sodict_build_t* filter_dict)
    {
        if(NULL == ch_name || NULL == song_list){
            WARNING_LOG("ch_name or song_list is NULL");
            return FAIL;
        }
        if(song_list_len < 0){
            WARNING_LOG("song_list_len[%d] < 0 ", song_list_len);
            return FAIL;
        }
        if(0 == song_list_len){
            return SUCCESS;
        }
        int ret;
        sodict_snode_t node;
        char ch_name_temp[MAX_CHNAME_LEN];
        snprintf(ch_name_temp, MAX_CHNAME_LEN, "%s", ch_name);
        uint ch_sign = creat_sign32(ch_name_temp);
        node.sign1 = ch_sign;
        node.sign2 = SPREAD_SONG_DICT;
        ret = odb_seek_search(p_global.bigDict, &node);
        if (ret == ODB_SEEK_ERROR){
            WARNING_LOG("seek bigDict faild[ret:%d][sign1:%u][sign2:%u]", ret, node.sign1, node.sign2);
            return FAIL;
        }
        if (ret == ODB_SEEK_FAIL){
                TRACE_LOG("no matching found in bigDict[ret:%d][sign1:%u][sign2:%u]", ret, node.sign1,
                          node.sign2);
                return NOEXIST;
        }
        if (node.cuint1 + node.cuint2 > p_global.max_spreadsonglist_len){
                WARNING_LOG("bad pos[%u] len[%u] for song-song buf. max len[%u]",
                            node.cuint1, node.cuint2, p_global.max_chsonglist_len);
                return FAIL;
        }
        spread_song_t* spread_song_list = p_global.spreadsong_list + node.cuint1;
        uint32_t spread_len = node.cuint2;
#ifdef _DEBUG_TIME
        for(uint i = 0; i < spread_len; i++){
            DEBUG_LOG("spread song:i[%d],song_id[%u],begin[%d],end[%d],rate[%d]",
                i, spread_song_list[i].song_id, spread_song_list[i].pos_begin, spread_song_list[i].pos_end, spread_song_list[i].rate);
        }
        for(uint i = 0; i < song_list_len; i++){
            DEBUG_LOG("before spread:i[%d],song_id[%u],weight[%d],source[%d]",
                i, song_list[i].song_id, song_list[i].weight, song_list[i].source);
        }
#endif
        bsl::hashmap<uint, uint> rdata;
        rdata.create(song_list_len);
        for(int i = 0; i < song_list_len; i++){
            rdata.set(song_list[i].song_id, 0);
        }
        //插入推广歌曲
        uint value = 0;
        int rate = 0;//推广概率
        int begin, end = 0;
        int dis, pos = 0;
        Song_item_t temp_song_list[MAX_USER_LIST_LEN];
        for(uint32_t i = 0; i < spread_len; i++ ){
            ret = rdata.get(spread_song_list[i].song_id, &value);
            //如果推广歌曲属于列表中，将不插入推广
            if(ret == bsl::HASH_NOEXIST){
                //推广概率
                rate = rand()%100;
                if (rate > spread_song_list[i].rate){
                    DEBUG_LOG("the rand rate[%d] more than spread rate[%d]", rate, spread_song_list[i].rate);
                    continue;
                }
                end = spread_song_list[i].pos_end;
                begin = spread_song_list[i].pos_begin;
                if(song_list_len < spread_song_list[i].pos_end){
                    end = song_list_len;
                }
                if(begin < 0 || end > MAX_USER_LIST_LEN || begin >= end){
                    WARNING_LOG("the spread pos is error, pos_begin[%d], pos_end:[%d], song_list_len[%d]",
                                spread_song_list[i].pos_begin, spread_song_list[i].pos_end, song_list_len);
                    continue;
                }
                dis = end - begin;
                pos = rand()%dis;
#ifdef _DEBUG_TIME
                DEBUG_LOG("the insert spread song_id[%d], pos[%d]", spread_song_list[i].song_id, begin + pos);
#endif
                memcpy(temp_song_list, song_list, sizeof(Song_item_t) * song_list_len);
                uint cpy_len = song_list_len - pos - begin;
                if(song_list_len + 1 > umax){
                    cpy_len--;
                }
                memcpy(song_list + begin + pos + 1, temp_song_list + begin + pos, sizeof(Song_item_t) * cpy_len);
                song_list[begin + pos].song_id =  spread_song_list[i].song_id;
                song_list[begin + pos].source = DEFAULT_SOURCE;
                song_list_len =  begin + pos + cpy_len;
                song_list_len++;
                rdata.set(spread_song_list[i].song_id, 0);
            }
        }
        rdata.destroy();
#ifdef _DEBUG_TIME
        for(uint i = 0; i < song_list_len; i++){
            DEBUG_LOG("after spread:i[%d],song_id[%u],weight[%d],source[%d]",
                i, song_list[i].song_id, song_list[i].weight, song_list[i].source);
        }
#endif
        return SUCCESS;
    }


    int RGen::gen_y_list(const char* ch_name, uint baiduid, uint uid,
                                 Song_item_t* r_song_list, uint max_len, uint &r_song_len,
                                 const y_user_data_t &user_data,
                                 bool is_login, bsl::mempool &pool, int rf)
    {
        if(NULL == ch_name || NULL == r_song_list){
            WARNING_LOG("wrong param");
            return FAIL;
        }
        int ret = -1;
        //填充过滤歌曲
        sodict_build_t* filter_dict = odb_creat(FILT_DICT_HASH);
        if (!filter_dict){
            WARNING_LOG("creat odict faild");
            return -1;
        }
        _dict_seeker->fill_y_filter_dict(user_data, filter_dict);

        //获取频道歌曲列表
        sodict_snode_t node;
        char ch_name_temp[MAX_CHNAME_LEN];
        snprintf(ch_name_temp, MAX_CHNAME_LEN, "%s", ch_name);
        uint ch_sign = creat_sign32(ch_name_temp);
        node.sign1 = ch_sign;
        node.sign2 = ch_sign;
        ret = odb_seek_search(p_global.y_channel_dict, &node);
        if (ret == ODB_SEEK_ERROR){
            WARNING_LOG("seek y_channel_dict faild[ret:%d][sign1:%u][sign2:%u]", ret, node.sign1, node.sign2);
            if (filter_dict){
                odb_destroy(filter_dict);
            }
            return FAIL;
        }
        if (ret == ODB_SEEK_FAIL){
            TRACE_LOG("no matching found in y_channel_dict[ret:%d][sign1:%u][sign2:%u]", ret, node.sign1,
                      node.sign2);
            if (filter_dict){
                odb_destroy(filter_dict);
            }
            return NOEXIST;
        }
        if (node.cuint1 + node.cuint2 > p_global.max_ychannel_list_len){
            WARNING_LOG("bad pos[%u] len[%u] for ychannel_list. max len[%u]",
                        node.cuint1, node.cuint2, p_global.max_ychannel_list_len);
            if (filter_dict){
                odb_destroy(filter_dict);
            }
            return FAIL;
        }
        song_id_t* chsong_list = p_global.ychannel_list + node.cuint1;
        uint32_t chsong_len = node.cuint2;
        ret = _ral->get_y_list(chsong_list, chsong_len,
                                    r_song_list, r_song_len, user_data, max_len, filter_dict, ch_name_temp);
        if(ret == FAIL){
            WARNING_LOG("gen_y_list fail");
            if (filter_dict){
                odb_destroy(filter_dict);
            }
            return FAIL;
        }
        //shuffle
        std::random_shuffle(r_song_list, r_song_list + r_song_len);

        //歌曲不足时，由频道歌曲补充
        uint random_rlen;
        if(r_song_len < MIN_USER_LIST_LEN && r_song_len < max_len){
            bsl::hashmap<uint, uint> result_ids;
            result_ids.create(MAX_USER_LIST_LEN);
            for(uint i = 0; i < r_song_len; i++){
                result_ids.set(r_song_list[i].song_id, i);
            }
            sodict_build_t* hate_filter_dict = odb_creat(FILT_DICT_HASH);
            if (!hate_filter_dict){
                WARNING_LOG("creat odict faild");
                return -1;
            }
            _dict_seeker->fill_y_hate_dict(user_data, hate_filter_dict);

            Song_item_t random_list[MAX_USER_LIST_LEN];
            uint random_need_len = max_len + EXTEND_RANDOM_LEN - r_song_len;
            random_need_len = random_need_len > MAX_USER_LIST_LEN ? MAX_USER_LIST_LEN : random_need_len;
            ret = _ral->get_simplelist(chsong_list, chsong_len, random_list, random_rlen,
                                       random_need_len, hate_filter_dict);
            if(ret == FAIL){
                WARNING_LOG("get_randomlist fail");
                if(hate_filter_dict){
                    odb_destroy(hate_filter_dict);
                }
                result_ids.destroy();
                goto END_RANDOM;
            }
            uint value;
            //加入随机补充，需要去重
            for(uint i = 0; i < random_rlen && r_song_len < max_len; i++){
                if(result_ids.get(random_list[i].song_id, &value) == bsl::HASH_NOEXIST){
                    r_song_list[r_song_len] = random_list[i];
                    r_song_list[r_song_len].weight = 0;
                    r_song_list[r_song_len].source |= 0;
                    r_song_len++;
                    result_ids.set(random_list[i].song_id, r_song_len);
                }
            }
            if(hate_filter_dict){
                odb_destroy(hate_filter_dict);
            }
            result_ids.destroy();
        }
    END_RANDOM:
        //重定义权值
        _rstrategy->define_list_weight(r_song_list, r_song_len);

        if (filter_dict){
            odb_destroy(filter_dict);
        }
        //更新缓存
        snprintf(ch_name_temp, MAX_CHNAME_LEN, "%s$$%d", ch_name, rf);
        uint id = is_login ? uid : baiduid;
        if(is_login){
            mcc_update_ch_list(id, ch_name, r_song_list, r_song_len);
        }
        else{
            mcc_update_co_ch_list(id, ch_name, r_song_list, r_song_len);
        }
        return SUCCESS;
    }

}

