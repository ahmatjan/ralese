//============================================================================
// @author      : weijingqi (weijingqi@baidu.com)
// @file        : rls_playerhandler.h
// @date        : 13 May 2012,11:27:53
// @copyright   : 2011 Baidu.com, Inc. All Rights Reserved
// @encoding    :
// @version     :
// @brief       : 处理播放请求
//============================================================================

#include "mystring.h"
#include "rls_playerhandler.h"
namespace rls{

    PlayerHandler::PlayerHandler(){
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

    PlayerHandler::~PlayerHandler(){
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

    int PlayerHandler::handle_playlist_cmd(const User_worker_buf& u_buf){
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
        char tag_word[MAX_CHNAME_LEN];
        Song_item_t r_song_list[MAX_USER_LIST_LEN];
        snprintf(ch_name, MAX_CHNAME_LEN, "%s", plc.ch_name());
        //判断频道是否存在
        if(!_dict_seeker->has_ch(ch_name)
           && strcmp(ch_name, CH_PRIVATE_NAME) != 0   //私人频道
           && strcmp(ch_name, CH_LOVESONGS_NAME) != 0 //红心频道
           && strncmp(ch_name, CH_ARTIST_PRE, CH_ARTIST_PRE_LEN) != 0 //歌手频道
           && strncmp(ch_name, CH_TAG_PRE, CH_TAG_PRE_LEN) != 0){ //标签频道
            WARNING_LOG("channel not exit, cat not server, ch_name:%s", ch_name);
            return NOEXIST;
        }
        snprintf(username, MAX_USRNAME_LEN, "%s", u_buf.p_cmd->username());
        snprintf(baiduid_str, MAX_BAIDUID_LEN, "%s", u_buf.p_cmd->baiduid());
        if(NULL == baiduid_str){
            snprintf(baiduid_str, MAX_BAIDUID_LEN, "%s", "");
        }
        uint baiduid = 0;
        uint r_song_len = 0;
        uint uid = u_buf.p_cmd->uid();
        int rf = u_buf.p_cmd->rf();
        bool login = false;
        bool is_new = false; // 是否是私人频道新用户
        if(uid > 0){
            login = true;
        }

        //是否推荐，有百度cookie或登录用户才推荐
        bool can_rec = true;
        if((int)strlen(baiduid_str) != BAIDUID_LEN  && uid <= 0){
            can_rec = false;
        }

        int ret;
        ret = create_baiduid(baiduid_str, baiduid);
        if(ret != 0){
            WARNING_LOG("create baiduid fail");
            return FAIL;
        }
        NOTICE_LOG("start handle playlist cmd, ch_name[%s], baiduid[%u], uid[%u], username[%s]",
                   ch_name, baiduid, uid, username);

        //用户的行为
        r_userdata_t user_data;
        if(login){//登录用户取登录行为
            mcc_get_user_data(*_usc_getter, uid, user_data);
        }
        else{//非登录用户取非登录行为
            mcc_get_co_user_data(baiduid, user_data);
        }

        int tmp_value;
        //私人频道特殊处理, 参数instant与即时策略频道关联
        if(can_rec && strcmp(ch_name, CH_PRIVATE_NAME) == 0){
            if(!login){
                WARNING_LOG("not login user, private channel not availble");
                return FAIL;
            }
            ret = _rgen->gen_fuse_list(ch_name, baiduid, uid,
                                            r_song_list, MAX_USER_LIST_LEN, r_song_len,
                                            user_data, false, login, u_buf.pool, rf, is_new);
            if(ret == FAIL){
                WARNING_LOG("gen_fuse_list fail");
                return FAIL;
            }
        }

        if(strcmp(ch_name, CH_PRIVATE_NAME) != 0 || is_new){
            //推荐频道列表
            if(can_rec && p_global.recommend_channel.get(ch_name, &tmp_value) == bsl :: HASH_EXIST){
                ret = _rgen->gen_recommend_list(ch_name, baiduid, uid,
                                         r_song_list, MAX_USER_LIST_LEN, r_song_len,
                                                user_data, true, login, u_buf.pool, rf);
                if(ret == FAIL){
                    WARNING_LOG("gen_recommend_colist fail");
                    return FAIL;
                }
            }
            //即时行为建模频道列表
            else if(_dict_seeker->has_ch(ch_name)){
                ret = _rgen->gen_instant_list(ch_name, baiduid, uid,
                                         r_song_list, MAX_USER_LIST_LEN, r_song_len,
                                                user_data, login, rf);
                if(ret == FAIL){
                    WARNING_LOG("gen instant list fail");
                    return FAIL;
                }
            }
            else if(is_new){
                ret = _rgen->gen_newuser_private_list(ch_name, baiduid, uid,
                                         r_song_list, MAX_USER_LIST_LEN, r_song_len,
                                                user_data, login, rf);
                if(ret == FAIL){
                    WARNING_LOG("gen newuser_private_list fail");
                    return FAIL;
                }
            }
            //红心频道列表
            else if(strcmp(ch_name, CH_LOVESONGS_NAME) == 0){//红心频道
                if(!login){
                    WARNING_LOG("not loging user, lovesongs channel not availble");
                    return FAIL;
                }
                Item_bean lovesongs[MAX_LOVESONG_LEN];
                uint len_lovesongs;
                uint total;
                ret = _usc_getter->get_prefdata(lovesongs, len_lovesongs,
                                          total, MAX_LOVESONG_LEN,
                                          MAX_LOVESONG_LEN, USC_START, uid, false, DB_SONGLOVE);
                if(ret == FAIL){
                    WARNING_LOG("get_prefdata fail");
                    return FAIL;
                }
                ret = _rgen->gen_lovesong_list(lovesongs, len_lovesongs, r_song_list,
                                               MAX_USER_LIST_LEN, r_song_len);
                if(ret == FAIL){
                    WARNING_LOG("gen lovesong list fail");
                    return FAIL;
                }
            }
            //标签频道
            else if(strncmp(ch_name, CH_TAG_PRE, CH_TAG_PRE_LEN) == 0){//标签频道
                snprintf(tag_word, MAX_CHNAME_LEN, "%s", ch_name+CH_TAG_PRE_LEN);
                ret = _rgen->gen_tag_list(r_song_list, MAX_USER_LIST_LEN, r_song_len,
                                          user_data, tag_word, _usc_getter);
                if(ret == FAIL){
                    WARNING_LOG("gen_tag_list fail");
                    return FAIL;
                }
            }
            //其他公用频道
            else{
                ret = _rgen->gen_simple_list(ch_name, r_song_list, MAX_USER_LIST_LEN, user_data, r_song_len);
                if(ret == FAIL){
                    WARNING_LOG("get_randomlist fail");
                    return FAIL;
                }
            }
        }

        //打包结果
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
        //全部实现id化
        ret = mc_pack_put_int32(mcpack, "ids", 1);
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
        char* ch_sname;
        uint ch_sign = creat_sign32(ch_name);
        if(strcmp(ch_name, CH_PRIVATE_NAME) == 0){
            ch_sname = const_cast<char*>(CH_PRIVATE_SNAME);
        }
        else if(strncmp(ch_name, CH_TAG_PRE, CH_TAG_PRE_LEN) == 0){
            ch_sname = tag_word;
        }
        else if(strcmp(ch_name, CH_LOVESONGS_NAME) == 0){
            ch_sname = const_cast<char*>(CH_LOVESONGS_SNAME);
        }
        else{
            ch_info_t *ch_info = _dict_seeker->get_ch_info(ch_sign);
            if(NULL == ch_info){
                WARNING_LOG("get ch_info fail");
                return FAIL;
            }
            ch_sname = ch_info->ch_sname;
        }
        ret = mc_pack_put_str(mcpack, "ch_sname", ch_sname);
        if(ret != 0){
            WARNING_LOG("put ch_sname fail[%d]", ret);
            return FAIL;
        }
        mcpack_arr = mc_pack_put_array(mcpack, "songinfos");
        if (MC_PACK_PTR_ERR(mcpack_arr)){
            WARNING_LOG("mcpack put array fail");
            return FAIL;
        }
        bsl::hashmap<uint, uint> songlove_ids;
        songlove_ids.create(100);
        if(!user_data.isset && login){//对登录用户，没有获取过用户行为数据，则现在获取数据
            uint len_songlove;
            uint total;
            ret = _usc_getter->get_prefdata(user_data.songlove, len_songlove, total,
                                          (uint)MAX_PREF_ITEM_NUM, (uint)MAX_PREF_ITEM_NUM, (uint)USC_START,
                                          uid, false, DB_SONGLOVE);
            if (ret != 0){
                WARNING_LOG("get_prefdata fail");
                len_songlove = 0;
            }
            user_data.len_songlove = len_songlove;
        }
        if(login){
            for(int i = 0; i < user_data.len_songlove; i++){
                songlove_ids.set(user_data.songlove[i].itemid, 0);
            }
        }
        ret = this->_pack_song_arr(r_song_list, r_song_len, mcpack_arr, songlove_ids);
        if(ret == FAIL){
            WARNING_LOG("pack song_list fail");
            songlove_ids.destroy();
            return FAIL;
        }
        songlove_ids.destroy();
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
        //i love cici =.=
        NOTICE_LOG("end handle playlist cmd, ch_name[%s], baiduid[%u], uid[%u], username[%s], status[0],list_len:%d",
                   ch_name, baiduid, uid, username, r_song_len);
        return SUCCESS;
    }


    int PlayerHandler::handle_playaction_cmd(const User_worker_buf& u_buf){
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
        if(!_dict_seeker->has_ch(ch_name) //公用频道
           && strcmp(ch_name, CH_PRIVATE_NAME) != 0 //私人频道
           && strcmp(ch_name, CH_LOVESONGS_NAME) != 0 //红心频道
           && strncmp(ch_name, CH_TAG_PRE, CH_TAG_PRE_LEN) != 0 //标签频道
           && strncmp(ch_name, CH_ARTIST_PRE, CH_ARTIST_PRE_LEN) != 0){//歌手频道
            WARNING_LOG("channel not exit, cat not server, ch_name:%s", ch_name);
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
        int item_id = 0;
        char pack_item_ids[MAX_BPR_LOG_IDS];
        if(action_no == BPR_NEXT_PAGE){
            snprintf(pack_item_ids, MAX_BPR_LOG_IDS, "%s", pac.pack_item_ids());
        }else{
            item_id = pac.item_id();
            memset(pack_item_ids, 0, sizeof(pack_item_ids));
        }
        //是否需要更新前端播放列表
        bool need_update = false;
        //是否需要重新生成列表
        bool need_regen = false;
        //是否是公用频道
        bool is_public = true;
        if(strcmp(ch_name, CH_PRIVATE_NAME) == 0){
            is_public = false;
            need_regen = true;
        }
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
        bool need_real = false;
        int tmp_value;
        //推荐策略频道实时反馈处理
        if(p_global.recommend_channel.get(ch_name, &tmp_value) == bsl :: HASH_EXIST ||
           strcmp(ch_name, CH_PRIVATE_NAME) == 0){
            need_real = true;
        }
        //公共频道(采用pcpr)，实时更新处理
        if(_dict_seeker->has_ch(ch_name)){
            need_real = true;
        }


        NOTICE_LOG("start handle_playaction_cmd, baiduid:%u,uid:%u,action_no:%d,item_id:%u,pack_item_ids:%s,is_public:%d,is_login:%d",
                   baiduid, uid, action_no, item_id, pack_item_ids, is_public, is_login);
        uint id = is_login ? uid : baiduid;
        //将用户行为发至bigpipe
        if(action_no == BPR_NEXT_PAGE){
            bigpipe_send_bpr_message(id, pack_item_ids, action_no, ch_name);
        }else{
            bigpipe_send_action_message(id, item_id, action_no, ch_name);
        }

        r_userdata_t user_data;
        user_data.isset = false;
        bool is_exist = false;
        switch (action_no){
        case PRE_SONG:
            mcc_update_behavior_cnt(baiduid, uid, is_login, item_id, baiduid_str);
            this->_handle_pre_song(baiduid, baiduid_str, uid, item_id, ch_name,
                                   need_update, is_public, is_login,
                                   need_real, u_buf.pool, rf);
            mcc_update_user_instant_behavior(id, item_id, action_no);
            break;
        case NEXT_SONG:
            ret = mcc_get_user_instant_behavior(id, item_id, is_exist);
            if(ret == 0 && is_exist){
                NOTICE_LOG("id[%d] exist a positive behavior with song_id[%d]", item_id);
                return SUCCESS;
            }
            mcc_update_behavior_cnt(baiduid, uid, is_login, item_id, baiduid_str);
            this->_handle_next_song(baiduid, baiduid_str, uid, item_id, ch_name,
                                    need_update, is_public, is_login,
                                    need_real, u_buf.pool, rf);
            need_regen = this->_is_bad_need_regen(id, is_login, ch_name);
            mcc_update_user_instant_behavior(id, item_id, action_no);
            break;
        case COMPLETE_SONG:
            mcc_update_behavior_cnt(baiduid, uid, is_login, item_id, baiduid_str);
            this->_handle_complete_song(baiduid, baiduid_str, uid, item_id, ch_name,
                                        need_update, is_public, is_login,
                                        need_real, u_buf.pool, rf);
            mcc_update_user_instant_behavior(id, item_id, action_no);
            break;
        case LOVE_SONG:
            mcc_update_behavior_cnt(baiduid, uid, is_login, item_id, baiduid_str);
            if(!user_data.isset){
                if(is_login){
                    mcc_get_user_data(*_usc_getter, uid, user_data);
                }
                else{
                    mcc_get_co_user_data(baiduid, user_data);
                }
            }
            this->_handle_love_song(baiduid, baiduid_str, uid, item_id, ch_name,
                                    need_update, is_public, is_login,
                                    need_real, u_buf.pool, user_data, rf);
            mcc_update_user_instant_behavior(id, item_id, action_no);
            break;
        case HATE_SONG:
            mcc_update_behavior_cnt(baiduid, uid, is_login, item_id, baiduid_str);
            this->_handle_hate_song(baiduid, baiduid_str,  uid, item_id, ch_name,
                                    need_update, is_public, is_login,
                                    need_real, u_buf.pool, rf);
            need_regen = this->_is_bad_need_regen(id, is_login, ch_name);
            mcc_update_user_instant_behavior(id, item_id, action_no);
            break;
        case CANCLE_LOVE_SONG:
        case CANCLE_HATE_SONG:
        case CANCLE_HATE_SINGER:
        case CANCLE_LOVE_SINGER:
            this->_handle_cancel(baiduid, baiduid_str, uid, item_id, ch_name,
                                 need_update, is_public, is_login,
                                 need_real, u_buf.pool, rf);
            break;
        case BPR_NEXT_PAGE:
            //this->_handle_bpr_next_page();
            //need_regen = this->_is_bad_need_regen(id, is_login, ch_name);
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

        //判断redis推荐是否更新，如果更新则重建
        if(strcmp(ch_name, CH_PRIVATE_NAME) == 0 || strcmp(ch_name, CH_HUAYU_NAME) == 0){
            if(_is_redis_rlist_sign_changed(id, ch_name, LDAC_REDIS_TAG, REDIS_SIGN_FIELD) || _is_redis_rlist_sign_changed(id, ch_name, BPR_REDIS_TAG, REDIS_SIGN_FIELD)){
                need_regen = true;
                need_update = true;
            }
        }

        if(need_regen){
            //用户数据获取
            if(!user_data.isset){
                if(is_login){//登录用户取登录行为
                    mcc_get_user_data(*_usc_getter, uid, user_data);
                }
                else{//非登录用户取非登录行为
                    mcc_get_co_user_data(baiduid, user_data);
                }
            }

            //重建列表...
            NOTICE_LOG("regen playlist [baiduid:%u][uid:%u]", baiduid, uid);
            int tmp_value;
            bool is_new;//是否是私人频道新用户
            //私人频道处理
            if(strcmp(ch_name, CH_PRIVATE_NAME) == 0){
                if(!is_login){
                    WARNING_LOG("not login user, private channel not availble");
                    return FAIL;
                }
                ret = _rgen->gen_fuse_list(ch_name, baiduid, uid,
                                                r_song_list, MAX_USER_LIST_LEN, r_song_len,
                                                user_data, false, is_login, u_buf.pool, rf, is_new);
                if(ret == FAIL){
                    WARNING_LOG("gen_fuse_list fail");
                    return FAIL;
                }
            }

            if(strcmp(ch_name, CH_PRIVATE_NAME) != 0 || is_new){
                //推荐频道
                if(p_global.recommend_channel.get(ch_name, &tmp_value) == bsl::HASH_EXIST){

                    ret = _rgen->gen_recommend_list(ch_name, baiduid, uid,
                                                    r_song_list, MAX_USER_LIST_LEN, r_song_len,
                                                    user_data, true, is_login, u_buf.pool, rf);
                    if(ret == FAIL){
                        WARNING_LOG("gen_recommend_list fail");
                        return FAIL;
                    }
                }
                //即时频道
                else if(_dict_seeker->has_ch(ch_name)){
                    DEBUG_LOG("begin to regenerate instant list...");
                    ret = _rgen->gen_instant_list(ch_name, baiduid, uid,
                                             r_song_list, MAX_USER_LIST_LEN, r_song_len,
                                                    user_data, is_login, rf);
                    if(ret == FAIL){
                        WARNING_LOG("gen_instant_list fail");
                        return FAIL;
                    }
                }
                else if(is_new && strcmp(ch_name, CH_PRIVATE_NAME) == 0){
                    DEBUG_LOG("begin to regenerate newuser private list...");
                    ret = _rgen->gen_newuser_private_list(ch_name, baiduid, uid,
                            r_song_list, MAX_USER_LIST_LEN, r_song_len,
                            user_data, is_login, rf);
                    if(ret == FAIL){
                        WARNING_LOG("gen newuser_private_list fail");
                        return FAIL;
                    }
                }
                //其它公共频道
                else{
                    ret = _rgen->gen_simple_list(ch_name, r_song_list, MAX_USER_LIST_LEN, user_data, r_song_len);
                    if(ret == FAIL){
                        WARNING_LOG("gen_simple_list fail");
                        return FAIL;
                    }
                }
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
        //已全部id化
        ret = mc_pack_put_int32(mcpack, "ids", 1);
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
        char* ch_sname;
        char ch_tname[MAX_CHNAME_LEN];
        if(strcmp(ch_name, CH_PRIVATE_NAME) == 0){
            ch_sname = const_cast<char*>(CH_PRIVATE_SNAME);
        }
        else if(strcmp(ch_name, CH_LOVESONGS_NAME) == 0){
            ch_sname = const_cast<char*>(CH_LOVESONGS_SNAME);
        }
        else if(strncmp(ch_name, CH_ARTIST_PRE, CH_ARTIST_PRE_LEN) == 0){
            snprintf(ch_tname, MAX_CHNAME_LEN, "%s", ch_name+CH_ARTIST_PRE_LEN);
            ch_sname = ch_tname;
        }
        else if(strncmp(ch_name, CH_TAG_PRE, CH_TAG_PRE_LEN) == 0){
            snprintf(ch_tname, MAX_CHNAME_LEN, "%s", ch_name+CH_TAG_PRE_LEN);
            ch_sname = ch_tname;
        }
        else{
            ch_info_t *ch_info = _dict_seeker->get_ch_info(ch_sign);
            if(NULL == ch_info){
                WARNING_LOG("get ch_info fail");
                return FAIL;
            }
            ch_sname = ch_info->ch_sname;
        }
        ret = mc_pack_put_str(mcpack, "ch_sname", ch_sname);
        if(ret != 0){
            WARNING_LOG("put ch_sname fail[%d]", ret);
            return FAIL;
        }
        mcpack_arr = mc_pack_put_array(mcpack, "songinfos");
        if (MC_PACK_PTR_ERR(mcpack_arr)){
            WARNING_LOG("mcpack put array fail");
            return FAIL;
        }

        if(need_update){
            bsl::hashmap<uint, uint> songlove_ids;
            songlove_ids.create(100);
            if(!user_data.isset && is_login){//对登录用户，没有获取过用户行为数据，则现在获取数据
                uint len_songlove;
                uint total;
                ret = _usc_getter->get_prefdata(user_data.songlove, len_songlove, total,
                                                (uint)MAX_PREF_ITEM_NUM, (uint)MAX_PREF_ITEM_NUM, (uint)USC_START,
                                                uid, false, DB_SONGLOVE);
                if (ret != 0){
                    WARNING_LOG("get_prefdata fail");
                    len_songlove = 0;
                }
                user_data.len_songlove = len_songlove;
            }
            if(is_login){
                for(int i = 0; i < user_data.len_songlove; i++){
                    songlove_ids.set(user_data.songlove[i].itemid, 0);
                }
            }
            ret = this->_pack_song_arr(result_list, result_list_len, mcpack_arr, songlove_ids);
            if(ret == FAIL){
                WARNING_LOG("pack song_list fail");
                songlove_ids.destroy();
                return FAIL;
            }
            songlove_ids.destroy();
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
                   "item_id:%u,pack_item_ids:%s,is_public:%d,is_login:%d,need_regen:%d,need_update:%d",
                   baiduid, uid, action_no, item_id,pack_item_ids,is_public, is_login, need_regen, need_update);
        return SUCCESS;
    }

    bool PlayerHandler::_is_redis_rlist_sign_changed(uint uid, const char *ch_name, const char *list_tag, const char *field){
        if(uid <=0 || NULL == ch_name || NULL == field || NULL == list_tag){
            WARNING_LOG("wrong params in judge redis_sign");
            return false;
        }

        int ret = -1;
        char redis_sign[MAX_REDIS_SIGN_LEN];
        uint redis_sign_len = 0;
        memset(redis_sign, 0, MAX_REDIS_SIGN_LEN);
        if(get_redis_sign(uid, ch_name, list_tag, field, redis_sign, redis_sign_len) == 0 && redis_sign_len > 0){
            char mc_sign[MAX_REDIS_SIGN_LEN];
            memset(mc_sign, 0, MAX_REDIS_SIGN_LEN);
            uint mc_sign_len = 0;

            ret = mcc_get_redis_sign(uid, ch_name, list_tag, field, mc_sign, mc_sign_len);
            if(ret == 0 && mc_sign_len > 0){
                if(atoi(mc_sign) == atoi(redis_sign)){
                    return false;
                }
            }

            ret = mcc_update_redis_sign(uid, ch_name, list_tag, field, redis_sign);
            return true;
        }

        return false;
    }

    int PlayerHandler::handle_csreq_cmd(const User_worker_buf& u_buf){
        if (NULL == u_buf.p_thread_buf || NULL == u_buf.p_cmd){
                WARNING_LOG("p_thread_buf or clientCmd is null");
                return FAIL;
        }
        if(!u_buf.p_cmd->has_crc()){
            WARNING_LOG("unsupport cmd, should be crc");
            return FAIL;
        }
        int ret;
        const idl::coldstartreqcmd& crc = u_buf.p_cmd->crc();
        int rf = u_buf.p_cmd->rf();
        char ch_name[MAX_CHNAME_LEN];
        snprintf(ch_name, MAX_CHNAME_LEN, "%s", crc.ch_name());
        char baiduid_str[MAX_BAIDUID_LEN];
        snprintf(baiduid_str, MAX_BAIDUID_LEN, "%s", u_buf.p_cmd->baiduid());
        if(NULL == baiduid_str){
            snprintf(baiduid_str, MAX_BAIDUID_LEN, "%s", "");
        }
        uint baiduid;
        ret = create_baiduid(baiduid_str, baiduid);
        uint uid = u_buf.p_cmd->uid();
        if((int)strlen(baiduid_str) != BAIDUID_LEN && uid <= 0){
            WARNING_LOG("there are not both baiduid  and uid, could not service");
            return FAIL;
        }
        NOTICE_LOG("start handle_csreq_cmd, baiduid:%u,uid:%u", baiduid, uid);
        //分割字符串
        char lovesinger_str[1024];
        snprintf(lovesinger_str, 1024, "%s", crc.lovesinger());
        //存储数据
        if(strlen(lovesinger_str) > 0){
            std::vector<std::string> segs;
            segs.reserve(10);
            cmm::str_split(lovesinger_str, ",", segs);
            uint64_t singer_id = 0;
            uint64_t q_sid = 0;
            for(int i = 0; i < segs.size(); i++){
                singer_id = atoi(segs[i].c_str());
                if(singer_id == 0){
                    WARNING_LOG("wrong singerid, singerid[%s]", segs[i].c_str());
                    continue;
                }
                ret = p_global.quku_ting_artistid.get(singer_id, &q_sid);
                if(ret == bsl::HASH_NOEXIST){
                    WARNING_LOG("not exist quku artist id, ting id[%d]", singer_id);
                    continue;
                }
                if(uid > 0){
                    /*ret = _usc_getter->add_prefdata(q_sid, uid, DB_SINGERLOVE);
                    if(ret != 0){
                        WARNING_LOG("add_prefdata fail[%d]", ret);
                    }*/
                }
                else if(baiduid > 0){
                    ret = mcc_update_co_pref_data(baiduid, baiduid_str, q_sid, DB_SINGERLOVE, DB_VALID, ch_name);
                    if (ret != 0){
                        WARNING_LOG("addup_co_prefdata faild[%d]", ret);
                    }
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
        //回复
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
        NOTICE_LOG("finish handle_csreq_cmd, baiduid:%u,uid:%u",
                   baiduid, uid);
        return SUCCESS;
    }


    bool PlayerHandler::_is_bad_need_regen(uint uid, bool is_login, char * ch_name){
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

    int PlayerHandler::_handle_pre_song(uint baiduid, const char* baiduid_str, uint uid, uint item_id,
                                        char* ch_name, bool &need_update,
                                        bool is_public, bool is_login,
                                        bool need_real, bsl::mempool &pool, int rf){
        if(NULL == ch_name){
            WARNING_LOG("wrong param in _handle_pre_song");
            return FAIL;
        }
        int ret;
#ifdef _DEBUG_TIME
        DEBUG_LOG("_handle_pre_song, [baiduid:%u][uid:%u][itemid:%u]"
                  "[ch_name:%s][is_public:%d][is_login:%d][need_real:%d]",
                  baiduid, uid, item_id, ch_name, is_public,
                  is_login, need_real);
#endif
        if(is_login){//登录用户
            ret = mcc_add_user_real_behavior(uid, item_id, PRE_SONG, ch_name);
            if(ret != 0){
                WARNING_LOG("addBehavior fail");
                return FAIL;
            }
        }
        else{
            ret = mcc_add_co_user_real_behavior(baiduid, baiduid_str, item_id, PRE_SONG, ch_name);
            if(ret != 0){
                WARNING_LOG("mcc_add_co_user_real_behavior fail");
                return FAIL;
            }
        }
        need_update = false;
        if(!need_real){//不需处理实时策略，保存数据后返回
            need_update = false;
            return SUCCESS;
        }
        //继续实时处理5、
        need_update = false;
        return SUCCESS;
    }

    int PlayerHandler::_handle_next_song(uint baiduid, const char* baiduid_str, uint uid, uint item_id,
                                        char* ch_name, bool &need_update,
                                        bool is_public, bool is_login,
                                         bool need_real, bsl::mempool &pool, int rf){
        if(NULL == ch_name){
            WARNING_LOG("wrong param in _heandle_next_song");
            return FAIL;
        }
#ifdef _DEBUG_TIME
        DEBUG_LOG("_handle_next_song,[baiduid:%d][uid:%u][item_id:%u][ch_name:%s]"
                  "[is_public:%d][is_login:%d][need_real:%d]",baiduid, uid, item_id,
                  ch_name, is_public, is_login, need_real);
#endif
        int ret;
        //保存
        if(is_login){
            ret = mcc_add_user_real_behavior(uid, item_id, NEXT_SONG, ch_name);
            if (ret != 0){
                WARNING_LOG("mcc_add_user_real_behavior faild[%d], type:%d;uid:%d;item_id:%d,",
                            ret, NEXT_SONG, uid, item_id);
                return FAIL;
            }
        }
        else{
            ret = mcc_add_co_user_real_behavior(baiduid, baiduid_str, item_id, NEXT_SONG, ch_name);
            if (ret != 0){
                WARNING_LOG("mcc_add_co_user_real_behavior faild[%d], type:%d;baiduid:%d;item_id:%d,",
                            ret, NEXT_SONG, baiduid, item_id);
                return FAIL;
            }
        }
        char sign_temp[MAX_CHNAME_LEN];
        snprintf(sign_temp, MAX_CHNAME_LEN, "%s$$%d", ch_name, rf);
        uint ch_sign = creat_sign32(ch_name);
        uint ca_sign = creat_sign32(sign_temp);
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

        //跳过歌手歌曲、相关歌曲删除
        Song_item_t tmp_list[MAX_USER_LIST_LEN];
        int tmp_list_len = 0;
        //相关歌曲数据
        Song_item_t *songlist = NULL;
        int songlist_len = 0;
        ret = _dict_seeker->seek_public_song_song(item_id, ch_sign, &songlist, songlist_len);
        if (0 != ret){
            WARNING_LOG("seek relation song for song[%u] faild[%d]", item_id, ret);
            songlist_len = 0;
            songlist = NULL;
        }

        //歌手数据
        uint singer_id = _dict_seeker->get_singer_id(item_id);
        DEBUG_LOG("rsinger singer_id[%u]", singer_id);
        int i = 0;
        for(; i < g_config.pass_deletesong_len && i < len; i++){
            //跳过歌手的歌曲,删除
            if(_dict_seeker->get_singer_id(p[i].song_id) == singer_id){
#ifdef _DEBUG_TIME
                DEBUG_LOG("delete same singer song,[i:%d][songid:%u][singerid:%u]", i, p[i].song_id, singer_id);
#endif
                continue;
            }
			//跳过歌曲相关的歌曲,删除
			bool flag = false;
            for (int j = 0; j < g_config.pass_deweigth_len && j < songlist_len; ++j){
                if (p[i].song_id == songlist[j].song_id){
#ifdef _DEBUG_TIME
                    DEBUG_LOG("delete relation song,[j:%d][songid:%u][weight:%d]", i,  p[i].song_id, p[i].weight);
#endif
					flag = true;
					break;
                }
			}
			if(flag){
#ifdef _DEBUG_TIME
				DEBUG_LOG("delete relation song,[i:%d][songid:%u][weight:%d]", i,  p[i].song_id, p[i].weight);
#endif
				continue;
			}
            memcpy(tmp_list + tmp_list_len, p + i, sizeof(Song_item_t));
            tmp_list_len++;
        }
        //剩下的拷贝
        for(; i < len; i++){
            memcpy(tmp_list + tmp_list_len, p + i, sizeof(Song_item_t));
            tmp_list_len++;
        }
        if(is_login){
            ret = mcc_update_ch_list(id, ch_name, tmp_list, tmp_list_len);
        }
        else{
            ret = mcc_update_co_ch_list(id, ch_name, tmp_list, tmp_list_len);
        }
        if(ret != 0){
            WARNING_LOG("faild to push the user list back to cache[%d]",ret);
            return FAIL;
        }
        need_update = true;
        return SUCCESS;
    }

    int PlayerHandler::_handle_complete_song(uint baiduid, const char* baiduid_str, uint uid, uint item_id,
                                        char* ch_name, bool &need_update,
                                        bool is_public, bool is_login,
                                             bool need_real, bsl::mempool &pool, int rf){
        if(NULL == ch_name){
            WARNING_LOG("wrong param in _heandle_complete_song");
            return FAIL;
        }
        need_update = false;
        int ret;
        if(is_login){
            ret = mcc_add_listen_history(uid, item_id, ch_name);
            if (ret != 0){
                WARNING_LOG("mcc_add_listen_history faild[%d]", ret);
                return FAIL;
            }
        }
        else{
            ret = mcc_add_co_listen_history(baiduid, baiduid_str, item_id, ch_name);
            if (ret != 0){
                WARNING_LOG("mcc_add_co_listen_history faild[%d]", ret);
                return FAIL;
            }
        }
        Song_item_t p[MAX_USER_LIST_LEN];
        char sign_temp[MAX_CHNAME_LEN];
        snprintf(sign_temp, MAX_CHNAME_LEN, "%s$$%d", ch_name, rf);
        uint ca_sign = creat_sign32(sign_temp);
        uint id = is_login ? uid : baiduid;
        int len = 0;
        if(is_login){
            len = mcc_get_ch_list(id, ch_name, p, MAX_USER_LIST_LEN);
        }
        else{
            len = mcc_get_co_ch_list(id, ch_name, p, MAX_USER_LIST_LEN);
        }
		if (len <= 0){
            WARNING_LOG("fail get song_list from cache faild[%d]", ret);
            return FAIL;
        }
        if(!need_real){//不需要实时处理
            for (int i = 0; i < len; i++){
                if (p[i].song_id == item_id){
                    --len;
                    for (int j = i; j < len; ++j){
                        memcpy(p + j, p + j + 1, sizeof(Song_item_t));
                    }
                    break;
                }
            }
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
        //继续实时处理
        for (int i = 0; i < len; i++){
            if (p[i].song_id == item_id){
                --len;
                for (int j = i; j < len; ++j){
                    memcpy(p + j, p + j + 1, sizeof(Song_item_t));
                }
                break;
            }
        }
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

    int PlayerHandler::_handle_love_song(uint baiduid, const char* baiduid_str, uint uid, uint item_id,
                                         char* ch_name, bool &need_update,
                                         bool is_public, bool is_login,
                                         bool need_real, bsl::mempool &pool,
                                         const r_userdata_t &user_data, int rf){
        if(NULL == ch_name){
            WARNING_LOG("wrong param in _heandle_love_song");
            return FAIL;
        }
        int ret;
#ifdef _DEBUG_TIME
        DEBUG_LOG("_handle_love_song,[baiduid:%u][uid:%u][itemid:%u][ch_name:%s]"
                  "[is_public:%d][is_login:%d][need_real:%d]",
                  baiduid, uid, item_id, ch_name, is_public,
                  is_login, need_real);
#endif
        if(!is_login){
            ret = mcc_update_co_pref_data(baiduid, baiduid_str, item_id, DB_SONGLOVE, DB_VALID, ch_name);
            if (ret != 0){
                WARNING_LOG("mcc_update_co_pref_data faild[%d]", ret);
            }
        }
        else{
            ret = mcc_update_pref_data(uid, DB_SONGLOVE, ch_name);
            if (ret != 0){
                WARNING_LOG("mcc_update_pref_data faild[%d]", ret);
            }
        }
        Song_item_t p[MAX_USER_LIST_LEN];
        char sign_temp[MAX_CHNAME_LEN];
        snprintf(sign_temp, MAX_CHNAME_LEN, "%s$$%d", ch_name, rf);
        uint ch_sign = creat_sign32(ch_name);
        uint ca_sign = creat_sign32(sign_temp);
        uint id = is_login ? uid : baiduid;
        int len = 0;
        if(is_login){
            len = mcc_get_ch_list(id, ch_name, p, MAX_USER_LIST_LEN);
        }
        else{
            len = mcc_get_co_ch_list(id, ch_name, p, MAX_USER_LIST_LEN);
        }
        if (len <= 0){
            WARNING_LOG("fail to remove the complete song for cache faild[%d], chname[%s]", ret, ch_name);
            return FAIL;
        }
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
        //剩余列表不足,直接FAIL返回
        if(len < 2){
            WARNING_LOG("the left lenght in cache is not enough, [len:%u]", len);
            return FAIL;
        }
        //设置过滤歌曲
        sodict_build_t* filter_dict = odb_creat(FILT_DICT_HASH);
        if (!filter_dict){
            WARNING_LOG("creat odict faild");
            return -1;
        }
        _dict_seeker->fill_filter_dict(user_data, filter_dict);
        //加心生，应用插入策略，在第二和第四首歌处，插入相关歌曲
        Song_item_t new_list[MAX_USER_LIST_LEN];
        int new_list_len = 0;
        uint value;
        Song_item_t* p_rand_res[2];
        bzero(p_rand_res, sizeof(Song_item_t) * 2);

        bsl::hashmap<uint, uint> idset;
        idset.create(MAX_USER_LIST_LEN);

        //插入歌曲
        Song_item_t *p_song_song = NULL;
        int song_song_len = 0;
        Song_item_t *p_singer_song = NULL;
        int singer_song_len = 0;
        uint singer_id;
        //歌曲相关歌曲
        ret = _dict_seeker->seek_public_song_song(item_id, ch_sign, &p_song_song, song_song_len);
        if(ret != 0){
            WARNING_LOG("seek song song faild");
            p_song_song = NULL;
            song_song_len = 0;
        }
        //歌手的相关歌曲
        singer_id = _dict_seeker->get_singer_id(item_id);
        ret = _dict_seeker->seek_public_singer_song(singer_id, ch_sign, &p_singer_song, singer_song_len);
		if(ret != 0){
            WARNING_LOG("seek_public_singer_song fail");
        }
        else{
            p_rand_res[0] = _ral->song_topN_rand(p_singer_song, singer_song_len, pool, filter_dict);
        }
        //歌曲的相关歌曲
        p_rand_res[1] = _ral->song_topN_rand(p_song_song, song_song_len, pool, filter_dict);
        //第一首歌
        if (len >= 1){
            memcpy(new_list + new_list_len, p, sizeof(Song_item_t));
            idset.set(new_list[new_list_len].song_id, 0);
        }
        new_list_len++;
        //第二首歌
        if(NULL != p_rand_res[0]){
            if(idset.get(p_rand_res[0]->song_id, &value) == bsl::HASH_NOEXIST){
                memcpy(new_list + new_list_len, p_rand_res[0], sizeof(Song_item_t));
                new_list[new_list_len].weight = MAX_WEIGHT;
                idset.set(new_list[new_list_len].song_id, 0);
                new_list_len++;
            }
        }
        //第三首歌
        if((len >= 2) && (idset.get(p[1].song_id, &value) == bsl::HASH_NOEXIST)){
            memcpy(new_list + new_list_len, p + 1, sizeof(Song_item_t));
            idset.set(new_list[new_list_len].song_id, 0);
            new_list_len++;
        }
        //第四首歌
        if(NULL != p_rand_res[1]){
            if(idset.get(p_rand_res[1]->song_id, &value) == bsl::HASH_NOEXIST){
                memcpy(new_list + new_list_len, p_rand_res[1], sizeof(Song_item_t));
                new_list[new_list_len].weight = MAX_WEIGHT;
                idset.set(new_list[new_list_len].song_id, 0);
                new_list_len++;
            }
        }
        //拷贝剩余数据
        for(int i = 2; i < len && new_list_len < MAX_USER_LIST_LEN; i++){
            if(idset.get(p[i].song_id, &value) == bsl::HASH_NOEXIST){
                memcpy(new_list + new_list_len, p + i, sizeof(Song_item_t));
                idset.set(new_list[new_list_len].song_id, 0);
                new_list_len++;
            }
        }

        if(is_login){
            ret = mcc_update_ch_list(id, ch_name, new_list, new_list_len);
        }
        else{
            ret = mcc_update_co_ch_list(id, ch_name, new_list, new_list_len);
        }
        if(ret != 0){
            WARNING_LOG("faild to push the user list back to cache[%d]",ret);
            goto ERROR;
        }
        //需要更新列表
        need_update = true;
        if(filter_dict){
            odb_destroy(filter_dict);
        }
        idset.destroy();
        return SUCCESS;
    ERROR:
        if(filter_dict){
            odb_destroy(filter_dict);
        }
        idset.destroy();
        return FAIL;
    }

    int PlayerHandler::_handle_hate_song(uint baiduid, const char* baiduid_str, uint uid, uint item_id,
                                         char* ch_name, bool &need_update,
                                         bool is_public, bool is_login,
                                         bool need_real, bsl::mempool &pool, int rf){
        if(NULL == ch_name){
            WARNING_LOG("wrong param in _heandle_complete_song");
            return FAIL;
        }
#ifdef _DEBUG_TIME
        DEBUG_LOG("_handle_hate_song,[baiduid:%u][uid:%u][itemid:%d]"
                  "[ch_name:%s][is_public:%d][is_login:%d]",
                  baiduid, uid, item_id, ch_name, is_public,
                  is_login);
#endif
        int ret;
        uint id = is_login ? uid : baiduid;
        //保存
        if(!is_login){
            ret = mcc_update_co_pref_data(baiduid, baiduid_str, item_id, DB_SONGHATE, DB_VALID, ch_name);
            if (ret != 0){
                WARNING_LOG("mcc_update_co_pref_data faild[%d]", ret);
            }
        }
        else{
            ret = mcc_update_pref_data(uid, DB_SONGHATE, ch_name);
            if (ret != 0){
                WARNING_LOG("mcc_update_pref_data faild[%d]", ret);
            }
        }
        char sign_temp[MAX_CHNAME_LEN];
        snprintf(sign_temp, MAX_CHNAME_LEN, "%s$$%d", ch_name, rf);
        uint ch_sign = creat_sign32(ch_name);
        uint ca_sign = creat_sign32(sign_temp);
        Song_item_t p[MAX_USER_LIST_LEN];
        int len = 0;
        if(is_login){
            len = mcc_get_ch_list(id, ch_name, p, MAX_USER_LIST_LEN);
        }
        else{
            len = mcc_get_co_ch_list(id, ch_name, p, MAX_USER_LIST_LEN);
        }
        if (len <= 0){
            WARNING_LOG("fail to get ch rlist song for cache faild[%d]", ret);
            return FAIL;
        }
        //删除歌曲
        for (int i = 0; i < len; i++){
            if (p[i].song_id == item_id){
#ifdef _DEBUG_TIME
                DEBUG_LOG("delete song, [i:%d][songid:%u]", i, item_id);
#endif
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

        //歌手歌曲、相关歌曲删除
        Song_item_t tmp_list[MAX_USER_LIST_LEN];
        int tmp_list_len = 0;
        //相关歌曲数据
        Song_item_t *songlist = NULL;
        int songlist_len = 0;
        ret = _dict_seeker->seek_public_song_song(item_id, ch_sign, &songlist, songlist_len);
        if (0 != ret){
            WARNING_LOG("seek relation song for song[%u] faild[%d]", item_id, ret);
            songlist_len = 0;
            songlist = NULL;
        }
        //歌手数据
        uint singer_id = _dict_seeker->get_singer_id(item_id);
        int i = 0;
        for(; i < g_config.pass_deletesong_len && i < len; i++){
            //歌手的歌曲,删除
            if(_dict_seeker->get_singer_id(p[i].song_id) == singer_id){
#ifdef _DEBUG_TIME
                DEBUG_LOG("delete same singer song,[i:%d][songid:%u][singerid:%u]", i, p[i].song_id, singer_id);
#endif
                continue;
            }
            //歌曲相关的歌曲,删除
			bool flag = false;
			for (int j = 0; j < g_config.pass_deweigth_len && j < songlist_len; ++j){
                if (p[i].song_id == songlist[j].song_id){
#ifdef _DEBUG_TIME
                    DEBUG_LOG("delete relation song,[songid:%u][j:%d][weight:%d]",p[i].song_id,j,p[i].weight);
#endif
					flag = true;
					break;
                }
			}
			if(flag){
#ifdef _DEBUG_TIME
				DEBUG_LOG("delete relation song,[i:%d][songid:%u][weight:%d]", i,  p[i].song_id, p[i].weight);
#endif
				continue;
			}
            memcpy(tmp_list + tmp_list_len, p + i, sizeof(Song_item_t));
            tmp_list_len++;
        }
        //剩下的拷贝
        for(; i < len; i++){
            memcpy(tmp_list + tmp_list_len, p + i, sizeof(Song_item_t));
            tmp_list_len++;
        }
        if(is_login){
            ret = mcc_update_ch_list(id, ch_name, tmp_list, tmp_list_len);
        }
        else{
            ret = mcc_update_co_ch_list(id, ch_name, tmp_list, tmp_list_len);
        }
        if(ret != 0){
            WARNING_LOG("faild to push the user list back to cache[%d]",ret);
            return FAIL;
        }
        need_update = true;
        return SUCCESS;
    }

    int PlayerHandler::_handle_cancel(uint baiduid, const char* baiduid_str, uint uid, uint item_id,
                                      char* ch_name, bool &need_update,
                                      bool is_public, bool is_login,
                                      bool need_real, bsl::mempool &pool, int rf){
        if(NULL == ch_name){
            WARNING_LOG("wrong param in _heandle_cancel");
            return FAIL;
        }
        need_update = false;
        int ret;
        //保存
        if(!is_login){
            //喜欢类型可随便填写,会影响cache的更新情况, no care
            ret = mcc_update_co_pref_data(baiduid, baiduid_str, item_id, DB_SONGHATE, DB_DELETE, ch_name);
            if (ret != 0){
                WARNING_LOG("mcc_update_co_pref_data faild[%d]", ret);
            }
        }
        else{
            ret = mcc_update_pref_data(uid, DB_SONGLOVE, ch_name);
            if (ret != 0){
                WARNING_LOG("mcc_update_pref_data faild[%d]", ret);
            }
        }
        if(!need_real){//不需要实时处理
            return SUCCESS;
        }
        //继续进行实时处理
        return SUCCESS;
    }

    int PlayerHandler::_pack_song_arr(const Song_item_t* song_list, int song_len,
                                      mc_pack_t* mcpack_arr, const bsl::hashmap<uint, uint> songlove_ids){
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
            if(songlove_ids.get(song_list[i].song_id, &value) == bsl::HASH_EXIST){
                ret = mc_pack_put_int32(mcpack_obj, "type", RESP_SONGLOVE_STATUS);
            }
            else{
                ret = mc_pack_put_int32(mcpack_obj, "type", RESP_NONE_STATUS);
            }
            if (ret != 0){
                WARNING_LOG("mcpack put int32 fail");
            }
            mc_pack_finish( mcpack_obj);
        }

        return SUCCESS;
    }

    int PlayerHandler::bigpipe_send_action_message(uint uid, uint song_id, int type, const char* ch_name){
        if(uid <= 0){
            return FAIL;
        }

        time_t now = time((time_t*)NULL);
        char newmsg[200];
        snprintf(newmsg, 200, "%u|%u|%d|%s|%d", uid, song_id, type, ch_name, now);

        MESSAGE_LOG(BIGPIPE_LDAC_TAG, newmsg);
        return SUCCESS;
    }

    int PlayerHandler::bigpipe_send_bpr_message(uint uid, const char *pack_item_ids, int type, const char* ch_name){
        if(uid <= 0){
            return FAIL;
        }

        time_t now = time((time_t*)NULL);
        char newmsg[200];
        snprintf(newmsg, 200, "%u|%s|%d|%s|%d", uid, pack_item_ids, type, ch_name, now);

        BPR_LOG(BIGPIPE_BPR_TAG, newmsg);
        return SUCCESS;
    }

}

