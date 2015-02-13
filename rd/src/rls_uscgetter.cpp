//============================================================================
// @author      : weijingqi (weijingqi@baidu.com)
// @file        : rls_uscgetter.h
// @date        : 25 May 2012, 14:19:53
// @copyright   : 2011 Baidu.com, Inc. All Rights Reserved
// @encoding    :
// @version     :
// @brief       : 数据中心用户数据获取
//============================================================================

#include<time.h>
#include "bsl/var/JsonDeserializer.h"
#include "bsl/ResourcePool.h"
#include "bsl/var/implement.h"
#include <curl/curl.h>
#include "rls_uscgetter.h"

namespace rls{

    int write_result(char *data, size_t size, size_t nmemb, void *userData){

        if (userData == NULL) {
            return 0;
        }
        char* page = (char*) userData;
        int len = 0;
        if (page) {
            len = strlen(page);
        }
        int realsize = size * nmemb;
        //为了适应多次回调来接受一个完整的应答包
        if ((len + realsize) >= MAX_USC_RESP_LEN) {
            return -1;
        }
        if (page) {
            memcpy(page+len, data, realsize);
            page[len+realsize] = 0;
        }
        return size * nmemb;
    }

    /**
     *@brief:构造函数
     */
    UscGetter::UscGetter(){
    }
    /**
     *@brief:虚构函数
     */
    UscGetter::~UscGetter(){

    }

    int UscGetter::get_prefdata(Item_bean* items, uint &len_items,
                                uint &total, uint max_len_items,
                                uint need_len, const uint start,
                                uint uid, bool need_mtime,
                                enum DB_PREF_TYPE type){
        struct timeval s;
        struct timeval e;
        gettimeofday(&s, NULL);
        if(NULL == items){
            gettimeofday(&e, NULL);
            WARNING_LOG("third[usc_third_fail], cost[%u] [wrong param in get_prefdata]", TIMEMSECDIFF(s, e));
            return FAIL;
        }
        if(p_global.USC_OK == false){
            gettimeofday(&e, NULL);
            WARNING_LOG("third[usc_third_fail], cost[%d] [usc fail]", TIMEMSECDIFF(s, e));
            return FAIL;
        }
        char* ipport = p_global.USC_IPPORT;
        char url[MAX_URL_LEN];
        int usc_type;
        int usc_cmdno;
        int time_sign = 0;
        switch (type){
            case DB_SONGLOVE:
                usc_type = USC_PREF_TYPE_LSONG;
                usc_cmdno = USC_PREF_CMD_NO;
                if(need_mtime){
                    time_sign = 1;
                }
                break;
            case DB_SONGHATE:
                usc_type = USC_PREF_TYPE_HSONG;
                usc_cmdno = USC_DIANTAI_HATE_CMD_NO;
                if(need_mtime){
                    time_sign = 1;
                }
                break;
            case DB_SONGCLOUD:
				usc_type = USC_CLOUD_TYPE_SONG;
                if(need_mtime){
                    usc_cmdno = USC_CLOUD_TIME_CMD_NO;
                    time_sign = 1;
                }
                else{
                    usc_cmdno = USC_CLOUD_CMD_NO;
                }
                break;
            default:
                gettimeofday(&e, NULL);
                WARNING_LOG("third[usc_third_fail], cost[%d] [wrong pref type[%d]]", TIMEMSECDIFF(s, e), type);
                return FAIL;
        }

        if(need_len > max_len_items){
            need_len = max_len_items;
        }

        if(need_len > max_len_items){
            need_len = max_len_items;
        }
        snprintf(url, MAX_URL_LEN, USC_PREF_REQUEST_FORMAT, ipport, usc_cmdno, uid, usc_type, USC_NEED_TOTAL,
                 start, need_len, time_sign);
#ifdef _DEBUG_TIME
        DEBUG_LOG("usc_url:%s", url);
#endif
        CURL* curl = NULL;
        CURLcode code;
        bsl::ResourcePool rp;
        char page[MAX_USC_RESP_LEN];
        memset(page, 0, sizeof(page));
        bsl::var::JsonDeserializer jd(rp);
        curl = curl_easy_init();
        if(NULL == curl){
            gettimeofday(&e, NULL);
            WARNING_LOG("third[usc_third_fail], cost[%d] [curl_easy_init fail]", TIMEMSECDIFF(s, e));
            if (curl != NULL) {
                curl_easy_cleanup(curl);
            }
            return FAIL;
        }
        code = curl_easy_setopt(curl, CURLOPT_URL, url);
        if(code != CURLE_OK){
            gettimeofday(&e, NULL);
            WARNING_LOG("third[usc_third_fail], cost[%d] [curl_easy_setopt(curl, CURLOPT_URL, %s) fail]", TIMEMSECDIFF(s, e), url);
            if (curl != NULL) {
                curl_easy_cleanup(curl);
            }
            return FAIL;
        }
        code = curl_easy_setopt(curl, CURLOPT_TIMEOUT, CWR_TIMEOUT);
        if(code != CURLE_OK){
            gettimeofday(&e, NULL);
            WARNING_LOG("third[usc_third_fail], cost[%d] [curl_easy_setopt(curl, CURLOPT_TIMEOUT, %s) fail]", TIMEMSECDIFF(s, e), url);
            if (curl != NULL) {
                curl_easy_cleanup(curl);
            }
            return FAIL;
        }
        code = curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1L);
        if(code != CURLE_OK){
            gettimeofday(&e, NULL);
            WARNING_LOG("third[usc_third_fail], cost[%d] [curl_easy_setopt(curl, CURLOPT_NOSIGNAL, %s) fail]", TIMEMSECDIFF(s, e), url);
            if (curl != NULL) {
                curl_easy_cleanup(curl);
            }
            return FAIL;
        }
        code = curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_result);
        if(code != CURLE_OK){
            gettimeofday(&e, NULL);
            WARNING_LOG("third[usc_third_fail], cost[%d] [curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_result) fail]", TIMEMSECDIFF(s, e));
            if (curl != NULL) {
                curl_easy_cleanup(curl);
            }
            return FAIL;
        }
        code = curl_easy_setopt(curl, CURLOPT_WRITEDATA, page);
        if(code != CURLE_OK){
            gettimeofday(&e, NULL);
            WARNING_LOG("third[usc_third_fail], cost[%d] [curl_easy_setopt(curl, CURLOPT_WRITEDATA, page) fail]", TIMEMSECDIFF(s, e));
            if (curl != NULL) {
                curl_easy_cleanup(curl);
            }
            return FAIL;
        }
        memset(page, 0, MAX_USC_RESP_LEN);
        code = curl_easy_perform(curl);
        if(code != CURLE_OK){
            gettimeofday(&e, NULL);
            WARNING_LOG("third[usc_third_fail], cost[%d] [curl_easy_perform(curl) fail]", TIMEMSECDIFF(s, e));
            if (curl != NULL) {
                curl_easy_cleanup(curl);
            }
            return FAIL;
        }
        if(strlen(page) == 0){
            gettimeofday(&e, NULL);
            WARNING_LOG("third[usc_third_fail], cost[%d] [get data from usc fail, pagelen=0]", TIMEMSECDIFF(s, e));
            return FAIL;
        }
        try{
            bsl::var::IVar &resp = jd.deserialize(page);
            int err_no = resp["error"].to_int32();
            if(err_no != USC_RESP_OK && err_no != USC_RESP_OK2){
                gettimeofday(&e, NULL);
                WARNING_LOG("third[usc_third_fail], cost[%d] [usc resp fail, err_no[%d]]", TIMEMSECDIFF(s, e), err_no);
                if (curl != NULL) {
                    curl_easy_cleanup(curl);
                }
                return FAIL;
            }
            total = resp["total"].to_int32();
            len_items = resp["data"].size();
            if(need_mtime){
                for(int i = 0; i < len_items; i++){
                    items[i].itemid = resp["data"][i]["id"].to_int64();
                    items[i].date = resp["data"][i]["ctime"].to_int32();
                }
            }
            else{
                if(type == DB_SONGLOVE){
                    for(int i = 0; i < len_items; i++){
                        items[i].itemid = resp["data"][i]["song_id"].to_int64();
                    }
                }else{
                    for(int i = 0; i < len_items; i++){
                        items[i].itemid = resp["data"][i].to_int64();
                    }
                }
            }
        }
        catch(bsl::Exception& exception){
            /*
            WARNING_LOG("An exception[%s] was thrown from[%s:%d:%s] with a message[%s]! stack_trace:%s%s",
                        e.name(), e.file(), int(e.line()), e.function(),
                        e.what(), e.get_line_delimiter(), e.stack());
            */
            gettimeofday(&e, NULL);
            WARNING_LOG("third[usc_third_fail], cost[%d] "
                "[An exception[%s] was thrown from[%s:%d:%s] with a message[%s]! stack_trace:%s%s]",
                TIMEMSECDIFF(s, e), exception.name(), exception.file(), int(exception.line()), exception.function(),
                exception.what(), exception.get_line_delimiter(), exception.stack());
            if(NULL != curl){
                curl_easy_cleanup(curl);
            }
            return FAIL;

        }catch(std::exception& exception){
            gettimeofday(&e, NULL);
            WARNING_LOG("third[usc_third_fail], cost[%d] "
                "A std::exception[%s] was thrown! there must be a BUG!",
                TIMEMSECDIFF(s, e), exception.what());
            if(NULL != curl){
                curl_easy_cleanup(curl);
            }
            return FAIL;
        }

#ifdef _DEBUG_TIME
        DEBUG_LOG("get prefdata from usc, usc type:%d, usc_start:%d, usc len:%d, usc total:%d, resp len:%d",
                  usc_type, start, need_len, total, len_items);
#endif
        if(NULL != curl){
            curl_easy_cleanup(curl);
        }
        gettimeofday(&e, NULL);
        NOTICE_LOG("third[usc_third], cost[%d]", TIMEMSECDIFF(s, e));
        return SUCCESS;
    }

    int UscGetter::get_allprefcnt(uint &len_songlove, uint &len_songhate,
                                  uint &len_singerlove, uint &len_singerhate,
                                  uint uid){
        struct timeval s;
        struct timeval e;
        gettimeofday(&s, NULL);
        if(p_global.USC_OK == false){
            gettimeofday(&e, NULL);
            WARNING_LOG("third[usc_third_fail], cost[%d] [usc fail]", TIMEMSECDIFF(s, e));
            return FAIL;
        }
        char* ipport = p_global.USC_IPPORT;
        char url[MAX_URL_LEN];
        snprintf(url, MAX_URL_LEN, USC_PREF_REQUEST_FORMAT3, ipport, USC_ALL_PREF_COUNT_CMD_NO,
                 uid, USC_LOVE_HATE_PREF_ITEM_TYPE);
#ifdef _DEBUG_TIME
        DEBUG_LOG("usc_url:%s", url);
#endif
        NOTICE_LOG("usc_url:%s", url);
        CURL* curl = NULL;
        CURLcode code;
        bsl::ResourcePool rp;
        char page[MAX_USC_RESP_LEN];
        memset(page, 0, sizeof(page));
        bsl::var::JsonDeserializer jd(rp);
        curl = curl_easy_init();
        if(NULL == curl){
            gettimeofday(&e, NULL);
            WARNING_LOG("third[usc_third_fail], cost[%d] [curl_easy_init fail]", TIMEMSECDIFF(s, e));
            if (curl != NULL) {
                curl_easy_cleanup(curl);
            }
            return FAIL;
        }
        code = curl_easy_setopt(curl, CURLOPT_URL, url);
        if(code != CURLE_OK){
            gettimeofday(&e, NULL);
            WARNING_LOG("third[usc_third_fail], cost[%d] [curl_easy_setopt(curl, CURLOPT_URL, %s) fail]", TIMEMSECDIFF(s, e), url);
            if (curl != NULL) {
                curl_easy_cleanup(curl);
            }
            return FAIL;
        }
        code = curl_easy_setopt(curl, CURLOPT_TIMEOUT, CWR_TIMEOUT);
        if(code != CURLE_OK){
            gettimeofday(&e, NULL);
            WARNING_LOG("third[usc_third_fail], cost[%d] [curl_easy_setopt(curl, CURLOPT_TIMEOUT, %s) fail]", TIMEMSECDIFF(s, e), url);
            if (curl != NULL) {
                curl_easy_cleanup(curl);
            }
            return FAIL;
        }
        code = curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1L);
        if(code != CURLE_OK){
            gettimeofday(&e, NULL);
            WARNING_LOG("third[usc_third_fail], cost[%d] [curl_easy_setopt(curl, CURLOPT_NOSIGNAL, %s) fail]", TIMEMSECDIFF(s, e), url);
            if (curl != NULL) {
                curl_easy_cleanup(curl);
            }
            return FAIL;
        }
        code = curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_result);
        if(code != CURLE_OK){
            gettimeofday(&e, NULL);
            WARNING_LOG("third[usc_third_fail], cost[%d] [curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_result) fail]", TIMEMSECDIFF(s, e));
            if (curl != NULL) {
                curl_easy_cleanup(curl);
            }
            return FAIL;
        }
        code = curl_easy_setopt(curl, CURLOPT_WRITEDATA, page);
        if(code != CURLE_OK){
            gettimeofday(&e, NULL);
            WARNING_LOG("third[usc_third_fail], cost[%d] [curl_easy_setopt(curl, CURLOPT_WRITEDATA, page) fail]", TIMEMSECDIFF(s, e));
            if (curl != NULL) {
                curl_easy_cleanup(curl);
            }
            return FAIL;
        }
        memset(page, 0, MAX_USC_RESP_LEN);
        code = curl_easy_perform(curl);
        if(code != CURLE_OK){
            gettimeofday(&e, NULL);
            WARNING_LOG("third[usc_third_fail], cost[%d] [curl_easy_perform(curl) fail]", TIMEMSECDIFF(s, e));
            if (curl != NULL) {
                curl_easy_cleanup(curl);
            }
            return FAIL;
        }
        if(strlen(page) == 0){
            gettimeofday(&e, NULL);
            WARNING_LOG("third[usc_third_fail], cost[%d] [get data from usc fail, pagelen=0]", TIMEMSECDIFF(s, e));
            return FAIL;
        }
        try{
            bsl::var::IVar &resp = jd.deserialize(page);
            int err_no = resp["error"].to_int32();
            if(err_no != USC_RESP_OK && err_no != USC_RESP_OK2){
                gettimeofday(&e, NULL);
                WARNING_LOG("third[usc_third_fail], cost[%d] [usc resp fail, err_no[%d]]", TIMEMSECDIFF(s, e), err_no);
                if (curl != NULL) {
                    curl_easy_cleanup(curl);
                }
                return FAIL;
            }
            char type[5];
            snprintf(type, 5, "%d", USC_PREF_TYPE_LSONG);
            len_songlove = resp["data"][type].to_int32();
            snprintf(type, 5, "%d", USC_PREF_TYPE_HSONG);
            len_songhate = resp["data"][type].to_int32();
            len_singerlove = 0;
            len_singerhate = 0;
        }
        catch(bsl::Exception& exception){
            gettimeofday(&e, NULL);
            WARNING_LOG("third[usc_third_fail], cost[%d] "
                "[An exception[%s] was thrown from[%s:%d:%s] with a message[%s]! stack_trace:%s%s]",
                TIMEMSECDIFF(s, e), exception.name(), exception.file(), int(exception.line()), exception.function(),
                exception.what(), exception.get_line_delimiter(), exception.stack());
            if(NULL != curl){
                curl_easy_cleanup(curl);
            }
            return FAIL;

        }catch(std::exception& exception){
            gettimeofday(&e, NULL);
            WARNING_LOG("third[usc_third_fail], cost[%d] "
                "A std::exception[%s] was thrown! there must be a BUG!",
                TIMEMSECDIFF(s, e), exception.what());
            if(NULL != curl){
                curl_easy_cleanup(curl);
            }
            return FAIL;
        }
        if(NULL != curl){
            curl_easy_cleanup(curl);
        }
        gettimeofday(&e, NULL);
        NOTICE_LOG("third[usc_third], cost[%d]", TIMEMSECDIFF(s, e));
        return SUCCESS;
    }

    int UscGetter::get_tagsong(song_id_t* tagsong, uint &len_tagsong,
                    char* tag_word, uint max_len){
        struct timeval s;
        struct timeval e;
        gettimeofday(&s, NULL);
        if(NULL == tagsong || NULL == tag_word){
            gettimeofday(&e, NULL);
            WARNING_LOG("third[tagsearch_third_fail], cost[%d] [null param]", TIMEMSECDIFF(s, e));
            return FAIL;
        }
        len_tagsong = 0;
        int ret;
        bsl::ResourcePool rpool;
        bsl::var::Dict currDict;
        ts_head_t ts_head;
        int pack_len;
        int ret_num;
        int res_arr_len;
        mc_pack_t* mcpack_arr = NULL;
        mc_pack_t* item = NULL;
        mc_uint32_t song_id;
        mc_pack_t * pack = NULL;
        int ts_head_len;
        ub::nshead_talkwith_t* currTalk = new ub::nshead_talkwith_t;
        if(NULL == currTalk){
            gettimeofday(&e, NULL);
            WARNING_LOG("third[tagsearch_third_fail], cost[%d] [create nshead_talkwith_t fail]", TIMEMSECDIFF(s, e));
            return FAIL;
        }
        currTalk->reqhead.log_id = rand();
        currTalk->reqbuf = new char[DEFAULT_MCPACK_LEN];
        if(NULL == currTalk->reqbuf){
            gettimeofday(&e, NULL);
            WARNING_LOG("third[tagsearch_third_fail], cost[%d] [create reqbuf fail]", TIMEMSECDIFF(s, e));
            goto TAG_SONG_ERROR;
        }
        memset(currTalk->reqbuf, 0, DEFAULT_MCPACK_LEN);
        ts_head_len = sizeof(ts_head);
        ts_head.cmd_no = TAG_CMD_NO;
        snprintf(ts_head.data_type, 64, "%s", TAG_KIT);
        ts_head.page_no = TAG_START_PAGE_NO;
        ts_head.num_per_page = max_len;
        memcpy(currTalk->reqbuf, &ts_head, ts_head_len);
        pack = mc_pack_open_w_rp(1, currTalk->reqbuf + ts_head_len, DEFAULT_MCPACK_LEN - ts_head_len, &rpool);
        ret = MC_PACK_PTR_ERR(pack);
        if (0 != ret){
            gettimeofday(&e, NULL);
            WARNING_LOG("third[tagsearch_third_fail], cost[%d] [the mcpack of request is invalid, return.]", TIMEMSECDIFF(s, e));
            goto TAG_SONG_ERROR;
        }
        ret = mc_pack_put_str(pack, "word", tag_word);
        if(ret != 0){
            gettimeofday(&e, NULL);
            WARNING_LOG("third[tagsearch_third_fail], cost[%d] [put word fail[%d]]", TIMEMSECDIFF(s, e), ret);
            goto TAG_SONG_ERROR;
        }
        ret = mc_pack_put_int32(pack, "type", 6);
        if (ret != 0){
            gettimeofday(&e, NULL);
            WARNING_LOG("third[tagsearch_third_fail], cost[%d] [put type fail[%d]]", TIMEMSECDIFF(s, e), ret);
            goto TAG_SONG_ERROR;
        }
        ret = mc_pack_put_int32(pack, "copycat", 4);
        if (ret != 0){
            gettimeofday(&e, NULL);
            WARNING_LOG("third[tagsearch_third_fail], cost[%d] [put copycat fail[%d]]", TIMEMSECDIFF(s, e), ret);
            goto TAG_SONG_ERROR;
        }
        ret = mc_pack_put_int32(pack, "from", 0);
        if (ret != 0){
            gettimeofday(&e, NULL);
            WARNING_LOG("third[tagsearch_third_fail], cost[%d] [put from fail[%d]]", TIMEMSECDIFF(s, e), ret);
            goto TAG_SONG_ERROR;
        }
        ret = mc_pack_put_int32(pack, "limit", 0);
        if (ret != 0){
            gettimeofday(&e, NULL);
            WARNING_LOG("third[tagsearch_third_fail], cost[%d] [put limit fail[%d]]", TIMEMSECDIFF(s, e), ret);
            goto TAG_SONG_ERROR;
        }
        ret = mc_pack_put_int32(pack, "ip", 0);
        if (ret != 0){
            gettimeofday(&e, NULL);
            WARNING_LOG("third[tagsearch_third_fail], cost[%d] [put ip fail[%d]]", TIMEMSECDIFF(s, e), ret);
            goto TAG_SONG_ERROR;
        }
        mc_pack_close(pack);
        pack_len = mc_pack_get_size(pack);
        if (pack_len < 0){
            gettimeofday(&e, NULL);
            WARNING_LOG("third[tagsearch_third_fail], cost[%d] [get req pack size fail]", TIMEMSECDIFF(s, e));
            goto TAG_SONG_ERROR;
        }
        currTalk->reqhead.body_len = ts_head_len + pack_len;
        currTalk->resbuf = new char[DEFAULT_MCPACK_LEN];
        if(NULL == currTalk->resbuf){
            gettimeofday(&e, NULL);
            WARNING_LOG("third[tagsearch_third_fail], cost[%d] [create resbuf fail]", TIMEMSECDIFF(s, e));
            goto TAG_SONG_ERROR;
        }
        memset(currTalk->resbuf, 0, DEFAULT_MCPACK_LEN);
        currTalk->maxreslen = DEFAULT_MCPACK_LEN;
        ret = p_global.ubmgr.nshead_singletalk(TAG_SERVICE, currTalk, currDict);
        if(0 != ret){
            gettimeofday(&e, NULL);
            WARNING_LOG("third[tagsearch_third_fail], cost[%d] [simple talk error:%s]", TIMEMSECDIFF(s, e), ub::get_talk_errorinfo(ret));
            goto TAG_SONG_ERROR;
        }
        else{
            ret_num = ((ts_head_t *)(currTalk->resbuf))->ret_num;
            if(ret_num <= 0){
                gettimeofday(&e, NULL);
                WARNING_LOG("third[tagsearch_third_fail], cost[%d] [ret_num <= 0]", TIMEMSECDIFF(s, e));
                goto TAG_SONG_ERROR;
            }
            pack = mc_pack_open_r_rp(currTalk->resbuf+ts_head_len, DEFAULT_MCPACK_LEN - ts_head_len, &rpool);
            mcpack_arr = mc_pack_get_array(pack, "res_array");
            ret = MC_PACK_PTR_ERR(mcpack_arr);
            if(0 != ret){
                gettimeofday(&e, NULL);
                WARNING_LOG("third[tagsearch_third_fail], cost[%d] [get res_array fail]", TIMEMSECDIFF(s, e));
                goto TAG_SONG_ERROR;
            }
            res_arr_len = mc_pack_get_item_count(mcpack_arr);
            for(int i = 0; i < res_arr_len && i < max_len; i++){
                item = mc_pack_get_object_arr(mcpack_arr, i);
                ret = MC_PACK_PTR_ERR(item);
                if(0 != ret){
                    WARNING_LOG("get item fail");
                    break;
                }
                ret = mc_pack_get_uint32(item, "song_id", &song_id);
                if(ret != 0){
                    WARNING_LOG("get song_id fail");
                    break;
                }
                tagsong[len_tagsong].sid = (uint32_t)song_id;
                len_tagsong++;
            }
            mc_pack_close(pack);
        }

        if(NULL != currTalk->resbuf){
            delete []currTalk->resbuf;
        }
        if(NULL != currTalk->reqbuf){
            delete []currTalk->reqbuf;
        }
        if(NULL != currTalk){
            delete currTalk;
        }
        gettimeofday(&e, NULL);
        NOTICE_LOG("third[tagsearch_third], cost[%d]", TIMEMSECDIFF(s, e));
        return SUCCESS;
    TAG_SONG_ERROR:
        if(NULL != currTalk->resbuf){
            delete []currTalk->resbuf;
        }
        if(NULL != currTalk->reqbuf){
            delete []currTalk->reqbuf;
        }
        if(NULL != currTalk){
            delete currTalk;
        }
        return FAIL;
    }

}

