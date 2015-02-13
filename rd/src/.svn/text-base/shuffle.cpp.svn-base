/**
 * =====================================================================================
 *
 *	Filename:  shuffle.cpp
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

#include <time.h>
#include <stdlib.h>
#include "shuffle.h"
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
 * ========================================================================
 */
void permutation(int len, int *perm)
{
	int i;
	int j;
	unsigned int rand_tmp;
	unsigned int rand_seed = time(NULL);
	int tmp;

	// First initialize the array "perm" to the identity permutation.
	for (j = 0; j < len; j++)
	{
		perm[j] = j;
	}

	// Now swap a random element in the front with the i'th element.
	// When i gets down to 0, we're done.
	for (i = len - 1; i > 0; i--) // Element i is a swap candidate.
	{
		rand_tmp = (unsigned int) rand_r(&rand_seed);
		rand_tmp %= i;
		tmp = perm[i]; // Swap elements i and k.
		perm[i] = perm[rand_tmp];
		perm[rand_tmp] = tmp;
	}
}

