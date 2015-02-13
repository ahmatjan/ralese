/**
 * @file rls_dictseeker.cpp
 * @Synopsis  rls字典数据查找
 * @author sparkwen
 * @version 1.0.0
 * @date 2013-10-11
 */
#include "rls_dictseeker.h"
#include "ul_sign.h"

namespace rls{
    DictSeeker::DictSeeker(){

    }

    DictSeeker::~DictSeeker(){

    }

    int DictSeeker::seek_public_song_song(uint itemid, uint ch_sign,
            Song_item_t **p, int &len){
        if(0 == itemid){
            WARNING_LOG("error itemid[0]");
            return FAIL;
        }
        sodict_snode_t node;
        node.sign1 = itemid;
        node.sign2 = ch_sign;
        int ret = odb_seek_search(p_global.bigDict, &node);
        if (ret == ODB_SEEK_ERROR){
            WARNING_LOG("seek bigDict faild[ret:%d][sign1:%u][sign2:%u]", ret, node.sign1, node.sign2);
            return FAIL;
        }
        if (ret == ODB_SEEK_FAIL){
            TRACE_LOG("no matching found in bigDict[ret:%d][sign1:%u][sign2:%u]", ret, node.sign1, node.sign2);
            p = NULL;
            len = 0;
            return NOEXIST;
        }
        if (node.cuint1 + node.cuint2 > p_global.max_publicrsong_len){
            WARNING_LOG("bad pos[%u] len[%u] for public-song-song buf. max len[%u]",
                    node.cuint1, node.cuint2, p_global.max_publicrsong_len);
            return FAIL;
        }
        *p = p_global.public_rsong_list + node.cuint1;
        len = node.cuint2;
        return SUCCESS;
    }

    int DictSeeker::seek_feature_pos(uint itemid){
        if(0 == itemid){
            WARNING_LOG("error itemid[0]");
            return FAIL;
        }
        sodict_snode_t node;
        node.sign1 = itemid;
        node.sign2 = itemid;
        int pos = -1;
        int ret = odb_seek_search(p_global.lr_feature_dict, &node);
        if (ret == ODB_SEEK_ERROR){
            WARNING_LOG("seek lr_feature_dict faild[ret:%d][sign1:%u][sign2:%u]", ret, node.sign1, node.sign2);
            return FAIL;
        }
        if (ret == ODB_SEEK_FAIL){
            //TRACE_LOG("no matching found in lr_feature_dict[ret:%d][sign1:%u][sign2:%u]", ret, node.sign1, node.sign2);
            return NOEXIST;
        }
        pos = node.cuint1;
        return pos;
    }

    int DictSeeker::seek_singer_singer(uint itemid, Singer_item_t **p, int &len)
    {
        if(0 == itemid){
            WARNING_LOG("error itemid[0]");
            return FAIL;
        }
        sodict_snode_t node;
        node.sign1 = itemid;
        node.sign2 = SINGER_SINGER_DICT;

        int ret = odb_seek_search(p_global.bigDict, &node);
        if (ret == ODB_SEEK_ERROR){
            WARNING_LOG("seek bigDict faild[ret:%d][sign1:%u][sign2:%u]", ret, node.sign1, node.sign2);
            return FAIL;
        }
        if (ret == ODB_SEEK_FAIL){
            TRACE_LOG("no matching found in bigDict[ret:%d][sign1:%u][sign2:%u]", ret, node.sign1, node.sign2);
            p = NULL;
            len = 0;
            return NOEXIST;
        }
        if (node.cuint1 + node.cuint2 > p_global.max_sisi_len){
            WARNING_LOG("bad pos[%u] len[%u] for singer-singer buf. max len[%u]",
                    node.cuint1, node.cuint2, p_global.max_sisi_len);
            return FAIL;
        }
        *p = p_global.singersingerlist + node.cuint1;
        len = node.cuint2;
        return SUCCESS;
    }

    int DictSeeker::seek_song_song(uint itemid, Song_item_t **p, int &len){
        if(0 == itemid){
            WARNING_LOG("error itemid[0]");
            return FAIL;
        }
        sodict_snode_t node;
        node.sign1 = itemid;
        node.sign2 = SONG_SONG_DICT;
        int ret = odb_seek_search(p_global.bigDict, &node);
        if (ret == ODB_SEEK_ERROR){
            WARNING_LOG("seek bigDict faild[ret:%d][sign1:%u][sign2:%u]", ret, node.sign1, node.sign2);
            return FAIL;
        }
        if (ret == ODB_SEEK_FAIL){
            TRACE_LOG("no matching found in bigDict[ret:%d][sign1:%u][sign2:%u]", ret, node.sign1, node.sign2);
            p = NULL;
            len = 0;
            return NOEXIST;
        }
        if (node.cuint1 + node.cuint2 > p_global.max_soso_len){
            WARNING_LOG("bad pos[%u] len[%u] for song-song buf. max len[%u]",
                    node.cuint1, node.cuint2, p_global.max_soso_len);
            return FAIL;
        }
        *p = p_global.songsonglist + node.cuint1;
        len = node.cuint2;
        return SUCCESS;
    }


    int DictSeeker::seek_lrmodel_pos(uint itemid, uint& lr_weight_pos, uint& lr_label_num){
        if(0 == itemid){
            WARNING_LOG("error itemid[0]");
            return FAIL;
        }
        sodict_snode_t node;
        node.sign1 = itemid;
        node.sign2 = itemid;
        int ret = odb_seek_search(p_global.lr_model_dict, &node);
        if (ret == ODB_SEEK_ERROR){
            WARNING_LOG("seek lr_feature_dict faild[ret:%d][sign1:%u][sign2:%u]", ret, node.sign1, node.sign2);
            return FAIL;
        }
        if (ret == ODB_SEEK_FAIL){
            //TRACE_LOG("no matching found in lr_feature_dict[ret:%d][sign1:%u][sign2:%u]", ret, node.sign1, node.sign2);
            return NOEXIST;
        }
        lr_weight_pos = node.cuint1;
        lr_label_num = node.cuint2;
        return SUCCESS;
    }


    int DictSeeker::seek_public_singer_song(uint itemid, uint ch_sign,
            Song_item_t** p, int &len){
        if(0 == itemid){
            WARNING_LOG("error itemid[0]");
            return FAIL;
        }
        sodict_snode_t node;
        node.sign1 = itemid;
        node.sign2 = ch_sign;
        int ret = odb_seek_search(p_global.bigDict, &node);
        if (ret == ODB_SEEK_ERROR){
            WARNING_LOG("seek bigDict faild [ret:%d][sign1:%u][sign2:%u]", ret, node.sign1, node.sign2);
            return FAIL;
        }
        if (ret == ODB_SEEK_FAIL){
            TRACE_LOG("no matching found in bigDict[ret:%d][sign1:%u][sign2:%u]", ret, node.sign1, node.sign2);
            p = NULL;
            len = 0;
            return NOEXIST;
        }
        if (node.cuint1 + node.cuint2 > p_global.max_publicrsingersong_len){
            WARNING_LOG("bad sign1[%u] sign2[%u] pos[%u] len[%u] for public-singer-song buf. max len[%u]",
                    node.sign1, node.sign2, node.cuint1, node.cuint2, p_global.max_publicrsingersong_len);
            return FAIL;
        }
        *p = p_global.public_rsingersong_list + node.cuint1;
        len = node.cuint2;
        return SUCCESS;
    }

    int DictSeeker::seek_singer_song(uint itemid, Song_item_t** p, int &len){
        if(0 == itemid){
            WARNING_LOG("error itemid[0]");
            return FAIL;
        }
        sodict_snode_t node;
        node.sign1 = itemid;
        node.sign2 = SINGER_SONG_DICT;
        int ret = odb_seek_search(p_global.bigDict, &node);
        if (ret == ODB_SEEK_ERROR){
            WARNING_LOG("seek bigDict faild [ret:%d][sign1:%u][sign2:%u]", ret, node.sign1, node.sign2);
            return FAIL;
        }
        if (ret == ODB_SEEK_FAIL){
            TRACE_LOG("no matching found in bigDict[ret:%d][sign1:%u][sign2:%u]", ret, node.sign1, node.sign2);
            p = NULL;
            len = 0;
            return NOEXIST;
        }
        if (node.cuint1 + node.cuint2 > p_global.max_siso_len){
            WARNING_LOG("bad pos[%u] len[%u] for singer-song buf. max len[%u]",
                    node.cuint1, node.cuint2, p_global.max_siso_len);
            return FAIL;
        }
        *p = p_global.singersonglist + node.cuint1;
        len = node.cuint2;
        return SUCCESS;
    }


    Song_brief_t* DictSeeker::get_song_brief(uint itemid){
        if(0 == itemid){
            WARNING_LOG("error itemid[0]");
            return NULL;
        }
        sodict_snode_t node;
        node.sign1 = itemid;
        node.sign2 = SONG_BRIEF;

        int ret = odb_seek_search(p_global.bigDict, &node);
        if (ret != ODB_SEEK_OK){
            //WARNING_LOG("get_song_brief seek bigDict faild [ret:%d][sign1:%u][sign2:%u]", ret,
            //            node.sign1, node.sign2);
            return NULL;
        }

        if (node.cuint1 >= p_global.max_songbrief_len){
            WARNING_LOG("bad pos[%u] for SONG_BRIEF buf. max len[%u]",
                    node.cuint1, p_global.max_songbrief_len);
            return NULL;
        }
        return  p_global.songbrieflist + node.cuint1;
    }

    int DictSeeker::get_channel_song_weight(uint songid, const char* ch_name){
        if(0 == songid){
            WARNING_LOG("error songid[0]");
            return -1;
        }
        sodict_snode_t node;
        char tmp_ch_name[MAX_CHNAME_LEN];
        snprintf(tmp_ch_name, MAX_CHNAME_LEN, "%s", ch_name);
        node.sign1 = creat_sign32(tmp_ch_name);
        node.sign2 = songid;
        int ret = odb_seek_search(p_global.channel_song_dict, &node);
        if (ret != ODB_SEEK_OK){
            return 0;
        }
        return node.cuint1;
    }


    int* DictSeeker::judge_detect_song(uint itemid, const char* ch_name){
        if(0 == itemid){
            WARNING_LOG("error itemid[0]");
            return NULL;
        }
        sodict_snode_t node;
        node.sign1 = itemid;
        char tmp_ch_name[MAX_CHNAME_LEN];
        snprintf(tmp_ch_name, MAX_CHNAME_LEN, "%s", ch_name);
        node.sign2 = creat_sign32(tmp_ch_name);

        int ret = odb_seek_search(p_global.detect_judge_song_dict, &node);
        if (ret != ODB_SEEK_OK){
            //WARNING_LOG("get_song_brief seek bigDict faild [ret:%d][sign1:%u][sign2:%u]", ret,
            //            node.sign1, node.sign2);
            return NULL;
        }

        if (node.cuint1 >= p_global.max_songbrief_len){
            WARNING_LOG("bad pos[%u] for judge_detect_song  buf. max len[%u]",
                    node.cuint1, p_global.max_detectjudge_song_len);
            return NULL;
        }
        return  p_global.detectjudge_list + node.cuint1;
    }


    int DictSeeker::get_rand_detect(uint &detectid, int dim, int cla, char* ch_name, const sodict_build_t *filter_dict){
        if(NULL == filter_dict){
            return -1;
        }
        if(NULL == ch_name){
            WARNING_LOG("error ch_name[NULL]");
            return FAIL;
        }
        DEBUG_LOG("begin to gen detect song dim[%d], cla[%d], ch_name[%s]", dim, cla, ch_name);
        sodict_snode_t node;
        node.sign1 = (dim<<16)|cla;
        node.sign2 = creat_sign32(ch_name);
        int ret = odb_seek_search(p_global.channel_detect_song_dict, &node);
        if (ret == ODB_SEEK_ERROR){
            WARNING_LOG("seek channel_detect_song_dict faild[ret:%d][sign1:%u][sign2:%u]", ret, node.sign1, node.sign2);
            return FAIL;
        }
        if (ret == ODB_SEEK_FAIL){
            TRACE_LOG("no matching found in channel_detect_song_dict[ret:%d][sign1:%u][sign2:%u]", ret, node.sign1, node.sign2);
            detectid=0;
            return NOEXIST;
        }
        if (node.cuint1 + node.cuint2 > p_global.max_channel_detect_song_len){
            WARNING_LOG("bad pos[%u] len[%u] for detect songlist buf. max len[%u]",
                    node.cuint1, node.cuint2, p_global.max_channel_detect_song_len);
            return FAIL;
        }
        int len = node.cuint2;
        for(int i = 0; i < 5; i++){
            int temp  = rand()%len;
            detectid = *(p_global.detectsong_list+ node.cuint1+temp);
            if(filt_song(filter_dict, detectid)){
                continue;
            }
            else{
                DEBUG_LOG("gen detect song dim [%d], cla[%d], ch_name[%s], songid[%d]", dim, cla, ch_name, detectid);
                return SUCCESS;
            }
        }
        return FAIL;
    }

    ch_info_t* DictSeeker::get_ch_info(uint ch_sign){
        if(0 == ch_sign){
            WARNING_LOG("error ch_sign[0]");
            return NULL;
        }
        sodict_snode_t node;
        node.sign1 = ch_sign;
        node.sign2 = CHANNEL_LIST_DICT;

        int ret = odb_seek_search(p_global.bigDict, &node);
        if (ret != ODB_SEEK_OK){
            WARNING_LOG("seek bigDict faild [ret:%d][sign1:%u][sign2:%u]", ret, node.sign1, node.sign2);
            return NULL;
        }

        if (node.cuint1 >= p_global.max_chinfolist_len){
            WARNING_LOG("bad pos[%u] forchinfolist buf. max len[%u]",
                    node.cuint1, p_global.max_chinfolist_len);
            return NULL;
        }
        return  p_global.ch_info_list + node.cuint1;
    }


    bool DictSeeker::has_ch(const char *ch_name){
        if(NULL == ch_name || strlen(ch_name) == 0){
            WARNING_LOG("error ch_name in ha_ch");
            return false;
        }
        sodict_snode_t node;
        char temp_ch_name[MAX_CHNAME_LEN];
        snprintf(temp_ch_name, MAX_CHNAME_LEN, "%s", ch_name);
        node.sign1 = creat_sign32(temp_ch_name);
        node.sign2 = CHANNEL_LIST_DICT;
        int ret = odb_seek_search(p_global.bigDict, &node);
        if (ret == ODB_SEEK_OK){
            return true;
        }
        return false;
    }

    bool DictSeeker::has_song_tag(uint song_id, uint tag_id){
        if(0 == song_id || 0 == tag_id){
            WARNING_LOG("error song_id or tag_id in has_song_tag");
            return false;
        }
        sodict_snode_t node;
        node.sign1 = song_id;
        node.sign2 = tag_id;
        int ret = odb_seek_search(p_global.song_tag_dict, &node);
        if (ret == ODB_SEEK_OK){
            return true;
        }
        return false;
    }

    bool DictSeeker::filt_song(const sodict_build_t* dict, uint songid){
        if(0 == songid){
            return true;
        }
        if(dict == NULL){
            return false;
        }
        sodict_snode_t node;
        node.sign1 = songid;
        node.sign2 = 0;//song type
        sodict_build_t* mydict = const_cast<sodict_build_t*>(dict);
        int ret = odb_seek(mydict,&node);
        if(ret == ODB_SEEK_OK){
            return true;
        }

        Song_brief_t* p_brief = this->get_song_brief(songid);
        if(NULL == p_brief){
            return false;
        }

        node.sign1 = p_brief->singer_id;
        node.sign2 = 1;//song type
        ret = odb_seek(mydict,&node);
        if(ret == ODB_SEEK_OK){
            return true;
        }
        return false;
    }

    /**
     *@brief:获取歌曲的歌手id
     *@param[in]:itemid,歌曲的id
     */
    uint DictSeeker::get_singer_id(uint itemid){
        Song_brief_t* p = get_song_brief(itemid);
        if(NULL == p){
            return 0;
        }
        if (p->singer_id < 0){
            return 0;
        }
        return  p->singer_id;
    }


    int DictSeeker::fill_filter_dict(const r_userdata_t &user_data,
            sodict_build_t* filter_dict){
        if(NULL == filter_dict){
            return -1;
        }
        //fill the filter dict
        int i=0;
        sodict_snode_t node;
        time_t now = time((time_t*)NULL);
        //获取垃圾桶歌曲统计
        const Item_bean* songhate = user_data.songhate;
        int len_songhate = user_data.len_songhate;
        if (len_songhate > 0){
            for(i=0;i<len_songhate;++i){
                node.sign1 = songhate[i].itemid;
                node.sign2 = 0;//song
                node.cuint1 = 0;
                node.cuint2 = 0;
                if (odb_add(filter_dict, &node, 1) == ODB_ADD_ERROR){
                    WARNING_LOG("add the node info into filter dict failed");
                }
            }
        }

        //过滤最近的下一首
        const Action_bean* action = user_data.action;
        int len_action = user_data.len_action;
        if (len_action > 0){
            for(i=0;i<len_action;++i){
                //过滤歌曲加入字典filter_dict
                if (action[i].type == DB_NEXT_SONG && now - action[i].date < JUMP_FILTER_TIME){
                    node.sign1 = action[i].itemid;
                    node.sign2 = 0;//song
                    node.cuint1 = 0;
                    node.cuint2 = 0;
                    if (odb_add(filter_dict, &node, 1) == ODB_ADD_ERROR){
                        WARNING_LOG("add the node info into filter dict failed");
                    }
                }
            }
        }

        //获取听过歌曲列表
        const Item_bean* p_listenhistory = user_data.listenhistory;
        int len_listenhistory = user_data.len_listenhistory;
        if(len_listenhistory > 0){
            //过滤歌曲加入字典filter_dict
            for(i = 0; i < len_listenhistory; ++i){
                if (now - p_listenhistory[i].date < LISTEN_FILTER_TIME){
                    node.sign1 = p_listenhistory[i].itemid;
                    node.sign2 = 0;//song
                    node.cuint1 = 0;
                    node.cuint2 = 0;
                    if (odb_add(filter_dict, &node, 1) == ODB_ADD_ERROR){
                        WARNING_LOG("add the node info into filter dict failed");
                    }
                }
            }
        }
        return 0;
    }

    int DictSeeker::fill_hate_dict(const r_userdata_t &user_data,
            sodict_build_t* filter_dict){
        if(NULL == filter_dict){
            return -1;
        }
        //fill the filter dict
        int i=0;
        sodict_snode_t node;
        //获取垃圾桶歌曲统计
        const Item_bean* songhate = user_data.songhate;
        int len_songhate = user_data.len_songhate;
        if (len_songhate > 0){
            for(i=0;i<len_songhate;++i){
                node.sign1 = songhate[i].itemid;
                node.sign2 = 0;//song
                node.cuint1 = 0;
                node.cuint2 = 0;
                if (odb_add(filter_dict, &node, 1) == ODB_ADD_ERROR){
                    WARNING_LOG("add the node info into filter dict failed");
                }
            }
        }
        return 0;
    }

    int DictSeeker::get_rand_top(uint &insertid, char* ch_name, sodict_build_t *filter_dict){
        if(NULL == filter_dict){
            return -1;
        }
        //fill the filter dict
        sodict_snode_t node;
        node.sign1 = creat_sign32(ch_name);
        node.sign2 = INSERT_SONG_DICT;
        int ret = odb_seek_search(p_global.bigDict, &node);
        if (ret == ODB_SEEK_ERROR){
            WARNING_LOG("seek bigDict faild [ret:%d][sign1:%u][sign2:%u]", ret, node.sign1, node.sign2);
            return FAIL;
        }
        if (ret == ODB_SEEK_FAIL){
            TRACE_LOG("no matching found in bigDict[ret:%d][sign1:%u][sign2:%u]", ret, node.sign1, node.sign2);
            insertid=0;
            return NOEXIST;
        }
        if (node.cuint1 + node.cuint2 > p_global.max_insertsong_len){
            WARNING_LOG("bad pos[%u] len[%u] for insert song buf. max len[%u]",
                    node.cuint1, node.cuint2, p_global.max_insertsong_len);
            return FAIL;
        }
        int len = node.cuint2;
        for(int i = 0; i < 5; i++){
            int temp  = rand()%len;
            insertid = (p_global.insertsong_list+ node.cuint1+temp)->sid;
            if(filt_song(filter_dict, insertid)){
                continue;
            }
            else{
                return SUCCESS;
            }
        }
        return FAIL;
    }

    int DictSeeker::fill_y_filter_dict(const y_user_data_t &user_data,
            sodict_build_t* filter_dict){
        if(NULL == filter_dict){
            return -1;
        }
        //fill the filter dict
        int i=0;
        sodict_snode_t node;
        time_t now = time((time_t*)NULL);
        //获取垃圾桶歌曲、最近的下一首、最近的60s歌曲
        const Action_bean* action = user_data.y_user_behavior;
        int len_action = user_data.len_y_user_behavior;
        for(int i = 0; i < len_action; ++i){
            switch(action[i].type){
            case NEXT_SONG:
                //过滤歌曲加入字典filter_dict
                if (now - action[i].date < JUMP_FILTER_TIME){
                    node.sign1 = action[i].itemid;
                    node.sign2 = 0;//song
                    node.cuint1 = 0;
                    node.cuint2 = 0;
                    if (odb_add(filter_dict, &node, 1) == ODB_ADD_ERROR){
                        WARNING_LOG("add the node info into filter dict failed");
                    }
                }
                break;
            case COMPLETE_SONG:
                if (now - action[i].date < LISTEN_FILTER_TIME){
                    node.sign1 = action[i].itemid;
                    node.sign2 = 0;//song
                    node.cuint1 = 0;
                    node.cuint2 = 0;
                    if (odb_add(filter_dict, &node, 1) == ODB_ADD_ERROR){
                        WARNING_LOG("add the node info into filter dict failed");
                    }
                }
                break;

            case HATE_SONG:
                node.sign1 = action[i].itemid;
                node.sign2 = 0;//song
                node.cuint1 = 0;
                node.cuint2 = 0;
                if (odb_add(filter_dict, &node, 1) == ODB_ADD_ERROR){
                    WARNING_LOG("add the node info into filter dict failed");
                }
                break;
            default:
                break;

            }

        }
        return 0;
    }


    int DictSeeker::fill_y_hate_dict(const y_user_data_t &user_data,
            sodict_build_t* filter_dict){
        if(NULL == filter_dict){
            return -1;
        }
        //fill the filter dict
        int i=0;
        sodict_snode_t node;
        //time_t now = time((time_t*)NULL);
        //获取垃圾桶歌曲、最近的下一首、最近的60s歌曲
        const Action_bean* action = user_data.y_user_behavior;
        int len_action = user_data.len_y_user_behavior;
        for(i = 0; i < len_action; ++i){
            switch(action[i].type){
            case HATE_SONG:
                node.sign1 = action[i].itemid;
                node.sign2 = 0;//song
                node.cuint1 = 0;
                node.cuint2 = 0;
                if (odb_add(filter_dict, &node, 1) == ODB_ADD_ERROR){
                    WARNING_LOG("add the node info into filter dict failed");
                }
                break;
            default:
                break;

            }

        }
        return 0;
    }

}

