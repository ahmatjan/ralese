/**
 * =====================================================================================
 *
 *	Filename:  reload.h
 *
 *	Description:  header file for reload.cpp
 *
 *	Version:  1.0
 *  Created: 2010-11-24
 *	Revision:  none
 *	Compiler:  gcc
 *
 *	Author:  zhangjunying, zhangjunying@baidu.com
 *	Company:  baidu.com Inc.
 *
 * =====================================================================================
 */

#ifndef _RELOAD_H_
#define _RELOAD_H_

/**< RELOAD CMD */
#define SIG_RELOAD_CMD 1
/**< SHOW LIST CMD */
#define RELOAD_SHOW_CMD 0
/**< SET LIST CMD */
#define RELOAD_SET_CMD 1

/**
 *  @function reload thread function
 *  	difference singnal will lead to reloading difference data
 *
 *  @param[in]  无
 *  @param[out]  无
 *  @return 操作结果
 *  	-1    失败
 *  	0     成功
 */
extern void *svr_reload(void *arg);

#endif /* _RELOAD_H_ */
