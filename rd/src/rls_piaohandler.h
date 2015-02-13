/* ========================================================
 *   Copyright (C) 2014 All rights reserved.
 *   
 *   filename : rls_piaohandler.h
 *   author   : Songbin Liu
 *   date     : 2014-02-28
 *   info     : 
 * ======================================================== */

#ifndef RLS_PIAOHANDLER_H
#define RLS_PIAOHANDLER_H

#include "rls_def.h"
#include "rls_dictseeker.h"
#include "idl/rls2.idl.h"
#include "common.h"
#include "rls.h"
#include "macro.h"
#include "rls_struct.h"
#include "rls_uscgetter.h"
#include "mcCache.h"

#ifndef MAX_PIAO_LEN
  #define MAX_PIAO_LEN (200)
#endif

#ifndef DEFAULT_PIAO_LEN
  #define DEFAULT_PIAO_LEN (20)
#endif

namespace rls{
  //Piao and PiaoList are internal classes.
  class Piao{
    public:
      Piao();
      ~Piao();
      Piao& operator=(const Piao& x);
      
    public:
      uint ticket_id;
      uint singer_id;
      int32_t  weight;
      int32_t  source;
  };

  class PiaoList{
    public:
      PiaoList(int n);
      ~PiaoList();


      bool should_add(const Piao& p);
      int pop_add(const Piao& p, uint& singer_id);
      int add_piao(const Piao& p);
      int append_piao(const Piao& p);

      int sort();

      uint32_t get_size();

      bool is_full();

      Piao* get_ticket_list();
      int mcpack_it(char *buf, uint& len);

    protected:
      Piao *tlist;
      uint32_t capacity;     // capacity
      uint32_t size;         // filled
  };


  class PiaoHandler{
    public:
      PiaoHandler();
      ~PiaoHandler();

      int dispatch(const User_worker_buf& ubuf);

    protected:
      int sanitize_req_length(uint32_t *req_len);

      int check_para(const User_worker_buf& ubuf);

      int get_userdata(const User_worker_buf& ubuf,
          r_userdata_t& udata);

      int fill_singers_loved(const r_userdata_t& udata,
          bsl::hashmap<uint, int>& singers);

      int fill_singers_hated(const r_userdata_t& udata,
          bsl::hashmap<uint, int>& singers);



      int fill_singers_related(uint singer_id,
          const bsl::hashmap<uint, int>& loved,
          const bsl::hashmap<uint, int>& hated,
          bsl::hashmap<uint, int>& related);

      int fill_related_tickets(const bsl::hashmap<uint, int>& related,
          bsl::hashmap<uint, int>& filter,
          PiaoList& plist);

      int append_good_tickets(const bsl::hashmap<uint, int>& loved,
          const bsl::hashmap<uint, int>& hated,
          bsl::hashmap<uint, int>& filter,
          PiaoList& plist);

      int gen_match_list(uint singer_id,
          const r_userdata_t& udata,
          PiaoList& plst);
      int get_best_match(const User_worker_buf& ubuf);

      int fill_singers_favored(const r_userdata_t& udata, 
          bsl::hashmap<uint, int>& singers);

      int fill_tickets_favored(const bsl::hashmap<uint, int>& singers,
          bsl::hashmap<uint, int>& filter,
          PiaoList& plist);

      int append_tickets_notbad(
          const bsl::hashmap<uint, int>& singers_hated,
          bsl::hashmap<uint, int>& filter,
          PiaoList& plist);

      int gen_top_n(const r_userdata_t& udata, PiaoList& plist);
      int get_best_n(const User_worker_buf& ubuf);

    private:
      DictSeeker* m_dict_seeker;
      UscGetter* m_usc_getter;

      /* artists of the tickets*/
      bsl::hashmap<uint, int> m_artists_hash;
  };
}



#endif //RLS_PIAOHANDLER_H
