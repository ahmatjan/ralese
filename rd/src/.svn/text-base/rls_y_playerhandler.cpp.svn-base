/**
 * @file rls_y_playerhander.cpp
 * @Synopsis  处理百度音乐人播放请求
 * @author wensaiping, wensaiping@baidu.com
 * @version 1.0.0
 * @date 2013-11-14
 */

#include "mystring.h"
#include "rls_y_playerhandler.h"
namespace rls{

    YPlayerHandler::YPlayerHandler(){
        _rgen = new RGen();
        if(NULL == _rgen){
            FATAL_LOG("create _rgen fail");
        }
        _rstrategy = new RStrategy();
        if(NULL == _rstrategy){
            FATAL_LOG("create _rstrategy fail");
        }
        _dict_seeker = new DictSeeker();
        if(NULL == _dict_seeker){
            FATAL_LOG("create _dict_seeker fail");
        }
        _ral = new RAl();
        if(NULL == _ral){
            FATAL_LOG("create _ral fail");
        }
        _usc_getter = new UscGetter();
        if(NULL == _usc_getter){
            FATAL_LOG("create _usc_getter fail");
        }
    }

    YPlayerHandler::~YPlayerHandler(){
        if(NULL != _rgen){
            delete _rgen;
        }
        if(NULL != _rstrategy){
            delete _rstrategy;
        }
        if(NULL != _dict_seeker){
            delete _dict_seeker;
        }
        if(NULL != _ral){
            delete _ral;
        }
        if(NULL != _usc_getter){
            delete _usc_getter;
        }
    }

    int YPlayerHandler::handle_playlist_cmd(const User_worker_buf& u_buf){
        if (NULL == u_buf.p_thread_buf || NULL == u_buf.p_cmd){
                WARNING_LOG("p_thread_buf or clientCmd is null");
                return FAIL;
        }
        if(!u_buf.p_cmd->has_plc()){
            WARNING_LOG("unsupport cmd, should be plc");
            return FAIL;
        }
        const idl::playlistcmd& plc = u_buf.p_cmd->plc();
        char ch_name[MAX_CHNAME_LEN];
        char baiduid_str[MAX_BAIDUID_LEN];
        char username[MAX_USRNAME_LEN];
        snprintf(ch_name, MAX_CHNAME_LEN, "%s", plc.ch_name());
        //判断频道是否存在
        if(strncmp(ch_name, CH_Y_PRE, CH_Y_PRE_LEN) != 0){
            WARNING_LOG("channel not exit, do nothing, ch_name:%s", ch_name);
            return NOEXIST;
        }
        snprintf(username, MAX_USRNAME_LEN, "%s", u_buf.p_cmd->username());
        snprintf(baiduid_str, MAX_BAIDUID_LEN, "%s", u_buf.p_cmd->baiduid());
        if(NULL == baiduid_str){
            snprintf(baiduid_str, MAX_BAIDUID_LEN, "%s", "");
        }
        uint baiduid = 0;
        uint uid = u_buf.p_cmd->uid();
        int rf = u_buf.p_cmd->rf();
        bool login = false;
        if(uid > 0){
            login = true;
        }
        if((int)strlen(baiduid_str) != BAIDUID_LEN  && uid <= 0){
            WARNING_LOG("there are not both baiduid  and uid, could not service");
            return FAIL;
        }
        int ret;
        ret = create_baiduid(baiduid_str, baiduid);
        if(ret != 0){
            WARNING_LOG("create baiduid fail");
            baiduid = 0;
        }

        NOTICE_LOG("start handle playlist cmd, ch_name[%s], baiduid[%u], uid[%u], username[%s]",
                   ch_name, baiduid, uid, username);

        Song_item_t r_song_list[MAX_USER_LIST_LEN];
        uint r_song_len = 0;

        ////获取用户的行为
        y_user_data_t user_data;
        if(login){
            mcc_get_y_user_data(uid, user_data);
        }
        else{
            mcc_get_co_y_user_data(baiduid, user_data);
        }

        ////生成百度音乐人歌曲列表
        ret = _rgen->gen_y_list(ch_name, baiduid, uid,
                                r_song_list, MAX_USER_LIST_LEN, r_song_len,
                                user_data, login, u_buf.pool, rf);
        if(ret == FAIL){
            WARNING_LOG("gen_y_list fail");
            return FAIL;
        }

        ////打包结果
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
        //写入状态
        ret = mc_pack_put_int32(mcpack, "status", 0);
        if (ret != 0){
            WARNING_LOG("put status fail[%d]", ret);
            return FAIL;
        }
        //写入频道信息
        ret = mc_pack_put_str(mcpack, "ch_name", ch_name);
        if(ret != 0){
            WARNING_LOG("put ch_name fail[%d]", ret);
            return FAIL;
        }
        //写入歌曲列表信息
        mcpack_arr = mc_pack_put_array(mcpack, "songinfos");
        if (MC_PACK_PTR_ERR(mcpack_arr)){
            WARNING_LOG("mcpack put array fail");
            return FAIL;
        }
        ret = this->_pack_song_arr(r_song_list, r_song_len, mcpack_arr);
        if(ret == FAIL){
            WARNING_LOG("pack song_list fail");
            return FAIL;
        }
        //回复结果
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

        //生成播放列表结束
        NOTICE_LOG("end handle playlist cmd, ch_name[%s], baiduid[%u], uid[%u], username[%s], status[0], list_len:%d",
                   ch_name, baiduid, uid, username, r_song_len);

        return SUCCESS;
    }


    int YPlayerHandler::handle_playaction_cmd(const User_worker_buf& u_buf){
        if (NULL == u_buf.p_thread_buf || NULL == u_buf.p_cmd){
                WARNING_LOG("p_thread_buf or clientCmd is null");
                return FAIL;
        }
        if(!u_buf.p_cmd->has_pac()){
            WARNING_LOG("unsupport cmd, should be pac");
            return FAIL;
        }
        int ret;
        const idl::playactioncmd& pac = u_buf.p_cmd->pac();
        int rf = u_buf.p_cmd->rf();
        char ch_name[MAX_CHNAME_LEN];
        snprintf(ch_name, MAX_CHNAME_LEN, "%s", pac.ch_name());
        //判断频道是否存在
        if(strncmp(ch_name, CH_Y_PRE, CH_Y_PRE_LEN) != 0){
            WARNING_LOG("channel not exit, do nothing, ch_name:%s", ch_name);
            return FAIL;
        }
        uint ch_sign = creat_sign32(ch_name);
        char sign_temp[MAX_CHNAME_LEN];
        snprintf(sign_temp, MAX_CHNAME_LEN, "%s$$%d", ch_name, rf);
        uint ca_sign = creat_sign32(sign_temp);
        char baiduid_str[MAX_BAIDUID_LEN];
        snprintf(baiduid_str, MAX_BAIDUID_LEN, "%s", u_buf.p_cmd->baiduid());
        if(NULL == baiduid_str){
            snprintf(baiduid_str, MAX_BAIDUID_LEN, "%s", "");
        }
        uint baiduid;
        ret = create_baiduid(baiduid_str, baiduid);
        int action_no = pac.action_no();
        int item_id = pac.item_id();
        //是否需要更新前端播放列表
        bool need_update = false;
        //是否需要重新生成列表
        bool need_regen = true;

        uint uid = u_buf.p_cmd->uid();
        bool is_login = false;
        if(uid > 0){
            is_login = true;
        }
        if((int)strlen(baiduid_str) != BAIDUID_LEN && uid <= 0){
            WARNING_LOG("there are not both baiduid  and uid, could not service");
            return FAIL;
        }

        //是否需要实时策略来处理
        bool need_real = true;

        NOTICE_LOG("start handle_playaction_cmd, baiduid:%u,uid:%u,action_no:%d,item_id:%u,is_login:%d, ch_name[%s]",
                   baiduid, uid, action_no, item_id, is_login, ch_name);

        y_user_data_t user_data;
        user_data.isset = false;
        uint id = is_login ? uid : baiduid;
        switch (action_no){
        case PRE_SONG:
        case COMPLETE_SONG:
        case LOVE_SONG:
        case CANCLE_LOVE_SONG:
        case CANCLE_HATE_SONG:
        case CANCLE_HATE_SINGER:
        case CANCLE_LOVE_SINGER:
            this->_handle_user_behavior(baiduid, baiduid_str, uid, item_id,
                                 action_no, ch_name,
                                 need_update, is_login,
                                 need_real, u_buf.pool, rf);
            break;
        case NEXT_SONG:
        case HATE_SONG:
            this->_handle_user_behavior(baiduid, baiduid_str,  uid, item_id,
                                    action_no, ch_name,
                                    need_update, is_login,
                                    need_real, u_buf.pool, rf);
            need_regen = this->_is_bad_need_regen(id, is_login, ch_name);
            break;
        default:
            break;
        }
        //判断是否需要重新生成
        if(!need_regen && need_real){
            //判断列表的长度
            Song_item_t p[MAX_USER_LIST_LEN];
            int len = 0;
            if(is_login){
                len = mcc_get_ch_list(id, ch_name, p, MAX_USER_LIST_LEN);
            }
            else{
                len = mcc_get_co_ch_list(id, ch_name, p, MAX_USER_LIST_LEN);
            }
            if(len <= g_config.regenerate_title_len){
                need_regen = true;
                need_update = true;
            }
        }
        //重新生成列表
        Song_item_t r_song_list[MAX_USER_LIST_LEN];
        uint r_song_len = 0;
        if(need_regen){
            //用户数据获取
            if(!user_data.isset){
                if(is_login){
                    mcc_get_y_user_data(uid, user_data);
                }
                else{
                    mcc_get_co_y_user_data(baiduid, user_data);
                }
            }
            //重建列表...
            NOTICE_LOG("regen playlist [baiduid:%u][uid:%u]", baiduid, uid);
            ////生成百度音乐人歌曲列表
            ret = _rgen->gen_y_list(ch_name, baiduid, uid,
                                    r_song_list, MAX_USER_LIST_LEN, r_song_len,
                                    user_data, is_login, u_buf.pool, rf);
            if(ret == FAIL){
                WARNING_LOG("gen_y_list fail");
                return FAIL;
            }
        }
        //返回
        Song_item_t result_list[MAX_USER_LIST_LEN];
        uint result_list_len = 0;
        if(need_update){//需要更新
            if(need_regen){
                for(uint i = 0; i < r_song_len; i++){
                    memcpy(result_list + result_list_len, r_song_list + i, sizeof(Song_item_t));
                    result_list_len++;
                }
            }
            else{
                if(is_login){
                    result_list_len = mcc_get_ch_list(id, ch_name, result_list, MAX_USER_LIST_LEN);
                }
                else{
                    result_list_len = mcc_get_co_ch_list(id, ch_name, result_list, MAX_USER_LIST_LEN);
                }
                if(result_list_len <= 0){
                    WARNING_LOG("mcc_get_ch_list fail");
                    return FAIL;
                }
            }
        }
        //打包
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
        int up = need_update == true? 1 : 0;
        ret = mc_pack_put_int32(mcpack, "up", up);
        if (ret != 0){
            WARNING_LOG("put status fail[%d]", ret);
            return FAIL;
        }
        //注入频道信息
        ret = mc_pack_put_str(mcpack, "ch_name", ch_name);
        if(ret != 0){
            WARNING_LOG("put ch_name fail[%d]", ret);
            return FAIL;
        }
        mcpack_arr = mc_pack_put_array(mcpack, "songinfos");
        if (MC_PACK_PTR_ERR(mcpack_arr)){
            WARNING_LOG("mcpack put array fail");
            return FAIL;
        }

        if(need_update){
            ret = this->_pack_song_arr(result_list, result_list_len, mcpack_arr);
            if(ret == FAIL){
                WARNING_LOG("pack song_list fail");
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
        NOTICE_LOG("finish handle_playaction_cmd, baiduid:%u,uid:%u,action_no:%d,"
                   "item_id:%u, is_login:%d, need_regen:%d, need_update:%d, ch_name[%s]",
                   baiduid, uid, action_no, item_id, is_login, need_regen, need_update, ch_name);
        return SUCCESS;
    }



    bool YPlayerHandler::_is_bad_need_regen(uint uid, bool is_login, char * ch_name){
        action_record_t record;
        int ret = -1;
        if(is_login){
            ret = mcc_get_action_record(uid, ch_name, &record);
        }
        else{
            ret = mcc_get_co_action_record(uid, ch_name, &record);
        }
        bool regen = false;
        time_t now = time((time_t*)NULL);
        if(ret == 0){
            time_t t = record.bad_min_time;
            int cnt = record.bad_action_cnt;
            if((cnt+1) >= JUMP_ANALYSIS_LEN){
                if((now - t) < JUMP_LATEST_TIME){
                    regen = true;
                    record.bad_action_cnt = 0;
                    record.bad_min_time = now;
                }
            }
            else{
                record.bad_action_cnt += 1;
            }
        }
        else{
            record.bad_action_cnt = 0;
            record.bad_min_time = now;
        }

        if(is_login){
            mcc_update_action_record(uid, ch_name, &record);
        }
        else{
            mcc_update_co_action_record(uid, ch_name, &record);
        }
        return regen;
    }



    int YPlayerHandler::_handle_user_behavior(uint baiduid, const char* baiduid_str, uint uid, uint item_id,
                                        int type,
                                        char* ch_name, bool &need_update,
                                        bool is_login,
                                        bool need_real, bsl::mempool &pool, int rf){
        if(NULL == ch_name){
            WARNING_LOG("wrong param in _heandle_next_song");
            return FAIL;
        }
#ifdef _DEBUG_TIME
        DEBUG_LOG("_handle_user_behavior,[baiduid:%d][uid:%u][item_id:%u][ch_name:%s]"
                  "[is_login:%d][need_real:%d]",baiduid, uid, item_id,
                  ch_name, is_login, need_real);
#endif
        int ret;
        //保存
        if(is_login){
            ret = mcc_add_y_user_behavior(uid, item_id, type, ch_name);
            if (ret != 0){
                WARNING_LOG("mcc_add_y_user_behavior faild[%d], type:%d;uid:%d;item_id:%d,",
                            ret, NEXT_SONG, uid, item_id);
                return FAIL;
            }
        }
        else{
            ret = mcc_add_co_y_user_behavior(baiduid, baiduid_str, item_id, type, ch_name);
            if (ret != 0){
                WARNING_LOG("mcc_add_y_user_behavior faild[%d], type:%d;baiduid:%d;item_id:%d,",
                            ret, NEXT_SONG, baiduid, item_id);
                return FAIL;
            }
        }

        Song_item_t p[MAX_USER_LIST_LEN];
        uint id = is_login ? uid : baiduid;
        int len = 0;
        if(is_login){
            len = mcc_get_ch_list(id, ch_name, p, MAX_USER_LIST_LEN);
        }
        else{
            len = mcc_get_co_ch_list(id, ch_name, p, MAX_USER_LIST_LEN);
        }
        if (len <= 0){
            WARNING_LOG("fail to mcc_get_ch_list for cache faild[%d]", ret);
            return FAIL;
        }
        //删除歌曲
        for (int i = 0; i < len; i++){
            if (p[i].song_id == item_id){
                --len;
                for (int j = i; j < len; ++j){
                    memcpy(p + j, p + j + 1, sizeof(Song_item_t));
                }
                break;
            }
        }
        if(!need_real){//不需处理实时策略，保存数据后返回
            need_update = false;
            if(is_login){
                ret = mcc_update_ch_list(id, ch_name, p, len);
            }
            else{
                ret = mcc_update_co_ch_list(id, ch_name, p, len);
            }
            if(ret != 0){
                WARNING_LOG("faild to push the user list back to cache[%d]",ret);
                return FAIL;
            }
            return SUCCESS;
        }

        if(is_login){
            ret = mcc_update_ch_list(id, ch_name, p, len);
        }
        else{
            ret = mcc_update_co_ch_list(id, ch_name, p, len);
        }
        if(ret != 0){
            WARNING_LOG("faild to push the user list back to cache[%d]",ret);
            return FAIL;
        }

        return SUCCESS;
    }


    int YPlayerHandler::_pack_song_arr(const Song_item_t* song_list, int song_len,
                                      mc_pack_t* mcpack_arr){
        if(0 == song_len){
            return SUCCESS;
        }
        if(NULL == song_list){
            return FAIL;
        }

        if (0 != MC_PACK_PTR_ERR(mcpack_arr)){
            return FAIL;
        }

        int ret = 0;
        uint value;
        mc_pack_t * mcpack_obj = NULL;
        for (int i = 0; i < song_len; i++){
            mcpack_obj = mc_pack_put_object(mcpack_arr, NULL);
            if (MC_PACK_PTR_ERR(mcpack_obj)){
                WARNING_LOG("mcpack put object fail");
                return FAIL;
            }
            ret = mc_pack_put_uint64(mcpack_obj, "songid", song_list[i].song_id);
            if (ret != 0){
                WARNING_LOG("mcpack put uint64 fail");
            }
            //注入ab test分流mark
            ret = mc_pack_put_int32(mcpack_obj, "flow_mark", g_config.flow_mark);
            if (ret != 0){
                WARNING_LOG("put flow_mark fail[%d]", ret);
                return FAIL;
            }
            ret = mc_pack_put_uint64(mcpack_obj, "method", song_list[i].source);
            if (ret != 0){
                WARNING_LOG("mcpack put uint64 fail");
            }

            ret = mc_pack_put_int32(mcpack_obj, "type", RESP_NONE_STATUS);
            if (ret != 0){
                WARNING_LOG("mcpack put int32 fail");
            }
            mc_pack_finish( mcpack_obj);
        }
        return SUCCESS;
    }

}

