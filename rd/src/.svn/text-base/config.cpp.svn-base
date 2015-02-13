/**
 * =====================================================================================
 *
 *	Filename:  config.cpp
 *
 *	Description:  header file for config.cpp
 *
 *	Version:  1.0
 *  Created: 2010-11-23
 *	Revision:  none
 *	Compiler:  gcc
 *
 *	Author:  zhangjunying, zhangjunying@baidu.com
 *	Company:  baidu.com Inc.
 *
 * =====================================================================================
 */

/**
 * @file   config.cpp
 * @brief  config related
 * @author denglu
 * @version 1.0.0
 **/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "config.h"

/**
 * config constructor
 *
 */
config_t::config_t() {
	ul_strlcpy (configfile, "./conf/rls.conf", sizeof(configfile));
}

/**
 * config deconstructor
 *
 */
config_t::~config_t() {
}

/**
 * global config
 */
config_t g_config;

/**
 * c_des list. used to load config file
 * @arg1 : the mark
 * @arg2 : the type
 * @arg3 : the addr
 * @arg4 : whether necessary
 * @arg5 : the default value
 * @arg6 : the capability to fill
 */
c_descript_t
		g_c_descripts[] =
		{
				{ "fuse_rate", cdp_eInt, &(g_config.fuse_rate), 0, 0, 1000 },
				{ "original_weight", cdp_eInt, &(g_config.original_weight), 0, 0, 1 },
				{ "user_cf_weight", cdp_eInt, &(g_config.user_cf_weight), 0, 0, 1 },
				{ "item_cf_weight", cdp_eInt, &(g_config.item_cf_weight), 0, 0, 1 },
				{ "um_weight", cdp_eInt, &(g_config.um_weight), 0, 0, 1 },
				{ "uc_weight", cdp_eInt, &(g_config.uc_weight), 0, 0, 1 },
				{ "um_change_weight", cdp_eInt, &(g_config.um_change_weight), 0, 0, 10},
				{ "dbconfig", cdp_eStr, (g_config.dbconfig), cdp_Required,
						"db.conf", MAX_DIR_LEN },
				{ "dbconfigpath", cdp_eStr, (g_config.dbconfigpath),
						cdp_Required, "./conf", MAX_DIR_LEN },
				{ "comlog_conf_file", cdp_eStr, (g_config.comlog_conf_file),
						cdp_Required, "comlog.conf", MAX_DIR_LEN },
				{ "comlog_conf_path", cdp_eStr, (g_config.comlog_conf_path),
						cdp_Required, "./conf", MAX_DIR_LEN },
				{ "ub_client_conf_file", cdp_eStr, (g_config.ub_client_conf_file),
						cdp_Required, "ub_client.conf", MAX_DIR_LEN },
				{ "ub_client_conf_path", cdp_eStr, (g_config.ub_client_conf_path),
						cdp_Required, "./conf", MAX_DIR_LEN },
				{ "mcc_conf_file", cdp_eStr, (g_config.mcc_conf_file),
						cdp_Required, "mcc_conf.conf", MAX_DIR_LEN },
				{ "mcc_conf_path", cdp_eStr, (g_config.mcc_conf_path),
						cdp_Required, "./conf", MAX_DIR_LEN },
				{ "redis_conf_path", cdp_eStr, (g_config.redis_conf_path),
						cdp_Required, "./conf", MAX_DIR_LEN },
				{ "redis_conf_file", cdp_eStr, (g_config.redis_conf_file),
						cdp_Required, "redis_conf.conf", MAX_DIR_LEN },

				{ "cs_conf_file", cdp_eStr, (g_config.cs_conf_file),
						cdp_Required, "cs.conf", MAX_DIR_LEN },
				{ "cs_conf_path", cdp_eStr, (g_config.cs_conf_path),
						cdp_Required, "./conf", MAX_DIR_LEN },

				{ "mcc_product_name", cdp_eStr, (g_config.mcc_product_name),
						cdp_Required, "/baidu/ns/ksarch/cache", MAX_DIR_LEN },
				{ "ctimeout", cdp_eInt, &(g_config.ctimeout), 0, 0, 10 },
				{ "rtimeout", cdp_eInt, &(g_config.rtimeout), 0, 0, 10 },
				{ "wtimeout", cdp_eInt, &(g_config.wtimeout), 0, 0, 10 },

				{ "threadnum", cdp_eInt, &(g_config.threadnum), 0, 0, 10 },
				{ "listennum", cdp_eInt, &(g_config.listennum), 0, 0, 1024 },
				{ "max_sock_num", cdp_eInt, &(g_config.max_sock_num), 0, 0,
						1000 },
				{ "work_threadnum", cdp_eInt, &(g_config.work_threadnum), 0, 0,
						30 },
				{ "max_socket_request_num", cdp_eInt,
						&(g_config.max_socket_request_num), 0, 0, 10000 },
				{ "rehash_token", cdp_eStr, (g_config.rehash_token),
						cdp_Required, "TOKEN", MAX_DIR_LEN },
				{ "inpath", cdp_eStr, (g_config.inpath), cdp_Required,
						"./data/in/", MAX_DIR_LEN },
				{ "pid_filepath", cdp_eStr, (g_config.pid_filepath),
						cdp_Required, "./status/rls.pid", MAX_DIR_LEN },
                { "usc_ipport", cdp_eStr, (g_config.usc_ipport),
						cdp_Required, "", MAX_USCIPPORT_LEN*MAX_IPPORT_LEN+20 },
				{ "recommend_channel", cdp_eStr, (g_config.recommend_channel),
						cdp_Required, "", MAX_RECOMMEND_CHANNEL_LEN*MAX_CHNAME_LEN+50 },
				{ "detect_channel", cdp_eStr, (g_config.detect_channel),
						cdp_Required, "", MAX_DETECT_CHANNEL_LEN*MAX_CHNAME_LEN+50 },
				{ "i_brief_lan", cdp_eStr, (g_config.i_brief_lan),
						cdp_Required, "", MAX_DIM_BIT_LEN*MAX_INSTANT_DIM_CLASS_LEN + 100},
				{ "i_brief_year", cdp_eStr, (g_config.i_brief_year),
						cdp_Required, "", MAX_DIM_BIT_LEN*MAX_INSTANT_DIM_CLASS_LEN + 100},
				{ "i_brief_area", cdp_eStr, (g_config.i_brief_area),
						cdp_Required, "", MAX_DIM_BIT_LEN*MAX_INSTANT_DIM_CLASS_LEN + 100},
				{ "i_brief_gender", cdp_eStr, (g_config.i_brief_gender),
						cdp_Required, "", MAX_DIM_BIT_LEN*MAX_INSTANT_DIM_CLASS_LEN + 100},
                { "default_list_fname", cdp_eStr,
						(g_config.default_list_fname), cdp_Required,
						"./data/out/", MAX_DIR_LEN },
				{ "cold_start_singer_fname", cdp_eStr,
						(g_config.cold_start_singer_fname), cdp_Required,
						"./data/out/", MAX_DIR_LEN },
                { "blank_song_path", cdp_eStr, (g_config.blank_song_path),
                  cdp_Required, "blanksong.txt", MAX_DIR_LEN},
				{ "big_dict", cdp_eStr, (g_config.big_dict), cdp_Required,
						"big_dict", MAX_DIR_LEN },
				{ "detect_judge_song_dict", cdp_eStr, (g_config.detect_judge_song_dict), cdp_Required,
						"detect_judge_song_dict", MAX_DIR_LEN },
				{ "song_tag_dict", cdp_eStr, (g_config.song_tag_dict), cdp_Required,
						"song_tag_dict", MAX_DIR_LEN },
				{ "lr_model_dict", cdp_eStr, (g_config.lr_model_dict), cdp_Required,
						"lr_model_dict", MAX_DIR_LEN },
                { "ticket_dict", cdp_eStr, (g_config.ticket_dict), cdp_Required,
						"ticket_dict", MAX_DIR_LEN },

				{ "lr_feature_dict", cdp_eStr, (g_config.lr_feature_dict), cdp_Required,
						"lr_feature_dict", MAX_DIR_LEN },
                { "y_song_dict", cdp_eStr, (g_config.y_song_dict), cdp_Required,
                        "y_song_dict", MAX_DIR_LEN },
                { "y_channel_dict", cdp_eStr, (g_config.y_channel_dict), cdp_Required,
                        "y_channel_dict", MAX_DIR_LEN },
				{ "channel_song_dict", cdp_eStr, (g_config.channel_song_dict), cdp_Required,
						"channel_song_dict", MAX_DIR_LEN },
				{ "channel_detect_song_dict", cdp_eStr, (g_config.channel_detect_song_dict), cdp_Required,
						"channel_detect_song_dict", MAX_DIR_LEN },
				{ "yyr_chsong_dict", cdp_eStr, (g_config.yyr_chsong_dict), cdp_Required,
						"yyr_chsong_dict", MAX_DIR_LEN },
				{ "song_data", cdp_eStr, (g_config.song_data), cdp_Required,
						"song_data.dat", MAX_DIR_LEN },
				{ "singer_data", cdp_eStr, (g_config.singer_data),
						cdp_Required, "singer_data.dat", MAX_DIR_LEN },
				{ "album_data", cdp_eStr, (g_config.album_data), cdp_Required,
						"album_data.dat", MAX_DIR_LEN },
				{ "songsong_data", cdp_eStr, (g_config.songsong_data),
						cdp_Required, "songsong_data.dat", MAX_DIR_LEN },
				{ "singersinger_data", cdp_eStr, (g_config.singersinger_data),
						cdp_Required, "singersinger_data.dat", MAX_DIR_LEN },
				{ "singersong_data", cdp_eStr, (g_config.singersong_data),
						cdp_Required, "singersong_data.dat", MAX_DIR_LEN },
				{ "songbrief_data", cdp_eStr, (g_config.songbrief_data),
						cdp_Required, "songbrief_data.dat", MAX_DIR_LEN },
				{ "districtsinger_data", cdp_eStr,
						(g_config.districtsinger_data), cdp_Required,
						"districtsinger_data.dat", MAX_DIR_LEN },
                { "chinfolist_data", cdp_eStr,
                    (g_config.chinfolist_data), cdp_Required,
                    "channel_list.dat", MAX_DIR_LEN},
                { "lrweight_list_data", cdp_eStr,
                    (g_config.lrweight_list_data), cdp_Required,
                    "lr_model_dict.dat", MAX_DIR_LEN},
                { "ysong_list_data", cdp_eStr,
                    (g_config.ysong_list_data), cdp_Required,
                    "y_song_dict.dat", MAX_DIR_LEN},
                { "ychannel_list_data", cdp_eStr,
                    (g_config.ychannel_list_data), cdp_Required,
                    "y_channel_dict.dat", MAX_DIR_LEN},
                { "ticket_list_data", cdp_eStr,
                    (g_config.ticket_list_data), cdp_Required,
                    "ticket.dat", MAX_DIR_LEN},
                { "chsonglist_data", cdp_eStr,
                    (g_config.chsonglist_data), cdp_Required,
                    "channel_song.dat", MAX_DIR_LEN},
                { "insertsong_data", cdp_eStr,
                    (g_config.insertsong_data), cdp_Required,
                    "insert_song_stat.dat", MAX_DIR_LEN},
                { "channel_detect_song_data", cdp_eStr,
                    (g_config.channel_detect_song_data), cdp_Required,
                    "channel_detect_song.dat", MAX_DIR_LEN},
                { "detect_judge_song_data", cdp_eStr,
                    (g_config.detect_judge_song_data), cdp_Required,
                    "detect_judge_song.dat", MAX_DIR_LEN},
                { "spread_song_data", cdp_eStr,
                    (g_config.spread_song_data), cdp_Required,
                    "spread_song.dat", MAX_DIR_LEN},
                { "yyr_chsong_data", cdp_eStr,
                    (g_config.yyr_chsong_data), cdp_Required,
                    "yyr_chsong_dict.dat", MAX_DIR_LEN},
                { "publicrsong_data", cdp_eStr,
                    (g_config.publicrsong_data), cdp_Required,
                    "public_rsong.dat", MAX_DIR_LEN},
                { "publicrsingersong_data", cdp_eStr,
                    (g_config.publicrsingersong_data), cdp_Required,
                    "public_rsinger_song.dat", MAX_DIR_LEN},
                { "ting_artist_id", cdp_eStr,
                    (g_config.ting_artist_id), cdp_Required,
                    "ting_artist_id.dat", MAX_DIR_LEN},
                { "tail_song_data", cdp_eStr,
                    (g_config.tail_song_data), cdp_Required,
                    "tail_song.dat", MAX_DIR_LEN},
                { "user_list_pair", cdp_eStr,
                    (g_config.user_list_pair), cdp_Required,
                    "user_list_pair", MAX_DIR_LEN},
				{ "singer_scatter_m", cdp_eInt, &(g_config.singer_scatter_m),
						0, 0, 5 },
				{ "singer_scatter_n", cdp_eInt, &(g_config.singer_scatter_n),
						0, 0, 2 },
				{ "regenerate_title_len", cdp_eInt,
						&(g_config.regenerate_title_len), 0, 0, 10 },
				{ "regenerate_jump_len", cdp_eInt,
						&(g_config.regenerate_jump_len), 0, 0, 5 },
				{ "pass_deweight", cdp_eInt, &(g_config.pass_deweight), 0, 0,
						50 },
				{ "pass_deweigth_len", cdp_eInt, &(g_config.pass_deweigth_len),
						0, 0, 10 },
				{ "lovesong_inweight", cdp_eInt, &(g_config.lovesong_inweight), 0, 0,
                  30 },
                { "pass_deletesinger_len", cdp_eInt, &(g_config.pass_deletesinger_len), 0, 0,
                  10 },
				{ "lovesong_inweigth_len", cdp_eInt, &(g_config.lovesong_inweight_len),
						0, 0, 10 },
				{ "hate_deweight", cdp_eInt, &(g_config.hate_deweight), 0, 0,
						50 },
				{ "min_list_len", cdp_eInt, &(g_config.min_list_len), 0, 0, 50 },
                {"low_weight_replace_len", cdp_eInt, &(g_config.low_weight_replace_len), 0, 0, 50},
				{ "default_list_weight", cdp_eInt,
						&(g_config.default_list_weight), 0, 0, 10 },
				{ "action_timeout", cdp_eInt, &(g_config.action_timeout), 0, 0,
						1800 },
				{ "list_timeout", cdp_eInt, &(g_config.list_timeout), 0, 0,
						1800 },
				{ "tag_timeout", cdp_eInt, &(g_config.tag_timeout), 0, 0,
						10800 },
				{ "imodel_timeout", cdp_eInt, &(g_config.imodel_timeout), 0, 0,
						10800 },
                { "next_singerde_part", cdp_eInt, &(g_config.next_singerde_part), 0, 0, 25},
                { "next_pvde_part", cdp_eInt, &(g_config.next_pvde_part), 0, 0, 25},
                { "next_yearde_part", cdp_eInt, &(g_config.next_yearde_part), 0, 0, 25},
                { "next_lande_part", cdp_eInt, &(g_config.next_lande_part), 0, 0, 25},
                { "hate_singer_len", cdp_eInt, &(g_config.hate_singer_len), 0, 0, 3},
                { "pass_singer_len", cdp_eInt, &(g_config.pass_singer_len), 0, 0, 8},
                { "pass_deletesong_len", cdp_eInt, &(g_config.pass_deletesong_len), 0, 0, 20},
                { "filter_len", cdp_eInt, &(g_config.filter_len), 0, 0, 30},
                { "weight_param", cdp_eInt, &(g_config.weight_param), 0, 0, 40},
                { "smooth_lan", cdp_eInt, &(g_config.smooth_lan), 0, 0, 10},
                { "smooth_year", cdp_eInt, &(g_config.smooth_year), 0, 0, 30},
                { "smooth_pitch", cdp_eInt, &(g_config.smooth_pitch), 0, 0, 30},
                { "smooth_tune", cdp_eInt, &(g_config.smooth_tune), 0, 0, 30},
                { "smooth_area", cdp_eInt, &(g_config.smooth_area), 0, 0, 10},
                { "smooth_remove_num", cdp_eInt, &(g_config.smooth_remove_num), 0, 0, 2},
                { "smooth_times", cdp_eInt, &(g_config.smooth_times), 0, 0, 3},



				//权重配置
				{ "listen_w", cdp_eInt, &(g_config.WConf.listen_w), 0, 0, 75 },
				{ "mb_addso_w", cdp_eInt, &(g_config.WConf.mb_addso_w), 0, 0,
						25 },
				{ "mb_storesso_w", cdp_eInt, &(g_config.WConf.mb_storesso_w),
						0, 0, 100 },
				{ "mb_sharesso_w", cdp_eInt, &(g_config.WConf.mb_sharesso_w),
						0, 0, 100 },
				{ "mb_storeso_w", cdp_eInt, &(g_config.WConf.mb_storeso_w), 0,
						0, 100 },
				{ "mb_searchso_w", cdp_eInt, &(g_config.WConf.mb_searchso_w),
						0, 0, 25 },
				{ "mb_listenend_w", cdp_eInt, &(g_config.WConf.mb_listenend_w),
						0, 0, 0 },
				{ "fm_heartso_w", cdp_eInt, &(g_config.WConf.fm_heartso_w), 0,
						0, 100 },
				{ "fm_jumpso_w", cdp_eInt, &(g_config.WConf.fm_jumpso_w), 0, 0,
						-30 },
				{ "fm_listenend_w", cdp_eInt, &(g_config.WConf.fm_listenend_w),
						0, 0, 0 },
				{ "fm_jumpprior_w", cdp_eInt, &(g_config.WConf.fm_jumpprior_w),
						0, 0, 75 },
				{ "fm_heartsi_w", cdp_eInt, &(g_config.WConf.fm_heartsi_w), 0,
						0, 60 },
				{ "fm_hateso_w", cdp_eInt, &(g_config.WConf.fm_hateso_w), 0, 0,
						-50 },
				{ "fm_cloudso_w", cdp_eInt, &(g_config.WConf.fm_cloudso_w), 0, 0,
						-50 },
				{ "fm_hatesi_w", cdp_eInt, &(g_config.WConf.fm_hatesi_w), 0, 0,
						-50 },
				{ "good_pref_score", cdp_eInt, &(g_config.good_pref_score), 0, 0,
						10 },
				{ "high_pv_upweight", cdp_eInt, &(g_config.high_pv_upweight), 0, 0,
						10 },
				//即时行为的权值配置
				{ "fm_listen_60", cdp_eInt, &(g_config.IWConf.fm_listen_60), 0, 0, 1 },
				{ "fm_behavior_pre", cdp_eInt, &(g_config.IWConf.fm_behavior_pre), 0, 0, 4 },
				{ "fm_behavior_next", cdp_eInt, &(g_config.IWConf.fm_behavior_next), 0, 0, -2 },
				{ "fm_behavior_love", cdp_eInt, &(g_config.IWConf.fm_behavior_love), 0, 0, 5 },
				{ "fm_behavior_hate", cdp_eInt, &(g_config.IWConf.fm_behavior_hate), 0, 0, -5 },
				{ "i_lan_up", cdp_eInt, &(g_config.IWConf.i_lan_up), 0, 0, 60 },
				{ "i_lan_de", cdp_eInt, &(g_config.IWConf.i_lan_de), 0, 0, -30 },
				{ "i_year_up", cdp_eInt, &(g_config.IWConf.i_year_up), 0, 0, 50 },
				{ "i_year_de", cdp_eInt, &(g_config.IWConf.i_year_de), 0, 0, -25 },
				{ "i_gender_up", cdp_eInt, &(g_config.IWConf.i_gender_up), 0, 0, 20 },
				{ "i_gender_de", cdp_eInt, &(g_config.IWConf.i_gender_de), 0, 0, -10 },
				{ "i_area_up", cdp_eInt, &(g_config.IWConf.i_area_up), 0, 0, 20 },
				{ "i_area_de", cdp_eInt, &(g_config.IWConf.i_area_de), 0, 0, -10 },
				{ "general_rate", cdp_eInt, &(g_config.IWConf.general_rate), 0, 0, 2 },
				{ "real_rate", cdp_eInt, &(g_config.IWConf.real_rate), 0, 0, 1 },
				{ "detect_rate", cdp_eInt, &(g_config.IWConf.detect_rate), 0, 0, 5 },
				//mcc超时
				{ "mcc_listen_history_timeout", cdp_eInt, &(g_config.mcc_listen_history_timeout), 0, 0, 86400 },
				{ "mcc_co_listen_history_timeout", cdp_eInt, &(g_config.mcc_co_listen_history_timeout), 0, 0, 86400 },
				{ "mcc_user_behavior_timeout", cdp_eInt, &(g_config.mcc_user_behavior_timeout), 0, 0, 86400 },
				{ "mcc_co_user_behavior_timeout", cdp_eInt, &(g_config.mcc_co_user_behavior_timeout), 0, 0, 86400 },
				{ "mcc_co_item_pref_timeout", cdp_eInt, &(g_config.mcc_co_item_pref_timeout), 0, 0, 86400 },
				{ "mcc_user_list_timeout", cdp_eInt, &(g_config.mcc_user_list_timeout), 0, 0, 86400 },

				{ "mcc_usc_timeout", cdp_eInt, &(g_config.mcc_usc_timeout), 0, 0, 172800 },
				{ "mcc_user_redis_list_sign_timeout", cdp_eInt, &(g_config.mcc_user_redis_list_sign_timeout), 0, 0, 86400},
                { "mcc_y_user_behavior_timeout", cdp_eInt, &(g_config.mcc_y_user_behavior_timeout), 0, 0, 10800 },
                { "mcc_co_y_user_behavior_timeout", cdp_eInt, &(g_config.mcc_co_y_user_behavior_timeout), 0, 0, 10800 },

				{ "mcc_play_list", cdp_eInt, &(g_config.mcc_play_list), 0, 0, 10800 },
				{ "mcc_co_play_list", cdp_eInt, &(g_config.mcc_co_play_list), 0, 0, 10800 },
				{ "mcc_negation_record", cdp_eInt, &(g_config.mcc_negation_record), 0, 0, 1200 },
				{ "mcc_co_negation_record", cdp_eInt, &(g_config.mcc_co_negation_record), 0, 0, 1200 },
				{ "mcc_instant_model", cdp_eInt, &(g_config.mcc_instant_model), 0, 0, 10800 },
				{ "mcc_co_instant_model", cdp_eInt, &(g_config.mcc_co_instant_model), 0, 0, 10800 },
                { "mcc_user_instant_behavior", cdp_eInt, &(g_config.mcc_user_instant_behavior), 0, 0, 3600 },

				{ "redis_client_num", cdp_eInt, &(g_config.redis_client_num), 0, 0, 60},

				{ 0, cdp_eNull, 0, 0, 0, 0 } };

c_descript_t
		g_cs_descripts[] =
			{
				{ "listenport", cdp_eInt, &(g_config.listenport), 0, 0, 9899 },//监听端口
				{ "reload_port", cdp_eInt, &(g_config.reload_port), 0, 0, 9900 },//重载端口
				{ "flow_mark", cdp_eInt, &(g_config.flow_mark), 0, 0, 0}//分流标识
			};
/**
 * @function: load all config
 * @param configfile : the config file name ,containing path
 * @param cdp_list : cdp_list , need to load
 * @param openlogfile : whether open log file
 * @param defaultlogname : default log name
 * @return 0: ok ;   -1 : err
 */
int load_all_c_descripts(const char *configfile, c_descript_t* cdp_list,
		int openlogfile, char*defaultlogname)
{

	// init buckets
	Ul_confdata *buckets = load_confdata(configfile);
	if (buckets == NULL)
	{
		return -1;
	}

	c_descript_t *cdp = cdp_list;
	int tmpInt;
	char tmpStr[LINE_MAX];

	while (cdp && cdp->name)
	{
		switch (cdp->type)
		{
		case cdp_eInt:
			tmpInt = 0;
			if (!ul_getconfint(buckets, cdp->name, &tmpInt))
			{
				if (cdp->options & cdp_Required)
				{
					WARNING_LOG("cdp {name \"%s\", type %d} Required, but not found!",
							cdp->name, cdp->type);
					return -1;
				}
				// else keep it as it is ...
			}
			else
			{
				*(int*) cdp->addr = cdp->capability;
			}
			break;
		case cdp_eStr:
			*tmpStr = '\0';
			if (!ul_getconfstr(buckets, cdp->name, tmpStr))
			{
				if (cdp->options & cdp_Required)
				{
					WARNING_LOG("cdp {name \"%s\", type %d} Required, but not found!",
							cdp->name, cdp->type);
					return -1;
				}

				if (cdp->default_str)
				{
					ul_strlcpy ((char *)cdp->addr, cdp->default_str,cdp->capability);
				}

				// keep it as it is ...
			}
			else
			{
				ul_strlcpy ((char *)cdp->addr, tmpStr, cdp->capability);
			}
			break;
		default:
			WARNING_LOG("Unknown cdp->type, %d,check it!", cdp->type);
			return -1;
		}

		cdp++;
	}

	// logfile
	char tmpdir[PATH_MAX];
	char tmpfilename[PATH_MAX];
	int loglevel = UL_LOG_DEBUG;
	int logsize = 1024;

	if (openlogfile)
	{
		if (!ul_getconfstr(buckets, "LOG_PATH", tmpdir))
		{
			ul_strlcpy(tmpdir, "./log/", sizeof(tmpdir));
		}

		if (!ul_getconfstr(buckets, "LOG_NAME", tmpfilename))
		{
			if (!defaultlogname || *defaultlogname == '\0')
			{
				WARNING_LOG("call load_all_c_descripts with"
						"defaultlogname empty when openlogfile is true!!!");
				return -1;
			}

			ul_strlcpy(tmpfilename, defaultlogname, sizeof(tmpfilename));
		}

		if (!ul_getconfint(buckets, "LOG_LEVEL", &loglevel))
		{
			loglevel = UL_LOG_DEBUG;
		}

		if (!ul_getconfint(buckets, "LOG_SIZE", &logsize))
		{
			logsize = 1024;
		}
	}

	ul_freeconf(buckets);

//	if (openlogfile)
//	{
//		g_log_stat.events = loglevel;
//		g_log_stat.spec = 0;
//		g_log_stat.to_syslog = 0;
//
//		if (ul_openlog(tmpdir, tmpfilename, &g_log_stat, logsize))
//		{
//			WARNING_LOG("ul_openlog failed {\"%s\", \"%s\", %d, %d}, %m",
//					tmpdir, tmpfilename, loglevel, logsize);
//			return -1;
//		}
//
//		//     ul_threadlog_sup();
//	}

	return 0;
}

/**
 * @function: load all config
 * @param configfile : the config data
 * @param cdp_list : cdp_list , need to load
 * @param openlogfile : whether open log file
 * @param defaultlogname : default log name
 * @return 0: ok ;   -1 : err
 */
int load_all_c_descripts(Ul_confdata *buckets, c_descript_t* cdp_list,
		int openlogfile, char*defaultlogname)
{
	c_descript_t *cdp = cdp_list;
	int tmpInt;
	char tmpStr[LINE_MAX];

	while (cdp && cdp->name)
	{
		switch (cdp->type)
		{
		case cdp_eInt:
			tmpInt = 0;
			if (!ul_getconfint(buckets, cdp->name, &tmpInt))
			{
				if (cdp->options & cdp_Required)
				{
					WARNING_LOG("cdp {name \"%s\", type %d} Required, but not found!",
							cdp->name, cdp->type);
					return -1;
				}
				else
				{
					*(int*) cdp->addr = cdp->capability;
				}
			}
			else
			{
				*(int*) cdp->addr = tmpInt;
			}
			break;
		case cdp_eStr:
			*tmpStr = '\0';
			if (!ul_getconfstr(buckets, cdp->name, tmpStr))
			{
				if (cdp->options & cdp_Required)
				{
					WARNING_LOG("cdp {name \"%s\", type %d} Required, but not found!",
							cdp->name, cdp->type);
					return -1;
				}

				if (cdp->default_str)
				{
					ul_strlcpy ((char *)cdp->addr, cdp->default_str,cdp->capability);
				}

				// keep it as it is ...
			}
			else
			{
				ul_strlcpy ((char *)cdp->addr, tmpStr, cdp->capability);
			}
			break;
		default:
			WARNING_LOG("Unknown cdp->type, %d,check it!", cdp->type);
			return -1;
		}

		cdp++;
	}

	return 0;
}


/**
 * @function: load all config
 * @param configfile : the config file name ,containing path
 * @param cdp_list : cdp_list , need to load
 * @param openlogfile : whether open log file
 * @param defaultlogname : default log name
 * @return 0: ok ;   -1 : err
 */
Ul_confdata* load_confdata(const char *configfile)
{
	Ul_confdata *buckets;

	// init buckets
	buckets = ul_initconf(0);
	if (!buckets)
	{
		WARNING_LOG("ul_initconf failed, \"%s\"", configfile);
		return NULL;
	}

	// load ...
	if (access(configfile, F_OK | R_OK) != 0)
	{
		WARNING_LOG("configfile \"%s\" access failed, %m", configfile);
		return NULL;
	}

	char tmpdir[PATH_MAX];
	char tmpfilename[PATH_MAX];

	char *lastslash = strrchr(configfile, '/');
	if (!lastslash)
	{
		ul_strlcpy(tmpdir, "./", sizeof(tmpdir));
	}
	else
	{
		int pathLen = lastslash - configfile + 1;
		if (pathLen >= (int) sizeof(tmpdir))
		{
			WARNING_LOG("configfile \"%s\" PATH Length(%d) > %d, failed.",
					configfile, pathLen, (int) sizeof(tmpdir));
			return NULL;
		}

		ul_strlcpy(tmpdir, configfile, pathLen + 1);
	}

	if (!lastslash)
	{
		ul_strlcpy(tmpfilename, configfile, sizeof(tmpfilename));
	}
	else
	{
		lastslash++;
		int nameLen = strlen(lastslash);

		if (nameLen <= 0 || nameLen >= (int) sizeof(tmpfilename))
		{
			WARNING_LOG("configfile \"%s\" FILE Length(%d) > %d, failed.",
					configfile, nameLen, (int) sizeof(tmpfilename));
			return NULL;
		}

		ul_strlcpy(tmpfilename, lastslash, nameLen + 1);
	}

	if (ul_readconf(tmpdir, tmpfilename, buckets) < 0)
	{
		WARNING_LOG("load configfile \"%s\" {\"%s\", \"%s\"} failed, %m",
				configfile, tmpdir, tmpfilename);
		return NULL;
	}
	return buckets;
}
