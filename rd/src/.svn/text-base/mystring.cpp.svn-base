
//============================================================================
// @author      : weijingqi (weijingqi@baidu.com)
// @file        : mystring.h
// @date        : 28 Oct 2011,17:51:41
// @copyright   : 2011 Baidu.com, Inc. All Rights Reserved
// @encoding    : 
// @version     : 
// @brief       : 字符串相关的处理
//============================================================================
#include <cstring>
#include <pthread.h>
#include "mystring.h"

#include <iostream>

namespace cmm{

    int str_split(const char* src_in, const char* delim, std::vector<std::string> &str_segs){
        if(NULL == src_in || NULL == delim){
            return -1;
        }
        std::string str;
        std::string in_str = std::string(src_in);
        char* src = const_cast<char*>(in_str.c_str());
        char* result = NULL;
        char* out = NULL;
        result = strtok_r(src, delim, &out);
        int i = 0;
        while(NULL != result){
            str.assign(result);
            str_segs.push_back(str);
            result = strtok_r(NULL, delim, &out);
        }
        return 0;
    }

    char* str_trim(char* str){
        char* tail;
        char* head;
        for (tail = str + strlen(str) - 1; tail >= str; tail-- ){
            if (!ISSPACE(*tail)){
                break;
            }
        }
        tail[1] = 0;
        for(head = str; head <= tail; head++ ){
            if (!ISSPACE(*head ))
                break;
        }
        if (head != str)
            memcpy(str, head, (tail-head+2 )*sizeof(char));
        return str;
    }

    const char* str_replacechar(const char* str, char pattern, char* replace){
        uint32_t size = strlen(str);
        uint32_t replacesize = strlen(replace);
        std::string mystr;
        mystr.reserve(size*2);
        int i,j;
        for(i = 0; i < size; i++){
            if(str[i] == pattern){
                for(j = 0; j < replacesize; j++){
                    mystr.push_back(replace[j]);
                }
            }
            else{
                mystr.push_back(str[i]);
            }
        }
        return mystr.c_str();
    }
}

