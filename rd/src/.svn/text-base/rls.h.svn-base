/**
 *
 * =====================================================================================
 *
 *	Filename:  rls.h
 *
 *	Description:  header file for rls.cpp
 *
 *	Version:  1.0
 *  Created: 2011-5-26
 *	Revision:  none
 *	Compiler:  gcc
 *
 *	Author:  zhangjunying, zhangjunying@baidu.com
 *	Company:  baidu.com Inc.
 *
 * =====================================================================================
 */

#ifndef _RLS_H_
#define _RLS_H_
#include <queue>
#include "odict.h"
#include "ul_dict.h"
#include "ul_log.h"
#include "ul_conf.h"
#include "ul_net.h"
#include "ul_sign.h"
#include "stdlib.h"
#include "stdio.h"
#include "nshead.h"
#include "mc_pack.h"
#include "mc_pack_rp.h"
#include <netinet/tcp.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include "mynet.h"
#include "ependingpool.h"
#include "config.h"
#include "myclient_include.h"
#include "common.h"
#include "macro.h"
#include "idl/rls2.idl.h"
#include "spcache.h"
#include "rls_def.h"
#include <bsl/map.h>
#include <ubclient_include.h>
//#include "McClient.h"
#include "redis_client.h"
#include "ne_mcclient.h"
 

/**< project name */
#define PROJECT_NAME 	"rls"
#define PROJECT_DESCRIPTION 	"rls is develop to provide service for login-user"
/**< 配置文件 */
#define DEFAULT_CONF_FILE "./conf/rls.conf"

/**< debug used*/
//#define _DEBUG_TIME
#undef _DEBUG_TIME
using namespace rls;
/**< unsigned int定义 */
typedef unsigned int uint;

//推广歌曲数据结构
typedef struct _spread_song_t{
  uint song_id;//歌曲id
  //推广位置为[pos_begin, pos_end)
  int pos_begin; //推广列表位首
  int pos_end; //推广列表位尾
  int rate;//概率
}spread_song_t;

//长尾好歌数据结构
typedef struct _tail_song_t{
    uint song_id; //歌曲id
    int weight;//选择阈值
}tail_song_t;

//百度音乐人歌曲数据结构
typedef struct y_song_info_t
{
    int artist_id;
    int genre;
    int hot_listen;
}y_song_info;


/**struct for thread data*/
typedef struct _Svr_thread_data_t
{
	int fd; /**< 对应套接字 */
	int handle; /**< 套接字句柄 */
	char buf[DEFAULT_MCPACK_LEN];/**< buffer */
	nshead_t head; /**< nshead */

}Svr_thread_data_t;

//用于存时用户当天实时行为的cache, 最近的用户行为
typedef struct _user_instant_behavior_t{
        uint song_id; // 歌曲id
        int type; //类型
        uint timestamp; //时间戳
}user_instant_behavior_t;


/**buf struct for read and write*/
typedef struct _Svr_buf_t{
	pthread_mutex_t		write_mutex; /**< mutex */
    std::queue<Svr_thread_data_t>* svr_data; /*线程请求数据队列*/
}Svr_buf_t;

typedef struct _singer_id_t{
    /*曲库的歌手id*/
    uint64_t qid;
    /*其他的歌手id*/
    uint64_t oid;
}singer_id_t;

/**< 歌曲信息结构体 */
typedef struct _song_item_t
{
	uint song_id;/**< 歌曲id */
	int weight;/**< 权重 */
    uint source;//来源
} Song_item_t;

/**< 标签信息结构体 */
typedef struct _user_tag_t
{
    char tag_title[USER_TAG_LEN];/**< 标签名*/
    int tag_id;
    int tag_weight;
} User_tag_t;

/**< 歌手信息结构体 */
typedef struct _singer_item_t
{
	uint singer_id;/**< 歌手id */
	int weight;/**< 权重 */
    uint source;//来源
} Singer_item_t;

/**< 歌曲详细信息结构体 */
typedef struct _song_brief_t
{
	int pv; /**< pv */
	int year;/**< 年代 */
	int lang;/**< 语言 */
	int album_id;/**< 专辑id */
	int singer_id;/**< 歌手id */
    int area; //地区
    int gender; //性别
	int pitch;//音调
	int tune;//节奏
} Song_brief_t;

//票务数据结构
//@piao.baidu.com/mis/ticketsinfo
typedef struct _ticket_info_t{
    int ticket_id; //票id
    int artist_id; //艺人id
    int start_time; //开始时间
    int end_time; //结束时间
    char city[10]; //演出城市
    char price[10]; //价格区间
    int pv; //pv访问量
    int sell; //平台售票量
}Ticket_info_t;

/*频道信息结构体*/
typedef struct _ch_info_t{
    /*频道名字*/
    char ch_name[MAX_CHNAME_LEN];
    /*频道显示名字*/
    char ch_sname[MAX_CHNAME_LEN];
    /*频道的描述*/
    char ch_desc[MAX_CHDESC_LEN];
    /*频道id*/
    uint ch_id;
    /*频道顺序*/
    uint ch_order;
    /*频道分类名字*/
    char cate_name[MAX_CHNAME_LEN];
    /*频道分类显示名字*/
    char cate_sname[MAX_CHNAME_LEN];
    /*频道分类顺序*/
    uint cate_order;
    /*频道pv顺序*/
    uint ch_pv_order;    
    /*频道的描述*/
    char ch_cover[MAX_CHCOVER_LEN];
}ch_info_t;

/*歌曲id信息*/
typedef struct _song_id_t{
    /*歌曲的曲库id*/
    uint64_t sid;
    //频道歌曲的权值
    uint64_t oid;
}song_id_t;

/*融合列表结构, 第一个为原列表，第二个为user_cf列表，第三个为item_cf列表
 *第三个为UM列表，第四个为UC列表
*/
typedef struct _fuse_list_t{
	//list指针数组
   	Song_item_t * (fuse_list[FUSE_LIST_NUM]) ;
    //对应列表长度
    uint fuse_list_len[FUSE_LIST_NUM];
	//对应列表的权值
	uint fuse_list_weight[FUSE_LIST_NUM];
    //对应列表的r_type值
    uint fuse_list_type[FUSE_LIST_NUM];
}fuse_list_t;

/*instant 初始化的建模维度和试探维度*/
typedef struct _instant_init{
    int dim_type; //需要建模的维度
    int dim_det; //需要试探的维度

}instant_init;

/*fuse init,初始化算法列表整合的数据结构*/
typedef struct _fuse_init{
    int source; //整合时的来源标识
    int rate; //整合比例
}fuse_init;

//user_cnt 结构，用于疲劳度控制
typedef struct _user_cnt_t{
    int cnt;
    int timestamp;
}user_cnt_t;

/**brief struct for global data*/
typedef struct _Global_t
{
	//输入歌曲、歌手、用户索引字典
	SpCache *listCache;/**< 列表缓存 */
	SpCache *lsongCache;/**< 喜好歌曲缓存 */
	SpCache *hsongCache;/**< 垃圾桶歌曲缓存 */
	SpCache *lsingerCache;/**< 喜好歌手缓存 */
	SpCache *hsingerCache;/**< 垃圾桶歌手缓存 */
	SpCache *listenCache;/**< 收听历史缓存 */
	SpCache *actionCache;/**< 行为缓存 */

	SpCache *user_tag_cache;//user tag，有上限，key:uid, ,uid
    SpCache *i_model_cache;//user tag，有上限，key:uid, ,频道create_sign32

	SpCache *ral_list_cache;//ral列表，有上限，key:uid, 频道create_sign32, r_type
    SpCache *co_ch_list_cache; //分频道的个性化列表缓存,key:baiduid, 频道create_sign32
    SpCache *co_lsong_cache; //cookie的喜欢歌曲列表,有上限,key:baiduid,baiduid
    SpCache *co_hsong_cache; //cookie的讨厌歌曲列表,有上限,key:baiduid,baiduid
    SpCache *co_lsinger_cache;//cookie喜欢歌手cache, 有上限, key:baiduid, baiduid
    SpCache *co_hsinger_cache; //cookie讨厌歌手cache,有上限,key:baiduid, baiduid
    SpCache *co_listen_cache; //cookie试听歌曲列表,有上限,key:baiduid,baiduid
    SpCache *co_action_cache; //cookie行为缓存,有上限，key:baiduid,baiduid
    SpCache *action_record_cache; //用户实时行为统计记录, key:baiduid,baiduid或者uid,uid,重建列表时会清空
    SpCache *co_i_model_cache;//user tag，有上限，key:baiduid, ,频道create_sign32
    SpCache *db_type_cache; //dbtype cache, 有上限，key：uid或baiduid, DATA_DB_TYPE 

    char USC_IPPORT[MAX_IPPORT_LEN]; //用户中心的IP端口列表
    char USC_IPPORT1[MAX_IPPORT_LEN];//用户中心IP端口列表1，主用
    char USC_IPPORT2[MAX_IPPORT_LEN]; //用户中心的IP端口2，备用
    bool USC_OK; //usc是否可用
    
	/**< msql连接池 */
	MyclientPool* dbpool;

    /** redis */
    store::RedisClientManager *redis_cli;

    /***mcc cache集群***/
    //McClient *mcc;
    NeMcClient *mcc;

	sodict_search_t *bigDict; /**< big dict*/
    sodict_search_t *channel_detect_song_dict; /**< channel_detect_song_dict*/
    sodict_search_t *detect_judge_song_dict; /**< detect_judge_song_dict*/
    sodict_search_t *song_tag_dict; //歌曲标签字典
    sodict_build_t* blank_song_list; //全局过滤的黑名单
    sodict_search_t *channel_song_dict; //频道歌曲权值字典
    sodict_search_t *lr_feature_dict; //pcpr特征字典
    sodict_search_t *lr_model_dict; //pcpr模型字典
    sodict_search_t *y_channel_dict;//百度音乐人频道字典
    sodict_search_t *y_song_dict;//百度音乐人歌曲字典
    sodict_search_t *ticket_dict;//票务字典
    sodict_search_t *yyr_chsong_dict;//公共频道音乐人歌曲字典

	Song_item_t* songsonglist;/**< 歌关联歌曲数据buf */
	Singer_item_t* singersingerlist;/**< 关联歌手数据buf */
	Song_item_t* singersonglist;/**< 歌手关联歌曲数据buf */
	Song_brief_t* songbrieflist;/**< 歌曲详细信息buf */
	Singer_item_t* districtsingerlist;/**< 地区歌手buf */
	Song_item_t* defaultlist;/**< 默认列表buf */
    uint64_t* cold_start_singer_list; /*冷启动歌手列表*/
    ch_info_t* ch_info_list; /*频道信息列表*/
    song_id_t* ch_song_list; /*频道歌曲列表*/
    Song_item_t* public_rsong_list;/*公用频道歌曲的关联歌曲列表*/
    Song_item_t* public_rsingersong_list;/*公用频道歌手的关联歌曲列表*/
    song_id_t* insertsong_list;/*插入歌曲列表*/
    spread_song_t * spreadsong_list;//推广歌曲列表
    uint64_t *yyrchsong_list;//公共频道音乐人歌曲列表
    float* lrweight_list; //pcpr权值列表
    y_song_info* ysong_list;//百度音乐人歌曲列表
    song_id_t* ychannel_list;//百度音乐人频道列表
    Ticket_info_t* ticket_list; //票务数据列表
    tail_song_t* tail_song_list; //长尾好歌列表
    int * detectsong_list;/*试探歌曲列表*/    
    int * detectjudge_list;/*试探歌曲列表*/
    singer_id_t* ting_artist_id;/*ting歌手id映射*/
	uint max_soso_len;/**< 歌曲关联buf长度 */
	uint max_sisi_len;/**< 歌手关联buf长度 */
	uint max_siso_len;/**< 歌手关联歌曲buf长度 */
	uint max_songbrief_len;/**< 歌曲详细信息buf长度 */
	uint max_districtsinger_len;/**< 歌手地区buf长度 */
	uint defaultlist_num; /**< 冷启动列表长度*/
    uint cold_start_singer_len; /*冷启动歌手的长度*/
    uint max_chinfolist_len; /*频道列表的最大长度*/
    uint max_chsonglist_len; /*频道歌曲的最大长度*/
    uint max_publicrsong_len; /*公用频道关联歌曲的最大长度*/
    uint max_publicrsingersong_len; /*公用频道歌手的关联歌曲列表最大长度*/
    uint ting_artist_id_len; /*ting_artist_id的长度*/
    uint max_insertsong_len; /*插入歌曲最大长度*/
    uint max_channel_detect_song_len; /*试探歌曲最大长度*/
    uint max_detectjudge_song_len; /*判断试探歌曲最大长度*/
    uint max_spreadsonglist_len; //推广歌曲最大长度
    uint max_yyrchsonglist_len;//公共频道音乐人歌曲最大长度
    uint max_lrweight_list_len; //lrweigh_list最大长度
    uint max_tail_song_list_len; //tail_song_list最大长度
    uint max_ysong_list_len;//百度音乐人歌曲最大长度
    uint max_ychannel_list_len;//百度音乐人频道列表最大长度
    uint max_ticket_list_len; //票务数据最大长度

    bsl::hashmap<uint64_t, uint64_t> quku_ting_artistid;/*quku和ting的歌手id映射*/
    ub::UbClientManager ubmgr; /*ubmgr*/
    bsl::hashmap<std::string, int> recommend_channel;/*存储推荐策略列表*/
    bsl::hashmap<std::string, instant_init> detect_channel;/*存储即时策略列表, key为频道名，value为初始化值*/
    //bsl::hashmap<std::string, int> detect_channel;/*存储即时策略列表*/
    bsl::hashmap<int, fuse_init> user_list_pair;//user pair, r_type与method、rate的对应关系
    bsl::hashmap<int, int> i_brief_lan;//即时推荐时语言分类对应关系
    bsl::hashmap<int, int> i_brief_year;//即时推荐时语言分类对应关系
    bsl::hashmap<int, int> i_brief_area;//即时推荐时语言分类对应关系
    bsl::hashmap<int, int> i_brief_gender;//即时推荐时语言分类对应关系
    bsl::hashmap<uint32_t, bsl::hashmap<std::string, float> > songs_attrs;//歌曲属性表


} Global_t;


//#define MAX_BIGLIST_SIZE 1000
//typedef struct _User_data_t
//{
//	int len_biglist;
//	Song_item_t biglist[1000];
//	int len_smalllist;
//};

/***********globlevar***************/
//extern ul_logstat_t g_log_stat;
/**< 全局数据结构 */
extern Global_t p_global;
//extern LogConf_t     LogConf;
/**< 全局ependingpool */
extern ependingpool g_svr_pool;
/**< 全局命令数据结构 */
extern Svr_buf_t* td;

/*********************************/
/**
 * @brief exit
 */
void myExit(int ret);


#endif /* _RLS_H_ */
