/**
 * =====================================================================================
 *
 *  Filename:  rls_instant.h
 *
 *  Description:  header file for rls_instant.cpp, 即时用户模型
 *
 *  Version:  1.0
 *  Created: 2012-10-29
 *  Revision:  none
 *  Compiler:  gcc
 *
 *  Author:  wensaiping@baidu.com
 *  Company:  baidu.com Inc.
 *
 * =====================================================================================
 */

#ifndef _RLS_INSTANCE_H
#define _RLS_INSTANCE_H

#include<time.h>
#include "bsl/pool.h"
#include "ub.h"
#include "macro.h"
#include "rls.h"
#include "dao.h"
#include "rls_struct.h"
#include "userworker.h"


//即时行为建模默认提权和降权的维度 
const int DEFAULT_LAN_UP = 0;//华语
const int DEFAULT_LAN_DE = 2;//粤语
const int DEFAULT_YEAR_UP = 4;//11到现在
const int DEFAULT_YEAR_DE = 0;//81-90
const int DEFAULT_AREA_UP = 1;//港台
const int DEFAULT_AREA_DE = 0;//内地
const int DEFAULT_GENDER_UP = 0;//女
const int DEFAULT_GENDER_DE = 2;//组合
//即时行为推荐歌曲的默认权值
const int DEFAULT_INSTANT_SONG_WEIGHT = 30;

//华语的维度
const int HUAYU_LAN = 0;
//华语倍率
const int HUAYU_RATE = 2;
//华语初始化值
const int HUAYU_INIT = 8;

/**
 * 单首歌曲计算即时用户权值
 * instant_model， 即时用户模型
 * songid, 歌曲id
 * type 歌曲处理类型（加心，60s等）
 * rate 不同行为的倍率
 * dim_type 建模维度度
 * return >=0 成功 -1失败
 */
int per_instant_songid(instant_model_t& instant_model, int song_id, int type, int rate);

/**
 * 建立用户模型
 * instant_model， 即时用户模型
 * i_user_data, 即时用户数据
 * ch_name 频道名
 * return >=0 成功 -1失败
 */
int build_instant_model(instant_model_t& instant_model, i_userdata_t i_user_data, const char * ch_name);

/**
 * 单首歌曲计算即时用户权值
 * instant_model，即时用户模型
 * songid, 歌曲id
 * type 歌曲处理类型（加心，60s等）
 * dim 为试探的维度
 * return >=0 成功 -1失败
 */
int detect_instant_songid(instant_model_t& instant_model, int song_id, int type, int dim);

#endif /* _RLS_INSTANCE_H */
