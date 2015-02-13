//============================================================================
// @author      : weijingqi (weijingqi@baidu.com)
// @file        : rls_queryhandler.h
// @date        : 13 May 2012,11:17:57
// @copyright   : 2011 Baidu.com, Inc. All Rights Reserved
// @encoding    :
// @version     :
// @brief       : 处理查询类的请求
//============================================================================

#include "rls_queryhandler.h"
#include "mcCache.h"

namespace rls{
    bool ticket_cmp(Ticket_rec_t a, Ticket_rec_t b){
        return a.weight > b.weight;
    }

    inline bool ch_weight_cmp(ch_info_t const &a, ch_info_t const &b){
        return a.ch_pv_order < b.ch_pv_order;
    }


    QueryHandler::QueryHandler(){
        _usc_getter = new UscGetter();
        if(NULL == _usc_getter){
            FATAL_LOG("create _usc_getter fail");
        }
        _dict_seeker = new DictSeeker();
        if(NULL == _dict_seeker){
            FATAL_LOG("create _dict_seeker fail");
        }
    }

    QueryHandler::~QueryHandler(){
        if(NULL != _usc_getter){
            delete _usc_getter;
        }
        if(NULL != _dict_seeker){
            delete _dict_seeker;
        }
    }

    int QueryHandler::handle_channellist_cmd(const User_worker_buf& u_buf){
        if (NULL == u_buf.p_thread_buf || NULL == u_buf.p_cmd){
                WARNING_LOG("p_thread_buf or clientCmd is null");
                return FAIL;
        }
        if(!u_buf.p_cmd->has_chlc()){
            WARNING_LOG("unsupport cmd, should be chlc");
            return FAIL;
        }
        const idl::chlistcmd& chlc = u_buf.p_cmd->chlc();
        char cate_name[MAX_CHNAME_LEN];
        snprintf(cate_name, MAX_CHNAME_LEN, "%s", chlc.cate_name());
        NOTICE_LOG("start handle_channellist_cmd, [cate_name:%s]", cate_name);
        //所有分类的频道
        char pack_buf[DEFAULT_MCPACK_LEN];
        bsl::ResourcePool rp;
        mc_pack_t * mcpack = NULL;
        mc_pack_t * mcpack_arr = NULL;
        mcpack = mc_pack_open_w_rp(2, pack_buf, DEFAULT_MCPACK_LEN, &rp);
        int ret = MC_PACK_PTR_ERR(mcpack);
        if (0 != ret){
            WARNING_LOG("the mcpack of request is invalid, return.");
            return FAIL;
        }
        ret = mc_pack_put_int32(mcpack, "status", 0);
        if (ret != 0){
            WARNING_LOG("put status fail[%d]", ret);
            return FAIL;
        }
        mcpack_arr = mc_pack_put_array(mcpack, "channels");
        if (MC_PACK_PTR_ERR(mcpack_arr)){
            WARNING_LOG("mcpack put array fail");
            return FAIL;
        }

        if(strcmp(chlc.cate_name(), CH_PERSONAL_NAME) == 0){
            ret = this->_pack_personal_ch_arr(p_global.ch_info_list, p_global.max_chinfolist_len, mcpack_arr, u_buf);
            if(ret == FAIL){
                WARNING_LOG("pack ch_info_list fail");
                return FAIL;
            }
        }else{
            ret = this->_pack_ch_arr(p_global.ch_info_list, p_global.max_chinfolist_len, mcpack_arr, cate_name);
            if(ret == FAIL){
                WARNING_LOG("pack ch_info_list fail");
                return FAIL;
            }
        }

        //回复
        mc_pack_close(mcpack);
        int res_pack_len = mc_pack_get_size(mcpack);
        if (res_pack_len < 0){
            WARNING_LOG("get res pack size fail");
            return FAIL;
        }
        nshead_t head;
        head.body_len = res_pack_len;
        strncpy(head.provider, PROJECT_NAME, 8);
        head.provider[7] = 0;
        head.log_id = u_buf.p_thread_buf->head.log_id;
        ret = nshead_write(u_buf.p_thread_buf->fd, &head, (void *) pack_buf,
                           g_config.wtimeout * 1000);
        if (0 != ret){
            WARNING_LOG("send response to ui error[errno:%d]", ret);
            return FAIL;
        }
        NOTICE_LOG("The process end info:[tid:%d][usrname:%s][client request type: chlc][status:0]",
               u_buf.tid, u_buf.p_cmd->username(NULL));
        return SUCCESS;
    }

    int QueryHandler::handle_cssingerlist_cmd(const User_worker_buf& u_buf){
        if (NULL == u_buf.p_thread_buf || NULL == u_buf.p_cmd){
                WARNING_LOG("p_thread_buf or clientCmd is null");
                return FAIL;
        }
        if(!u_buf.p_cmd->has_cslc()){
            WARNING_LOG("unsupport cmd, should be cslc");
            return FAIL;
        }
        uint uid = u_buf.p_cmd->uid();
        int rf = u_buf.p_cmd->rf();
        char baiduid_str[MAX_BAIDUID_LEN];
        snprintf(baiduid_str, MAX_BAIDUID_LEN, "%s", u_buf.p_cmd->baiduid());
        if(NULL == baiduid_str){
            snprintf(baiduid_str, MAX_BAIDUID_LEN, "%s", "");
        }
        if((int)strlen(baiduid_str) != BAIDUID_LEN  && uid <= 0){//有百度cookie和登录用户才可以进行冷启动
            WARNING_LOG("can not get cs singer list, has not baiduid and uid");
            return FAIL;
        }
        NOTICE_LOG("start handle_cssingerlist_cmd,baiduid[%s],uid[%d]", baiduid_str, uid);
        //冷启动歌手列表
        char pack_buf[DEFAULT_MCPACK_LEN];
        bsl::ResourcePool rp;
        mc_pack_t * mcpack = NULL;
        mc_pack_t * mcpack_arr = NULL;
        mc_pack_t * mcpack_obj = NULL;
        mcpack = mc_pack_open_w_rp(2, pack_buf, DEFAULT_MCPACK_LEN, &rp);
        int ret = MC_PACK_PTR_ERR(mcpack);
        if (0 != ret){
            WARNING_LOG("the mcpack of request is invalid, return.");
            return FAIL;
        }
        ret = mc_pack_put_int32(mcpack, "status", 0);
        if (ret != 0){
            WARNING_LOG("put status fail[%d]", ret);
            return FAIL;
        }
        mcpack_arr = mc_pack_put_array(mcpack, "list");
        if (MC_PACK_PTR_ERR(mcpack_arr)){
            WARNING_LOG("mcpack put array fail");
            return FAIL;
        }
        for(uint i = 0; i < p_global.cold_start_singer_len; i++){
            mcpack_obj = mc_pack_put_object(mcpack_arr, NULL);
            if (MC_PACK_PTR_ERR(mcpack_obj)){
                WARNING_LOG("mcpack put object fail");
                return FAIL;
            }
            ret = mc_pack_put_int64(mcpack_obj, "singerid", (uint64_t)(p_global.cold_start_singer_list[i]));
            if (ret != 0){
                WARNING_LOG("mcpack put int64 fail");
            }
        }
        //回复
        mc_pack_close(mcpack);
        int res_pack_len = mc_pack_get_size(mcpack);
        if (res_pack_len < 0){
            WARNING_LOG("get res pack size fail");
            return FAIL;
        }
        nshead_t head;
        head.body_len = res_pack_len;
        strncpy(head.provider, PROJECT_NAME, 8);
        head.provider[7] = 0;
        head.log_id = u_buf.p_thread_buf->head.log_id;
        ret = nshead_write(u_buf.p_thread_buf->fd, &head, (void *) pack_buf,
                           g_config.wtimeout * 1000);
        if (0 != ret){
            WARNING_LOG("send response to ui error[errno:%d]", ret);
            return FAIL;
        }
        NOTICE_LOG("The process end info:[tid:%d][usrname:%s][client request type: cslc][status:0]",
               u_buf.tid, u_buf.p_cmd->username(NULL));
        return SUCCESS;
    }

    int QueryHandler::handle_newuser_cmd(const User_worker_buf& u_buf){
        if (NULL == u_buf.p_thread_buf || NULL == u_buf.p_cmd){
                WARNING_LOG("p_thread_buf or clientCmd is null");
                return FAIL;
        }
        if(!u_buf.p_cmd->has_nuc()){
            WARNING_LOG("unsupport cmd, should be nuc");
            return FAIL;
        }
        int ret;
        uint uid = u_buf.p_cmd->uid();
        int rf = u_buf.p_cmd->rf();
        char baiduid_str[MAX_BAIDUID_LEN];
        snprintf(baiduid_str, MAX_BAIDUID_LEN, "%s", u_buf.p_cmd->baiduid());
        if(NULL == baiduid_str){
            snprintf(baiduid_str, MAX_BAIDUID_LEN, "%s", "");
        }
        if((int)strlen(baiduid_str) != BAIDUID_LEN  && uid <= 0){//有百度cookie和登录用户才可以进行冷启动
            WARNING_LOG("can not run new user cmd, has not baiduid and uid");
            return FAIL;
        }
        uint baiduid;
        ret = create_baiduid(baiduid_str, baiduid);
        NOTICE_LOG("start handle_newuser_cmd,baiduid[%s],uid[%d]", baiduid_str, uid);
        int is_new = 0;
        if(uid > 0){
            mcc_is_new_user(uid, 1, is_new);
        }
        else if(baiduid > 0){
            mcc_is_new_user(baiduid, 2, is_new);
        }
        //冷启动歌手列表
        char pack_buf[DEFAULT_MCPACK_LEN];
        bsl::ResourcePool rp;
        mc_pack_t * mcpack = NULL;
        mcpack = mc_pack_open_w_rp(2, pack_buf, DEFAULT_MCPACK_LEN, &rp);
        ret = MC_PACK_PTR_ERR(mcpack);
        if (0 != ret){
            WARNING_LOG("the mcpack of request is invalid, return.");
            return FAIL;
        }
        ret = mc_pack_put_int32(mcpack, "status", 0);
        if (ret != 0){
            WARNING_LOG("put status fail[%d]", ret);
            return FAIL;
        }
        ret = mc_pack_put_int32(mcpack, "newuser", is_new);
        if (ret != 0){
            WARNING_LOG("put status fail[%d]", ret);
            return FAIL;
        }
        //回复
        mc_pack_close(mcpack);
        int res_pack_len = mc_pack_get_size(mcpack);
        if (res_pack_len < 0){
            WARNING_LOG("get res pack size fail");
            return FAIL;
        }
        nshead_t head;
        head.body_len = res_pack_len;
        strncpy(head.provider, PROJECT_NAME, 8);
        head.provider[7] = 0;
        head.log_id = u_buf.p_thread_buf->head.log_id;
        ret = nshead_write(u_buf.p_thread_buf->fd, &head, (void *) pack_buf,
                           g_config.wtimeout * 1000);
        if (0 != ret){
            WARNING_LOG("send response to ui error[errno:%d]", ret);
            return FAIL;
        }
        NOTICE_LOG("The process end info:[tid:%d][usrname:%s][client request type: cslc][status:0]",
               u_buf.tid, u_buf.p_cmd->username(NULL));
        return SUCCESS;
    }

    int QueryHandler::_pack_personal_ch_arr(const ch_info_t* ch_list, int len,
            mc_pack_t* mcpack_arr, const User_worker_buf& u_buf){
        if(0 == len){
            return SUCCESS;
        }
        if(NULL == ch_list){
            return FAIL;
        }

        if (0 != MC_PACK_PTR_ERR(mcpack_arr)){
            return FAIL;
        }

        int ret = 0;
        //if(u_buf.p_cmd->uid() <= 0){
        ch_info_t ch_info_list[len];
        memcpy(ch_info_list, ch_list, sizeof(ch_info_t) * len);
        std::sort(ch_info_list, ch_info_list + len, ch_weight_cmp);

        mc_pack_t * mcpack_obj = NULL;
        for (int i = 0; i < len; i++){
            mcpack_obj = mc_pack_put_object(mcpack_arr, NULL);
            if (MC_PACK_PTR_ERR(mcpack_obj)){
                WARNING_LOG("mcpack put object fail");
                return FAIL;
            }
            ret = mc_pack_put_int32(mcpack_obj, "ch_id", ch_info_list[i].ch_id);
            if (ret != 0){
                WARNING_LOG("mcpack put int32 fail");
            }
            ret = mc_pack_put_str(mcpack_obj, "ch_name", ch_info_list[i].ch_name);
            if (ret != 0){
                WARNING_LOG("mcpack put str fail");
            }
            ret = mc_pack_put_str(mcpack_obj, "ch_sname", ch_info_list[i].ch_sname);
            if (ret != 0){
                WARNING_LOG("mcpack put str fail");
            }
            ret = mc_pack_put_str(mcpack_obj, "ch_desc", ch_info_list[i].ch_desc);
            if (ret != 0){
                WARNING_LOG("mcpack put str fail");
            }
            ret = mc_pack_put_int32(mcpack_obj, "ch_order", ch_info_list[i].ch_order);
            if (ret != 0){
                WARNING_LOG("mcpack put int32 fail");
            }
            ret = mc_pack_put_str(mcpack_obj, "cate_name", ch_info_list[i].cate_name);
            if (ret != 0){
                WARNING_LOG("mcpack put str fail");
            }
            ret = mc_pack_put_str(mcpack_obj, "cate_sname", ch_info_list[i].cate_sname);
            if (ret != 0){
                WARNING_LOG("mcpack put str fail");
            }
            ret = mc_pack_put_int32(mcpack_obj, "cate_order", ch_info_list[i].cate_order);
            if (ret != 0){
                WARNING_LOG("mcpack put int32 fail");
            }
            ret = mc_pack_put_int32(mcpack_obj, "ch_pv_order", ch_info_list[i].ch_pv_order);
            if (ret != 0){
                WARNING_LOG("mcpack put int32 fail");
            }
            ret = mc_pack_put_str(mcpack_obj, "ch_cover", ch_info_list[i].ch_cover);
            if (ret != 0){
                WARNING_LOG("mcpack put str fail");
            }

            mc_pack_finish( mcpack_obj);
        }
        return SUCCESS;
    }

    int QueryHandler::_pack_ch_arr(const ch_info_t* ch_info_list,
                                   int len, mc_pack_t* mcpack_arr, const char* cate_name){
        if(0 == len){
            return SUCCESS;
        }
        if(NULL == ch_info_list){
            return FAIL;
        }

        if (0 != MC_PACK_PTR_ERR(mcpack_arr)){
            return FAIL;
        }
        int ret = 0;
        mc_pack_t * mcpack_obj = NULL;
        for (int i = 0; i < len; i++){
            if(strcmp(cate_name, CATE_ALL_NAME) == 0 || strcmp(ch_info_list[i].cate_name, cate_name) == 0){
                mcpack_obj = mc_pack_put_object(mcpack_arr, NULL);
                if (MC_PACK_PTR_ERR(mcpack_obj)){
                    WARNING_LOG("mcpack put object fail");
                    return FAIL;
                }
                ret = mc_pack_put_int32(mcpack_obj, "ch_id", ch_info_list[i].ch_id);
                if (ret != 0){
                    WARNING_LOG("mcpack put int32 fail");
                }
                ret = mc_pack_put_str(mcpack_obj, "ch_name", ch_info_list[i].ch_name);
                if (ret != 0){
                    WARNING_LOG("mcpack put str fail");
                }
                ret = mc_pack_put_str(mcpack_obj, "ch_sname", ch_info_list[i].ch_sname);
                if (ret != 0){
                    WARNING_LOG("mcpack put str fail");
                }
                ret = mc_pack_put_str(mcpack_obj, "ch_desc", ch_info_list[i].ch_desc);
                if (ret != 0){
                    WARNING_LOG("mcpack put str fail");
                }
                ret = mc_pack_put_int32(mcpack_obj, "ch_order", ch_info_list[i].ch_order);
                if (ret != 0){
                    WARNING_LOG("mcpack put int32 fail");
                }
                ret = mc_pack_put_str(mcpack_obj, "cate_name", ch_info_list[i].cate_name);
                if (ret != 0){
                    WARNING_LOG("mcpack put str fail");
                }
                ret = mc_pack_put_str(mcpack_obj, "cate_sname", ch_info_list[i].cate_sname);
                if (ret != 0){
                    WARNING_LOG("mcpack put str fail");
                }
                ret = mc_pack_put_int32(mcpack_obj, "cate_order", ch_info_list[i].cate_order);
                if (ret != 0){
                    WARNING_LOG("mcpack put int32 fail");
                }
                ret = mc_pack_put_int32(mcpack_obj, "ch_pv_order", ch_info_list[i].ch_pv_order);
                if (ret != 0){
                    WARNING_LOG("mcpack put int32 fail");
                }
                ret = mc_pack_put_str(mcpack_obj, "ch_cover", ch_info_list[i].ch_cover);
                if (ret != 0){
                    WARNING_LOG("mcpack put str fail");
                }

                mc_pack_finish( mcpack_obj);
            }
        }
        return SUCCESS;
    }


    int QueryHandler::handle_utag_cmd(const User_worker_buf& u_buf){
        DEBUG_LOG("begin to handle utag cmd...");
        if (NULL == u_buf.p_thread_buf || NULL == u_buf.p_cmd){
                WARNING_LOG("p_thread_buf or utag is null");
                return FAIL;
        }
        if(!u_buf.p_cmd->has_utag_cmd()){
            WARNING_LOG("unsupport cmd, should be utag_cmd");
            return FAIL;
        }
        uint uid = u_buf.p_cmd->uid();
        if(uid <= 0){
            WARNING_LOG("utag request must have uid");
            return FAIL;
        }
        const idl::usertagscmd& utag_cmd = u_buf.p_cmd->utag_cmd();
        //const idl::chlistcmd& chlc = u_buf.p_cmd->chlc();
        uint src = utag_cmd.src();
        NOTICE_LOG("start handle_utag_cmd, [src:%u]", src);
        //请求数据
        User_tag_t user_tag_list[USER_TAG_LEN];
        int buf_size = USER_TAG_NUM;
        int len = -1;
        len = mcc_get_tag_list(uid, user_tag_list, buf_size);
        if (len <= 0){
            WARNING_LOG("get user tag fail[%d]", len);
            return FAIL;
        }

        char pack_buf[DEFAULT_MCPACK_LEN];
        bsl::ResourcePool rp;
        mc_pack_t * mcpack = NULL;
        mc_pack_t * mcpack_arr = NULL;
        mcpack = mc_pack_open_w_rp(2, pack_buf, DEFAULT_MCPACK_LEN, &rp);
        int ret = MC_PACK_PTR_ERR(mcpack);
        if (0 != ret){
            WARNING_LOG("the mcpack of request is invalid, return.");
            return FAIL;
        }
        ret = mc_pack_put_int32(mcpack, "status", 0);
        if (ret != 0){
            WARNING_LOG("put status fail[%d]", ret);
            return FAIL;
        }

        /**
        ret = mc_pack_put_int32(mcpack, "length", len);
        if (ret != 0){
            WARNING_LOG("put len fail[%d]", ret);
            return FAIL;
        }
        */

        mcpack_arr = mc_pack_put_array(mcpack, "res_arr");
        if (MC_PACK_PTR_ERR(mcpack_arr)){
            WARNING_LOG("mcpack put array fail");
            return FAIL;
        }

        mc_pack_t * mcpack_obj = NULL;
        for(uint i = 0; i < len; i++){
            mcpack_obj = mc_pack_put_object(mcpack_arr, NULL);
            if (MC_PACK_PTR_ERR(mcpack_obj)){
                WARNING_LOG("mcpack put object fail");
                return FAIL;
            }
            ret = mc_pack_put_str(mcpack_obj, "tag_title", user_tag_list[i].tag_title);
            if (ret != 0){
                WARNING_LOG("mcpack put tagtile fail");
            }
            ret = mc_pack_put_int64(mcpack_obj, "tag_id", user_tag_list[i].tag_id);
            if (ret != 0){
                WARNING_LOG("mcpack put tagid fail");
            }
            ret = mc_pack_put_int64(mcpack_obj, "tag_weight", user_tag_list[i].tag_weight);
            if (ret != 0){
                WARNING_LOG("mcpack put tagweight fail");
            }
            mc_pack_finish( mcpack_obj);
        }

        //回复
        mc_pack_close(mcpack);
        int res_pack_len = mc_pack_get_size(mcpack);
        if (res_pack_len <= 0){
            WARNING_LOG("get res pack size fail");
            return FAIL;
        }
        nshead_t head;
        head.body_len = res_pack_len;
        strncpy(head.provider, PROJECT_NAME, 8);
        head.provider[7] = 0;
        head.log_id = u_buf.p_thread_buf->head.log_id;
        ret = nshead_write(u_buf.p_thread_buf->fd, &head, (void *) pack_buf,
                           g_config.wtimeout * 1000);
        if (0 != ret){
            WARNING_LOG("send response to ui error[errno:%d]", ret);
            return FAIL;
        }
        NOTICE_LOG("The process end info:[tid:%d][usrname:%s][client request type: utag_cmd][status:0]",
               u_buf.tid, u_buf.p_cmd->username(NULL));
        return SUCCESS;
    }

    int QueryHandler::handle_tic_cmd(const User_worker_buf& u_buf){
        DEBUG_LOG("begin to handle tic cmd...");
        if (NULL == u_buf.p_thread_buf || NULL == u_buf.p_cmd){
                WARNING_LOG("p_thread_buf or utag is null");
                return FAIL;
        }
        if(!u_buf.p_cmd->has_tic()){
            WARNING_LOG("unsupport cmd, should be tic");
            return FAIL;
        }
        const idl::ticketcmd& tic = u_buf.p_cmd->tic();
        uint uid = u_buf.p_cmd->uid();
        int32_t request_len = tic.len();
        if(request_len <= 0){
            WARNING_LOG("tic cmd fail, request len[%d] <= 0", request_len);
            return 1;
        }
        if(request_len > MAX_TICKET_LEN){
            request_len = MAX_TICKET_LEN;
        }
        char baiduid_str[MAX_BAIDUID_LEN];
        snprintf(baiduid_str, MAX_BAIDUID_LEN, "%s", u_buf.p_cmd->baiduid());
        if(NULL == baiduid_str){
            snprintf(baiduid_str, MAX_BAIDUID_LEN, "%s", "");
        }
        if((int)strlen(baiduid_str) != BAIDUID_LEN  && uid <= 0){
            WARNING_LOG("tic cmd does not exec with no uid and baiduid, uid[%d], baiduid_str[%s]", uid, baiduid_str);
            return 1;
        }
        uint baiduid = 0;
        int ret;
        ret = create_baiduid(baiduid_str, baiduid);
        if(ret != 0){
            WARNING_LOG("create baiduid fail");
            return FAIL;
        }
        NOTICE_LOG("start handle tic cmd, uid[%d], baiduid[%d], request_len[%d]", uid, baiduid, request_len);

        //用户的行为
        r_userdata_t user_data;
        if(uid > 0){//登录用户取登录行为
            mcc_get_user_data(*_usc_getter, uid, user_data);
        }
        else{//非登录用户取非登录行为
            mcc_get_co_user_data(baiduid, user_data);
        }

        //统计数据
        bsl::hashmap<int, int> artist_map;
        artist_map.create(200);
        for(int i = 0; i < p_global.max_ticket_list_len; i++){
            artist_map.set(p_global.ticket_list[i].artist_id, 0, 1);
        }
        DEBUG_LOG("artist_map len[%d]", artist_map.size());
        //遍历加心
        int artist_id;
        int cnt;
        for(int i =0; i < user_data.len_songlove; i++){
            artist_id = _dict_seeker->get_singer_id(user_data.songlove[i].itemid);
            if(artist_id <= 0){
                continue;
            }
            if(artist_map.get(artist_id, &cnt) == bsl::HASH_EXIST){
                cnt += 1;
                artist_map.set(artist_id, cnt, 1);
            }
        }
        //遍历云收藏
        for(int i =0; i < user_data.len_songcloud; i++){
            artist_id = _dict_seeker->get_singer_id(user_data.songcloud[i].itemid);
            if(artist_id <= 0){
                continue;
            }
            if(artist_map.get(artist_id, &cnt) == bsl::HASH_EXIST){
                cnt += 1;
                artist_map.set(artist_id, cnt, 1);
            }
        }
        //遍历音乐盒试听
        for(int i =0; i < user_data.len_action; i++){
            if(user_data.action[i].type == (int)DB_BOX_COMPLETE_TYPE || user_data.action[i].type == (int)DB_SEARCH_SONG){
                artist_id = _dict_seeker->get_singer_id(user_data.action[i].itemid);
                if(artist_id <= 0){
                    continue;
                }
                if(artist_map.get(artist_id, &cnt) == bsl::HASH_EXIST){
                    cnt += 1;
                    artist_map.set(artist_id, cnt, 1);
                }
            }
        }
#ifdef _DEBUG_TIME
        for(bsl::hashmap <int, int>::iterator iter = artist_map.begin(); iter != artist_map.end(); iter++){
            DEBUG_LOG("artist_id[%d], cnt[%d]", iter->first, iter->second);
        }
#endif
        Ticket_rec_t rec_list[MAX_TICKET_LEN];
        int len = 0;
        bsl::hashmap <int, int> result_ids;
        result_ids.create(100);
        int tmp;
        for(int i = 0; i < p_global.max_ticket_list_len; i++){
            if(p_global.ticket_list[i].artist_id <= 0){
                continue;
            }
            if(result_ids.get(p_global.ticket_list[i].artist_id, &tmp) == bsl::HASH_NOEXIST){
                if(artist_map.get(p_global.ticket_list[i].artist_id, &tmp) == bsl::HASH_EXIST){
                    if(tmp <= 0){
                        continue;
                    }
                    if(len < request_len){
                        rec_list[len].ticket_id = p_global.ticket_list[i].ticket_id;
                        rec_list[len].weight = tmp;
                        rec_list[len].source = 1;
                        len += 1;
                        std::push_heap(rec_list, rec_list + len, ticket_cmp);
                    }
                    else{
                        if(rec_list[0].weight < tmp){
                            std::pop_heap(rec_list, rec_list + len, ticket_cmp);
                            rec_list[len-1].ticket_id = p_global.ticket_list[i].ticket_id;
                            rec_list[len-1].weight = tmp;
                            rec_list[len-1].source = 1;
                            std::push_heap(rec_list, rec_list + len, ticket_cmp);
                        }
                    }
                    result_ids.set(p_global.ticket_list[i].artist_id, 1, 1);
                }
            }
        }
        std::sort_heap(rec_list, rec_list + len, ticket_cmp);
        if(len < request_len){
            for(int i = 0; i < p_global.max_ticket_list_len && len < request_len; i++){
                if(result_ids.get(p_global.ticket_list[i].artist_id, &tmp) == bsl::HASH_NOEXIST){
                    rec_list[len].ticket_id = p_global.ticket_list[i].ticket_id;
                    rec_list[len].weight = 0;
                    rec_list[len].source = 2;
                    len += 1;
                    result_ids.set(p_global.ticket_list[i].artist_id, 1, 1);
                }
            }
        }
#ifdef _DEBUG_TIME
        for(int i = 0; i < len; i++){
            DEBUG_LOG("after heap: pos[%d] ticket_id[%d], weight[%d], source[%d]", \
                    i, rec_list[i].ticket_id, rec_list[i].weight, rec_list[i].source);
        }
#endif
        artist_map.destroy();
        result_ids.destroy();

        char pack_buf[DEFAULT_MCPACK_LEN];
        bsl::ResourcePool rp;
        mc_pack_t * mcpack = NULL;
        mc_pack_t * mcpack_arr = NULL;
        mcpack = mc_pack_open_w_rp(2, pack_buf, DEFAULT_MCPACK_LEN, &rp);
        ret = MC_PACK_PTR_ERR(mcpack);
        if (0 != ret){
            WARNING_LOG("the mcpack of request is invalid, return.");
            return FAIL;
        }
        ret = mc_pack_put_int32(mcpack, "status", 0);
        if (ret != 0){
            WARNING_LOG("put status fail[%d]", ret);
            return FAIL;
        }

        mcpack_arr = mc_pack_put_array(mcpack, "list");
        if (MC_PACK_PTR_ERR(mcpack_arr)){
            WARNING_LOG("mcpack put array fail");
            return FAIL;
        }

        mc_pack_t * mcpack_obj = NULL;
        for(uint i = 0; i < len; i++){
            mcpack_obj = mc_pack_put_object(mcpack_arr, NULL);
            if (MC_PACK_PTR_ERR(mcpack_obj)){
                WARNING_LOG("mcpack put object fail");
                return FAIL;
            }
            ret = mc_pack_put_int64(mcpack_obj, "ticket_id", rec_list[i].ticket_id);
            if (ret != 0){
                WARNING_LOG("mcpack put ticket_id fail");
            }
            ret = mc_pack_put_int64(mcpack_obj, "weight", rec_list[i].weight);
            if (ret != 0){
                WARNING_LOG("mcpack put ticket_weight fail");
            }
            ret = mc_pack_put_int64(mcpack_obj, "method", rec_list[i].source);
            if (ret != 0){
                WARNING_LOG("mcpack put ticket_source fail");
            }
            mc_pack_finish( mcpack_obj);
        }

        //回复
        mc_pack_close(mcpack);
        int res_pack_len = mc_pack_get_size(mcpack);
        if (res_pack_len <= 0){
            WARNING_LOG("get res pack size fail");
            return FAIL;
        }
        nshead_t head;
        head.body_len = res_pack_len;
        strncpy(head.provider, PROJECT_NAME, 8);
        head.provider[7] = 0;
        head.log_id = u_buf.p_thread_buf->head.log_id;
        ret = nshead_write(u_buf.p_thread_buf->fd, &head, (void *) pack_buf,
                           g_config.wtimeout * 1000);
        if (0 != ret){
            WARNING_LOG("send response to ui error[errno:%d]", ret);
            return FAIL;
        }
        NOTICE_LOG("The process end info:[tid:%d][usrname:%s][client request type: tic_cmd][status:0]",
               u_buf.tid, u_buf.p_cmd->username(NULL));
        return SUCCESS;
    }

}
