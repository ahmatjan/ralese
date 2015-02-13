//============================================================================
// @author      : weijingqi (weijingqi@baidu.com)
// @file        : mystring.h
// @date        : 28 Oct 2011,17:51:41
// @copyright   : 2011 Baidu.com, Inc. All Rights Reserved
// @encoding    : 
// @version     : 
// @brief       : 字符串相关的处理
//============================================================================

#ifndef _MYSTRING_H
#define _MYSTRING_H
#include <vector>
#include <string>
#include <memory.h>

//是否是空格,需要trim掉的字符
#define        ISSPACE(x)        ((x)==' '||(x)=='\r'||(x)=='\n'||(x)=='\f'||(x)=='\b'||(x)=='\t')
namespace cmm{
    /**
     *@brief:将字符串进行分割
     *@param[in]:src,源字符串
     *@param[in]:delim,分隔符
     *@param[out]:分割后的字符串数组
     */
    int str_split(const char* src, const char* delim, std::vector<std::string> &str_segs);
    /**
     *@brief: trim一个字符串 
     *@param[in]:str,原始的字符串 
     *@return: trim之后的字符串
     */
    char* str_trim(char* str);
    /**
     *@brief:字符串替换,将一个字符替换长一个字符串
     *@param[in]:str, 原始的字符串
     *@param[in]:pattern,要替换的字符
     *@param[in]:replace，替换后的字符串
     *@return:替换后的字符串的结构
     */
    const char* str_replacechar(const char* str, char pattern, char* replace);
}

#endif /* _MYSTRING_H */

