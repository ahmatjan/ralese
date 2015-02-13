/**
 * =====================================================================================
 *
 *	Filename:  config.h
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

#ifndef _CONFIG_H_
#define _CONFIG_H_

#include <time.h>
#include <limits.h>

#include "macro.h"
#include "common.h"
#include "ul_conf.h"
#include "rls_def.h"

//extern ul_logstat_t g_log_stat;

///require config
#define cdp_Required	0x01

using namespace rls;

/// conf struct
enum cdpType {
    cdp_eNull,
    cdp_eInt,
    cdp_eStr,
};

/**
 * config descript
 */
typedef struct {
		///name
    char *name;
    ///type
    enum cdpType type;
    ///addr
    void *addr;
    ///option.
    int options;
    ///default
    char *default_str;
    ///str size for str. default value for int
    int capability;
} c_descript_t;


/**权值信息*/
typedef struct _weight_conf_t
{
	int listen_w;  /**<视听歌曲权重*/
	int mb_addso_w;  /**<音乐盒添加歌曲权重*/
	int mb_storesso_w; /**<音乐盒收藏单曲权重*/
	int mb_sharesso_w; /**<音乐盒分享单曲权重*/
	int mb_storeso_w;  /**<音乐盒收藏歌曲权重*/
	int mb_searchso_w;  /**<音乐盒搜索歌曲权重*/
	int mb_listenend_w;  /**<音乐盒听完歌曲权重*/
	int fm_heartso_w;  /**<电台歌曲加心权重*/
	int fm_jumpso_w;  /**<电台跳过歌曲权重*/
	int fm_listenend_w;  /**<电台听完歌曲权重*/
	int fm_jumpprior_w;  /**<电台点击上一首歌曲权重*/
	int fm_heartsi_w;   /**<电台加心歌手*/
	int fm_hateso_w;	/**<电台垃圾桶歌曲*/
	int fm_hatesi_w;	/**<电台垃圾桶歌手*/
    int fm_cloudso_w;  //音乐盒云收藏


	double day_w[MAX_DAY];  /**<天数权值*/
    double num_w[MAX_NUM];  /**<次数权值*/
	/**<歌曲权重累积公式表*/
	int good_weight_table[MAX_WEIGHT+1][MAX_PERCENT+1];//100*(x/100)^(e^(-n/100)) lookup this table using x and n;
	/**<歌曲有负权值是，权重累积公式表*/
	int bad_weight_table[MAX_WEIGHT + 1];//100*(x/100)^(e^(-n/100)) lookup this table using x and n;

}Weight_Conf_t;


/**即时行为权值信息*/
typedef struct _i_weight_conf_t
{
    int fm_listen_60;  /**<完整听歌歌曲权重*/
    int fm_behavior_pre;  /**<上一首歌曲权重*/
    int fm_behavior_next; /**<下一首歌曲权重*/
    int fm_behavior_love; /**<喜欢单曲权重*/
    int fm_behavior_hate;  /**<不喜欢歌曲权重*/
    int i_lan_up; //语言提权
    int i_lan_de; //语言降权
    int i_year_up; //年代提权
    int i_year_de; //年代降权
    int i_gender_up; //地区提权
    int i_gender_de; //地区降权
    int i_area_up; //性别提权
    int i_area_de ; //性别降权
    //不同反馈行为的不同权值
    int general_rate ; //普通行为
    int real_rate ; //即时行为
    int detect_rate ; //反馈行为
}I_Weight_Conf_t;

/**
 * config_t class
 */
class config_t {
public:

	char configfile[MAX_DIR_LEN];	/**<配置文件*/
	char dbconfig[MAX_DIR_LEN];	/**<数据库配置文件*/
	char dbconfigpath[MAX_DIR_LEN];	/**<数据库配置文件路径*/
	char comlog_conf_file[MAX_DIR_LEN];	/**<comlog配置文件路径*/
	char comlog_conf_path[MAX_DIR_LEN];/**<comlog配置文件路径*/
	char ub_client_conf_path[MAX_DIR_LEN];/**<ub_client配置文件路径*/
	char ub_client_conf_file[MAX_DIR_LEN];	/**<ub_client配置文件路径*/
	char mcc_conf_path[MAX_DIR_LEN]; //mcc 配置文件路径
	char mcc_conf_file[MAX_DIR_LEN]; //mcclient 配置文件名	
	char redis_conf_path[MAX_DIR_LEN]; //redis配置文件路径
	char redis_conf_file[MAX_DIR_LEN]; //redis配置文件名	
    char cs_conf_path[MAX_DIR_LEN]; //cs 配置文件路径
    char cs_conf_file[MAX_DIR_LEN]; //cs 配置文件名   
	char usc_ipport[MAX_USCIPPORT_LEN*MAX_IPPORT_LEN + 20]; //用户中心ip端口的配置
    char recommend_channel[MAX_CHNAME_LEN*MAX_RECOMMEND_CHANNEL_LEN + 50]; //含推荐策略的频道配置
    char detect_channel[MAX_CHNAME_LEN*MAX_DETECT_CHANNEL_LEN + 50];//含推荐策略的频道配置
    char i_brief_lan[MAX_DIM_BIT_LEN*MAX_INSTANT_DIM_CLASS_LEN + 100]; //即时策略语言编号的对应关系
    char i_brief_year[MAX_DIM_BIT_LEN*MAX_INSTANT_DIM_CLASS_LEN + 100]; //即时策略年代编号的对应关系
    char i_brief_gender[MAX_DIM_BIT_LEN*MAX_INSTANT_DIM_CLASS_LEN + 100]; //即时策略性别编号的对应关系
    char i_brief_area[MAX_DIM_BIT_LEN*MAX_INSTANT_DIM_CLASS_LEN + 100]; //即时策略地区编号的对应关系
    int good_pref_score; //一个好的分数下限
    int pass_deletesinger_len;//跳过的歌手删除
    int pass_deletesong_len;//跳过时，歌曲删除    
	int original_weight; //原始列表权值
	int user_cf_weight; //user-cf列表权值
	int item_cf_weight; //item-cf列表权值
    int um_weight; //um列表权值
    int uc_weight; //uc列表权值
	int fuse_rate; //列表融合的公共系数
    int um_change_weight; //用户模型调权比率
    int weight_param;//重定义权值参数
    int smooth_lan; //平滑列表时，语言权值
    int smooth_year; //平滑列表时，年代权值
    int smooth_pitch; //平滑列表时，音调权值
    int smooth_tune; //平滑列表时，节奏权值
    int smooth_area; //平滑区间
    int smooth_remove_num; //平滑移除数
    int smooth_times; //平滑次数
    int flow_mark; //分流标识 

	//for rls 服务使用
	int ctimeout; /**< connection timeout(ms)*/
	int rtimeout; /**< read timeout(ms)*/
	int wtimeout; /**< write timeout(ms)*/

	//服务有关数据
	int	listenport; /**< listen port*/
	int reload_port; /**< reload port*/
	int threadnum;  /**< thread num*/
	int listennum; /**< listen num*/
	int max_sock_num; /**< max sock num */
	int work_threadnum; /**< work thread num */
	uint max_socket_request_num; /**< max request num for one socket */

	char rehash_token[MAX_DIR_LEN]; /**< 用户名重新签名的token*/

    char mcc_product_name[MAX_DIR_LEN]; //mcc的产品名字

	Weight_Conf_t WConf; /**< 权值配置*/
    I_Weight_Conf_t IWConf; //即时行为建模的权值配置

	char inpath[MAX_DIR_LEN]; /**< 输入数据目录 */
	char pid_filepath[MAX_DIR_LEN]; /**< 保存进程id文件*/
	char default_list_fname[MAX_DIR_LEN]; /**< 冷启动列表文件名 */
    char cold_start_singer_fname[MAX_DIR_LEN]; /*冷启动歌手文件名*/

	char big_dict[MAX_DIR_LEN]; /*大索引字典*/
    char channel_detect_song_dict[MAX_DIR_LEN]; /*试探歌曲索引字典*/
    char detect_judge_song_dict[MAX_DIR_LEN]; /*试探歌曲判断索引字典*/
    char song_tag_dict[MAX_DIR_LEN]; /*歌曲标签字典*/
    char channel_song_dict[MAX_DIR_LEN]; //频道歌曲字典，查歌曲权值
    char lr_feature_dict[MAX_DIR_LEN]; //pcpr的特征字典
    char lr_model_dict[MAX_DIR_LEN]; //pcpr的模型字典
    char y_channel_dict[MAX_DIR_LEN];//百度音乐人频道字典
    char y_song_dict[MAX_DIR_LEN];//百度音乐歌曲字典
    char ticket_dict[MAX_DIR_LEN]; //票务数据字典
    char yyr_chsong_dict[MAX_DIR_LEN]; //公共频道音乐人歌曲字典

	char song_data[MAX_DIR_LEN]; /**< 歌曲列表文件名 */
	char singer_data[MAX_DIR_LEN]; /**< 歌手列表文件名 */
	char album_data[MAX_DIR_LEN]; /**< 专辑列表文件名 */
	char songsong_data[MAX_DIR_LEN]; /**< 歌曲关联列表文件名 */
	char singersinger_data[MAX_DIR_LEN]; /**< 歌手关联列表文件名 */
	char singersong_data[MAX_DIR_LEN]; /**< 歌手关联歌曲列表文件名 */
	char songbrief_data[MAX_DIR_LEN]; /**< 歌曲详细信息文件名 */
	char districtsinger_data[MAX_DIR_LEN]; /**< 地区歌手详细信息文件名 */
    char insertsong_data[MAX_DIR_LEN]; /**< 插入歌曲文件名 */
    char channel_detect_song_data[MAX_DIR_LEN]; /**< 试探歌曲文件名 */
    char detect_judge_song_data[MAX_DIR_LEN]; /**< 判断试探歌曲文件名 */
    char spread_song_data[MAX_DIR_LEN]; //推广歌曲
    char yyr_chsong_data[MAX_DIR_LEN]; //公共频道音乐人歌曲

    char blank_song_path[MAX_DIR_LEN]; //黑名单文件路径名
    
    char chinfolist_data[MAX_DIR_LEN]; /*频道信息列表文件名*/
    char chsonglist_data[MAX_DIR_LEN]; /*频道歌曲列表文件名*/
    char publicrsong_data[MAX_DIR_LEN]; /*公用频道歌曲的关联歌曲列表文件名*/
    char publicrsingersong_data[MAX_DIR_LEN]; /*公用频道歌手的关联歌曲列表*/
    char lrweight_list_data[MAX_DIR_LEN]; //pcpr权值列表文件名
    char tail_song_data[MAX_DIR_LEN];//长尾好歌
    char ysong_list_data[MAX_DIR_LEN];//百度音乐人歌曲数据
    char ychannel_list_data[MAX_DIR_LEN];//百度音乐人频道数据
    char ticket_list_data[MAX_DIR_LEN]; //票务数据

    char ting_artist_id[MAX_DIR_LEN]; /*ting id映射*/

    char user_list_pair[MAX_DIR_LEN]; /*user_list的r_type与method对应关系*/

	int singer_scatter_m; /**< 歌曲打散的大长度*/
	int singer_scatter_n; /**< 歌曲打散的重复阈值*/

	int regenerate_title_len; /**< 重新生成列表的最低阈值*/
	int regenerate_jump_len;	/**< 重新生成列表的跳过阈值*/

	int pass_deweight;	/**<跳过的降权阈值(降到n%)*/
	int pass_deweigth_len;	/**<跳过降权topN长度*/
    
    int lovesong_inweight; //加心歌曲关联歌曲提权比例
    int lovesong_inweight_len; //加心歌曲提权topN长度

	int hate_deweight;	/**<垃圾桶降权阈值*/
	int min_list_len;	/**<列表的最小长度*/
	int default_list_weight;	/**<备选歌曲列表的权重*/

	int action_timeout;	/**<行为缓存的超时秒数*/
	int list_timeout;	/**<列表数据缓存的超时秒数*/
    int tag_timeout;    /**<标签数据缓存的超时秒数*/
    int imodel_timeout;    //即时用户模型的超时秒数
    int next_singerde_part; //跳过的百分比阈值
    int next_yearde_part;
    int next_pvde_part;
    int next_lande_part;
    
    int high_pv_upweight; //高PV提权百分比
    int low_weight_replace_len; //低权重替换的个数

    int hate_singer_len;//过滤最近垃圾桶歌曲的歌手歌曲数
    int pass_singer_len;//过滤最近behavior中跳过歌曲的歌手的歌曲数
    int filter_len; //过滤长度

    /***mcc 超时时间*/
    int mcc_listen_history_timeout; //试听历史
    int mcc_co_listen_history_timeout; //cookie试听历史
    int mcc_user_behavior_timeout; //用户行为   
    int mcc_co_user_behavior_timeout; //cookie用户行为
    int mcc_co_item_pref_timeout; //cookie用户喜好数据
    int mcc_user_list_timeout;//用户算法列表

	int mcc_user_redis_list_sign_timeout;//redis list sign
    int mcc_y_user_behavior_timeout;//百度音乐人用户行为
    int mcc_co_y_user_behavior_timeout;//百度音乐人cookie用户行为
    
    int mcc_usc_timeout; //用户中心数据 

    int mcc_play_list; //播放列表
    int mcc_co_play_list; //cookie播放列表
    int mcc_negation_record; //负向行为
    int mcc_co_negation_record; //cookie负向行为
    int mcc_instant_model; //即时模型
    int mcc_co_instant_model; //cookie即时模型
    int mcc_user_instant_behavior; //实时行为cache

    int redis_client_num; //redis client启动数
    
	config_t ();
	~config_t ();
};



/**
 * global config
 */
extern config_t g_config;

/**
 * c_des list. used to load config file
 * @arg1 : the mark
 * @arg2 : the type
 * @arg3 : the addr
 * @arg4 : whether necessary
 * @arg5 : the default value
 * @arg6 : the capability to fill
 */
extern c_descript_t g_c_descripts [];

extern c_descript_t g_cs_descripts [];

/**
 * @function: load all config
 * @param configfile : the config file name ,containing path
 * @param cdp_list : cdp_list , need to load
 * @param openlogfile : whether open log file
 * @param defaultlogname : default log name
 * @return 0: ok ;   -1 : err
 */
int load_all_c_descripts(const char *configfile, c_descript_t* cdp_list,
		int openlogfile, char*defaultlogname);

/**
 * @function: load all config
 * @param configfile : the config data
 * @param cdp_list : cdp_list , need to load
 * @param openlogfile : whether open log file
 * @param defaultlogname : default log name
 * @return 0: ok ;   -1 : err
 */
int load_all_c_descripts(Ul_confdata *buckets, c_descript_t* cdp_list,
		int openlogfile, char*defaultlogname);

/**
 * @function: load all config
 * @param configfile : the config file name ,containing path
 * @param cdp_list : cdp_list , need to load
 * @param openlogfile : whether open log file
 * @param defaultlogname : default log name
 * @return 0: ok ;   -1 : err
 */
Ul_confdata* load_confdata(const char *configfile);
#endif /* _CONFIG_H_ */
