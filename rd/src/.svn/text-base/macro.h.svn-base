/**
 * =====================================================================================
 *
 *	Filename:  macro.h
 *
 *	Description:  header file for macro.cpp
 *
 *	Version:  1.0
 *  Created: 2010-11-24
 *	Revision:  none
 *	Compiler:  gcc
 *
 *	Author:  zhangjunying, zhangjunying@baidu.com
 *	Company:  baidu.com Inc.
 *
 * =====================================================================================
 */

#ifndef _MACRO_H_
#define _MACRO_H_

#define SVR_VERSION "1.0.4.0" /**< 版本 */

#define MAX_DIR_LEN                1024    /**<最大路径长度*/
#define LINK_STR_LEN               1024    /**<url串最大长度*/
#define SITE_STR_LEN               128     /**< 站点名最大长度 */
#define MAX_PORT_VALUE 						65535    /**< 端口号的最大值 */
/**< 默认mcpack长度 */
#define DEFAULT_MCPACK_LEN  500*1024
/**<默认可以buff用户行为数*/
#define DEFAULT_BUF_LEN 60
/**< 用户名最大长度 */
#define MAX_USRNAME_LEN	64
/**< reload监听队列产长度 */
#define DEFAULT_RELOAD_LISTENNUM 10
//歌手的歌曲补充循环次数
#define REPLACE_SONG_LOOP 200
/**< 最大的喜好数据数据长度 */
#define MAX_PREF_ITEM_NUM 500
/**< 最大的收听数据长度 */
#define MAX_LISTENED_ITEM_NUM 500
//单类用户行为最大长度
#define MAX_ACTION_NUM_PER_TYPE 250
//音乐盒行为最大长度
#define MAX_BOX_ACTION_NUM 500

//百度音乐人行为最大长度
 #define MAX_Y_USER_BEHAVIOR_NUM 500

/**< 最大的行为数据长度 */
#define MAX_ACTION_ITEM_NUM 1000
/**< 最大的用户列表数据长度 */
#define MAX_USER_LIST_LEN 200
/**< 最大的即时用户列表请求的数据长度 */
#define MAX_INSTANT_LIST_LEN 100
//即时新用户列表取top歌曲数
#define NEW_INSTATNT_LIST_LEN 200
//即时新老用户判断域值
#define NEW_INSTANT_USER_LIMIT 25
//即时频道，列表头shuffle长度
#define INSTANT_SHUFFLE_HEAD_LEN 10

//最小列表长度
 #define MIN_USER_LIST_LEN 25

/*分析数据的最大长度*/
#define MAX_ANALYS_LEN 100
/**分析数据各类*/
#define ANALYS_CLASS_NUM 6
/*随机补充列表时多出的个数，避免重复后个数不够,生成的随机数为需要的个数+多出个数*/
#define EXTEND_RANDOM_LEN 50

/**< 歌曲随机的topn */
#define SONG_RAND_TOPN 20
/**< 歌手随机的topn */
#define SINGER_RAND_TOPN 3
/**< 最大列表权重 */
#define MAX_WEIGHT 100
 /**用户模型中标签最大权值*/
#define MAX_UTAG_WEIGHT 100
/*列表最小权重*/
#define MIN_WEIGHT 0
/*索引的最大权重*/
#define MAX_INDEX_WEIGHT 100
/*索引的最小权重*/
#define MIN_INDEX_WEIGHT -100
/**< 最大的百分比 */
#define MAX_PERCENT 100
/**< 最大的天数 */
#define MAX_DAY 50
/**< 最大的次数 */
#define MAX_NUM 30
/**< 权值的天数衰减率 */
#define REDUCE_RATE_DAY 1
/**< 权值的次数衰减率 */
#define REDUCE_RATE_NUM 0.75
/**ral, um, uc列表最大长度*/
#define CF_LIST_MAX_LEN 200
/**ral, random列表最大长度*/
#define RANDOM_LIST_MAX_LEN 300
/***USER CF TYPE */
#define USER_CF_TYPE 2
/****ITEM CF TYPE */
#define ITEM_CF_TYPE 1
 /***UM TYPE */
#define UM_TYPE 3
 /***UC TYPE */
#define UC_TYPE 4
/****融合列表数 */
#define FUSE_LIST_NUM 9
/**< 跳过分析的长度 */
#define JUMP_ANALYSIS_LEN 5
/**< 跳过分析的最长时间 */
#define JUMP_ANALYSIS_TIME 12*60*60
/**< 最近跳过的时间要求 */
#define JUMP_LATEST_TIME 20*60
 /**< 最近即时行为跳过的时间要求 */
#define JUMP_INSTANT_LATEST_TIME 5*60
/**< 跳过降权的阈值 */
#define JUMP_DEWEIGHT_LEVEL 3
/**< 跳过降权的降权百分比 */
#define JUMP_DEWEIGHT_PERCENT 50
/**< 跳过过滤的时间 */
#define JUMP_FILTER_TIME 24*60*60*14
/**< 收听过滤的时间 */
#define LISTEN_FILTER_TIME 24*60*60*7
/**< 喜好歌曲召回的阈值 */
#define LOVE_SONG_FIND_TOPN_SINGER 2

/**< 过滤字典的hash大小 */
#define FILT_DICT_HASH 10000
/**< 默认列表召回时使用的随机数组的大小上限 */
#define MAX_DEFAULT_SHUFFLE_RANG 10000
/**/
#define PLAYSONG_PAGE_TYPE  4
/**< 数据库用户偏好枚举值 */
enum DB_PREF_TYPE {
	DB_SONGLOVE=0,/**< 加心歌曲 */
	DB_SONGHATE=1,/**< 垃圾桶歌曲 */
	DB_SINGERLOVE=2,/**< 加心歌手 */
	DB_SINGERHATE=3,/**< 垃圾桶歌手 */
	DB_SONGCLOUD=4,//云收藏歌曲
};

/**< 即时用户模型维度表示枚举值 */
enum I_DIM_TYPE {
	I_LAN_DIM=0,/**< 语言 */
	I_YEAR_DIM=1,/**< 年代 */
	I_AREA_DIM=2,/**< 地区 */
	I_GENDER_DIM=3,/**< 性别 */
};

/**< 数据库删除标志 */
enum DB_DEL_TYPE {
	DB_DELETE=0,/**< 删除数据 */
	DB_VALID=1,/**< 有效数据 */
};

/**< Cache类型枚举值 */
enum CACHE_TYPE {
	LISTEN_TOTAL_NUM=1,/**< 收听总数Cache */
};

/**< 字典类型枚举值 */
enum DICT_TYPE {
	SONG_SONG_DICT=1,/**< 相关歌曲字典 */
	SINGER_SINGER_DICT=2,/**< 相关歌手字典 */
	SINGER_SONG_DICT=3,/**< 歌手相关歌曲字典 */
	SONG_BRIEF=4,/**< 歌曲信息字典 */
	DISTRICT_SINGER=5,/**< 歌手地区字典 */
    CHANNEL_LIST_DICT = 6, /*频道列表字典*/
    CHANNEL_SONG_DICT = 7, /*频道歌曲字典*/
    INSERT_SONG_DICT = 8, /*插入歌曲字典*/
    SPREAD_SONG_DICT = 9, //推广歌曲字典
};

/**< 用户行为类型枚举值 */
enum DIANTAI_USER_BEHAVIOR_TYPE {
	PRE_SONG=1,/**< 上一首 */
	NEXT_SONG=2,/**< 下一首 */
	COMPLETE_SONG=3,/**< 完整试听 */
	LOVE_SONG=4,/**< 加心歌曲 */
	CANCLE_LOVE_SONG=5,/**< 取消加心歌曲 */
	HATE_SONG=6,/**< 垃圾桶歌曲 */
	CANCLE_HATE_SONG=7,/**< 取消垃圾桶歌曲 */
	LOVE_SINGER=8,/**< 加心歌手 */
	CANCLE_LOVE_SINGER=9,/**< 取消加心歌手 */
	HATE_SINGER=10,/**< 垃圾桶歌手 */
	CANCLE_HATE_SINGER=11,/**< 取消垃圾桶歌手 */
    BPR_NEXT_PAGE=14,/**<bpr pair>*/
};

/**< 数据库用户行为枚举值 */
enum DB_USER_BEHAVIOR_TYPE {
    DB_FM_LISTENEND_TYPE=0,//电台听完歌曲权重,不存在behavior表中，存在 listenhistory表中
	DB_BOX_COMPLETE_TYPE=5,/**< 音乐盒完整听完 */
	DB_PRE_SONG=6,/**< 上一首 */
	DB_NEXT_SONG=7,/**< 下一首 */
	DB_SEARCH_SONG=12, //音乐盒搜索歌曲
};

/**< 歌曲状态 */
enum SONG_STATUS_TYPE {
	NONE_STATUS =0,/**< 无状态 */
	LOVED_SONG = 1,/**< 标记喜欢歌曲 */
	LOVED_SINGER = 2,/**< 标记喜欢歌手 */
	LOVED_BOTH = 3,/**< 标记喜欢歌手和歌曲 */
};

enum DATA_DB_TYPE {
	DB_HISTORY_TYPE =0,//登陆用户试听历史
	DB_CO_HISTORY_TYPE = 1,//cookie用户
	DB_BEHAVIOR_TYPE = 2,//登陆用户行为
	DB_CO_BEHAVIOR_TYPE = 3,//cookie用户
	DB_CO_LOVE_SONG_TYPE = 4,//cookie用户喜好数据，喜欢歌曲
	DB_CO_HATE_SONG_TYPE = 5,//cookie用户喜好数据，不喜欢歌曲
	DB_CO_LOVE_SINGER_TYPE = 6,//cookie用户喜好数据，喜欢歌手
	DB_CO_HATE_SINGER_TYPE = 7,//cookie用户喜好数据，不喜欢歌手
};


enum rls_source_e{
    RLS_SOURCE_MP3 = 1, //来源mp3
    RLS_SOURCE_TING = 2, //来源ting
    RLS_SOURCE_ALL = 0,//全部
};

//source的sql条件长度
#define SOURCE_SQL_LEN 20

//user_list中标签的类型
#define TAG_LIST_TYPE 11
//标签名的最大长度
#define USER_TAG_LEN 100
//最大标签数
#define USER_TAG_NUM 30

#endif /* _MACRO_H_ */
