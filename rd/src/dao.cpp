/**
 * =====================================================================================
 *
 *	Filename:  dao.cpp
 *
 *	Description:  header file for dao.cpp
 *
 *	Version:  1.0
 *  Created: 2011-6-6
 *	Revision:  none
 *	Compiler:  gcc
 *
 *	Author:  zhangjunying, zhangjunying@baidu.com
 *	Company:  baidu.com Inc.
 *
 * =====================================================================================
 */

#include "dao.h"
#include "common.h"
#include <algorithm>
#include "bsl/map.h"
#include "rls_dictseeker.h"

/***
* @brief 时间戳格式为成字符串
*/
void FormatTime(time_t time1, char *szTime, int szLen)
{
	struct tm tm1;
	localtime_r(&time1, &tm1);
	snprintf(szTime, szLen, "%4.4d-%2.2d-%2.2d %2.2d:%2.2d:%2.2d", tm1.tm_year
		+ 1900, tm1.tm_mon + 1, tm1.tm_mday, tm1.tm_hour, tm1.tm_min,
		tm1.tm_sec);
	szTime[szLen-1] = 0;
}

/***
* @brief 时间戳格式为成字符串,随机为当天的某个时间点
*/
void FormatRandomTime(time_t time1, char *szTime, int szLen)
{
	time1 = (time1/SECONDS_OF_DAY) * SECONDS_OF_DAY + rand()%SECONDS_OF_DAY;
	struct tm tm1;
	localtime_r(&time1, &tm1);
	snprintf(szTime, szLen, "%4.4d-%2.2d-%2.2d %2.2d:%2.2d:%2.2d", tm1.tm_year
		+ 1900, tm1.tm_mon + 1, tm1.tm_mday, tm1.tm_hour, tm1.tm_min,
		tm1.tm_sec);
	szTime[szLen-1] = 0;
}

/***
* @brief 字符串格式化为时间戳
*/
time_t FormatTime2(const char * szTime)
{
	struct tm tm1;
	time_t time1;
	int ret = sscanf(szTime, "%4d-%2d-%2d %2d:%2d:%2d", &tm1.tm_year,
		&tm1.tm_mon, &tm1.tm_mday, &tm1.tm_hour, &tm1.tm_min, &tm1.tm_sec);
	if(ret < 0)
	{
		return (time_t)-1;
	}
	tm1.tm_year -= 1900;
	tm1.tm_mon--;
	tm1.tm_isdst = -1;
	time1 = mktime(&tm1);
	return time1;
}

/***
* @brief 获取一年前的时间字符串
*/
void YearBefore(char *szTime, int szLen){
	struct tm tm1;
	time_t time1 = time (NULL);
	time1 -= 86400 * 360;
	localtime_r(&time1, &tm1);
	snprintf(szTime, szLen, "%4.4d-%2.2d-%2.2d %2.2d:%2.2d:%2.2d", tm1.tm_year
		+ 1900, tm1.tm_mon + 1, tm1.tm_mday, tm1.tm_hour, tm1.tm_min,
		tm1.tm_sec);
	szTime[szLen-1] = 0;
}

/**
 * @berif 一个简单的fail_handle处理函数，只是打印出错误
 * */
void fail_handler(MysqlConnection *conn, const char *sql)
{
	FATAL_LOG("[ddbs_fatal] [query error: errno[%d], error[%s], sql[%s]]\n",
        conn->getMysqlErrno(), conn->getMysqlError(), sql);
}

/**
 * @berif 一个简单的fail_handle处理函数，只是打印出错误, WARNING日志
 * */
void fail_handler_warning(MysqlConnection *conn, const char *sql)
{
	WARNING_LOG("[ddbs_warning] [query error: errno[%d], error[%s], sql[%s]]\n",
        conn->getMysqlErrno(), conn->getMysqlError(), sql);
}

/**
 * 对行为列表按照id(升序) type(升序) 时间(降序)排序
 */
bool behavior_all_cmp(Action_bean a, Action_bean b)
{
	if(a.itemid < b.itemid)
	{
		return true;
	}
	else if(a.itemid > b.itemid)
	{
		return false;
	}

	if(a.type < b.type)
	{
		return true;
	}
	else if(a.type > b.type)
	{
		return false;
	}

	return a.date > b.date;
}

/**
 * 对行为列表按照时间排序，降序
 */
bool behavior_date_cmp(Action_bean a, Action_bean b)
{
	return a.date > b.date;
}

/**
 * 完成ddbs不支持的group by soid,type order by m_date
 * p_benas 行为列表
 * bean_len 列表长度
 * return void
 */
void mergeUserBehavior(Action_bean*p_benas, int& bean_len)
{
	if(!p_benas || bean_len < 1)
	{
		return;
	}

	std::sort(p_benas, p_benas+bean_len, behavior_all_cmp);

	int i=1;
	int j=1;
	uint pre_itemid = p_benas[0].itemid;
	int pre_type = p_benas[0].type;
	//merge the same id and type with max time
	for(i=1, j=1; i < bean_len; ++i)
	{
		if(p_benas[i].itemid != pre_itemid || p_benas[i].type != pre_type)
		{
			p_benas[j++] = p_benas[i];
		}
	}
	bean_len = j;

	std::sort(p_benas, p_benas+bean_len, behavior_date_cmp);
}


/**
 * 查询用户行为数据
 * uid 用户id(用户名的签名)
 * p_beans 数据的buf,由外部初始化
 * bean_len 数据buf的长度
 * return >=0 成功并返回获取数据的长度 -1失败
 *
 */
int db_get_user_real_behavior(unsigned int uid, Action_bean*p_benas, enum DB_USER_BEHAVIOR_TYPE type, int bean_len)
{
	struct timeval s;
	struct timeval e;
	gettimeofday(&s,NULL);
	MyclientRes res;
	int err = 0;
	int result = 0;
	bool reconnect = false;
	int i = 0;

	MysqlConnection *test_connection = p_global.dbpool->fetchConnection(
			MYCLIENT_AVERAGE_HOST_TYPE, &err, 0);
	if (test_connection == NULL)
	{
		gettimeofday(&e,NULL);
		FATAL_LOG("[ddbs_fatal], cost[%d], [error in fetch, err[%d]]", TIMEMSECDIFF(s, e), err);
		return -1;
	}
	test_connection->setFailHandler(fail_handler);
	DEBUG_LOG("get connection ok!");

	char timeStr[MAX_DIR_LEN];
	YearBefore(timeStr, MAX_DIR_LEN);
	char query[] =
		"select soid, m_type, m_date, ch_name from user_real_behavior where uid=%u and m_type = %d and m_date > '%s' ORDER BY m_date DESC LIMIT %d";
	err = test_connection->queryf(&res, true, query, uid, type, timeStr, bean_len);
	DEBUG_LOG("sql execute[select soid, m_type, m_date, ch_name from user_real_behavior where uid=%u and m_type = %d and m_date > '%s' ORDER BY m_date DESC LIMIT %d]", \
		uid, type, timeStr, bean_len);

	if (err < success)
	{
        gettimeofday(&e,NULL);
        FATAL_LOG("[ddbs_fatal], cost[%d],  msg[db_get_user_real_behavior], uid[%u], [sql error. myclient err[%d]]", TIMEMSECDIFF(s, e), uid, err);
		result = -1;
		reconnect = true;
	}
	else
	{
		unsigned int rows_count = res.getRowsCount();
		if (rows_count > 0)
		{
			const char *itemid = NULL;
			const char *t_date = NULL;
			const char *m_type = NULL;
			const char *ch_name = NULL;
			for (i = 0; (unsigned int) i < rows_count && i < bean_len; i++)
			{
				itemid = res[i][0];
				m_type = res[i][1];
				t_date = res[i][2];
				ch_name = res[i][3];
				p_benas[i].itemid = (unsigned int) atoi(itemid);
				p_benas[i].date = FormatTime2(t_date);
				strcpy(p_benas[i].ch_name, ch_name);
				p_benas[i].type = atoi(m_type);
			}
			bean_len = i;
		}
		else
		{
			bean_len = 0;
		}
		mergeUserBehavior(p_benas, bean_len);
		result = bean_len;
	}

	res.free();
	int ret = p_global.dbpool->putBackConnection(test_connection, reconnect);
	if (ret != 0)
	{
        gettimeofday(&e,NULL);
        WARNING_LOG("third[ddbs_third_fail], cost[%d], [putback connection ret[%d]]", TIMEMSECDIFF(s, e), ret);
		return -1;
	}
	DEBUG_LOG("put back connection ok!\n");
    //ddbs正常处理请求
    if(result >= 0){
        gettimeofday(&e,NULL);
        NOTICE_LOG("third[ddbs_third], msg[db_get_user_real_behavior], uid[%u], cost[%d]", uid, TIMEMSECDIFF(s, e));
    }
	return result;
}


/**
 * 查询音乐盒用户行为数据
 * uid 用户id(用户名的签名)
 * p_beans 数据的buf,由外部初始化
 * bean_len 数据buf的长度
 * return >=0 成功并返回获取数据的长度 -1失败
 *
 */
int db_get_user_behavior(unsigned int uid, Action_bean*p_benas, int bean_len)
{
	struct timeval s;
	struct timeval e;
	gettimeofday(&s,NULL);
	MyclientRes res;
	int err = 0;
	int result = 0;
	bool reconnect = false;
	int i = 0;

	MysqlConnection *test_connection = p_global.dbpool->fetchConnection(
			MYCLIENT_AVERAGE_HOST_TYPE, &err, 0);
	if (test_connection == NULL)
	{
		gettimeofday(&e,NULL);
		FATAL_LOG("[ddbs_fatal], cost[%d], [error in fetch, err[%d]]", TIMEMSECDIFF(s, e), err);
		return -1;
	}
	test_connection->setFailHandler(fail_handler);
	DEBUG_LOG("get connection ok!");

	char timeStr[MAX_DIR_LEN];
	YearBefore(timeStr, MAX_DIR_LEN);
	char query[] =
		"select soid, m_type, m_date, ch_name from user_behavior where uid=%u and m_date > '%s' ORDER BY m_date DESC LIMIT %d";
	err = test_connection->queryf(&res, true, query, uid, timeStr, bean_len);
	DEBUG_LOG("sql execute[select soid, m_type, m_date, ch_name from user_behavior where uid=%u and m_date > '%s' ORDER BY m_date DESC LIMIT %d]", \
		uid, timeStr, bean_len);

	if (err < success)
	{
        gettimeofday(&e,NULL);
        FATAL_LOG("[ddbs_fatal], cost[%d],  msg[db_get_user_behavior], uid[%u], [sql error. myclient err[%d]]", TIMEMSECDIFF(s, e), uid, err);
		result = -1;
		reconnect = true;
	}
	else
	{
		unsigned int rows_count = res.getRowsCount();
		if (rows_count > 0)
		{
			const char *itemid = NULL;
			const char *t_date = NULL;
			const char *m_type = NULL;
			const char *ch_name = NULL;
			for (i = 0; (unsigned int) i < rows_count && i < bean_len; i++)
			{
				itemid = res[i][0];
				m_type = res[i][1];
				t_date = res[i][2];
				ch_name = res[i][3];
				p_benas[i].itemid = (unsigned int) atoi(itemid);
				p_benas[i].date = FormatTime2(t_date);
				strcpy(p_benas[i].ch_name, ch_name);
				p_benas[i].type = atoi(m_type);
			}
			bean_len = i;
		}
		else
		{
			bean_len = 0;
		}
		result = bean_len;
	}

	res.free();
	int ret = p_global.dbpool->putBackConnection(test_connection, reconnect);
	if (ret != 0)
	{
        gettimeofday(&e,NULL);
        WARNING_LOG("third[ddbs_third_fail], cost[%d], [putback connection ret[%d]]", TIMEMSECDIFF(s, e), ret);
		return -1;
	}
	DEBUG_LOG("put back connection ok!\n");
    //ddbs正常处理请求
    if(result >= 0){
        gettimeofday(&e,NULL);
        NOTICE_LOG("third[ddbs_third], msg[db_get_user_behavior], uid[%u], cost[%d]", uid, TIMEMSECDIFF(s, e));
    }
	return result;
}


/**
 * 查询音乐盒cookie用户行为数据
 * uid 用户id(用户名的签名)
 * p_beans 数据的buf,由外部初始化
 * bean_len 数据buf的长度
 * return >=0 成功并返回获取数据的长度 -1失败
 *
 */
int db_get_co_user_behavior(unsigned int uid, Action_bean*p_benas, int bean_len)
{
	struct timeval s;
	struct timeval e;
	gettimeofday(&s,NULL);
	MyclientRes res;
	int err = 0;
	int result = 0;
	bool reconnect = false;
	int i = 0;

	MysqlConnection *test_connection = p_global.dbpool->fetchConnection(
			MYCLIENT_AVERAGE_HOST_TYPE, &err, 0);
	if (test_connection == NULL)
	{
		gettimeofday(&e,NULL);
		FATAL_LOG("[ddbs_fatal], cost[%d], [error in fetch, err[%d]]", TIMEMSECDIFF(s, e), err);
		return -1;
	}
	test_connection->setFailHandler(fail_handler);
	DEBUG_LOG("get connection ok!");

	char timeStr[MAX_DIR_LEN];
	YearBefore(timeStr, MAX_DIR_LEN);
	char query[] =
		"select itemid, m_type, m_date, ch_name from co_user_behavior where baiduid=%u and m_date > '%s' ORDER BY m_date DESC LIMIT %d";
	err = test_connection->queryf(&res, true, query, uid, timeStr, bean_len);
	DEBUG_LOG("sql execute[select soid, m_type, m_date, ch_name from co_user_behavior where baiduid=%u and m_date > '%s' ORDER BY m_date DESC LIMIT %d]", \
		uid, timeStr, bean_len);

	if (err < success)
	{
        gettimeofday(&e,NULL);
        FATAL_LOG("[ddbs_fatal], cost[%d],  msg[db_get_co_user_behavior], baiduid[%u], [sql error. myclient err[%d]]", TIMEMSECDIFF(s, e), uid, err);
		result = -1;
		reconnect = true;
	}
	else
	{
		unsigned int rows_count = res.getRowsCount();
		if (rows_count > 0)
		{
			const char *itemid = NULL;
			const char *t_date = NULL;
			const char *m_type = NULL;
			const char *ch_name = NULL;
			for (i = 0; (unsigned int) i < rows_count && i < bean_len; i++)
			{
				itemid = res[i][0];
				m_type = res[i][1];
				t_date = res[i][2];
				ch_name = res[i][3];
				p_benas[i].itemid = (unsigned int) atoi(itemid);
				p_benas[i].date = FormatTime2(t_date);
				strcpy(p_benas[i].ch_name, ch_name);
				p_benas[i].type = atoi(m_type);
			}
			bean_len = i;
		}
		else
		{
			bean_len = 0;
		}
		result = bean_len;
	}

	res.free();
	int ret = p_global.dbpool->putBackConnection(test_connection, reconnect);
	if (ret != 0)
	{
        gettimeofday(&e,NULL);
        WARNING_LOG("third[ddbs_third_fail], cost[%d], [putback connection ret[%d]]", TIMEMSECDIFF(s, e), ret);
		return -1;
	}
	DEBUG_LOG("put back connection ok!\n");
    //ddbs正常处理请求
    if(result >= 0){
        gettimeofday(&e,NULL);
        NOTICE_LOG("third[ddbs_third], msg[db_get_co_user_behavior], baiduid[%u], cost[%d]", uid, TIMEMSECDIFF(s, e));
    }
	return result;
}


int db_get_co_user_real_behavior(unsigned int baiduid, Action_bean*p_benas, enum DB_USER_BEHAVIOR_TYPE type, int bean_len)
{
	struct timeval s;
	struct timeval e;
	gettimeofday(&s,NULL);
	MyclientRes res;
	int err = 0;
	int result = 0;
	bool reconnect = false;
	int i = 0;

	MysqlConnection *test_connection = p_global.dbpool->fetchConnection(
			MYCLIENT_AVERAGE_HOST_TYPE, &err, 0);
	if (test_connection == NULL)
	{
		gettimeofday(&e,NULL);
		FATAL_LOG("[ddbs_fatal], cost[%d], [error in fetch, err[%d]]", TIMEMSECDIFF(s, e), err);
		return -1;
	}
	test_connection->setFailHandler(fail_handler);
	DEBUG_LOG("get connection ok!");

	char timeStr[MAX_DIR_LEN];
	YearBefore(timeStr, MAX_DIR_LEN);
	char query[] =
		"select itemid, m_type, m_date, ch_name from co_user_real_behavior where baiduid=%u and m_type = %d and m_date > '%s' ORDER BY m_date DESC LIMIT %d";
	err = test_connection->queryf(&res, true, query, baiduid, type, timeStr, bean_len);
	DEBUG_LOG("sql execute[select itemid, m_type, m_date, ch_name from co_user_real_behavior where baiduid=%u and m_type = %d and m_date > '%s' ORDER BY m_date DESC LIMIT %d]", \
		baiduid, type, timeStr, bean_len);

	if (err < success)
	{
        gettimeofday(&e,NULL);
        FATAL_LOG("[ddbs_fatal], cost[%d],  msg[db_get_co_user_real_behavior], baiduid[%u], [sql error. myclient err[%d]]", TIMEMSECDIFF(s, e), baiduid, err);
		result = -1;
		reconnect = true;
	}
	else
	{
		unsigned int rows_count = res.getRowsCount();
		if (rows_count > 0)
		{
			const char *itemid = NULL;
			const char *t_date = NULL;
			const char *m_type = NULL;
			const char *ch_name = NULL;
			for (i = 0; (unsigned int) i < rows_count && i < bean_len; i++)
			{
				itemid = res[i][0];
				m_type = res[i][1];
				t_date = res[i][2];
				ch_name = res[i][3];
				p_benas[i].itemid = (unsigned int) atoi(itemid);
				p_benas[i].date = FormatTime2(t_date);
				strcpy(p_benas[i].ch_name, ch_name);
				p_benas[i].type = atoi(m_type);
			}
			bean_len = i;
		}
		else
		{
			bean_len = 0;
		}
		mergeUserBehavior(p_benas, bean_len);
		result = bean_len;
	}

	res.free();
	int ret = p_global.dbpool->putBackConnection(test_connection, reconnect);
	if (ret != 0)
	{
        gettimeofday(&e,NULL);
        WARNING_LOG("third[ddbs_third_fail], cost[%d], [putback connection ret[%d]]", TIMEMSECDIFF(s, e), ret);
		return -1;
	}
	DEBUG_LOG("put back connection ok!\n");
    //ddbs正常处理请求
    if(result >= 0){
        gettimeofday(&e,NULL);
        NOTICE_LOG("third[ddbs_third], msg[db_get_co_user_real_behavior], baiduid[%u], cost[%d]", baiduid, TIMEMSECDIFF(s, e));
    }
	return result;
}

/**
 * 查询ral列表数据
 * uid 用户id(用户名的签名)
 * ch_name 频道名
 * r_type 列表类型
 * cf_list 数据的buf,由外部初始化
 * max 数据buf的长度
 *
 * return >=0 成功并返回获取数据的长度 -1失败
 */
int db_get_ral_list(unsigned int uid, const char *ch_name, uint r_type, Song_item_t* cf_list, int source, uint max_len)
{
	struct timeval s;
    struct timeval e;
    gettimeofday(&s,NULL);
    MyclientRes res;
    DictSeeker* _dict_seeker = new DictSeeker();
	int err = 0;
	int result = 0;
	bool reconnect = false;
	MysqlConnection *test_connection = p_global.dbpool->fetchConnection(
			MYCLIENT_AVERAGE_HOST_TYPE, &err, 0);
	if (test_connection == NULL)
	{
        gettimeofday(&e,NULL);
        FATAL_LOG("[ddbs_fatal], cost[%d], [error in fetch, err[%d]]", TIMEMSECDIFF(s, e), err);
        if(NULL != _dict_seeker){
            delete _dict_seeker;
        }
		return -1;
	}
	test_connection->setFailHandler(fail_handler);
	DEBUG_LOG("get connection ok!");
	char query[] =
		"select r_list from user_list where uid=%u and r_type=%d and ch_name='%s'";
#ifdef _DEBUG_TIME
        DEBUG_LOG("ral_db_request[select r_list from user_list where uid=%u and r_type=%d and ch_name='%s']",\
        	uid, r_type, ch_name);
#endif
	err = test_connection->queryf(&res, true, query, uid, r_type, ch_name);
	if (err < success)
	{
        gettimeofday(&e,NULL);
        FATAL_LOG("[ddbs_fatal], cost[%d], [sql error. myclient err[%d]]", TIMEMSECDIFF(s, e), err);
		result = -1;
		reconnect = true;
	}
	else
	{
		unsigned int rows_count = res.getRowsCount();
		if(rows_count > 0){
			uint len = 0;
			char * tmp_r_list = res[0][0];
			char * out = NULL;
			char *tmp_song_item = strtok_r(tmp_r_list,",",&out);
			while(tmp_song_item!=NULL && len < max_len)
			{
				char *split_str = strchr(tmp_song_item, ':');
				if(split_str == NULL){
					WARNING_LOG("the cf list in db is format error, uid[%u],ch_name[%s],r_type[%d]", uid, ch_name, r_type);
				}
				else{
					*split_str = '\0';
					uint song_weight = atoi(++split_str);
					uint song_id = atoi(tmp_song_item);
                    if(NULL == _dict_seeker->get_song_brief(song_id)){
                        tmp_song_item = strtok_r(NULL, ",", &out);
                        continue;
                    }
					cf_list[len].song_id = song_id;
					cf_list[len].weight = song_weight;
					cf_list[len].source = source;
				}
				len ++;
				tmp_song_item = strtok_r(NULL, ",", &out);
			}
			result =  len;
		}
		else
		{
			WARNING_LOG("no cf list exist, uid[%u],ch_name[%s],r_type[%d]", uid, ch_name, r_type);
		}
	}

    if(NULL != _dict_seeker){
        delete _dict_seeker;
    }
	res.free();
	int ret = p_global.dbpool->putBackConnection(test_connection, reconnect);
	if (ret != 0)
	{
		gettimeofday(&e,NULL);
        WARNING_LOG("third[ddbs_third_fail], cost[%d], [putback connection ret[%d]]", TIMEMSECDIFF(s, e), ret);
		return -1;
	}
	DEBUG_LOG("put back connection ok!\n");
    //ddbs正常处理请求
    if(result >= 0){
        gettimeofday(&e,NULL);
        NOTICE_LOG("third[ddbs_third], cost[%d]", TIMEMSECDIFF(s, e));
    }
	return result;
}

/**
 * 查询用户标签数据
 * uid 用户id(用户名的签名)
 * user_tag 数据的buf,由外部初始化
 * max 数据buf的长度
 *
 * return >=0 成功并返回获取数据的长度 -1失败
 */
int db_get_user_tags(unsigned int uid, User_tag_t* user_tag, uint max_len)
{
	struct timeval s;
    struct timeval e;
    gettimeofday(&s,NULL);
    MyclientRes res;
	int err = 0;
	int result = 0;
	bool reconnect = false;
	uint r_type = TAG_LIST_TYPE;//标签数据类型
	MysqlConnection *test_connection = p_global.dbpool->fetchConnection(
			MYCLIENT_AVERAGE_HOST_TYPE, &err, 0);
	if (test_connection == NULL)
	{
		gettimeofday(&e,NULL);
        FATAL_LOG("[ddbs_fatal], cost[%d], [error in fetch, err[%d]]", TIMEMSECDIFF(s, e), err);
		return -1;
	}
	test_connection->setFailHandler(fail_handler);

	DEBUG_LOG("get connection ok!");

	char query[] =
		"select r_list from user_list where uid=%u and r_type=%u";

	err = test_connection->queryf(&res, true, query, uid, r_type);
	if (err < success)
	{
		gettimeofday(&e,NULL);
        FATAL_LOG("[ddbs_fatal], cost[%d], [sql error. myclient err[%d]]", TIMEMSECDIFF(s, e), err);
		result = -1;
		reconnect = true;
	}
	else
	{
		unsigned int rows_count = res.getRowsCount();
		if(rows_count > 0){
			uint len = 0;
			char * tmp_r_list = res[0][0];
			char * out = NULL;
			DEBUG_LOG("tags[%s]", tmp_r_list);
			char *tmp_tag_item = strtok_r(tmp_r_list,"\7",&out);
			while(tmp_tag_item!=NULL && len < max_len)
			{
				DEBUG_LOG("tag[%s]", tmp_tag_item);
				uint tag_id = 0;
				char tag_title[USER_TAG_LEN];
				float tag_weight = 0.0;
				char *split_str1 = strchr(tmp_tag_item, '\5');
				if(split_str1 == NULL){
					WARNING_LOG("the user tag in db is format error, uid[%u], tags[%s]", uid, tmp_r_list);
					break;
				}
				*split_str1 = '\0';
				user_tag[len].tag_id = atoi(tmp_tag_item);
				split_str1 ++;
				char *split_str2 = strchr(split_str1, '\5');
				if(split_str2 == NULL){
					WARNING_LOG("the user tag in db is format error, uid[%u], tags[%s]", uid, tmp_r_list);
                    break;
				}
				*split_str2 = '\0';
				if(strlen(split_str1) + 1 >USER_TAG_LEN){
					WARNING_LOG("the user tag in db is format error, uid[%u], tags[%s]", uid, tmp_r_list);
					break;
				}
				strcpy(user_tag[len].tag_title,  split_str1);
				split_str2 ++;
				user_tag[len].tag_weight = (int)(atof(split_str2) * 100);
				len ++;
				tmp_tag_item = strtok_r(NULL, "\7", &out);
			}
			result =  len;
		}
		else
		{
			WARNING_LOG("no user tag exist, uid[%u]", uid);
		}
	}

	res.free();
	int ret = p_global.dbpool->putBackConnection(test_connection, reconnect);
	if (ret != 0)
	{
		gettimeofday(&e,NULL);
        WARNING_LOG("third[ddbs_third_fail], cost[%d], [putback connection ret[%d]]", TIMEMSECDIFF(s, e), ret);
		return -1;
	}
	DEBUG_LOG("put back connection ok!\n");
    //ddbs正常处理请求
    if(result >= 0){
        gettimeofday(&e,NULL);
        NOTICE_LOG("third[ddbs_third], cost[%d]", TIMEMSECDIFF(s, e));
    }
	return result;
}


int db_get_listen_history(unsigned int uid, Item_bean *p_benas, int bean_len)
{
	struct timeval s;
    struct timeval e;
    gettimeofday(&s,NULL);
    MyclientRes res;
	int err = 0;
	int result = 0;
	bool reconnect = false;
	int i = 0;

	MysqlConnection *test_connection = p_global.dbpool->fetchConnection(
			MYCLIENT_AVERAGE_HOST_TYPE, &err, 0);
	if (test_connection == NULL)
	{
		gettimeofday(&e,NULL);
        FATAL_LOG("[ddbs_fatal], cost[%d], [error in fetch, err[%d]]", TIMEMSECDIFF(s, e), err);
		return -1;
	}
	test_connection->setFailHandler(fail_handler);

	DEBUG_LOG("get connection ok!");


	char timeStr[MAX_DIR_LEN];
	YearBefore(timeStr, MAX_DIR_LEN);
	char query[] =
		"select soid, m_date, ch_name from listen_history where uid=%u and m_date > '%s' ORDER BY m_date DESC LIMIT %d";
	err	= test_connection->queryf(&res, true, query, uid, timeStr, bean_len);
	DEBUG_LOG("sql execute[select soid, m_date, ch_name from listen_history where uid=%u and m_date > '%s' ORDER BY m_date DESC LIMIT %d]", uid, timeStr, bean_len);

	if (err < success)
	{
		gettimeofday(&e,NULL);
        FATAL_LOG("[ddbs_fatal], cost[%d], msg[db_get_listen_history], uid[%u], [sql error. myclient err[%d]]", TIMEMSECDIFF(s, e), uid, err);
		result = -1;
		reconnect = true;
	}
	else
	{
		unsigned int rows_count = res.getRowsCount();

		if (rows_count > 0)
		{
			const char *soid = NULL;
			const char *t_date = NULL;
			const char *ch_name = NULL;
			for (i = 0; (unsigned int) i < rows_count && i < bean_len; i++)
			{
				soid = res[i][0];
				t_date = res[i][1];
				ch_name = res[i][2];
				p_benas[i].itemid = (unsigned int) atoi(soid);
				strcpy(p_benas[i].ch_name, ch_name);
				p_benas[i].date = FormatTime2(t_date);
			}
			rows_count = i;
		}
		else
		{
			rows_count = 0;
		}
		result = (int) rows_count;
	}

	res.free();
	int ret = p_global.dbpool->putBackConnection(test_connection, reconnect);
	if (ret != 0)
	{
		gettimeofday(&e,NULL);
        WARNING_LOG("third[ddbs_third_fail], cost[%d], [putback connection ret[%d]]", TIMEMSECDIFF(s, e), ret);
		return -1;
	}
	DEBUG_LOG("put back connection ok!\n");
    //ddbs正常处理请求
    if(result >= 0){
        gettimeofday(&e,NULL);
        NOTICE_LOG("third[ddbs_third], cost[%d]", TIMEMSECDIFF(s, e));
    }
	return result;
}


int db_get_y_user_behavior(unsigned int uid, Action_bean *p_benas, int bean_len)
{
	struct timeval s;
    struct timeval e;
    gettimeofday(&s,NULL);
    MyclientRes res;
	int err = 0;
	int result = 0;
	bool reconnect = false;
	int i = 0;

	MysqlConnection *test_connection = p_global.dbpool->fetchConnection(
			MYCLIENT_AVERAGE_HOST_TYPE, &err, 0);
	if (test_connection == NULL)
	{
		gettimeofday(&e,NULL);
        FATAL_LOG("[ddbs_fatal], cost[%d], [error in fetch, err[%d]]", TIMEMSECDIFF(s, e), err);
		return -1;
	}
	test_connection->setFailHandler(fail_handler);

	DEBUG_LOG("get connection ok!");


	time_t year_before = time (NULL);
	year_before -= 86400 * 360;
	char query[] =
		"select itemid, m_type, m_date, ch_name from y_user_behavior where uid=%u and m_date > %d ORDER BY m_date DESC LIMIT %d";
	err	= test_connection->queryf(&res, true, query, uid, year_before, bean_len);
	DEBUG_LOG("sql execute[select itemid, m_type, m_date, ch_name from y_user_behavior where uid=%u and m_date > %d ORDER BY m_date DESC LIMIT %d]", uid, year_before, bean_len);

	if (err < success)
	{
		gettimeofday(&e,NULL);
        FATAL_LOG("[ddbs_fatal], cost[%d], msg[db_get_y_user_behavior], uid[%u], [sql error. myclient err[%d]]", TIMEMSECDIFF(s, e), uid, err);
		result = -1;
		reconnect = true;
	}
	else
	{
		unsigned int rows_count = res.getRowsCount();

		if (rows_count > 0)
		{
			const char *itemid = NULL;
			const char *t_date = NULL;
			const char *ch_name = NULL;
			const char *type = NULL;
			for (i = 0; (unsigned int) i < rows_count && i < bean_len; i++)
			{
				itemid = res[i][0];
				type = res[i][1];
				t_date = res[i][2];
				ch_name = res[i][3];
				p_benas[i].itemid = (unsigned int) atoi(itemid);
				p_benas[i].type = atoi(type);
				strcpy(p_benas[i].ch_name, ch_name);
				p_benas[i].date = atoi(t_date);
			}
			rows_count = i;
		}
		else
		{
			rows_count = 0;
		}
		result = (int) rows_count;
	}

	res.free();
	int ret = p_global.dbpool->putBackConnection(test_connection, reconnect);
	if (ret != 0)
	{
		gettimeofday(&e,NULL);
        WARNING_LOG("third[ddbs_third_fail], cost[%d], [putback connection ret[%d]]", TIMEMSECDIFF(s, e), ret);
		return -1;
	}
	DEBUG_LOG("put back connection ok!\n");
    //ddbs正常处理请求
    if(result >= 0){
        gettimeofday(&e,NULL);
        NOTICE_LOG("third[ddbs_third], cost[%d]", TIMEMSECDIFF(s, e));
    }
	return result;
}


int db_get_co_y_user_behavior(unsigned int baiduid, Action_bean *p_benas, int bean_len)
{
	struct timeval s;
    struct timeval e;
    gettimeofday(&s,NULL);
    MyclientRes res;
	int err = 0;
	int result = 0;
	bool reconnect = false;
	int i = 0;

	MysqlConnection *test_connection = p_global.dbpool->fetchConnection(
			MYCLIENT_AVERAGE_HOST_TYPE, &err, 0);
	if (test_connection == NULL)
	{
		gettimeofday(&e,NULL);
        FATAL_LOG("[ddbs_fatal], cost[%d], [error in fetch, err[%d]]", TIMEMSECDIFF(s, e), err);
		return -1;
	}
	test_connection->setFailHandler(fail_handler);

	DEBUG_LOG("get connection ok!");


	time_t year_before = time (NULL);
	year_before -= 86400 * 360;
	char query[] =
		"select itemid, m_type, m_date, ch_name from co_y_user_behavior where baiduid=%u and m_date > %d ORDER BY m_date DESC LIMIT %d";
	err	= test_connection->queryf(&res, true, query, baiduid, year_before, bean_len);
	DEBUG_LOG("sql execute[select itemid, m_type, m_date, ch_name from co_y_user_behavior where baiduid=%u and m_date > %d ORDER BY m_date DESC LIMIT %d]", baiduid, year_before, bean_len);

	if (err < success)
	{
		gettimeofday(&e,NULL);
        FATAL_LOG("[ddbs_fatal], cost[%d], msg[db_get_co_y_user_behavior], baiduid[%u], [sql error. myclient err[%d]]", TIMEMSECDIFF(s, e), baiduid, err);
		result = -1;
		reconnect = true;
	}
	else
	{
		unsigned int rows_count = res.getRowsCount();

		if (rows_count > 0)
		{
			const char *itemid = NULL;
			const char *t_date = NULL;
			const char *ch_name = NULL;
			const char *type = NULL;
			for (i = 0; (unsigned int) i < rows_count && i < bean_len; i++)
			{
				itemid = res[i][0];
				type = res[i][1];
				t_date = res[i][2];
				ch_name = res[i][3];
				p_benas[i].itemid = (unsigned int) atoi(itemid);
				p_benas[i].type = atoi(type);
				strcpy(p_benas[i].ch_name, ch_name);
				p_benas[i].date = atoi(t_date);
			}
			rows_count = i;
		}
		else
		{
			rows_count = 0;
		}
		result = (int) rows_count;
	}

	res.free();
	int ret = p_global.dbpool->putBackConnection(test_connection, reconnect);
	if (ret != 0)
	{
		gettimeofday(&e,NULL);
        WARNING_LOG("third[ddbs_third_fail], cost[%d], [putback connection ret[%d]]", TIMEMSECDIFF(s, e), ret);
		return -1;
	}
	DEBUG_LOG("put back connection ok!\n");
    //ddbs正常处理请求
    if(result >= 0){
        gettimeofday(&e,NULL);
        NOTICE_LOG("third[ddbs_third], cost[%d]", TIMEMSECDIFF(s, e));
    }
	return result;
}

/**
 * 查询用户收听总数
 * uid 用户id(用户名的签名)
 *
 * return >=0 成功并返回获取数据的长度 -1失败
 *
 */
int db_get_listen_history_num(unsigned int uid, int src)
{
	struct timeval s;
    struct timeval e;
    gettimeofday(&s,NULL);
    MyclientRes res;
	int err = 0;
	int result = 0;
	bool reconnect = false;
	char src_cond[SOURCE_SQL_LEN] = "";
	if(src == RLS_SOURCE_MP3 || src == RLS_SOURCE_TING)
	{
		//snprintf(src_cond, sizeof(src_cond), "AND m_source=%d", src);
	}
	MysqlConnection *test_connection = p_global.dbpool->fetchConnection(
			MYCLIENT_AVERAGE_HOST_TYPE, &err, 0);
	if (test_connection == NULL)
	{
		gettimeofday(&e,NULL);
        FATAL_LOG("[ddbs_fatal], cost[%d], [error in fetch, err[%d]]", TIMEMSECDIFF(s, e), err);
		return -1;
	}
	test_connection->setFailHandler(fail_handler);

	DEBUG_LOG("get connection ok!");
	char query[] =
		"select count(*) from listen_history where uid=%u %s";
	err	= test_connection->queryf(&res, true, query, uid, src_cond);
	if (err < success)
	{
		gettimeofday(&e,NULL);
        FATAL_LOG("[ddbs_fatal], cost[%d], [sql error. myclient err[%d]]", TIMEMSECDIFF(s, e), err);
		result = -1;
		reconnect = true;
	}
	else
	{
		unsigned int rows_count = res.getRowsCount();

		if (rows_count > 0)
		{
			result = atoi(res[0][0]);
		}
		else
		{
			result = 0;
		}
	}

	res.free();
	int ret = p_global.dbpool->putBackConnection(test_connection, reconnect);
	if (ret != 0)
	{
		gettimeofday(&e,NULL);
        WARNING_LOG("third[ddbs_third_fail], cost[%d], [putback connection ret[%d]]", TIMEMSECDIFF(s, e), ret);
		return -1;
	}
	DEBUG_LOG("put back connection ok!\n");
    //ddbs正常处理请求
    if(result >= 0){
        gettimeofday(&e,NULL);
        NOTICE_LOG("third[ddbs_third], cost[%d]", TIMEMSECDIFF(s, e));
    }
	return result;

}

/**
 *获取试听历史分页数据
 */
int db_get_history_page(unsigned int uid, Item_bean *p_benas,
		int start_no, int page_len, int src){
	struct timeval s;
    struct timeval e;
    gettimeofday(&s,NULL);
    MyclientRes res;
	MyclientRes pref_res;
	int err = 0;
	int result = 0;
	bool reconnect = false;
	int i = 0;
	char src_cond[SOURCE_SQL_LEN] = "";
	if(src == RLS_SOURCE_MP3 || src == RLS_SOURCE_TING)
	{
		//snprintf(src_cond, sizeof(src_cond), "AND m_source=%d", src);
	}
	MysqlConnection *test_connection = p_global.dbpool->fetchConnection(
			MYCLIENT_AVERAGE_HOST_TYPE, &err, 0);
	if (test_connection == NULL)
	{
		gettimeofday(&e,NULL);
        FATAL_LOG("[ddbs_fatal], cost[%d], [error in fetch, err[%d]]", TIMEMSECDIFF(s, e), err);
		return -1;
	}
	test_connection->setFailHandler(fail_handler);
	int res_len = start_no+page_len;
	DEBUG_LOG("get connection ok!");
	char query[] =
		"select soid, m_date as t_date from listen_history where uid=%u %s ORDER BY t_date DESC LIMIT %d";
	err = test_connection->queryf(&res, true, query, uid, src_cond, res_len);
	if (err < success)
	{
		gettimeofday(&e,NULL);
        FATAL_LOG("[ddbs_fatal], cost[%d], [sql error. myclient err[%d]]", TIMEMSECDIFF(s, e), err);
		result = -1;
		reconnect = true;
	}
	else
	{
		unsigned int rows_count = res.getRowsCount();
		int j = 0;
		if (rows_count > 0)
		{
			const char *soid = NULL;
			const char *t_date = NULL;
			j = 0;
			for (i = start_no; (unsigned int) i < rows_count && i < res_len; i++)
			{
				soid = res[i][0];
				t_date = res[i][1];
				p_benas[j].itemid = (unsigned int) atoi(soid);
				p_benas[j].date = FormatTime2(t_date);
				p_benas[j].pref_type = -1;
				j++;
			}
			rows_count = i;
		}
		else
		{
			rows_count = 0;
		}
		result = j;
	}

	res.free();
	int ret = p_global.dbpool->putBackConnection(test_connection, reconnect);
	if (ret != 0)
	{
		gettimeofday(&e,NULL);
        WARNING_LOG("third[ddbs_third_fail], cost[%d], [putback connection ret[%d]]", TIMEMSECDIFF(s, e), ret);
		return -1;
	}
	DEBUG_LOG("put back connection ok!\n");
    //ddbs正常处理请求
    if(result >= 0){
        gettimeofday(&e,NULL);
        NOTICE_LOG("third[ddbs_third], cost[%d]", TIMEMSECDIFF(s, e));
    }
	return result;
}

/**
 * 插入用户收听数据
 * uid 用户id(用户名的签名)
 * soid 歌曲id
 *
 * return 0 成功  -1失败
 *
 */
int db_add_listen_history(unsigned int uid, uint soid, const char* ch_name)
{
	struct timeval s;
    struct timeval e;
    gettimeofday(&s,NULL);
    MyclientRes res;
	int err = 0;
	int result = 0;
	bool reconnect = false;

	MysqlConnection *test_connection = p_global.dbpool->fetchConnection(
			MYCLIENT_AVERAGE_HOST_TYPE, &err, 0);
	if (test_connection == NULL)
	{
		gettimeofday(&e,NULL);
        FATAL_LOG("[ddbs_fatal], cost[%d], [error in fetch, err[%d]]", TIMEMSECDIFF(s, e), err);
		return -1;
	}
	test_connection->setFailHandler(fail_handler_warning);

	DEBUG_LOG("get connection ok!");

	time_t now = time((time_t*) NULL);
	char timeStr[MAX_DIR_LEN];
	FormatTime(now,timeStr,MAX_DIR_LEN);

	char query[] =
		"insert into listen_history(uid,soid,m_date, ch_name) values(%u,%u,'%s','%s')";
	int i = 0;
	for(i = 0; i < TRY_TIME; i++){
		DEBUG_LOG("insert into listen_history(uid,soid,m_date, ch_name) values(%u,%u,'%s','%s'), times[%d]", \
			uid, soid, timeStr, ch_name, i);
		err = test_connection->queryf(&res, true, query, uid, soid, timeStr, ch_name);
		if (err < success)
		{
			gettimeofday(&e,NULL);
	        FormatRandomTime(now, timeStr, MAX_DIR_LEN);
		}
		else{
			break;
		}
	}
	if (i == TRY_TIME){
		FATAL_LOG("[ddbs_fatal], cost[%d], [sql error. myclient err[%d]]", TIMEMSECDIFF(s, e), err);
		result = -1;
		reconnect = true;
	}

	res.free();
	int ret = p_global.dbpool->putBackConnection(test_connection, reconnect);
	if (ret != 0)
	{
		gettimeofday(&e,NULL);
        WARNING_LOG("third[ddbs_third_fail], cost[%d], [putback connection ret[%d]]", TIMEMSECDIFF(s, e), ret);
		return -1;
	}
	DEBUG_LOG("put back connection ok!\n");
    //ddbs正常处理请求
    if(result >= 0){
        gettimeofday(&e,NULL);
        NOTICE_LOG("third[ddbs_third], cost[%d]", TIMEMSECDIFF(s, e));
    }
	return result;

}

/**
 * 插入用户行为数据
 * uid 用户id(用户名的签名)
 * soid 歌曲id
 * type行为类型
 *
 * return 0 成功  -1失败
 *
 */
int db_add_user_real_behavior(unsigned int uid, uint soid,
		enum DB_USER_BEHAVIOR_TYPE type, const char* ch_name)
{
	struct timeval s;
    struct timeval e;
    gettimeofday(&s,NULL);
    MyclientRes res;
	int err = 0;
	int result = 0;
	bool reconnect = false;

	MysqlConnection *test_connection = p_global.dbpool->fetchConnection(
			MYCLIENT_AVERAGE_HOST_TYPE, &err, 0);
	if (test_connection == NULL)
	{
		gettimeofday(&e,NULL);
        FATAL_LOG("[ddbs_fatal], cost[%d], [error in fetch, err[%d]]", TIMEMSECDIFF(s, e), err);
		return -1;
	}
	test_connection->setFailHandler(fail_handler_warning);

	DEBUG_LOG("get connection ok!");

	time_t now = time((time_t*) NULL);
	char timeStr[MAX_DIR_LEN];
	FormatTime(now,timeStr,MAX_DIR_LEN);

	char query[] =
		"insert into user_real_behavior(uid,soid,m_type, m_date, ch_name) values(%u,%u,%d,'%s', '%s')";
	int i = 0;
	for(i = 0; i < TRY_TIME; i++){
		DEBUG_LOG("insert into user_real_behavior(uid,soid,m_type, m_date, ch_name) values(%u,%u,%d,'%s','%s'), times[%d]", \
			uid, soid, type, timeStr, ch_name, i);
		err = test_connection->queryf(&res, true, query, uid, soid, type, timeStr, ch_name);
		if (err < success)
		{
			gettimeofday(&e,NULL);
	        FormatRandomTime(now,timeStr,MAX_DIR_LEN);
		}
		else{
			break;
		}
	}
	if (i == TRY_TIME){
		FATAL_LOG("[ddbs_fatal], cost[%d], [sql error. myclient err[%d]]", TIMEMSECDIFF(s, e), err);
		result = -1;
		reconnect = true;
	}

	res.free();
	int ret = p_global.dbpool->putBackConnection(test_connection, reconnect);
	if (ret != 0)
	{
		gettimeofday(&e,NULL);
        WARNING_LOG("third[ddbs_third_fail], cost[%d], [putback connection ret[%d]]", TIMEMSECDIFF(s, e), ret);
		return -1;
	}
	DEBUG_LOG("put back connection ok!\n");
    //ddbs正常处理请求
    if(result >= 0){
        gettimeofday(&e,NULL);
        NOTICE_LOG("third[ddbs_third], cost[%d]", TIMEMSECDIFF(s, e));
    }
	return result;
}

int db_add_co_y_user_behavior(unsigned int baiduid, const char* baiduid_str, uint soid,
		int type, const char* ch_name)
{
	struct timeval s;
    struct timeval e;
    gettimeofday(&s,NULL);
    MyclientRes res;
	int err = 0;
	int result = 0;
	bool reconnect = false;

	MysqlConnection *test_connection = p_global.dbpool->fetchConnection(
			MYCLIENT_AVERAGE_HOST_TYPE, &err, 0);
	if (test_connection == NULL)
	{
		gettimeofday(&e,NULL);
        FATAL_LOG("[ddbs_fatal], cost[%d], [error in fetch, err[%d]]", TIMEMSECDIFF(s, e), err);
		return -1;
	}
	test_connection->setFailHandler(fail_handler_warning);

	DEBUG_LOG("get connection ok!");

	time_t now = time((time_t*) NULL);

	char query[] =
		"insert into co_y_user_behavior(baiduid, itemid, m_type, m_date, ch_name, baiduid_str) values(%u, %u, %d, %d, '%s', '%s')";
	int i = 0;
	for(i = 0; i < TRY_TIME; i++){
		DEBUG_LOG("insert into co_y_user_behavior(baiduid,itemid,m_type, m_date, ch_name, baiduid_str) values(%u,%u,%d,%d,'%s', '%s'), times[%d]", \
			baiduid, soid, type, now, ch_name, i);
		err = test_connection->queryf(&res, true, query, baiduid, soid, type, now, ch_name, baiduid_str);
		if (err < success)
		{
			gettimeofday(&e,NULL);
	        now =  (now/SECONDS_OF_DAY) * SECONDS_OF_DAY + rand()%SECONDS_OF_DAY;
		}
		else{
			break;
		}
	}
	if (i == TRY_TIME){
		FATAL_LOG("[ddbs_fatal], cost[%d], [sql error. myclient err[%d]]", TIMEMSECDIFF(s, e), err);
		result = -1;
		reconnect = true;
	}

	res.free();
	int ret = p_global.dbpool->putBackConnection(test_connection, reconnect);
	if (ret != 0)
	{
		gettimeofday(&e,NULL);
        WARNING_LOG("third[ddbs_third_fail], cost[%d], [putback connection ret[%d]]", TIMEMSECDIFF(s, e), ret);
		return -1;
	}
	DEBUG_LOG("put back connection ok!\n");
    //ddbs正常处理请求
    if(result >= 0){
        gettimeofday(&e,NULL);
        NOTICE_LOG("third[ddbs_third], cost[%d]", TIMEMSECDIFF(s, e));
    }
	return result;
}


int db_add_y_user_behavior(unsigned int uid, uint soid,
		int type, const char* ch_name)
{
	struct timeval s;
    struct timeval e;
    gettimeofday(&s,NULL);
    MyclientRes res;
	int err = 0;
	int result = 0;
	bool reconnect = false;

	MysqlConnection *test_connection = p_global.dbpool->fetchConnection(
			MYCLIENT_AVERAGE_HOST_TYPE, &err, 0);
	if (test_connection == NULL)
	{
		gettimeofday(&e,NULL);
        FATAL_LOG("[ddbs_fatal], cost[%d], [error in fetch, err[%d]]", TIMEMSECDIFF(s, e), err);
		return -1;
	}
	test_connection->setFailHandler(fail_handler_warning);

	DEBUG_LOG("get connection ok!");

	time_t now = time((time_t*) NULL);

	char query[] =
		"insert into y_user_behavior(uid, itemid, m_type, m_date, ch_name) values(%u,%u,%d,%d, '%s')";
	int i = 0;
	for(i = 0; i < TRY_TIME; i++){
		DEBUG_LOG("insert into y_user_behavior(uid,itemid,m_type, m_date, ch_name) values(%u,%u,%d,%d,'%s'), times[%d]", \
			uid, soid, type, now, ch_name, i);
		err = test_connection->queryf(&res, true, query, uid, soid, type, now, ch_name);
		if (err < success)
		{
			gettimeofday(&e,NULL);
	        now =  (now/SECONDS_OF_DAY) * SECONDS_OF_DAY + rand()%SECONDS_OF_DAY;
		}
		else{
			break;
		}
	}
	if (i == TRY_TIME){
		FATAL_LOG("[ddbs_fatal], cost[%d], [sql error. myclient err[%d]]", TIMEMSECDIFF(s, e), err);
		result = -1;
		reconnect = true;
	}

	res.free();
	int ret = p_global.dbpool->putBackConnection(test_connection, reconnect);
	if (ret != 0)
	{
		gettimeofday(&e,NULL);
        WARNING_LOG("third[ddbs_third_fail], cost[%d], [putback connection ret[%d]]", TIMEMSECDIFF(s, e), ret);
		return -1;
	}
	DEBUG_LOG("put back connection ok!\n");
    //ddbs正常处理请求
    if(result >= 0){
        gettimeofday(&e,NULL);
        NOTICE_LOG("third[ddbs_third], cost[%d]", TIMEMSECDIFF(s, e));
    }
	return result;
}

int db_get_co_listen_history(uint baiduid, Item_bean* p, int buf_size){
	struct timeval s;
    struct timeval e;
    gettimeofday(&s,NULL);
    MyclientRes res;
	int err = 0;
	int result = 0;
	bool reconnect = false;
	int i = 0;

	MysqlConnection *test_connection = p_global.dbpool->fetchConnection(
			MYCLIENT_AVERAGE_HOST_TYPE, &err, 0);
	if (test_connection == NULL){
		gettimeofday(&e,NULL);
        FATAL_LOG("[ddbs_fatal], cost[%d], [error in fetch, err[%d]]", TIMEMSECDIFF(s, e), err);
		return -1;
	}
	test_connection->setFailHandler(fail_handler);
	DEBUG_LOG("get connection ok!");

	char timeStr[MAX_DIR_LEN];
	YearBefore(timeStr, MAX_DIR_LEN);
	char query[] =
		"SELECT soid, m_date, ch_name FROM co_listen_history WHERE baiduid=%u and m_date > '%s' ORDER BY m_date DESC LIMIT %d";
	err = test_connection->queryf(&res, true, query, baiduid, timeStr, buf_size);
	DEBUG_LOG("sql execute[SELECT soid, m_date, ch_name FROM co_listen_history WHERE baiduid=%u and m_date > '%s' ORDER BY m_date DESC LIMIT %d", \
		baiduid, timeStr, buf_size);

	if (err < success){
		gettimeofday(&e,NULL);
        FATAL_LOG("[ddbs_fatal], cost[%d], msg[db_get_co_listen_history], baiduid[%u], [sql error. myclient err[%d]]", TIMEMSECDIFF(s, e), baiduid, err);
		result = -1;
		reconnect = true;
	}
	else{
		unsigned int rows_count = res.getRowsCount();
		if (rows_count > 0){
			const char* itemid = NULL;
			const char* m_date = NULL;
			const char* ch_name = NULL;
			for (i = 0; (unsigned int) i < rows_count && i < buf_size; i++){
				itemid = res[i][0];
				m_date = res[i][1];
				ch_name = res[i][2];
				p[i].itemid = (unsigned int) atoi(itemid);
				p[i].date = FormatTime2(m_date);
				strcpy(p[i].ch_name, ch_name);
			}
			rows_count = i;
		}
		else{
			rows_count = 0;
		}
		result = (int) rows_count;
	}

	res.free();
	int ret = p_global.dbpool->putBackConnection(test_connection, reconnect);
	if (ret != 0){
		gettimeofday(&e,NULL);
        WARNING_LOG("third[ddbs_third_fail], cost[%d], [putback connection ret[%d]]", TIMEMSECDIFF(s, e), ret);
		return -1;
	}
	DEBUG_LOG("put back connection ok!\n");
	//ddbs正常处理请求
    if(result >= 0){
        gettimeofday(&e,NULL);
        NOTICE_LOG("third[ddbs_third], msg[db_get_co_listen_history], baiduid[%u], cost[%d]", baiduid, TIMEMSECDIFF(s, e));
    }
    return result;
}


/**
 *@brief:获取 cookie喜好数据
 *@param[in]:baiduid, 百度 id
 *@param[out]:p ,行为数据
 *@param[in]:type,喜好类型
 *@param[in]:buf_size, 最大个数
 * retrun >=0 成功,返回数据长度 -1失败
 */
int db_get_co_pref_data(uint baiduid, enum DB_PREF_TYPE type, Item_bean* p, int buf_size){
	struct timeval s;
    struct timeval e;
    gettimeofday(&s,NULL);
    MyclientRes res;
	int err = 0;
	int result = 0;
	bool reconnect = false;
	int i = 0;

	MysqlConnection *test_connection = p_global.dbpool->fetchConnection(
			MYCLIENT_AVERAGE_HOST_TYPE, &err, 0);
	if (test_connection == NULL){
		gettimeofday(&e,NULL);
        FATAL_LOG("[ddbs_fatal], cost[%d], [error in fetch, err[%d]]", TIMEMSECDIFF(s, e), err);
		return -1;
	}
	test_connection->setFailHandler(fail_handler);
	DEBUG_LOG("get connection ok!");


	char timeStr[MAX_DIR_LEN];
	YearBefore(timeStr, MAX_DIR_LEN);
	char query[] =
		"SELECT itemid, m_type, m_date FROM co_item_pref WHERE baiduid=%u AND m_type=%d AND m_del=%d AND m_date > '%s' ORDER BY m_date DESC LIMIT %d";
	err = test_connection->queryf(&res, true, query, baiduid, type, DB_VALID, timeStr, buf_size);
	DEBUG_LOG("sql execute[ SELECT itemid, m_type, m_date FROM co_item_pref WHERE baiduid=%u AND m_type=%d AND m_del=%d  and m_date > '%s' ORDER BY m_date DESC LIMIT %d]", baiduid, type, DB_VALID, timeStr, buf_size);

	if (err < success){
		gettimeofday(&e,NULL);
        FATAL_LOG("[ddbs_fatal], cost[%d], msg[db_get_co_prefdata], baiduid[%u], [sql error. myclient err[%d]]", TIMEMSECDIFF(s, e), baiduid, err);
		result = -1;
		reconnect = true;
	}
	else{
		unsigned int rows_count = res.getRowsCount();
		if (rows_count > 0){
			const char* itemid = NULL;
			const char* m_date = NULL;
			const char* pref_type = NULL;
			for (i = 0; (unsigned int) i < rows_count && i < buf_size; i++){
				itemid = res[i][0];
				pref_type = res[i][1];
				m_date = res[i][2];
				p[i].itemid = (unsigned int) atoi(itemid);
				p[i].pref_type = (int) atoi(pref_type);
				p[i].date = FormatTime2(m_date);
			}
			rows_count = i;
		}
		else{
			rows_count = 0;
		}
		result = (int) rows_count;
	}

	res.free();
	int ret = p_global.dbpool->putBackConnection(test_connection, reconnect);
	if (ret != 0){
		gettimeofday(&e,NULL);
        WARNING_LOG("third[ddbs_third_fail], cost[%d], [putback connection ret[%d]]", TIMEMSECDIFF(s, e), ret);
		return -1;
	}
	DEBUG_LOG("put back connection ok!\n");
	//ddbs正常处理请求
    if(result >= 0){
        gettimeofday(&e,NULL);
        NOTICE_LOG("third[ddbs_third], cost[%d]", TIMEMSECDIFF(s, e));
    }
    return result;
}


int db_add_co_listen_history(uint baiduid, const char* baiduid_str, uint itemid, const char* ch_name){
	struct timeval s;
    struct timeval e;
    gettimeofday(&s,NULL);
    if(NULL == ch_name){
        gettimeofday(&e,NULL);
        WARNING_LOG("[ddbs_fail], cost[%d], [wrong param]", TIMEMSECDIFF(s, e));
		return -1;
	}
	MyclientRes res;
	int err = 0;
	int result = 0;
	bool reconnect = false;

	MysqlConnection *test_connection = p_global.dbpool->fetchConnection(
			MYCLIENT_AVERAGE_HOST_TYPE, &err, 0);
	if (test_connection == NULL)
	{
		gettimeofday(&e,NULL);
        FATAL_LOG("[ddbs_fatal], cost[%d], [error in fetch, err[%d]]", TIMEMSECDIFF(s, e), err);
		return -1;
	}
	test_connection->setFailHandler(fail_handler_warning);
	DEBUG_LOG("get connection ok!");

	time_t now = time((time_t*) NULL);
	char timeStr[MAX_DIR_LEN];
	FormatTime(now,timeStr,MAX_DIR_LEN);
	char query[] =
		"INSERT INTO co_listen_history SET baiduid=%u, baiduid_str='%s', soid=%u, m_date='%s', ch_name='%s'";
	int i = 0;
	for(i = 0; i < TRY_TIME; i++){
		DEBUG_LOG("INSERT INTO co_listen_history SET baiduid=%u, baiduid_str='%s', soid=%u, m_date='%s', ch_name='%s', times[%d]", \
			baiduid, baiduid_str, itemid, timeStr, ch_name, i);
		err = test_connection->queryf(&res, true, query, baiduid, baiduid_str, itemid, timeStr, ch_name);
		if (err < success)
		{
			gettimeofday(&e,NULL);
	        FormatRandomTime(now, timeStr, MAX_DIR_LEN);
		}
		else{
			break;
		}
	}
	if (i == TRY_TIME){
		FATAL_LOG("[ddbs_fatal], cost[%d], [sql error. myclient err[%d]]", TIMEMSECDIFF(s, e), err);
		result = -1;
		reconnect = true;
	}

	res.free();
	int ret = p_global.dbpool->putBackConnection(test_connection, reconnect);
	if (ret != 0)
	{
		gettimeofday(&e,NULL);
        WARNING_LOG("third[ddbs_third_fail], cost[%d], [putback connection ret[%d]]", TIMEMSECDIFF(s, e), ret);
		return -1;
	}
	DEBUG_LOG("put back connection ok!\n");
    //ddbs正常处理请求
    if(result >= 0){
        gettimeofday(&e,NULL);
        NOTICE_LOG("third[ddbs_third], cost[%d]", TIMEMSECDIFF(s, e));
    }
	return result;
}

int db_add_co_user_real_behavior(uint baiduid, const char* baiduid_str,  uint itemid,
		enum DB_USER_BEHAVIOR_TYPE type, const char* ch_name){
	struct timeval s;
    struct timeval e;
    gettimeofday(&s,NULL);
    if(NULL == ch_name){
		gettimeofday(&e,NULL);
        WARNING_LOG("[ddbs_fail], cost[%d], [wrong param]", TIMEMSECDIFF(s, e));
		return -1;
	}
	MyclientRes res;
	int err = 0;
	int result = 0;
	bool reconnect = false;

	MysqlConnection *test_connection = p_global.dbpool->fetchConnection(
			MYCLIENT_AVERAGE_HOST_TYPE, &err, 0);
	if (test_connection == NULL){
		gettimeofday(&e,NULL);
        FATAL_LOG("[ddbs_fatal], cost[%d], [error in fetch, err[%d]]", TIMEMSECDIFF(s, e), err);
		return -1;
	}
	test_connection->setFailHandler(fail_handler_warning);
	DEBUG_LOG("get connection ok!");

	time_t now = time((time_t*) NULL);
	char timeStr[MAX_DIR_LEN];
	FormatTime(now,timeStr,MAX_DIR_LEN);
	char query[] =
		"INSERT INTO co_user_real_behavior SET baiduid=%u, baiduid_str = '%s', itemid=%u, m_date='%s', ch_name='%s', m_type=%d";

	int i = 0;
	for(i = 0; i < TRY_TIME; i++){
		DEBUG_LOG("INSERT INTO co_user_real_behavior SET baiduid=%u, baiduid_str = '%s', itemid=%u, m_date='%s', ch_name='%s', m_type=%d, times[%d]", \
			baiduid, baiduid_str, itemid, timeStr, ch_name, i);
		err = test_connection->queryf(&res, true, query, baiduid, baiduid_str, itemid, timeStr, ch_name, type);
		if (err < success)
		{
			gettimeofday(&e,NULL);
	        FormatRandomTime(now, timeStr, MAX_DIR_LEN);
		}
		else{
			break;
		}
	}
	if (i == TRY_TIME){
		FATAL_LOG("[ddbs_fatal], cost[%d], [sql error. myclient err[%d]]", TIMEMSECDIFF(s, e), err);
		result = -1;
		reconnect = true;
	}

	res.free();
	int ret = p_global.dbpool->putBackConnection(test_connection, reconnect);
	if (ret != 0){
		gettimeofday(&e,NULL);
        WARNING_LOG("third[ddbs_third_fail], cost[%d], [putback connection ret[%d]]", TIMEMSECDIFF(s, e), ret);
		return -1;
	}
	DEBUG_LOG("put back connection ok!\n");
    //ddbs正常处理请求
    if(result >= 0){
        gettimeofday(&e,NULL);
        NOTICE_LOG("third[ddbs_third], cost[%d]", TIMEMSECDIFF(s, e));
    }
	return result;
}

/**
 *@brief:判断是否有试听历史
 *@param[in]:uid,用户id
 *@param[out]:has_history,true有历史 false没有试听历史
 */
int db_has_listen_history(uint uid, bool &has_history){
	struct timeval s;
    struct timeval e;
    gettimeofday(&s,NULL);
    MyclientRes res;
	int err = 0;
	int result = 0;
	bool reconnect = false;
	has_history = true;
	MysqlConnection *test_connection = p_global.dbpool->fetchConnection(
			MYCLIENT_AVERAGE_HOST_TYPE, &err, 0);
	if (test_connection == NULL){
		gettimeofday(&e,NULL);
        FATAL_LOG("[ddbs_fatal], cost[%d], [error in fetch, err[%d]]", TIMEMSECDIFF(s, e), err);
		return -1;
	}
	test_connection->setFailHandler(fail_handler);
	DEBUG_LOG("get connection ok!");

	time_t now = time((time_t*) NULL);
	char query[] =
		"SELECT uid FROM listen_history WHERE uid=%u LIMIT 1";
	err = test_connection->queryf(&res, true, query, uid);
	if (err < success){
		gettimeofday(&e,NULL);
        FATAL_LOG("[ddbs_fatal], cost[%d], [sql error. myclient err[%d]]", TIMEMSECDIFF(s, e), err);
		result = -1;
		reconnect = true;
	}
	else{
		unsigned int rows_count = res.getRowsCount();
		if(rows_count == 0){
			has_history = false;
		}
	}
	res.free();
	int ret = p_global.dbpool->putBackConnection(test_connection, reconnect);
	if (ret != 0){
		gettimeofday(&e,NULL);
        WARNING_LOG("third[ddbs_third_fail], cost[%d], [putback connection ret[%d]]", TIMEMSECDIFF(s, e), ret);
		return -1;
	}
	DEBUG_LOG("put back connection ok!\n");
    //ddbs正常处理请求
    if(result >= 0){
        gettimeofday(&e,NULL);
        NOTICE_LOG("third[ddbs_third], cost[%d]", TIMEMSECDIFF(s, e));
    }
	return result;
}



int db_has_co_listen_history(uint baiduid, bool &has_history){
	struct timeval s;
    struct timeval e;
    gettimeofday(&s,NULL);
    MyclientRes res;
	int err = 0;
	int result = 0;
	bool reconnect = false;
	has_history = true;
	MysqlConnection *test_connection = p_global.dbpool->fetchConnection(
			MYCLIENT_AVERAGE_HOST_TYPE, &err, 0);
	if (test_connection == NULL){
		gettimeofday(&e,NULL);
        FATAL_LOG("[ddbs_fatal], cost[%d], [error in fetch, err[%d]]", TIMEMSECDIFF(s, e), err);
		return -1;
	}
	test_connection->setFailHandler(fail_handler);
	DEBUG_LOG("get connection ok!");
	time_t now = time((time_t*) NULL);
	char query[] =
		"SELECT baiduid FROM co_listen_history WHERE baiduid=%u LIMIT 1";
	err = test_connection->queryf(&res, true, query, baiduid);
	if (err < success){
		gettimeofday(&e,NULL);
        FATAL_LOG("[ddbs_fatal], cost[%d], [sql error. myclient err[%d]]", TIMEMSECDIFF(s, e), err);
		result = -1;
		reconnect = true;
	}
	else{
		unsigned int rows_count = res.getRowsCount();
		if(rows_count == 0){
			has_history = false;
		}
	}
	res.free();
	int ret = p_global.dbpool->putBackConnection(test_connection, reconnect);
	if (ret != 0){
		gettimeofday(&e,NULL);
        WARNING_LOG("third[ddbs_third_fail], cost[%d], [putback connection ret[%d]]", TIMEMSECDIFF(s, e), ret);
		return -1;
	}
	DEBUG_LOG("put back connection ok!\n");
    //ddbs正常处理请求
    if(result >= 0){
        gettimeofday(&e,NULL);
        NOTICE_LOG("third[ddbs_third], cost[%d]", TIMEMSECDIFF(s, e));
    }
	return result;
}

int db_update_user_behavior_cnt(uint uid, uint soid){
    struct timeval s;
    struct timeval e;
    gettimeofday(&s,NULL);

	MyclientRes res;
	int err = 0;
	int result = 0;
	bool reconnect = false;

	MysqlConnection *test_connection = p_global.dbpool->fetchConnection(
			MYCLIENT_AVERAGE_HOST_TYPE, &err, 0);
	if (test_connection == NULL)
	{
		gettimeofday(&e,NULL);
        FATAL_LOG("[ddbs_fatal], cost[%d], [error in fetch, err[%d]]", TIMEMSECDIFF(s, e), err);
		return -1;
	}
	test_connection->setFailHandler(fail_handler_warning);
	DEBUG_LOG("get connection ok!");

	time_t now = time((time_t*) NULL);
	char query[] =
        "insert into user_behavior_cnt set uid = %u, soid = %d, cnt = 1, m_date = %d on duplicate key update cnt = cnt + 1, m_date = %d;";
    DEBUG_LOG("insert into user_behavior_cnt set uid = %u, soid = %d, cnt = 1, m_date = %d on duplicate key update cnt = cnt + 1, m_date = %d;", uid, soid, now, now);
    err = test_connection->queryf(&res, true, query, uid, soid, now, now);
    if (err < success){
		gettimeofday(&e,NULL);
        FATAL_LOG("[ddbs_fatal], cost[%d], [sql error. myclient err[%d]]", TIMEMSECDIFF(s, e), err);
		result = -1;
		reconnect = true;
	}

	res.free();
	int ret = p_global.dbpool->putBackConnection(test_connection, reconnect);
	if (ret != 0){
		gettimeofday(&e,NULL);
        WARNING_LOG("third[ddbs_third_fail], cost[%d], [putback connection ret[%d]]", TIMEMSECDIFF(s, e), ret);
		return -1;
	}
	DEBUG_LOG("put back connection ok!\n");
    //ddbs正常处理请求
    if(result >= 0){
        gettimeofday(&e,NULL);
        NOTICE_LOG("third[ddbs_third], cost[%d]", TIMEMSECDIFF(s, e));
    }
    return result;
}

int db_update_co_user_behavior_cnt(uint baiduid, uint soid, const char* baidu_str){
    struct timeval s;
    struct timeval e;
    gettimeofday(&s,NULL);

	MyclientRes res;
	int err = 0;
	int result = 0;
	bool reconnect = false;

	MysqlConnection *test_connection = p_global.dbpool->fetchConnection(
			MYCLIENT_AVERAGE_HOST_TYPE, &err, 0);
	if (test_connection == NULL)
	{
		gettimeofday(&e,NULL);
        FATAL_LOG("[ddbs_fatal], cost[%d], [error in fetch, err[%d]]", TIMEMSECDIFF(s, e), err);
		return -1;
	}
	test_connection->setFailHandler(fail_handler_warning);
	DEBUG_LOG("get connection ok!");

	time_t now = time((time_t*) NULL);
	char query[] =
        "insert into co_user_behavior_cnt set baiduid = %u, soid = %d, cnt = 1, m_date = %d, baiduid_str = '%s' "
        "on duplicate key update cnt = cnt + 1, m_date = %d, baiduid_str = '%s';";
    DEBUG_LOG("insert into co_user_behavior_cnt set baiduid = %u, soid = %d, cnt = 1, m_date = %d, baiduid_str = '%s' \
            on duplicate key update cnt = cnt + 1, m_date = %d, baiduid_str = '%s';", \
            baiduid, soid, now, baidu_str, now, baidu_str);
    err = test_connection->queryf(&res, true, query, baiduid, soid, now, baidu_str, now, baidu_str);
    if (err < success){
		gettimeofday(&e,NULL);
        FATAL_LOG("[ddbs_fatal], cost[%d], [sql error. myclient err[%d]]", TIMEMSECDIFF(s, e), err);
		result = -1;
		reconnect = true;
	}

	res.free();
	int ret = p_global.dbpool->putBackConnection(test_connection, reconnect);
	if (ret != 0){
		gettimeofday(&e,NULL);
        WARNING_LOG("third[ddbs_third_fail], cost[%d], [putback connection ret[%d]]", TIMEMSECDIFF(s, e), ret);
		return -1;
	}
	DEBUG_LOG("put back connection ok!\n");
    //ddbs正常处理请求
    if(result >= 0){
        gettimeofday(&e,NULL);
        NOTICE_LOG("third[ddbs_third], cost[%d]", TIMEMSECDIFF(s, e));
    }
    return result;
}

int db_update_co_pref(uint baiduid, const char* baiduid_str,  uint itemid,enum DB_PREF_TYPE type,
		enum DB_DEL_TYPE del_flag, const char* ch_name){
    struct timeval s;
    struct timeval e;
    gettimeofday(&s,NULL);
	if(NULL == ch_name){
		gettimeofday(&e,NULL);
        WARNING_LOG("[ddbs_fail], cost[%d], [wrong param]", TIMEMSECDIFF(s, e));
		return -1;
	}
	MyclientRes res;
	int err = 0;
	int result = 0;
	bool reconnect = false;

	MysqlConnection *test_connection = p_global.dbpool->fetchConnection(
			MYCLIENT_AVERAGE_HOST_TYPE, &err, 0);
	if (test_connection == NULL)
	{
		gettimeofday(&e,NULL);
        FATAL_LOG("[ddbs_fatal], cost[%d], [error in fetch, err[%d]]", TIMEMSECDIFF(s, e), err);
		return -1;
	}
	test_connection->setFailHandler(fail_handler_warning);
	DEBUG_LOG("get connection ok!");

	time_t now = time((time_t*) NULL);
	char timeStr[MAX_DIR_LEN];
	FormatTime(now,timeStr,MAX_DIR_LEN);
	char query[] =
		"INSERT INTO co_item_pref SET baiduid=%u, baiduid_str = '%s', itemid=%u, m_date='%s', ch_name='%s', m_type=%d,"
		"m_del=%d on duplicate key update m_date='%s', m_type=%d, m_del=%d, ch_name='%s';";

	int i = 0;
	for(i = 0; i < TRY_TIME; i++){
		DEBUG_LOG("INSERT INTO co_item_pref SET baiduid=%u, baiduid_str = '%s', itemid=%u, m_date='%s', ch_name='%s', m_type=%d,"
			"m_del=%d on duplicate key update m_date='%s', m_type=%d, m_del=%d, ch_name='%s'; times[%d]", \
			baiduid, baiduid_str, itemid, timeStr, ch_name, \
			type,del_flag, timeStr, type, del_flag, ch_name, i);
		err = test_connection->queryf(&res, true, query, baiduid, baiduid_str, itemid, timeStr, ch_name,
			type,del_flag, timeStr, type, del_flag, ch_name);
		if (err < success)
		{
			gettimeofday(&e,NULL);
	        FormatRandomTime(now, timeStr, MAX_DIR_LEN);
		}
		else{
			break;
		}
	}
	if (i == TRY_TIME){
		FATAL_LOG("[ddbs_fatal], cost[%d], [sql error. myclient err[%d]]", TIMEMSECDIFF(s, e), err);
		result = -1;
		reconnect = true;
	}

	res.free();
	int ret = p_global.dbpool->putBackConnection(test_connection, reconnect);
	if (ret != 0)
	{
		gettimeofday(&e,NULL);
        WARNING_LOG("third[ddbs_third_fail], cost[%d], [putback connection ret[%d]]", TIMEMSECDIFF(s, e), ret);
		return -1;
	}
	DEBUG_LOG("put back connection ok!\n");
    //ddbs正常处理请求
    if(result >= 0){
        gettimeofday(&e,NULL);
        NOTICE_LOG("third[ddbs_third], cost[%d]", TIMEMSECDIFF(s, e));
    }
	return result;
}

int db_get_co_user_behavior_cnt(uint baiduid, const char* song_set, std::map<int, user_cnt_t> &user_cnt_map)
{
	struct timeval s;
    struct timeval e;
    gettimeofday(&s,NULL);
    MyclientRes res;
	int err = 0;
	int result = 0;
	bool reconnect = false;
	int i = 0;

	MysqlConnection *test_connection = p_global.dbpool->fetchConnection(
			MYCLIENT_AVERAGE_HOST_TYPE, &err, 0);
	if (test_connection == NULL)
	{
		gettimeofday(&e,NULL);
        FATAL_LOG("[ddbs_fatal], cost[%d], [error in fetch, err[%d]]", TIMEMSECDIFF(s, e), err);
		return -1;
	}
	test_connection->setFailHandler(fail_handler);

	DEBUG_LOG("get connection ok!");


	char query[] =
		"select  soid, cnt, m_date from co_user_behavior_cnt where baiduid = %u and soid in (%s) ;";
	err	= test_connection->queryf(&res, true, query, baiduid, song_set);
	DEBUG_LOG("sql execute[select soid, cnt, m_date from co_user_behavior_cnt where baiduid = %u and soid in (%s)", baiduid, song_set);

	if (err < success)
	{
		gettimeofday(&e,NULL);
        FATAL_LOG("[ddbs_fatal], cost[%d], msg[db_get_co_user_behavior_cnt], baiduid[%u], [sql error. myclient err[%d]]", TIMEMSECDIFF(s, e), baiduid, err);
		result = -1;
		reconnect = true;
	}
	else
	{
		unsigned int rows_count = res.getRowsCount();

		if (rows_count > 0)
		{
			const char *soid = NULL;
			const char *m_date = NULL;
			const char *cnt = NULL;
            user_cnt_t item;
			for (i = 0; (unsigned int) i < rows_count; i++)
			{
				soid = res[i][0];
				cnt = res[i][1];
				m_date = res[i][2];
                item.cnt = atoi(cnt);
                item.timestamp = atoi(m_date);
                user_cnt_map.insert(std::pair<int, user_cnt_t>(atoi(soid), item));
			}
			rows_count = i;
		}
		else
		{
			rows_count = 0;
		}
		result = (int) rows_count;
	}

	res.free();
	int ret = p_global.dbpool->putBackConnection(test_connection, reconnect);
	if (ret != 0)
	{
		gettimeofday(&e,NULL);
        WARNING_LOG("third[ddbs_third_fail], cost[%d], [putback connection ret[%d]]", TIMEMSECDIFF(s, e), ret);
		return -1;
	}
	DEBUG_LOG("put back connection ok!\n");
    //ddbs正常处理请求
    if(result >= 0){
        gettimeofday(&e,NULL);
        NOTICE_LOG("third[ddbs_third], cost[%d]", TIMEMSECDIFF(s, e));
    }
	return result;
}

int db_get_user_behavior_cnt(uint uid, const char* song_set, std::map<int, user_cnt_t> &user_cnt_map)
{
	struct timeval s;
    struct timeval e;
    gettimeofday(&s,NULL);
    MyclientRes res;
	int err = 0;
	int result = 0;
	bool reconnect = false;
	int i = 0;

	MysqlConnection *test_connection = p_global.dbpool->fetchConnection(
			MYCLIENT_AVERAGE_HOST_TYPE, &err, 0);
	if (test_connection == NULL)
	{
		gettimeofday(&e,NULL);
        FATAL_LOG("[ddbs_fatal], cost[%d], [error in fetch, err[%d]]", TIMEMSECDIFF(s, e), err);
		return -1;
	}
	test_connection->setFailHandler(fail_handler);

	DEBUG_LOG("get connection ok!");


	char timeStr[MAX_DIR_LEN];
	YearBefore(timeStr, MAX_DIR_LEN);
	char query[] =
		"select soid, cnt, m_date from user_behavior_cnt where uid = %u and soid in (%s);";
	err	= test_connection->queryf(&res, true, query, uid, song_set);
	DEBUG_LOG("sql execute[select soid, cnt, m_date from user_behavior_cnt where uid = %u and soid in (%s)", uid, song_set);

	if (err < success)
	{
		gettimeofday(&e,NULL);
        FATAL_LOG("[ddbs_fatal], cost[%d], msg[db_get_user_behavior_cnt], uid[%u], [sql error. myclient err[%d]]", TIMEMSECDIFF(s, e), uid, err);
		result = -1;
		reconnect = true;
	}
	else
	{
		unsigned int rows_count = res.getRowsCount();

		if (rows_count > 0)
		{
			const char *soid = NULL;
			const char *m_date = NULL;
			const char *cnt = NULL;
            user_cnt_t item;
			for (i = 0; (unsigned int) i < rows_count; i++)
			{
				soid = res[i][0];
				cnt = res[i][1];
				m_date = res[i][2];
                item.cnt = atoi(cnt);
                item.timestamp = atoi(m_date);
                user_cnt_map.insert(std::pair<int, user_cnt_t>(atoi(soid), item));
			}
			rows_count = i;
		}
		else
		{
			rows_count = 0;
		}
		result = (int) rows_count;
	}

	res.free();
	int ret = p_global.dbpool->putBackConnection(test_connection, reconnect);
	if (ret != 0)
	{
		gettimeofday(&e,NULL);
        WARNING_LOG("third[ddbs_third_fail], cost[%d], [putback connection ret[%d]]", TIMEMSECDIFF(s, e), ret);
		return -1;
	}
	DEBUG_LOG("put back connection ok!\n");
    //ddbs正常处理请求
    if(result >= 0){
        gettimeofday(&e,NULL);
        NOTICE_LOG("third[ddbs_third], cost[%d]", TIMEMSECDIFF(s, e));
    }
	return result;
}

