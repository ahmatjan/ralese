/**
 * =====================================================================================
 *
 *	Filename:  shuffle.h
 *
 *	Description:  header file for shuffle.cpp
 *
 *	Version:  1.0
 *  Created: 2010-7-25
 *	Revision:  none
 *	Compiler:  gcc
 *
 *	Author:  zhangjunying, zhangjunying@baidu.com
 *	Company:  baidu.com Inc.
 *
 * =====================================================================================
 */

#ifndef _SHUFFLE_H_
#define _SHUFFLE_H_

/**
 * ===================  FUNCTION permutation ==============================
 * @brief shuffle a integer array
 *
 * @param [in] len, the length of the integer array
 * @param [in] perm, the array will be shuffled
 * @param [out] perm, shuffling result
 *
 * @return void
 * @retval errno
 *
 * @author zhangjunying, zhangjunying@baidu.com
 * @date 2010-7-25
 * @company Baidu Inc.
 * ==============================================================================
 */
void permutation( int len, int *perm );


#endif /* _SHUFFLE_H_ */
