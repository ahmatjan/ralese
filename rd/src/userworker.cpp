/**
 * =====================================================================================
 *
 *	Filename:  userworker.cpp
 *
 *	Description:  header file for userworker.cpp
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

#include "rls.h"
#include "userworker.h"
#include "rls_piaohandler.h"
#include "rls_queryhandler.h"
#include "rls_y_playerhandler.h"
#include "rls_playerhandler.h"
#include "rls_uscgetter.h"
#include "rls_struct.h"
#include "rls_def.h"
#include "dao.h"
#include "bsl/exception.h"
#include "bsl/map.h"
#include "topn.h"
#include "shuffle.h"
#include "mcCache.h"
#include <algorithm>

using namespace rls;

int regenerateUserList(User_worker_buf& u_buf);
int handleCmd(User_worker_buf& u_buf, PiaoHandler& ph, QueryHandler *query_handler, PlayerHandler *player_handler, UscGetter* usc_getter, YPlayerHandler* y_player_handler);
idl::cmd* extractCmd(User_worker_buf& u_buf, bsl::mempool* pool);
void *userworker(void *arg);
int sendErrorStatus(User_worker_buf& u_buf, int status);
int handlePlayerCmd(User_worker_buf& u_buf);
int handleFoundCmd(User_worker_buf& u_buf);
int handleCntCmd(User_worker_buf& u_buf, UscGetter* usc_getter);
int handleListCmd(User_worker_buf& u_buf, UscGetter* usc_getter);
int hanldeOneActon(const idl::action& action, User_worker_buf& u_buf, bool need_modify_list);
int handle_pre_song(uint itemid, User_worker_buf& u_buf, bool need_modify_list);
int handle_complete_song(uint itemid, User_worker_buf& u_buf, bool need_modify_list);
int handle_next_song(uint itemid, User_worker_buf& u_buf, bool need_modify_list);
int handle_love_song(uint itemid, User_worker_buf& u_buf, bool need_modify_list);
int handle_common_cancle(uint itemid, enum DB_PREF_TYPE type, User_worker_buf& u_buf, bool need_modify_list);
int handle_hate_song(uint itemid, User_worker_buf& u_buf, bool need_modify_list);
int handle_love_singer(uint itemid, User_worker_buf& u_buf, bool need_modify_list);
int handle_hate_singer(uint itemid, User_worker_buf& u_buf,
    bool need_modify_list);

Song_item_t* song_topN_rand(Song_item_t *p_song_song, int song_song_len, User_worker_buf& u_buf, sodict_build_t *filt_dict);
Singer_item_t* singer_topN_rand(Singer_item_t *p_singer_singer, int singer_singer_len, User_worker_buf& u_buf, sodict_build_t *filt_dict);
inline bool filt_song(sodict_build_t* dict, uint songid);

int fill_filter_dict(User_worker_buf& u_buf, sodict_build_t* filter_dict);
inline bool isSenquenceJump(User_worker_buf& u_buf);

inline int prefIndexWeight(Item_bean *p_ref, int len_ref,
    enum DB_PREF_TYPE db_type, time_t max_time,
    sodict_build_t* lookup_dict, sodict_build_t* filter_dict,
    Index_type_t* p_index, int& index_size);
inline int actionIndexWeight(Action_bean* action, int len_action,
    time_t max_time, sodict_build_t* lookup_dict,
    sodict_build_t* filter_dict, Index_type_t* p_index, int& index_size);
/**
 * 歌曲权重比较函数
 */
inline bool song_item_weight_cmp(Song_item_t* const &a, Song_item_t* const &b)
{
  return a->weight > b->weight;
}

/**
 * 歌手权重比较函数
 */
inline bool singer_item_weight_cmp(Singer_item_t* const &a, Singer_item_t* const &b)
{
  return a->weight > b->weight;
}

/**
 * 列表权重比较函数
 */
inline bool list_item_weight_cmp(Song_item_t const &a, Song_item_t const &b)
{
  return a.weight > b.weight;
}

/**
 * ===================  FUNCTION list_cmp ==============================
 * @brief 根据成功率对选出来的结果进行快排
 * return -1 a排b前，1 a排b后
 * ===========================================================================
 */
//inline int list_cmp(const void *a, const void *b)
//{
//	Song_item_t *pa = (Song_item_t *)a;
//	Song_item_t *pb = (Song_item_t *)b;
//	if (pa->weight > pb->weight)
//	{
//		return -1;
//	}
//	else if (pa->weight < pb->weight)
//	{
//		return 1;
//	}
//	return 0;
//}

/**
 * ===================  FUNCTION list_cmp ==============================
 * @brief 根据成功率对选出来的结果进行快排
 * return true a排b前，false a排b后
 * ===========================================================================
 */
bool list_cmp(Song_item_t a, Song_item_t b)
{
  return a.weight > b.weight;
}

/**
 * ===================  FUNCTION singer com ==============================
 * @brief 根据成功率对选出来的结果进行快排
 * return -1 a排b前，1 a排b后
 * ===========================================================================
 */
//inline int singer_cmp(const void *a, const void *b)
//{
//	Singer_item_t *pa = (Singer_item_t *)a;
//	Singer_item_t *pb = (Singer_item_t *)b;
//	if (pa->weight > pb->weight)
//	{
//		return -1;
//	}
//	else if (pa->weight < pb->weight)
//	{
//		return 1;
//	}
//	return 0;
//}

/**
 * ===================  FUNCTION singer com ==============================
 * @brief 根据成功率对选出来的结果进行快排
 * return true a排b前，false a排b后
 * ===========================================================================
 */
bool singer_cmp(Singer_item_t a, Singer_item_t b)
{
  return a.weight > b.weight;
}


/**
 * 生成用户id签名
 * [IN]
 * 	cmd 命令指针
 * [OT]
 * 	sign1,sign2输出签名的指针
 *
 * return true成功 false失败
 */
//inline bool creatIdSign(idl::cmd* cmd, uint* sign1, uint* sign2)
//{
//	if(NULL == cmd || NULL == sign1 || NULL == sign2)
//	{
//		return false;
//	}
//	unsigned int usr_len=0;
//	const char* p_us = cmd->username(&usr_len);
//	if(usr_len >=MAX_USRNAME_LEN)
//	{
//		return false;
//	}
//	char user_buf[MAX_USRNAME_LEN];
//	snprintf(user_buf,sizeof(user_buf),"%s",p_us);
//	user_buf[MAX_USRNAME_LEN-1] = 0;
//	int ret = creat_sign_fs64(user_buf, usr_len, sign1, sign2);
//	if (ret != 1)
//	{
//		WARNING_LOG("create uid for username faild.[%d]", ret);
//		return false;
//	}
//	return true;
//}

/**
 * 查询歌曲关联歌曲
 */
int seek_song_song(uint itemid,Song_item_t **p, int*len)
{
  if(0 == itemid)
  {
    WARNING_LOG("error itemid[0]");
    return -1;
  }
  sodict_snode_t node;
  node.sign1 = itemid;
  node.sign2 = SONG_SONG_DICT;

  int ret = odb_seek_search(p_global.bigDict, &node);
  if (ret == ODB_SEEK_ERROR)
  {
    WARNING_LOG("seek bigDict faild[ret:%d][sign1:%u][sign2:%u]", ret, node.sign1, node.sign2);
    return -1;
  }
  if (ret == ODB_SEEK_FAIL)
  {
    TRACE_LOG("no matching found in bigDict[ret:%d][sign1:%u][sign2:%u]", ret, node.sign1, node.sign2);
    *p = NULL;
    *len = 0;
    return 0;
  }
  if (node.cuint1 + node.cuint2 > p_global.max_soso_len)
  {
    WARNING_LOG("bad pos[%u] len[%u] for song-song buf. max len[%u]",
        node.cuint1, node.cuint2, p_global.max_soso_len);
    return -1;
  }
  *p = p_global.songsonglist + node.cuint1;
  *len = node.cuint2;
  return 0;
}

/**
 * 查询歌手关联歌曲
 */
int seek_singer_song(uint itemid,Song_item_t **p, int*len)
{
  if(0 == itemid)
  {
    WARNING_LOG("error itemid[0]");
    return -1;
  }
  sodict_snode_t node;
  node.sign1 = itemid;
  node.sign2 = SINGER_SONG_DICT;

  int ret = odb_seek_search(p_global.bigDict, &node);
  if (ret == ODB_SEEK_ERROR)
  {
    WARNING_LOG("seek bigDict faild [ret:%d][sign1:%u][sign2:%u]", ret, node.sign1, node.sign2);
    return -1;
  }
  if (ret == ODB_SEEK_FAIL)
  {
    TRACE_LOG("no matching found in bigDict[ret:%d][sign1:%u][sign2:%u]", ret, node.sign1, node.sign2);
    *p = NULL;
    *len = 0;
    return 0;
  }
  if (node.cuint1 + node.cuint2 > p_global.max_siso_len)
  {
    WARNING_LOG("bad pos[%u] len[%u] for singer-song buf. max len[%u]",
        node.cuint1, node.cuint2, p_global.max_siso_len);
    return -1;
  }
  *p = p_global.singersonglist + node.cuint1;
  *len = node.cuint2;
  return 0;
}

/**
 * 查询歌手关联歌曲
 */
int seek_singer_singer(uint itemid,Singer_item_t **p, int*len)
{
  if(0 == itemid)
  {
    WARNING_LOG("error itemid[0]");
    return -1;
  }
  sodict_snode_t node;
  node.sign1 = itemid;
  node.sign2 = SINGER_SINGER_DICT;

  int ret = odb_seek_search(p_global.bigDict, &node);
  if (ret == ODB_SEEK_ERROR)
  {
    WARNING_LOG("seek bigDict faild [ret:%d][sign1:%u][sign2:%u]", ret, node.sign1, node.sign2);
    return -1;
  }
  if (ret == ODB_SEEK_FAIL)
  {
    TRACE_LOG("no matching found in bigDict[ret:%d][sign1:%u][sign2:%u]", ret, node.sign1, node.sign2);
    *p = NULL;
    *len = 0;
    return 0;
  }

  if (node.cuint1 + node.cuint2 > p_global.max_sisi_len)
  {
    WARNING_LOG("bad pos[%u] len[%u] for singer-singer buf.max len[%u]",
        node.cuint1, node.cuint2, p_global.max_sisi_len);
    return -1;
  }
  *p = p_global.singersingerlist + node.cuint1;
  *len = node.cuint2;
  return 0;
}

/**
 * 获取歌曲的歌手id
 */
inline uint get_singer_id(uint itemid)
{
  Song_brief_t* p = get_song_brief(itemid);
  if(NULL == p)
  {
    return 0;
  }
  return  p->singer_id;
}

/**
 * 对列表进行重排序,保证M首歌区中,不出现N个相同歌手的歌.
 */
int arrange_user_list(Song_item_t *p_userlist, int userlist_len,int M, int N)
{
  if(NULL == p_userlist)
  {
    WARNING_LOG("p_userlist is NULL");
    return -1;
  }

  if(userlist_len < 0)
  {
    WARNING_LOG("userlist_len[%d] < 0", userlist_len);
    return -1;
  }

  if(0 == userlist_len)
  {
    return 0;
  }

  if(N>=M)
  {
    TRACE_LOG("N[%d]>=M[%d] nothing need to do",N,M);
    return 0;
  }

  if(userlist_len > MAX_USER_LIST_LEN)
  {
    WARNING_LOG("userlist_len[%d] > MAX_USER_LIST_LEN[%d]", userlist_len, MAX_USER_LIST_LEN);
    return -1;
  }

  struct _inner_buf_t_
  {
    int index[MAX_USER_LIST_LEN];
    int pos;
    int len;
  };

  int ret=-1;
  _inner_buf_t_ swap_buf[MAX_USER_LIST_LEN];
  bzero(swap_buf, sizeof(_inner_buf_t_)*MAX_USER_LIST_LEN);
  int swap_len=0;
  int dest[MAX_USER_LIST_LEN];
  int dest_index=0;

  sodict_build_t *tempDict;
  tempDict = odb_creat(MAX_USER_LIST_LEN);
  if(!tempDict)
  {
    FATAL_LOG("create tmp dict faild");
    return -1;
  }

  sodict_build_t *singerDict = odb_creat(MAX_USER_LIST_LEN);
  if(!singerDict)
  {
    FATAL_LOG("create singerDict dict faild");
    return -1;
  }

  //先按照权重排序
  std::sort(p_userlist, p_userlist+userlist_len, list_cmp);
  //	qsort(p_userlist, userlist_len, sizeof(Song_item_t), list_cmp);

  uint singer_id;
  sodict_snode_t node;
  uint freq=0;
  int userlist_index=0;
  bool dest_filled = false;
  uint last_singer = 0;
  while (userlist_index < userlist_len)
  {
    dest_filled = false;
    freq = 0;
    if (last_singer)
    {
      node.sign1 = last_singer;
      node.sign2 = last_singer;
      ret = odb_seek(singerDict, &node);
      //error checking
      if (ODB_SEEK_OK == ret && (node.cuint1 >= MAX_USER_LIST_LEN
            || swap_buf[node.cuint1].pos >= swap_buf[node.cuint1].len
            || swap_buf[node.cuint1].pos >= MAX_USER_LIST_LEN
            || swap_buf[node.cuint1].len >= MAX_USER_LIST_LEN))
      {
        WARNING_LOG("singer dict data error");
      }
      else if (ODB_SEEK_OK == ret && node.cuint1 < MAX_USER_LIST_LEN
          && swap_buf[node.cuint1].pos < swap_buf[node.cuint1].len)
      {
        //found in swap buf
        dest[dest_index++]
          = swap_buf[node.cuint1].index[swap_buf[node.cuint1].pos++];
        dest_filled = true;
      }
    }

    while (!dest_filled && userlist_index < userlist_len)
    {
      //检查user_list
      singer_id = get_singer_id(p_userlist[userlist_index].song_id);
      node.sign1 = singer_id;
      node.sign2 = 0;

      ret = odb_seek(tempDict, &node);
      if (ret == ODB_SEEK_OK)
      {
        freq = node.cuint1;
      };

      if (freq <= (uint) N)
      {
        //put into the dest buf.
        dest[dest_index++] = userlist_index;
        node.cuint1 = ++freq;
        node.cuint2 = 0;
        if (odb_add(tempDict, &node, 1) == ODB_ADD_ERROR)
        {
          WARNING_LOG("add the singer info into dict failed");
        }
        dest_filled = true;
      }
      else
      {
        // put into the swap buf
        node.sign1 = singer_id;
        node.sign2 = singer_id;
        ret = odb_seek(singerDict, &node);
        //error checking
        if (ODB_SEEK_OK == ret && (node.cuint1 >= MAX_USER_LIST_LEN
              || swap_buf[node.cuint1].pos > swap_buf[node.cuint1].len
              || swap_buf[node.cuint1].pos >= MAX_USER_LIST_LEN
              || swap_buf[node.cuint1].len >= MAX_USER_LIST_LEN))
        {
          WARNING_LOG("singer dict data error");
        }
        else if (ODB_SEEK_OK == ret && node.cuint1 < MAX_USER_LIST_LEN
            && swap_buf[node.cuint1].len < MAX_USER_LIST_LEN)
        {
          swap_buf[node.cuint1].index[swap_buf[node.cuint1].len++] = userlist_index;
        }
        else if(swap_len < MAX_USER_LIST_LEN)
        {
          swap_buf[swap_len].index[0] = userlist_index;
          swap_buf[swap_len].pos = 0;
          swap_buf[swap_len].len = 1;
          node.cuint1 = swap_len;
          node.cuint2 = 0;
          ret = odb_add(singerDict, &node, 1);
          if(ret != ODB_ADD_OK)
          {
            WARNING_LOG("add singer index into singer dict faild.[%d]",ret);
          }
          ++swap_len;
        }
      }
      ++userlist_index;
    }

    if(dest_filled && dest_index>= M)
    {
      singer_id = get_singer_id(p_userlist[dest[dest_index - M]].song_id);
      node.sign1 = singer_id;
      node.sign2 = 0;
      ret = odb_seek(tempDict, &node);
      if (ret == ODB_SEEK_OK)
      {
        --node.cuint1;
        if (odb_add(tempDict, &node, 1) == ODB_ADD_ERROR)
        {
          WARNING_LOG("add the singer info into dict failed");
        }
      };
      last_singer = singer_id;
    }
  }

  //put rest swap buf into dest
  for(int i =0; i < MAX_USER_LIST_LEN; ++i)
  {
    while (swap_buf[i].pos < swap_buf[i].len && swap_buf[i].len
        <= MAX_USER_LIST_LEN)
    {
      dest[dest_index++] = swap_buf[i].index[swap_buf[i].pos++];
    }
  }

  //put the arranged list back.
  Song_item_t tmp_buf[MAX_USER_LIST_LEN];
  memcpy(tmp_buf,p_userlist, sizeof(Song_item_t)*userlist_len);
  for(int i = 0 ;i < dest_index; ++i)
  {
    memcpy(p_userlist+i, tmp_buf+dest[i],sizeof(Song_item_t));
  }

  if (tempDict)
  {
    odb_destroy(tempDict);
  }
  if (singerDict)
  {
    odb_destroy(singerDict);
  }
  return 0;
}

/**
 * @brief 用户处理数据线程函数
 * @param arg :线程id
 * @return
 */
void *userworker(void *arg)
{
  time_t t;
  time(&t);
  int tid = (int)(long)arg;
  int newusr = 0;
  int ret;
  struct timeval s;
  struct timeval e;
  bsl::xcompool pool;
  idl::cmd *clientCmd =NULL;
#ifdef _DEBUG_TIME
  struct timeval tv;
#endif
  QueryHandler* query_handler = new QueryHandler();
  PlayerHandler* player_handler = new PlayerHandler();
  UscGetter* usc_getter = new UscGetter();
  YPlayerHandler* y_player_handler = new YPlayerHandler();

  PiaoHandler piao_handler;

  Svr_buf_t *s_buf = &td[tid];
  ret = com_openlog_r();
  if (ret < 0){
    fprintf(stderr, "[Fatal Error] open log in thread userworker(%d) fail!\n", tid);
    return NULL;
  }
  TRACE_LOG("userworker[%d] begin:%s\n",tid, ctime(&t));

  User_worker_buf u_buf={pool,tid,NULL,NULL,0};
  Svr_thread_data_t thread_data;
  //读固定threadid对应td buff，处理请求
  while(1){
    u_buf.p_cmd = NULL;
    u_buf.p_thread_buf = NULL;
    u_buf.uid = 0;
    if (s_buf->svr_data->empty()){//队列是空
      usleep(GET_REQUEST_USLEEP);
      continue;
    }
    gettimeofday(&s,NULL);
    NOTICE_LOG("[===index_start===]");
    pool.clear();
    newusr = 0;
    thread_data = s_buf->svr_data->front();
    u_buf.p_thread_buf = &thread_data;
    //提取请求
    clientCmd = extractCmd(u_buf,&pool);
    if(NULL == clientCmd)
    {
      ret = sendErrorStatus(u_buf,1);
      if(0 != ret)
      {
        WARNING_LOG("[send_nrui_fail error status], ret[%d]",ret);
      }
      goto SESSION_EXT;
    }
    u_buf.p_cmd = clientCmd;
    u_buf.uid = clientCmd->uid();
    //处理请求
    ret = handleCmd(u_buf, piao_handler, query_handler, player_handler, usc_getter, y_player_handler);
    if(0!=ret){
      WARNING_LOG("handle cmd failed.ret[%d]",ret);
      ret = sendErrorStatus(u_buf, ret);
      if (0 != ret)
      {
        WARNING_LOG("[send_nrui_fail error status], ret[%d]",ret);
      }
      goto SESSION_EXT;
    }

    //会话结束
SESSION_EXT:
    gettimeofday(&e,NULL);
    NOTICE_LOG("[===index_end===], cost[%d]", TIMEMSECDIFF(s, e));
    idl::cmd::destroy(clientCmd);
    g_svr_pool.reset_item(thread_data.handle, false);
    ul_pthread_mutex_lock(&(s_buf->write_mutex));
    s_buf->svr_data->pop();
    ul_pthread_mutex_unlock(&(s_buf->write_mutex));

  }
  if(NULL != player_handler){
    delete player_handler;
  }
  if(NULL != query_handler){
    delete query_handler;
  }
  if(NULL != usc_getter){
    delete usc_getter;
  }
  if(NULL != y_player_handler){
    delete y_player_handler;
  }
  //修改readindex 连接RMinSvr获得扩展列表
  time(&t);
  TRACE_LOG("work_thread[%d] end:%s\n", tid, ctime(&t));
  com_closelog_r();
  return NULL;
}

/**
 * 从命令buf中解析出cmd结构
 * [IN]
 * 	u_buf 用户命令buf
 * 	pool 内存只指针
 *
 * return not null 转换的cmd null失败
 */
idl::cmd* extractCmd(User_worker_buf& u_buf, bsl::mempool* pool)
{
  Svr_thread_data_t* buf = u_buf.p_thread_buf;
  if(NULL == buf || NULL == buf->buf)return NULL;
  idl::cmd* p_cmd = NULL;
  int ret = -1;
  try{
    bsl::ResourcePool rp;
    mc_pack_t* pack = mc_pack_open_r_rp(buf->buf, DEFAULT_MCPACK_LEN,&rp);

    ret = MC_PACK_PTR_ERR(pack);
    if (0 != ret)
    {
      WARNING_LOG("the mcpack of request is invalid, return.");
      return NULL;
    }
    p_cmd = idl::cmd::create(pool);
    p_cmd->load(pack);
  }
  catch (bsl::Exception e) {
    WARNING_LOG("extractCmd faild.name[%s], what[%s]",e.name(),e.what());
    return NULL;
  }
  return p_cmd;
}

/**
 * 给客户端反馈错误码
 * [IN]
 * 	buf 用户命令
 * 	status 错误码
 */
int sendErrorStatus(User_worker_buf& u_buf, int status)
{
  int ret;
  Svr_thread_data_t* buf = u_buf.p_thread_buf;
  if(NULL == buf || NULL == buf->buf)return -1;
  if(buf->fd < 0  || buf->handle < 0)
  {
    WARNING_LOG("bad fd[%d] or handle[%d]", buf->fd, buf->handle);
    return -1;
  }
  char pack_buf[DEFAULT_MCPACK_LEN];
  bsl::ResourcePool rp;
  mc_pack_t *pack = mc_pack_open_w_rp(2,pack_buf,DEFAULT_MCPACK_LEN,&rp);
  ret = MC_PACK_PTR_ERR(pack);
  if (0 != ret)
  {
    WARNING_LOG("the mcpack of request is invalid, return.");
    return -1;
  }

  ret = mc_pack_put_int32(pack, "status",status);
  if (ret != 0)
  {
    WARNING_LOG("put status fail[%d]", ret);
    return -1;
  }
  ret = mc_pack_close(pack);
  if (0 != ret)
  {
    WARNING_LOG("close res pack fail");
    return -1;
  }

  int res_pack_len = mc_pack_get_size(pack);
  if (res_pack_len < 0)
  {
    WARNING_LOG("get res pack size fail");
    return -1;
  }
  nshead_t head;
  head.body_len = res_pack_len;
  strncpy(head.provider, PROJECT_NAME, 8);
  head.provider[7] = 0;
  head.log_id = buf->head.log_id;
  DEBUG_LOG("write error status[%d] to ui", status);
  ret = nshead_write(buf->fd, &head, (void *)pack_buf,g_config.wtimeout*1000);
  if (0 != ret)
  {
    WARNING_LOG("send response to webserver error[errno:%d]", ret);
    return -1;
  }

  if(u_buf.p_cmd)
  {
    NOTICE_LOG("The process end info:[tid:%d][usrname:%s][client request type: [fc:%d pc:%d mc:%d][status:%d]",
        u_buf.tid, u_buf.p_cmd->username(NULL),
        u_buf.p_cmd->has_fc(),
        u_buf.p_cmd->has_pc(),
        u_buf.p_cmd->has_mc(),
        status);
  }
  else
  {
    NOTICE_LOG("The process end info:[tid:%d]status:%d]", u_buf.tid, status);
  }

  return 0;
}

/**
 * 处理用户命令，负责命令类型的路由
 * [IN]
 * 	u_buf 用户命令buf
 *
 * return 0成功 1失败
 */
int handleCmd(User_worker_buf& u_buf, 
              PiaoHandler& piao_handler,
              QueryHandler* query_handler,
              PlayerHandler* player_handler, 
              UscGetter* usc_getter, 
              YPlayerHandler* y_player_handler)
{
  if (NULL == u_buf.p_thread_buf || NULL == u_buf.p_cmd){
    WARNING_LOG("p_thread_buf or clientCmd is null");
    return 1;
  }
  if(NULL == query_handler || NULL == player_handler
      || NULL == usc_getter){
    WARNING_LOG("null intern object");
    return 1;
  }

  int ret=1;
  struct timeval s;
  struct timeval e;
  gettimeofday(&s,NULL);
  if(u_buf.p_cmd->has_chlc()){//频道列表
    ret = query_handler->handle_channellist_cmd(u_buf);
    gettimeofday(&e,NULL);
    if(ret != 0){
      //重要的请求不能有错误
      FATAL_LOG("cmd[channellist_cmd_fatal] cost[%d]",  TIMEMSECDIFF(s, e));
    }
    else{
      NOTICE_LOG("cmd[channellist_cmd] cost[%d]",  TIMEMSECDIFF(s, e));
    }
  }
  else if(u_buf.p_cmd->has_plc() && u_buf.p_cmd->rf() == Y_RF){//获取频道歌曲列表(音乐人)
    ret = y_player_handler->handle_playlist_cmd(u_buf);
    gettimeofday(&e,NULL);
    if(ret != 0){
      if (ret == NOEXIST){
        WARNING_LOG("cmd[playlist_cmd_fail] [channel not exist] cost[%d]",  TIMEMSECDIFF(s, e));
      }
      else{
        FATAL_LOG("cmd[playlist_cmd_fatal] cost[%d]",  TIMEMSECDIFF(s, e));
      }
    }
    else{
      NOTICE_LOG("cmd[playlist_cmd] cost[%d]",  TIMEMSECDIFF(s, e));
    }
  }
  else if(u_buf.p_cmd->has_plc() && u_buf.p_cmd->rf() != Y_RF){//获取频道歌曲列表
    ret = player_handler->handle_playlist_cmd(u_buf);
    gettimeofday(&e,NULL);
    if(ret != 0){
      if (ret == NOEXIST){
        WARNING_LOG("cmd[playlist_cmd_fail] [channel not exist] cost[%d]",  TIMEMSECDIFF(s, e));
      }
      else{
        FATAL_LOG("cmd[playlist_cmd_fatal] cost[%d]",  TIMEMSECDIFF(s, e));
      }
    }
    else{
      NOTICE_LOG("cmd[playlist_cmd] cost[%d]",  TIMEMSECDIFF(s, e));
    }
  }
  else if(u_buf.p_cmd->has_pac() && u_buf.p_cmd->rf() != Y_RF){//播放行为指令
    ret = player_handler->handle_playaction_cmd(u_buf);
    gettimeofday(&e,NULL);
    if(ret != 0){
      //次要的请求，WARNING标记
      WARNING_LOG("cmd[playaction_cmd_fail] cost[%d]",  TIMEMSECDIFF(s, e));
    }
    else{
      NOTICE_LOG("cmd[playaction_cmd] cost[%d]",  TIMEMSECDIFF(s, e));
    }
  }
  else if(u_buf.p_cmd->has_pac() && u_buf.p_cmd->rf() == Y_RF){//播放行为指令
    ret = y_player_handler->handle_playaction_cmd(u_buf);
    gettimeofday(&e,NULL);
    if(ret != 0){
      //次要的请求，WARNING标记
      WARNING_LOG("cmd[playaction_cmd_fail] cost[%d]",  TIMEMSECDIFF(s, e));
    }
    else{
      NOTICE_LOG("cmd[playaction_cmd] cost[%d]",  TIMEMSECDIFF(s, e));
    }
  }
  else if(u_buf.p_cmd->has_cc()){//获取个数
    ret = handleCntCmd(u_buf, usc_getter);
    gettimeofday(&e,NULL);
    if(ret != 0){
      //次要的请求，WARNING标记
      WARNING_LOG("cmd[usercount_cmd_fail] cost[%d]",  TIMEMSECDIFF(s, e));
    }
    else{
      NOTICE_LOG("cmd[usercount_cmd] cost[%d]",  TIMEMSECDIFF(s, e));
    }
  }
  else if(u_buf.p_cmd->has_lc()){//获取分页列表
    ret = handleListCmd(u_buf, usc_getter);
    gettimeofday(&e,NULL);
    if(ret != 0){
      //次要的请求，WARNING标记
      WARNING_LOG("cmd[userlist_cmd_fail] cost[%d]",  TIMEMSECDIFF(s, e));
    }
    else{
      NOTICE_LOG("cmd[userlist_cmd] cost[%d]",  TIMEMSECDIFF(s, e));
    }
  }
  else if(u_buf.p_cmd->has_nuc()){//新用户判断
    ret = query_handler->handle_newuser_cmd(u_buf);
    if(ret != 0){
      //次要的请求，WARNING标记
      WARNING_LOG("cmd[newuser_cmd_fail] cost[%d]",  TIMEMSECDIFF(s, e));
    }
    else{
      NOTICE_LOG("cmd[newuser_cmd] cost[%d]",  TIMEMSECDIFF(s, e));
    }
  }
  else if(u_buf.p_cmd->has_cslc()){//冷启动歌手列表
    ret = query_handler->handle_cssingerlist_cmd(u_buf);
    if(ret != 0){
      //次要的请求，WARNING标记
      WARNING_LOG("cmd[cssingerlist_cmd_fail] cost[%d]",  TIMEMSECDIFF(s, e));
    }
    else{
      NOTICE_LOG("cmd[cssingerlist_cmd] cost[%d]",  TIMEMSECDIFF(s, e));
    }
  }
  else if(u_buf.p_cmd->has_crc()){//冷启动提交请求
    ret = player_handler->handle_csreq_cmd(u_buf);
    if(ret != 0){
      //次要的请求，WARNING标记
      WARNING_LOG("cmd[csreq_cmd_fail] cost[%d]",  TIMEMSECDIFF(s, e));
    }
    else{
      NOTICE_LOG("cmd[csreq_cmd] cost[%d]",  TIMEMSECDIFF(s, e));
    }
  }
  else if(u_buf.p_cmd->has_utag_cmd()){//用户标签请求
    ret = query_handler->handle_utag_cmd(u_buf);
    if(ret != 0){
      //次要的请求，WARNING标记
      WARNING_LOG("cmd[utag_cmd_fail] cost[%d]",  TIMEMSECDIFF(s, e));
    }
    else{
      NOTICE_LOG("cmd[utag_cmd] cost[%d]",  TIMEMSECDIFF(s, e));
    }
  }
  else if(u_buf.p_cmd->has_tic()){//票务请求
    ret = query_handler->handle_tic_cmd(u_buf);
    if(ret != 0){
      //次要的请求，WARNING标记
      WARNING_LOG("cmd[tic_cmd fail] cost[%d]",  TIMEMSECDIFF(s, e));
    }
    else{
      NOTICE_LOG("cmd[tic_cmd] cost[%d]",  TIMEMSECDIFF(s, e));
    }
  }
  else if(u_buf.p_cmd->has_piao()){
    //PiaoHandler piao_handler;
    ret = piao_handler.dispatch(u_buf);
    if(ret != 0){
      //次要的请求，WARNING标记
      WARNING_LOG("cmd[piao_cmd fail] cost[%d]",  TIMEMSECDIFF(s, e));
    }
    else{
      NOTICE_LOG("cmd[piao_cmd] cost[%d]",  TIMEMSECDIFF(s, e));
    }
  }
  /**历史接口，不再使用，mark 2013.1.8
    else if(u_buf.p_cmd->has_pc())
    {
    return FAIL;
    ret = handlePlayerCmd(u_buf);
    }
    else if(u_buf.p_cmd->has_fc())
    {
    return FAIL;
    ret = handleFoundCmd(u_buf);
    }
    else if(u_buf.p_cmd->has_mc())
    {
    return FAIL;
    ret = handleMgrCmd(u_buf);
    }
    */
  else
  {
    //未知cmd
    WARNING_LOG("cmd[unknown_cmd_fail] cost[%d]",  TIMEMSECDIFF(s, e));
    ret = 1;
  }
  return ret;
}

/**
 * 工具函数，将返回的结构数组放入mcpack中{itemid,type,date}
 * [in]
 * 	p_loop 结构数组的指针 * 	loop_size 数组长度
 * 	mcpack_arr mcpack的数组
 *
 * return 0 成功 -1失败
 */
inline int mgrResPackArry(Item_bean *p_loop, int loop_size, mc_pack_t * mcpack_arr, enum DB_PREF_TYPE type)
{
  if(0 == loop_size)
  {
    return 0;
  }
  if(NULL == p_loop)
  {
    return -1;
  }

  if (0 != MC_PACK_PTR_ERR(mcpack_arr))
  {
    return -1;
  }

  int ret = 0;
  mc_pack_t * mcpack_obj = NULL;
  for (int i = 0; i < loop_size; i++)
  {
    mcpack_obj = mc_pack_put_object(mcpack_arr, NULL);
    if (MC_PACK_PTR_ERR(mcpack_arr))
    {
      WARNING_LOG("mcpack put object fail");
      return 1;
    }
    ret = mc_pack_put_uint32(mcpack_obj, "itemid", p_loop[i].itemid);
    if (ret != 0)
    {
      WARNING_LOG("mcpack put uint32 fail");
    }
    ret = mc_pack_put_int32(mcpack_obj, "type", p_loop[i].pref_type);
    if (ret != 0)
    {
      WARNING_LOG("mcpack put int32 fail");
    }
    ret = mc_pack_put_int64(mcpack_obj, "date", (long) p_loop[i].date);
    if (ret != 0)
    {
      WARNING_LOG("mcpack put int64 fail");
    }

    mc_pack_finish( mcpack_obj);
  }
  return 0;
}

/**
 *@brief:处理统计个数的指令
 *@param[in]:u_buf,用户命令buf
 *@return: 0 成功， 1失败
 */
int handleCntCmd(User_worker_buf& u_buf, UscGetter* usc_getter){
  if (NULL == u_buf.p_thread_buf || NULL == u_buf.p_cmd
      || !u_buf.p_cmd->has_cc()){
    WARNING_LOG("p_thread_buf or p_cmd or cc is null");
    return 1;
  }
  uint uid = u_buf.uid;
  if(uid <= 0){
    WARNING_LOG("uid<=0, can not server");
    return 1;
  }
  NOTICE_LOG("start handle cnt cmd, uid:%u", uid);
  const idl::cntcmd& cc = u_buf.p_cmd->cc();
  int32_t src = cc.src();
  uint total;
  Item_bean items[1];
  uint len_items;
  uint max_len_items = 1;
  int ret;
  uint lovesong_cnt = 0;
  uint hatesong_cnt = 0;
  uint lovesinger_cnt = 0;
  uint hatesinger_cnt = 0;
  ret = usc_getter->get_allprefcnt(lovesong_cnt, hatesong_cnt, lovesinger_cnt, hatesinger_cnt, uid);
  if(ret != SUCCESS){
    WARNING_LOG("usc get_allprefcnt fail");
    return 1;
  }
  int play_cnt = mcc_get_listen_total_num(u_buf.uid, src);
  char pack_buf[DEFAULT_MCPACK_LEN];
  bsl::ResourcePool rp;
  mc_pack_t * mcpack = NULL;
  mcpack = mc_pack_open_w_rp(2, pack_buf, DEFAULT_MCPACK_LEN, &rp);
  ret = MC_PACK_PTR_ERR(mcpack);
  if (0 != ret)
  {
    WARNING_LOG("the mcpack of request is invalid, return.");
    return 1;
  }
  ret = mc_pack_put_int32(mcpack, "status", 0);
  if (ret != 0)
  {
    WARNING_LOG("put status fail[%d]", ret);
    return 1;
  }
  ret = mc_pack_put_int32(mcpack, "lovesong_cnt", lovesong_cnt);
  if (0 != ret)
  {
    WARNING_LOG("mcpack put int32 fail");
  }
  ret = mc_pack_put_int32(mcpack, "hatesong_cnt", hatesong_cnt);
  if (0 != ret)
  {
    WARNING_LOG("mcpack put int32 fail");
  }
  ret = mc_pack_put_int32(mcpack, "lovesinger_cnt", lovesinger_cnt);
  if (0 != ret)
  {
    WARNING_LOG("mcpack put int32 fail");
  }
  ret = mc_pack_put_int32(mcpack, "hatesinger_cnt", hatesinger_cnt);
  if (0 != ret)
  {
    WARNING_LOG("mcpack put int32 fail");
  }
  ret = mc_pack_put_int32(mcpack, "play_cnt", play_cnt);
  if (0 != ret)
  {
    WARNING_LOG("mcpack put int32 fail");
  }

  ret = mc_pack_close(mcpack);
  if (0 != ret)
  {
    WARNING_LOG("close res pack fail");
    return 1;
  }
  int res_pack_len = mc_pack_get_size(mcpack);
  if (res_pack_len < 0)
  {
    WARNING_LOG("get res pack size fail");
    return 1;
  }
  nshead_t head;
  head.body_len = res_pack_len;
  strncpy(head.provider, PROJECT_NAME, 8);
  head.provider[7] = 0;
  head.log_id = u_buf.p_thread_buf->head.log_id;
  ret = nshead_write(u_buf.p_thread_buf->fd, &head, (void *) pack_buf,
      g_config.wtimeout * 1000);
  if (0 != ret)
  {
    WARNING_LOG("send response to ui error[errno:%d]", ret);
    return 1;
  }
  NOTICE_LOG("finish cnt cmd[status:0][SongLove:%d][SongHate:%d][SingerLove:%d][SingerHate:%d][listen:%d]",
      lovesong_cnt, hatesong_cnt, lovesinger_cnt, hatesinger_cnt, play_cnt);
  return 0;
}
/**
 *@brief:处理分页列表查询
 *@param[in]:u_buf,用户命令buf
 *@return: 0 成功， 1失败
 */
int handleListCmd(User_worker_buf& u_buf, UscGetter* usc_getter){
  if (NULL == u_buf.p_thread_buf || NULL == u_buf.p_cmd
      || !u_buf.p_cmd->has_lc() || NULL == usc_getter){
    WARNING_LOG("p_thread_buf or p_cmd or cc is null");
    return 1;
  }
  try
  {
    uint uid = u_buf.uid;
    const idl::listcmd& lc = u_buf.p_cmd->lc();
    int32_t type = lc.type();
    int32_t page_len = lc.page_len();
    int32_t page_no = lc.page_no();
    int32_t src = lc.src();
    if(uid <= 0 || page_no<= 0 || page_len <= 0){
      WARNING_LOG("uid <= 0 || page_no<= 0 || page_len <= 0, can not server");
      return 1;
    }
    uint total_cnt;
    uint start_no;
    int ret = -1;
    uint total_page;
    Item_bean p_beans[MAX_PREF_ITEM_NUM];
    uint item_len;
    start_no = (page_no-1)*page_len;
    NOTICE_LOG("start list cmd, [uid:%u][page_no:%d][start_no:%d][page_len:%d]", uid,page_no, start_no, page_len);
    if(type == PLAYSONG_PAGE_TYPE){
      if(page_len >= MAX_LISTENED_ITEM_NUM){
        WARNING_LOG("page_len>=%d, not allow", MAX_LISTENED_ITEM_NUM);
        return 1;
      }
      total_cnt = mcc_get_listen_total_num(u_buf.uid, src);
      total_page = total_cnt/page_len;
      if(total_cnt == 0){
        total_page = 0;
      }
      else{
        total_page = (total_cnt-1)/page_len + 1;
      }
      ret = mcc_get_history_page(u_buf.uid, p_beans, start_no, page_len, src);
      if (-1 == ret)
      {
        WARNING_LOG("get history page item fail, return.");
        return 1;
      }
      item_len = ret;
      Item_bean songs[MAX_PREF_ITEM_NUM];
      uint len_songlove;
      uint len_songhate;
      uint total;
      bsl::hashmap<uint, uint> love_ids;
      love_ids.create(MAX_PREF_ITEM_NUM);
      bsl::hashmap<uint, uint> hate_ids;
      hate_ids.create(MAX_PREF_ITEM_NUM);
      ret = usc_getter->get_prefdata(songs, len_songlove, total,
          MAX_PREF_ITEM_NUM, MAX_PREF_ITEM_NUM,
          USC_START, uid, false, DB_SONGLOVE);
      if(ret == SUCCESS){
        for(uint i = 0; i < len_songlove; i++){
          love_ids.set(songs[i].itemid, 0);
        }
      }
      ret = usc_getter->get_prefdata(songs, len_songhate, total,
          MAX_PREF_ITEM_NUM, MAX_PREF_ITEM_NUM,
          USC_START, uid, false, DB_SONGHATE);
      if(ret == SUCCESS){
        for(uint i = 0; i < len_songhate; i++){
          hate_ids.set(songs[i].itemid, 0);
        }
      }
      uint value;
      for(uint i = 0; i < item_len; i++){
        if(love_ids.get(p_beans[i].itemid, &value) == bsl::HASH_EXIST){
          p_beans[i].pref_type = DB_SONGLOVE;
        }
        else if(hate_ids.get(p_beans[i].itemid, &value) == bsl::HASH_EXIST){
          p_beans[i].pref_type = DB_SONGHATE;
        }
      }
      love_ids.destroy();
      hate_ids.destroy();
    }
    else{
      if(page_len >= MAX_PREF_ITEM_NUM){
        WARNING_LOG("page_len>=%d, not allow", MAX_PREF_ITEM_NUM);
        return 1;
      }
      ret = usc_getter->get_prefdata(p_beans, item_len, total_cnt,
          MAX_PREF_ITEM_NUM, page_len,
          start_no, uid, false, (DB_PREF_TYPE)type);
      if(ret != SUCCESS){
        WARNING_LOG("get_prefdata fail,type:%d", type);
        return 1;
      }
      if(total_cnt == 0){
        total_page = 0;
      }
      else{
        total_page = (total_cnt-1)/page_len + 1;
      }
      //类型
      for(uint i = 0; i < item_len; i++){
        p_beans[i].pref_type = type;
      }
    }
    char pack_buf[DEFAULT_MCPACK_LEN];
    bsl::ResourcePool rp;
    mc_pack_t * mcpack = NULL;
    mc_pack_t * mcpack_arr = NULL;
    mcpack = mc_pack_open_w_rp(2, pack_buf, DEFAULT_MCPACK_LEN, &rp);
    ret = MC_PACK_PTR_ERR(mcpack);
    if (0 != ret){
      WARNING_LOG("the mcpack of request is invalid, return.");
      return 1;
    }
    ret = mc_pack_put_int32(mcpack, "status", 0);
    if (ret != 0){
      WARNING_LOG("put status fail[%d]", ret);
      return 1;
    }
    ret = mc_pack_put_int32(mcpack, "total_page", total_page);
    mcpack_arr = mc_pack_put_array(mcpack, "titles");
    if (MC_PACK_PTR_ERR(mcpack_arr)){
      WARNING_LOG("mcpack put Qarray fail");
      return 1;
    }
    ret = mgrResPackArry(p_beans, item_len, mcpack_arr, (DB_PREF_TYPE)type);
    if (0 != ret){
      WARNING_LOG("mgrResPackArry put songLove fail");
      return 1;
    }
    mc_pack_finish(mcpack_arr);
    ret = mc_pack_close(mcpack);
    if (0 != ret){
      WARNING_LOG("close res pack fail");
      return 1;
    }
    int res_pack_len = mc_pack_get_size(mcpack);
    if (res_pack_len < 0){
      WARNING_LOG("get res pack size fail");
      return 1;
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
      return 1;
    }
    NOTICE_LOG("finish list cmd,[uid:%u][status:0],[page_no:%d],[len:%d]",
        u_buf.tid, page_no, item_len);
  } catch (bsl::Exception e)
  {
    WARNING_LOG("handleFoundCmd catch exception[name:%s][what:%s]",e.name(),e.what());
    return 1;
  }
  return 0;
}
