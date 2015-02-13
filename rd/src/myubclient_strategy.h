//============================================================================
// @author      : weijingqi (weijingqi@baidu.com)
// @file        : myubclient_strategy.h
// @date        : 25 Apr 2012,15:24:26
// @copyright   : 2012 Baidu.com, Inc. All Rights Reserved
// @encoding    : 
// @version     : 
// @brief       : 
//============================================================================

#ifndef _MYUBCLIENT_STRATEGY_H_
#define _MYUBCLIENT_STRATEGY_H_ 
#include <ubclient_include.h>
#include "ubclient_strategy.h"

/**
 * @brief MyUbClientStrategy,自定义的ubclient 策略
 * 在filterServer时，过滤非健康的机器，当前机房的机器正常个数>=当前机房机器总数的1/2情况下，
 * 过滤掉其他机房的机器(只使用当前机房的机器),否则启用其他机房的机器
 * 当前机房机器 配置Master 1 , 其它机房机器配置 Master 0
 */
class MyUbClientStrategy : public ub::UbClientStrategy{
 public:
    /**
     * @brief :构造函数
     **/
    MyUbClientStrategy(){}
    /**
     * @brief :虚构函数
     **/
    virtual ~MyUbClientStrategy(){}

    /**
     * @brief server选择接口，非healthy状态的server将被过滤,当前机房机器都正常时，将过滤其他机房的机器
     * 参数注释参见ubclient_strategy.h中
     * @param [in/out] req   : ConnectionRequestex*
     * @param [in] confVar   : bsl::var::IVar&
     * @param [in/out] serverSelectedInfo   : ConnectionRes *
     * @return  int
     * 0 : 成功
     * -1 : 失败
     **/
    virtual int filterServer(ub::ConnectionRequestex *req, 
                             bsl::var::IVar& confVar,
                             ub::ConnectionRes *serverSelectedInfo);
};
#endif /* _MYUBCLIENT_STRATEGY_H_ */
