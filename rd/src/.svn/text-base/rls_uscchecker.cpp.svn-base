//============================================================================
// @author      : weijingqi (weijingqi@baidu.com)
// @file        : rls_uscchecker.cpp
// @date        : 05 Jul 2012,11:28:27
// @copyright   : 2012 Baidu.com, Inc. All Rights Reserved
// @encoding    :
// @version     :
// @brief       : 用户中心检测
//============================================================================
#include "rls_uscchecker.h"
#include "common.h"
#include "userworker.h"
#include "rls.h"
#include<time.h>
#include "bsl/var/JsonDeserializer.h"
#include "bsl/ResourcePool.h"
#include "bsl/var/implement.h"
#include <curl/curl.h>

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

int check_one(char* ipport){
    struct timeval s;
    struct timeval e;
    gettimeofday(&s, NULL);
    char url[MAX_URL_LEN];
    int usc_type = 1;
    //int usc_cmdno = 70003;
    int usc_cmdno = 21000;
    int uid = 256272475;
    int start = 0;
    int need_len = 5;
    snprintf(url, MAX_URL_LEN, USC_PREF_REQUEST_FORMAT, ipport, usc_cmdno, uid, usc_type, USC_NOTNEED_TOTAL,
             start, need_len, 0);
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
    return SUCCESS;
}

void* usc_check(void *arg){
    int current_ip = 1;
    int ret;
    bool check1 = false;
    bool check2 = false;
    while(1){
        check1 = true;
        check2 = true;
        //检测第一台
        ret = check_one(p_global.USC_IPPORT1);
        if(ret == FAIL){
            FATAL_LOG("third[usc_fatal], uscipport[%s]", p_global.USC_IPPORT1);
            check1 = false;
        }
        else if(current_ip != 1){//第一台成功，恢复过来
            snprintf(p_global.USC_IPPORT, MAX_IPPORT_LEN, "%s", p_global.USC_IPPORT1);
            current_ip = 1;
            p_global.USC_OK = true;
            NOTICE_LOG("change usc ipport, [%s]", p_global.USC_IPPORT);
        }
        //检测第二台
        ret = check_one(p_global.USC_IPPORT2);
        if(ret == FAIL){
            FATAL_LOG("third[usc_fatal], uscipport[%s]", p_global.USC_IPPORT2);
            check2 = false;
        }
        //如果第一台失败，第二台成功，切换
        if(check1 == false && check2 == true){
            snprintf(p_global.USC_IPPORT, MAX_IPPORT_LEN, "%s", p_global.USC_IPPORT2);
            current_ip = 2;
            p_global.USC_OK = true;
            NOTICE_LOG("change usc ipport, [%s]", p_global.USC_IPPORT);
        }
        //如果两台都有问题，则用户中心不可用
        if(check1 == false && check2 == false){
            p_global.USC_OK = false;
            current_ip = 0;
        }
        //5s
        sleep(5);
    }

}
