#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "mcCache.h"
#include "macro.h"
#include "common.h"
#include "redis.h"
#include "mystring.h"
#include <algorithm>

using namespace rls;

int get_redis_ulikesongs(uint uid, Item_bean* redis_list,int &list_len){
    if(NULL == redis_list || uid <= 0){
        WARNING_LOG("wrong param in get_redis_ulikesongs");
        return FAIL;
    }

    if(NULL == p_global.redis_cli){
        WARNING_LOG("redis_client_manager exception");
        return FAIL;
    }

    store::RedisClient *client = NULL;
    client = p_global.redis_cli->fetch_client();
    if(NULL == client){
        WARNING_LOG("fetch client error\n");
        return FAIL;
    }

    client->set_logid(rand());

    int ret = -1;
    struct timeval s;
    struct timeval e;
    store::SimpleString value;
    char key[128];
    snprintf(key, 128, "cb_uls_%u", uid);

    DictSeeker* _dict_seeker = NULL;
    gettimeofday(&s,NULL);
    ret = client->get(key, value);
    gettimeofday(&e, NULL);
    if(ret == 0){
        if(value.len > 0){
            NOTICE_LOG("[query redis rlist success] cost[%d], key[%s], value:[%s]", TIMEMSECDIFF(s, e), key, value.str);
            _dict_seeker = new DictSeeker();

            std::vector<std::string> song_like_items;
            song_like_items.reserve(100);
            cmm::str_split(value.str, ",", song_like_items);
            NOTICE_LOG("split.size: %d", song_like_items.size());

            char *sep;
            char songidbuf[20];
            for(int i=0;i<song_like_items.size();i++)
            {
                if(list_len>= MAX_PREF_ITEM_NUM) break;
                const char *song_weight = song_like_items[i].c_str();
                NOTICE_LOG("process the song_weight pair: %s", song_weight);
                sep=strchr(song_weight,':');
                if(sep == NULL )
                {
                    WARNING_LOG("query redis song likeness error, the format is wrong!%s",song_weight);
                    goto EXIT_REDIS_FAIL;
                }
                sep=sep+1;
                sscanf(song_weight,"%[^:]", songidbuf);
                uint32_t songid=atoi(songidbuf);
                double weight_d = atof(sep);
                int weight=(int)weight_d*10000;

                //是否是合法歌曲
                //if(NULL == _dict_seeker->get_song_brief(songid)){
                //    continue;
                //}
                int i=0;
                bool needadd = true;
                for(i=0;i<list_len;i++)
                {
                    if(redis_list[i].itemid == songid)
                    {
                        needadd=false;
                        continue;
                    }
                }
                if(needadd)
                {
                    NOTICE_LOG("add songlove: %d", songid);
                    redis_list[list_len].itemid = songid;
                    snprintf(redis_list[list_len].ch_name, MAX_CHNAME_LEN, "%s", CH_80S_NAME);
                    redis_list[list_len].pref_type = DB_SONGLOVE;
                    redis_list[list_len].date =s.tv_sec ;
                    list_len ++;
                }
                NOTICE_LOG("Now the list_len: %d", list_len);

            }
        }else{
            NOTICE_LOG("[query redis rlist success] cost [%d], redis key not exists key:[%s], value:[%s]", TIMEMSECDIFF(s, e), key, value.str);
           // goto EXIT_REDIS_FAIL;
        }
    }else{
        WARNING_LOG("[redis hget fail cost[%d]], key[%s], errno:[%d]", TIMEMSECDIFF(s, e), key, client->get_err_no());
        goto EXIT_REDIS_FAIL;
    }

    if(NULL != _dict_seeker){
        delete _dict_seeker;
    }
    p_global.redis_cli->put_back_client(client);//最后必须归还
    return 0;

EXIT_REDIS_FAIL:
    if(NULL != _dict_seeker){
        delete _dict_seeker;
    }
    p_global.redis_cli->put_back_client(client);//最后必须归还
    return -1;
}

int get_redis_rlist(uint uid, const char *ch_name, const char *list_tag, const char *field, Song_item_t* redis_list, uint max_len, uint &list_len, uint redis_source,const sodict_build_t* filter_dict){
    if(NULL == redis_list || NULL == ch_name || NULL == field || NULL == list_tag || uid <= 0){
        WARNING_LOG("wrong param in get_redis_rlist");
        return FAIL;
    }
    //不用此份数据
    list_len = 0;
    return 0;

    if(NULL == p_global.redis_cli){
        WARNING_LOG("redis_client_manager exception");
        return FAIL;
    }

    store::RedisClient *client = NULL;
    client = p_global.redis_cli->fetch_client();
    if(NULL == client){
        WARNING_LOG("fetch client error\n");
        return FAIL;
    }

    client->set_logid(rand());
    list_len = 0;

    int ret = -1;
    struct timeval s;
    struct timeval e;
    store::ss value;
    char key[128];
    snprintf(key, 128, "%u_%s_%s", uid, ch_name, list_tag);

    DictSeeker* _dict_seeker = NULL;
    gettimeofday(&s,NULL);
    ret = client->hget(key, field, value);
    gettimeofday(&e, NULL);
    if(ret == 0){
        if(value.len > 0){
            NOTICE_LOG("[query redis rlist success] cost[%d], key[%s], value:[%s]", TIMEMSECDIFF(s, e), key, value.str);
            _dict_seeker = new DictSeeker();
            uint song_id, weight;
            char *in_ptr = NULL;
            char *out_ptr = NULL;
            char *in_str = NULL;
            char *out_str = strtok_r(value.str, ",", &out_ptr);
            while(out_str && list_len < max_len){
                in_str = strtok_r(out_str, ":", &in_ptr);
                if(in_str != NULL){
                    song_id = atoi(in_str);
                    in_str = strtok_r(NULL, ":", &in_ptr);
                    if(in_str != NULL){
                        if(NULL != filter_dict && _dict_seeker->filt_song(filter_dict, song_id)){
                            out_str = strtok_r(NULL, ",", &out_ptr);
                            continue;
                        }
                        //是否是合法歌曲
                        if(NULL == _dict_seeker->get_song_brief(song_id)){
                            out_str = strtok_r(NULL, ",", &out_ptr);
                            continue;
                        }
                        weight = atoi(in_str);
                        redis_list[list_len].song_id = song_id;
                        redis_list[list_len].weight = weight;
                        redis_list[list_len].source = redis_source;
                        list_len ++;
                    }else{
                        WARNING_LOG("key[%s] redis_values format invalid:[%s]", key, out_str);
                        goto EXIT_REDIS_FAIL;
                    }
                }else{
                    WARNING_LOG("key[%s] redis_values format invalid:[%s]", key, out_str);
                    goto EXIT_REDIS_FAIL;
                }

                DEBUG_LOG("song_id:[%d],weight:[%d]", song_id, weight);
                out_str = strtok_r(NULL, ",", &out_ptr);
            }
        }else{
            NOTICE_LOG("[query redis rlist success] cost [%d], redis key not exists key:[%s], value:[%s]", TIMEMSECDIFF(s, e), key, value.str);
            goto EXIT_REDIS_FAIL;
        }
    }else{
        WARNING_LOG("[redis hget fail cost[%d]], key[%s], errno:[%d]", TIMEMSECDIFF(s, e), key, client->get_err_no());
        goto EXIT_REDIS_FAIL;
    }

    if(NULL != _dict_seeker){
        delete _dict_seeker;
    }
    p_global.redis_cli->put_back_client(client);//最后必须归还
    return list_len;

EXIT_REDIS_FAIL:
    if(NULL != _dict_seeker){
        delete _dict_seeker;
    }
    p_global.redis_cli->put_back_client(client);//最后必须归还
    return 0;
}

int get_redis_sign(uint uid, const char *ch_name, const char *list_tag, const char *field, char *redis_sign, uint &dest_redis_sign_len){
    if(uid <= 0 || NULL == ch_name || NULL == redis_sign || NULL == field){
        WARNING_LOG("wrong params in get_redis_rlist_sign");
        return FAIL;
    }
    if(NULL == p_global.redis_cli){
        WARNING_LOG("redis_client_manager exception");
        return FAIL;
    }

    store::RedisClient *client = NULL;
    client = p_global.redis_cli->fetch_client();
    if(NULL == client){
        WARNING_LOG("fetch client error");
        return FAIL;
    }

    client->set_logid(rand());
    dest_redis_sign_len = 0;

    char redis_key[MAX_MCC_KEY_LEN];
    snprintf(redis_key, MAX_MCC_KEY_LEN, "%u_%s_%s", uid, ch_name, list_tag);
    store::ss value;
    int ret = -1;

    ret = client->hget(redis_key, field, value);
    if(ret == 0 && value.len > 0){
        NOTICE_LOG("get redis sign success, key:[%s], field[%s],value[%s]", redis_key, field, value.str);
        dest_redis_sign_len = value.len;
        snprintf(redis_sign, MAX_REDIS_SIGN_LEN, "%s", value.str);

        p_global.redis_cli->put_back_client(client);
        return SUCCESS;
    }else{
        NOTICE_LOG("get redis sign fail, key:[%s], field[%s],value[%s]", redis_key, field, value.str);
    }

    p_global.redis_cli->put_back_client(client);
    return FAIL;
}

int redis_get_random_list(Song_item_t* redis_list, uint max_len, uint &list_len, const sodict_build_t* filter_dict){
    if(NULL == redis_list){
        WARNING_LOG("list is null");
        return -1;
    }

    list_len = 0;
    return 0;//因大首页版权问题,暂时不用这份数据


    store::RedisClient *client = NULL;
    client = p_global.redis_cli->fetch_client();
    if(NULL == client){
        WARNING_LOG("fetch client error");
        return -1;
    }

    client->set_logid(rand());

    store::ss *query_list;
    int max_key_len = 128;
    char key[max_key_len];
    snprintf(key, max_key_len, "%s", RANDOM_LIST_REDIS_KEY);

    int ret = -1;
    int list_num = 0;
    ret = client->lrange(store::ss(key), 0, RANDOM_LIST_MAX_LEN, query_list, list_num);
    if(ret != 0){
        WARNING_LOG("lrange fail, key[%s], ret[%d]", key, ret);
        p_global.redis_cli->put_back_client(client);
        return -1;
    }else{
        NOTICE_LOG("query random song list from redis succ,key[%s], num[%d]", key, list_num);
    }

    std::random_shuffle(query_list, query_list + list_num);
    DictSeeker* _dict_seeker = new DictSeeker();
    int song_id = 0;
    for(int i = 0; i < list_num && list_len < max_len; i ++){
        song_id = atoi(query_list[i].str);
        if(NULL != filter_dict && _dict_seeker->filt_song(filter_dict, song_id)){
            continue;
        }

        redis_list[list_len].song_id = song_id;
        redis_list[list_len].weight = 1;
        redis_list[list_len].source = RANDOM_SOURCE;

        list_len ++;
    }

    if(NULL != _dict_seeker){
        delete _dict_seeker;
        _dict_seeker = NULL;
    }

    p_global.redis_cli->put_back_client(client);
    return list_len;
}
