//============================================================================
// @author      : weijingqi (weijingqi@baidu.com)
// @file        : rls_rstrategy.h
// @date        : 13 May 2012,11:44:14
// @copyright   : 2011 Baidu.com, Inc. All Rights Reserved
// @encoding    :
// @version     :
// @brief       : 推荐策略
//============================================================================

#include "rls_rstrategy.h"
namespace rls{



	/**
	 * ===================  FUNCTION singer com ==============================
	 * @brief 根据成功率对选出来的结果进行快排
	 * return true a排b前，false a排b后
	 * ===========================================================================
	 */
	bool singer_cmp(Singer_item_t a, Singer_item_t b){
		return a.weight > b.weight;
	}

	/**
     * 平滑数据距离比较
     */
    bool smooth_data_cmp(smooth_data_t const &a, smooth_data_t const &b){
        return a.distance < b.distance;
    }

	RStrategy::RStrategy(){
		_dict_seeker = new DictSeeker();
		_ral = new RAl();
	}

	RStrategy::~RStrategy(){
		if(NULL != _dict_seeker){
			delete _dict_seeker;
		}
		if(NULL != _ral){
			delete _ral;
		}
	}

	/**
	 *@brief:对列表进行重排序,保证M首歌区中,不出现N个相同歌手的歌.
	 *@param[in]:p_userlist,输入的歌曲列表
	 *@param[in]:userlist_len,用户歌曲列表的长度
	 *@param[in]:M,区间长度
	 *@param[in]:N,最多的重复个数,暂时保留，不使用
	 *@param[in]:need_sort, 是否需要先排序
	 *@return:FAIL SUCCESS
	 */
	int RStrategy::arrange_user_list(Song_item_t *p_userlist, int userlist_len, int M, int N, bool need_sort){
		if(NULL == p_userlist){
			WARNING_LOG("p_userlist is NULL");
			return -1;
		}
		if(userlist_len < 0){
			WARNING_LOG("userlist_len[%d] < 0", userlist_len);
			return -1;
		}
		if(0 == userlist_len){
			return 0;
		}
		if(N>=M){
			TRACE_LOG("N[%d]>=M[%d] nothing need to do",N,M);
			return 0;
		}
		if(M <= 1){
			WARNING_LOG("M[%d] <= 1 nothing need to do", M);
			return 0;
		}
		if(userlist_len > MAX_USER_LIST_LEN){
			WARNING_LOG("userlist_len[%d] > MAX_USER_LIST_LEN[%d]", userlist_len, MAX_USER_LIST_LEN);
			return -1;
		}

		//是否需要排序
		if (need_sort){
			_ral->sort_songlist(p_userlist, userlist_len);
		}

#ifdef _DEBUG_TIME
		DEBUG_LOG("before arrange_singer, [M:%d] [N:%d]", M, N);
		for(int i = 0; i < userlist_len; i++){
			int _singer_id = _dict_seeker->get_singer_id(p_userlist[i].song_id);
			DEBUG_LOG("[singerid:%d][songid:%d][weight:%d]", _singer_id,p_userlist[i].song_id, p_userlist[i].weight);
		}
#endif

		//区间歌手去重队列
		singer_queue_t singer_queue;
		singer_queue.tail = singer_queue.head = 0;
		//判重map,存储当前队列的singer_id
		bsl::hashmap<uint, uint> singer_map;
		singer_map.create(M);
		uint singer_id = 0;
		uint tmp_singer_id = 0;
		uint tmp_song_id = 0;
		uint tmp = 0;
		Song_item_t tmp_item;
		int i,j;
		for(i = 0; i < userlist_len; i ++){
			singer_id = _dict_seeker->get_singer_id(p_userlist[i].song_id);
			if(singer_id <= 0){
				//没歌手时，置入随机数，以免歌手为空时，按singer_id = 0打散
				singer_id = rand();
			}

			//已经存在于队列中
			if(singer_map.get(singer_id, &tmp) == bsl::HASH_EXIST){
				//从list后查找不在队列中的歌曲
				for(j = i + 1; j < userlist_len; j++){
					tmp_singer_id = _dict_seeker->get_singer_id(p_userlist[j].song_id);
					if(tmp_singer_id <= 0){
						//没歌手歌曲，转入随机数
						tmp_singer_id = rand();
					}
					if(singer_map.get(tmp_singer_id, &tmp) == bsl::HASH_NOEXIST){
						singer_id = tmp_singer_id;
						memcpy(&tmp_item, p_userlist + i, sizeof(Song_item_t));
						memcpy(p_userlist + i, p_userlist + j, sizeof(Song_item_t));
						memcpy(p_userlist + j, &tmp_item, sizeof(Song_item_t));
						break;
					}
				}
				//在list后查取不到非队列中的singer_id时，已经无法完成后部歌曲的打散
				if (j == userlist_len){
					break;
				}
			}

			//更新queue与hashmap
			//singer_queue.head = (singer_queue.head + 1) % M;
			singer_queue.singers[singer_queue.head] = singer_id;
			singer_queue.head = (singer_queue.head + 1) % M;
			singer_map.set(singer_id, 0);

			//队列满
			if (singer_queue.head  == singer_queue.tail){
				tmp_singer_id = singer_queue.singers[singer_queue.tail];
				singer_map.erase(tmp_singer_id);
				singer_queue.tail = (singer_queue.tail + 1) % M;
			}
		}
		singer_map.destroy();
#ifdef _DEBUG_TIME
		DEBUG_LOG("after arrange_singer");
		for(int i = 0; i < userlist_len; i++){
			int _singer_id = _dict_seeker->get_singer_id(p_userlist[i].song_id);
			DEBUG_LOG("[singerid:%d][songid:%d][weight:%d]", _singer_id,p_userlist[i].song_id, p_userlist[i].weight);
		}
#endif
		return SUCCESS;
	}

	/**
	 *@brief:对列表进行重排序,保证M首歌区中,不出现N个相同歌手的歌.
	 *@param[in]:p_userlist,输入的歌曲列表
	 *@param[in]:userlist_len,用户歌曲列表的长度
	 *@param[in]:hate_singer_len,过滤垃圾桶歌曲数
	 *@param[in]:pass_singer_len,过滤跳过数
	 *@param[in]:filter_len, 过滤长度
	 *@param[in]:user_data, 用户数据
	 *@return:FAIL SUCCESS
	 */
	int RStrategy::filter_user_list(Song_item_t *p_userlist, unsigned int& userlist_len,
			int hate_singer_len, int pass_singer_len,
			int filter_len, const r_userdata_t &user_data)
	{
		if(NULL == p_userlist){
			WARNING_LOG("p_userlist is NULL");
			return -1;
		}
		if(userlist_len < 0 || filter_len < 0){
			WARNING_LOG("userlist_len[%d] < 0 or filter_len[%d] < 0 ", userlist_len, filter_len);
			return -1;
		}
		if(0 == userlist_len || 0 == filter_len){
			return 0;
		}
		if(hate_singer_len < 0 || pass_singer_len < 0){
			WARNING_LOG("hate_singer_len[%d] < 0 or pass_singer_len[%d] < 0 ", hate_singer_len, pass_singer_len);
			return -1;
		}
#ifdef _DEBUG_TIME
        for(int i = 0; i < userlist_len; i++){
			DEBUG_LOG("filter before:, position:%d, song_id:%u, weight:%d", i, p_userlist[i].song_id, p_userlist[i].weight);
        }
#endif

		//存储需要过滤的歌曲id
		bsl::hashmap<uint, uint> filter_map;
		filter_map.create(hate_singer_len + pass_singer_len);
		uint singer_id = 0;
		uint item_id = 0;
		//填充hate song singer
		for(int i = 0; i < hate_singer_len && i < user_data.len_songhate; i++){
			item_id = user_data.songhate[i].itemid;
			singer_id = _dict_seeker->get_singer_id(item_id);
			filter_map.set(singer_id, 0);
		}
		//填充pass song singer
		for(int i = 0; i < pass_singer_len && i < user_data.len_action; i++){
			if(user_data.action[i].type != DB_NEXT_SONG)
				continue;
			item_id = user_data.action[i].itemid;
			singer_id = _dict_seeker->get_singer_id(item_id);
			filter_map.set(singer_id, 0);
		}

		//过滤歌曲
		Song_item_t tmp_list[MAX_USER_LIST_LEN];
		int tmp_list_len = 0;
		int song_id = 0;
		int i = 0;
		for(; i < filter_len && i < userlist_len; i++){
			song_id = p_userlist[i].song_id;
			bool not_filter = true;
			for(bsl::hashmap <uint, uint>::iterator iter =  filter_map.begin(); iter != filter_map.end(); iter++ ){
                singer_id = iter->first;
		        if(_dict_seeker->get_singer_id(song_id) == singer_id){
		#ifdef _DEBUG_TIME
		            DEBUG_LOG("delete singer, [i:%d][songid:%u]", i, p_userlist[i].song_id);
		#endif
		            not_filter = false;
		            break;
		        }
        	}
        	if(not_filter){
	        	memcpy(tmp_list + tmp_list_len, p_userlist + i, sizeof(Song_item_t));
				tmp_list_len++;
			}
        }
		//剩下的拷贝
        if(userlist_len > i){
        	memcpy(tmp_list + tmp_list_len, p_userlist + i, sizeof(Song_item_t) * (userlist_len - i));
        	tmp_list_len +=  userlist_len - i;
        }
		userlist_len = tmp_list_len;
		memcpy(p_userlist, tmp_list, tmp_list_len * sizeof(Song_item_t));
        filter_map.destroy();
#ifdef _DEBUG_TIME
        for(int i = 0; i < userlist_len; i++){
			DEBUG_LOG("filter over:, position:%d, song_id:%u, weight:%d", i, p_userlist[i].song_id, p_userlist[i].weight);
        }
#endif
        return SUCCESS;
	}


	/**
	 *@brief:重定义歌曲列表权值
	 *@param[in]:p_userlist,输入的歌曲列表
	 *@param[in]:userlist_len,用户歌曲列表的长度
	 *@return:FAIL SUCCESS
	 */
	int RStrategy::define_list_weight(Song_item_t *p_userlist, int userlist_len)
	{
		if(NULL == p_userlist){
			WARNING_LOG("p_userlist is NULL");
			return -1;
		}
		if(userlist_len < 0){
			WARNING_LOG("userlist_len[%d] < 0 ", userlist_len);
			return -1;
		}
		if(0 == userlist_len){
			return 0;
		}
		int weight = 0;
		for(int i = 0; i < userlist_len; i++){
			weight = MAX_WEIGHT * exp(((-1.0) * i)/g_config.weight_param);
			p_userlist[i].weight = weight;
		}
        return SUCCESS;
	}

	/**
	 *@brief:歌曲列表平滑
	 *@param[in]:p_userlist,输入的歌曲列表
	 *@param[in]:userlist_len,用户歌曲列表的长度
	 *@param[in]:M,平滑区间
	 *@param[in]:L,平滑剔除长度
	 *@param[in]:N,平滑次数
	 *@return:FAIL SUCCESS
	 */
	int RStrategy::smooth_list(Song_item_t *p_userlist, int userlist_len, int M, int L, int N)
	{
		if(NULL == p_userlist){
			WARNING_LOG("p_userlist is NULL");
			return -1;
		}
		if(userlist_len < 0){
			WARNING_LOG("userlist_len[%d] < 0 ", userlist_len);
			return -1;
		}
		if(0 == userlist_len){
			return 0;
		}
		if(M <= 1){
			WARNING_LOG("smooth M[%d] <= 1 nothing need to do", M);
			return 0;
		}
		if(L <= 0){
			WARNING_LOG("smooth L[%d] <= 0 nothing need to do", L);
			return 0;
		}
		if(N <= 0){
			WARNING_LOG("smooth N[%d] <= 0 nothing need to do", N);
			return 0;
		}
		if(L >= M){
			WARNING_LOG("smooth L[%d] >= M[%d] nothing need to do", L, M);
			return 0;
		}

		Song_item_t tmp_list[MAX_USER_LIST_LEN];
		//平滑歌曲
		smooth_dim_t smooth_dim;
		smooth_data_t * smooth_data = (smooth_data_t *) malloc(sizeof(smooth_data_t) * M);
		int lan_count[5];//只统计0-4的5种语言
		Song_brief_t *tmp_song_brief = NULL;
		int valid_num = 0;
		int left_len = userlist_len;
		bsl::hashmap<uint, uint> result_ids;
        result_ids.create(L);
		for(int i = 0; i < N; i++){
			if(left_len <= L){
				WARNING_LOG("smooth over, left len too small:left_len[%d] <= L[%d], smooth times i[%d]", L, M, i);
				return 0;
			}
			//计算M区间内的歌曲
			memset(lan_count, 0, sizeof(int) * 5);
			memset(&smooth_dim, 0, sizeof(smooth_dim_t));
			valid_num = M > left_len ? left_len : M ;
			if(L >= M){
				WARNING_LOG("smooth L[%d] >= valid_num[%d] nothing need to do", L, valid_num);
				continue;
			}
			for(int j = 0; j < valid_num; j++){
				tmp_song_brief = _dict_seeker->get_song_brief(p_userlist[i*M - i*L + j].song_id);
				if(tmp_song_brief == NULL){
					continue;
				}
#ifdef _DEBUG_TIME
				DEBUG_LOG("the smooth_dim: j[%d], pos[%d], songid[%d], lan[%d], year[%d], pitch[%d], tune[%d]",
					j, i*M - i*L + j, p_userlist[i*M - i*L + j].song_id, tmp_song_brief->lang, tmp_song_brief->year, tmp_song_brief->pitch, tmp_song_brief->tune);
#endif
				//语言
				if(tmp_song_brief->lang >= 0 && tmp_song_brief->lang < 5){
					lan_count[tmp_song_brief->lang] ++;
				}
				//年代
				if(tmp_song_brief->year >= 0){
					smooth_dim.year += tmp_song_brief->year * YEAR_RATE;
					smooth_dim.year_num ++;
				}
				//音调
				if(tmp_song_brief->pitch >= 0){
					smooth_dim.pitch += tmp_song_brief->pitch;
					smooth_dim.pitch_num ++;
				}
				//节奏
				if(tmp_song_brief->tune >= 0){
					smooth_dim.tune += tmp_song_brief->tune * TUNE_RATE;
					smooth_dim.tune_num ++;
				}
			}
			//计算各维度的均值
			//语言
			smooth_dim.lan = 0;
			for(int j = 1; j < 5; j++){
				if(lan_count[j] > lan_count[smooth_dim.lan])
					smooth_dim.lan = j;
			}
			//年代
			if(smooth_dim.year_num != 0){
				smooth_dim.year /= smooth_dim.year_num;
			}
			else{
				smooth_dim.year = -1;
			}
			//音调
			if(smooth_dim.pitch_num != 0){
				smooth_dim.pitch /= smooth_dim.pitch_num;
			}
			else{
				smooth_dim.pitch = -1;
			}
			//节奏
			if(smooth_dim.tune_num != 0){
				smooth_dim.tune /= smooth_dim.tune_num;
			}
			else{
				smooth_dim.tune = -1;
			}
#ifdef _DEBUG_TIME
			DEBUG_LOG("the smooth_dim average: lan[%d], year[%d], pitch[%d], tune[%d]",
				smooth_dim.lan, smooth_dim.year, smooth_dim.pitch, smooth_dim.tune);
#endif

			int distance = 0;
			for(int j = 0; j < valid_num; j++){
				distance = 0;
				tmp_song_brief = _dict_seeker->get_song_brief(p_userlist[i*M - i*L + j].song_id);
				smooth_data[j].song_id = p_userlist[i*M - i*L + j].song_id;
				//语言
				if(tmp_song_brief == NULL || tmp_song_brief->lang != smooth_dim.lan){
					distance += UNKNOWN_DISTANCE * g_config.smooth_lan;
				}
				//年代
				if(tmp_song_brief == NULL || tmp_song_brief->year == -1 || smooth_dim.year == -1){
					distance += UNKNOWN_DISTANCE * g_config.smooth_year;
				}
				else{
					int year_dis = smooth_dim.year - tmp_song_brief->year * YEAR_RATE;
					year_dis = (year_dis > 0) ? year_dis : (-1) * year_dis;
					distance +=  year_dis * g_config.smooth_year;
				}
				//音调
				if(tmp_song_brief == NULL || tmp_song_brief->pitch == -1 || smooth_dim.pitch == -1){
					distance += UNKNOWN_DISTANCE * g_config.smooth_pitch;
				}
				else{
					int pitch_dis = smooth_dim.pitch - tmp_song_brief->pitch;
					pitch_dis = (pitch_dis > 0) ? pitch_dis : (-1) * pitch_dis;
					distance +=  pitch_dis * g_config.smooth_pitch;
				}
				//节奏
				if(tmp_song_brief == NULL || tmp_song_brief->tune == -1 || smooth_dim.tune == -1){
					distance += UNKNOWN_DISTANCE * g_config.smooth_tune;
				}
				else{
					int tune_dis = smooth_dim.tune - tmp_song_brief->tune * TUNE_RATE;
					tune_dis = (tune_dis > 0) ? tune_dis : (-1) * tune_dis;
					distance +=  tune_dis * g_config.smooth_tune;
				}
				smooth_data[j].distance = distance;
			}

			//构建大顶堆
#ifdef _DEBUG_TIME
			//堆前输出
			for(int j = 0; j < valid_num; j++){
				DEBUG_LOG("the smooth heap before distance: j[%d], song_id[%d], distance[%d]",
					j, smooth_data[j].song_id, smooth_data[j].distance);
			}
#endif
			std::make_heap(smooth_data, smooth_data + valid_num, smooth_data_cmp);
#ifdef _DEBUG_TIME
			//堆后输出
			for(int j = 0; j < valid_num; j++){
				DEBUG_LOG("the smooth heap over distance: j[%d], song_id[%d], distance[%d]",
					j, smooth_data[j].song_id, smooth_data[j].distance);
			}
#endif
			//平滑后重排列表
			result_ids.clear();
			uint tmp_song_id = 0;
			uint tmp_value = 0;
			for(int j = 0; j < L; j++){
				result_ids.set(smooth_data[0].song_id, 0);
#ifdef _DEBUG_TIME
				DEBUG_LOG("the smooth remove song_id[%d], distance[%d]", smooth_data[0].song_id, smooth_data[0].distance);
#endif
				std::pop_heap(smooth_data, smooth_data + valid_num - j, smooth_data_cmp);
			}
			int valid_smooth_num = 0;
			int valid_unsmooth_num = 0;
			for(int j = 0; j < valid_num ; j++){
				if(result_ids.get(p_userlist[i*M - i*L + j].song_id, &tmp_value) == bsl::HASH_NOEXIST){
                    memcpy(tmp_list + i*M - i*L + valid_smooth_num, &p_userlist[i*M - i*L + j], sizeof(Song_item_t));
                    valid_smooth_num ++;
                }
                else{
                	memcpy(tmp_list + i*M - i*L + valid_num - L + valid_unsmooth_num, &p_userlist[i*M - i*L + j], sizeof(Song_item_t));
                    valid_unsmooth_num ++;
                }
			}

#ifdef _DEBUG_TIME
			//堆后输出
			for(int j = 0; j < valid_num; j++){
				DEBUG_LOG("the list after: j[%d], song_id[%d], weight[%d]",
					j, tmp_list[i*M - i*L + j].song_id, tmp_list[i*M - i*L + j].weight);
			}
#endif
			memcpy(p_userlist + (i*M -i*L), tmp_list + (i*M - i*L), sizeof(Song_item_t) * valid_num);
			left_len -= (valid_num + L);
		}

		memcpy(p_userlist, tmp_list, sizeof(Song_item_t) * userlist_len);
		//标记平滑来源
		for(int j = 0; j < userlist_len; j++){
			p_userlist[j].source |= FLAG_SOURCE;
		}
		result_ids.destroy();
        return SUCCESS;
	}


    int RStrategy::tire_list(Song_item_t *p_userlist, int userlist_len, uint uid, uint baiduid, bool is_login)
	{
		if(NULL == p_userlist){
			WARNING_LOG("p_userlist is NULL");
			return -1;
		}
		if(userlist_len < 0){
			WARNING_LOG("userlist_len[%d] < 0 ", userlist_len);
			return -1;
		}
		if(0 == userlist_len){
			return 0;
		}
#ifdef _DEBUG_TIME
        for(int i =0; i < userlist_len; ++i){
            DEBUG_LOG("tire_list before, pos[%d], song_id[%d], weight[%d], source[%d]", \
                i, p_userlist[i].song_id, p_userlist[i].weight, p_userlist[i].source);
        }
#endif
        int ret = -1;
        //存储结果列表
		Song_item_t* tmp_list = (Song_item_t*)malloc(userlist_len * sizeof(Song_item_t));
        if(NULL == tmp_list){
            WARNING_LOG("malloc tmp_list fail");
            return FAIL;
        }
        //查询疲劳度数据
        std::string str;
        std::map<int, user_cnt_t> user_cnt_map;
        char uint_str[20];
        for(int i = 0; i < userlist_len; ++i){
            snprintf(uint_str, 20, "%d", p_userlist[i].song_id);
            str.append(uint_str);
            if(i != userlist_len - 1){
                str.append(",");
            }
        }
        DEBUG_LOG("tire_list song_set[%s]", str.c_str());
        if(is_login){
            ret = db_get_user_behavior_cnt(uid, str.c_str(), user_cnt_map);
            if(ret < 0){
                WARNING_LOG("db_get_user_behavior_cnt fail");
                free(tmp_list);
                return FAIL;
            }
        }
        else{
            ret = db_get_co_user_behavior_cnt(baiduid, str.c_str(), user_cnt_map);
            if(ret < 0){
                WARNING_LOG("db_get_co_user_behavior_cnt fail");
                free(tmp_list);
                return FAIL;
            }
        }
        //疲劳度处理
        std::map<int, user_cnt_t>::iterator it;
        int begin = 0;
        int end = userlist_len - 1;
        int cnt = 0;
        int timestamp = 0;
        int days = 0;
        time_t now = time((time_t *)NULL);
        for(int i = 0; i < userlist_len; ++i){
            it = user_cnt_map.find(p_userlist[i].song_id);
            if(it != user_cnt_map.end()){
                cnt = it->second.cnt;
                timestamp = it->second.timestamp;
                days = (now - timestamp) / 86400;
                if(cnt >= 1 && days/log2(1 + cnt) < TIRE_DEGREE){
                    memcpy(tmp_list + end, p_userlist + i, sizeof(Song_item_t));
                    --end;
#ifdef _DEBUG_TIME
                    DEBUG_LOG("tired:cnt[%d],timestamp[%d],days[%d],song_id[%d],degree[%.2f],pos[%d]",\
                            cnt, timestamp, days, p_userlist[i].song_id, days/log2(1 + cnt), i);
#endif
                }
                else{
                    memcpy(tmp_list + begin, p_userlist + i, sizeof(Song_item_t));
                    ++begin;
                }
            }
            else{
                memcpy(tmp_list + begin, p_userlist + i, sizeof(Song_item_t));
                ++begin;
            }

        }
        memcpy(p_userlist, tmp_list, userlist_len * sizeof(Song_item_t));
        free(tmp_list);
#ifdef _DEBUG_TIME
        for(int i =0; i < userlist_len; ++i){
            DEBUG_LOG("tire_list after, pos[%d], song_id[%d], weight[%d], source[%d]", \
                i, p_userlist[i].song_id, p_userlist[i].weight, p_userlist[i].source);
        }
#endif
        return SUCCESS;
	}

}

