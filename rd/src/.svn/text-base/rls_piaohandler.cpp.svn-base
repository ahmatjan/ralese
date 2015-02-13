/* ========================================================
 *   Copyright (C) 2014 All rights reserved.
 *   
 *   filename : rls_xpiao.cpp
 *   author   : ***
 *   date     : 2014-03-19
 *   info     : 
 * ======================================================== */

#include "mcCache.h"
#include "rls_piaohandler.h"


namespace rls{

  bool piao_cmp(const Piao& a, const Piao& b)
  {
    return a.weight > b.weight;
  }

  /* ------------------ begin of PiaoList ----------*/
  //local variable
  Piao::Piao()
  {
    ticket_id = 0;
    singer_id = 0;
    weight = -1;
    source = -2;
  }

  Piao::~Piao()
  {
  }

  Piao& Piao::operator=(const Piao& x)
  {
    ticket_id = x.ticket_id;
    singer_id = x.singer_id;
    weight = x.weight;
    source = x.source;

    return *this;
  }


  PiaoList::PiaoList(int n)
  {
    if(n<0 || n > 1024*1024*1024)
    {
      FATAL_LOG("The required size of list is out of range[%d]", n);
      tlist = NULL;
      return;
    }

    tlist = new Piao[n];
    if(tlist == NULL)
    {
      FATAL_LOG("Failed to alloc memory for list[%d]", n);
      return;
    }

    capacity = n;
    size = 0;
  }

  PiaoList::~PiaoList()
  {
    if(tlist != NULL)
      delete[] tlist;

    tlist = NULL;
    capacity = 0;
    size = 0;
  }

  uint32_t PiaoList::get_size()
  {
    return size;
  }
  
  bool PiaoList::should_add(const Piao& p)
  {
    return tlist[0].weight < p.weight;
  }

  int PiaoList::pop_add(const Piao& x, uint& singer_id)
  {
    singer_id = tlist[0].singer_id;

    std::pop_heap(tlist, tlist+size, piao_cmp);
    tlist[size-1] = x;
    std::push_heap(tlist, tlist+size, piao_cmp);

    return 0;
  }

  int PiaoList::add_piao(const Piao& p)
  {
    if(size >= capacity)
      return -1;
    tlist[size] = p;
    size += 1;

    std::push_heap(tlist, tlist+size, piao_cmp);
    return 0;
  }

  int PiaoList::append_piao(const Piao& p)
  {
    if(size >= capacity)
      return -1;

    tlist[size] = p;
    size += 1;
    return 0;
  }

  int PiaoList::sort()
  {
    std::sort_heap(tlist, tlist+size, piao_cmp);
    return 0;
  }

  bool PiaoList::is_full()
  {
    return size >= capacity;
  }

  Piao* PiaoList::get_ticket_list()
  {
    return tlist;
  }

  int PiaoList::mcpack_it(char *buf, uint& len)
  {
    int ret;
    uint i;

    bsl::ResourcePool rp;
    mc_pack_t *mcpack = NULL;
    mc_pack_t *mcpack_arr = NULL;
    mc_pack_t *mcpack_obj = NULL;

    if(buf == NULL)
      return -1;

    mcpack = mc_pack_open_w_rp(2, buf, DEFAULT_MCPACK_LEN, &rp);
    if(MC_PACK_PTR_ERR(mcpack) != 0)
    {
      WARNING_LOG("the mcpack of request is invalid, return.");
      return FAIL;
    }

    if((ret = mc_pack_put_int32(mcpack, "status", 0)) != 0)
    {
      WARNING_LOG("put status fail[%d]", ret);
      return FAIL;
    }

    if((ret = mc_pack_put_int32(mcpack, "type", 0)) != 0)
    {
      WARNING_LOG("put status fail[%d]", ret);
      return FAIL;
    }

    mcpack_arr = mc_pack_put_array(mcpack, "list");
    if(MC_PACK_PTR_ERR(mcpack_arr) != 0)
    {
      WARNING_LOG("mcpack put array fail");
      return FAIL;
    }

    for(i=0; i < size; i++)
    {
      mcpack_obj = mc_pack_put_object(mcpack_arr, NULL);
      if(MC_PACK_PTR_ERR(mcpack_obj) != 0)
      {
        WARNING_LOG("mcpack put object fail");
        return FAIL;
      }

      ret = mc_pack_put_int64(mcpack_obj, "ticket_id", tlist[i].ticket_id);
      if(ret != 0)
      {
        WARNING_LOG("mcpack put ticket_id fail");
        return FAIL;
      }

      ret = mc_pack_put_int32(mcpack_obj, "weight", tlist[i].weight);
      if(ret != 0)
      {
        WARNING_LOG("mcpack put ticket weight fail");
        return FAIL;
      }

      ret = mc_pack_put_int32(mcpack_obj, "method", tlist[i].source);
      if(ret != 0)
      {
        WARNING_LOG("mcpack put ticket source fail");
        return FAIL;
      }
      mc_pack_finish(mcpack_obj);
    }

    mc_pack_close(mcpack);

    len = mc_pack_get_size(mcpack);
    if(len < 1)
    {
      WARNING_LOG("get res pack size fail");
      return FAIL;
    }

    return 0;
  }

  /* ------------------ end of PiaoList ----------*/

  PiaoHandler::PiaoHandler()
  {
    m_usc_getter = new UscGetter();
    if(NULL == m_usc_getter)
    {
      FATAL_LOG("create _usc_getter fail");
    }

    m_dict_seeker = new DictSeeker();
    if(NULL == m_dict_seeker)
    {
      FATAL_LOG("create _dict_seeker fail");
    }

    uint i, artist_id;

    m_artists_hash.create(200);
    for(i = 0; i < p_global.max_ticket_list_len; i++)
    {
      artist_id = p_global.ticket_list[i].artist_id;

      m_artists_hash.set(artist_id, 1, 0);
    }

  }

  PiaoHandler::~PiaoHandler()
  {
    if(NULL != m_usc_getter)
      delete m_usc_getter;
    if(NULL != m_dict_seeker)
      delete m_dict_seeker;

    m_artists_hash.destroy();
  }

  int PiaoHandler::get_userdata(const User_worker_buf& ubuf, 
      r_userdata_t& udata)
  {
    uint uid = ubuf.p_cmd->uid();
    if(uid > 0)
    {
      mcc_get_user_data(*m_usc_getter, uid, udata);
      return 0;
    }

    uint baiduid = 0;
    char baiduid_str[MAX_BAIDUID_LEN] = {0};
    snprintf(baiduid_str, MAX_BAIDUID_LEN, "%s", ubuf.p_cmd->baiduid());

    if((int)(strlen(baiduid_str)) != BAIDUID_LEN)
    {
      WARNING_LOG("piao cmd cannot exec without uid or baiduid, uid[%d], baiduid_str[%s]", uid, baiduid_str);
      return -1;
    }

    if(create_baiduid(baiduid_str, baiduid) != 0)
    {
      WARNING_LOG("create baiduid fail");
      return -1;
    }

    mcc_get_co_user_data(baiduid, udata);

    return 0;
  }

  int PiaoHandler::check_para(const User_worker_buf& ubuf)
  {
    if(NULL == ubuf.p_thread_buf || NULL == ubuf.p_cmd )
    {
      WARNING_LOG("p_thread_buf or utag is null");
      return -1;
    }

    if(!ubuf.p_cmd->has_piao())
    {
      WARNING_LOG("unsupport cmd, should be piao");
      return -1;
    }

    const idl::piaocmd& mpiao = ubuf.p_cmd->piao();
    if(!mpiao.has_sub_cmd())
    {
      WARNING_LOG("sub_cmd is missing for piao_cmd");
      return -1;
    }

    switch(mpiao.sub_cmd())
    {
      case 1:
        break;
      case 2:
        if(mpiao.artist_id() < 1)
        {
          WARNING_LOG("artist_id(%u) is illegal (< 1)for piao_cmd", 
              mpiao.artist_id());
          return -1;
        }
        break;
      default:
          WARNING_LOG("unknown sub_cmd(%d) for piao_cmd", 
              mpiao.sub_cmd());
        return -1;
    }

    return 0;
  }

  int PiaoHandler::sanitize_req_length(uint32_t *req_len)
  {
    if(*req_len > MAX_PIAO_LEN)
      *req_len = MAX_PIAO_LEN;

    if(*req_len <= 0)
      *req_len = DEFAULT_PIAO_LEN;
    return 0;
  }

  int PiaoHandler::fill_singers_loved(const r_userdata_t& udata,
      bsl::hashmap<uint, int>& singers)
  {
    int i;
    uint singer_id;

    for(i = 0; i < udata.len_songlove; i++)
    {
      singer_id = m_dict_seeker->get_singer_id(udata.songlove[i].itemid);
      if(singer_id < 1)
        continue;

      singers.set(singer_id, 1, 0);
    }

    return 0;
  }

  int PiaoHandler::fill_singers_hated(const r_userdata_t& udata,
      bsl::hashmap<uint, int>& singers)
  {
    int i;
    uint singer_id;

    for(i = 0; i < udata.len_songhate; i++)
    {
      singer_id = m_dict_seeker->get_singer_id(udata.songhate[i].itemid);
      if(singer_id < 1)
        continue;

      singers.set(singer_id, 1, 0);
    }

    return 0;
  }

  int PiaoHandler::fill_singers_related(uint singer_id,
                                const bsl::hashmap<uint, int>& loved,
                                const bsl::hashmap<uint, int>& hated,
                                bsl::hashmap<uint, int>& related)
  {
    int ret;
    int i, len;
    Singer_item_t *match_list;
    int weight, nouse;
    uint m_id;

    ret = m_dict_seeker->seek_singer_singer(singer_id, &match_list, len);
    if(ret != SUCCESS)
      return -1;

    for(i=0; i<len; i++)
    {
      m_id = match_list[i].singer_id;
      weight = match_list[i].weight;
      if(hated.get(m_id, &nouse) == bsl::HASH_EXIST)
        weight = weight - weight/2;
      else if(loved.get(m_id, &nouse) == bsl::HASH_EXIST)
        weight = weight + weight/5;

      related.set(m_id, weight, 1);
    }

    return 0;
  }

  int PiaoHandler::fill_singers_favored(const r_userdata_t& udata, 
      bsl::hashmap<uint, int>& singers)
  {
    int i, weight, nouse;
    uint singer_id;

    //process singers of red-hearted songs
    // weight = 3 for each song
    for(i = 0; i < udata.len_songlove; i++)
    {
      singer_id = m_dict_seeker->get_singer_id(udata.songlove[i].itemid);

      DEBUG_LOG("omg loved singer_id=%d", singer_id);
      if((singer_id < 1) ||
          (m_artists_hash.get(singer_id, &nouse) != bsl::HASH_EXIST))
        continue;

      if(singers.get(singer_id, &weight) == bsl::HASH_EXIST)
        weight += 3;
      else
        weight = 3;

      DEBUG_LOG("omg loved singer_id=%d", singer_id);
      singers.set(singer_id, weight, 1);
    }

    //process singers of 'collected songs'
    // weight = 2 for each song
    for(i = 0; i < udata.len_songcloud; i++)
    {
      singer_id = m_dict_seeker->get_singer_id(udata.songcloud[i].itemid);

      if((singer_id < 1) ||
          (m_artists_hash.get(singer_id, &nouse) != bsl::HASH_EXIST))
        continue;

      if(singers.get(singer_id, &weight) == bsl::HASH_EXIST)
        weight += 2;
      else
        weight = 2;

      singers.set(singer_id, weight, 1);
    }

    //process singers of 'music-box songs'
    // weight = 1 for each song
    for(i = 0; i< udata.len_action; i++)
    {
      if(udata.action[i].type == (int)DB_BOX_COMPLETE_TYPE || 
          udata.action[i].type == (int)DB_SEARCH_SONG)
      {
        singer_id = m_dict_seeker->get_singer_id(udata.action[i].itemid);

        if((singer_id < 1) ||
            (m_artists_hash.get(singer_id, &nouse) != bsl::HASH_EXIST))
          continue;

        if(singers.get(singer_id, &weight) == bsl::HASH_EXIST)
          weight += 1;
        else
          weight = 1;

        singers.set(singer_id, weight, 1);
      }
    }
    return 0;
  }
  int PiaoHandler::fill_tickets_favored(
                                  const bsl::hashmap<uint, int>& singers,
                                        bsl::hashmap<uint, int>& filter,
                                        PiaoList& plist)
  {
    uint i;
    uint singer_id;
    int weight, nouse;
    Piao tmp;

    for(i = 0; i < p_global.max_ticket_list_len; i ++)
    {
      singer_id = p_global.ticket_list[i].artist_id;

      if(singer_id < 1 ||
          (filter.get(singer_id, &nouse) == bsl::HASH_EXIST))
        continue;

      if(singers.get(singer_id, &weight) == bsl::HASH_NOEXIST)
        continue;

      tmp.singer_id = singer_id;
      tmp.ticket_id = p_global.ticket_list[i].ticket_id;
      tmp.weight = weight;
      tmp.source = 1;

      if(!plist.is_full())
      {
        filter.set(singer_id, 1, 0);
        plist.add_piao(tmp);
      }
      else if(plist.should_add(tmp))
      {
        filter.set(singer_id, 1, 0);
        plist.pop_add(tmp, singer_id);
        filter.erase(singer_id);
      }
    }

    plist.sort();
    return 0;
  }

  int PiaoHandler::append_tickets_notbad(
                          const bsl::hashmap<uint, int>& hated,
                                bsl::hashmap<uint, int>& filter,
                                PiaoList& plist)
  {
    uint i;
    Piao tmp;
    int nouse;

    //1. append tickets according to pv, excluding hated singers
    for(i=0; (i < p_global.max_ticket_list_len) && (!plist.is_full()); i ++)
    {
      tmp.singer_id = p_global.ticket_list[i].artist_id;
      if(filter.get(tmp.singer_id, &nouse) == bsl::HASH_EXIST)
        continue;

      if(hated.get(tmp.singer_id, &nouse) == bsl::HASH_EXIST)
        continue;

      tmp.ticket_id = p_global.ticket_list[i].ticket_id;
      tmp.weight = 1;
      tmp.source = 2;

      plist.append_piao(tmp);
      filter.set(tmp.singer_id, 1, 0);
    }

    //2. append the tickets according to pv
    for(i=0; (i<p_global.max_ticket_list_len) && (! plist.is_full()); i++)
    {
      tmp.singer_id = p_global.ticket_list[i].artist_id;
      if(filter.get(tmp.singer_id, &nouse) == bsl::HASH_EXIST)
        continue;

      tmp.ticket_id = p_global.ticket_list[i].ticket_id;
      tmp.weight = 0;
      tmp.source = 3;

      plist.append_piao(tmp);

      filter.set(tmp.singer_id, 1, 0);
    }

    return 0;
  }

  int PiaoHandler::gen_top_n(const r_userdata_t& udata,
                             PiaoList& plist)
  {
    int ret;
    bsl::hashmap<uint, int> singers_favored;
    bsl::hashmap<uint, int> singers_hated;
    bsl::hashmap<uint, int> filter;

    singers_favored.create(50);
    filter.create(50);

    ret = fill_singers_favored(udata, singers_favored);
    if(ret != 0)
      return -1;

    DEBUG_LOG("omg songs(%d), singers favored:%u", 
        udata.len_songlove, singers_favored.size());

    ret = fill_tickets_favored(singers_favored, filter, plist);
    if(ret != 0)
      return -1;

    DEBUG_LOG("omg tickets favored:%d", plist.get_size());

    if(!plist.is_full())
    {
      singers_hated.create(20);
      ret = fill_singers_hated(udata, singers_hated);
      if(ret != 0)
        return -1;

      ret = append_tickets_notbad(singers_hated, filter, plist);
      if(ret != 0)
        return -1;

      singers_hated.destroy();
    }

    DEBUG_LOG("omg tickets top n:%d", plist.get_size());
    filter.destroy();
    singers_favored.destroy();
    return 0;
  }

  int PiaoHandler::get_best_n(const User_worker_buf& ubuf)
  {
    int ret;
    const idl::piaocmd& mpiao = ubuf.p_cmd->piao();
    uint32_t request_len = mpiao.len();
    r_userdata_t user_data;

    sanitize_req_length(&request_len);
    if(get_userdata(ubuf, user_data) != 0)
    {
      WARNING_LOG("get userdata failed");
      return -1;
    }

    PiaoList plst((int)request_len);
    ret = gen_top_n(user_data, plst);
    if(ret != 0)
      return -1;

    uint32_t res_pack_len;
    char pack_buf[DEFAULT_MCPACK_LEN];
    nshead_t head;

    ret = plst.mcpack_it(pack_buf, res_pack_len);
    if(ret != 0)
      return -1;

    head.body_len = res_pack_len;
    strncpy(head.provider, PROJECT_NAME, 8);
    head.provider[7] = 0;
    head.log_id = ubuf.p_thread_buf->head.log_id;
    ret = nshead_write(ubuf.p_thread_buf->fd, &head, 
        (void*)pack_buf, g_config.wtimeout * 1000);
    if (0 != ret){
      WARNING_LOG("send response to ui error[errno:%d]", ret);
      return FAIL;
    }

    return SUCCESS;
  }

  int PiaoHandler::fill_related_tickets(
                                 const bsl::hashmap<uint, int>& related,
                                       bsl::hashmap<uint, int>& filter,
                                       PiaoList& plist)
  {
    uint i, singer_id;
    int weight, nouse;
    Piao tmp;

    for(i = 0; i < p_global.max_ticket_list_len; i++)
    {
      singer_id = p_global.ticket_list[i].artist_id;
      if(singer_id < 1 ||
          (filter.get(singer_id, &nouse) == bsl::HASH_EXIST))
        continue;

      if(related.get(singer_id, &weight) == bsl::HASH_NOEXIST)
        continue;

      tmp.singer_id = singer_id;
      tmp.ticket_id = p_global.ticket_list[i].ticket_id;
      tmp.weight = weight;
      tmp.source = 1;

      if(!plist.is_full())
      {
        filter.set(singer_id, 1, 0);
        plist.add_piao(tmp);
      }
      else if(plist.should_add(tmp))
      {
        filter.set(singer_id, 1, 0);
        plist.pop_add(tmp, singer_id);
        filter.erase(singer_id);
      }
      
    }

    plist.sort();

    return 0;
  }

  int PiaoHandler::append_good_tickets(
                                 const bsl::hashmap<uint, int>& loved,
                                 const bsl::hashmap<uint, int>& hated,
                                 bsl::hashmap<uint, int>& filter,
                                 PiaoList& plist)
  {
    uint i;
    Piao tmp;
    int nouse;

    //1. append the tickets of loved singers first
    for(i=0; (i<p_global.max_ticket_list_len) && (! plist.is_full()); i++)
    {
      tmp.singer_id = p_global.ticket_list[i].artist_id;
      if(filter.get(tmp.singer_id, &nouse) == bsl::HASH_EXIST)
        continue;

      if(loved.get(tmp.singer_id, &nouse) == bsl::HASH_NOEXIST)
        continue;

      tmp.ticket_id = p_global.ticket_list[i].ticket_id;
      tmp.weight = 1;
      tmp.source = 2;

      plist.append_piao(tmp);

      filter.set(tmp.singer_id, 1, 0);
    }

    //2. append the rest tickets excluding hated singers' secondly
    for(i=0; (i<p_global.max_ticket_list_len) && (! plist.is_full()); i++)
    {
      tmp.singer_id = p_global.ticket_list[i].artist_id;
      if(filter.get(tmp.singer_id, &nouse) == bsl::HASH_EXIST)
        continue;

      if(hated.get(tmp.singer_id, &nouse) == bsl::HASH_EXIST)
        continue;

      tmp.ticket_id = p_global.ticket_list[i].ticket_id;
      tmp.weight = 0;
      tmp.source = 3;

      plist.append_piao(tmp);

      filter.set(tmp.singer_id, 1, 0);
    }

    //3. append the rest tickets according to pv thirdly
    for(i=0; (i<p_global.max_ticket_list_len) && (! plist.is_full()); i++)
    {
      tmp.singer_id = p_global.ticket_list[i].artist_id;
      if(filter.get(tmp.singer_id, &nouse) == bsl::HASH_EXIST)
        continue;

      tmp.ticket_id = p_global.ticket_list[i].ticket_id;
      tmp.weight = 0;
      tmp.source = 4;

      plist.append_piao(tmp);

      filter.set(tmp.singer_id, 1, 0);
    }
    return 0;
  }
                                      
  int PiaoHandler::gen_match_list(uint singer_id,
                                      const r_userdata_t& udata,
                                      PiaoList& plist)
  {
    int ret;

    bsl::hashmap<uint, int> singers_related;
    bsl::hashmap<uint, int> singers_loved;
    bsl::hashmap<uint, int> singers_hated;
    bsl::hashmap<uint, int> filter;

    singers_loved.create(20);
    singers_hated.create(20);
    singers_related.create(100);
    filter.create(20);

    ret = fill_singers_loved(udata, singers_loved);
    if(ret != 0)
      return -1;

    ret = fill_singers_hated(udata, singers_hated);
    if(ret != 0)
      return -1;


    DEBUG_LOG("singers_loved:%u, singers_hated:%u",
        (uint)singers_loved.size(), (uint)singers_hated.size());

    ret = fill_singers_related(singer_id, singers_loved, singers_hated, 
        singers_related);
    if(ret != 0)
      return -1;

    filter.set(singer_id, 1, 0); /* filte the tickets of this singer */
    fill_related_tickets(singers_related, filter, plist);

    if(!plist.is_full())
    {
      append_good_tickets(singers_loved, singers_hated, filter, plist);
    }

    filter.destroy();
    singers_related.destroy();
    singers_loved.destroy();
    singers_hated.destroy();

    DEBUG_LOG("tickets_len = %u", plist.get_size());
    return 0;

  }
  
  int PiaoHandler::get_best_match(const User_worker_buf& ubuf)
  {
    int ret;
    const idl::piaocmd& mpiao = ubuf.p_cmd->piao();
    uint32_t request_len = mpiao.len();
    uint singer_id = mpiao.artist_id();
    r_userdata_t user_data;

    sanitize_req_length(&request_len);
    if(get_userdata(ubuf, user_data) != 0)
    {
      WARNING_LOG("get userdata failed");
      return -1;
    }

    //uint32_t tickets_len;
    PiaoList plst((int)request_len);
    if(plst.get_ticket_list() == NULL)
      return -1;

    ret = gen_match_list(singer_id, user_data, plst);
    if(ret != 0)
      return -1;

    //pack and send out
    uint32_t res_pack_len;
    char pack_buf[DEFAULT_MCPACK_LEN];
    nshead_t head;

    ret = plst.mcpack_it(pack_buf, res_pack_len);
    //ret = pack_list(plst, pack_buf, &res_pack_len);
    if(ret != 0)
      return -2;

    head.body_len = res_pack_len;
    strncpy(head.provider, PROJECT_NAME, 8);
    head.provider[7] = 0;
    head.log_id = ubuf.p_thread_buf->head.log_id;
    ret = nshead_write(ubuf.p_thread_buf->fd, &head, 
                       (void*)pack_buf, g_config.wtimeout * 1000);
    if (0 != ret){
      WARNING_LOG("send response to ui error[errno:%d]", ret);
      return FAIL;
    }

    return SUCCESS;
  }

  //TODO: use cache
  int PiaoHandler::dispatch(const User_worker_buf& ubuf)
  {
    DEBUG_LOG("begin to handle piao cmd...");
    if(check_para(ubuf) != 0)
      return FAIL;

    int ret;
    const idl::piaocmd& mpiao = ubuf.p_cmd->piao();

    switch (mpiao.sub_cmd())
    {
      case 1:
        ret = get_best_n(ubuf);
        break;
      case 2:
        ret = get_best_match(ubuf);
        break;
      default:
        WARNING_LOG("piao sub_cmd([%d]) is illegal", mpiao.sub_cmd()); 
        ret = -1;
    }

    DEBUG_LOG("end of handling piao cmd...");
    return ret;
  }
}
