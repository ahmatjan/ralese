/**
 * =====================================================================================
 *
 *  Filename: rls_instant.cpp
 *
 *  Description: 即时用户模型
 *
 *  Version: 1.0
 *  Created:2012-10-29
 *  Revision: none
 *  Compiler: gcc
 *
 *  Author: wensaiping@baidu.com
 *  Company: baidu.com Inc.
 *  
 * =====================================================================================
 */

#include "rls_instant.h"
#include "common.h"
#include <algorithm>
#include "bsl/map.h"


/**
 * 建立用户模型
 * instant_model， 即时用户模型
 * i_user_data, 即时用户数据
 * ch_name 频道名
 * return 1为建模成功 其它失败
 */
int build_instant_model(instant_model_t& instant_model, i_userdata_t i_user_data, const char * ch_name){
	//清空内存,置初值为0
	memset(&instant_model, 0, sizeof(instant_model_t));
	instant_init init_value;  
	if(p_global.detect_channel.get(ch_name, &init_value) == bsl::HASH_NOEXIST){
		WARNING_LOG("the channel is error in detect_channel[%s]", ch_name);
		return FAIL;
	}
	//建模维度
	instant_model.dim_type = init_value.dim_type;
	//试探维度
	instant_model.dim_det = init_value.dim_det;
	//建模初始化
	instant_model.dim_len = DIM_LEN;    
	instant_model.dim_lan_len = DIM_LAN_NUM;
	instant_model.dim_year_len = DIM_YEAR_NUM;
	instant_model.dim_area_len = DIM_AREA_NUM;
	instant_model.dim_gender_len = DIM_GENDER_NUM;
	if(i_user_data.len_listenhistory <= 0){
		instant_model.is_new = true;
		instant_model.dim_lan[HUAYU_LAN] = HUAYU_INIT;
	}
	else{
		instant_model.is_new = false;
	}

	//喜欢歌曲
	for(int i = 0; i < i_user_data.len_songlove; i++){
		per_instant_songid(instant_model, i_user_data.songlove[i].itemid, g_config.IWConf.fm_behavior_love, g_config.IWConf.general_rate);
	}
	//不喜欢歌曲
	for(int i = 0; i < i_user_data.len_songhate; i++){
		per_instant_songid(instant_model, i_user_data.songhate[i].itemid, g_config.IWConf.fm_behavior_hate, g_config.IWConf.general_rate);
	}
	//试听历史
	for(int i = 0; i < i_user_data.len_listenhistory; i++){
		per_instant_songid(instant_model, i_user_data.listenhistory[i].itemid, g_config.IWConf.fm_listen_60, g_config.IWConf.general_rate);
	}
	//behavior
	for(int i = 0; i < i_user_data.len_action; i++){
		if(i_user_data.action[i].type == DB_PRE_SONG){
			per_instant_songid(instant_model, i_user_data.action[i].itemid, g_config.IWConf.fm_behavior_pre, g_config.IWConf.general_rate);
		}
		if(i_user_data.action[i].type == DB_NEXT_SONG){
			per_instant_songid(instant_model, i_user_data.action[i].itemid, g_config.IWConf.fm_behavior_next, g_config.IWConf.general_rate);
		}
	}
	return 1;
}

/**
 * 单首歌曲计算即时用户权值
 * instant_model， 即时用户模型
 * songid, 歌曲id
 * type 歌曲处理类型（加心，60s等）
 * rate 不同行为的倍率
 * dim_type 建模维度度
 * return >=0 成功 -1失败
 */
int per_instant_songid(instant_model_t& instant_model, int song_id, int type, int rate){
	int dim_type = instant_model.dim_type;   
	const Song_brief_t* p_brief = get_song_brief(song_id);
	if(NULL == p_brief){
		WARNING_LOG("no song brief, songid[%d]", song_id);
		return -1;
	}
	int tmp = 0;
	//语言
	if((dim_type & (1 << I_LAN_DIM)) != 0){
		if(p_global.i_brief_lan.get(p_brief->lang, &tmp) == bsl::HASH_EXIST){
			if(tmp == HUAYU_LAN){
				if(type > 0){
					instant_model.dim_lan[tmp] += HUAYU_RATE * type * rate;
				}
				else{
					instant_model.dim_lan[tmp] += (type * rate)/HUAYU_RATE;
				}
			}else{
				instant_model.dim_lan[tmp] += type * rate;
			}
		}
	}
	//年代
	if((dim_type & (1 << I_YEAR_DIM)) != 0){
		if(p_global.i_brief_year.get(p_brief->year, &tmp) == bsl::HASH_EXIST){
			instant_model.dim_year[tmp] += type * rate;
		}
	}
	//地区
	if((dim_type & (1 << I_AREA_DIM)) != 0){
		if(p_global.i_brief_area.get(p_brief->area, &tmp) == bsl::HASH_EXIST){
			instant_model.dim_area[tmp] += type * rate;
		}
	}
	//性别
	if((dim_type & (1 << I_GENDER_DIM)) != 0){
		if(p_global.i_brief_gender.get(p_brief->gender, &tmp) == bsl::HASH_EXIST){
			instant_model.dim_gender[tmp] += type * rate;
		}
	}
	return SUCCESS;
}

/**
 * 单首歌曲计算即时用户权值
 * instant_model， 即时用户模型
 * songid, 歌曲id
 * type 歌曲处理类型（加心，60s等）
 * dim 为试探的维度
 * return >=0 成功 -1失败
 */
int detect_instant_songid(instant_model_t& instant_model, int song_id, int type, int dim){
	int dim_type = instant_model.dim_type;   
	const Song_brief_t* p_brief = get_song_brief(song_id);
	if(NULL == p_brief){
		WARNING_LOG("detect song, no song brief, songid[%d]", song_id);
		return FAIL;
	}
	int tmp = 0;
	//语言
	if((dim_type & (1 << I_LAN_DIM)) != 0){
		if(p_global.i_brief_lan.get(p_brief->lang, &tmp) == bsl::HASH_EXIST){
			if(tmp == HUAYU_LAN){
				if(type > 0){
					instant_model.dim_lan[tmp] += HUAYU_RATE * type * g_config.IWConf.detect_rate;
				}
				else{
					instant_model.dim_lan[tmp] += (type * g_config.IWConf.detect_rate)/HUAYU_RATE;
				}
			}else{
				instant_model.dim_lan[tmp] += type * g_config.IWConf.detect_rate;
			}
		}
	}
	//语言
	if((dim_type & (1 << I_LAN_DIM)) != 0 && dim == I_LAN_DIM){
		if(p_global.i_brief_lan.get(p_brief->lang, &tmp) == bsl::HASH_EXIST){
			if(tmp == HUAYU_LAN){
				if(type > 0){
					instant_model.dim_lan[tmp] += HUAYU_RATE * type * g_config.IWConf.detect_rate;
				}
				else{
					instant_model.dim_lan[tmp] += (type * g_config.IWConf.detect_rate)/HUAYU_RATE;
				}
			}else{
				instant_model.dim_lan[tmp] += type * g_config.IWConf.detect_rate;
			}
		}
	}
	//年代
	if((dim_type & (1 << I_YEAR_DIM)) != 0  && dim == I_YEAR_DIM ){
		if(p_global.i_brief_year.get(p_brief->year, &tmp) == bsl::HASH_EXIST){
			instant_model.dim_year[tmp] += type * g_config.IWConf.detect_rate;
		}
	}
	
	//地区
	if((dim_type & (1 << I_AREA_DIM)) != 0 && dim == I_AREA_DIM ){
		if(p_global.i_brief_area.get(p_brief->area, &tmp) == bsl::HASH_EXIST){
			instant_model.dim_area[tmp] += type * g_config.IWConf.detect_rate;
		}
	}
	//性别
	if((dim_type & (1 << I_GENDER_DIM)) != 0 && dim == I_GENDER_DIM){
		if(p_global.i_brief_gender.get(p_brief->gender, &tmp) == bsl::HASH_EXIST){
			instant_model.dim_gender[tmp] += type * g_config.IWConf.detect_rate;
		}
	}
	return SUCCESS;
}
