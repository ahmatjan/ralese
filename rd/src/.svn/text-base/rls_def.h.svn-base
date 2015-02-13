//============================================================================
// @author      : weijingqi (weijingqi@baidu.com)
// @file        : rls_def.h
// @date        : 13 May 2012,13:09:08
// @copyright   : 2011 Baidu.com, Inc. All Rights Reserved
// @encoding    : 
// @version     : 
// @brief       : 常量的定义 
//============================================================================

#ifndef _RLS_DEF_H
#define _RLS_DEF_H


namespace rls{

    /*函数执行状态返回值*/
    enum rls_method_return_e{
        SUCCESS = 0, //成功
        FAIL = -1, //失败
        NOEXIST = -2, //不存在
    };
    enum rls_item_type_e{
        ITEM_TYPE_SONG = 0, //歌曲
        ITEM_TYPE_SINGER = 1, //歌手
    };
    /*获取request的为空时的间隔数, 1/1000秒*/
    const int GET_REQUEST_USLEEP = 1000;
    /*每个兴趣点最多推荐结果个数，避免兴趣点少的用户推荐过于集中*/
    const int MAX_R_PER_ITEM = 3;
    /*数组的最大长度*/
    const int MAX_ARR_LEN = 1000;
    /*最大的收藏歌曲长度*/
    const int MAX_LOVESONG_LEN = 1000;
    /*频道名字的最大长度*/
    const int MAX_CHNAME_LEN = 50;
    /*BPR LOG 歌曲ID最大长度*/
    const int MAX_BPR_LOG_IDS = 100;
    /*连接和读取的超时时间，s*/
    const int CWR_TIMEOUT = 1;
    /*含推荐策略的频道最大个数*/
    const int MAX_RECOMMEND_CHANNEL_LEN = 20;
    /*含即时推荐策略的频道最大个数*/
    const int MAX_DETECT_CHANNEL_LEN = 20;
    /*缓存歌曲属性列表的hash字典的初始大小*/
    const int INIT_SONG_ATTR_DICT_LEN = 10000;
    /*最大的算法列表个数*/
    const int MAX_USER_LIST_PAIR_LEN = 10;
    /*即时行为建模维度下分类的最多个数*/
    const int MAX_INSTANT_DIM_CLASS_LEN = 100;
    /*即时维度分类编号的最大位数*/
    const int MAX_DIM_BIT_LEN = 4;
    /*百度id字符串最大长度*/
    const int MAX_BAIDUID_LEN = 40;
    /*百度cookie的字符串长度*/
    const int BAIDUID_LEN = 32;
    /*频道描述的最大长度*/
    const int MAX_CHDESC_LEN = 100;
    /*频道图片最大长度*/
    const int MAX_CHCOVER_LEN = 200;
    /*用户中心的IP最大个数*/
    const int MAX_USCIPPORT_LEN = 10;
	//mcc cache的key的最大长度
	const int MAX_MCC_KEY_LEN = 100;
    //redis sign的最大长度
    const int MAX_REDIS_SIGN_LEN = 128;
	/*IP端口字符串的最大长度*/
    const int MAX_IPPORT_LEN = 20;
    //cache前缀的最大长度
	const int MAX_CACHE_PRE_LEN = 20;
	//即时行为的天数
    const int INSTANT_DAYS = 15;
    /*所有频道分类名字的标识*/
    const char CATE_ALL_NAME[] = "all";
    /*随便听听频道的名字标识*/
    const char CH_SUIBIANTINGTING_NAME[] = "public_tuijian_suibiantingting";
    /*用户中心连接重试次数*/
    const int USC_CONN_RETRY_CNT = 5;
    /*私人频道名字标识*/
    const char CH_PRIVATE_NAME[] = "private";
    /*私人频道的中文名字*/
    const char CH_PRIVATE_SNAME[] = "私人频道";
    /*华语频道*/
    const char CH_HUAYU_NAME[] = "public_yuzhong_huayu";
    /*80s频道*/
    const char CH_80S_NAME[] = "public_shiguang_80hou";
    /*个性化频道排序*/
    const char CH_PERSONAL_NAME[] = "personal";
    /*红心频道*/
    const char CH_LOVESONGS_NAME[] = "lovesongs";
    /*红心频道中文名*/
    const char CH_LOVESONGS_SNAME[] = "红心频道";
    /*歌手频道前缀*/
    const char CH_ARTIST_PRE[] = "public_artist_";
    /*歌手频道前缀长度*/
    const int CH_ARTIST_PRE_LEN = 14;
    /*标签频道前缀*/
    const char CH_TAG_PRE[] = "public_tag_";
    /*标签频道前缀的长度*/
    const int CH_TAG_PRE_LEN = 11;
    //百度音乐人频道前缀
    const char CH_Y_PRE[] = "public_y_";
    //百度音乐人频道前缀长度
    const int CH_Y_PRE_LEN = 9;
    //ldac BIGPIPE TAG名
    const char BIGPIPE_LDAC_TAG[] = "ldac";
    //bpr BIGPIPE TAG名
    const char BIGPIPE_BPR_TAG[] = "bprpair";
    /*第一档pv标识*/
    const int FIRST_PV_FLAG = 1;
    /*第二档pv*/
	const int SECOND_PV_FLAG = 2;
	/*第三档pv*/
	const int THIRD_PV_FLAG = 3;
	/*lan pv year 不存在时的默认值*/
	const int INT_NONE = -1;
	/*零分时的基准分数*/
    const int BASE_SCORE = 5;
    /*即时行为建模推荐时，保留有序的top歌曲数*/
    const int BASE_INSTANT_NUM = 50;
    /*用户中心请求个数*/
    const char USC_PREF_REQUEST_FORMAT[] = "%s/index.php?cmd_no=%d&baidu_id=%u&item_type=%d&total=%d&cloud_type=0&start=%d&size=%d&from=fm.baidu&time=%d";
    /*用户中心请求格式2*/
    const char USC_PREF_REQUEST_FORMAT2[] = "%s/index.php?cmd_no=%d&baidu_id=%u&item_type=%s&size=%d&from=fm.baidu";
    /*用户中心请求格式3*/
    const char USC_PREF_REQUEST_FORMAT3[] = "%s/index.php?cmd_no=%d&baidu_id=%u&item_type=%s&from=fm.baidu";
    /*用户中心写请求格式*/
    const char USC_WRITE_PREF_REQUEST_FORMAT[] = "%s/index.php?cmd_no=%d&baidu_id=%u&item_type=%d&item_id=%u&from=fm.baidu";
    /*标签检索指令号*/
    const int TAG_CMD_NO = 100003;
    /*标签检索kit*/
    const char TAG_KIT[] = "tagkit";
    /*标签检索服务*/
    const char TAG_SERVICE[] = "tagservice";
    /*标签检索开始页码*/
    const int TAG_START_PAGE_NO = 0;
    /*收藏列表的请求*/
    const int USC_PREF_CMD_NO = 21000;
    /*电台垃圾桶列表请求*/
    const int USC_DIANTAI_HATE_CMD_NO = 20012;
	/* 用户中心云列表，带时间 */
	const int USC_CLOUD_TIME_CMD_NO = 20008;
	/*用户中心云数据*/
	const int USC_CLOUD_CMD_NO = 20004;
	/*所有喜好数据的总数*/
    const int USC_ALL_PREF_COUNT_CMD_NO = 20015;
    /*用户中心喜欢歌曲*/
    const int USC_PREF_TYPE_LSONG = 1;
    /*用户中心不喜欢歌曲*/
    const int USC_PREF_TYPE_HSONG = 2;
	/* 用户中心云歌曲 */
    const int USC_CLOUD_TYPE_SONG = 1;
    /*用户中心电台收藏和垃圾桶总数后缀参数*/
    const char USC_LOVE_HATE_PREF_ITEM_TYPE[] = "1,2";
    /*用户中心开始*/
    const int USC_START = 0;
    /*用户中心需要总数*/
    const int USC_NEED_TOTAL = 1;
    /*用户中心不需要总数*/
    const int USC_NOTNEED_TOTAL = 0;
    /*url的最大长度*/
    const int MAX_URL_LEN = 150;
    /*用户中心返回的数据长度*/
    const int MAX_USC_RESP_LEN = 1024*400;
    /*用户中心返回成功*/
    const int USC_RESP_OK = 22000;
    const int USC_RESP_OK2 = 0;
    //即时行为推荐歌曲的默认权值
    const int DEFAULT_INSTANT_SONG_WEIGHT = 30;
    //有效兴趣点歌曲数控制
    const int VALID_RELATION_SONG_NUM = 3;
    //算法标记
    //无来源
    const unsigned int DEFAULT_SOURCE = 0;
    //mmb来源 
    const unsigned int MMB_SOURCE = 0X00FF;
    //item cf来源,256
    const unsigned int ITEMCFLIST_SOURCE = 0X0100; 
    //user-cf来源,512
    const unsigned int USERCFLIST_SOURCE = 0X0200;
    //即时行为建模来源,1024
    const unsigned int INSTANT_SOURCE = 0X0400;
    //用户模型列表来源,2048
    const unsigned int USERMODELLIST_SOURCE = 0X0800;
    //用户聚类来源,4096
    const unsigned int USERCLUSTERLIST_SOURCE = 0X1000;
    //用户模型调权来源,8192
    const unsigned int USERMODEL_SOURCE = 0X2000;
    //新用户标记,16384
    const unsigned int NEWUSER_SOURCE = 0X4000;
    //特意标记来源,1073741824
    const unsigned int FLAG_SOURCE = 0X40000000;
    //长尾歌曲来源
    const unsigned int TAIL_SOURCE = 0X10000;
    //ldac 来源标记,131072
    const unsigned int LDAC_SOURCE = 0X20000;
    //bpr 来源标记,131072 * 2
    const unsigned int BPR_SOURCE = 0X40000;
    //随机歌曲来源, 524288
    const unsigned int RANDOM_SOURCE = 0X80000;
    //音乐人歌曲来源, 524288 * 2
    const unsigned int YYR_SOURCE = 0x100000;
    //私人频道新用户试听历史数判断
    const unsigned int NEW_USER_HISTORY_NUM = 50;
    //年代倍率，将年代扩展10倍，以免计算浮点数
    const unsigned int YEAR_RATE = 10;
    //节奏倍率，将节奏扩展10倍，以免计算浮点数
    const unsigned int TUNE_RATE = 10;
    //平滑的维度无数据的距离定义
    const unsigned int UNKNOWN_DISTANCE = 50;
    //平滑是的度有数据的距离定义
    const unsigned int KNOWN_DISTANCE = 50;
    /*返回列表时的歌曲状态*/
    typedef enum RESP_SONG_STATUS{
        RESP_NONE_STATUS = -1,
        RESP_SONGLOVE_STATUS = 0,
    };

    //建模长度
    const unsigned int DIM_LEN = 4;
    //语言的维数
    const unsigned int DIM_LAN_NUM = 3;
    //年代的维数
    const unsigned int DIM_YEAR_NUM = 5;
    //地区的维数
    const unsigned int DIM_AREA_NUM = 2;
    //性别的维数
    const unsigned int DIM_GENDER_NUM = 3;
    //pcpr的特征歌曲数
    const unsigned int FEATURE_SONG_NUM = 1000;
    //pcpr的特征数，歌曲数的3位
    const unsigned int FEATURE_NUM = 3000;
    //pcpr置信度值
    const unsigned int PCPR_CONFIDENCE = 400;
    //用户实时数据长度
    const unsigned int MAX_USER_INSTANT_BEHAVIOR_NUM = 20;
    //长尾歌曲随机取歌曲数
    const unsigned int RAN_TAIL_NUM = 100;

    //redis ldac tag
    const char LDAC_REDIS_TAG[] = "rlist";//由于刚开始没设计好所以沿用rlist,实际应该是ldac
    //reids bpr-pair tag
    const char BPR_REDIS_TAG[] = "bpr";
    //redis algrithm list field
    const char REDIS_LIST_FIELD[] = "rlist";
    //redis algrithm sign field
    const char REDIS_SIGN_FIELD[] = "sign";
    //random list
    const char RANDOM_LIST_REDIS_KEY[] = "diantai_hot_song";

    //百度音乐人的rf
    const unsigned int Y_RF = 3;
    //疲劳度控制值，天数比次数
    const unsigned int TIRE_DEGREE = 7;
    //最大票务长度
    const unsigned int MAX_TICKET_LEN = 25;
}


#endif /* _RLS_DEF_H */

