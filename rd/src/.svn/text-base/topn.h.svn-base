/**
 * =====================================================================================
 *
 *	Filename:  topn.h
 *
 *	Description:  header file for topn.cpp
 *
 *	Version:  1.0
 *  Created: 2011-6-14
 *	Revision:  none
 *	Compiler:  gcc
 *
 *	Author:  zhangjunying, zhangjunying@baidu.com
 *	Company:  baidu.com Inc.
 *
 * =====================================================================================
 */

#ifndef _TOPN_H_
#define _TOPN_H_

#include <stdio.h>
#include <string.h>
#include <vector>
#include <algorithm>


/**
 * topN堆操作模板函数。向堆中放入item
 * [in]
 *  p 堆buf的指针
 *  x 数据引用
 *  cmp 比较函数
 *
 * return void
 */
template <class T> void topN_put(T* p, int len, T const & x, bool(*cmp)(T const& a, T const& b))
{
    if (NULL == p || len <= 0)
    {
        return;
    }
    if(cmp(x, p[0]))
    {
        std::pop_heap(p, p+len, cmp);
        p[len-1]=x;
        std::push_heap(p, p+len, cmp);
    }
}

/**
 * topN堆操作模板函数。向堆中放入item
 * [in]
 *  p 堆buf的指针
 *  x 数据引用, 返回堆中pop的对象
 *  cmp 比较函数
 *  item, pop调整堆是输出的歌曲
 * return bool, true需要调整堆，false为不需要调整堆
 */
template <class T> bool topN_put_out(T* p, int len, const T & x, bool(*cmp)(T const& a, T const& b), T &pop_item)
{
    if (NULL == p || len <= 0)
    {
        return false;
    }
    T item = x;
    if(cmp(x, p[0]))
    {
        item = p[0];
        std::pop_heap(p, p+len, cmp);
        p[len-1]=x;
        std::push_heap(p, p+len, cmp);
        return true;
    }    
    return false;
}
#endif /* _TOPN_H_ */
