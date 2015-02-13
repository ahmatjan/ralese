/**
 * =====================================================================================
 *
 *	Filename:  common.cpp
 *
 *	Description:  header file for common.cpp
 *
 *	Version:  1.0
 *  Created: 2010-8-25
 *	Revision:  none
 *	Compiler:  gcc
 *
 *	Author:  zhangjunying, zhangjunying@baidu.com
 *	Company:  baidu.com Inc.
 *
 * =====================================================================================
 */
#include "common.h"
#include "ul_sign.h"

/**********global var**********/
//static char esp_char[4] = {'#', '<', '>', '"'};

/***********************************
字符串最有一个字符双字修订，注意是直接在源字符串上修改
s:	要检查的字符串
***********************************/
/**
 *@brief 功能：  trim the last half zi
 *
 *@param s 需要修订的字符串
 *@return
 * */ 
int FixLastChr(char *s)
{
	char	*p = s;
	char flag = 0;

	while (*p) {
		if (*p & 0x80)
		{
			flag = (flag) ? 0 : 1;
		}
		else
		{
			flag = 0;
		}
		p ++;
	}

	if (flag)
	{
		*(--p) = 0;
	}

	return 0;
}

/**
 * @breif 消除字符串前后空格 
 * @param des: 过滤后字符串
 * @param src: 原字符串
 * @param des_len：字符串长度
 * @return dest str len
 */
int strTrim(char *des,char *src,int des_len)
{
	char *p1;
	char *p2;
	char *pd;
	p1 = src;
	p2 = src + (strlen(src) -1);
	pd = des;

	while (0x20 == *p1)
	{
		p1++;
	}
	while (0x20 == *p2)
	{
		p2--;
	}

	p2++;
	while ((p1 != p2) && (pd-des < des_len-1))
	{
		*pd++ = *p1++;
	}
	*pd = '\0';

	return pd-des;
}


/**
 * @brief : open files. try,0,1,2,3,4,5,6,7,8,9...50
 * @param void
 * @return not NULL:ok; NULL; no more files
 */
FILE * open_series_files(const char *dir,const char *file_name,int *file_no)
{
	char tmp_buf[MAX_DIR_LEN];

	snprintf(tmp_buf,sizeof(tmp_buf),"%s%s.%d",dir, file_name,*file_no);
	*file_no = *file_no + 1;
	NOTICE_LOG("now try open the file.%s",tmp_buf);
	FILE * fp = fopen(tmp_buf,"r");
	if (fp != NULL)
	{
		NOTICE_LOG("open file succ.[%s]",tmp_buf);
		return fp;
	}

	while ( *file_no < MAX_IN_FILE_NUM)
	{
		snprintf(tmp_buf,sizeof(tmp_buf),"%s%s.%d",dir,file_name,*file_no);
		*file_no = *file_no +1;
		NOTICE_LOG("now try open the file.%s",tmp_buf);
		fp = fopen(tmp_buf,"r");
		if (fp != NULL)
		{
			NOTICE_LOG("open file succ.[%s]",tmp_buf);
			return fp;
		}
	}

	NOTICE_LOG("[file_no:%d] is too big,wont try",*file_no);
	return NULL;
}


/**
 * @brief : read dat file into membuf
 * @param
 * @return 0:ok; -1:read error
 */
int read_file_in_mem(const char *file_path, void **pdata, uint st_size,
		uint max_node_num, uint *read_node_num)
{
	if(file_path==NULL || pdata==NULL)
	{
		return -1;
	}
	FILE *fp=NULL;
	struct stat statbuf;
	int remain_size;
	int ret=-1;
	int read_err=-1;
	uint node_num;
	uint read_size;

	do{
		ret = stat(file_path, &statbuf);
		if ( 0 != ret )
		{
		  WARNING_LOG("input file not exist[%s]\n",file_path);
		  break;
		}
		fp=fopen(file_path,"r");
		if (fp == NULL)
		{
			WARNING_LOG("input file not exist[%s]\n",file_path);
		  break;
		}
		if(st_size!=0)
		{
			node_num=statbuf.st_size / st_size;
			if(0 == node_num)
			{
				FATAL_LOG("input file size is err[%s][size:%lu][st_size:%u]",file_path,statbuf.st_size,st_size);
				break;
			}
			remain_size=statbuf.st_size % st_size;
			if(remain_size!=0)
			{
				FATAL_LOG("input file size is err[%s][size:%lu][st_size:%u]",file_path,statbuf.st_size,st_size);
				break;
			}
			if(max_node_num!=0 && max_node_num<node_num)
			{
				FATAL_LOG("intput node num id too big[%s][max:%u][cur:%u]",file_path,max_node_num,node_num);
				break;
			}
			if(*pdata==NULL)
			{
				*pdata=calloc ( statbuf.st_size, 1);
				if(*pdata==NULL)
				{
					FATAL_LOG("cant alloc mem[size:%lu]",statbuf.st_size);
					break;
				}
				NOTICE_LOG("alloc mem for[path:%s]",file_path);
			}
			read_size = fread(*pdata, st_size, node_num, fp);
			if ( read_size != node_num )
			{
				FATAL_LOG("read file[%s] fail, read[%u],node[%u],st_size[%u]",
							file_path, read_size, node_num,st_size);
				break;
			}
		}else{
			if(*pdata==NULL)
			{
				*pdata=calloc ( statbuf.st_size, sizeof(char));
				if(*pdata==NULL)
				{
					FATAL_LOG("cant alloc mem[size:%lu]",statbuf.st_size);
					break;
				}
				NOTICE_LOG("alloc mem for[path:%s]",file_path);
			}
			read_size = fread(*pdata, sizeof(char),statbuf.st_size, fp);
			if ( read_size != (uint)statbuf.st_size )
			{
				FATAL_LOG("read file[%s] fail, read[%u],st_size[%lu]",
							file_path, read_size, statbuf.st_size);
				break;
			}
		}
		read_err=0;
	}while(false);
	if(fp!=NULL)
	{
		fclose(fp);
	}
	if(NULL!=read_node_num)
	{
		*read_node_num=node_num;
	}
	return read_err;
}

int create_baiduid(char* baiduid_str, uint &baiduid){
    if(NULL == baiduid_str){
        WARNING_LOG("wrong param");
        return -1;
    }
    unsigned int s1, s2;
    int ret = creat_sign_fs64(baiduid_str, 32, &s1, &s2);
    if(ret != 1){
        WARNING_LOG("create_sing_fs64 fail");
        return -1;
    }
    baiduid = s1 + s2;
    return 0;
}
