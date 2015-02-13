#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include "mcCache.h"
#include "macro.h"
#include "common.h"
#include "dao.h"
#include "rls_instant.h"
#include <algorithm>
#include "redis.h"

using namespace rls;

/**
 * 对行为列表按照时间排序，降序
 */
bool user_real_behavior_cmp(Action_bean a, Action_bean b)
{
    return a.date > b.date;
}

/**
 *@brief:二分查找即时行为期间内的喜好行为
 *@param[in]:prefe_data, 喜好数据
 *@param[in]:len，喜好数据长度
 *@param[out]:len, 有效的即时喜好的长度
 */
int _check_prefer_date(int &len, Item_bean* prefe_data){
    int i_len = 0;
    if(prefe_data ==NULL || len <= 0){
        DEBUG_LOG("prefer data should be not NULL or prefer data len should be > 0");
        len = 0;
        return FAIL;
    }
    time_t now = time((time_t*) NULL);
    time_t begin_time = now - INSTANT_DAYS*86400;
    int low = 0 ;
    int high = len -1 ;
    int middle = 0;
    while(low < high - 1){
        middle = low + (high - low)/2;
        if(prefe_data[middle].date > begin_time){
            low = middle;
        }
        else{
            high = middle;
        }
    }
    if(prefe_data[high].date > begin_time){
        i_len = high;
    }
    else if(prefe_data[low].date > begin_time){
        i_len = low;
    }
    else{
        i_len = low -1;
    }
    i_len += 1;
    len = i_len;
    return i_len;
}

/**
 *@brief:即时建模有效的历史数据
 *@param[in]:history_data, 试听历史数据
 *@param[in]:len，数据总长度
 *@param[in]:ch_name, 频道名
 *@param[out]:len, 有效即时数据的长度
 */
int _check_histroy_date(int &len, Item_bean* history_data, const char * ch_name){
    int i_len = 0;
    if(history_data ==NULL || len <= 0){
        DEBUG_LOG("histroy data should be not NULL or histroy data len should be > 0");
        len = 0;
        return FAIL;
    }
    time_t now = time((time_t*) NULL);
    time_t begin_time = now - INSTANT_DAYS*86400;
    for(int i = 0; i < len; i++){
        if(history_data[i].date < begin_time){
            break;
        }
        if((strncmp(ch_name, history_data[i].ch_name, 32) == 0) || (strcmp(ch_name, CH_PRIVATE_NAME) == 0)){
            history_data[i_len++] = history_data[i];
        }
    }
    len = i_len;
    return i_len;
}

/**
 *@brief:即时建模有效的行为数据
 *@param[in]:action_data, 试听行为数据
 *@param[in]:len，数据总长度
 *@param[in]:ch_name，频道名
 *@param[out]:len, 有效即时数据的长度
 */
int _check_action_date(int &len, Action_bean* action_data, const char * ch_name){
    int i_len = 0;
    if(action_data ==NULL || len <= 0){
        DEBUG_LOG("action data should be not NULL or action data len should be > 0");
        len = 0;
        return FAIL;
    }
    time_t now = time((time_t*) NULL);
    time_t begin_time = now - INSTANT_DAYS*86400;
    for(int i = 0; i < len; i++){
        if(action_data[i].date < begin_time){
            break;
        }
        if(strncmp(ch_name, action_data[i].ch_name, 32) == 0 || strcmp(ch_name, CH_PRIVATE_NAME) == 0){
            action_data[i_len++] = action_data[i];
        }
    }
    len = i_len;
    return i_len;
}

int mcc_get_behavior(uint id, Action_bean* p, int buf_size){
    if(buf_size <= 0)
    {
        return 0;
    }
    if(NULL == p){
        WARNING_LOG("mcc_get_behavior param error[NULL == p]");
        return -1;
    }
    int res_len = 0;

    //查找下一首cache
    Action_bean action_next[MAX_ACTION_NUM_PER_TYPE];
    int action_next_len = -1;
    action_next_len = mcc_get_user_real_behavior_by_type(id, action_next, DB_NEXT_SONG, MAX_ACTION_NUM_PER_TYPE);
    if(action_next_len < 0){
        WARNING_LOG("get_action action_next fail");
        action_next_len = 0;
    }
    //查找上一首
    Action_bean action_previous[MAX_ACTION_NUM_PER_TYPE];
    int action_previous_len = -1;
    action_previous_len = mcc_get_user_real_behavior_by_type(id, action_previous, DB_PRE_SONG, MAX_ACTION_NUM_PER_TYPE);
    if(action_previous_len < 0){
        WARNING_LOG("get_action action_previous fail");
        action_previous_len = 0;
    }
    //音乐盒完整试听
    Action_bean action_box_list[MAX_BOX_ACTION_NUM];
    int action_box_list_len = -1;
    action_box_list_len = mcc_get_box_action(id, action_box_list, MAX_BOX_ACTION_NUM);
    if(action_box_list_len < 0){
        WARNING_LOG("get_action action_box_list fail");
        action_box_list_len = 0;
    }

    //整合如上4种行为数据
    std::merge(action_next, action_next + action_next_len, \
        action_previous, action_previous + action_previous_len,\
        p, user_real_behavior_cmp);
    res_len += action_next_len + action_previous_len;
    memcpy(p + action_previous_len + action_next_len, action_box_list, action_box_list_len * sizeof(Action_bean));
    res_len +=  action_box_list_len;
    std::inplace_merge(p, p + action_next_len + action_previous_len, p + res_len, user_real_behavior_cmp);

#ifdef _DEBUG_TIME
    //debug中输出查找到的用户行为结果
    DEBUG_LOG("all behavior len [%d]", res_len);
    for(int i = 0; i < res_len; i++){
        DEBUG_LOG("the behavior: uid[%u], pos[%d], itemid[%d], type[%d], time[%ld]", id, i, p[i].itemid, p[i].type, p[i].date);
    }
#endif
    return res_len;
}

int mcc_get_box_action(uint id, Action_bean* p, int buf_size){
    if(buf_size <= 0)
    {
        return 0;
    }
    if(NULL == p){
        WARNING_LOG("mcc_get_box_action param error[NULL == p]");
        return -1;
    }
    //cache选择

    struct timeval s;
    struct timeval e;
    int ret = -1;
    int res_len = 0;
    char key[MAX_MCC_KEY_LEN];
    snprintf(key, MAX_MCC_KEY_LEN, "%s_%u", BOX_ACTION, id);
    char* value = NULL;
    int value_len = 0;
    bsl::ResourcePool rp;//负责value的内存分配
    time_t expire = g_config.mcc_user_behavior_timeout;

    gettimeofday(&s,NULL);
    ret = p_global.mcc->get(key, strlen(key), value, value_len, expire, rp);

    //查找失败
    //MC2.0 get在没找到的情况下也会返回<0的值，MC1.0则只有在连接MC失败时才返回<0,所以先注释
    /*if (ret != 0){
        gettimeofday(&e,NULL);
        WARNING_LOG("third[mcc_third_fail], cost[%d] [get mcc fail], key[%s], ret[%d]", TIMEMSECDIFF(s, e), key, ret);
        return -1;
    }

    //查找成功
    if(NULL != value || 0 == value_len){*/
    if(ret == 0){
        memcpy(p, value, value_len);
        res_len  = value_len/sizeof(Action_bean);
        gettimeofday(&e,NULL);
        NOTICE_LOG("third[mcc_third], cost[%d] [get mcc success], len[%d], key[%s], ret[%d]", TIMEMSECDIFF(s, e), res_len, key, ret);
#ifdef _DEBUG_TIME
        DEBUG_LOG("the box behaqvior data is in cache: key[%s], len[%d]", key, res_len);
        for(int i = 0; i < res_len; i++){
            DEBUG_LOG("the box behaqvior data: pos[%d], song_id[%u], date[%ld]", i, p[i].itemid, p[i].date);
        }
#endif
        return res_len;
    }
    //没命中cache
    gettimeofday(&e,NULL);
    NOTICE_LOG("third[mcc_third], cost[%d] [get mcc no shoot], key[%s], ret[%d]", TIMEMSECDIFF(s, e), key, ret);
    res_len = db_get_user_behavior(id, p, buf_size);
    if(res_len < 0){
        WARNING_LOG("read box behaqvior from db faild.ret[%d]",ret);
        res_len = 0;
        return -1;
    }
    else{
        gettimeofday(&s,NULL);
        ret = p_global.mcc->add(key, strlen(key), (char*)p, sizeof(Item_bean) * res_len, expire);
        if(0 != ret)
        {
            gettimeofday(&e,NULL);
            WARNING_LOG("third[mcc_third_fail], cost[%d] [put mcc fail], len[%d], key[%s], ret[%d]", TIMEMSECDIFF(s, e), res_len, key, ret);
        }
        else{
            gettimeofday(&e,NULL);
            NOTICE_LOG("third[mcc_third], cost[%d] [put mcc success], len[%d], key[%s], ret[%d]", TIMEMSECDIFF(s, e), res_len, key, ret);
        }
    }
    return res_len;
}


int mcc_get_user_real_behavior_by_type(uint id, Action_bean* p, enum DB_USER_BEHAVIOR_TYPE type, int buf_size){
    if(buf_size <= 0)
    {
        return 0;
    }
    if(NULL == p){
        WARNING_LOG("get_action param error[NULL == p]");
        return -1;
    }
    //cache选择
    char cache_type[MAX_CACHE_PRE_LEN];
    switch (type) {
        case DB_BOX_COMPLETE_TYPE:
            snprintf(cache_type, MAX_CACHE_PRE_LEN, "%s", ACTION_BOX_HISTORY);
            break;
        case DB_PRE_SONG:
            snprintf(cache_type, MAX_CACHE_PRE_LEN, "%s", ACTION_PREVIOUS);
            break;
        case DB_NEXT_SONG:
            snprintf(cache_type, MAX_CACHE_PRE_LEN, "%s", ACTION_NEXT);
            break;
        case DB_SEARCH_SONG:
            snprintf(cache_type, MAX_CACHE_PRE_LEN, "%s", ACTION_BOX_SEARCH);
            break;
        default:
            WARNING_LOG("mcc_get_user_real_behavior_by_type param error");
            return -1;
    }
    struct timeval s;
    struct timeval e;
    int ret = -1;
    int res_len = 0;
    char key[MAX_MCC_KEY_LEN];
    char* value = NULL;
    int value_len = 0;
    bsl::ResourcePool rp;//负责value的内存分配
    time_t expire = g_config.mcc_user_behavior_timeout;

    gettimeofday(&s,NULL);
    snprintf(key, MAX_MCC_KEY_LEN, "%s_%u", cache_type, id);
    ret = p_global.mcc->get(key, strlen(key), value, value_len, expire, rp);
    /*
    //查找失败
    if (ret != 0){
        gettimeofday(&e,NULL);
        WARNING_LOG("third[mcc_third_fail], cost[%d] [get mcc fail], key[%s], ret[%d]", TIMEMSECDIFF(s, e), key, ret);
        return -1;
    }
    //查找成功
    if(NULL != value || 0 == value_len){*/
    if(ret == 0){
        memcpy(p, value, value_len);
        res_len  = value_len/sizeof(Action_bean);
        gettimeofday(&e,NULL);
        NOTICE_LOG("third[mcc_third], cost[%d] [get mcc success], len[%d], key[%s], ret[%d]", TIMEMSECDIFF(s, e), res_len, key, ret);
#ifdef _DEBUG_TIME
        DEBUG_LOG("the user behavior data is in cache: key[%s], len[%d]", key, res_len);
        for(int i = 0; i < res_len; i++){
            DEBUG_LOG("user behavior data: pos[%d], song_id[%u], date[%ld]", i, p[i].itemid, p[i].date);
        }
#endif
        return res_len;
    }
    //没命中cache
    gettimeofday(&e,NULL);
    NOTICE_LOG("third[mcc_third], cost[%d] [get mcc no shoot], key[%s], ret[%d]", TIMEMSECDIFF(s, e), key, ret);
    res_len = db_get_user_real_behavior(id, p, type, buf_size);
    if(res_len < 0){
        WARNING_LOG("read user_real_behavior from db faild.ret[%d]",ret);
        res_len = 0;
        return -1;
    }
    else{
        gettimeofday(&s,NULL);
        ret = p_global.mcc->add(key, strlen(key), (char*)p, sizeof(Item_bean) * res_len, expire);
        if(0 != ret)
        {
            gettimeofday(&e,NULL);
            WARNING_LOG("third[mcc_third_fail], cost[%d] [put mcc fail], len[%d], key[%s], ret[%d]", TIMEMSECDIFF(s, e), res_len, key, ret);
        }
        else{
            gettimeofday(&e,NULL);
            NOTICE_LOG("third[mcc_third], cost[%d] [put mcc success], len[%d], key[%s], ret[%d]", TIMEMSECDIFF(s, e), res_len, key, ret);
        }
    }
    return res_len;
}

int mcc_add_y_user_behavior(uint id, uint itemid, int type, const char* ch_name){
    int ret = -1;
    ret = db_add_y_user_behavior(id, itemid, type, ch_name);
    if(ret != 0)
    {
        WARNING_LOG("db_add_y_user_behavior [id:%u][itemid:%u][fail:%d]",
                id,itemid,ret);
        return -1;
    }
    struct timeval s;
    struct timeval e;
    char key[MAX_MCC_KEY_LEN];
    time_t expire = g_config.mcc_user_behavior_timeout;
    gettimeofday(&s,NULL);
    snprintf(key, MAX_MCC_KEY_LEN, "%s_%u", Y_USER_BEHAVIOR, id);
    ret = p_global.mcc->del(key, strlen(key));
    if (ret != 0){
        gettimeofday(&e,NULL);
        NOTICE_LOG("third[mcc_third_fail], cost[%d] [del mcc fail], key[%s], ret[%d]", TIMEMSECDIFF(s, e), key, ret);
    }
    else{
        gettimeofday(&e,NULL);
        NOTICE_LOG("third[mcc_third], cost[%d] [del mcc success], key[%s], ret[%d]", TIMEMSECDIFF(s, e), key, ret);
    }
    return 0;
}

int mcc_add_co_y_user_behavior(uint id, const char *baiduid_str, uint itemid, int type, const char* ch_name){
    int ret = -1;
    ret = db_add_co_y_user_behavior(id, baiduid_str,itemid,type, ch_name);
    if(ret != 0)
    {
        WARNING_LOG("db_add_co_y_user_behavior [id:%u][itemid:%u][fail:%d]",
                id,itemid,ret);
        return -1;
    }
    struct timeval s;
    struct timeval e;
    char key[MAX_MCC_KEY_LEN];
    time_t expire = g_config.mcc_co_user_behavior_timeout;
    gettimeofday(&s,NULL);
    snprintf(key, MAX_MCC_KEY_LEN, "%s_%u", CO_Y_USER_BEHAVIOR, id);
    ret = p_global.mcc->del(key, strlen(key));
    if (ret != 0){
        gettimeofday(&e,NULL);
        NOTICE_LOG("third[mcc_third_fail], cost[%d] [del mcc fail], key[%s], ret[%d]", TIMEMSECDIFF(s, e), key, ret);
    }
    else{
        gettimeofday(&e,NULL);
        NOTICE_LOG("third[mcc_third], cost[%d] [del mcc success], key[%s], ret[%d]", TIMEMSECDIFF(s, e), key, ret);
    }
    return 0;
}



int mcc_add_user_real_behavior(uint id, uint itemid, enum DIANTAI_USER_BEHAVIOR_TYPE type, const char* ch_name){
    int ret = -1;
    //cache选择
    char cache_type[MAX_CACHE_PRE_LEN];
    DB_USER_BEHAVIOR_TYPE db_type;
    switch (type) {
        case PRE_SONG:
            db_type = DB_PRE_SONG;
            snprintf(cache_type, MAX_CACHE_PRE_LEN, "%s", ACTION_PREVIOUS);
            break;
        case NEXT_SONG:
            db_type = DB_NEXT_SONG;
            snprintf(cache_type, MAX_CACHE_PRE_LEN, "%s", ACTION_NEXT);
            break;
        default:
            WARNING_LOG("bad behavior type param error");
            return -1;
    }
    ret = db_add_user_real_behavior(id,itemid,db_type, ch_name);
    if(ret != 0)
    {
        WARNING_LOG("db_add_user_real_behavior [id:%u][itemid:%u][fail:%d]",
                id,itemid,ret);
        return -1;
    }
    struct timeval s;
    struct timeval e;
    char key[MAX_MCC_KEY_LEN];
    time_t expire = g_config.mcc_user_behavior_timeout;
    gettimeofday(&s,NULL);
    snprintf(key, MAX_MCC_KEY_LEN, "%s_%u", cache_type, id);
    ret = p_global.mcc->del(key, strlen(key));
    if (ret != 0){
        gettimeofday(&e,NULL);
        NOTICE_LOG("third[mcc_third_fail], cost[%d] [del mcc fail], key[%s], ret[%d]", TIMEMSECDIFF(s, e), key, ret);
    }
    else{
        gettimeofday(&e,NULL);
        NOTICE_LOG("third[mcc_third], cost[%d] [del mcc success], key[%s], ret[%d]", TIMEMSECDIFF(s, e), key, ret);
    }
    return 0;
}


int mcc_add_co_user_real_behavior(uint id, const char *baiduid_str, uint itemid, enum DIANTAI_USER_BEHAVIOR_TYPE type, const char* ch_name){
    int ret = -1;
    //cache选择
    char cache_type[MAX_CACHE_PRE_LEN];
    DB_USER_BEHAVIOR_TYPE db_type;
    switch (type) {
        case PRE_SONG:
            db_type = DB_PRE_SONG;
            snprintf(cache_type, MAX_CACHE_PRE_LEN, "%s", CO_ACTION_PREVIOUS);
            break;
        case NEXT_SONG:
            db_type = DB_NEXT_SONG;
            snprintf(cache_type, MAX_CACHE_PRE_LEN, "%s", CO_ACTION_NEXT);
            break;
        default:
            WARNING_LOG("bad behavior type param error");
            return -1;
    }
    ret = db_add_co_user_real_behavior(id, baiduid_str,itemid,db_type, ch_name);
    if(ret != 0)
    {
        WARNING_LOG("db_add_co_user_real_behavior [id:%u][itemid:%u][fail:%d]",
                id,itemid,ret);
        return -1;
    }
    struct timeval s;
    struct timeval e;
    char key[MAX_MCC_KEY_LEN];
    time_t expire = g_config.mcc_co_user_behavior_timeout;
    gettimeofday(&s,NULL);
    snprintf(key, MAX_MCC_KEY_LEN, "%s_%u", cache_type, id);
    ret = p_global.mcc->del(key, strlen(key));
    if (ret != 0){
        gettimeofday(&e,NULL);
        NOTICE_LOG("third[mcc_third_fail], cost[%d] [del mcc fail], key[%s], ret[%d]", TIMEMSECDIFF(s, e), key, ret);
    }
    else{
        gettimeofday(&e,NULL);
        NOTICE_LOG("third[mcc_third], cost[%d] [del mcc success], key[%s], ret[%d]", TIMEMSECDIFF(s, e), key, ret);
    }
    return 0;
}


int mcc_update_co_pref_data(uint id, const char* baiduid_str, uint itemid, enum DB_PREF_TYPE type,
                      enum DB_DEL_TYPE del_flag, const char* ch_name){
    int ret = -1;
    ret = db_update_co_pref(id, baiduid_str, itemid, type, del_flag, ch_name);
    if(ret != 0)
    {
        WARNING_LOG("db_update_co_pref [id:%u][itemid:%u][fail:%d]",
                id,itemid,ret);
        return -1;
    }
    //cache选择
    char cache_type[MAX_CACHE_PRE_LEN];
    DB_USER_BEHAVIOR_TYPE db_type;
    switch (type) {
        case DB_SONGLOVE:
            snprintf(cache_type, MAX_CACHE_PRE_LEN, "%s", CO_LOVE_SONG);
            break;
        case DB_SONGHATE:
            snprintf(cache_type, MAX_CACHE_PRE_LEN, "%s", CO_HATE_SONG);
            break;
        default:
            WARNING_LOG("bad prefer type param error");
            return -1;
    }
    struct timeval s;
    struct timeval e;
    char key[MAX_MCC_KEY_LEN];
    time_t expire = g_config.mcc_co_item_pref_timeout;
    gettimeofday(&s,NULL);
    snprintf(key, MAX_MCC_KEY_LEN, "%s_%u", cache_type, id);
    ret = p_global.mcc->del(key, strlen(key));
    if (ret != 0){
        gettimeofday(&e,NULL);
        NOTICE_LOG("third[mcc_third_fail], cost[%d] [del mcc fail], key[%s], ret[%d]", TIMEMSECDIFF(s, e), key, ret);
    }
    else{
        gettimeofday(&e,NULL);
        NOTICE_LOG("third[mcc_third], cost[%d] [del mcc success], key[%s], ret[%d]", TIMEMSECDIFF(s, e), key, ret);
    }
    return 0;
}


int mcc_update_pref_data(uint id, enum DB_PREF_TYPE type, const char* ch_name){
    //不用数据库操作
    //cache选择
    char cache_type[MAX_CACHE_PRE_LEN];
    switch (type) {
        case DB_SONGLOVE:
            snprintf(cache_type, MAX_CACHE_PRE_LEN, "%s", USC_LOVE_SONG);
            break;
        case DB_SONGHATE:
            snprintf(cache_type, MAX_CACHE_PRE_LEN, "%s", USC_HATE_SONG);
            break;
        default:
            WARNING_LOG("bad prefer type param error");
            return -1;
    }
    struct timeval s;
    struct timeval e;
    int ret = -1;
    char key[MAX_MCC_KEY_LEN];
    time_t expire = g_config.mcc_usc_timeout;
    gettimeofday(&s,NULL);
    snprintf(key, MAX_MCC_KEY_LEN, "%s_%u", cache_type, id);
    ret = p_global.mcc->del(key, strlen(key));
    if (ret != 0){
        gettimeofday(&e,NULL);
        NOTICE_LOG("third[mcc_third_fail], cost[%d] [del mcc fail], key[%s], ret[%d]", TIMEMSECDIFF(s, e), key, ret);
    }
    else{
        gettimeofday(&e,NULL);
        NOTICE_LOG("third[mcc_third], cost[%d] [del mcc success], key[%s], ret[%d]", TIMEMSECDIFF(s, e), key, ret);
    }
    return 0;
}


int mcc_get_co_box_action(uint id, Action_bean* p, int buf_size){
    if(buf_size <= 0)
    {
        return 0;
    }
    if(NULL == p){
        WARNING_LOG("mcc_get_co_box_action param error[NULL == p]");
        return -1;
    }
    //cache选择

    struct timeval s;
    struct timeval e;
    int ret = -1;
    int res_len = 0;
    char key[MAX_MCC_KEY_LEN];
    snprintf(key, MAX_MCC_KEY_LEN, "%s_%u", CO_BOX_ACTION, id);
    char* value = NULL;
    int value_len = 0;
    bsl::ResourcePool rp;//负责value的内存分配
    time_t expire = g_config.mcc_co_user_behavior_timeout;

    gettimeofday(&s,NULL);
    ret = p_global.mcc->get(key, strlen(key), value, value_len, expire, rp);
    /*
    //查找失败
    if (ret != 0){
        gettimeofday(&e,NULL);
        WARNING_LOG("third[mcc_third_fail], cost[%d] [get mcc fail], key[%s], ret[%d]", TIMEMSECDIFF(s, e), key, ret);
        return -1;
    }
    //查找成功
    if(NULL != value || 0 == value_len){*/
    if(ret == 0){
        memcpy(p, value, value_len);
        res_len  = value_len/sizeof(Action_bean);
        gettimeofday(&e,NULL);
        NOTICE_LOG("third[mcc_third], cost[%d] [get mcc success], len[%d], key[%s], ret[%d]", TIMEMSECDIFF(s, e), res_len, key, ret);
#ifdef _DEBUG_TIME
        DEBUG_LOG("the co box behaqvior data is in cache: key[%s], len[%d]", key, res_len);
        for(int i = 0; i < res_len; i++){
            DEBUG_LOG("the co box behaqvior data: pos[%d], song_id[%u], date[%ld]", i, p[i].itemid, p[i].date);
        }
#endif
        return res_len;
    }
    //没命中cache
    gettimeofday(&e,NULL);
    NOTICE_LOG("third[mcc_third], cost[%d] [get mcc no shoot], key[%s], ret[%d]", TIMEMSECDIFF(s, e), key, ret);
    res_len = db_get_co_user_behavior(id, p, buf_size);
    if(res_len < 0){
        WARNING_LOG("read co box behaqvior from db faild.ret[%d]",ret);
        res_len = 0;
        return -1;
    }
    else{
        gettimeofday(&s,NULL);
        ret = p_global.mcc->add(key, strlen(key), (char*)p, sizeof(Item_bean) * res_len, expire);
        if(0 != ret)
        {
            gettimeofday(&e,NULL);
            WARNING_LOG("third[mcc_third_fail], cost[%d] [put mcc fail], len[%d], key[%s], ret[%d]", TIMEMSECDIFF(s, e), res_len, key, ret);
        }
        else{
            gettimeofday(&e,NULL);
            NOTICE_LOG("third[mcc_third], cost[%d] [put mcc success], len[%d], key[%s], ret[%d]", TIMEMSECDIFF(s, e), res_len, key, ret);
        }
    }
    return res_len;
}


int mcc_get_co_behavior(uint id, Action_bean* p, int buf_size){
    if(buf_size <= 0)
    {
        return 0;
    }
    if(NULL == p){
        WARNING_LOG("mcc_get_co_behavior param error[NULL == p]");
        return -1;
    }
    int res_len = 0;

    //查找下一首cache
    Action_bean action_next[MAX_ACTION_NUM_PER_TYPE];
    int action_next_len = -1;
    action_next_len = mcc_get_co_user_real_behavior_by_type(id, action_next, DB_NEXT_SONG, MAX_ACTION_NUM_PER_TYPE);
    if(action_next_len < 0){
        WARNING_LOG("get_action action_next fail");
        action_next_len = 0;
    }
    //查找上一首
    Action_bean action_previous[MAX_ACTION_NUM_PER_TYPE];
    int action_previous_len = -1;
    action_previous_len = mcc_get_co_user_real_behavior_by_type(id, action_previous, DB_PRE_SONG, MAX_ACTION_NUM_PER_TYPE);
    if(action_previous_len < 0){
        WARNING_LOG("get_action action_previous fail");
        return -1;
    }
    //音乐盒数据
    Action_bean box_action_list[MAX_ACTION_NUM_PER_TYPE];
    int box_action_list_len = -1;
    box_action_list_len = mcc_get_co_box_action(id, box_action_list, MAX_BOX_ACTION_NUM);
    if(box_action_list_len < 0){
        WARNING_LOG("get_action mcc_get_co_box_action fail");
        box_action_list_len = 0;
    }
    //整合如上4种行为数据
    std::merge(action_next, action_next + action_next_len, \
        action_previous, action_previous + action_previous_len,\
        p, user_real_behavior_cmp);
    res_len += action_next_len + action_previous_len;
    memcpy(p + action_next_len + action_previous_len, box_action_list, box_action_list_len * sizeof(Action_bean));
    res_len += box_action_list_len;
    std::inplace_merge(p, p + action_next_len + action_previous_len, p + res_len, user_real_behavior_cmp);

#ifdef _DEBUG_TIME
    //debug中输出查找到的用户行为结果
    for(int i = 0; i < res_len; i++){
        DEBUG_LOG("the co_user_real_behavior: uid[%u], pos[%d], itemid[%d], type[%d], time[%ld]", id, i, p[i].itemid, p[i].type, p[i].date);
    }
#endif
    return res_len;
}


int mcc_get_co_user_real_behavior_by_type(uint id, Action_bean* p, enum DB_USER_BEHAVIOR_TYPE type, int buf_size){
    if(buf_size <= 0)
    {
        return 0;
    }
    if(NULL == p){
        WARNING_LOG("get_action param error[NULL == p]");
        return -1;
    }
    //cache选择
    char cache_type[MAX_CACHE_PRE_LEN];
    switch (type) {
        case DB_BOX_COMPLETE_TYPE:
            snprintf(cache_type, MAX_CACHE_PRE_LEN, "%s", CO_ACTION_BOX_HISTORY);
            break;
        case DB_PRE_SONG:
            snprintf(cache_type, MAX_CACHE_PRE_LEN, "%s", CO_ACTION_PREVIOUS);
            break;
        case DB_NEXT_SONG:
            snprintf(cache_type, MAX_CACHE_PRE_LEN, "%s", CO_ACTION_NEXT);
            break;
        case DB_SEARCH_SONG:
            snprintf(cache_type, MAX_CACHE_PRE_LEN, "%s", CO_ACTION_BOX_SEARCH);
            break;
        default:
            WARNING_LOG("mcc_get_co_user_real_behavior_by_type param error");
            return -1;
    }
    struct timeval s;
    struct timeval e;
    int ret = -1;
    int res_len = 0;
    char key[MAX_MCC_KEY_LEN];
    char* value = NULL;
    int value_len = 0;
    bsl::ResourcePool rp;//负责value的内存分配
    time_t expire = g_config.mcc_co_user_behavior_timeout;

    gettimeofday(&s,NULL);
    snprintf(key, MAX_MCC_KEY_LEN, "%s_%u", cache_type, id);
    ret = p_global.mcc->get(key, strlen(key), value, value_len, expire, rp);
    /*
    //查找失败
    if (ret != 0){
        gettimeofday(&e,NULL);
        WARNING_LOG("third[mcc_third_fail], cost[%d] [get mcc fail], key[%s], ret[%d]", TIMEMSECDIFF(s, e), key, ret);
        return -1;
    }
    //查找成功
    if(NULL != value || 0 == value_len){*/
    if(ret == 0){
        memcpy(p, value, value_len);
        res_len  = value_len/sizeof(Action_bean);
        gettimeofday(&e,NULL);
        NOTICE_LOG("third[mcc_third], cost[%d] [get mcc success], len[%d], key[%s], ret[%d]", TIMEMSECDIFF(s, e), res_len, key, ret);
#ifdef _DEBUG_TIME
        DEBUG_LOG("the co user behavior data is in cache: key[%s], len[%d]", key, res_len);
        for(int i = 0; i < res_len; i++){
            DEBUG_LOG("the co user behavior data: pos[%d], song_id[%u], date[%ld]", i, p[i].itemid, p[i].date);
        }
#endif
        return res_len;
    }
    //没命中cache
    gettimeofday(&e,NULL);
    NOTICE_LOG("third[mcc_third], cost[%d] [get mcc no shoot], key[%s], ret[%d]", TIMEMSECDIFF(s, e), key, ret);
    res_len = db_get_co_user_real_behavior(id, p, type, buf_size);
    if(res_len < 0){
        WARNING_LOG("read co_user_real_behavior from db faild.ret[%d]",ret);
        res_len = 0;
        return -1;
    }
    else{
        gettimeofday(&s,NULL);
        ret = p_global.mcc->add(key, strlen(key), (char*)p, sizeof(Item_bean) * res_len, expire);
        if(0 != ret)
        {
            gettimeofday(&e,NULL);
            WARNING_LOG("third[mcc_third_fail], cost[%d] [put mcc fail], len[%d], key[%s], ret[%d]", TIMEMSECDIFF(s, e), res_len, key, ret);
        }
        else{
            gettimeofday(&e,NULL);
            NOTICE_LOG("third[mcc_third], cost[%d] [put mcc success], len[%d], key[%s], ret[%d]", TIMEMSECDIFF(s, e), res_len, key, ret);
        }
    }
    return res_len;
}

int mcc_get_listen_history(uint id, Item_bean* p, int buf_size){
    if(buf_size <= 0)
    {
        return 0;
    }
    if(NULL == p){
        WARNING_LOG("get_listen_history param error[NULL == p]");
        return -1;
    }
    struct timeval s;
    struct timeval e;
    int ret = -1;
    int res_len = 0;
    char key[MAX_MCC_KEY_LEN];
    snprintf(key, MAX_MCC_KEY_LEN, "%s_%u", LISTEN_HISTORY, id);
    char* value = NULL;
    int value_len = 0;
    bsl::ResourcePool rp;//负责value的内存分配
    time_t expire = g_config.mcc_listen_history_timeout;

    //查找cache
    gettimeofday(&s,NULL);
    ret = p_global.mcc->get(key, strlen(key), value, value_len, expire, rp);
    /*
    //查找失败
    if (ret != 0){
        gettimeofday(&e,NULL);
        WARNING_LOG("third[mcc_third_fail], cost[%d] [get mcc fail], key[%s], ret[%d]", TIMEMSECDIFF(s, e), key, ret);
        return -1;
    }
    //查找成功
    if(NULL != value || 0 == value_len){*/
    if(ret == 0){
        memcpy(p, value, value_len);
        res_len  = value_len/sizeof(Item_bean);
        gettimeofday(&e,NULL);
        NOTICE_LOG("third[mcc_third], cost[%d] [get mcc success], len[%d], key[%s], ret[%d]", TIMEMSECDIFF(s, e), res_len, key, ret);
#ifdef _DEBUG_TIME
        DEBUG_LOG("the listen histroy data is in cache: key[%s], len[%d]", key, res_len);
        for(int i = 0; i < res_len; i++){
            DEBUG_LOG("the listen history data: pos[%d], song_id[%u], date[%ld]", i, p[i].itemid, p[i].date);
        }
#endif
        return res_len;
    }
    //没命中cache
    gettimeofday(&e,NULL);
    NOTICE_LOG("third[mcc_third], cost[%d] [get mcc no shoot], key[%s], ret[%d]", TIMEMSECDIFF(s, e), key, ret);
    res_len = db_get_listen_history(id, p, buf_size);
    if(res_len < 0){
        WARNING_LOG("read listen_history from db faild.ret[%d]",ret);
        res_len = 0;
    }
    else{
        gettimeofday(&s,NULL);
        ret = p_global.mcc->add(key, strlen(key), (char*)p, sizeof(Item_bean) * res_len, expire);
        if(0 != ret)
        {
            gettimeofday(&e,NULL);
            WARNING_LOG("third[mcc_third_fail], cost[%d] [put mcc fail], len[%d], key[%s], ret[%d]", TIMEMSECDIFF(s, e), res_len, key, ret);
        }
        else{
            gettimeofday(&e,NULL);
            NOTICE_LOG("third[mcc_third], cost[%d] [put mcc success], len[%d], key[%s], ret[%d]", TIMEMSECDIFF(s, e), res_len, key, ret);
        }
    }
    return res_len;
}


int mcc_get_co_listen_history(uint id, Item_bean* p, int buf_size){
    if(buf_size <= 0)
    {
        return 0;
    }
    if(NULL == p){
        WARNING_LOG("get_co_listen_history param error[NULL == p]");
        return -1;
    }
    struct timeval s;
    struct timeval e;
    gettimeofday(&s,NULL);
    int ret = -1;
    int res_len = 0;
    char key[MAX_MCC_KEY_LEN];
    snprintf(key, MAX_MCC_KEY_LEN, "%s_%u", CO_LISTEN_HISTORY, id);
    char* value = NULL;
    int value_len = 0;
    bsl::ResourcePool rp;//负责value的内存分配
    time_t expire = g_config.mcc_co_listen_history_timeout;

    //查找cache
    ret = p_global.mcc->get(key, strlen(key), value, value_len, expire, rp);
    /*
    //查找失败
    if (ret != 0){
        gettimeofday(&e,NULL);
        WARNING_LOG("third[mcc_third_fail], cost[%d] [get mcc fail], key[%s], ret[%d]", TIMEMSECDIFF(s, e), key, ret);
        return -1;
    }
    //查找成功
    if(NULL != value || 0 == value_len){*/
    if(ret == 0){
        memcpy(p, value, value_len);
        res_len  = value_len/sizeof(Item_bean);
        gettimeofday(&e,NULL);
        NOTICE_LOG("third[mcc_third], cost[%d] [get mcc success], len[%d], key[%s], ret[%d]", TIMEMSECDIFF(s, e), res_len, key, ret);
#ifdef _DEBUG_TIME
        DEBUG_LOG("the co listen histroy data is in cache: key[%s], len[%d]", key, res_len);
        for(int i = 0; i < res_len; i++){
            DEBUG_LOG("co listen history: pos[%d], song_id[%u], date[%ld]", i, p[i].itemid, p[i].date);
        }
#endif
        return res_len;
    }

    //没命中cache
    gettimeofday(&e,NULL);
    NOTICE_LOG("third[mcc_third], cost[%d] [get mcc no shoot], key[%s], ret[%d]", TIMEMSECDIFF(s, e), key, ret);
    res_len = db_get_co_listen_history(id, p, buf_size);
    if(res_len < 0){
        WARNING_LOG("read co_listen_history from db faild.ret[%d]",ret);
        res_len = 0;
        return -1;
    }
    else{
        gettimeofday(&s,NULL);
        ret = p_global.mcc->add(key, strlen(key), (char*)p, sizeof(Item_bean) * res_len, expire);
        if(0 != ret)
        {
            gettimeofday(&e,NULL);
            WARNING_LOG("third[mcc_third_fail], cost[%d] [put mcc fail], len[%d], key[%s], ret[%d]", TIMEMSECDIFF(s, e), res_len, key, ret);
        }
        else{
            gettimeofday(&e,NULL);
            NOTICE_LOG("third[mcc_third], cost[%d] [put mcc success], len[%d], key[%s], ret[%d]", TIMEMSECDIFF(s, e), res_len, key, ret);
        }
    }
    return res_len;
}

int mcc_add_co_listen_history(uint id, const char* baiduid_str, uint itemid, const char* ch_name){
    int ret = db_add_co_listen_history(id, baiduid_str, itemid, ch_name);
    if(ret != 0){
        WARNING_LOG("add_co_listen_history fail[id:%u][itemid:%u][fail:%d]",
                id, itemid, ret);
        return -1;
    }
    //删除缓存
    struct timeval s;
    struct timeval e;
    gettimeofday(&s,NULL);
    char key[MAX_MCC_KEY_LEN];
    snprintf(key, MAX_MCC_KEY_LEN, "%s_%u", CO_LISTEN_HISTORY, id);
    ret = p_global.mcc->del(key, strlen(key));
    if (ret != 0){
        gettimeofday(&e,NULL);
        NOTICE_LOG("third[mcc_third_fail], cost[%d] [del mcc fail], key[%s], ret[%d]", TIMEMSECDIFF(s, e), key, ret);
    }
    else{
        gettimeofday(&e,NULL);
        NOTICE_LOG("third[mcc_third], cost[%d] [del mcc success], key[%s], ret[%d]", TIMEMSECDIFF(s, e), key, ret);
    }
    return 0;
}

int mcc_add_listen_history(uint id, uint itemid, const char* ch_name){
    int ret = db_add_listen_history(id, itemid, ch_name);
    if(ret != 0){
        WARNING_LOG("add_listen_history fail [id:%u][itemid:%u][fail:%d]",
                id, itemid, ret);
        return -1;
    }
    //删除缓存
    struct timeval s;
    struct timeval e;
    gettimeofday(&s,NULL);
    char key[MAX_MCC_KEY_LEN];
    snprintf(key, MAX_MCC_KEY_LEN, "%s_%u", LISTEN_HISTORY, id);
    ret = p_global.mcc->del(key, strlen(key));
    if (ret != 0){
        gettimeofday(&e,NULL);
        NOTICE_LOG("third[mcc_third_fail], cost[%d] [del mcc fail], key[%s], ret[%d]", TIMEMSECDIFF(s, e), key, ret);
    }
    else{
        gettimeofday(&e,NULL);
        NOTICE_LOG("third[mcc_third], cost[%d] [del mcc success], key[%s], ret[%d]", TIMEMSECDIFF(s, e), key, ret);
    }
    return 0;
}

int mcc_get_user_data(UscGetter &usc_getter, uint id, r_userdata_t &user_data){
    time_t max_time = 0;
    user_data.len_songlove = 0;
    user_data.len_songhate = 0;
    user_data.len_songcloud = 0;
    user_data.len_listenhistory = 0;
    user_data.len_action = 0;
    int ret = -1;

    //喜欢歌曲
    ret = mcc_get_usc_data(usc_getter, user_data.songlove, (uint&)user_data.len_songlove, DB_SONGLOVE, id, (uint)MAX_PREF_ITEM_NUM);
    if (ret != 0){
        WARNING_LOG("mcc_get_usc_data fail, msg[songlove]");
        user_data.len_songlove = 0;
    }
    else{
        if(user_data.len_songlove > 0){
            user_data.maxtime_songlove = user_data.songlove[0].date;
            max_time = max_time > user_data.songlove[0].date ? max_time : user_data.songlove[0].date;
        }
    }

    // 添加从行为推荐获取的喜欢歌曲
    /*
    NOTICE_LOG("try to get data from redis,the number of songlove is %u ", user_data.len_songlove);
    ret = get_redis_ulikesongs(id, user_data.songlove,(int &)(user_data.len_songlove));
    if (ret != 0){
        WARNING_LOG("get redis ulikesongs fail, msg[songlove]");
        //user_data.len_songlove = 0;
    }
    else{
        if(user_data.len_songlove > 0){
            user_data.maxtime_songlove = user_data.songlove[0].date;
            max_time = max_time > user_data.songlove[0].date ? max_time : user_data.songlove[0].date;
        }
    }
    NOTICE_LOG("end of get data from redis,the number of songlove is %u ", user_data.len_songlove);
    */

    //不喜欢歌曲
    ret = mcc_get_usc_data(usc_getter, user_data.songhate, (uint&)user_data.len_songhate, DB_SONGHATE, id, (uint)MAX_PREF_ITEM_NUM);
    if (ret != 0){
        WARNING_LOG("mcc_get_usc_data fail, msg[songhate]");
        user_data.len_songhate = 0;
    }
    else{
        if(user_data.len_songhate > 0){
            user_data.maxtime_songhate = user_data.songhate[0].date;
            max_time = max_time > user_data.songhate[0].date ? max_time : user_data.songhate[0].date;
        }
    }
    //云歌曲
    ret = mcc_get_usc_data(usc_getter, user_data.songcloud, (uint&)user_data.len_songcloud, DB_SONGCLOUD, id,  (uint)MAX_PREF_ITEM_NUM);
    if (ret != 0){
        WARNING_LOG("mcc_get_usc_data fail, msg[songcloud]");
        user_data.len_songcloud = 0;
    }
    else{
        if(user_data.len_songcloud > 0){
            user_data.maxtime_songcloud = user_data.songcloud[0].date;
            max_time = max_time > user_data.songcloud[0].date ? max_time : user_data.songcloud[0].date;
        }
    }
    //电台试听历史数据
    int len_listenhistory = mcc_get_listen_history(id, user_data.listenhistory);
    if(len_listenhistory < 0){
        WARNING_LOG("mcc_get_listen_history fail, msg[listenhistory]");
        len_listenhistory = 0;
    }
    else{
        user_data.len_listenhistory = len_listenhistory;
        if(len_listenhistory > 0){
            max_time = max_time > user_data.listenhistory[0].date ? max_time : user_data.listenhistory[0].date;
            user_data.maxtime_listenhistory = user_data.listenhistory[0].date;
        }
    }
    //获取用户行为数据并统计最近行为日期
    int len_action = mcc_get_behavior(id, user_data.action);
    if(len_action < 0){
        WARNING_LOG("mcc_get_user_real_behavior fail, msg[listenhistory]");
        len_action = 0;
    }
    else{
        user_data.len_action = len_action;
        if(len_action > 0){
            max_time = max_time > user_data.listenhistory[0].date ? max_time : user_data.listenhistory[0].date;
            user_data.maxtime_listenhistory = user_data.listenhistory[0].date;
        }
    }

    user_data.maxtime_all = max_time;
    user_data.isset = true;
    return SUCCESS;
}


int mcc_get_co_user_data(uint id, r_userdata_t &user_data){
    time_t max_time = 0;
    user_data.len_songlove = 0;
    user_data.len_songhate = 0;
    user_data.len_songcloud = 0;
    user_data.len_listenhistory = 0;
    user_data.len_action = 0;
    int ret = -1;

    //喜欢歌曲
    ret = mcc_get_co_pref_data(user_data.songlove, (uint&)user_data.len_songlove, DB_SONGLOVE, id, (uint)MAX_PREF_ITEM_NUM);
    if (ret != 0){
        WARNING_LOG("mcc_get_co_pref_data fail, msg[songlove]");
        user_data.len_songlove = 0;
    }
    else{
        if(user_data.len_songlove > 0){
            user_data.maxtime_songlove = user_data.songlove[0].date;
            max_time = max_time > user_data.songlove[0].date ? max_time : user_data.songlove[0].date;
        }
    }
    //不喜欢歌曲
    ret = mcc_get_co_pref_data(user_data.songhate, (uint&)user_data.len_songhate, DB_SONGHATE, id, (uint)MAX_PREF_ITEM_NUM);
    if (ret != 0){
        WARNING_LOG("mcc_get_co_pref_data fail, msg[songhate]");
        user_data.len_songhate = 0;
    }
    else{
        if(user_data.len_songhate > 0){
            user_data.maxtime_songhate = user_data.songhate[0].date;
            max_time = max_time > user_data.songhate[0].date ? max_time : user_data.songhate[0].date;
        }
    }
    //cookie用户无云歌曲
    user_data.len_songcloud = 0;

    //电台试听历史数据
    int len_listenhistory = mcc_get_co_listen_history(id, user_data.listenhistory);
    if(len_listenhistory < 0){
        WARNING_LOG("mcc_get_co_listen_history fail, msg[listenhistory]");
        len_listenhistory = 0;
    }
    else{
        user_data.len_listenhistory = len_listenhistory;
        if(len_listenhistory > 0){
            max_time = max_time > user_data.listenhistory[0].date ? max_time : user_data.listenhistory[0].date;
            user_data.maxtime_listenhistory = user_data.listenhistory[0].date;
        }
    }
    //获取用户行为数据并统计最近行为日期
    int len_action = mcc_get_co_behavior(id, user_data.action);
    if(len_action < 0){
        WARNING_LOG("mcc_get_co_user_real_behavior fail, msg[listenhistory]");
        len_action = 0;
    }
    else{
        user_data.len_action = len_action;
        if(len_action > 0){
            max_time = max_time > user_data.listenhistory[0].date ? max_time : user_data.listenhistory[0].date;
            user_data.maxtime_listenhistory = user_data.listenhistory[0].date;
        }
    }
    user_data.maxtime_all = max_time;
    user_data.isset = true;
    return SUCCESS;
}

int mcc_get_y_user_data(uint id, y_user_data_t &user_data){
    user_data.len_y_user_behavior = 0;
    int ret = -1;
    //百度音乐人行为
    ret = mcc_get_y_user_behavior(user_data.y_user_behavior, id, (uint)MAX_Y_USER_BEHAVIOR_NUM);
    if (ret < 0){
        WARNING_LOG("mcc_get_y_user_behavior fail");
        user_data.len_y_user_behavior = 0;
    }
    else{
        user_data.len_y_user_behavior = ret;
    }
    //其它...
    user_data.isset = true;
    return SUCCESS;
}

int mcc_get_co_y_user_data(uint id, y_user_data_t &user_data){
    user_data.len_y_user_behavior = 0;
    int ret = -1;
    //百度音乐人行为
    ret = mcc_get_co_y_user_behavior(user_data.y_user_behavior, id, (uint)MAX_Y_USER_BEHAVIOR_NUM);
    if (ret < 0){
        WARNING_LOG("mcc_get_co_y_user_behavior fail");
        user_data.len_y_user_behavior = 0;
    }
    else{
        user_data.len_y_user_behavior = ret;
    }
    //其它...
    user_data.isset = true;
    return SUCCESS;
}

int mcc_get_y_user_behavior(Action_bean* p, uint id, int buf_size){
    if(buf_size <= 0)
    {
        return 0;
    }
    if(NULL == p){
        WARNING_LOG("get_y_user_behavior param error[NULL == p]");
        return -1;
    }
    struct timeval s;
    struct timeval e;
    int ret = -1;
    int res_len = 0;
    char key[MAX_MCC_KEY_LEN];
    snprintf(key, MAX_MCC_KEY_LEN, "%s_%u", Y_USER_BEHAVIOR, id);
    char* value = NULL;
    int value_len = 0;
    bsl::ResourcePool rp;//负责value的内存分配
    time_t expire = g_config.mcc_y_user_behavior_timeout;

    //查找cache
    gettimeofday(&s,NULL);
    ret = p_global.mcc->get(key, strlen(key), value, value_len, expire, rp);
    /*
    //查找失败
    if (ret != 0){
        gettimeofday(&e,NULL);
        WARNING_LOG("third[mcc_third_fail], cost[%d] [get mcc fail], key[%s], ret[%d]", TIMEMSECDIFF(s, e), key, ret);
        return -1;
    }
    //查找成功
    if(NULL != value || 0 == value_len){*/
    if(ret == 0){
        memcpy(p, value, value_len);
        res_len  = value_len/sizeof(Action_bean);
        gettimeofday(&e,NULL);
        NOTICE_LOG("third[mcc_third], cost[%d] [get mcc succAction_beaness], len[%d], key[%s], ret[%d]", TIMEMSECDIFF(s, e), res_len, key, ret);
#ifdef _DEBUG_TIME
        DEBUG_LOG("the y user behavior data is in cache: key[%s], len[%d]", key, res_len);
        for(int i = 0; i < res_len; i++){
            DEBUG_LOG("the y user behavior data: pos[%d], song_id[%u], date[%ld]", i, p[i].itemid, p[i].date);
        }
#endif
        return res_len;
    }
    //没命中cache
    gettimeofday(&e,NULL);
    NOTICE_LOG("third[mcc_third], cost[%d] [get mcc no shoot], key[%s], ret[%d]", TIMEMSECDIFF(s, e), key, ret);
    res_len = db_get_y_user_behavior(id, p, buf_size);
    if(res_len < 0){
        WARNING_LOG("read y_user_behavior from db faild.ret[%d]",ret);
        res_len = 0;
    }
    else{
        gettimeofday(&s,NULL);
        ret = p_global.mcc->add(key, strlen(key), (char*)p, sizeof(Action_bean) * res_len, expire);
        if(0 != ret)
        {
            gettimeofday(&e,NULL);
            WARNING_LOG("third[mcc_third_fail], cost[%d] [put mcc fail], len[%d], key[%s], ret[%d]", TIMEMSECDIFF(s, e), res_len, key, ret);
        }
        else{
            gettimeofday(&e,NULL);
            NOTICE_LOG("third[mcc_third], cost[%d] [put mcc success], len[%d], key[%s], ret[%d]", TIMEMSECDIFF(s, e), res_len, key, ret);
        }
    }
    return res_len;
}


int mcc_get_co_y_user_behavior(Action_bean* p, uint id, int buf_size){
    if(buf_size <= 0)
    {
        return 0;
    }
    if(NULL == p){
        WARNING_LOG("get_co_y_user_behavior param error[NULL == p]");
        return -1;
    }
    struct timeval s;
    struct timeval e;
    int ret = -1;
    int res_len = 0;
    char key[MAX_MCC_KEY_LEN];
    snprintf(key, MAX_MCC_KEY_LEN, "%s_%u", CO_Y_USER_BEHAVIOR, id);
    char* value = NULL;
    int value_len = 0;
    bsl::ResourcePool rp;//负责value的内存分配
    time_t expire = g_config.mcc_co_y_user_behavior_timeout;

    //查找cache
    gettimeofday(&s,NULL);
    ret = p_global.mcc->get(key, strlen(key), value, value_len, expire, rp);
    /*
    //查找失败
    if (ret != 0){
        gettimeofday(&e,NULL);
        WARNING_LOG("third[mcc_third_fail], cost[%d] [get mcc fail], key[%s], ret[%d]", TIMEMSECDIFF(s, e), key, ret);
        return -1;
    }
    //查找成功
    if(NULL != value || 0 == value_len){*/
    if(ret == 0){
        memcpy(p, value, value_len);
        res_len  = value_len/sizeof(Action_bean);
        gettimeofday(&e,NULL);
        NOTICE_LOG("third[mcc_third], cost[%d] [get mcc success], len[%d], key[%s], ret[%d]", TIMEMSECDIFF(s, e), res_len, key, ret);
#ifdef _DEBUG_TIME
        DEBUG_LOG("the co y user behavior data is in cache: key[%s], len[%d]", key, res_len);
        for(int i = 0; i < res_len; i++){
            DEBUG_LOG("the co y user behavior data: pos[%d], song_id[%u], date[%ld]", i, p[i].itemid, p[i].date);
        }
#endif
        return res_len;
    }
    //没命中cache
    gettimeofday(&e,NULL);
    NOTICE_LOG("third[mcc_third], cost[%d] [get mcc no shoot], key[%s], ret[%d]", TIMEMSECDIFF(s, e), key, ret);
    res_len = db_get_co_y_user_behavior(id, p, buf_size);
    if(res_len < 0){
        WARNING_LOG("read co_y_user_behavior from db faild.ret[%d]",ret);
        res_len = 0;
    }
    else{
        gettimeofday(&s,NULL);
        ret = p_global.mcc->add(key, strlen(key), (char*)p, sizeof(Action_bean) * res_len, expire);
        if(0 != ret)
        {
            gettimeofday(&e,NULL);
            WARNING_LOG("third[mcc_third_fail], cost[%d] [put mcc fail], len[%d], key[%s], ret[%d]", TIMEMSECDIFF(s, e), res_len, key, ret);
        }
        else{
            gettimeofday(&e,NULL);
            NOTICE_LOG("third[mcc_third], cost[%d] [put mcc success], len[%d], key[%s], ret[%d]", TIMEMSECDIFF(s, e), res_len, key, ret);
        }
    }
    return res_len;
}

/**
 *@brief:获取即时行为的用户的数据
 *@param[in]:id,用户id
 *@param[in]:is_login是否是登陆用户
 *@param[out]:i_user_data, 用户数据
 *@return:函数执行情况返回值
 */
int mcc_get_instant_user_data(UscGetter &usc_getter, uint id, i_userdata_t &i_user_data, char * ch_name){
    if(NULL == ch_name){
        WARNING_LOG("the channel name is NULL");
        return -1;
    }
    i_user_data.len_songlove = 0;
    i_user_data.len_songhate = 0;
    i_user_data.len_songcloud = 0;
    i_user_data.len_listenhistory = 0;
    i_user_data.len_action = 0;
    int ret = -1;

    //喜欢歌曲
    ret = mcc_get_usc_data(usc_getter, i_user_data.songlove, (uint&)i_user_data.len_songlove, DB_SONGLOVE, id, (uint)MAX_PREF_ITEM_NUM);
    if (ret != 0){
        WARNING_LOG("mcc_get_usc_data fail, msg[songlove]");
        i_user_data.len_songlove = 0;
    }
    else{
        if(i_user_data.len_songlove > 0){
            _check_prefer_date(i_user_data.len_songlove, i_user_data.songlove);
        }
    }
    //不喜欢歌曲
    ret = mcc_get_usc_data(usc_getter, i_user_data.songhate, (uint&)i_user_data.len_songhate, DB_SONGHATE, id, (uint)MAX_PREF_ITEM_NUM);
    if (ret != 0){
        WARNING_LOG("mcc_get_usc_data fail, msg[songhate]");
        i_user_data.len_songhate = 0;
    }
    else{
        if(i_user_data.len_songhate > 0){
            _check_prefer_date(i_user_data.len_songhate, i_user_data.songhate);
        }

    }
    //云歌曲
    ret = mcc_get_usc_data(usc_getter, i_user_data.songcloud, (uint&)i_user_data.len_songcloud, DB_SONGCLOUD, id, (uint)MAX_PREF_ITEM_NUM);
    if (ret != 0){
        WARNING_LOG("mcc_get_usc_data fail, msg[songcloud]");
        i_user_data.len_songcloud = 0;
    }
    else{
        if(i_user_data.len_songcloud > 0){
            _check_prefer_date(i_user_data.len_songcloud, i_user_data.songcloud);
        }
    }

    //获取电台试听历史数据
    int len_listenhistory = mcc_get_listen_history(id, i_user_data.listenhistory, MAX_LISTENED_ITEM_NUM);
    if(len_listenhistory < 0){
        i_user_data.len_listenhistory = 0;
    }
    else{
        i_user_data.len_listenhistory = len_listenhistory;
        _check_histroy_date(i_user_data.len_listenhistory, i_user_data.listenhistory, ch_name);
    }

    //获取用户行为数据并统计最近行为日期
    int len_action = mcc_get_behavior(id, i_user_data.action, MAX_ACTION_ITEM_NUM);
    if(len_action < 0){
        i_user_data.len_action = 0;
    }
    else{
        i_user_data.len_action = len_action;
        _check_action_date(i_user_data.len_action, i_user_data.action, ch_name);
    }
    return 0;
}

/**
 *@brief:获取即时行为的用户的数据
 *@param[in]:id,用户id
 *@param[in]:is_login是否是登陆用户
 *@param[out]:i_user_data, 用户数据
 *@return:函数执行情况返回值
 */
int mcc_get_co_instant_user_data(uint id, i_userdata_t &i_user_data, char * ch_name){
    if(NULL == ch_name){
        WARNING_LOG("the channel name is NULL");
        return -1;
    }
    i_user_data.len_songlove = 0;
    i_user_data.len_songhate = 0;
    i_user_data.len_songcloud = 0;
    i_user_data.len_listenhistory = 0;
    i_user_data.len_action = 0;
    int ret = -1;

    //喜欢歌曲
    ret = mcc_get_co_pref_data(i_user_data.songlove, (uint&)i_user_data.len_songlove, DB_SONGLOVE, id, (uint)MAX_PREF_ITEM_NUM);
    if (ret != 0){
        WARNING_LOG("mcc_get_co_pref_data fail, msg[songlove]");
        i_user_data.len_songlove = 0;
    }
    else{
        if(i_user_data.len_songlove > 0){
            _check_prefer_date(i_user_data.len_songlove, i_user_data.songlove);
        }
    }
    //不喜欢歌曲
    ret = mcc_get_co_pref_data(i_user_data.songhate, (uint&)i_user_data.len_songhate, DB_SONGHATE, id, (uint)MAX_PREF_ITEM_NUM);
    if (ret != 0){
        WARNING_LOG("mcc_get_co_pref_data fail, msg[songhate]");
        i_user_data.len_songhate = 0;
    }
    else{
        if(i_user_data.len_songhate > 0){
            _check_prefer_date(i_user_data.len_songhate, i_user_data.songhate);
        }

    }
    //cookie无云歌曲
    i_user_data.len_songcloud = 0;

    //获取电台试听历史数据
    int len_listenhistory = mcc_get_co_listen_history(id, i_user_data.listenhistory, MAX_LISTENED_ITEM_NUM);
    if(len_listenhistory < 0){
        i_user_data.len_listenhistory = 0;
    }
    else{
        i_user_data.len_listenhistory = len_listenhistory;
        _check_histroy_date(i_user_data.len_listenhistory, i_user_data.listenhistory, ch_name);
    }

    //获取用户行为数据并统计最近行为日期
    int len_action = mcc_get_co_behavior(id, i_user_data.action, MAX_ACTION_ITEM_NUM);
    if(len_action < 0){
        i_user_data.len_action = 0;
    }
    else{
        i_user_data.len_action = len_action;
        _check_action_date(i_user_data.len_action, i_user_data.action, ch_name);
    }
    return 0;
}


int mcc_get_co_pref_data(Item_bean *p, uint &len_items, enum DB_PREF_TYPE type, uint id, uint buf_size){
    if(buf_size <= 0)
    {
        len_items = 0;
        return 0;
    }
    if(NULL == p){
        WARNING_LOG("mcc_get_co_pref_data param error[NULL == p]");
        len_items = 0;
        return -1;
    }
    //cache选择
    char cache_type[MAX_CACHE_PRE_LEN];
    switch (type) {
    case DB_SONGLOVE:
        snprintf(cache_type, MAX_CACHE_PRE_LEN, "%s", CO_LOVE_SONG);
        break;
    case DB_SONGHATE:
        snprintf(cache_type, MAX_CACHE_PRE_LEN, "%s", CO_HATE_SONG);
        break;
    default:
        WARNING_LOG("mcc_get_co_pref_data param error");
        return -1;
    }

    struct timeval s;
    struct timeval e;
    int ret = -1;
    int res_len = 0;
    char key[MAX_MCC_KEY_LEN];
    char* value = NULL;
    int value_len = 0;
    bsl::ResourcePool rp;//负责value的内存分配
    time_t expire = g_config.mcc_usc_timeout;

    gettimeofday(&s,NULL);
    snprintf(key, MAX_MCC_KEY_LEN, "%s_%u", cache_type, id);
    ret = p_global.mcc->get(key, strlen(key), value, value_len, expire, rp);
    /*
    //查找失败
    if (ret != 0){
        gettimeofday(&e,NULL);
        WARNING_LOG("third[mcc_third_fail], cost[%d] [get mcc fail], key[%s], ret[%d]", TIMEMSECDIFF(s, e), key, ret);
        len_items = 0;
        return -1;
    }
    //查找成功
    if(NULL != value || 0 == value_len){*/
    if(ret == 0){
        memcpy(p, value, value_len);
        res_len  = value_len/sizeof(Item_bean);
        gettimeofday(&e,NULL);
        NOTICE_LOG("third[mcc_third], cost[%d] [get mcc success], len[%d], key[%s], ret[%d]", TIMEMSECDIFF(s, e), res_len, key, ret);
        len_items = res_len;
#ifdef _DEBUG_TIME
        DEBUG_LOG("the co pref data is in cache: key[%s], len[%d]", key, res_len);
        for(int i = 0; i < res_len; i++){
            DEBUG_LOG("usc data: pos[%d], song_id[%u], date[%ld]", i, p[i].itemid, p[i].date);
        }
#endif
        return 0;
    }
    //没命中cache
    gettimeofday(&e,NULL);
    NOTICE_LOG("third[mcc_third], cost[%d] [get mcc no shoot], key[%s], ret[%d]", TIMEMSECDIFF(s, e), key, ret);
    uint total;
    res_len = db_get_co_pref_data(id, type, p);
    if(res_len < 0){
        WARNING_LOG("db_get_co_pref_data faild.ret[%d]",ret);
        res_len = 0;
        len_items = res_len;
        return -1;
    }
    else{
        gettimeofday(&s,NULL);
        ret = p_global.mcc->add(key, strlen(key), (char*)p, sizeof(Item_bean) * res_len, expire);
        if(0 != ret)
        {
            gettimeofday(&e,NULL);
            WARNING_LOG("third[mcc_third_fail], cost[%d] [put mcc fail], len[%d], key[%s], ret[%d]", TIMEMSECDIFF(s, e), res_len, key, ret);
        }
        else{
            gettimeofday(&e,NULL);
            NOTICE_LOG("third[mcc_third], cost[%d] [put mcc success], len[%d], key[%s], ret[%d]", TIMEMSECDIFF(s, e), res_len, key, ret);
        }
    }
    len_items = res_len;
    return 0;
}



int mcc_get_usc_data(UscGetter &usc_getter, Item_bean *p, uint &len_items, enum DB_PREF_TYPE type, uint id, uint buf_size){
    if(buf_size <= 0)
    {
        len_items = 0;
        return 0;
    }
    if(NULL == p){
        WARNING_LOG("get_action param error[NULL == p]");
        len_items = 0;
        return -1;
    }
    //cache选择
    char cache_type[MAX_CACHE_PRE_LEN];
    switch (type) {
    case DB_SONGLOVE:
        snprintf(cache_type, MAX_CACHE_PRE_LEN, "%s", USC_LOVE_SONG);
        break;
    case DB_SONGHATE:
        snprintf(cache_type, MAX_CACHE_PRE_LEN, "%s", USC_HATE_SONG);
        break;
    case DB_SONGCLOUD:
        snprintf(cache_type, MAX_CACHE_PRE_LEN, "%s", USC_CLOUD_SONG);
        break;
    default:
        WARNING_LOG("mcc_get_usc_data param error");
        return -1;
    }

    struct timeval s;
    struct timeval e;
    int ret = -1;
    int res_len = 0;
    char key[MAX_MCC_KEY_LEN];
    char* value = NULL;
    int value_len = 0;
    bsl::ResourcePool rp;//负责value的内存分配
    time_t expire = g_config.mcc_usc_timeout;

    gettimeofday(&s,NULL);
    snprintf(key, MAX_MCC_KEY_LEN, "%s_%u", cache_type, id);
    ret = p_global.mcc->get(key, strlen(key), value, value_len, expire, rp);
    /*
    //查找失败
    if (ret != 0){
        gettimeofday(&e,NULL);
        WARNING_LOG("third[mcc_third_fail], cost[%d] [get mcc fail], key[%s], ret[%d]", TIMEMSECDIFF(s, e), key, ret);
        len_items = 0;
        return -1;
    }
    //查找成功
    if(NULL != value || 0 == value_len){*/
    if(ret == 0){
        memcpy(p, value, value_len);
        res_len  = value_len/sizeof(Item_bean);
        gettimeofday(&e,NULL);
        NOTICE_LOG("third[mcc_third], cost[%d] [get mcc success], len[%d], key[%s], ret[%d]", TIMEMSECDIFF(s, e), res_len, key, ret);
        len_items = res_len;
#ifdef _DEBUG_TIME
        //输出usc cache数据
        DEBUG_LOG("the usc data is in cache: key[%s], len[%d]", key, res_len);
        for(int i = 0; i < res_len; i++){
            DEBUG_LOG("usc data: pos[%d], song_id[%u], date[%ld]", i, p[i].itemid, p[i].date);
        }
#endif
        return 0;
    }
    //没命中cache
    gettimeofday(&e,NULL);
    NOTICE_LOG("third[mcc_third], cost[%d] [get mcc no shoot], key[%s], ret[%d]", TIMEMSECDIFF(s, e), key, ret);
    uint total;
    ret = usc_getter.get_prefdata(p, len_items, total, \
        (uint)MAX_PREF_ITEM_NUM, (uint)MAX_PREF_ITEM_NUM,
        (uint)USC_START, id, true, type);
    if(ret < 0){
        WARNING_LOG("read get_prefdata from usc faild.ret[%d]",ret);
        res_len = 0;
        len_items = res_len;
        return -1;
    }
    else{
        gettimeofday(&s,NULL);
        res_len = len_items;
        ret = p_global.mcc->add(key, strlen(key), (char*)p, sizeof(Item_bean) * res_len, expire);
        if(0 != ret)
        {
            gettimeofday(&e,NULL);
            WARNING_LOG("third[mcc_third_fail], cost[%d] [put mcc fail], len[%d], key[%s], ret[%d]", TIMEMSECDIFF(s, e), res_len, key, ret);
        }
        else{
            gettimeofday(&e,NULL);
            NOTICE_LOG("third[mcc_third], cost[%d] [put mcc success], len[%d], key[%s], ret[%d]", TIMEMSECDIFF(s, e), res_len, key, ret);
        }
    }
    len_items = res_len;
    return 0;
}


bool mcc_is_new_private_user(char *ch_name, uint uid){
    if(uid <= 0){
        WARNING_LOG("mcc_is_new_private_user must have uid[%d]", uid);
        return false;
    }
    struct timeval s;
    struct timeval e;
    int ret = -1;
    int res_len = 0;
    char key[MAX_MCC_KEY_LEN];
    char* value = NULL;
    int value_len = 0;
    bsl::ResourcePool rp;//负责value的内存分配
    time_t expire = g_config.mcc_instant_model;

    gettimeofday(&s,NULL);
    snprintf(key, MAX_MCC_KEY_LEN, "%s_%s_%u", INSTANT_MODEL, ch_name, uid);
    ret = p_global.mcc->get(key, strlen(key), value, value_len, expire, rp);

    if(ret != 0){
        gettimeofday(&e,NULL);
        WARNING_LOG("third[mcc_third_fail], cost[%d] [get mcc fail], key[%s], ret[%d]", TIMEMSECDIFF(s, e), key, ret);
        return false;
    }
    if(NULL == value){
        gettimeofday(&e,NULL);
        NOTICE_LOG("third[mcc_third], cost[%d] [get mcc success, buf not new user], key[%s], ret[%d]", TIMEMSECDIFF(s, e), key, ret);
        return false;
    }
    gettimeofday(&e,NULL);
    NOTICE_LOG("third[mcc_third], cost[%d] [get mcc success], key[%s], ret[%d]", TIMEMSECDIFF(s, e), key, ret);
    return true;
}


int mcc_get_instant_user_model(instant_model_t& instant_model, i_userdata_t i_user_data, const char* ch_name, uint id){
    struct timeval s;
    struct timeval e;
    int ret = -1;
    int res_len = 0;
    char key[MAX_MCC_KEY_LEN];
    char* value = NULL;
    int value_len = 0;
    bsl::ResourcePool rp;//负责value的内存分配
    time_t expire = g_config.mcc_instant_model;

    gettimeofday(&s,NULL);
    snprintf(key, MAX_MCC_KEY_LEN, "%s_%s_%u", INSTANT_MODEL, ch_name, id);
    ret = p_global.mcc->get(key, strlen(key), value, value_len, expire, rp);

    //查cache成功
    if(ret == 0 && NULL != value){
        gettimeofday(&e,NULL);
        NOTICE_LOG("third[mcc_third], cost[%d] [get mcc success], key[%s], ret[%d]", TIMEMSECDIFF(s, e), key, ret);
        memcpy(&instant_model, value, value_len);
        return value_len/sizeof(instant_model_t);
    }
    //查找cache错误，或无cache
    if(ret != 0){
        gettimeofday(&e,NULL);
        WARNING_LOG("third[mcc_third_fail], cost[%d] [get mcc fail], key[%s], ret[%d]", TIMEMSECDIFF(s, e), key, ret);
    }
    else{
        gettimeofday(&e,NULL);
        NOTICE_LOG("third[mcc_third], cost[%d] [get mcc success, no shoot], key[%s], ret[%d]", TIMEMSECDIFF(s, e), key, ret);
    }


    //建立用户模型
    res_len = build_instant_model(instant_model, i_user_data, ch_name);
    if (res_len <= 0){
        WARNING_LOG("build instant_model fail id[%u], ch_name[%s], ret[%d]",id, ch_name, ret);
        res_len = 0;
        instant_model.isset = false;
        return res_len;
    }

    gettimeofday(&s,NULL);
    ret = p_global.mcc->add(key, strlen(key), (char*) &instant_model, sizeof(instant_model), expire);
    if(0 != ret)
    {
        gettimeofday(&e,NULL);
        WARNING_LOG("third[mcc_third_fail], cost[%d] [put mcc fail], len[%d], key[%s], ret[%d]", TIMEMSECDIFF(s, e), res_len, key, ret);
    }
    else{
        gettimeofday(&e,NULL);
        NOTICE_LOG("third[mcc_third], cost[%d] [put mcc success], len[%d], key[%s], ret[%d]", TIMEMSECDIFF(s, e), res_len, key, ret);
    }

#ifdef _DEBUG_TIME
    //输出用户模型
    DEBUG_LOG("the model is exist: id[%u]", id);
    //语言
    DEBUG_LOG("lan, 0[%d], 1[%d],2[%d]", instant_model.dim_lan[0],
               instant_model.dim_lan[1], instant_model.dim_lan[2]);
    //年代
    DEBUG_LOG("year, 0[%d], 1[%d],2[%d],3[%d],4[%d]", instant_model.dim_year[0],
               instant_model.dim_year[1], instant_model.dim_year[2],
               instant_model.dim_year[3], instant_model.dim_year[4]);
    //地区
    DEBUG_LOG("area, 0[%d], 1[%d]", instant_model.dim_area[0],
               instant_model.dim_area[1]);
    //性别
    DEBUG_LOG("gender, 0[%d], 1[%d],2[%d]", instant_model.dim_gender[0],
               instant_model.dim_gender[1], instant_model.dim_gender[2]);
#endif

    instant_model.isset = true;
    return res_len;
}


int mcc_get_co_instant_user_model(instant_model_t& instant_model, i_userdata_t i_user_data, const char* ch_name, uint id){
    struct timeval s;
    struct timeval e;
    int ret = -1;
    int res_len = 0;
    char key[MAX_MCC_KEY_LEN];
    char* value = NULL;
    int value_len = 0;
    bsl::ResourcePool rp;//负责value的内存分配
    time_t expire = g_config.mcc_instant_model;

    gettimeofday(&s,NULL);
    snprintf(key, MAX_MCC_KEY_LEN, "%s_%s_%u", CO_INSTANT_MODEL, ch_name, id);
    ret = p_global.mcc->get(key, strlen(key), value, value_len, expire, rp);

    //查cache成功
    if(ret == 0 && NULL != value){
        gettimeofday(&e,NULL);
        NOTICE_LOG("third[mcc_third], cost[%d] [get mcc success], key[%s], ret[%d]", TIMEMSECDIFF(s, e), key, ret);
        memcpy(&instant_model, value, value_len);
        return value_len/sizeof(instant_model_t);
    }
    //查找cache错误，或无cache
    if(ret != 0){
        gettimeofday(&e,NULL);
        WARNING_LOG("third[mcc_third_fail], cost[%d] [get mcc fail], key[%s], ret[%d]", TIMEMSECDIFF(s, e), key, ret);
    }
    else{
        gettimeofday(&e,NULL);
        NOTICE_LOG("third[mcc_third], cost[%d] [get mcc success, no shoot], key[%s], ret[%d]", TIMEMSECDIFF(s, e), key, ret);
    }


    //建立用户模型
    res_len = build_instant_model(instant_model, i_user_data, ch_name);
    if (res_len <= 0){
        WARNING_LOG("build instant_model fail id[%u], ch_name[%s], ret[%d]",id, ch_name, ret);
        res_len = 0;
        instant_model.isset = false;
        return res_len;
    }

    gettimeofday(&s,NULL);
    ret = p_global.mcc->add(key, strlen(key), (char*)&instant_model, sizeof(instant_model), expire);
    if(0 != ret)
    {
        gettimeofday(&e,NULL);
        WARNING_LOG("third[mcc_third_fail], cost[%d] [put mcc fail], len[%d], key[%s], ret[%d]", TIMEMSECDIFF(s, e), res_len, key, ret);
    }
    else{
        gettimeofday(&e,NULL);
        NOTICE_LOG("third[mcc_third], cost[%d] [put mcc success], len[%d], key[%s], ret[%d]", TIMEMSECDIFF(s, e), res_len, key, ret);
    }

#ifdef _DEBUG_TIME
    //输出用户模型
    DEBUG_LOG("the model is exist: id[%u]", id);
    //语言
    DEBUG_LOG("lan, 0[%d], 1[%d],2[%d]", instant_model.dim_lan[0],
               instant_model.dim_lan[1], instant_model.dim_lan[2]);
    //年代
    DEBUG_LOG("year, 0[%d], 1[%d],2[%d],3[%d],4[%d]", instant_model.dim_year[0],
               instant_model.dim_year[1], instant_model.dim_year[2],
               instant_model.dim_year[3], instant_model.dim_year[4]);
    //地区
    DEBUG_LOG("area, 0[%d], 1[%d]", instant_model.dim_area[0],
               instant_model.dim_area[1]);
    //性别
    DEBUG_LOG("gender, 0[%d], 1[%d],2[%d]", instant_model.dim_gender[0],
               instant_model.dim_gender[1], instant_model.dim_gender[2]);
#endif
    instant_model.isset = true;
    return res_len;
}

/**
 *@brief：更新用户即时兴趣模型
 *@param[in]:instant_model, 即时用户模型
 *@param[in]:ch_name, 频道名
 *@param[in]:uid
 *@param[in]:type 歌曲处理类型（加心，60s等）
 *@param[in]:song_id 歌曲id
 *@param[out]:返回0 为成功，-1为失败
 */
int mcc_update_instant_user_model(instant_model_t& instant_model, const char* ch_name, uint id, int type, int song_id){
    struct timeval s;
    struct timeval e;
    int ret = -1;
    int res_len = 0;
    char key[MAX_MCC_KEY_LEN];
    char* value = NULL;
    int value_len = 0;
    bsl::ResourcePool rp;//负责value的内存分配
    time_t expire = g_config.mcc_instant_model;

    gettimeofday(&s,NULL);
    snprintf(key, MAX_MCC_KEY_LEN, "%s_%s_%u", INSTANT_MODEL, ch_name, id);
    ret = p_global.mcc->get(key, strlen(key), value, value_len, expire, rp);

    /*
    if(ret != 0){
        gettimeofday(&e,NULL);
        WARNING_LOG("third[mcc_third_fail], cost[%d] [get mcc fail], key[%s], ret[%d]", TIMEMSECDIFF(s, e), key, ret);
        return -1;
    }*/
    //查cache成功
    if(ret == 0 && NULL != value){
        gettimeofday(&e,NULL);
        NOTICE_LOG("third[mcc_third], cost[%d] [get mcc success], key[%s], ret[%d]", TIMEMSECDIFF(s, e), key, ret);
        memcpy(&instant_model, value, value_len);
        //更新模型
        per_instant_songid(instant_model, song_id, type, g_config.IWConf.real_rate);
        //试探歌曲
        DictSeeker* tmp_dict_seeker = new DictSeeker();
        int *dim = tmp_dict_seeker->judge_detect_song(song_id, ch_name);
        //试探歌曲
        if (NULL != dim){
            //试探处理
            detect_instant_songid(instant_model, song_id, type, *dim);
        }

        ret = p_global.mcc->del(key, strlen(key));
        if(ret != 0){
            gettimeofday(&e,NULL);
            NOTICE_LOG("third[mcc_third_fail], cost[%d] [del mcc fail], key[%s], ret[%d]", TIMEMSECDIFF(s, e), key, ret);
        }
        ret = p_global.mcc->add(key, strlen(key), (char*)(&instant_model), sizeof(instant_model_t), expire);
        //ret = p_global.mcc->set(key, strlen(key), (char*)(&instant_model), sizeof(instant_model_t), expire);
        if(ret != 0){
            WARNING_LOG("update instant_model in cache faild.[%d]",ret);
        }
        delete tmp_dict_seeker;
    #ifdef _DEBUG_TIME
        //输出用户模型
        DEBUG_LOG("the model update: id[%u]", id);
        //语言
        DEBUG_LOG("lan, 0[%d], 1[%d],2[%d]", instant_model.dim_lan[0],
                   instant_model.dim_lan[1], instant_model.dim_lan[2]);
        //年代
        DEBUG_LOG("year, 0[%d], 1[%d],2[%d],3[%d],4[%d]", instant_model.dim_year[0],
                   instant_model.dim_year[1], instant_model.dim_year[2],
                   instant_model.dim_year[3], instant_model.dim_year[4]);
        //地区
        DEBUG_LOG("area, 0[%d], 1[%d]", instant_model.dim_area[0],
                   instant_model.dim_area[1]);
        //性别
        DEBUG_LOG("gender, 0[%d], 1[%d],2[%d]", instant_model.dim_gender[0],
                   instant_model.dim_gender[1], instant_model.dim_gender[2]);
    #endif
        instant_model.isset = true;
        return 0;
    }

    DEBUG_LOG("no instant_model exist, id[%u], ch_name[%s]",  id, ch_name);
    instant_model.isset = false;
    return -1;
}



int mcc_update_co_instant_user_model(instant_model_t& instant_model, const char* ch_name, uint id, int type, int song_id){
    struct timeval s;
    struct timeval e;
    int ret = -1;
    int res_len = 0;
    char key[MAX_MCC_KEY_LEN];
    char* value = NULL;
    int value_len = 0;
    bsl::ResourcePool rp;//负责value的内存分配
    time_t expire = g_config.mcc_co_instant_model;

    gettimeofday(&s,NULL);
    snprintf(key, MAX_MCC_KEY_LEN, "%s_%s_%u", CO_INSTANT_MODEL, ch_name, id);
    ret = p_global.mcc->get(key, strlen(key), value, value_len, expire, rp);

    /*
    if(ret != 0){
        gettimeofday(&e,NULL);
        WARNING_LOG("third[mcc_third_fail], cost[%d] [get mcc fail], key[%s], ret[%d]", TIMEMSECDIFF(s, e), key, ret);
        return -1;
    }*/
    //查cache成功
    if(ret == 0 && NULL != value){

        gettimeofday(&e,NULL);
        NOTICE_LOG("third[mcc_third], cost[%d] [get mcc success], key[%s], ret[%d]", TIMEMSECDIFF(s, e), key, ret);
        memcpy(&instant_model, value, value_len);
        //更新模型
        per_instant_songid(instant_model, song_id, type, g_config.IWConf.real_rate);
        //试探歌曲
        DictSeeker* tmp_dict_seeker = new DictSeeker();
        int *dim = tmp_dict_seeker->judge_detect_song(song_id, ch_name);
        //试探歌曲
        if (NULL != dim){
            //试探处理
            detect_instant_songid(instant_model, song_id, type, *dim);
        }

        ret = p_global.mcc->del(key, strlen(key));
        if(ret != 0){
            gettimeofday(&e,NULL);
            NOTICE_LOG("third[mcc_third_fail], cost[%d] [del mcc fail], key[%s], ret[%d]", TIMEMSECDIFF(s, e), key, ret);
        }
        ret = p_global.mcc->add(key, strlen(key), (char*)(&instant_model), sizeof(instant_model_t), expire);
        //ret = p_global.mcc->set(key, strlen(key), (char*)(&instant_model), sizeof(instant_model_t), expire);
        if(ret != 0){
            WARNING_LOG("update instant_model in cache faild.[%d]",ret);
        }
        delete tmp_dict_seeker;
#ifdef _DEBUG_TIME
        //输出用户模型
        DEBUG_LOG("the model update: id[%u]", id);
        //语言
        DEBUG_LOG("lan, 0[%d], 1[%d],2[%d]", instant_model.dim_lan[0],
                   instant_model.dim_lan[1], instant_model.dim_lan[2]);
        //年代
        DEBUG_LOG("year, 0[%d], 1[%d],2[%d],3[%d],4[%d]", instant_model.dim_year[0],
                   instant_model.dim_year[1], instant_model.dim_year[2],
                   instant_model.dim_year[3], instant_model.dim_year[4]);
        //地区
        DEBUG_LOG("area, 0[%d], 1[%d]", instant_model.dim_area[0],
                   instant_model.dim_area[1]);
        //性别
        DEBUG_LOG("gender, 0[%d], 1[%d],2[%d]", instant_model.dim_gender[0],
                   instant_model.dim_gender[1], instant_model.dim_gender[2]);
#endif
        instant_model.isset = true;
        return 0;
    }

    DEBUG_LOG("no instant_model exist, id[%u], ch_name[%s]",  id, ch_name);
    instant_model.isset = false;
    return -1;
}



int mcc_get_ch_list(uint id, const char* ch_name, Song_item_t* p, int len){

    if(id <= 0){
        WARNING_LOG("mcc_get_ch_list must have id[%u]", id);
        return -1;
    }
    struct timeval s;
    struct timeval e;
    int ret = -1;
    int res_len = 0;
    char key[MAX_MCC_KEY_LEN];
    char* value = NULL;
    int value_len = 0;
    bsl::ResourcePool rp;//负责value的内存分配
    time_t expire = g_config.mcc_instant_model;

    gettimeofday(&s,NULL);
    snprintf(key, MAX_MCC_KEY_LEN, "%s_%s_%u", PLAY_LIST, ch_name, id);
    ret = p_global.mcc->get(key, strlen(key), value, value_len, expire, rp);

    /*
    if(ret != 0){
        gettimeofday(&e,NULL);
        WARNING_LOG("third[mcc_third_fail], cost[%d] [get mcc fail], key[%s], ret[%d]", TIMEMSECDIFF(s, e), key, ret);
        return -1;
    }
    if(NULL == value && value_len == -1){
        gettimeofday(&e,NULL);
        NOTICE_LOG("third[mcc_third], cost[%d] [get mcc fail], key[%s], ret[%d]", TIMEMSECDIFF(s, e), key, ret);
        return 0;
    }*/
    if(ret != 0){
        gettimeofday(&e,NULL);
        NOTICE_LOG("third[mcc_third], cost[%d] [get mcc fail], key[%s], ret[%d]", TIMEMSECDIFF(s, e), key, ret);
        return 0;
    }
    gettimeofday(&e,NULL);
    NOTICE_LOG("third[mcc_third], cost[%d] [get mcc success], key[%s], ret[%d]", TIMEMSECDIFF(s, e), key, ret);

    res_len = value_len/sizeof(Song_item_t);
    if (res_len > len){
        res_len = len;
    }
    memcpy(p, value, res_len * sizeof(Song_item_t));
#ifdef _DEBUG_TIME
    //输出ch list
    DEBUG_LOG("the ch list is in cache: key[%s], len[%d]", key, res_len);
    for(int i = 0; i < res_len; i++){
        DEBUG_LOG("ch list: pos[%d], song_id[%u], weight[%d], method[%d]", i, p[i].song_id, p[i].weight, p[i].source);
    }
#endif
    return res_len;

}


int mcc_get_co_ch_list(uint id, const char* ch_name, Song_item_t* p, int len){

    if(id <= 0){
        WARNING_LOG("mcc_get_co_ch_list must have id[%u]", id);
        return -1;
    }
    struct timeval s;
    struct timeval e;
    int ret = -1;
    int res_len = 0;
    char key[MAX_MCC_KEY_LEN];
    char* value = NULL;
    int value_len = 0;
    bsl::ResourcePool rp;//负责value的内存分配
    time_t expire = g_config.mcc_co_instant_model;

    gettimeofday(&s,NULL);
    snprintf(key, MAX_MCC_KEY_LEN, "%s_%s_%u", CO_PLAY_LIST, ch_name, id);
    ret = p_global.mcc->get(key, strlen(key), value, value_len, expire, rp);

    /*
    if(ret != 0){
        gettimeofday(&e,NULL);
        WARNING_LOG("third[mcc_third_fail], cost[%d] [get mcc fail], key[%s], ret[%d]", TIMEMSECDIFF(s, e), key, ret);
        return -1;
    }
    if(NULL == value && value_len == -1){
        gettimeofday(&e,NULL);
        NOTICE_LOG("third[mcc_third], cost[%d] [get mcc fail], key[%s], ret[%d]", TIMEMSECDIFF(s, e), key, ret);
        return 0;
    }*/
    if(ret != 0){
        gettimeofday(&e,NULL);
        NOTICE_LOG("third[mcc_third], cost[%d] [get mcc fail], key[%s], ret[%d]", TIMEMSECDIFF(s, e), key, ret);
        return 0;
    }
    gettimeofday(&e,NULL);
    NOTICE_LOG("third[mcc_third], cost[%d] [get mcc success], key[%s], ret[%d]", TIMEMSECDIFF(s, e), key, ret);
    res_len = value_len/sizeof(Song_item_t);
    if (res_len > len){
        res_len = len;
    }
    memcpy(p, value, res_len * sizeof(Song_item_t));
#ifdef _DEBUG_TIME
    //输出ch list
    DEBUG_LOG("the co ch list is in cache: key[%s], len[%d]", key, res_len);
    for(int i = 0; i < res_len; i++){
        DEBUG_LOG("co ch list: pos[%d], song_id[%u], weight[%d], method[%d]", i, p[i].song_id, p[i].weight, p[i].source);
    }
#endif
    return res_len;
}

int mcc_get_user_instant_behavior(uint id, uint song_id, bool &is_exist){
    is_exist = false;
    if(id <= 0){
        WARNING_LOG("mcc_get_user_instant_behavior must have id[%u]", id);
        return -1;
    }
    if(song_id == 0){
        WARNING_LOG("mcc_get_user_instant_behavior must song_id[%u] > 0", song_id);
        return -1;
    }
    struct timeval s;
    struct timeval e;
    int ret = -1;
    int res_len = 0;
    char key[MAX_MCC_KEY_LEN];
    char* value = NULL;
    int value_len = 0;
    bsl::ResourcePool rp;//负责value的内存分配
    time_t expire = g_config.mcc_user_instant_behavior;
    user_instant_behavior_t p[MAX_USER_INSTANT_BEHAVIOR_NUM];

    gettimeofday(&s,NULL);
    snprintf(key, MAX_MCC_KEY_LEN, "%s_%u", USER_INSTATNT_BEHAVIOR, id);
    ret = p_global.mcc->get(key, strlen(key), value, value_len, expire, rp);

    /*if(ret != 0){
        gettimeofday(&e,NULL);
        WARNING_LOG("third[mcc_third_fail], cost[%d] [get mcc fail], key[%s], ret[%d]", TIMEMSECDIFF(s, e), key, ret);
        return -1;
    }
    if(NULL == value && value_len == -1){
        gettimeofday(&e,NULL);
        NOTICE_LOG("third[mcc_third], cost[%d] [get mcc fail], key[%s], ret[%d]", TIMEMSECDIFF(s, e), key, ret);
        return 0;
    }*/
    if(ret != 0){
        gettimeofday(&e,NULL);
        NOTICE_LOG("third[mcc_third], cost[%d] [get mcc fail], key[%s], ret[%d]", TIMEMSECDIFF(s, e), key, ret);
        return 0;
    }
    gettimeofday(&e,NULL);
    NOTICE_LOG("third[mcc_third], cost[%d] [get mcc success], key[%s], ret[%d]", TIMEMSECDIFF(s, e), key, ret);
    res_len = value_len/sizeof(user_instant_behavior_t);
    if(res_len > 0){
        memcpy(p, value, res_len * sizeof(user_instant_behavior_t));
        time_t now = time((time_t*)NULL);
        if((p[res_len - 1].song_id == song_id) && \
            ((now - p[res_len -1].timestamp) < 5 * 60) && \
            (p[res_len - 1].type == COMPLETE_SONG || p[res_len -1].type == LOVE_SONG)){
            is_exist = true;
            NOTICE_LOG("id[%d], song_id[%d] exist the positive behavior");
        }
    }
#ifdef _DEBUG_TIME
    //输出ch list
    DEBUG_LOG("the user_instant_behavior_t in cache: key[%s], len[%d]", key, res_len);
    for(int i = 0; i < res_len; i++){
        DEBUG_LOG("user_instant_behavior_t list: pos[%d], song_id[%u], type[%d], time[%d]", \
            i, p[i].song_id, p[i].type, p[i].timestamp);
    }
#endif
    return SUCCESS;
}

int mcc_update_user_instant_behavior(uint id, uint song_id, int type){
    if(id <= 0){
        WARNING_LOG("mcc_update_user_instant_behavior must have id[%u]", id);
        return -1;
    }
    if(song_id == 0){
        WARNING_LOG("mcc_update_user_instant_behavior must song_id[%u] > 0", song_id);
        return -1;
    }
    struct timeval s;
    struct timeval e;
    int ret = -1;
    int res_len = 0;
    char key[MAX_MCC_KEY_LEN];
    char* value = NULL;
    int value_len = 0;
    bsl::ResourcePool rp;//负责value的内存分配
    time_t expire = g_config.mcc_user_instant_behavior;
    user_instant_behavior_t p[MAX_USER_INSTANT_BEHAVIOR_NUM];

    gettimeofday(&s,NULL);
    snprintf(key, MAX_MCC_KEY_LEN, "%s_%u", USER_INSTATNT_BEHAVIOR, id);
    ret = p_global.mcc->get(key, strlen(key), value, value_len, expire, rp);

    /*
    if(ret != 0){
        gettimeofday(&e,NULL);
        WARNING_LOG("third[mcc_third_fail], cost[%d] [get mcc fail], key[%s], ret[%d]", TIMEMSECDIFF(s, e), key, ret);
        return -1;
    }
    if(NULL == value && value_len == -1){
        gettimeofday(&e,NULL);
        NOTICE_LOG("third[mcc_third], cost[%d] [get mcc not exist], key[%s], ret[%d]", TIMEMSECDIFF(s, e), key, ret);
        value_len = 0;
    }*/
    if(ret != 0){
        gettimeofday(&e,NULL);
        NOTICE_LOG("third[mcc_third], cost[%d] [get mcc not exist], key[%s], ret[%d]", TIMEMSECDIFF(s, e), key, ret);
        value_len = 0;
    }else{
        gettimeofday(&e,NULL);
        NOTICE_LOG("third[mcc_third], cost[%d] [get mcc success], key[%s], ret[%d]", TIMEMSECDIFF(s, e), key, ret);

        ret = p_global.mcc->del(key, strlen(key));
        if(ret != 0){
            gettimeofday(&e,NULL);
            NOTICE_LOG("third[mcc_third_fail], cost[%d] [del mcc fail], key[%s], ret[%d]", TIMEMSECDIFF(s, e), key, ret);
        }
    }
    res_len = value_len/sizeof(user_instant_behavior_t);

    memcpy(p, value, res_len * sizeof(user_instant_behavior_t));
    time_t now = time((time_t*)NULL);
    if(res_len < MAX_USER_INSTANT_BEHAVIOR_NUM){
        p[res_len].song_id = song_id;
        p[res_len].timestamp = now;
        p[res_len].type = type;
        res_len ++;
    }
    else{
        memcpy(p, p + 1, (MAX_USER_INSTANT_BEHAVIOR_NUM - 1) * sizeof(user_instant_behavior_t));
        p[MAX_USER_INSTANT_BEHAVIOR_NUM - 1].song_id = song_id;
        p[MAX_USER_INSTANT_BEHAVIOR_NUM - 1].timestamp = now;
        p[MAX_USER_INSTANT_BEHAVIOR_NUM - 1].type = type;
        res_len = MAX_USER_INSTANT_BEHAVIOR_NUM;
    }
    //ret = p_global.mcc->set(key, strlen(key), (char *)p, res_len * sizeof(user_instant_behavior_t), expire);
    ret = p_global.mcc->add(key, strlen(key), (char *)p, res_len * sizeof(user_instant_behavior_t), expire);
    if(ret != 0){
        gettimeofday(&e,NULL);
        WARNING_LOG("third[mcc_third_fail], cost[%d] [update mcc fail], key[%s], ret[%d]", TIMEMSECDIFF(s, e), key, ret);
        return -1;
    }
    gettimeofday(&e,NULL);
    NOTICE_LOG("third[mcc_third], cost[%d] [update mcc success], key[%s], ret[%d]", TIMEMSECDIFF(s, e), key, ret);

#ifdef _DEBUG_TIME
    //输出user_instant_behavior
    DEBUG_LOG("the user_instant_behavior_t in cache: key[%s], len[%d]", key, res_len);
    for(int i = 0; i < res_len; i++){
        DEBUG_LOG("user_instant_behavior_t list: pos[%d], song_id[%u], type[%d], time[%d]", \
            i, p[i].song_id, p[i].type, p[i].timestamp);
    }
#endif
    return SUCCESS;
}


int mcc_update_ch_list(uint id, const char* ch_name, Song_item_t* p, int len){

    if(id <= 0){
        WARNING_LOG("mcc_update_ch_list must have id[%u]", id);
        return -1;
    }
    struct timeval s;
    struct timeval e;
    int ret = -1;
    char key[MAX_MCC_KEY_LEN];
    time_t expire = g_config.mcc_play_list;

    gettimeofday(&s,NULL);
    snprintf(key, MAX_MCC_KEY_LEN, "%s_%s_%u", PLAY_LIST, ch_name, id);
    ret = p_global.mcc->del(key, strlen(key));
    if(ret != 0){
        gettimeofday(&e,NULL);
        NOTICE_LOG("third[mcc_third_fail], cost[%d] [del mcc fail], key[%s], ret[%d]", TIMEMSECDIFF(s, e), key, ret);
    }
    ret = p_global.mcc->add(key, strlen(key), (char *)p, len * sizeof(Song_item_t), expire);
    //ret = p_global.mcc->set(key, strlen(key), (char *)p, len * sizeof(Song_item_t), expire);
    if(ret != 0){
        gettimeofday(&e,NULL);
        WARNING_LOG("third[mcc_third_fail], cost[%d] [update mcc fail], key[%s], ret[%d]", TIMEMSECDIFF(s, e), key, ret);
        return -1;
    }
    gettimeofday(&e,NULL);
    NOTICE_LOG("third[mcc_third], cost[%d] [update mcc success], key[%s], ret[%d]", TIMEMSECDIFF(s, e), key, ret);
#ifdef _DEBUG_TIME
    //输出ch list
    DEBUG_LOG("the ch list set into cache: key[%s], len[%d]", key, len);
    for(int i = 0; i < len; i++){
        DEBUG_LOG("the ch list set into cache: pos[%d], song_id[%u], weight[%d], method[%d]", i, p[i].song_id, p[i].weight, p[i].source);
    }
#endif

    return 0;
}


int mcc_update_co_ch_list(uint id, const char* ch_name, Song_item_t* p, int len){

    if(id <= 0){
        WARNING_LOG("mcc_update_co_ch_list must have id[%u]", id);
        return -1;
    }
    struct timeval s;
    struct timeval e;
    int ret = -1;
    char key[MAX_MCC_KEY_LEN];
    time_t expire = g_config.mcc_co_play_list;

    gettimeofday(&s,NULL);
    snprintf(key, MAX_MCC_KEY_LEN, "%s_%s_%u", CO_PLAY_LIST, ch_name, id);
    ret = p_global.mcc->del(key, strlen(key));
    if(ret != 0){
        gettimeofday(&e,NULL);
        NOTICE_LOG("third[mcc_third_fail], cost[%d] [del mcc fail], key[%s], ret[%d]", TIMEMSECDIFF(s, e), key, ret);
    }

    ret = p_global.mcc->add(key, strlen(key), (char *)p, len * sizeof(Song_item_t), expire);
    //ret = p_global.mcc->set(key, strlen(key), (char *)p, len * sizeof(Song_item_t), expire);

    if(ret != 0){
        gettimeofday(&e,NULL);
        WARNING_LOG("third[mcc_third_fail], cost[%d] [update mcc fail], key[%s], ret[%d]", TIMEMSECDIFF(s, e), key, ret);
        return -1;
    }
    gettimeofday(&e,NULL);
    NOTICE_LOG("third[mcc_third], cost[%d] [update mcc success], key[%s], ret[%d]", TIMEMSECDIFF(s, e), key, ret);
#ifdef _DEBUG_TIME
    //输出ch list
    DEBUG_LOG("the co ch list set into cache: key[%s], len[%d]", key, len);
    for(int i = 0; i < len; i++){
        DEBUG_LOG("the co ch list set into cache: pos[%d], song_id[%u], weight[%d], method[%d]", i, p[i].song_id, p[i].weight, p[i].source);
    }
#endif
    return 0;
}

int mcc_get_action_record(uint id, const char* ch_name, action_record_t* record){
    if(NULL == record){
        WARNING_LOG("wrong param in mcc_get_action_record");
        return -1;
    }
    if(id <= 0){
        WARNING_LOG("mcc_get_action_record must have id[%u]", id);
        return -1;
    }
    struct timeval s;
    struct timeval e;
    int ret = -1;
    int res_len = 0;
    char key[MAX_MCC_KEY_LEN];
    char* value = NULL;
    int value_len = 0;
    bsl::ResourcePool rp;//负责value的内存分配
    time_t expire = g_config.mcc_negation_record;

    gettimeofday(&s,NULL);
    snprintf(key, MAX_MCC_KEY_LEN, "%s_%s_%u", NEGATION_RECORD, ch_name, id);
    ret = p_global.mcc->get(key, strlen(key), value, value_len, expire, rp);

    /*if(ret != 0){
        gettimeofday(&e,NULL);
        WARNING_LOG("third[mcc_third_fail], cost[%d] [get mcc fail], key[%s], ret[%d]", TIMEMSECDIFF(s, e), key, ret);

        return -1;
    }
    if(NULL == value){*/
    if(ret != 0){
        gettimeofday(&e,NULL);
        NOTICE_LOG("third[mcc_third], cost[%d] [get mcc fail], key[%s], ret[%d]", TIMEMSECDIFF(s, e), key, ret);
        return 0;
    }
    gettimeofday(&e,NULL);
    NOTICE_LOG("third[mcc_third], cost[%d] [get mcc success], key[%s], ret[%d]", TIMEMSECDIFF(s, e), key, ret);
    memcpy(record, value, value_len);
    res_len = value_len/sizeof(action_record_t);
#ifdef _DEBUG_TIME
    //输出record
    DEBUG_LOG("the nagetive record in cache: key[%s], len[%d]", key, res_len);
    DEBUG_LOG("the nagetive record in cache: record_cnt[%d], min_time[%ld]", (*record).bad_action_cnt, (*record).bad_min_time);
#endif
    return 0;
}


int mcc_get_co_action_record(uint id, const char* ch_name, action_record_t* record){
    if(NULL == record){
        WARNING_LOG("wrong param in mcc_get_action_record");
        return -1;
    }
    if(id <= 0){
        WARNING_LOG("mcc_get_co_action_record must have id[%u]", id);
        return -1;
    }
    struct timeval s;
    struct timeval e;
    int ret = -1;
    int res_len = 0;
    char key[MAX_MCC_KEY_LEN];
    char* value = NULL;
    int value_len = 0;
    bsl::ResourcePool rp;//负责value的内存分配
    time_t expire = g_config.mcc_co_negation_record;

    gettimeofday(&s,NULL);
    snprintf(key, MAX_MCC_KEY_LEN, "%s_%s_%u", CO_NEGATION_RECORD, ch_name, id);
    ret = p_global.mcc->get(key, strlen(key), value, value_len, expire, rp);

    /*
    if(ret != 0){
        gettimeofday(&e,NULL);
        WARNING_LOG("third[mcc_third_fail], cost[%d] [get mcc fail], key[%s], ret[%d]", TIMEMSECDIFF(s, e), key, ret);
        return -1;
    }
    if(NULL == value && value_len == -1){*/
    if(ret != 0){
        gettimeofday(&e,NULL);
        NOTICE_LOG("third[mcc_third], cost[%d] [get mcc fail], key[%s], ret[%d]", TIMEMSECDIFF(s, e), key, ret);
        return 0;
    }
    gettimeofday(&e,NULL);
    NOTICE_LOG("third[mcc_third], cost[%d] [get mcc success], key[%s], ret[%d]", TIMEMSECDIFF(s, e), key, ret);
    memcpy(record, value, value_len);
    res_len = value_len/sizeof(action_record_t);
#ifdef _DEBUG_TIME
    //输出record
    DEBUG_LOG("the co nagetive record in cache: key[%s], len[%d]", key, res_len);
    DEBUG_LOG("the co nagetive record in cache: record_cnt[%d], min_time[%ld]", (*record).bad_action_cnt, (*record).bad_min_time);
#endif
    return 0;
}


int mcc_update_action_record(uint id, const char* ch_name, action_record_t* record){
    if(NULL == record){
        WARNING_LOG("wrong param in mcc_update_action_record");
        return -1;
    }
    if(id <= 0){
        WARNING_LOG("mcc_update_action_record must have id[%u]", id);
        return -1;
    }
    struct timeval s;
    struct timeval e;
    int ret = -1;
    int res_len = 0;
    char key[MAX_MCC_KEY_LEN];
    time_t expire = g_config.mcc_negation_record;

    gettimeofday(&s,NULL);
    snprintf(key, MAX_MCC_KEY_LEN, "%s_%s_%u", NEGATION_RECORD, ch_name, id);

    ret = p_global.mcc->del(key, strlen(key));
    if(ret != 0){
        gettimeofday(&e,NULL);
        NOTICE_LOG("third[mcc_third_fail], cost[%d] [del mcc fail], key[%s], ret[%d]", TIMEMSECDIFF(s, e), key, ret);
    }
    ret = p_global.mcc->add(key, strlen(key), (char*) record, sizeof(action_record_t), expire);
    //ret = p_global.mcc->set(key, strlen(key), (char*) record, sizeof(action_record_t), expire);
    if(ret != 0){
        gettimeofday(&e,NULL);
        WARNING_LOG("third[mcc_third_fail], cost[%d] [update mcc fail], key[%s], ret[%d]", TIMEMSECDIFF(s, e), key, ret);
        return -1;
    }
    gettimeofday(&e,NULL);
    NOTICE_LOG("third[mcc_third], cost[%d] [update mcc success], key[%s], ret[%d]", TIMEMSECDIFF(s, e), key, ret);
#ifdef _DEBUG_TIME
    //输出record
    DEBUG_LOG("the nagetive record set in cache: key[%s]", key);
    DEBUG_LOG("the nagetive record set cache: record_cnt[%d], min_time[%ld]", (*record).bad_action_cnt, (*record).bad_min_time);
#endif
    return 0;
}


int mcc_update_co_action_record(uint id, const char* ch_name, action_record_t* record){
    if(NULL == record){
        WARNING_LOG("wrong param in mcc_update_co_action_record");
        return -1;
    }
    if(id <= 0){
        WARNING_LOG("mcc_update_co_action_record must have id[%u]", id);
        return -1;
    }
    struct timeval s;
    struct timeval e;
    int ret = -1;
    int res_len = 0;
    char key[MAX_MCC_KEY_LEN];
    time_t expire = g_config.mcc_co_negation_record;

    gettimeofday(&s,NULL);
    snprintf(key, MAX_MCC_KEY_LEN, "%s_%s_%u", CO_NEGATION_RECORD, ch_name, id);
    ret = p_global.mcc->del(key, strlen(key));
    if(ret != 0){
        gettimeofday(&e,NULL);
        NOTICE_LOG("third[mcc_third_fail], cost[%d] [del mcc fail], key[%s], ret[%d]", TIMEMSECDIFF(s, e), key, ret);
    }
    ret = p_global.mcc->add(key, strlen(key), (char*) record, sizeof(action_record_t), expire);
    //ret = p_global.mcc->set(key, strlen(key), (char*) record, sizeof(action_record_t), expire);
    if(ret != 0){
        gettimeofday(&e,NULL);
        WARNING_LOG("third[mcc_third_fail], cost[%d] [update mcc fail], key[%s], ret[%d]", TIMEMSECDIFF(s, e), key, ret);
        return -1;
    }
    gettimeofday(&e,NULL);
    NOTICE_LOG("third[mcc_third], cost[%d] [update mcc success], key[%s], ret[%d]", TIMEMSECDIFF(s, e), key, ret);
#ifdef _DEBUG_TIME
    //输出record
    DEBUG_LOG("the co nagetive record set in cache: key[%s]", key);
    DEBUG_LOG("the co nagetive record set cache: record_cnt[%d], min_time[%ld]", (*record).bad_action_cnt, (*record).bad_min_time);
#endif
    return 0;
}

int mcc_is_new_user(uint id, int type, int &is_new){
    is_new = 0;
    if(id <= 0){
        WARNING_LOG("id should be > 0");
        return FAIL;
    }
    bool has_history = true;
    if(type == 1){
        db_has_listen_history(id, has_history);
    }
    else if(type == 2){
        db_has_co_listen_history(id, has_history);
    }
    if(has_history == false){
        is_new = 1;
    }
    return SUCCESS;
}


int mcc_get_ral_list(uint uid, char * ch_name, int r_type, Song_item_t * p, int source, int buf_size){
    if(buf_size <= 0)
    {
        return 0;
    }
    if(NULL == p){
        WARNING_LOG("get_ral_list param error[NULL == p]");
        return -1;
    }
    struct timeval s;
    struct timeval e;
    int ret = -1;
    int res_len = 0;
    char key[MAX_MCC_KEY_LEN];
    snprintf(key, MAX_MCC_KEY_LEN, "%s_%s_%u_%d", RAL_LIST, ch_name, uid, r_type);
    char* value = NULL;
    int value_len = 0;
    bsl::ResourcePool rp;//负责value的内存分配
    time_t expire = g_config.mcc_user_list_timeout;

    //查找cache
    gettimeofday(&s,NULL);
    ret = p_global.mcc->get(key, strlen(key), value, value_len, expire, rp);
    /*
    //查找失败
    if (ret != 0){
        gettimeofday(&e,NULL);
        WARNING_LOG("third[mcc_third_fail], cost[%d] [get mcc fail], key[%s], ret[%d]", TIMEMSECDIFF(s, e), key, ret);
        return -1;
    }
    //查找成功
    if(NULL != value || 0 == value_len){*/
    if(ret == 0){
        memcpy(p, value, value_len);
        res_len  = value_len/sizeof(Song_item_t);
        gettimeofday(&e,NULL);
        NOTICE_LOG("third[mcc_third], cost[%d] [get mcc success], len[%d], key[%s], ret[%d]", TIMEMSECDIFF(s, e), res_len, key, ret);
#ifdef _DEBUG_TIME
        DEBUG_LOG("the ral_list data put into cache: key[%s], len[%d]", key, res_len);
        for(int i = 0; i < res_len; i++){
            DEBUG_LOG("the ral_list data: pos[%d], song_id[%d], weight[%d], method[%u]", i, p[i].song_id, p[i].weight, p[i].source);
        }
#endif
        return res_len;
    }
    //没命中cache
    gettimeofday(&e,NULL);
    NOTICE_LOG("third[mcc_third], cost[%d] [get mcc no shoot], key[%s], ret[%d]", TIMEMSECDIFF(s, e), key, ret);
    res_len = db_get_ral_list(uid, ch_name, r_type, p, source, buf_size);
    if(res_len < 0){
        WARNING_LOG("read ral_list from db faild.ret[%d]",ret);
        res_len = 0;
    }
    else{
        gettimeofday(&s,NULL);
        ret = p_global.mcc->add(key, strlen(key), (char*)p, sizeof(Song_item_t) * res_len, expire);
        if(0 != ret)
        {
            gettimeofday(&e,NULL);
            WARNING_LOG("third[mcc_third_fail], cost[%d] [put mcc fail], len[%d], key[%s], ret[%d]", TIMEMSECDIFF(s, e), res_len, key, ret);
        }
        else{
            gettimeofday(&e,NULL);
            NOTICE_LOG("third[mcc_third], cost[%d] [put mcc success], len[%d], key[%s], ret[%d]", TIMEMSECDIFF(s, e), res_len, key, ret);
#ifdef _DEBUG_TIME
            DEBUG_LOG("the ral_list data put into cache: key[%s], len[%d]", key, res_len);
            for(int i = 0; i < res_len; i++){
                DEBUG_LOG("the ral_list data(put in): pos[%d], song_id[%d], weight[%d], method[%u]", i, p[i].song_id, p[i].weight, p[i].source);
            }
#endif
        }
    }
    return res_len;
}


int mcc_get_tag_list(uint uid, User_tag_t * p, int buf_size){
    if(buf_size <= 0)
    {
        return 0;
    }
    if(NULL == p){
        WARNING_LOG("get_tag_list param error[NULL == p]");
        return -1;
    }
    struct timeval s;
    struct timeval e;
    int ret = -1;
    int res_len = 0;
    char key[MAX_MCC_KEY_LEN];
    snprintf(key, MAX_MCC_KEY_LEN, "%s_%u", TAG_LIST, uid);
    char* value = NULL;
    int value_len = 0;
    bsl::ResourcePool rp;//负责value的内存分配
    time_t expire = g_config.mcc_user_list_timeout;

    //查找cache
    gettimeofday(&s,NULL);
    ret = p_global.mcc->get(key, strlen(key), value, value_len, expire, rp);
    /*
    //查找失败
    if (ret != 0){
        gettimeofday(&e,NULL);
        WARNING_LOG("third[mcc_third_fail], cost[%d] [get mcc fail], key[%s], ret[%d]", TIMEMSECDIFF(s, e), key, ret);
        return -1;
    }
    //查找成功
    if(NULL != value || 0 == value_len){*/
    if(ret == 0){
        memcpy(p, value, value_len);
        res_len  = value_len/sizeof(User_tag_t);
        gettimeofday(&e,NULL);
        NOTICE_LOG("third[mcc_third], cost[%d] [get mcc success], len[%d], key[%s], ret[%d]", TIMEMSECDIFF(s, e), res_len, key, ret);
#ifdef _DEBUG_TIME
        DEBUG_LOG("the user tag data is in cache: key[%s], len[%d]", key, res_len);
        for(int i = 0; i < res_len; i++){
            DEBUG_LOG("the user tag data: pos[%d], tag_title[%s], tag_tag_id[%d], weithg[%d]", i, p[i].tag_title, p[i].tag_id, p[i].tag_weight);
        }
#endif
        return res_len;
    }
    //没命中cache
    gettimeofday(&e,NULL);
    NOTICE_LOG("third[mcc_third], cost[%d] [get mcc no shoot], key[%s], ret[%d]", TIMEMSECDIFF(s, e), key, ret);
    res_len = db_get_user_tags(uid, p, buf_size);
    if(res_len < 0){
        WARNING_LOG("read tag_list from db faild.ret[%d]",ret);
        res_len = 0;
    }
    else{
        gettimeofday(&s,NULL);
        ret = p_global.mcc->add(key, strlen(key), (char*)p, sizeof(User_tag_t) * res_len, expire);
        if(0 != ret)
        {
            gettimeofday(&e,NULL);
            WARNING_LOG("third[mcc_third_fail], cost[%d] [put mcc fail], len[%d], key[%s], ret[%d]", TIMEMSECDIFF(s, e), res_len, key, ret);
        }
        else{
            gettimeofday(&e,NULL);
            NOTICE_LOG("third[mcc_third], cost[%d] [put mcc success], len[%d], key[%s], ret[%d]", TIMEMSECDIFF(s, e), res_len, key, ret);
#ifdef _DEBUG_TIME
            DEBUG_LOG("the user tag data put into cache: key[%s], len[%d]", key, res_len);
            for(int i = 0; i < res_len; i++){
                DEBUG_LOG("the user tag data(put in): pos[%d], tag_title[%s], tag_tag_id[%d], weithg[%d]", i, p[i].tag_title, p[i].tag_id, p[i].tag_weight);
            }
#endif
        }
    }
    return res_len;
}


/**
 * 或许历史分页数据
 * uid 用户id(用户名的签名)
 * type 物体类型
 * p_beans 物体数据的buf,由外部初始化
 * bean_len 数据buf的长度
 *
 * return >=0 成功并返回获取数据的长度 -1失败
 *
*/
int mcc_get_history_page(unsigned int uid, Item_bean *p_benas, int start_no, int page_len, int src)
{
    //不用cache
    return db_get_history_page(uid, p_benas, start_no, page_len, src);
}


/**
 * 获取历史总数
 * retrun >=0 成功,返回数据长度 -1失败
 */
int mcc_get_listen_total_num(uint uid, int src)
{
    int ret=-1;
    int total_num = 0;
    total_num = db_get_listen_history_num(uid, src);
    if(total_num < 0)
    {
        WARNING_LOG("read listen total num from db faild.[%d]",ret);
        total_num = 0;
    }
    return total_num;
}

/**
 * 获取用户当前redis中推荐列表的sign值
 */
int mcc_get_redis_sign(uint uid, const char* ch_name, const char *list_tag, const char *field, char *sign, uint &sign_len){
    if(NULL == ch_name || NULL == field || NULL == list_tag || uid <= 0){
        WARNING_LOG("wrong params in mcc_get_redis_sign");
        return -1;
    }

    char key[MAX_MCC_KEY_LEN];
    snprintf(key, MAX_MCC_KEY_LEN, "%u_%s_redis_%s_%s", uid, ch_name, list_tag, field);

    char* value = NULL;
    int ret = -1;
    int value_len = 0;
    sign_len = 0;
    bsl::ResourcePool rp;//负责value的内存分配

    ret = p_global.mcc->get(key, strlen(key), value, value_len, rp);
    if(ret != 0){
        NOTICE_LOG("mc get redis sign fail, redis key not exists[%s]", key);
        return -1;
    }
    if(NULL != value){
        NOTICE_LOG("mc get redis sign success, key:[%s], value[%s]:return_len:[%d]:str_len:[%d]", key, value, value_len, strlen(value));
    }else{
        WARNING_LOG("mc get redis sign error, key[%s]", key);
        return -1;
    }

    snprintf(sign, MAX_REDIS_SIGN_LEN, "%s", value);
    //memcpy(sign, value, value_len);
    sign_len = value_len;
    return 0;
}

int mcc_update_redis_sign(uint uid, const char *ch_name, const char *list_tag, const char *field, const char *sign){
    if(NULL == ch_name || NULL == sign || NULL == field || NULL == list_tag || uid <= 0){
        WARNING_LOG("wrong params in mcc_update_redis_sign");
        return FAIL;
    }

    int ret = -1;
    char key[MAX_MCC_KEY_LEN];
    time_t expire = g_config.mcc_user_redis_list_sign_timeout;
    snprintf(key, MAX_MCC_KEY_LEN, "%u_%s_redis_%s_%s", uid, ch_name, list_tag, field);

    ret = p_global.mcc->del(key, strlen(key));
    if(ret != 0){
        NOTICE_LOG("third[mcc_third_fail], [del mcc fail], key[%s], ret[%d]", key, ret);
    }
    ret = p_global.mcc->add(key, strlen(key), sign, strlen(sign), expire);
    //ret = p_global.mcc->set(key, strlen(key), sign, strlen(sign), expire);
    if(ret != 0){
        WARNING_LOG("memcached update fail, key:[%s], value:[%s]", key, sign);
        return FAIL;
    }

    NOTICE_LOG("memcached update success, key:[%s], value[%s]", key, sign);
    return SUCCESS;
}

int mcc_update_behavior_cnt(uint baiduid, uint uid, bool is_login, uint soid, const char* baidu_str)
{
    int ret = -1;
    if(is_login){
        ret = db_update_user_behavior_cnt(uid, soid);
        if(ret != 0){
            WARNING_LOG("db_update_user_behavior_cnt fail, uid[%d], soid[%d]", uid, soid);
            return FAIL;
        }
    }
    else{
        ret = db_update_co_user_behavior_cnt(baiduid, soid, baidu_str);
        if(ret != 0){
            WARNING_LOG("db_update_co_user_behavior_cnt fail, baiduid[%d], soid[%d]", baiduid, soid);
            return FAIL;
        }
    }
#ifdef _DEBUG_TIME
    DEBUG_LOG("mcc_update_behavior_cnt success, baiduid[%d], uid[%d], soid[%d]", baiduid, uid, soid);
#endif
    return SUCCESS;


}
