//============================================================================
// @author      : weijingqi (weijingqi@baidu.com)
// @file        : rls_struct.h
// @date        : 13 May 2012,13:08:23
// @copyright   : 2011 Baidu.com, Inc. All Rights Reserved
// @encoding    : 
// @version     : 
// @brief       : 结构体的定义
//============================================================================

#ifndef _RLS_STRUCT_H
#define _RLS_STRUCT_H
#include "rls.h"
#include "dao.h"
#include <ctime>
#include <bsl/pool.h>
/**< 用户线程数据buf */
typedef struct _u_worker_buf_t
{
	//<临时变量还有这指针
	/**< 存放线程的内存池的临时指针,在开始工作前被复制，在工作结束后被置NULL。永远不要free*/
	bsl::mempool &pool;
	int tid;/**<线程号*/
	idl::cmd* p_cmd; /** 存放线程命令的临时指针, */
	Svr_thread_data_t* p_thread_buf;/**< 线程数据指针 */
	uint uid;
} User_worker_buf;

//列表生成索引结构
/**< 列表生成索引结构 */
typedef struct _index_type_t_
{
	uint itemid; /**< 物体id */
	int type;/**< 类型0 song 1 singer */
	int weight;/**< 权重 */
	Song_item_t *pos;/**< 链表指针 */
	int len;/**< 链表长度 */
	int index;/**< 链表位置 */
} Index_type_t;

/*基本分类降权的结构体*/
typedef struct _de_weight_t{
    bool de_lan;    //是否语言降权
    uint lan;       //语言编号
    bool de_pv;     //是否PV降权
    uint pv;        //PV编号
    bool de_year;   //是否年代降权
    uint year;      //年代编号
}de_weight_t;

/*基本即时行为分类权值处理的结构体*/
typedef struct _i_weight_t{
    bool lan_flag;    //是否语言降权
    int lan_de;       //降权语言编号
    int lan_up;      //提权语言编号
    bool year_flag;    //是否年代降权
    int year_de;       //降权年代编号
    int year_up;      //提权年代编号
    bool area_flag;    //是否地区降权
    int area_de;       //降权地区编号
    int area_up;      //提权地区编号
    bool gender_flag;    //是否性别降权
    int gender_de;       //降权性别编号
    int gender_up;      //提权性别编号    
}i_weight_t;

typedef struct _action_record_t{
    uint bad_action_cnt; //负反馈的行为个数
    time_t bad_min_time; //负反馈的最小时间
}action_record_t;

/*推荐时用到的用户数据*/
typedef struct _r_userdata_t{
    Item_bean songlove[MAX_PREF_ITEM_NUM];
    int len_songlove;
    time_t maxtime_songlove;
    Item_bean songhate[MAX_PREF_ITEM_NUM];
    int len_songhate;
    time_t maxtime_songhate;
    Item_bean songcloud[MAX_PREF_ITEM_NUM];
    int len_songcloud;
    time_t maxtime_songcloud;
    Item_bean listenhistory[MAX_LISTENED_ITEM_NUM];
    int len_listenhistory;
    time_t maxtime_listenhistory;
    Action_bean action[MAX_ACTION_ITEM_NUM];
    int len_action;
    time_t maxtime_action;
    time_t maxtime_all;
    bool isset; //是否设置过数据
}r_userdata_t;

//百度音乐人用户数据
typedef struct  _y_user_data_t
{
    Action_bean y_user_behavior[MAX_Y_USER_BEHAVIOR_NUM];
    int len_y_user_behavior;
    bool isset;
}y_user_data_t;

/*即时即时行为建模的用户模型数据结构*/
typedef struct _instant_model_t{
    int dim_type; //需要建模的维度
    int dim_det; //需要试探的维度
    int dim_len; //总维度数
    int dim_lan_len;//语言建模类数
    int dim_lan[DIM_LAN_NUM];//对语言的建模（国语,粤语,英语,日语,韩语）=>(0,1,2,3,4)
    int dim_year_len;//年代建模类数
    int dim_year[DIM_YEAR_NUM];//对年代的建模(81-90,91-99,01-0,07-10,11到现在)=>(0,1,2,3,4)
    int dim_area_len;//地区建模类数
    int dim_area[DIM_AREA_NUM];//地区(大陆，港台)=>(0,1)
    int dim_gender_len;//语言建模类数
    int dim_gender[DIM_GENDER_NUM];//性别(男，女，组合)=>(0,1,2)
    bool is_new;//新用户判断
    bool isset; //是否设置过数据
}instant_model_t;

/*即时用户行为建模时用到的用户数据结构*/
typedef struct _i_userdata_t{
    Item_bean songlove[MAX_PREF_ITEM_NUM];
    int len_songlove;
    Item_bean songhate[MAX_PREF_ITEM_NUM];
    int len_songhate;
    Item_bean songcloud[MAX_PREF_ITEM_NUM];
    int len_songcloud;
    Item_bean listenhistory[MAX_LISTENED_ITEM_NUM];
    int len_listenhistory;
    Action_bean action[MAX_ACTION_ITEM_NUM];
    int len_action;
}i_userdata_t;

//区间内歌手id对应的个数
typedef struct _singer_record_t_{
    int index[MAX_USER_LIST_LEN];
    int len;
}singer_record_t;

//区间歌手去重队列
typedef struct _singer_queue_t{
    uint singers[MAX_USER_LIST_LEN];
    int tail;
    int head;
}singer_queue_t;

//平滑歌曲维度信息
typedef struct _smooth_dim_t{
    int lan;//语言
    int year;//年代
    int year_num;    
    int pitch;//音调
    int pitch_num;    
    int tune;//节奏
    int tune_num;
}smooth_dim_t;

//平滑歌曲数据
typedef struct _smooth_data_t{
    uint song_id;//歌曲id
    int distance;//偏移距离
}smooth_data_t;

//票务推荐结构
typedef struct _ticket_rec_t{
    int ticket_id;
    int weight;
    int source;
}Ticket_rec_t;

/**
 * @brief tinyse统一的命令接口
 *   
 *   +-------+------------------------+-------------------+
 *   |nshead | 定长部分 ts_head_t     |  变长部分mcpack   |
 *   +-------+------------------------+-------------------+
 */
typedef struct ts_head_t{
    uint32_t cmd_no;                         /**< 命令号     */
    uint32_t err_no;                         /**< 错误号     */
    char data_type[64];    /**< 数据类型      */
    uint32_t page_no;                        /**< 页号      */
    uint32_t num_per_page;                   /**< 每页显示条数       */
    uint32_t ret_num;                        /**< 返回个数      */
    uint32_t disp_num;                       /**< 总共查询到的个数      */
}ts_head_t;

#endif /* _RLS_STRUCT_H */

