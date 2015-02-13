/**
 * =====================================================================================
 *
 *	Filename:  userworker.h
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

#ifndef _USERWORKER_H_
#define _USERWORKER_H_

#include "bsl/pool.h"
#include "idl/rls2.idl.h"
#include "bsl/exception.h"
#include "rls.h"
#include "rls_struct.h"

/**
 * @brief 用户处理数据线程函数
 * @param arg :线程id
 * @return
 */
void *userworker(void *arg);

/**
 * 获取歌曲详细信息数据
 */
inline Song_brief_t* get_song_brief(uint itemid)
{
	if(0 == itemid)
	{
		WARNING_LOG("error itemid[0]");
		return NULL;
	}

	sodict_snode_t node;
	node.sign1 = itemid;
	node.sign2 = SONG_BRIEF;

	int ret = odb_seek_search(p_global.bigDict, &node);
	if (ret != ODB_SEEK_OK)
	{
		WARNING_LOG("seek bigDict faild [ret:%d][sign1:%u][sign2:%u]", ret, node.sign1, node.sign2);
		return NULL;
	}

	if (node.cuint1 >= p_global.max_songbrief_len)
	{
		WARNING_LOG("bad pos[%u] for SONG_BRIEF buf. max len[%u]",
				node.cuint1, p_global.max_songbrief_len);
		return NULL;
	}

	return  p_global.songbrieflist + node.cuint1;
}


#endif /* _USERWORKER_H_ */
