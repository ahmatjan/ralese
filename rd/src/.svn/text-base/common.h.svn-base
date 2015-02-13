/**
 * =====================================================================================
 *
 *	Filename:  common.h
 *
 *	Description:  header file for common.cpp
 *
 *	Version:  1.0
 *  Created: 2010-12-05
 *	Revision:  none
 *	Compiler:  gcc
 *
 *	Author:  zhangjunying, zhangjunying@baidu.com
 *	Company:  baidu.com Inc.
 *
 * =====================================================================================
 */
#ifndef __common_h
#define __common_h

#include <ctype.h>
#include "ul_log.h"
#include "ul_conf.h"
#include "rls.h"

////////////////////////////////////////////////////////////////////
/** common macro function */
#define TIMEDIFF(s, e)          (((e.tv_sec)-(s.tv_sec))*1000000 + (e.tv_usec) - (s.tv_usec))
#define TIMEMSECDIFF(s, e)      (((e.tv_sec)-(s.tv_sec))*1000 + ((e.tv_usec) - (s.tv_usec))/1000)
/**< space or table*/
#define IS_SPACE(ch)                    (' ' ==  (ch) || '\t' == (ch))
/**< change line */
#define IS_CHANGELINE(ch)               ('\r' ==  (ch) || '\n' == (ch))
/**< english character*/
#define IS_ENG(ch)                      (((ch) >= 'a' && (ch) <= 'z') || ((ch) >= 'A' && (ch) <='Z') )
/**< chinese character*/
#define IS_CHN(ch)                      ((ch) & 0x80)
/**< chinese space*/
#define IS_CHN_SPACE(ch0,ch1)   ((unsigned char)(ch0) == 0xA1 && (unsigned char)(ch1) == 0xA1)
/**< digital> */
#define IS_DIGITAL(ch)                  ((ch) - '0' >=0 && (ch) - '0' <= 9)
/**< sep*/
#define IS_SEP(ch)                              ((ch) == '-' || (ch) == '_')

///**< num func */
//#ifndef	min
///**< max */
//#define min(a,b) (((a)<(b))?(a):(b))
//#endif

//#ifndef	max
///**< min */
//#define max(a,b) (((a)>(b))?(a):(b))
//#endif

/**< str func */
//#define strlcpy(dst, src, size) snprintf ((dst), (size), "%s", (src))

/**< some usefull macro function */
//FATAL LOG wrapper
#define FATAL_LOG(fmt, arg...) do { \
    ul_writelog(UL_LOG_FATAL, "[%s:%d] " fmt " [%m]", __FILE__, __LINE__, ## arg); \
}while (0)
//WARNING LOG wrapper
#define WARNING_LOG(fmt, arg...) do { \
    ul_writelog(UL_LOG_WARNING, "[%s:%d] " fmt " [%m]", __FILE__, __LINE__, ## arg); \
}while (0)
//notice LOG wrapper
#define NOTICE_LOG(fmt, arg...) do { \
    ul_writelog(UL_LOG_NOTICE, "[%s:%d] " fmt, __FILE__, __LINE__, ## arg); \
}while (0)
//debug LOG wrapper
#define DEBUG_LOG(fmt, arg...) do { \
    ul_writelog(UL_LOG_DEBUG, "[%s:%d] " fmt, __FILE__, __LINE__, ## arg); \
}while (0)
//trace LOG wrapper
#define TRACE_LOG(fmt, arg...) do { \
    ul_writelog(UL_LOG_TRACE, "[%s:%d] " fmt, __FILE__, __LINE__, ## arg); \
}while (0)
#define MESSAGE_LOG(tag, msg) do { \
    com_writelog("MESSAGE", "tag[%s], msg[%s]", tag, msg); \
}while (0)
#define BPR_LOG(tag, msg) do { \
    com_writelog("BPR", "tag[%s], msg[%s]", tag, msg); \
}while (0)

//max in file num
#define MAX_IN_FILE_NUM 10



/////////////////////////////////////////////////////
/// functions statment

/**
 ** @function: init timer
 ** @param tindex : thread id
 ** @return : none
 **/
void init_timer(const int tindex);

/**
 ** @function: init timer
 ** @param type : record type
 ** @param tindex : thread id
 ** @return : none
 **/
void start_timer(int type, const int tindex);

/**
 ** @function: finish timer
 ** @param type : record type
 ** @param tindex : thread id
 ** @return : none
 **/
void finish_timer(int type, const int tindex);

/**
 ** @function: open series files
 ** @param dir : file dir
 ** @param file_name : common segment of filename
  ** @param file_no : file no of filename
 ** @return : FILE * or NULL
 **/
FILE * open_series_files(const char *dir,const char *file_name,int *file_no);

/**
 * @function: 删除一个字符串开头及结尾的空白符,str内容将被修改;删除空白符后的字符串长度为0或str==NULL,返回NULL
 * 其它情况返回不含空白符的字符串
 * @param s: the str need to be processed
 * @return the processed string pointer; NULL: err
 */

int strTrim(char *des,char *src,int des_len);
/**
 * @function: fix the last half chinese word
 * @param s: the chinese str
 * @return 0: ok
 */
int FixLastChr(char *s);


/**
 * @brief : read dat file into membuf
 * @param
 * @return 0:ok; -1:read error
 */
int read_file_in_mem(const char *file_path,void **pdata, uint st_size, uint max_node_num, uint *read_node_num);

/**
 *@brief:创建百度id
 *@param[in]:百度id字符串,cookieid
 *@param[in]:baiduid,结果
 *@return:0:ok, -1:fail
*/
int create_baiduid(char* baiduid_str, uint &baiduid);

#endif
