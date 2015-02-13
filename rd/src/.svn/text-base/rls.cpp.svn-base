/**
 * =====================================================================================
 *
 *	Filename:  rls.cpp
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


#include "rls.h"
#include "math.h"
#include "ul_sign.h"
#include "common.h"
#include "ependingpool.h"
#include "networker.h"
#include "reload.h"
#include "networker.h"
#include "userworker.h"
#include "mcCache.h"
#include "rls_uscchecker.h"
#include "rls_uscgetter.h"
#include "myubclient_strategy.h"
//自定义策略在命名空间中，下述宏调用也必须在命名空间中
UBCLIENT_GEN_IOC_CREATE(MyUbClientStrategy);

/***********globlevar***************/
//ul_logstat_t g_log_stat;
Global_t p_global;
//LogConf_t     LogConf;
ependingpool g_svr_pool;
Svr_buf_t *td = NULL;

double _DAY_WEIGHT_CONF_[MAX_DAY] = {90.4837418,81.87307531,74.08182207,67.0320046,60.65306597,54.88116361,49.65853038,44.93289641,40.65696597,36.78794412,33.28710837,30.11942119,27.2531793,24.65969639,22.31301601,20.1896518,18.26835241,16.52988882,14.95686192,13.53352832,12.24564283,11.08031584,10.02588437,9.071795329,8.208499862,7.427357821,6.720551274,6.081006263,5.502322006,4.978706837,4.504920239,4.076220398,3.68831674,3.337326996,3.019738342,2.732372245,2.472352647,2.237077186,2.024191145,1.831563889,1.65726754,1.499557682,1.356855901,1.22773399,1.110899654,1.005183574,0.90952771,0.822974705,0.744658307,0.6737947};

/*********************************/

void usage(void);
int Init(Ul_confdata* p_ulconf);
void *emain(void *arg);
int init_redis();
int destroy_redis();
int Clear();
int test_ub();
int SaveStatistic();
int parse_options(int argc, char **argv, char *conf_file, int length);
inline void setStrParam();

/**
 * ===================  FUNCTION char_cmp ==============================
 * @brief 根据成功率对选出来的结果进行快排
 * return -1 a排b前，1 a排b后
 * ===========================================================================
 */
inline int char_cmp(const void *a, const void *b)
{
	char *pa = (char *)a;
	char *pb = (char *)b;
	if (*pa > *pb)
	{
		return 1;
	}
	else if (*pa < *pb)
	{
		return -1;
	}
	return 0;
}


int main(int argc, char **argv)
{
	int i = 0;
	int ret = 0;
	pthread_t *pworkid;
	pthread_t  emainid;
	pthread_t  reloadid;
    pthread_t  usccheckid;
	pthread_t  *worktids;
	if (0 != parse_options(argc, argv, g_config.configfile, MAX_DIR_LEN))
	{
		FATAL_LOG("%s: parse options fail, exit!", PROJECT_NAME);
		return -1;
	}

	Ul_confdata* p_ulconf = load_confdata(g_config.configfile);
	if(NULL == p_ulconf)
	{
		FATAL_LOG("load conf data failed");
		return -1;
	}
	ret = load_all_c_descripts(p_ulconf,g_c_descripts,1,PROJECT_NAME);
	////load config
	if (0 != ret)
	{
		ul_freeconf(p_ulconf);
		FATAL_LOG("load_all_c_descripts failed");
		return -1;
	}

	if (Init(p_ulconf) != 0)
	{
		ul_freeconf(p_ulconf);
		FATAL_LOG("\ninit failed.\n");
		return -1;
	}

	ul_freeconf(p_ulconf);
	TRACE_LOG("initialization configure success.");

	if (g_config.pid_filepath[0] != '\0')
	{
		FILE *fpid = fopen(g_config.pid_filepath, "w");
		if (NULL == fpid)
		{
			FATAL_LOG("create pid file fail, file name with path is %s, exit.",
					g_config.pid_filepath);
			return -1;
		}
		if (0 >= fprintf(fpid, "%u", getpid()))
		{
			FATAL_LOG("write pid to file[%s] fail, exit.",
					g_config.pid_filepath);
			return -1;
		}
		DEBUG_LOG("write pid[%u] to pid file[%s] success.",
				getpid(), g_config.pid_filepath);
		fclose(fpid);
	}
	// ignore SIGPIPE
	signal(SIGPIPE, SIG_IGN);

	srand((int)time(0));


	// malloc for thread ids
	pworkid = (pthread_t *) malloc(g_config.threadnum * sizeof(pthread_t));
	DEBUG_LOG("malloc threadid for networker threads, thread num is %d\n",g_config.threadnum);
	if (!pworkid)
	{
		FATAL_LOG("malloc thread ids for networker threads fail, exit.\n");
		return -1;
	}
	worktids = (pthread_t *) malloc(g_config.work_threadnum * sizeof(pthread_t));
	DEBUG_LOG("malloc threadid for work threads, thread num is %d\n",g_config.work_threadnum);
	if (!worktids)
	{
		FATAL_LOG("malloc threads ids for work threads fail, exit.\n");
		return -1;
	}
	g_svr_pool.set_sock_num(g_config.max_sock_num);
	//start the emain thread for ependingpool; listening socket
	ret = ul_pthread_create(&(emainid), NULL, emain, NULL);
	if (0 != ret)
	{
		FATAL_LOG("create emain thread fail, exit.");
		return -1;
	}

	ret = ul_pthread_create(&(reloadid), NULL, svr_reload, NULL);
	if (0 != ret)
	{
		FATAL_LOG("create reload thread fail, myExit.");
		myExit(-1);
	}
	TRACE_LOG("create core thread(%lu) and update thread(%lu) success", emainid, reloadid);
    //start usc check
	ret = ul_pthread_create(&(usccheckid), NULL, usc_check, NULL);
	if (0 != ret)
	{
		FATAL_LOG("create uscchecker thread fail, myExit.");
		myExit(-1);
	}
	TRACE_LOG("create core thread(%lu) and update thread(%lu) success", emainid, usccheckid);

	//start the networker threads
	for (i = 0; i < g_config.threadnum; ++i)
	{
		ret = ul_pthread_create(&pworkid[i], NULL, networker, (void *)(long)i);
		if (0 != ret)
		{
			FATAL_LOG("create the %dth networker thread fail, exit.\n", i);
			myExit(-1);
		}
		TRACE_LOG("create the %dth networker thread success, thread id is %lu.\n",
				i, pworkid[i]);
	}

	//start work threads
	for (i = 0; i < g_config.work_threadnum; ++i)
	{

		ret = ul_pthread_create(&worktids[i], NULL, userworker, (void *)(long)i);
		if (0 != ret)
		{
			FATAL_LOG("create the %dth userworker thread fail, exit.\n", i);
			myExit(-1);
		}
		TRACE_LOG("create the %dth userworker thread success, thread id is %lu.\n",
				i, worktids[i]);
	}
	//wait the thread return
	for (i = 0; i < g_config.work_threadnum; ++i)
	{
		ul_pthread_join(worktids[i], NULL);
	}

	for (i = 0; i < g_config.threadnum; ++i)
	{
		ul_pthread_join(pworkid[i], NULL);
	}

	ul_pthread_join(emainid, NULL);
    ul_pthread_join(usccheckid, NULL);
    ul_pthread_join(reloadid, NULL);
	if(NULL != pworkid)
	{
		free(pworkid);
		pworkid = NULL;
	}
	if(NULL != worktids)
	{
		free(worktids);
		worktids = NULL;
	}

	Clear();
	return 0;
}


/**
 * @brief 打开目录文件
 * @param fp:文件指针
 * @param fname:文件名
 * @param path:文件路径
 * @return
 */
inline int fopen_dir(FILE** fp, const char *fname, const char *path,
		const char *mode)
{
	char tpfile[MAX_DIR_LEN];

	if (fname == NULL)
	{
		WARNING_LOG("fname is NULL");
		return -1;
	}
	if (path == NULL)
	{
		WARNING_LOG("path is NULL");
		return -1;
	}
	if (mode == NULL)
	{
		WARNING_LOG("mode is NULL");
		return -1;
	}

	if (*fp != NULL)
	{
		fclose(*fp);
		*fp = NULL;
	}
	snprintf(tpfile, MAX_DIR_LEN, "%s%s", path, fname);
	*fp = fopen(tpfile, mode);
	if (NULL == *fp)
	{
		WARNING_LOG("open DI file error %s!",tpfile);
		return -1;
	}
	return 0;
}

int test_ub(){
    int ret;
    ub_log_init("./log","test13");

    ub::UbClientManager ubmgr;

    ret = ubmgr.init("./conf", "ub_client.conf");
    if (ret == 0) {
        fprintf(stderr, "%s\n", "init ok");

    } else {
        fprintf(stderr, "%s\n", "init error");
        return -1;
    }

    int repNum = 0;
    bsl::ResourcePool rpool;
    bsl::var::Dict currDict;
    ub::nshead_talkwith_t* currTalk = new ub::nshead_talkwith_t;
    if(NULL == currTalk){
        return 1;
    }
    currTalk->reqhead.log_id = rand();
    currTalk->reqbuf = new char[DEFAULT_MCPACK_LEN];
    if(NULL == currTalk->reqbuf){
        return 1;
    }
    memset(currTalk->reqbuf, 0, DEFAULT_MCPACK_LEN);
    ts_head_t ts_head;
    int ts_head_len = sizeof(ts_head);
    printf("ts_head_len:%d\n", ts_head_len);
    ts_head.cmd_no = 100003;
    snprintf(ts_head.data_type, 64, "%s", "tagkit");
    ts_head.page_no = 0;
    ts_head.num_per_page = 200;
    memcpy(currTalk->reqbuf, &ts_head, ts_head_len);
    mc_pack_t * pack = NULL;
    pack = mc_pack_open_w_rp(1, currTalk->reqbuf + ts_head_len, DEFAULT_MCPACK_LEN - ts_head_len, &rpool);
    ret = MC_PACK_PTR_ERR(pack);
    if (0 != ret){
        //WARNING_LOG("the mcpack of request is invalid, return.");
        return 1;
    }
    ret = mc_pack_put_str(pack, "word", "流行");
    if(ret != 0){
        //WARNING_LOG("put word fail[%d]", ret);
        return 1;
    }
    ret = mc_pack_put_int32(pack, "type", 6);
    if (ret != 0){
        //WARNING_LOG("put type fail[%d]", ret);
        return 1;
    }
    ret = mc_pack_put_int32(pack, "copycat", 3);
    if (ret != 0){
        //WARNING_LOG("put type fail[%d]", ret);
        return 1;
    }
    ret = mc_pack_put_int32(pack, "from", 0);
    if (ret != 0){
        //WARNING_LOG("put from fail[%d]", ret);
        return 1;
    }
    ret = mc_pack_put_int32(pack, "limit", 0);
    if (ret != 0){
        //WARNING_LOG("put limit fail[%d]", ret);
        return 1;
    }
    ret = mc_pack_put_int32(pack, "ip", 0);
    if (ret != 0){
        //WARNING_LOG("put ip fail[%d]", ret);
        return 1;
    }
    int pack_len = mc_pack_get_size(pack);
    if (pack_len < 0){
        //WARNING_LOG("get req pack size fail");
        return 1;
    }
    currTalk->reqhead.body_len = ts_head_len + pack_len;
    currTalk->resbuf = new char[DEFAULT_MCPACK_LEN];
    if(NULL == currTalk->resbuf){
        return 1;
    }
    memset(currTalk->resbuf, 0, DEFAULT_MCPACK_LEN);
    currTalk->maxreslen = DEFAULT_MCPACK_LEN;
    printf("begin talk\n");
    ret = ubmgr.nshead_singletalk("tagservice", currTalk, currDict);
    printf("end talk\n");
    if(0 != ret){
        fprintf(stderr, "simple talk error*** : %s\n", ub::get_talk_errorinfo(ret));
        return 1;
    }
    else{
        int ret_num = ((ts_head_t *)(currTalk->resbuf))->ret_num;
        if(ret_num <= 0){
            return 1;
        }
        char tmp[1024*1024];

        pack = mc_pack_open_r_rp(currTalk->resbuf+ts_head_len, DEFAULT_MCPACK_LEN - ts_head_len, &rpool);
        mc_pack_pack2text(pack,
                          tmp,
                          1024*1024, 1);
        printf("res:%s\n", tmp);
        mc_pack_t* mcpack_arr = NULL;
        mc_pack_t* item = NULL;
        mcpack_arr = mc_pack_get_array(pack, "res_array");
        ret = MC_PACK_PTR_ERR(mcpack_arr);
        if(0 != ret){
            return 1;
        }
        int res_len = mc_pack_get_item_count(mcpack_arr);
        mc_uint32_t song_id;
        for(int i = 0; i < res_len; i++){
            item = mc_pack_get_object_arr(mcpack_arr, i);
            ret = MC_PACK_PTR_ERR(item);
            if(0 != ret){
                return 1;
            }
            ret = mc_pack_get_uint32(item, "song_id", &song_id);
            printf("\nsongid:%d", (uint32_t)song_id);
        }
    }
    delete []currTalk->resbuf;
    delete []currTalk->reqbuf;
	delete currTalk;
    return 0;
}
/**
 * @brief 初始化处理函数
 * @param pcf:配置
 * @return
 */
int Init(Ul_confdata* pcf)
{
	char tpfile[MAX_DIR_LEN];
	int i = 0;
	int j = 0;
	int ret = 0;
    int line_len = 32;
    char line[line_len];
	config_t& pconf=g_config;

	ret = com_loadlog(pconf.comlog_conf_path, pconf.comlog_conf_file);
	if (ret != 0){
        FATAL_LOG("load comlog config err\n");
        return -1;
	}
    //ub_client
    ub::strategy_ioc *strategyIoc = ub::ubclient_get_strategyioc();
    if (NULL == strategyIoc) {

        return -1;
    }
    //下述宏使用自定义策略类，必须是全路径 cmm::MyUbClientStrategy 配置文件中也必须是全路径
    UBCLIENT_ADD_IOC_CLASS(strategyIoc, MyUbClientStrategy);
    ret = p_global.ubmgr.init(pconf.ub_client_conf_path, pconf.ub_client_conf_file);
    if (ret == 0) {
        NOTICE_LOG("init ubclient mgr success!");
    }
    else{
        FATAL_LOG("init ubclient mgr fail");
        return -1;
    }
    p_global.ubmgr.startHealthyCheck(2000);

	//加载mmclient
	char mcc_file[MAX_DIR_LEN];
	//snprintf(mcc_file, MAX_DIR_LEN, "%s/%s", pconf.mcc_conf_path, pconf.mcc_conf_file);
    //p_global.mcc = McClient::create(mcc_file, pconf.mcc_product_name);
	snprintf(mcc_file, MAX_DIR_LEN, "%s", pconf.mcc_conf_file);
    p_global.mcc = NeMcClient::create(mcc_file, pconf.mcc_product_name);
    if (NULL == p_global.mcc){
        FATAL_LOG("init mcc fail, mcc_file[%s]", mcc_file);
        return -1;
    }
    else{
        NOTICE_LOG("init mcc success");
    }

    //加载cs.conf
    char cs_file[MAX_DIR_LEN];
    snprintf(cs_file, MAX_DIR_LEN, "%s/%s", pconf.cs_conf_path, pconf.cs_conf_file);
    Ul_confdata* p_cs_ulconf = load_confdata(cs_file);
    if(NULL == p_cs_ulconf)
    {
        FATAL_LOG("load p_cs_ulconf data failed");
        return -1;
    }
    ret = load_all_c_descripts(p_cs_ulconf,g_cs_descripts,1,PROJECT_NAME);
    ////load config
    if (0 != ret)
    {
        ul_freeconf(p_cs_ulconf);
        FATAL_LOG("load_all_c_descripts failed");
        return -1;
    }
    ul_freeconf(p_cs_ulconf);
    TRACE_LOG("initialization cs configure success.");
    NOTICE_LOG("listenport:%d, reloadport:%d", g_config.listenport, g_config.reload_port);

	//加载big_dict
	p_global.bigDict = odb_load_search(pconf.inpath, pconf.big_dict);
	if (p_global.bigDict == (sodict_search_t *) ODB_LOAD_NOT_EXISTS
			|| p_global.bigDict == NULL)
	{
		WARNING_LOG("cant load song dict[%s]", pconf.big_dict);
		return -1;
	}

    //加载channel_detect_song_dict
    p_global.channel_detect_song_dict = odb_load_search(pconf.inpath, pconf.channel_detect_song_dict);
    if (p_global.channel_detect_song_dict == (sodict_search_t *) ODB_LOAD_NOT_EXISTS
            || p_global.channel_detect_song_dict == NULL)
    {
        WARNING_LOG("cant load channel_detect_song_dict[%s]", pconf.channel_detect_song_dict);
        return -1;
    }

    //加载detect_judge_song_dict
    p_global.detect_judge_song_dict = odb_load_search(pconf.inpath, pconf.detect_judge_song_dict);
    if (p_global.detect_judge_song_dict == (sodict_search_t *) ODB_LOAD_NOT_EXISTS
            || p_global.detect_judge_song_dict == NULL)
    {
        WARNING_LOG("cant load detect_judge_song_dict[%s]", pconf.detect_judge_song_dict);
        return -1;
    }

    //加载song_tag_dict
    p_global.song_tag_dict = odb_load_search(pconf.inpath, pconf.song_tag_dict);
    if (p_global.song_tag_dict == (sodict_search_t *) ODB_LOAD_NOT_EXISTS
            || p_global.song_tag_dict == NULL)
    {
        WARNING_LOG("cant load song_tag_dict[%s]", pconf.song_tag_dict);
        return -1;
    }

    //加载lr_model_dict
    p_global.lr_model_dict = odb_load_search(pconf.inpath, pconf.lr_model_dict);
    if (p_global.lr_model_dict == (sodict_search_t *) ODB_LOAD_NOT_EXISTS
            || p_global.lr_model_dict == NULL)
    {
        WARNING_LOG("cant load lr_model_dict[%s]", pconf.lr_model_dict);
        return -1;
    }

    //加载ticket_dict
    p_global.ticket_dict = odb_load_search(pconf.inpath, pconf.ticket_dict);
    if (p_global.ticket_dict == (sodict_search_t *) ODB_LOAD_NOT_EXISTS
            || p_global.ticket_dict == NULL)
    {
        WARNING_LOG("cant load ticket_dict[%s]", pconf.ticket_dict);
        return -1;
    }

    //加载lr_feature_dict
    p_global.lr_feature_dict = odb_load_search(pconf.inpath, pconf.lr_feature_dict);
    if (p_global.lr_feature_dict == (sodict_search_t *) ODB_LOAD_NOT_EXISTS
            || p_global.lr_feature_dict == NULL)
    {
        WARNING_LOG("cant load lr_feature_dict[%s]", pconf.lr_feature_dict);
        return -1;
    }

    //加载y_channel_dict, 音乐人频道字典
    p_global.y_channel_dict = odb_load_search(pconf.inpath, pconf.y_channel_dict);
    if (p_global.y_channel_dict == (sodict_search_t *) ODB_LOAD_NOT_EXISTS
            || p_global.y_channel_dict == NULL)
    {
        WARNING_LOG("cant load y_channel_dict[%s]", pconf.y_channel_dict);
        return -1;
    }

    //加载y_song_dict， 音乐人歌曲字典
    p_global.y_song_dict = odb_load_search(pconf.inpath, pconf.y_song_dict);
    if (p_global.y_song_dict == (sodict_search_t *) ODB_LOAD_NOT_EXISTS
            || p_global.y_song_dict == NULL)
    {
        WARNING_LOG("cant load y_song_dict[%s]", pconf.y_song_dict);
        return -1;
    }

    //加载 channel_song_dict
    p_global.channel_song_dict = odb_load_search(pconf.inpath, pconf.channel_song_dict);
    if (p_global.channel_song_dict == (sodict_search_t *) ODB_LOAD_NOT_EXISTS
            || p_global.channel_song_dict == NULL)
    {
        WARNING_LOG("cant load channel_song_dict[%s]", pconf.channel_song_dict);
        return -1;
    }

    //加载 公共频道音乐人歌曲
    p_global.yyr_chsong_dict = odb_load_search(pconf.inpath, pconf.yyr_chsong_dict);
    if (p_global.yyr_chsong_dict == (sodict_search_t *) ODB_LOAD_NOT_EXISTS
            || p_global.yyr_chsong_dict == NULL)
    {
        WARNING_LOG("cant load yyr_chsong_dict[%s]", pconf.yyr_chsong_dict);
        return -1;
    }

    //处理用户中心的ip
    int split_count = 0;
    char* buffer = pconf.usc_ipport;
    char* result = NULL;
    char* out = NULL;
    result = strtok_r(buffer, ";", &out);
    char ipport_buffer[2][MAX_IPPORT_LEN];
    while(NULL != result){
        snprintf(ipport_buffer[split_count], MAX_IPPORT_LEN, "%s", result);
        split_count++;
        if(split_count >= 2){
            break;
        }
        result = strtok_r(NULL, ";", &out);
    }
    if(split_count != 2){
        FATAL_LOG("usc ip config wrong");
        return -1;
    }
    //机房
    FILE* host_fp;
    char host_pre_buffer[10];
    host_fp = popen("hostname|cut -f1 -d'-'", "r");
    fgets(host_pre_buffer, sizeof(host_pre_buffer), host_fp);
    //转换成大写
    int host_len = strlen(host_pre_buffer);
    if(host_pre_buffer[host_len-1] == '\n'){
        host_len--;
        host_pre_buffer[host_len] = '\0';
    }
    for(int i = 0; i < host_len; i++){
        host_pre_buffer[i] = toupper(host_pre_buffer[i]);
    }
    if(strcmp(host_pre_buffer, "TC") == 0 || strcmp(host_pre_buffer, "DB") == 0 || strcmp(host_pre_buffer, "CQ01")==0){
        snprintf(p_global.USC_IPPORT, MAX_IPPORT_LEN, "%s", ipport_buffer[0]);
        snprintf(p_global.USC_IPPORT1, MAX_IPPORT_LEN, "%s", ipport_buffer[0]);
        snprintf(p_global.USC_IPPORT2, MAX_IPPORT_LEN, "%s", ipport_buffer[1]);
    }
    else if(strcmp(host_pre_buffer, "JX") == 0 || strcmp(host_pre_buffer, "AI" ) == 0
            || strcmp(host_pre_buffer, "YF") == 0){
        snprintf(p_global.USC_IPPORT, MAX_IPPORT_LEN, "%s", ipport_buffer[1]);
        snprintf(p_global.USC_IPPORT1, MAX_IPPORT_LEN, "%s", ipport_buffer[1]);
        snprintf(p_global.USC_IPPORT2, MAX_IPPORT_LEN, "%s", ipport_buffer[0]);
    }
    else{
        snprintf(p_global.USC_IPPORT, MAX_IPPORT_LEN, "%s", ipport_buffer[1]);
        snprintf(p_global.USC_IPPORT1, MAX_IPPORT_LEN, "%s", ipport_buffer[1]);
        snprintf(p_global.USC_IPPORT2, MAX_IPPORT_LEN, "%s", ipport_buffer[0]);
    }
    p_global.USC_OK = true;
    NOTICE_LOG("set usc ip port success, [host_pre:%s][ipport:%s]", host_pre_buffer, p_global.USC_IPPORT);
    NOTICE_LOG("set usc ip port1 success, [host_pre:%s][ipport1:%s]", host_pre_buffer, p_global.USC_IPPORT1);
    NOTICE_LOG("set usc ip port2 success, [host_pre:%s][ipport2:%s]", host_pre_buffer, p_global.USC_IPPORT2);

    //处理recommend channel
    int ch_split_count = 0;
    char* ch_buffer = pconf.recommend_channel;
    char* ch_result = NULL;
    char* ch_out = NULL;
    ch_result = strtok_r(ch_buffer, ";", &ch_out);
    char temp_channel[MAX_CHNAME_LEN];
    int value;
    p_global.recommend_channel.create(MAX_RECOMMEND_CHANNEL_LEN);
    while(NULL !=ch_result){
        snprintf(temp_channel, MAX_CHNAME_LEN, "%s", ch_result);
        std :: string str(temp_channel);
        if(p_global.recommend_channel.get(str, &value) == bsl::HASH_NOEXIST){
            if(p_global.recommend_channel.set(str, 0)!=bsl::HASH_INSERT_SEC){
                WARNING_LOG("set recommend channenl error, [ch_name %s], the hashmap size is [%d]", str.c_str(), p_global.recommend_channel.size());
            }
            ch_split_count++;
        }
        ch_result = strtok_r(NULL, ";", &ch_out);
    }

    //处理user_list_pair
    ch_split_count = 0;
    ch_buffer = pconf.user_list_pair;
    ch_result = NULL;
    ch_out = NULL;
    ch_result = strtok_r(ch_buffer, ";", &ch_out);
    p_global.user_list_pair.create(MAX_USER_LIST_PAIR_LEN);
    fuse_init fuse_data;
    int user_list_type;
    while(NULL !=ch_result){
        char tmp_str[100];//缓存字符串
        snprintf(tmp_str, 100, "%s", ch_result);
        NOTICE_LOG("user_list_pair[%s]", tmp_str);
        char *split_str1 = strchr(tmp_str, ',');
        if(split_str1 == NULL){
            WARNING_LOG("the user_list_pair format error, tmp_str[%s]", tmp_str);
            continue;
        }
        *split_str1 = '\0';
        user_list_type = atoi(tmp_str);
        split_str1 ++;
        char *split_str2 = strchr(split_str1, ',');
        if(split_str2 == NULL){
            WARNING_LOG("the user_list_pair format error, tmp_str[%s]", tmp_str);
            continue;
        }
        fuse_data.source = atoi(split_str1);
        split_str2 ++;
        fuse_data.rate = atoi(split_str2);
        NOTICE_LOG("user_list_pair, r_type[%d], source[%d], rate[%d]", user_list_type, fuse_data.source, fuse_data.rate);
        fuse_init value;
        if(p_global.user_list_pair.get(user_list_type, &value) == bsl::HASH_NOEXIST){
            if(p_global.user_list_pair.set(user_list_type, fuse_data)!=bsl::HASH_INSERT_SEC){
                WARNING_LOG("set user_list_pair error, [user_list_type %d], the hashmap size is [%d]", user_list_type, p_global.user_list_pair.size());
            }
            ch_split_count++;
        }
        ch_result = strtok_r(NULL, ";", &ch_out);
    }
    NOTICE_LOG("user_list_pair len[%d]", ch_split_count);

    //初始化歌曲属性字典
    p_global.songs_attrs.create(INIT_SONG_ATTR_DICT_LEN);

    //处理detect channel
    ch_split_count = 0;
    ch_buffer = pconf.detect_channel;
    ch_result = NULL;
    ch_out = NULL;
    ch_result = strtok_r(ch_buffer, ";", &ch_out);
    temp_channel[MAX_CHNAME_LEN];
    char tmp_str[100];//缓存字符串
    p_global.detect_channel.create(MAX_DETECT_CHANNEL_LEN);
    instant_init i_init;
    instant_init init_value;
    while(NULL !=ch_result){
        snprintf(tmp_str, 100, "%s", ch_result);
        DEBUG_LOG("tmp_str[%s]", tmp_str);
        char *split_str1 = strchr(tmp_str, ',');
        if(split_str1 == NULL){
            WARNING_LOG("the detect_channel format error, ch[%s]", ch_result);
            continue;
        }
        *split_str1 = '\0';
        snprintf(temp_channel, MAX_CHNAME_LEN, "%s", tmp_str);

        split_str1 ++;
        char *split_str2 = strchr(split_str1, ',');
        if(split_str2 == NULL){
            WARNING_LOG("the detect_channel format error, ch[%s]", ch_result);
            continue;
        }
        *split_str2 = '\0';
        i_init.dim_type = atoi(split_str1);

        split_str2 ++;
        i_init.dim_det = atoi(split_str2);

        std :: string str(temp_channel);
        if(p_global.detect_channel.get(str, &init_value) == bsl::HASH_NOEXIST){
            if(p_global.detect_channel.set(str, i_init)!=bsl::HASH_INSERT_SEC){
                WARNING_LOG("set detect channenl error, [ch_name %s], the hashmap size is [%d]", str.c_str(), p_global.detect_channel.size());
            }
            ch_split_count++;
        }
        ch_result = strtok_r(NULL, ";", &ch_out);
    }
    DEBUG_LOG("detect channel len[%d]", ch_split_count);

    //处理i_brief_lan
    ch_split_count = 0;
    ch_buffer = pconf.i_brief_lan;
    ch_result = NULL;
    ch_out = NULL;
    ch_result = strtok_r(ch_buffer, ";", &ch_out);
    char temp_no[10];//缓存维度编号

    int brief_key;
    int brief_value;
    p_global.i_brief_lan.create(MAX_INSTANT_DIM_CLASS_LEN);
    while(NULL !=ch_result){
        snprintf(tmp_str, 100, "%s", ch_result);
        DEBUG_LOG("tmp_str[%s]", tmp_str);
        char *split_str1 = strchr(tmp_str, ',');
        if(split_str1 == NULL){
            WARNING_LOG("the i_brief_lan format error, ch[%s]", ch_result);
            continue;
        }
        *split_str1 = '\0';
        brief_key = atoi(tmp_str);
        split_str1 ++;
        brief_value = atoi(split_str1);
        if(p_global.i_brief_lan.get(brief_key, &value) == bsl::HASH_NOEXIST){
            if(p_global.i_brief_lan.set(brief_key, brief_value)!=bsl::HASH_INSERT_SEC){
                WARNING_LOG("set i_brief_lan error, brief_key [%d],brief_value[%d] , the hashmap size is [%d]", brief_key, brief_value, p_global.detect_channel.size());
            }
            ch_split_count++;
        }
        ch_result = strtok_r(NULL, ";", &ch_out);
    }
    DEBUG_LOG("i_brief_lan len[%d]", ch_split_count);

    //处理i_brief_year
    ch_split_count = 0;
    ch_buffer = pconf.i_brief_year;
    ch_result = NULL;
    ch_out = NULL;
    ch_result = strtok_r(ch_buffer, ";", &ch_out);
    temp_no[10];//缓存维度编号
    p_global.i_brief_year.create(MAX_INSTANT_DIM_CLASS_LEN);
    while(NULL !=ch_result){
        snprintf(tmp_str, 100, "%s", ch_result);
        DEBUG_LOG("tmp_str[%s]", tmp_str);
        char *split_str1 = strchr(tmp_str, ',');
        if(split_str1 == NULL){
            WARNING_LOG("the i_brief_year format error, ch[%s]", ch_result);
            continue;
        }
        *split_str1 = '\0';
        brief_key = atoi(tmp_str);
        split_str1 ++;
        brief_value = atoi(split_str1);
        if(p_global.i_brief_year.get(brief_key, &value) == bsl::HASH_NOEXIST){
            if(p_global.i_brief_year.set(brief_key, brief_value)!=bsl::HASH_INSERT_SEC){
                WARNING_LOG("set i_brief_year error, brief_key [%d],brief_value[%d] , the hashmap size is [%d]", brief_key, brief_value, p_global.detect_channel.size());
            }
            ch_split_count++;
        }
        ch_result = strtok_r(NULL, ";", &ch_out);
    }
    DEBUG_LOG("i_brief_year len[%d]", ch_split_count);

    //处理i_brief_area
    ch_split_count = 0;
    ch_buffer = pconf.i_brief_area;
    ch_result = NULL;
    ch_out = NULL;
    ch_result = strtok_r(ch_buffer, ";", &ch_out);
    temp_no[10];//缓存维度编号
    p_global.i_brief_area.create(MAX_INSTANT_DIM_CLASS_LEN);
    while(NULL !=ch_result){
        snprintf(tmp_str, 100, "%s", ch_result);
        DEBUG_LOG("tmp_str[%s]", tmp_str);
        char *split_str1 = strchr(tmp_str, ',');
        if(split_str1 == NULL){
            WARNING_LOG("the i_brief_area format error, ch[%s]", ch_result);
            continue;
        }
        *split_str1 = '\0';
        brief_key = atoi(tmp_str);
        split_str1 ++;
        brief_value = atoi(split_str1);
        if(p_global.i_brief_area.get(brief_key, &value) == bsl::HASH_NOEXIST){
            if(p_global.i_brief_area.set(brief_key, brief_value)!=bsl::HASH_INSERT_SEC){
                WARNING_LOG("set i_brief_area error, brief_key [%d],brief_value[%d] , the hashmap size is [%d]", brief_key, brief_value, p_global.detect_channel.size());
            }
            ch_split_count++;
        }
        ch_result = strtok_r(NULL, ";", &ch_out);
    }
    DEBUG_LOG("i_brief_area len[%d]", ch_split_count);


    //处理i_brief_gender
    ch_split_count = 0;
    ch_buffer = pconf.i_brief_gender;
    ch_result = NULL;
    ch_out = NULL;
    ch_result = strtok_r(ch_buffer, ";", &ch_out);
    p_global.i_brief_gender.create(MAX_INSTANT_DIM_CLASS_LEN);
    while(NULL !=ch_result){
        snprintf(tmp_str, 100, "%s", ch_result);
        DEBUG_LOG("tmp_str[%s]", tmp_str);
        char *split_str1 = strchr(tmp_str, ',');
        if(split_str1 == NULL){
            WARNING_LOG("the i_brief_gender format error, ch[%s]", ch_result);
            continue;
        }
        *split_str1 = '\0';
        brief_key = atoi(tmp_str);
        split_str1 ++;
        brief_value = atoi(split_str1);
        if(p_global.i_brief_gender.get(brief_key, &value) == bsl::HASH_NOEXIST){
            if(p_global.i_brief_gender.set(brief_key, brief_value)!=bsl::HASH_INSERT_SEC){
                WARNING_LOG("set i_brief_gender error, brief_key [%d],brief_value[%d] , the hashmap size is [%d]", brief_key, brief_value, p_global.detect_channel.size());
            }
            ch_split_count++;
        }
        ch_result = strtok_r(NULL, ";", &ch_out);
    }
    DEBUG_LOG("i_brief_gender len[%d]", ch_split_count);


    //加载黑名单
    p_global.blank_song_list = odb_creat(FILT_DICT_HASH);
    FILE* blank_file = fopen(pconf.blank_song_path, "r");
    char* read_ret;
    uint songid;
    sodict_snode_t blank_node;
    if(NULL == blank_file){
        WARNING_LOG("cant open blank song file:%s", pconf.blank_song_path);
    }
    else{
        read_ret = fgets(line, line_len, blank_file);
        while(NULL != read_ret){
            songid = atoi(line);
            blank_node.sign1 = songid;
            blank_node.sign2 = 0;
            blank_node.cuint1 = 0;
            blank_node.cuint2 = 0;
            if (odb_add(p_global.blank_song_list, &blank_node, 1) == ODB_ADD_ERROR){
                WARNING_LOG("add the node info into blank dict failed");
            }
            memset(line, 0, line_len);
            read_ret = fgets(line, line_len, blank_file);
        }
    }

    MyclientPoolConf conn_pool_conf;
    conn_pool_conf.monitor_reconnection_time = 5;   //后台线程每隔5秒去检测连接的连通性
    conn_pool_conf.plevel = 1;                      //开启profiling
    conn_pool_conf.sqlBufSize= 4096;
    conn_pool_conf.failHandler= NULL;       //do nothing
	p_global.dbpool = new MyclientPool(&conn_pool_conf);
	if(NULL == p_global.dbpool)
	{
		FATAL_LOG("create MyclientPool faild.");
		return -1;
	}

	ret = p_global.dbpool->init(false);
	if (0 != ret)
	{
		FATAL_LOG("MyclientPool init faild.");
		return -1;
	}

	ret = p_global.dbpool->addServer(g_config.dbconfigpath, g_config.dbconfig);
	if( 0 != ret)
	{
		FATAL_LOG("MyclientPool addServer faild.");
		return -1;
	}

    //启动redis
    ret = init_redis();
    if(0 != ret){
        return ret;
    }

	//加载singersinger_data
	snprintf(tpfile, sizeof(tpfile), "%s%s", pconf.inpath,
			pconf.singersinger_data);
	if (read_file_in_mem(tpfile, (void **) &(p_global.singersingerlist),
			sizeof(Singer_item_t), 0, &(p_global.max_sisi_len)) < 0)
	{
		WARNING_LOG("cant load singersinger_data");
		return -1;
	}

	//加载songbrief_data
	snprintf(tpfile, sizeof(tpfile), "%s%s", pconf.inpath,
			pconf.songbrief_data);
	if (read_file_in_mem(tpfile, (void **) &(p_global.songbrieflist),
			sizeof(Song_brief_t), 0, &(p_global.max_songbrief_len)) < 0)
	{
		WARNING_LOG("cant load songbrief_data");
		return -1;
	}

    //加载频道列表数据
	snprintf(tpfile, sizeof(tpfile), "%s%s", pconf.inpath,
			pconf.chinfolist_data);
	if (read_file_in_mem(tpfile, (void **) &(p_global.ch_info_list),
			sizeof(ch_info_t), 0, &(p_global.max_chinfolist_len)) < 0)
	{
		WARNING_LOG("cant load chinfolist_data");
		return -1;
	}

    //pcpr权值数据
    snprintf(tpfile, sizeof(tpfile), "%s%s", pconf.inpath,
            pconf.lrweight_list_data);
    if (read_file_in_mem(tpfile, (void **) &(p_global.lrweight_list),
            sizeof(float), 0, &(p_global.max_lrweight_list_len)) < 0)
    {
        WARNING_LOG("cant load lrweight_list_data");
        return -1;
    }

    //y_song数据
    snprintf(tpfile, sizeof(tpfile), "%s%s", pconf.inpath,
            pconf.ysong_list_data);
    if (read_file_in_mem(tpfile, (void **) &(p_global.ysong_list),
            sizeof(y_song_info), 0, &(p_global.max_ysong_list_len)) < 0)
    {
        WARNING_LOG("cant load ysong_list_data");
        return -1;
    }

    //y_channel数据
    snprintf(tpfile, sizeof(tpfile), "%s%s", pconf.inpath,
            pconf.ychannel_list_data);
    if (read_file_in_mem(tpfile, (void **) &(p_global.ychannel_list),
            sizeof(song_id_t), 0, &(p_global.max_ychannel_list_len)) < 0)
    {
        WARNING_LOG("cant load ychannel_list_data");
        return -1;
    }

    //ticket数据
    snprintf(tpfile, sizeof(tpfile), "%s%s", pconf.inpath,
            pconf.ticket_list_data);
    if (read_file_in_mem(tpfile, (void **) &(p_global.ticket_list),
            sizeof(Ticket_info_t), 0, &(p_global.max_ticket_list_len)) < 0)
    {
        WARNING_LOG("cant load ticket_list");
        return -1;
    }

    //tail_song加载
    snprintf(tpfile, sizeof(tpfile), "%s%s", pconf.inpath,
            pconf.tail_song_data);
    if (read_file_in_mem(tpfile, (void **) &(p_global.tail_song_list),
            sizeof(tail_song_t), 0, &(p_global.max_tail_song_list_len)) < 0)
    {
        WARNING_LOG("cant load tail_song_data");
        return -1;
    }

    //加载频道歌曲列表数据
	snprintf(tpfile, sizeof(tpfile), "%s%s", pconf.inpath,
			pconf.chsonglist_data);
	if (read_file_in_mem(tpfile, (void **) &(p_global.ch_song_list),
			sizeof(song_id_t), 0, &(p_global.max_chsonglist_len)) < 0)
	{
		WARNING_LOG("cant load chsonglist_data");
		return -1;
	}

    //加载公用频道关联歌曲列表数据
	snprintf(tpfile, sizeof(tpfile), "%s%s", pconf.inpath,
			pconf.publicrsong_data);
	if (read_file_in_mem(tpfile, (void **) &(p_global.public_rsong_list),
			sizeof(Song_item_t), 0, &(p_global.max_publicrsong_len)) < 0)
	{
		WARNING_LOG("cant load publicrsong_data");
		return -1;
	}

    //加载公用频道歌手关联歌曲列表数据
	snprintf(tpfile, sizeof(tpfile), "%s%s", pconf.inpath,
			pconf.publicrsingersong_data);
	if (read_file_in_mem(tpfile, (void **) &(p_global.public_rsingersong_list),
			sizeof(Song_item_t), 0, &(p_global.max_publicrsingersong_len)) < 0)
	{
		WARNING_LOG("cant load publicrsingersong_data");
		return -1;
	}

    //加载插入歌曲字典
	snprintf(tpfile, sizeof(tpfile), "%s%s", pconf.inpath,
			pconf.insertsong_data);
	if (read_file_in_mem(tpfile, (void **) &(p_global.insertsong_list),
			sizeof(song_id_t), 0, &(p_global.max_insertsong_len)) < 0)
	{
		WARNING_LOG("cant load insertsong_data");
		return -1;
	}

    //加载试探歌曲字典
    snprintf(tpfile, sizeof(tpfile), "%s%s", pconf.inpath,
            pconf.channel_detect_song_data);
    if (read_file_in_mem(tpfile, (void **) &(p_global.detectsong_list),
            sizeof(int), 0, &(p_global.max_channel_detect_song_len)) < 0)
    {
        WARNING_LOG("cant load channel_detect_song_dict");
        return -1;
    }

    //加载试探歌曲判断字典
    snprintf(tpfile, sizeof(tpfile), "%s%s", pconf.inpath,
            pconf.detect_judge_song_data);
    if (read_file_in_mem(tpfile, (void **) &(p_global.detectjudge_list),
            sizeof(int), 0, &(p_global.max_detectjudge_song_len)) < 0)
    {
        WARNING_LOG("cant load detect_judge_song_data");
        return -1;
    }

    //加载推广歌曲字典
    snprintf(tpfile, sizeof(tpfile), "%s%s", pconf.inpath,
            pconf.spread_song_data);
    if (read_file_in_mem(tpfile, (void **) &(p_global.spreadsong_list),
            sizeof(spread_song_t), 0, &(p_global.max_spreadsonglist_len)) < 0)
    {
        WARNING_LOG("cant load spread_song_data");
        p_global.max_spreadsonglist_len = 0;
		//推广歌曲加载失败时，不错误返回
		//return -1;
    }

    //加载公共频道音乐人歌曲字典
    snprintf(tpfile, sizeof(tpfile), "%s%s", pconf.inpath,
            pconf.yyr_chsong_data);
    if (read_file_in_mem(tpfile, (void **) &(p_global.yyrchsong_list),
            sizeof(uint64_t), 0, &(p_global.max_yyrchsonglist_len)) < 0)
    {
        WARNING_LOG("cant load yyr_chsong_data");
        p_global.max_yyrchsonglist_len = 0;
		//音乐人歌曲加载失败时，不错误返回
		//return -1;
    }

	//加载冷启动歌手列表
	snprintf(tpfile, sizeof(tpfile), "%s%s", pconf.inpath,
			pconf.cold_start_singer_fname);
	if (read_file_in_mem(tpfile, (void **) &(p_global.cold_start_singer_list),
			sizeof(uint64_t), 0, &(p_global.cold_start_singer_len)) < 0)
	{
		FATAL_LOG("cant load cold start singer data");
		return -1;
	}

	//加载ting id 映射数据
	snprintf(tpfile, sizeof(tpfile), "%s%s", pconf.inpath,
			pconf.ting_artist_id);
	if (read_file_in_mem(tpfile, (void **) &(p_global.ting_artist_id),
			sizeof(singer_id_t), 0, &(p_global.ting_artist_id_len)) < 0)
	{
		FATAL_LOG("cant load ting artist id data");
		return -1;
	}
    p_global.quku_ting_artistid.create(5000);
    singer_id_t* singer_id;
    for(int i = 0; i < p_global.ting_artist_id_len; i++){
        p_global.quku_ting_artistid.set(p_global.ting_artist_id[i].oid, p_global.ting_artist_id[i].qid);
    }
	//初始化数据buff
	if (g_config.work_threadnum > 0){
		td = (Svr_buf_t *)malloc(g_config.work_threadnum * sizeof(Svr_buf_t));
		if (NULL == td)
		{
			FATAL_LOG(" malloc for thread bufdat failed, work_threadnum:%d",g_config.work_threadnum);
			return -1;
		}
		for (i = 0; i < g_config.work_threadnum; i++)
		{
            td[i].svr_data = new std::queue<Svr_thread_data_t>();
            if(NULL == td[i].svr_data){
                FATAL_LOG("create thread queue fail");
                return -1;
            }
			if( 0 != pthread_mutex_init(&(td[i].write_mutex),NULL))
			{
				FATAL_LOG("pthread_mutex_init data_mutex failed for [%d] worker thread",i);
				myExit(-1);
			}
		}
	}
//	//////////////init global vars///////////

	double tmp_double=0;
	for(i =0; i < MAX_DAY; ++i)
	{
	    if(i < 10){
    	    tmp_double = (double)(-1*(i*REDUCE_RATE_DAY));
		    g_config.WConf.day_w[i] = exp(tmp_double/18);
        }
        else{
            tmp_double = (double)(-1*(i*REDUCE_RATE_DAY));
		    g_config.WConf.day_w[i] = exp(tmp_double/10);

        }
	}
    for(i =0; i < MAX_NUM; ++i)
	{
		tmp_double = (double)(-1*(i*REDUCE_RATE_NUM));
		g_config.WConf.num_w[i] = exp(tmp_double/10);
	}
	for(i=0; i <= MAX_WEIGHT; ++i)
	{
		for(j=0; j<= MAX_PERCENT; ++j)
		{
			g_config.WConf.good_weight_table[i][j] = (int)(100*pow((double)i/100, exp(-1*(double)j/MAX_PERCENT)));
		}
		g_config.WConf.bad_weight_table[i] = (int)(pow(i,2)/100);
	}


	return 0;
}

/**
 * @brief  处理传入参数
 * @param
 * @return
 */
int parse_options(int argc, char **argv, char *conf_file, int length)
{
	int err = 0;
	switch (argc)
	{
	case 1:
		snprintf(conf_file, length, "%s", DEFAULT_CONF_FILE);
		break;
	case 2:
		if ('-' == argv[1][0])
		{
			if (0 == strncmp(argv[1], "-h", 2) || 0 == strncmp(argv[1],
					"--help", 6))
			{
				usage();
			}
			if (0 == strncmp(argv[1], "-v", 2) || 0 == strncmp(argv[1],
					"--version", 9))
			{
				printf("%s %s\n", PROJECT_NAME, VERSION);
			}
			err = 1;
		}
		else
		{
			snprintf(conf_file, length, "%s", argv[1]);
		}
		break;
	default:
		err = 1;
		break;
	};
	if (1 == err)
	{
		usage();
	}

	return err;
}

/**
 * @brief  打印帮助信息
 * @param
 * @return
 */
void usage()
{
	printf("\n");
	printf("Project  : %s\n", PROJECT_NAME);
	//prntf("BuildDate: %s\n", BuildDate);
	printf("Version  : %s\n", VERSION);

	printf("\nusage: %s [option] [conf]\n", PROJECT_NAME);
	printf("option:\n");
	printf("\t-v|--version  show the version of %s\n", PROJECT_NAME);
	printf("\t-h|--help	 show this help message of %s\n", PROJECT_NAME);
	printf("conf: the configure file for %s. default is %s\n", PROJECT_NAME,
			DEFAULT_CONF_FILE);
	printf("\n%s\n", PROJECT_DESCRIPTION);
}

/**
 * ===================  FUNCTION emain ==============================
 * @brief thread callback function  for listening socket
 *
 * @param [in] arg all the parameter
 * @param [out]
 *
 * @return void
 * @retval errno
 *
 * @author zhangjunying, zhangjunying@baidu.com
 * @date 12/01/2010 10:39:40 AM
 * @company Baidu Inc.
 * ==============================================================================
 */
void *emain(void *arg)
{
	int fd_listen;
    int ret;
	ret = com_openlog_r();
	if (0 != ret)
	{
		printf("%s", "[fatal error] open log in thread emain fail, exit.\n");
		myExit(1);
	}
	DEBUG_LOG("emain open log success, use ul_log.\n");

	fd_listen = ul_tcplisten(g_config.listenport, g_config.listennum);
	if (-1 == fd_listen)
	{
		FATAL_LOG("listening socket[port: %d] error, exit.\n",g_config.listenport);
		myExit(-1);
	}
	DEBUG_LOG("listening port: %d.", g_config.listenport);

	int on = 1;
	ret = ul_setsockopt(fd_listen, IPPROTO_TCP, TCP_NODELAY, &on, sizeof(on));
	if (0 != ret)
	{
		WARNING_LOG("set socket option: [IPPROTO_TCP TCP_NODELAY] fail, exit");
	}
	DEBUG_LOG("set socket[fd: %d, port: %d] option [IPPROTO_TCP TCP_NODELAY]",
			fd_listen, g_config.listenport);

	g_svr_pool.set_conn_timeo(g_config.ctimeout);
	g_svr_pool.set_read_timeo(g_config.rtimeout);
	g_svr_pool.set_write_timeo(g_config.wtimeout);
	g_svr_pool.set_listen_fd(fd_listen);
	TRACE_LOG("EPENDINGPOOL PARAMETER: \
			listening fd: %d, \
			connect timeout: %d, \
			read timeout: %d, \
			write timeout: %d, \
			sock_num: %d.",
			fd_listen,
			g_config.ctimeout,
			g_config.rtimeout,
			g_config.wtimeout,
			g_config.max_sock_num);

	TRACE_LOG("EPENDINGPOOL IS RUNNING");
	while (g_svr_pool.is_run())
	{
		g_svr_pool.check_item();
	}
	TRACE_LOG("EPENDINGPOOL IS STOPED");

//	ul_closelog_r(0);
	if (fd_listen > 0)
	{
		ul_close(fd_listen);
		fd_listen = -1;
	}
	com_closelog_r();

	return NULL;
}

int
init_redis(){
    int ret;
    //ret = ub_log_init("./log", "redis_log.");
    p_global.redis_cli = new store::RedisClientManager;
    if(NULL == p_global.redis_cli){
        FATAL_LOG("RedisClientManager create failed\n");
        return -1;
    }

    ret = p_global.redis_cli->init(g_config.redis_conf_path, g_config.redis_conf_file);
    if(ret != 0){
        FATAL_LOG("RedisClientManager init failed\n");
        return -1;
    }

    ret = p_global.redis_cli->create_client_pool(g_config.redis_client_num);
    if(ret != 0){
        FATAL_LOG("create client pool failed\n");
        return -1;
    }

    srand((int) time(0));
    NOTICE_LOG("create client pool success [%d]", g_config.redis_client_num);
    return 0;
}

int
destroy_redis(){
    if(NULL == p_global.redis_cli){
        FATAL_LOG("redis client exception\n");
        return -1;
    }

    int ret;
    ret = p_global.redis_cli->destroy_client_pool();
    if(ret != 0){
        FATAL_LOG("destroy client failed\n");
        return -1;
    }

    p_global.redis_cli->close();
    NOTICE_LOG("destroy client pool success");
    return 0;
}

/**
 * 读取字符串配置项
 *
 */
inline void load_conf_item(Ul_confdata* pcf, char *name, char *p,
		const char *def_value, int max_len = MAX_DIR_LEN)
{
	if (!ul_getconfstr(pcf, name, p))
	{
		snprintf(p, max_len, "%s", def_value);
	}
}
/**
 * 读取int配置项
 *
 */
inline void load_conf_item(Ul_confdata* pcf, char *name, int* p,
		const int def_value)
{
	if (!ul_getconfint(pcf, name, p))
	{
		*p = def_value;
	}
}
/**
 * 读取uint配置项
 *
 */
inline void load_conf_item(Ul_confdata* pcf, char *name, uint *p,
		const uint def_value)
{
	if (!ul_getconfuint(pcf, name, p))
	{
		*p = def_value;
	}
}

/**
 * @brief 拷贝字符串
 * @param
 * @return
 */
inline void setStrParam(char *des, const char *src, int length)
{
	strncpy(des, src, length);
	des[length - 1] = 0;
	FixLastChr(des);
}

/**
 * @brief 关闭文件指针
 * @param p:文件指针
 * @return
 */
inline void closeFP(FILE **p)
{
	if(p != NULL && *p != NULL)
	{
		fclose(*p);
		*p = NULL;
	}
}

/**
 * 内存指针清理的宏定义函数
 */
template<class T> void freePointer(T* p)
{
	if(p && *p)
	{
		free(*p);
		*p = NULL;
	}
}

/**
 * @brief 数据buffer清理函数
 * @param
 * @return
 */
int Clear()
{
	if(p_global.bigDict)
	{
		odb_destroy_search(p_global.bigDict);
	}
	freePointer(&p_global.songsonglist);
	freePointer(&p_global.singersingerlist);
	freePointer(&p_global.singersonglist);
	freePointer(&p_global.songbrieflist);
	freePointer(&p_global.districtsingerlist);
	freePointer(&p_global.defaultlist);
	for(int i = 0; i < g_config.work_threadnum; ++i)
	{
		pthread_mutex_destroy(&td[i].write_mutex);
	}
	freePointer(&td);
    destroy_redis();
//	freePointer(mbtimer_arr);
	return 0;
}

/**
 * @brief 自杀退出
 */
void myExit(int ret)
{
	while (1){
		raise(SIGKILL);
	}
    destroy_redis();
    NOTICE_LOG("rls exit[%d]", ret);
}


