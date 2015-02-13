#ifndef IDL_GENERATED_FILE_RLS2_IDL_H_
#define IDL_GENERATED_FILE_RLS2_IDL_H_
#include "cxx/runtime.h"
namespace idl {
class action;
class playercmd;
class findcmd;
class mgrcmd;
class cntcmd;
class listcmd;
class ticketcmd;
class piaocmd;
class chlistcmd;
class playlistcmd;
class playactioncmd;
class coldstartreqcmd;
class coldstartsingerlistcmd;
class newusercmd;
class usertagscmd;
class cmd;
class action : public ::idl::IDLObject , public ::idl::McpackBean {
public:
static action* create(bsl::mempool* pool);
static void destroy(action* v);
explicit action(bsl::mempool* pool);
action(const action& v);
~action();
action& operator=(const action& v);
void clear();
void check() const;
void detach();
action& assign(const action& v);
// @@uint32_t itemid;
inline bool has_itemid() const;
inline uint32_t itemid() const;
inline action& set_itemid(uint32_t v);
// @@int32_t action_no;
inline bool has_action_no() const;
inline int32_t action_no() const;
inline action& set_action_no(int32_t v);
inline ::idl::Unknown* mutable_unknown();
inline const ::idl::Unknown& unknown() const;
// deprecated.use 'mutable_unknown' instead.
inline ::idl::Unknown& unknown();
// deprecated.use 'unknown().size()' instead.
inline size_t unknown_size() const;
//============================================================
// mcpack2 load/save.
void load(const mc_pack_t* pack);
void LoadWithoutCheck(const mc_pack_t* pack);
//for compatiblity.return 0 when it accepts item,else return -1
int load(const mc_pack_item_t& item);
size_t save(mc_pack_t* pack) const;
public:
bsl::mempool* _pool;
 uint32_t _m_itemid;
 int32_t _m_action_no;
mutable ::idl::Unknown _unknown;
char _flag[1];
}; // class action
class playercmd : public ::idl::IDLObject , public ::idl::McpackBean {
public:
static playercmd* create(bsl::mempool* pool);
static void destroy(playercmd* v);
explicit playercmd(bsl::mempool* pool);
playercmd(const playercmd& v);
~playercmd();
playercmd& operator=(const playercmd& v);
void clear();
void check() const;
void detach();
playercmd& assign(const playercmd& v);
// @@int32_t needdata;
inline bool has_needdata() const;
inline int32_t needdata() const;
inline playercmd& set_needdata(int32_t v);
// @@action titles=array(0);
inline bool has_titles() const;
inline const ::idl::vector< ::idl::action >& titles() const;
inline ::idl::vector< ::idl::action >* mutable_titles();
// deprecated.use 'mutable_titles' instead.
inline ::idl::vector< ::idl::action >* m_titles();
// deprecated.use 'titles().size()' instead.
inline size_t titles_size() const;
inline const ::idl::action& titles(size_t i0) const;
inline ::idl::action* mutable_titles(size_t i0);
// deprecated.use 'mutable_titles' instead.
inline ::idl::action* m_titles(size_t i0);
inline ::idl::Unknown* mutable_unknown();
inline const ::idl::Unknown& unknown() const;
// deprecated.use 'mutable_unknown' instead.
inline ::idl::Unknown& unknown();
// deprecated.use 'unknown().size()' instead.
inline size_t unknown_size() const;
//============================================================
// mcpack2 load/save.
void load(const mc_pack_t* pack);
void LoadWithoutCheck(const mc_pack_t* pack);
//for compatiblity.return 0 when it accepts item,else return -1
int load(const mc_pack_item_t& item);
size_t save(mc_pack_t* pack) const;
public:
bsl::mempool* _pool;
 int32_t _m_needdata;
 ::idl::vector< ::idl::action > _m_titles;
mutable ::idl::Unknown _unknown;
char _flag[1];
}; // class playercmd
class findcmd : public ::idl::IDLObject , public ::idl::McpackBean {
public:
static findcmd* create(bsl::mempool* pool);
static void destroy(findcmd* v);
explicit findcmd(bsl::mempool* pool);
findcmd(const findcmd& v);
~findcmd();
findcmd& operator=(const findcmd& v);
void clear();
void check() const;
void detach();
findcmd& assign(const findcmd& v);
// @@int32_t category;
inline bool has_category() const;
inline int32_t category() const;
inline findcmd& set_category(int32_t v);
// @@string keyword;
inline bool has_keyword() const;
inline const char* keyword(unsigned int* size=0) const;
inline findcmd& set_keyword(const char* s,ssize_t size=-1);
inline findcmd& set_ptr_keyword(const char* s,ssize_t size=-1);
inline ::idl::Unknown* mutable_unknown();
inline const ::idl::Unknown& unknown() const;
// deprecated.use 'mutable_unknown' instead.
inline ::idl::Unknown& unknown();
// deprecated.use 'unknown().size()' instead.
inline size_t unknown_size() const;
//============================================================
// mcpack2 load/save.
void load(const mc_pack_t* pack);
void LoadWithoutCheck(const mc_pack_t* pack);
//for compatiblity.return 0 when it accepts item,else return -1
int load(const mc_pack_item_t& item);
size_t save(mc_pack_t* pack) const;
public:
bsl::mempool* _pool;
 int32_t _m_category;
 ::idl::string _m_keyword;
mutable ::idl::Unknown _unknown;
char _flag[1];
}; // class findcmd
class mgrcmd : public ::idl::IDLObject , public ::idl::McpackBean {
public:
static mgrcmd* create(bsl::mempool* pool);
static void destroy(mgrcmd* v);
explicit mgrcmd(bsl::mempool* pool);
mgrcmd(const mgrcmd& v);
~mgrcmd();
mgrcmd& operator=(const mgrcmd& v);
void clear();
void check() const;
void detach();
mgrcmd& assign(const mgrcmd& v);
// @@int32_t action;
inline bool has_action() const;
inline int32_t action() const;
inline mgrcmd& set_action(int32_t v);
// @@int32_t category;
inline bool has_category() const;
inline int32_t category() const;
inline mgrcmd& set_category(int32_t v);
// @@uint32_t itemid;
inline bool has_itemid() const;
inline uint32_t itemid() const;
inline mgrcmd& set_itemid(uint32_t v);
inline ::idl::Unknown* mutable_unknown();
inline const ::idl::Unknown& unknown() const;
// deprecated.use 'mutable_unknown' instead.
inline ::idl::Unknown& unknown();
// deprecated.use 'unknown().size()' instead.
inline size_t unknown_size() const;
//============================================================
// mcpack2 load/save.
void load(const mc_pack_t* pack);
void LoadWithoutCheck(const mc_pack_t* pack);
//for compatiblity.return 0 when it accepts item,else return -1
int load(const mc_pack_item_t& item);
size_t save(mc_pack_t* pack) const;
public:
bsl::mempool* _pool;
 int32_t _m_action;
 int32_t _m_category;
 uint32_t _m_itemid;
mutable ::idl::Unknown _unknown;
char _flag[1];
}; // class mgrcmd
class cntcmd : public ::idl::IDLObject , public ::idl::McpackBean {
public:
static cntcmd* create(bsl::mempool* pool);
static void destroy(cntcmd* v);
explicit cntcmd(bsl::mempool* pool);
cntcmd(const cntcmd& v);
~cntcmd();
cntcmd& operator=(const cntcmd& v);
void clear();
void check() const;
void detach();
cntcmd& assign(const cntcmd& v);
// @@int32_t src;
inline bool has_src() const;
inline int32_t src() const;
inline cntcmd& set_src(int32_t v);
inline ::idl::Unknown* mutable_unknown();
inline const ::idl::Unknown& unknown() const;
// deprecated.use 'mutable_unknown' instead.
inline ::idl::Unknown& unknown();
// deprecated.use 'unknown().size()' instead.
inline size_t unknown_size() const;
//============================================================
// mcpack2 load/save.
void load(const mc_pack_t* pack);
void LoadWithoutCheck(const mc_pack_t* pack);
//for compatiblity.return 0 when it accepts item,else return -1
int load(const mc_pack_item_t& item);
size_t save(mc_pack_t* pack) const;
public:
bsl::mempool* _pool;
 int32_t _m_src;
mutable ::idl::Unknown _unknown;
char _flag[1];
}; // class cntcmd
class listcmd : public ::idl::IDLObject , public ::idl::McpackBean {
public:
static listcmd* create(bsl::mempool* pool);
static void destroy(listcmd* v);
explicit listcmd(bsl::mempool* pool);
listcmd(const listcmd& v);
~listcmd();
listcmd& operator=(const listcmd& v);
void clear();
void check() const;
void detach();
listcmd& assign(const listcmd& v);
// @@int32_t type;
inline bool has_type() const;
inline int32_t type() const;
inline listcmd& set_type(int32_t v);
// @@int32_t page_len;
inline bool has_page_len() const;
inline int32_t page_len() const;
inline listcmd& set_page_len(int32_t v);
// @@int32_t page_no;
inline bool has_page_no() const;
inline int32_t page_no() const;
inline listcmd& set_page_no(int32_t v);
// @@int32_t src;
inline bool has_src() const;
inline int32_t src() const;
inline listcmd& set_src(int32_t v);
inline ::idl::Unknown* mutable_unknown();
inline const ::idl::Unknown& unknown() const;
// deprecated.use 'mutable_unknown' instead.
inline ::idl::Unknown& unknown();
// deprecated.use 'unknown().size()' instead.
inline size_t unknown_size() const;
//============================================================
// mcpack2 load/save.
void load(const mc_pack_t* pack);
void LoadWithoutCheck(const mc_pack_t* pack);
//for compatiblity.return 0 when it accepts item,else return -1
int load(const mc_pack_item_t& item);
size_t save(mc_pack_t* pack) const;
public:
bsl::mempool* _pool;
 int32_t _m_type;
 int32_t _m_page_len;
 int32_t _m_page_no;
 int32_t _m_src;
mutable ::idl::Unknown _unknown;
char _flag[1];
}; // class listcmd
class ticketcmd : public ::idl::IDLObject , public ::idl::McpackBean {
public:
static ticketcmd* create(bsl::mempool* pool);
static void destroy(ticketcmd* v);
explicit ticketcmd(bsl::mempool* pool);
ticketcmd(const ticketcmd& v);
~ticketcmd();
ticketcmd& operator=(const ticketcmd& v);
void clear();
void check() const;
void detach();
ticketcmd& assign(const ticketcmd& v);
// @@int32_t len;
inline bool has_len() const;
inline int32_t len() const;
inline ticketcmd& set_len(int32_t v);
inline ::idl::Unknown* mutable_unknown();
inline const ::idl::Unknown& unknown() const;
// deprecated.use 'mutable_unknown' instead.
inline ::idl::Unknown& unknown();
// deprecated.use 'unknown().size()' instead.
inline size_t unknown_size() const;
//============================================================
// mcpack2 load/save.
void load(const mc_pack_t* pack);
void LoadWithoutCheck(const mc_pack_t* pack);
//for compatiblity.return 0 when it accepts item,else return -1
int load(const mc_pack_item_t& item);
size_t save(mc_pack_t* pack) const;
public:
bsl::mempool* _pool;
 int32_t _m_len;
mutable ::idl::Unknown _unknown;
char _flag[1];
}; // class ticketcmd
class piaocmd : public ::idl::IDLObject , public ::idl::McpackBean {
public:
static piaocmd* create(bsl::mempool* pool);
static void destroy(piaocmd* v);
explicit piaocmd(bsl::mempool* pool);
piaocmd(const piaocmd& v);
~piaocmd();
piaocmd& operator=(const piaocmd& v);
void clear();
void check() const;
void detach();
piaocmd& assign(const piaocmd& v);
// @@uint32_t sub_cmd;
inline bool has_sub_cmd() const;
inline uint32_t sub_cmd() const;
inline piaocmd& set_sub_cmd(uint32_t v);
// @@int32_t len=optional();
inline bool has_len() const;
inline int32_t len() const;
inline piaocmd& set_len(int32_t v);
// @@uint32_t artist_id=optional();
inline bool has_artist_id() const;
inline uint32_t artist_id() const;
inline piaocmd& set_artist_id(uint32_t v);
// @@uint32_t top_len=optional();
inline bool has_top_len() const;
inline uint32_t top_len() const;
inline piaocmd& set_top_len(uint32_t v);
// @@uint32_t page_size=optional();
inline bool has_page_size() const;
inline uint32_t page_size() const;
inline piaocmd& set_page_size(uint32_t v);
// @@int32_t page_number=optional();
inline bool has_page_number() const;
inline int32_t page_number() const;
inline piaocmd& set_page_number(int32_t v);
inline ::idl::Unknown* mutable_unknown();
inline const ::idl::Unknown& unknown() const;
// deprecated.use 'mutable_unknown' instead.
inline ::idl::Unknown& unknown();
// deprecated.use 'unknown().size()' instead.
inline size_t unknown_size() const;
//============================================================
// mcpack2 load/save.
void load(const mc_pack_t* pack);
void LoadWithoutCheck(const mc_pack_t* pack);
//for compatiblity.return 0 when it accepts item,else return -1
int load(const mc_pack_item_t& item);
size_t save(mc_pack_t* pack) const;
public:
bsl::mempool* _pool;
 uint32_t _m_sub_cmd;
 int32_t _m_len;
 uint32_t _m_artist_id;
 uint32_t _m_top_len;
 uint32_t _m_page_size;
 int32_t _m_page_number;
mutable ::idl::Unknown _unknown;
char _flag[1];
}; // class piaocmd
class chlistcmd : public ::idl::IDLObject , public ::idl::McpackBean {
public:
static chlistcmd* create(bsl::mempool* pool);
static void destroy(chlistcmd* v);
explicit chlistcmd(bsl::mempool* pool);
chlistcmd(const chlistcmd& v);
~chlistcmd();
chlistcmd& operator=(const chlistcmd& v);
void clear();
void check() const;
void detach();
chlistcmd& assign(const chlistcmd& v);
// @@string cate_name;
inline bool has_cate_name() const;
inline const char* cate_name(unsigned int* size=0) const;
inline chlistcmd& set_cate_name(const char* s,ssize_t size=-1);
inline chlistcmd& set_ptr_cate_name(const char* s,ssize_t size=-1);
inline ::idl::Unknown* mutable_unknown();
inline const ::idl::Unknown& unknown() const;
// deprecated.use 'mutable_unknown' instead.
inline ::idl::Unknown& unknown();
// deprecated.use 'unknown().size()' instead.
inline size_t unknown_size() const;
//============================================================
// mcpack2 load/save.
void load(const mc_pack_t* pack);
void LoadWithoutCheck(const mc_pack_t* pack);
//for compatiblity.return 0 when it accepts item,else return -1
int load(const mc_pack_item_t& item);
size_t save(mc_pack_t* pack) const;
public:
bsl::mempool* _pool;
 ::idl::string _m_cate_name;
mutable ::idl::Unknown _unknown;
char _flag[1];
}; // class chlistcmd
class playlistcmd : public ::idl::IDLObject , public ::idl::McpackBean {
public:
static playlistcmd* create(bsl::mempool* pool);
static void destroy(playlistcmd* v);
explicit playlistcmd(bsl::mempool* pool);
playlistcmd(const playlistcmd& v);
~playlistcmd();
playlistcmd& operator=(const playlistcmd& v);
void clear();
void check() const;
void detach();
playlistcmd& assign(const playlistcmd& v);
// @@string ch_name;
inline bool has_ch_name() const;
inline const char* ch_name(unsigned int* size=0) const;
inline playlistcmd& set_ch_name(const char* s,ssize_t size=-1);
inline playlistcmd& set_ptr_ch_name(const char* s,ssize_t size=-1);
inline ::idl::Unknown* mutable_unknown();
inline const ::idl::Unknown& unknown() const;
// deprecated.use 'mutable_unknown' instead.
inline ::idl::Unknown& unknown();
// deprecated.use 'unknown().size()' instead.
inline size_t unknown_size() const;
//============================================================
// mcpack2 load/save.
void load(const mc_pack_t* pack);
void LoadWithoutCheck(const mc_pack_t* pack);
//for compatiblity.return 0 when it accepts item,else return -1
int load(const mc_pack_item_t& item);
size_t save(mc_pack_t* pack) const;
public:
bsl::mempool* _pool;
 ::idl::string _m_ch_name;
mutable ::idl::Unknown _unknown;
char _flag[1];
}; // class playlistcmd
class playactioncmd : public ::idl::IDLObject , public ::idl::McpackBean {
public:
static playactioncmd* create(bsl::mempool* pool);
static void destroy(playactioncmd* v);
explicit playactioncmd(bsl::mempool* pool);
playactioncmd(const playactioncmd& v);
~playactioncmd();
playactioncmd& operator=(const playactioncmd& v);
void clear();
void check() const;
void detach();
playactioncmd& assign(const playactioncmd& v);
// @@string ch_name;
inline bool has_ch_name() const;
inline const char* ch_name(unsigned int* size=0) const;
inline playactioncmd& set_ch_name(const char* s,ssize_t size=-1);
inline playactioncmd& set_ptr_ch_name(const char* s,ssize_t size=-1);
// @@uint64_t item_id;
inline bool has_item_id() const;
inline uint64_t item_id() const;
inline playactioncmd& set_item_id(uint64_t v);
// @@string pack_item_ids;
inline bool has_pack_item_ids() const;
inline const char* pack_item_ids(unsigned int* size=0) const;
inline playactioncmd& set_pack_item_ids(const char* s,ssize_t size=-1);
inline playactioncmd& set_ptr_pack_item_ids(const char* s,ssize_t size=-1);
// @@int32_t action_no;
inline bool has_action_no() const;
inline int32_t action_no() const;
inline playactioncmd& set_action_no(int32_t v);
inline ::idl::Unknown* mutable_unknown();
inline const ::idl::Unknown& unknown() const;
// deprecated.use 'mutable_unknown' instead.
inline ::idl::Unknown& unknown();
// deprecated.use 'unknown().size()' instead.
inline size_t unknown_size() const;
//============================================================
// mcpack2 load/save.
void load(const mc_pack_t* pack);
void LoadWithoutCheck(const mc_pack_t* pack);
//for compatiblity.return 0 when it accepts item,else return -1
int load(const mc_pack_item_t& item);
size_t save(mc_pack_t* pack) const;
public:
bsl::mempool* _pool;
 ::idl::string _m_ch_name;
 uint64_t _m_item_id;
 ::idl::string _m_pack_item_ids;
 int32_t _m_action_no;
mutable ::idl::Unknown _unknown;
char _flag[1];
}; // class playactioncmd
class coldstartreqcmd : public ::idl::IDLObject , public ::idl::McpackBean {
public:
static coldstartreqcmd* create(bsl::mempool* pool);
static void destroy(coldstartreqcmd* v);
explicit coldstartreqcmd(bsl::mempool* pool);
coldstartreqcmd(const coldstartreqcmd& v);
~coldstartreqcmd();
coldstartreqcmd& operator=(const coldstartreqcmd& v);
void clear();
void check() const;
void detach();
coldstartreqcmd& assign(const coldstartreqcmd& v);
// @@string ch_name;
inline bool has_ch_name() const;
inline const char* ch_name(unsigned int* size=0) const;
inline coldstartreqcmd& set_ch_name(const char* s,ssize_t size=-1);
inline coldstartreqcmd& set_ptr_ch_name(const char* s,ssize_t size=-1);
// @@string lovesinger;
inline bool has_lovesinger() const;
inline const char* lovesinger(unsigned int* size=0) const;
inline coldstartreqcmd& set_lovesinger(const char* s,ssize_t size=-1);
inline coldstartreqcmd& set_ptr_lovesinger(const char* s,ssize_t size=-1);
inline ::idl::Unknown* mutable_unknown();
inline const ::idl::Unknown& unknown() const;
// deprecated.use 'mutable_unknown' instead.
inline ::idl::Unknown& unknown();
// deprecated.use 'unknown().size()' instead.
inline size_t unknown_size() const;
//============================================================
// mcpack2 load/save.
void load(const mc_pack_t* pack);
void LoadWithoutCheck(const mc_pack_t* pack);
//for compatiblity.return 0 when it accepts item,else return -1
int load(const mc_pack_item_t& item);
size_t save(mc_pack_t* pack) const;
public:
bsl::mempool* _pool;
 ::idl::string _m_ch_name;
 ::idl::string _m_lovesinger;
mutable ::idl::Unknown _unknown;
char _flag[1];
}; // class coldstartreqcmd
class coldstartsingerlistcmd : public ::idl::IDLObject , public ::idl::McpackBean {
public:
static coldstartsingerlistcmd* create(bsl::mempool* pool);
static void destroy(coldstartsingerlistcmd* v);
explicit coldstartsingerlistcmd(bsl::mempool* pool);
coldstartsingerlistcmd(const coldstartsingerlistcmd& v);
~coldstartsingerlistcmd();
coldstartsingerlistcmd& operator=(const coldstartsingerlistcmd& v);
void clear();
void check() const;
void detach();
coldstartsingerlistcmd& assign(const coldstartsingerlistcmd& v);
// @@string ch_name;
inline bool has_ch_name() const;
inline const char* ch_name(unsigned int* size=0) const;
inline coldstartsingerlistcmd& set_ch_name(const char* s,ssize_t size=-1);
inline coldstartsingerlistcmd& set_ptr_ch_name(const char* s,ssize_t size=-1);
inline ::idl::Unknown* mutable_unknown();
inline const ::idl::Unknown& unknown() const;
// deprecated.use 'mutable_unknown' instead.
inline ::idl::Unknown& unknown();
// deprecated.use 'unknown().size()' instead.
inline size_t unknown_size() const;
//============================================================
// mcpack2 load/save.
void load(const mc_pack_t* pack);
void LoadWithoutCheck(const mc_pack_t* pack);
//for compatiblity.return 0 when it accepts item,else return -1
int load(const mc_pack_item_t& item);
size_t save(mc_pack_t* pack) const;
public:
bsl::mempool* _pool;
 ::idl::string _m_ch_name;
mutable ::idl::Unknown _unknown;
char _flag[1];
}; // class coldstartsingerlistcmd
class newusercmd : public ::idl::IDLObject , public ::idl::McpackBean {
public:
static newusercmd* create(bsl::mempool* pool);
static void destroy(newusercmd* v);
explicit newusercmd(bsl::mempool* pool);
newusercmd(const newusercmd& v);
~newusercmd();
newusercmd& operator=(const newusercmd& v);
void clear();
void check() const;
void detach();
newusercmd& assign(const newusercmd& v);
// @@string ch_name;
inline bool has_ch_name() const;
inline const char* ch_name(unsigned int* size=0) const;
inline newusercmd& set_ch_name(const char* s,ssize_t size=-1);
inline newusercmd& set_ptr_ch_name(const char* s,ssize_t size=-1);
inline ::idl::Unknown* mutable_unknown();
inline const ::idl::Unknown& unknown() const;
// deprecated.use 'mutable_unknown' instead.
inline ::idl::Unknown& unknown();
// deprecated.use 'unknown().size()' instead.
inline size_t unknown_size() const;
//============================================================
// mcpack2 load/save.
void load(const mc_pack_t* pack);
void LoadWithoutCheck(const mc_pack_t* pack);
//for compatiblity.return 0 when it accepts item,else return -1
int load(const mc_pack_item_t& item);
size_t save(mc_pack_t* pack) const;
public:
bsl::mempool* _pool;
 ::idl::string _m_ch_name;
mutable ::idl::Unknown _unknown;
char _flag[1];
}; // class newusercmd
class usertagscmd : public ::idl::IDLObject , public ::idl::McpackBean {
public:
static usertagscmd* create(bsl::mempool* pool);
static void destroy(usertagscmd* v);
explicit usertagscmd(bsl::mempool* pool);
usertagscmd(const usertagscmd& v);
~usertagscmd();
usertagscmd& operator=(const usertagscmd& v);
void clear();
void check() const;
void detach();
usertagscmd& assign(const usertagscmd& v);
// @@uint32_t src;
inline bool has_src() const;
inline uint32_t src() const;
inline usertagscmd& set_src(uint32_t v);
inline ::idl::Unknown* mutable_unknown();
inline const ::idl::Unknown& unknown() const;
// deprecated.use 'mutable_unknown' instead.
inline ::idl::Unknown& unknown();
// deprecated.use 'unknown().size()' instead.
inline size_t unknown_size() const;
//============================================================
// mcpack2 load/save.
void load(const mc_pack_t* pack);
void LoadWithoutCheck(const mc_pack_t* pack);
//for compatiblity.return 0 when it accepts item,else return -1
int load(const mc_pack_item_t& item);
size_t save(mc_pack_t* pack) const;
public:
bsl::mempool* _pool;
 uint32_t _m_src;
mutable ::idl::Unknown _unknown;
char _flag[1];
}; // class usertagscmd
class cmd : public ::idl::IDLObject , public ::idl::McpackBean {
public:
static cmd* create(bsl::mempool* pool);
static void destroy(cmd* v);
explicit cmd(bsl::mempool* pool);
cmd(const cmd& v);
~cmd();
cmd& operator=(const cmd& v);
void clear();
void check() const;
void detach();
cmd& assign(const cmd& v);
// @@int32_t rf=default(-1);
static const int32_t k_rf;
inline bool has_rf() const;
inline int32_t rf() const;
inline cmd& set_rf(int32_t v);
// @@string username=default("");
static const ::idl::string k_username;
inline bool has_username() const;
inline const char* username(unsigned int* size=0) const;
inline cmd& set_username(const char* s,ssize_t size=-1);
inline cmd& set_ptr_username(const char* s,ssize_t size=-1);
// @@uint32_t uid=default(0);
static const uint32_t k_uid;
inline bool has_uid() const;
inline uint32_t uid() const;
inline cmd& set_uid(uint32_t v);
// @@string baiduid=default("");
static const ::idl::string k_baiduid;
inline bool has_baiduid() const;
inline const char* baiduid(unsigned int* size=0) const;
inline cmd& set_baiduid(const char* s,ssize_t size=-1);
inline cmd& set_ptr_baiduid(const char* s,ssize_t size=-1);
// @@playercmd pc=optional();
inline bool has_pc() const;
inline const ::idl::playercmd& pc() const;
inline ::idl::playercmd* mutable_pc();
// deprecated.use 'mutable_pc()' instead.
inline ::idl::playercmd* m_pc();
// @@findcmd fc=optional();
inline bool has_fc() const;
inline const ::idl::findcmd& fc() const;
inline ::idl::findcmd* mutable_fc();
// deprecated.use 'mutable_fc()' instead.
inline ::idl::findcmd* m_fc();
// @@mgrcmd mc=optional();
inline bool has_mc() const;
inline const ::idl::mgrcmd& mc() const;
inline ::idl::mgrcmd* mutable_mc();
// deprecated.use 'mutable_mc()' instead.
inline ::idl::mgrcmd* m_mc();
// @@cntcmd cc=optional();
inline bool has_cc() const;
inline const ::idl::cntcmd& cc() const;
inline ::idl::cntcmd* mutable_cc();
// deprecated.use 'mutable_cc()' instead.
inline ::idl::cntcmd* m_cc();
// @@listcmd lc=optional();
inline bool has_lc() const;
inline const ::idl::listcmd& lc() const;
inline ::idl::listcmd* mutable_lc();
// deprecated.use 'mutable_lc()' instead.
inline ::idl::listcmd* m_lc();
// @@chlistcmd chlc=optional();
inline bool has_chlc() const;
inline const ::idl::chlistcmd& chlc() const;
inline ::idl::chlistcmd* mutable_chlc();
// deprecated.use 'mutable_chlc()' instead.
inline ::idl::chlistcmd* m_chlc();
// @@playlistcmd plc=optional();
inline bool has_plc() const;
inline const ::idl::playlistcmd& plc() const;
inline ::idl::playlistcmd* mutable_plc();
// deprecated.use 'mutable_plc()' instead.
inline ::idl::playlistcmd* m_plc();
// @@playactioncmd pac=optional();
inline bool has_pac() const;
inline const ::idl::playactioncmd& pac() const;
inline ::idl::playactioncmd* mutable_pac();
// deprecated.use 'mutable_pac()' instead.
inline ::idl::playactioncmd* m_pac();
// @@coldstartreqcmd crc=optional();
inline bool has_crc() const;
inline const ::idl::coldstartreqcmd& crc() const;
inline ::idl::coldstartreqcmd* mutable_crc();
// deprecated.use 'mutable_crc()' instead.
inline ::idl::coldstartreqcmd* m_crc();
// @@coldstartsingerlistcmd cslc=optional();
inline bool has_cslc() const;
inline const ::idl::coldstartsingerlistcmd& cslc() const;
inline ::idl::coldstartsingerlistcmd* mutable_cslc();
// deprecated.use 'mutable_cslc()' instead.
inline ::idl::coldstartsingerlistcmd* m_cslc();
// @@newusercmd nuc=optional();
inline bool has_nuc() const;
inline const ::idl::newusercmd& nuc() const;
inline ::idl::newusercmd* mutable_nuc();
// deprecated.use 'mutable_nuc()' instead.
inline ::idl::newusercmd* m_nuc();
// @@usertagscmd utag_cmd=optional();
inline bool has_utag_cmd() const;
inline const ::idl::usertagscmd& utag_cmd() const;
inline ::idl::usertagscmd* mutable_utag_cmd();
// deprecated.use 'mutable_utag_cmd()' instead.
inline ::idl::usertagscmd* m_utag_cmd();
// @@ticketcmd tic=optional();
inline bool has_tic() const;
inline const ::idl::ticketcmd& tic() const;
inline ::idl::ticketcmd* mutable_tic();
// deprecated.use 'mutable_tic()' instead.
inline ::idl::ticketcmd* m_tic();
// @@piaocmd piao=optional();
inline bool has_piao() const;
inline const ::idl::piaocmd& piao() const;
inline ::idl::piaocmd* mutable_piao();
// deprecated.use 'mutable_piao()' instead.
inline ::idl::piaocmd* m_piao();
inline ::idl::Unknown* mutable_unknown();
inline const ::idl::Unknown& unknown() const;
// deprecated.use 'mutable_unknown' instead.
inline ::idl::Unknown& unknown();
// deprecated.use 'unknown().size()' instead.
inline size_t unknown_size() const;
//============================================================
// mcpack2 load/save.
void load(const mc_pack_t* pack);
void LoadWithoutCheck(const mc_pack_t* pack);
//for compatiblity.return 0 when it accepts item,else return -1
int load(const mc_pack_item_t& item);
size_t save(mc_pack_t* pack) const;
public:
bsl::mempool* _pool;
 int32_t _m_rf;
 ::idl::string _m_username;
 uint32_t _m_uid;
 ::idl::string _m_baiduid;
mutable ::idl::playercmd* _m_pc;
mutable ::idl::findcmd* _m_fc;
mutable ::idl::mgrcmd* _m_mc;
mutable ::idl::cntcmd* _m_cc;
mutable ::idl::listcmd* _m_lc;
mutable ::idl::chlistcmd* _m_chlc;
mutable ::idl::playlistcmd* _m_plc;
mutable ::idl::playactioncmd* _m_pac;
mutable ::idl::coldstartreqcmd* _m_crc;
mutable ::idl::coldstartsingerlistcmd* _m_cslc;
mutable ::idl::newusercmd* _m_nuc;
mutable ::idl::usertagscmd* _m_utag_cmd;
mutable ::idl::ticketcmd* _m_tic;
mutable ::idl::piaocmd* _m_piao;
mutable ::idl::Unknown _unknown;
char _flag[3];
}; // class cmd
inline action* action::create(bsl::mempool* pool){
if(!pool){
throw bsl::NullPointerException() << BSL_EARG;
}
action* tmp=(action*)pool->malloc(sizeof(*tmp));
if(!tmp){
throw bsl::BadAllocException() << BSL_EARG;
}
new(tmp)action(pool);
return tmp;
}
inline void action::destroy(action* v){
if(v){
bsl::mempool *pool=v->_pool;
v->~action();
pool->free(v,sizeof(*v));
}
}
inline action::action(bsl::mempool *pool): 
::idl::McpackBean(pool),
_pool(pool)
,_m_itemid(0)
,_m_action_no(0)
,_unknown(_pool){
memset(_flag,0,sizeof(_flag));
}
inline action::action(const action& v): 
::idl::McpackBean(v._pool),
_pool(v._pool)
,_m_itemid(0)
,_m_action_no(0)
,_unknown(_pool){
assign(v);
}
inline action::~action(){
}
inline action& action::operator=(const action& v){
assign(v);
return *this;
}
inline void action::clear(){
// _m_itemid=0;
// _m_action_no=0;
memset(_flag,0,sizeof(_flag));
_unknown.clear(); 
::idl::McpackBean::clear();
}
// @@CF(constraint functions).
inline void action::check() const{
// @@uint32_t itemid;
if(!(_flag[0 >> 3] & (1 << (0 & 0x7)))){
throw bsl::KeyNotFoundException() << BSL_EARG << "key '" << "itemid" << "' not found";
}
{
__attribute__((unused)) uint32_t item=_m_itemid;

}
// @@int32_t action_no;
if(!(_flag[1 >> 3] & (1 << (1 & 0x7)))){
throw bsl::KeyNotFoundException() << BSL_EARG << "key '" << "action_no" << "' not found";
}
{
__attribute__((unused)) int32_t item=_m_action_no;

}

::idl::McpackBean::check();
}
inline void action::detach(){
_unknown.clear();

::idl::McpackBean::detach();
}
inline action& action::assign(const action& v){
_m_itemid=v._m_itemid;
_m_action_no=v._m_action_no;
_unknown=v._unknown;
bsl::xmemcpy(_flag,v._flag,sizeof(v._flag));
return *this;
}
inline bool action::has_itemid() const{
return (_flag[0 >> 3] & (1 << (0 & 0x7)));
}
inline uint32_t action::itemid() const{
return _m_itemid;
}
inline action& action::set_itemid(uint32_t v){
_flag[0 >> 3] |= (1 << (0 & 0x7));
 _m_itemid=v;
return *this;
}
inline bool action::has_action_no() const{
return (_flag[1 >> 3] & (1 << (1 & 0x7)));
}
inline int32_t action::action_no() const{
return _m_action_no;
}
inline action& action::set_action_no(int32_t v){
_flag[1 >> 3] |= (1 << (1 & 0x7));
 _m_action_no=v;
return *this;
}
inline ::idl::Unknown* action::mutable_unknown(){
return &_unknown;
}
inline const ::idl::Unknown& action::unknown() const{
return _unknown;
}
inline ::idl::Unknown& action::unknown(){
return _unknown;
}
inline size_t action::unknown_size() const{
return _unknown.size();
}
inline playercmd* playercmd::create(bsl::mempool* pool){
if(!pool){
throw bsl::NullPointerException() << BSL_EARG;
}
playercmd* tmp=(playercmd*)pool->malloc(sizeof(*tmp));
if(!tmp){
throw bsl::BadAllocException() << BSL_EARG;
}
new(tmp)playercmd(pool);
return tmp;
}
inline void playercmd::destroy(playercmd* v){
if(v){
bsl::mempool *pool=v->_pool;
v->~playercmd();
pool->free(v,sizeof(*v));
}
}
inline playercmd::playercmd(bsl::mempool *pool): 
::idl::McpackBean(pool),
_pool(pool)
,_m_needdata(0)
,_m_titles(_pool)
,_unknown(_pool){
memset(_flag,0,sizeof(_flag));
}
inline playercmd::playercmd(const playercmd& v): 
::idl::McpackBean(v._pool),
_pool(v._pool)
,_m_needdata(0)
,_m_titles(_pool)
,_unknown(_pool){
assign(v);
}
inline playercmd::~playercmd(){
}
inline playercmd& playercmd::operator=(const playercmd& v){
assign(v);
return *this;
}
inline void playercmd::clear(){
// _m_needdata=0;
_m_titles.clear();
memset(_flag,0,sizeof(_flag));
_unknown.clear(); 
::idl::McpackBean::clear();
}
// @@CF(constraint functions).
inline void playercmd::check() const{
// @@int32_t needdata;
if(!(_flag[0 >> 3] & (1 << (0 & 0x7)))){
throw bsl::KeyNotFoundException() << BSL_EARG << "key '" << "needdata" << "' not found";
}
{
__attribute__((unused)) int32_t item=_m_needdata;

}
// @@action titles=array(0);
if(!(_flag[1 >> 3] & (1 << (1 & 0x7)))){
throw bsl::KeyNotFoundException() << BSL_EARG << "key '" << "titles" << "' not found";
}
{
// level 0 begin
typeof(_m_titles)& lr0=(_m_titles);
__attribute__((unused)) size_t size0=lr0.size();
for(size_t i0=0;i0<size0;i0++){
::idl::action& item=const_cast< ::idl::action& >(lr0.GetWithoutCheck(i0));
item.check();

}

}

::idl::McpackBean::check();
}
inline void playercmd::detach(){
_m_titles.detach();
_unknown.clear();

::idl::McpackBean::detach();
}
inline playercmd& playercmd::assign(const playercmd& v){
_m_needdata=v._m_needdata;
_m_titles=v._m_titles;
_unknown=v._unknown;
bsl::xmemcpy(_flag,v._flag,sizeof(v._flag));
return *this;
}
inline bool playercmd::has_needdata() const{
return (_flag[0 >> 3] & (1 << (0 & 0x7)));
}
inline int32_t playercmd::needdata() const{
return _m_needdata;
}
inline playercmd& playercmd::set_needdata(int32_t v){
_flag[0 >> 3] |= (1 << (0 & 0x7));
 _m_needdata=v;
return *this;
}
inline bool playercmd::has_titles() const{
return (_flag[1 >> 3] & (1 << (1 & 0x7)));
}
inline const ::idl::vector< ::idl::action >& playercmd::titles() const{
 return _m_titles;
}
inline ::idl::vector< ::idl::action >* playercmd::mutable_titles(){
_flag[1 >> 3] |= (1 << (1 & 0x7));
 return &(_m_titles);
}
inline ::idl::vector< ::idl::action >* playercmd::m_titles(){
_flag[1 >> 3] |= (1 << (1 & 0x7));
 return &(_m_titles);
}
inline size_t playercmd::titles_size() const{
 return _m_titles.size();
}
inline const ::idl::action& playercmd::titles(size_t i0) const{
 return _m_titles.get(i0);
}
inline ::idl::action* playercmd::mutable_titles(size_t i0){
_flag[1 >> 3] |= (1 << (1 & 0x7));
 return _m_titles.mutable_get(i0);
}
inline ::idl::action* playercmd::m_titles(size_t i0){
_flag[1 >> 3] |= (1 << (1 & 0x7));
 return _m_titles.mutable_get(i0);
}
inline ::idl::Unknown* playercmd::mutable_unknown(){
return &_unknown;
}
inline const ::idl::Unknown& playercmd::unknown() const{
return _unknown;
}
inline ::idl::Unknown& playercmd::unknown(){
return _unknown;
}
inline size_t playercmd::unknown_size() const{
return _unknown.size();
}
inline findcmd* findcmd::create(bsl::mempool* pool){
if(!pool){
throw bsl::NullPointerException() << BSL_EARG;
}
findcmd* tmp=(findcmd*)pool->malloc(sizeof(*tmp));
if(!tmp){
throw bsl::BadAllocException() << BSL_EARG;
}
new(tmp)findcmd(pool);
return tmp;
}
inline void findcmd::destroy(findcmd* v){
if(v){
bsl::mempool *pool=v->_pool;
v->~findcmd();
pool->free(v,sizeof(*v));
}
}
inline findcmd::findcmd(bsl::mempool *pool): 
::idl::McpackBean(pool),
_pool(pool)
,_m_category(0)
,_m_keyword(_pool)
,_unknown(_pool){
memset(_flag,0,sizeof(_flag));
}
inline findcmd::findcmd(const findcmd& v): 
::idl::McpackBean(v._pool),
_pool(v._pool)
,_m_category(0)
,_m_keyword(_pool)
,_unknown(_pool){
assign(v);
}
inline findcmd::~findcmd(){
}
inline findcmd& findcmd::operator=(const findcmd& v){
assign(v);
return *this;
}
inline void findcmd::clear(){
// _m_category=0;
_m_keyword.clear();
memset(_flag,0,sizeof(_flag));
_unknown.clear(); 
::idl::McpackBean::clear();
}
// @@CF(constraint functions).
inline void findcmd::check() const{
// @@int32_t category;
if(!(_flag[0 >> 3] & (1 << (0 & 0x7)))){
throw bsl::KeyNotFoundException() << BSL_EARG << "key '" << "category" << "' not found";
}
{
__attribute__((unused)) int32_t item=_m_category;

}
// @@string keyword;
if(!(_flag[1 >> 3] & (1 << (1 & 0x7)))){
throw bsl::KeyNotFoundException() << BSL_EARG << "key '" << "keyword" << "' not found";
}
{
__attribute__((unused)) const char* item=_m_keyword.get();

}

::idl::McpackBean::check();
}
inline void findcmd::detach(){
_m_keyword.detach();
_unknown.clear();

::idl::McpackBean::detach();
}
inline findcmd& findcmd::assign(const findcmd& v){
_m_category=v._m_category;
_m_keyword=v._m_keyword;
_unknown=v._unknown;
bsl::xmemcpy(_flag,v._flag,sizeof(v._flag));
return *this;
}
inline bool findcmd::has_category() const{
return (_flag[0 >> 3] & (1 << (0 & 0x7)));
}
inline int32_t findcmd::category() const{
return _m_category;
}
inline findcmd& findcmd::set_category(int32_t v){
_flag[0 >> 3] |= (1 << (0 & 0x7));
 _m_category=v;
return *this;
}
inline bool findcmd::has_keyword() const{
return (_flag[1 >> 3] & (1 << (1 & 0x7)));
}
inline const char* findcmd::keyword(unsigned int* size) const{
return _m_keyword.get(size);
}
inline findcmd& findcmd::set_keyword(const char* s,ssize_t size){
_flag[1 >> 3] |= (1 << (1 & 0x7));
 _m_keyword.set(s,(size==-1)?strlen(s):(size_t)size);
return *this;
}
inline findcmd& findcmd::set_ptr_keyword(const char* s,ssize_t size){
_flag[1 >> 3] |= (1 << (1 & 0x7));
 _m_keyword.set_ptr(s,(size==-1)?strlen(s):(size_t)size);
return *this;
}
inline ::idl::Unknown* findcmd::mutable_unknown(){
return &_unknown;
}
inline const ::idl::Unknown& findcmd::unknown() const{
return _unknown;
}
inline ::idl::Unknown& findcmd::unknown(){
return _unknown;
}
inline size_t findcmd::unknown_size() const{
return _unknown.size();
}
inline mgrcmd* mgrcmd::create(bsl::mempool* pool){
if(!pool){
throw bsl::NullPointerException() << BSL_EARG;
}
mgrcmd* tmp=(mgrcmd*)pool->malloc(sizeof(*tmp));
if(!tmp){
throw bsl::BadAllocException() << BSL_EARG;
}
new(tmp)mgrcmd(pool);
return tmp;
}
inline void mgrcmd::destroy(mgrcmd* v){
if(v){
bsl::mempool *pool=v->_pool;
v->~mgrcmd();
pool->free(v,sizeof(*v));
}
}
inline mgrcmd::mgrcmd(bsl::mempool *pool): 
::idl::McpackBean(pool),
_pool(pool)
,_m_action(0)
,_m_category(0)
,_m_itemid(0)
,_unknown(_pool){
memset(_flag,0,sizeof(_flag));
}
inline mgrcmd::mgrcmd(const mgrcmd& v): 
::idl::McpackBean(v._pool),
_pool(v._pool)
,_m_action(0)
,_m_category(0)
,_m_itemid(0)
,_unknown(_pool){
assign(v);
}
inline mgrcmd::~mgrcmd(){
}
inline mgrcmd& mgrcmd::operator=(const mgrcmd& v){
assign(v);
return *this;
}
inline void mgrcmd::clear(){
// _m_action=0;
// _m_category=0;
// _m_itemid=0;
memset(_flag,0,sizeof(_flag));
_unknown.clear(); 
::idl::McpackBean::clear();
}
// @@CF(constraint functions).
inline void mgrcmd::check() const{
// @@int32_t action;
if(!(_flag[0 >> 3] & (1 << (0 & 0x7)))){
throw bsl::KeyNotFoundException() << BSL_EARG << "key '" << "action" << "' not found";
}
{
__attribute__((unused)) int32_t item=_m_action;

}
// @@int32_t category;
if(!(_flag[1 >> 3] & (1 << (1 & 0x7)))){
throw bsl::KeyNotFoundException() << BSL_EARG << "key '" << "category" << "' not found";
}
{
__attribute__((unused)) int32_t item=_m_category;

}
// @@uint32_t itemid;
if(!(_flag[2 >> 3] & (1 << (2 & 0x7)))){
throw bsl::KeyNotFoundException() << BSL_EARG << "key '" << "itemid" << "' not found";
}
{
__attribute__((unused)) uint32_t item=_m_itemid;

}

::idl::McpackBean::check();
}
inline void mgrcmd::detach(){
_unknown.clear();

::idl::McpackBean::detach();
}
inline mgrcmd& mgrcmd::assign(const mgrcmd& v){
_m_action=v._m_action;
_m_category=v._m_category;
_m_itemid=v._m_itemid;
_unknown=v._unknown;
bsl::xmemcpy(_flag,v._flag,sizeof(v._flag));
return *this;
}
inline bool mgrcmd::has_action() const{
return (_flag[0 >> 3] & (1 << (0 & 0x7)));
}
inline int32_t mgrcmd::action() const{
return _m_action;
}
inline mgrcmd& mgrcmd::set_action(int32_t v){
_flag[0 >> 3] |= (1 << (0 & 0x7));
 _m_action=v;
return *this;
}
inline bool mgrcmd::has_category() const{
return (_flag[1 >> 3] & (1 << (1 & 0x7)));
}
inline int32_t mgrcmd::category() const{
return _m_category;
}
inline mgrcmd& mgrcmd::set_category(int32_t v){
_flag[1 >> 3] |= (1 << (1 & 0x7));
 _m_category=v;
return *this;
}
inline bool mgrcmd::has_itemid() const{
return (_flag[2 >> 3] & (1 << (2 & 0x7)));
}
inline uint32_t mgrcmd::itemid() const{
return _m_itemid;
}
inline mgrcmd& mgrcmd::set_itemid(uint32_t v){
_flag[2 >> 3] |= (1 << (2 & 0x7));
 _m_itemid=v;
return *this;
}
inline ::idl::Unknown* mgrcmd::mutable_unknown(){
return &_unknown;
}
inline const ::idl::Unknown& mgrcmd::unknown() const{
return _unknown;
}
inline ::idl::Unknown& mgrcmd::unknown(){
return _unknown;
}
inline size_t mgrcmd::unknown_size() const{
return _unknown.size();
}
inline cntcmd* cntcmd::create(bsl::mempool* pool){
if(!pool){
throw bsl::NullPointerException() << BSL_EARG;
}
cntcmd* tmp=(cntcmd*)pool->malloc(sizeof(*tmp));
if(!tmp){
throw bsl::BadAllocException() << BSL_EARG;
}
new(tmp)cntcmd(pool);
return tmp;
}
inline void cntcmd::destroy(cntcmd* v){
if(v){
bsl::mempool *pool=v->_pool;
v->~cntcmd();
pool->free(v,sizeof(*v));
}
}
inline cntcmd::cntcmd(bsl::mempool *pool): 
::idl::McpackBean(pool),
_pool(pool)
,_m_src(0)
,_unknown(_pool){
memset(_flag,0,sizeof(_flag));
}
inline cntcmd::cntcmd(const cntcmd& v): 
::idl::McpackBean(v._pool),
_pool(v._pool)
,_m_src(0)
,_unknown(_pool){
assign(v);
}
inline cntcmd::~cntcmd(){
}
inline cntcmd& cntcmd::operator=(const cntcmd& v){
assign(v);
return *this;
}
inline void cntcmd::clear(){
// _m_src=0;
memset(_flag,0,sizeof(_flag));
_unknown.clear(); 
::idl::McpackBean::clear();
}
// @@CF(constraint functions).
inline void cntcmd::check() const{
// @@int32_t src;
if(!(_flag[0 >> 3] & (1 << (0 & 0x7)))){
throw bsl::KeyNotFoundException() << BSL_EARG << "key '" << "src" << "' not found";
}
{
__attribute__((unused)) int32_t item=_m_src;

}

::idl::McpackBean::check();
}
inline void cntcmd::detach(){
_unknown.clear();

::idl::McpackBean::detach();
}
inline cntcmd& cntcmd::assign(const cntcmd& v){
_m_src=v._m_src;
_unknown=v._unknown;
bsl::xmemcpy(_flag,v._flag,sizeof(v._flag));
return *this;
}
inline bool cntcmd::has_src() const{
return (_flag[0 >> 3] & (1 << (0 & 0x7)));
}
inline int32_t cntcmd::src() const{
return _m_src;
}
inline cntcmd& cntcmd::set_src(int32_t v){
_flag[0 >> 3] |= (1 << (0 & 0x7));
 _m_src=v;
return *this;
}
inline ::idl::Unknown* cntcmd::mutable_unknown(){
return &_unknown;
}
inline const ::idl::Unknown& cntcmd::unknown() const{
return _unknown;
}
inline ::idl::Unknown& cntcmd::unknown(){
return _unknown;
}
inline size_t cntcmd::unknown_size() const{
return _unknown.size();
}
inline listcmd* listcmd::create(bsl::mempool* pool){
if(!pool){
throw bsl::NullPointerException() << BSL_EARG;
}
listcmd* tmp=(listcmd*)pool->malloc(sizeof(*tmp));
if(!tmp){
throw bsl::BadAllocException() << BSL_EARG;
}
new(tmp)listcmd(pool);
return tmp;
}
inline void listcmd::destroy(listcmd* v){
if(v){
bsl::mempool *pool=v->_pool;
v->~listcmd();
pool->free(v,sizeof(*v));
}
}
inline listcmd::listcmd(bsl::mempool *pool): 
::idl::McpackBean(pool),
_pool(pool)
,_m_type(0)
,_m_page_len(0)
,_m_page_no(0)
,_m_src(0)
,_unknown(_pool){
memset(_flag,0,sizeof(_flag));
}
inline listcmd::listcmd(const listcmd& v): 
::idl::McpackBean(v._pool),
_pool(v._pool)
,_m_type(0)
,_m_page_len(0)
,_m_page_no(0)
,_m_src(0)
,_unknown(_pool){
assign(v);
}
inline listcmd::~listcmd(){
}
inline listcmd& listcmd::operator=(const listcmd& v){
assign(v);
return *this;
}
inline void listcmd::clear(){
// _m_type=0;
// _m_page_len=0;
// _m_page_no=0;
// _m_src=0;
memset(_flag,0,sizeof(_flag));
_unknown.clear(); 
::idl::McpackBean::clear();
}
// @@CF(constraint functions).
inline void listcmd::check() const{
// @@int32_t type;
if(!(_flag[0 >> 3] & (1 << (0 & 0x7)))){
throw bsl::KeyNotFoundException() << BSL_EARG << "key '" << "type" << "' not found";
}
{
__attribute__((unused)) int32_t item=_m_type;

}
// @@int32_t page_len;
if(!(_flag[1 >> 3] & (1 << (1 & 0x7)))){
throw bsl::KeyNotFoundException() << BSL_EARG << "key '" << "page_len" << "' not found";
}
{
__attribute__((unused)) int32_t item=_m_page_len;

}
// @@int32_t page_no;
if(!(_flag[2 >> 3] & (1 << (2 & 0x7)))){
throw bsl::KeyNotFoundException() << BSL_EARG << "key '" << "page_no" << "' not found";
}
{
__attribute__((unused)) int32_t item=_m_page_no;

}
// @@int32_t src;
if(!(_flag[3 >> 3] & (1 << (3 & 0x7)))){
throw bsl::KeyNotFoundException() << BSL_EARG << "key '" << "src" << "' not found";
}
{
__attribute__((unused)) int32_t item=_m_src;

}

::idl::McpackBean::check();
}
inline void listcmd::detach(){
_unknown.clear();

::idl::McpackBean::detach();
}
inline listcmd& listcmd::assign(const listcmd& v){
_m_type=v._m_type;
_m_page_len=v._m_page_len;
_m_page_no=v._m_page_no;
_m_src=v._m_src;
_unknown=v._unknown;
bsl::xmemcpy(_flag,v._flag,sizeof(v._flag));
return *this;
}
inline bool listcmd::has_type() const{
return (_flag[0 >> 3] & (1 << (0 & 0x7)));
}
inline int32_t listcmd::type() const{
return _m_type;
}
inline listcmd& listcmd::set_type(int32_t v){
_flag[0 >> 3] |= (1 << (0 & 0x7));
 _m_type=v;
return *this;
}
inline bool listcmd::has_page_len() const{
return (_flag[1 >> 3] & (1 << (1 & 0x7)));
}
inline int32_t listcmd::page_len() const{
return _m_page_len;
}
inline listcmd& listcmd::set_page_len(int32_t v){
_flag[1 >> 3] |= (1 << (1 & 0x7));
 _m_page_len=v;
return *this;
}
inline bool listcmd::has_page_no() const{
return (_flag[2 >> 3] & (1 << (2 & 0x7)));
}
inline int32_t listcmd::page_no() const{
return _m_page_no;
}
inline listcmd& listcmd::set_page_no(int32_t v){
_flag[2 >> 3] |= (1 << (2 & 0x7));
 _m_page_no=v;
return *this;
}
inline bool listcmd::has_src() const{
return (_flag[3 >> 3] & (1 << (3 & 0x7)));
}
inline int32_t listcmd::src() const{
return _m_src;
}
inline listcmd& listcmd::set_src(int32_t v){
_flag[3 >> 3] |= (1 << (3 & 0x7));
 _m_src=v;
return *this;
}
inline ::idl::Unknown* listcmd::mutable_unknown(){
return &_unknown;
}
inline const ::idl::Unknown& listcmd::unknown() const{
return _unknown;
}
inline ::idl::Unknown& listcmd::unknown(){
return _unknown;
}
inline size_t listcmd::unknown_size() const{
return _unknown.size();
}
inline ticketcmd* ticketcmd::create(bsl::mempool* pool){
if(!pool){
throw bsl::NullPointerException() << BSL_EARG;
}
ticketcmd* tmp=(ticketcmd*)pool->malloc(sizeof(*tmp));
if(!tmp){
throw bsl::BadAllocException() << BSL_EARG;
}
new(tmp)ticketcmd(pool);
return tmp;
}
inline void ticketcmd::destroy(ticketcmd* v){
if(v){
bsl::mempool *pool=v->_pool;
v->~ticketcmd();
pool->free(v,sizeof(*v));
}
}
inline ticketcmd::ticketcmd(bsl::mempool *pool): 
::idl::McpackBean(pool),
_pool(pool)
,_m_len(0)
,_unknown(_pool){
memset(_flag,0,sizeof(_flag));
}
inline ticketcmd::ticketcmd(const ticketcmd& v): 
::idl::McpackBean(v._pool),
_pool(v._pool)
,_m_len(0)
,_unknown(_pool){
assign(v);
}
inline ticketcmd::~ticketcmd(){
}
inline ticketcmd& ticketcmd::operator=(const ticketcmd& v){
assign(v);
return *this;
}
inline void ticketcmd::clear(){
// _m_len=0;
memset(_flag,0,sizeof(_flag));
_unknown.clear(); 
::idl::McpackBean::clear();
}
// @@CF(constraint functions).
inline void ticketcmd::check() const{
// @@int32_t len;
if(!(_flag[0 >> 3] & (1 << (0 & 0x7)))){
throw bsl::KeyNotFoundException() << BSL_EARG << "key '" << "len" << "' not found";
}
{
__attribute__((unused)) int32_t item=_m_len;

}

::idl::McpackBean::check();
}
inline void ticketcmd::detach(){
_unknown.clear();

::idl::McpackBean::detach();
}
inline ticketcmd& ticketcmd::assign(const ticketcmd& v){
_m_len=v._m_len;
_unknown=v._unknown;
bsl::xmemcpy(_flag,v._flag,sizeof(v._flag));
return *this;
}
inline bool ticketcmd::has_len() const{
return (_flag[0 >> 3] & (1 << (0 & 0x7)));
}
inline int32_t ticketcmd::len() const{
return _m_len;
}
inline ticketcmd& ticketcmd::set_len(int32_t v){
_flag[0 >> 3] |= (1 << (0 & 0x7));
 _m_len=v;
return *this;
}
inline ::idl::Unknown* ticketcmd::mutable_unknown(){
return &_unknown;
}
inline const ::idl::Unknown& ticketcmd::unknown() const{
return _unknown;
}
inline ::idl::Unknown& ticketcmd::unknown(){
return _unknown;
}
inline size_t ticketcmd::unknown_size() const{
return _unknown.size();
}
inline piaocmd* piaocmd::create(bsl::mempool* pool){
if(!pool){
throw bsl::NullPointerException() << BSL_EARG;
}
piaocmd* tmp=(piaocmd*)pool->malloc(sizeof(*tmp));
if(!tmp){
throw bsl::BadAllocException() << BSL_EARG;
}
new(tmp)piaocmd(pool);
return tmp;
}
inline void piaocmd::destroy(piaocmd* v){
if(v){
bsl::mempool *pool=v->_pool;
v->~piaocmd();
pool->free(v,sizeof(*v));
}
}
inline piaocmd::piaocmd(bsl::mempool *pool): 
::idl::McpackBean(pool),
_pool(pool)
,_m_sub_cmd(0)
,_m_len(0)
,_m_artist_id(0)
,_m_top_len(0)
,_m_page_size(0)
,_m_page_number(0)
,_unknown(_pool){
memset(_flag,0,sizeof(_flag));
}
inline piaocmd::piaocmd(const piaocmd& v): 
::idl::McpackBean(v._pool),
_pool(v._pool)
,_m_sub_cmd(0)
,_m_len(0)
,_m_artist_id(0)
,_m_top_len(0)
,_m_page_size(0)
,_m_page_number(0)
,_unknown(_pool){
assign(v);
}
inline piaocmd::~piaocmd(){
}
inline piaocmd& piaocmd::operator=(const piaocmd& v){
assign(v);
return *this;
}
inline void piaocmd::clear(){
// _m_sub_cmd=0;
// _m_len=0;
// _m_artist_id=0;
// _m_top_len=0;
// _m_page_size=0;
// _m_page_number=0;
memset(_flag,0,sizeof(_flag));
_unknown.clear(); 
::idl::McpackBean::clear();
}
// @@CF(constraint functions).
inline void piaocmd::check() const{
// @@uint32_t sub_cmd;
if(!(_flag[0 >> 3] & (1 << (0 & 0x7)))){
throw bsl::KeyNotFoundException() << BSL_EARG << "key '" << "sub_cmd" << "' not found";
}
{
__attribute__((unused)) uint32_t item=_m_sub_cmd;

}
// @@int32_t len=optional();
if((_flag[1 >> 3] & (1 << (1 & 0x7)))){
{
__attribute__((unused)) int32_t item=_m_len;

}
}    
// @@uint32_t artist_id=optional();
if((_flag[2 >> 3] & (1 << (2 & 0x7)))){
{
__attribute__((unused)) uint32_t item=_m_artist_id;

}
}    
// @@uint32_t top_len=optional();
if((_flag[3 >> 3] & (1 << (3 & 0x7)))){
{
__attribute__((unused)) uint32_t item=_m_top_len;

}
}    
// @@uint32_t page_size=optional();
if((_flag[4 >> 3] & (1 << (4 & 0x7)))){
{
__attribute__((unused)) uint32_t item=_m_page_size;

}
}    
// @@int32_t page_number=optional();
if((_flag[5 >> 3] & (1 << (5 & 0x7)))){
{
__attribute__((unused)) int32_t item=_m_page_number;

}
}    

::idl::McpackBean::check();
}
inline void piaocmd::detach(){
_unknown.clear();

::idl::McpackBean::detach();
}
inline piaocmd& piaocmd::assign(const piaocmd& v){
_m_sub_cmd=v._m_sub_cmd;
_m_len=v._m_len;
_m_artist_id=v._m_artist_id;
_m_top_len=v._m_top_len;
_m_page_size=v._m_page_size;
_m_page_number=v._m_page_number;
_unknown=v._unknown;
bsl::xmemcpy(_flag,v._flag,sizeof(v._flag));
return *this;
}
inline bool piaocmd::has_sub_cmd() const{
return (_flag[0 >> 3] & (1 << (0 & 0x7)));
}
inline uint32_t piaocmd::sub_cmd() const{
return _m_sub_cmd;
}
inline piaocmd& piaocmd::set_sub_cmd(uint32_t v){
_flag[0 >> 3] |= (1 << (0 & 0x7));
 _m_sub_cmd=v;
return *this;
}
inline bool piaocmd::has_len() const{
return (_flag[1 >> 3] & (1 << (1 & 0x7)));
}
inline int32_t piaocmd::len() const{
if(!((_flag[1 >> 3] & (1 << (1 & 0x7))))){
throw bsl::KeyNotFoundException() << BSL_EARG;
}
return _m_len;
}
inline piaocmd& piaocmd::set_len(int32_t v){
_flag[1 >> 3] |= (1 << (1 & 0x7));
 _m_len=v;
return *this;
}
inline bool piaocmd::has_artist_id() const{
return (_flag[2 >> 3] & (1 << (2 & 0x7)));
}
inline uint32_t piaocmd::artist_id() const{
if(!((_flag[2 >> 3] & (1 << (2 & 0x7))))){
throw bsl::KeyNotFoundException() << BSL_EARG;
}
return _m_artist_id;
}
inline piaocmd& piaocmd::set_artist_id(uint32_t v){
_flag[2 >> 3] |= (1 << (2 & 0x7));
 _m_artist_id=v;
return *this;
}
inline bool piaocmd::has_top_len() const{
return (_flag[3 >> 3] & (1 << (3 & 0x7)));
}
inline uint32_t piaocmd::top_len() const{
if(!((_flag[3 >> 3] & (1 << (3 & 0x7))))){
throw bsl::KeyNotFoundException() << BSL_EARG;
}
return _m_top_len;
}
inline piaocmd& piaocmd::set_top_len(uint32_t v){
_flag[3 >> 3] |= (1 << (3 & 0x7));
 _m_top_len=v;
return *this;
}
inline bool piaocmd::has_page_size() const{
return (_flag[4 >> 3] & (1 << (4 & 0x7)));
}
inline uint32_t piaocmd::page_size() const{
if(!((_flag[4 >> 3] & (1 << (4 & 0x7))))){
throw bsl::KeyNotFoundException() << BSL_EARG;
}
return _m_page_size;
}
inline piaocmd& piaocmd::set_page_size(uint32_t v){
_flag[4 >> 3] |= (1 << (4 & 0x7));
 _m_page_size=v;
return *this;
}
inline bool piaocmd::has_page_number() const{
return (_flag[5 >> 3] & (1 << (5 & 0x7)));
}
inline int32_t piaocmd::page_number() const{
if(!((_flag[5 >> 3] & (1 << (5 & 0x7))))){
throw bsl::KeyNotFoundException() << BSL_EARG;
}
return _m_page_number;
}
inline piaocmd& piaocmd::set_page_number(int32_t v){
_flag[5 >> 3] |= (1 << (5 & 0x7));
 _m_page_number=v;
return *this;
}
inline ::idl::Unknown* piaocmd::mutable_unknown(){
return &_unknown;
}
inline const ::idl::Unknown& piaocmd::unknown() const{
return _unknown;
}
inline ::idl::Unknown& piaocmd::unknown(){
return _unknown;
}
inline size_t piaocmd::unknown_size() const{
return _unknown.size();
}
inline chlistcmd* chlistcmd::create(bsl::mempool* pool){
if(!pool){
throw bsl::NullPointerException() << BSL_EARG;
}
chlistcmd* tmp=(chlistcmd*)pool->malloc(sizeof(*tmp));
if(!tmp){
throw bsl::BadAllocException() << BSL_EARG;
}
new(tmp)chlistcmd(pool);
return tmp;
}
inline void chlistcmd::destroy(chlistcmd* v){
if(v){
bsl::mempool *pool=v->_pool;
v->~chlistcmd();
pool->free(v,sizeof(*v));
}
}
inline chlistcmd::chlistcmd(bsl::mempool *pool): 
::idl::McpackBean(pool),
_pool(pool)
,_m_cate_name(_pool)
,_unknown(_pool){
memset(_flag,0,sizeof(_flag));
}
inline chlistcmd::chlistcmd(const chlistcmd& v): 
::idl::McpackBean(v._pool),
_pool(v._pool)
,_m_cate_name(_pool)
,_unknown(_pool){
assign(v);
}
inline chlistcmd::~chlistcmd(){
}
inline chlistcmd& chlistcmd::operator=(const chlistcmd& v){
assign(v);
return *this;
}
inline void chlistcmd::clear(){
_m_cate_name.clear();
memset(_flag,0,sizeof(_flag));
_unknown.clear(); 
::idl::McpackBean::clear();
}
// @@CF(constraint functions).
inline void chlistcmd::check() const{
// @@string cate_name;
if(!(_flag[0 >> 3] & (1 << (0 & 0x7)))){
throw bsl::KeyNotFoundException() << BSL_EARG << "key '" << "cate_name" << "' not found";
}
{
__attribute__((unused)) const char* item=_m_cate_name.get();

}

::idl::McpackBean::check();
}
inline void chlistcmd::detach(){
_m_cate_name.detach();
_unknown.clear();

::idl::McpackBean::detach();
}
inline chlistcmd& chlistcmd::assign(const chlistcmd& v){
_m_cate_name=v._m_cate_name;
_unknown=v._unknown;
bsl::xmemcpy(_flag,v._flag,sizeof(v._flag));
return *this;
}
inline bool chlistcmd::has_cate_name() const{
return (_flag[0 >> 3] & (1 << (0 & 0x7)));
}
inline const char* chlistcmd::cate_name(unsigned int* size) const{
return _m_cate_name.get(size);
}
inline chlistcmd& chlistcmd::set_cate_name(const char* s,ssize_t size){
_flag[0 >> 3] |= (1 << (0 & 0x7));
 _m_cate_name.set(s,(size==-1)?strlen(s):(size_t)size);
return *this;
}
inline chlistcmd& chlistcmd::set_ptr_cate_name(const char* s,ssize_t size){
_flag[0 >> 3] |= (1 << (0 & 0x7));
 _m_cate_name.set_ptr(s,(size==-1)?strlen(s):(size_t)size);
return *this;
}
inline ::idl::Unknown* chlistcmd::mutable_unknown(){
return &_unknown;
}
inline const ::idl::Unknown& chlistcmd::unknown() const{
return _unknown;
}
inline ::idl::Unknown& chlistcmd::unknown(){
return _unknown;
}
inline size_t chlistcmd::unknown_size() const{
return _unknown.size();
}
inline playlistcmd* playlistcmd::create(bsl::mempool* pool){
if(!pool){
throw bsl::NullPointerException() << BSL_EARG;
}
playlistcmd* tmp=(playlistcmd*)pool->malloc(sizeof(*tmp));
if(!tmp){
throw bsl::BadAllocException() << BSL_EARG;
}
new(tmp)playlistcmd(pool);
return tmp;
}
inline void playlistcmd::destroy(playlistcmd* v){
if(v){
bsl::mempool *pool=v->_pool;
v->~playlistcmd();
pool->free(v,sizeof(*v));
}
}
inline playlistcmd::playlistcmd(bsl::mempool *pool): 
::idl::McpackBean(pool),
_pool(pool)
,_m_ch_name(_pool)
,_unknown(_pool){
memset(_flag,0,sizeof(_flag));
}
inline playlistcmd::playlistcmd(const playlistcmd& v): 
::idl::McpackBean(v._pool),
_pool(v._pool)
,_m_ch_name(_pool)
,_unknown(_pool){
assign(v);
}
inline playlistcmd::~playlistcmd(){
}
inline playlistcmd& playlistcmd::operator=(const playlistcmd& v){
assign(v);
return *this;
}
inline void playlistcmd::clear(){
_m_ch_name.clear();
memset(_flag,0,sizeof(_flag));
_unknown.clear(); 
::idl::McpackBean::clear();
}
// @@CF(constraint functions).
inline void playlistcmd::check() const{
// @@string ch_name;
if(!(_flag[0 >> 3] & (1 << (0 & 0x7)))){
throw bsl::KeyNotFoundException() << BSL_EARG << "key '" << "ch_name" << "' not found";
}
{
__attribute__((unused)) const char* item=_m_ch_name.get();

}

::idl::McpackBean::check();
}
inline void playlistcmd::detach(){
_m_ch_name.detach();
_unknown.clear();

::idl::McpackBean::detach();
}
inline playlistcmd& playlistcmd::assign(const playlistcmd& v){
_m_ch_name=v._m_ch_name;
_unknown=v._unknown;
bsl::xmemcpy(_flag,v._flag,sizeof(v._flag));
return *this;
}
inline bool playlistcmd::has_ch_name() const{
return (_flag[0 >> 3] & (1 << (0 & 0x7)));
}
inline const char* playlistcmd::ch_name(unsigned int* size) const{
return _m_ch_name.get(size);
}
inline playlistcmd& playlistcmd::set_ch_name(const char* s,ssize_t size){
_flag[0 >> 3] |= (1 << (0 & 0x7));
 _m_ch_name.set(s,(size==-1)?strlen(s):(size_t)size);
return *this;
}
inline playlistcmd& playlistcmd::set_ptr_ch_name(const char* s,ssize_t size){
_flag[0 >> 3] |= (1 << (0 & 0x7));
 _m_ch_name.set_ptr(s,(size==-1)?strlen(s):(size_t)size);
return *this;
}
inline ::idl::Unknown* playlistcmd::mutable_unknown(){
return &_unknown;
}
inline const ::idl::Unknown& playlistcmd::unknown() const{
return _unknown;
}
inline ::idl::Unknown& playlistcmd::unknown(){
return _unknown;
}
inline size_t playlistcmd::unknown_size() const{
return _unknown.size();
}
inline playactioncmd* playactioncmd::create(bsl::mempool* pool){
if(!pool){
throw bsl::NullPointerException() << BSL_EARG;
}
playactioncmd* tmp=(playactioncmd*)pool->malloc(sizeof(*tmp));
if(!tmp){
throw bsl::BadAllocException() << BSL_EARG;
}
new(tmp)playactioncmd(pool);
return tmp;
}
inline void playactioncmd::destroy(playactioncmd* v){
if(v){
bsl::mempool *pool=v->_pool;
v->~playactioncmd();
pool->free(v,sizeof(*v));
}
}
inline playactioncmd::playactioncmd(bsl::mempool *pool): 
::idl::McpackBean(pool),
_pool(pool)
,_m_ch_name(_pool)
,_m_item_id(0)
,_m_pack_item_ids(_pool)
,_m_action_no(0)
,_unknown(_pool){
memset(_flag,0,sizeof(_flag));
}
inline playactioncmd::playactioncmd(const playactioncmd& v): 
::idl::McpackBean(v._pool),
_pool(v._pool)
,_m_ch_name(_pool)
,_m_item_id(0)
,_m_pack_item_ids(_pool)
,_m_action_no(0)
,_unknown(_pool){
assign(v);
}
inline playactioncmd::~playactioncmd(){
}
inline playactioncmd& playactioncmd::operator=(const playactioncmd& v){
assign(v);
return *this;
}
inline void playactioncmd::clear(){
_m_ch_name.clear();
// _m_item_id=0;
_m_pack_item_ids.clear();
// _m_action_no=0;
memset(_flag,0,sizeof(_flag));
_unknown.clear(); 
::idl::McpackBean::clear();
}
// @@CF(constraint functions).
inline void playactioncmd::check() const{
// @@string ch_name;
if(!(_flag[0 >> 3] & (1 << (0 & 0x7)))){
throw bsl::KeyNotFoundException() << BSL_EARG << "key '" << "ch_name" << "' not found";
}
{
__attribute__((unused)) const char* item=_m_ch_name.get();

}
// @@uint64_t item_id;
if(!(_flag[1 >> 3] & (1 << (1 & 0x7)))){
throw bsl::KeyNotFoundException() << BSL_EARG << "key '" << "item_id" << "' not found";
}
{
__attribute__((unused)) uint64_t item=_m_item_id;

}
// @@string pack_item_ids;
if(!(_flag[2 >> 3] & (1 << (2 & 0x7)))){
throw bsl::KeyNotFoundException() << BSL_EARG << "key '" << "pack_item_ids" << "' not found";
}
{
__attribute__((unused)) const char* item=_m_pack_item_ids.get();

}
// @@int32_t action_no;
if(!(_flag[3 >> 3] & (1 << (3 & 0x7)))){
throw bsl::KeyNotFoundException() << BSL_EARG << "key '" << "action_no" << "' not found";
}
{
__attribute__((unused)) int32_t item=_m_action_no;

}

::idl::McpackBean::check();
}
inline void playactioncmd::detach(){
_m_ch_name.detach();
_m_pack_item_ids.detach();
_unknown.clear();

::idl::McpackBean::detach();
}
inline playactioncmd& playactioncmd::assign(const playactioncmd& v){
_m_ch_name=v._m_ch_name;
_m_item_id=v._m_item_id;
_m_pack_item_ids=v._m_pack_item_ids;
_m_action_no=v._m_action_no;
_unknown=v._unknown;
bsl::xmemcpy(_flag,v._flag,sizeof(v._flag));
return *this;
}
inline bool playactioncmd::has_ch_name() const{
return (_flag[0 >> 3] & (1 << (0 & 0x7)));
}
inline const char* playactioncmd::ch_name(unsigned int* size) const{
return _m_ch_name.get(size);
}
inline playactioncmd& playactioncmd::set_ch_name(const char* s,ssize_t size){
_flag[0 >> 3] |= (1 << (0 & 0x7));
 _m_ch_name.set(s,(size==-1)?strlen(s):(size_t)size);
return *this;
}
inline playactioncmd& playactioncmd::set_ptr_ch_name(const char* s,ssize_t size){
_flag[0 >> 3] |= (1 << (0 & 0x7));
 _m_ch_name.set_ptr(s,(size==-1)?strlen(s):(size_t)size);
return *this;
}
inline bool playactioncmd::has_item_id() const{
return (_flag[1 >> 3] & (1 << (1 & 0x7)));
}
inline uint64_t playactioncmd::item_id() const{
return _m_item_id;
}
inline playactioncmd& playactioncmd::set_item_id(uint64_t v){
_flag[1 >> 3] |= (1 << (1 & 0x7));
 _m_item_id=v;
return *this;
}
inline bool playactioncmd::has_pack_item_ids() const{
return (_flag[2 >> 3] & (1 << (2 & 0x7)));
}
inline const char* playactioncmd::pack_item_ids(unsigned int* size) const{
return _m_pack_item_ids.get(size);
}
inline playactioncmd& playactioncmd::set_pack_item_ids(const char* s,ssize_t size){
_flag[2 >> 3] |= (1 << (2 & 0x7));
 _m_pack_item_ids.set(s,(size==-1)?strlen(s):(size_t)size);
return *this;
}
inline playactioncmd& playactioncmd::set_ptr_pack_item_ids(const char* s,ssize_t size){
_flag[2 >> 3] |= (1 << (2 & 0x7));
 _m_pack_item_ids.set_ptr(s,(size==-1)?strlen(s):(size_t)size);
return *this;
}
inline bool playactioncmd::has_action_no() const{
return (_flag[3 >> 3] & (1 << (3 & 0x7)));
}
inline int32_t playactioncmd::action_no() const{
return _m_action_no;
}
inline playactioncmd& playactioncmd::set_action_no(int32_t v){
_flag[3 >> 3] |= (1 << (3 & 0x7));
 _m_action_no=v;
return *this;
}
inline ::idl::Unknown* playactioncmd::mutable_unknown(){
return &_unknown;
}
inline const ::idl::Unknown& playactioncmd::unknown() const{
return _unknown;
}
inline ::idl::Unknown& playactioncmd::unknown(){
return _unknown;
}
inline size_t playactioncmd::unknown_size() const{
return _unknown.size();
}
inline coldstartreqcmd* coldstartreqcmd::create(bsl::mempool* pool){
if(!pool){
throw bsl::NullPointerException() << BSL_EARG;
}
coldstartreqcmd* tmp=(coldstartreqcmd*)pool->malloc(sizeof(*tmp));
if(!tmp){
throw bsl::BadAllocException() << BSL_EARG;
}
new(tmp)coldstartreqcmd(pool);
return tmp;
}
inline void coldstartreqcmd::destroy(coldstartreqcmd* v){
if(v){
bsl::mempool *pool=v->_pool;
v->~coldstartreqcmd();
pool->free(v,sizeof(*v));
}
}
inline coldstartreqcmd::coldstartreqcmd(bsl::mempool *pool): 
::idl::McpackBean(pool),
_pool(pool)
,_m_ch_name(_pool)
,_m_lovesinger(_pool)
,_unknown(_pool){
memset(_flag,0,sizeof(_flag));
}
inline coldstartreqcmd::coldstartreqcmd(const coldstartreqcmd& v): 
::idl::McpackBean(v._pool),
_pool(v._pool)
,_m_ch_name(_pool)
,_m_lovesinger(_pool)
,_unknown(_pool){
assign(v);
}
inline coldstartreqcmd::~coldstartreqcmd(){
}
inline coldstartreqcmd& coldstartreqcmd::operator=(const coldstartreqcmd& v){
assign(v);
return *this;
}
inline void coldstartreqcmd::clear(){
_m_ch_name.clear();
_m_lovesinger.clear();
memset(_flag,0,sizeof(_flag));
_unknown.clear(); 
::idl::McpackBean::clear();
}
// @@CF(constraint functions).
inline void coldstartreqcmd::check() const{
// @@string ch_name;
if(!(_flag[0 >> 3] & (1 << (0 & 0x7)))){
throw bsl::KeyNotFoundException() << BSL_EARG << "key '" << "ch_name" << "' not found";
}
{
__attribute__((unused)) const char* item=_m_ch_name.get();

}
// @@string lovesinger;
if(!(_flag[1 >> 3] & (1 << (1 & 0x7)))){
throw bsl::KeyNotFoundException() << BSL_EARG << "key '" << "lovesinger" << "' not found";
}
{
__attribute__((unused)) const char* item=_m_lovesinger.get();

}

::idl::McpackBean::check();
}
inline void coldstartreqcmd::detach(){
_m_ch_name.detach();
_m_lovesinger.detach();
_unknown.clear();

::idl::McpackBean::detach();
}
inline coldstartreqcmd& coldstartreqcmd::assign(const coldstartreqcmd& v){
_m_ch_name=v._m_ch_name;
_m_lovesinger=v._m_lovesinger;
_unknown=v._unknown;
bsl::xmemcpy(_flag,v._flag,sizeof(v._flag));
return *this;
}
inline bool coldstartreqcmd::has_ch_name() const{
return (_flag[0 >> 3] & (1 << (0 & 0x7)));
}
inline const char* coldstartreqcmd::ch_name(unsigned int* size) const{
return _m_ch_name.get(size);
}
inline coldstartreqcmd& coldstartreqcmd::set_ch_name(const char* s,ssize_t size){
_flag[0 >> 3] |= (1 << (0 & 0x7));
 _m_ch_name.set(s,(size==-1)?strlen(s):(size_t)size);
return *this;
}
inline coldstartreqcmd& coldstartreqcmd::set_ptr_ch_name(const char* s,ssize_t size){
_flag[0 >> 3] |= (1 << (0 & 0x7));
 _m_ch_name.set_ptr(s,(size==-1)?strlen(s):(size_t)size);
return *this;
}
inline bool coldstartreqcmd::has_lovesinger() const{
return (_flag[1 >> 3] & (1 << (1 & 0x7)));
}
inline const char* coldstartreqcmd::lovesinger(unsigned int* size) const{
return _m_lovesinger.get(size);
}
inline coldstartreqcmd& coldstartreqcmd::set_lovesinger(const char* s,ssize_t size){
_flag[1 >> 3] |= (1 << (1 & 0x7));
 _m_lovesinger.set(s,(size==-1)?strlen(s):(size_t)size);
return *this;
}
inline coldstartreqcmd& coldstartreqcmd::set_ptr_lovesinger(const char* s,ssize_t size){
_flag[1 >> 3] |= (1 << (1 & 0x7));
 _m_lovesinger.set_ptr(s,(size==-1)?strlen(s):(size_t)size);
return *this;
}
inline ::idl::Unknown* coldstartreqcmd::mutable_unknown(){
return &_unknown;
}
inline const ::idl::Unknown& coldstartreqcmd::unknown() const{
return _unknown;
}
inline ::idl::Unknown& coldstartreqcmd::unknown(){
return _unknown;
}
inline size_t coldstartreqcmd::unknown_size() const{
return _unknown.size();
}
inline coldstartsingerlistcmd* coldstartsingerlistcmd::create(bsl::mempool* pool){
if(!pool){
throw bsl::NullPointerException() << BSL_EARG;
}
coldstartsingerlistcmd* tmp=(coldstartsingerlistcmd*)pool->malloc(sizeof(*tmp));
if(!tmp){
throw bsl::BadAllocException() << BSL_EARG;
}
new(tmp)coldstartsingerlistcmd(pool);
return tmp;
}
inline void coldstartsingerlistcmd::destroy(coldstartsingerlistcmd* v){
if(v){
bsl::mempool *pool=v->_pool;
v->~coldstartsingerlistcmd();
pool->free(v,sizeof(*v));
}
}
inline coldstartsingerlistcmd::coldstartsingerlistcmd(bsl::mempool *pool): 
::idl::McpackBean(pool),
_pool(pool)
,_m_ch_name(_pool)
,_unknown(_pool){
memset(_flag,0,sizeof(_flag));
}
inline coldstartsingerlistcmd::coldstartsingerlistcmd(const coldstartsingerlistcmd& v): 
::idl::McpackBean(v._pool),
_pool(v._pool)
,_m_ch_name(_pool)
,_unknown(_pool){
assign(v);
}
inline coldstartsingerlistcmd::~coldstartsingerlistcmd(){
}
inline coldstartsingerlistcmd& coldstartsingerlistcmd::operator=(const coldstartsingerlistcmd& v){
assign(v);
return *this;
}
inline void coldstartsingerlistcmd::clear(){
_m_ch_name.clear();
memset(_flag,0,sizeof(_flag));
_unknown.clear(); 
::idl::McpackBean::clear();
}
// @@CF(constraint functions).
inline void coldstartsingerlistcmd::check() const{
// @@string ch_name;
if(!(_flag[0 >> 3] & (1 << (0 & 0x7)))){
throw bsl::KeyNotFoundException() << BSL_EARG << "key '" << "ch_name" << "' not found";
}
{
__attribute__((unused)) const char* item=_m_ch_name.get();

}

::idl::McpackBean::check();
}
inline void coldstartsingerlistcmd::detach(){
_m_ch_name.detach();
_unknown.clear();

::idl::McpackBean::detach();
}
inline coldstartsingerlistcmd& coldstartsingerlistcmd::assign(const coldstartsingerlistcmd& v){
_m_ch_name=v._m_ch_name;
_unknown=v._unknown;
bsl::xmemcpy(_flag,v._flag,sizeof(v._flag));
return *this;
}
inline bool coldstartsingerlistcmd::has_ch_name() const{
return (_flag[0 >> 3] & (1 << (0 & 0x7)));
}
inline const char* coldstartsingerlistcmd::ch_name(unsigned int* size) const{
return _m_ch_name.get(size);
}
inline coldstartsingerlistcmd& coldstartsingerlistcmd::set_ch_name(const char* s,ssize_t size){
_flag[0 >> 3] |= (1 << (0 & 0x7));
 _m_ch_name.set(s,(size==-1)?strlen(s):(size_t)size);
return *this;
}
inline coldstartsingerlistcmd& coldstartsingerlistcmd::set_ptr_ch_name(const char* s,ssize_t size){
_flag[0 >> 3] |= (1 << (0 & 0x7));
 _m_ch_name.set_ptr(s,(size==-1)?strlen(s):(size_t)size);
return *this;
}
inline ::idl::Unknown* coldstartsingerlistcmd::mutable_unknown(){
return &_unknown;
}
inline const ::idl::Unknown& coldstartsingerlistcmd::unknown() const{
return _unknown;
}
inline ::idl::Unknown& coldstartsingerlistcmd::unknown(){
return _unknown;
}
inline size_t coldstartsingerlistcmd::unknown_size() const{
return _unknown.size();
}
inline newusercmd* newusercmd::create(bsl::mempool* pool){
if(!pool){
throw bsl::NullPointerException() << BSL_EARG;
}
newusercmd* tmp=(newusercmd*)pool->malloc(sizeof(*tmp));
if(!tmp){
throw bsl::BadAllocException() << BSL_EARG;
}
new(tmp)newusercmd(pool);
return tmp;
}
inline void newusercmd::destroy(newusercmd* v){
if(v){
bsl::mempool *pool=v->_pool;
v->~newusercmd();
pool->free(v,sizeof(*v));
}
}
inline newusercmd::newusercmd(bsl::mempool *pool): 
::idl::McpackBean(pool),
_pool(pool)
,_m_ch_name(_pool)
,_unknown(_pool){
memset(_flag,0,sizeof(_flag));
}
inline newusercmd::newusercmd(const newusercmd& v): 
::idl::McpackBean(v._pool),
_pool(v._pool)
,_m_ch_name(_pool)
,_unknown(_pool){
assign(v);
}
inline newusercmd::~newusercmd(){
}
inline newusercmd& newusercmd::operator=(const newusercmd& v){
assign(v);
return *this;
}
inline void newusercmd::clear(){
_m_ch_name.clear();
memset(_flag,0,sizeof(_flag));
_unknown.clear(); 
::idl::McpackBean::clear();
}
// @@CF(constraint functions).
inline void newusercmd::check() const{
// @@string ch_name;
if(!(_flag[0 >> 3] & (1 << (0 & 0x7)))){
throw bsl::KeyNotFoundException() << BSL_EARG << "key '" << "ch_name" << "' not found";
}
{
__attribute__((unused)) const char* item=_m_ch_name.get();

}

::idl::McpackBean::check();
}
inline void newusercmd::detach(){
_m_ch_name.detach();
_unknown.clear();

::idl::McpackBean::detach();
}
inline newusercmd& newusercmd::assign(const newusercmd& v){
_m_ch_name=v._m_ch_name;
_unknown=v._unknown;
bsl::xmemcpy(_flag,v._flag,sizeof(v._flag));
return *this;
}
inline bool newusercmd::has_ch_name() const{
return (_flag[0 >> 3] & (1 << (0 & 0x7)));
}
inline const char* newusercmd::ch_name(unsigned int* size) const{
return _m_ch_name.get(size);
}
inline newusercmd& newusercmd::set_ch_name(const char* s,ssize_t size){
_flag[0 >> 3] |= (1 << (0 & 0x7));
 _m_ch_name.set(s,(size==-1)?strlen(s):(size_t)size);
return *this;
}
inline newusercmd& newusercmd::set_ptr_ch_name(const char* s,ssize_t size){
_flag[0 >> 3] |= (1 << (0 & 0x7));
 _m_ch_name.set_ptr(s,(size==-1)?strlen(s):(size_t)size);
return *this;
}
inline ::idl::Unknown* newusercmd::mutable_unknown(){
return &_unknown;
}
inline const ::idl::Unknown& newusercmd::unknown() const{
return _unknown;
}
inline ::idl::Unknown& newusercmd::unknown(){
return _unknown;
}
inline size_t newusercmd::unknown_size() const{
return _unknown.size();
}
inline usertagscmd* usertagscmd::create(bsl::mempool* pool){
if(!pool){
throw bsl::NullPointerException() << BSL_EARG;
}
usertagscmd* tmp=(usertagscmd*)pool->malloc(sizeof(*tmp));
if(!tmp){
throw bsl::BadAllocException() << BSL_EARG;
}
new(tmp)usertagscmd(pool);
return tmp;
}
inline void usertagscmd::destroy(usertagscmd* v){
if(v){
bsl::mempool *pool=v->_pool;
v->~usertagscmd();
pool->free(v,sizeof(*v));
}
}
inline usertagscmd::usertagscmd(bsl::mempool *pool): 
::idl::McpackBean(pool),
_pool(pool)
,_m_src(0)
,_unknown(_pool){
memset(_flag,0,sizeof(_flag));
}
inline usertagscmd::usertagscmd(const usertagscmd& v): 
::idl::McpackBean(v._pool),
_pool(v._pool)
,_m_src(0)
,_unknown(_pool){
assign(v);
}
inline usertagscmd::~usertagscmd(){
}
inline usertagscmd& usertagscmd::operator=(const usertagscmd& v){
assign(v);
return *this;
}
inline void usertagscmd::clear(){
// _m_src=0;
memset(_flag,0,sizeof(_flag));
_unknown.clear(); 
::idl::McpackBean::clear();
}
// @@CF(constraint functions).
inline void usertagscmd::check() const{
// @@uint32_t src;
if(!(_flag[0 >> 3] & (1 << (0 & 0x7)))){
throw bsl::KeyNotFoundException() << BSL_EARG << "key '" << "src" << "' not found";
}
{
__attribute__((unused)) uint32_t item=_m_src;

}

::idl::McpackBean::check();
}
inline void usertagscmd::detach(){
_unknown.clear();

::idl::McpackBean::detach();
}
inline usertagscmd& usertagscmd::assign(const usertagscmd& v){
_m_src=v._m_src;
_unknown=v._unknown;
bsl::xmemcpy(_flag,v._flag,sizeof(v._flag));
return *this;
}
inline bool usertagscmd::has_src() const{
return (_flag[0 >> 3] & (1 << (0 & 0x7)));
}
inline uint32_t usertagscmd::src() const{
return _m_src;
}
inline usertagscmd& usertagscmd::set_src(uint32_t v){
_flag[0 >> 3] |= (1 << (0 & 0x7));
 _m_src=v;
return *this;
}
inline ::idl::Unknown* usertagscmd::mutable_unknown(){
return &_unknown;
}
inline const ::idl::Unknown& usertagscmd::unknown() const{
return _unknown;
}
inline ::idl::Unknown& usertagscmd::unknown(){
return _unknown;
}
inline size_t usertagscmd::unknown_size() const{
return _unknown.size();
}
inline cmd* cmd::create(bsl::mempool* pool){
if(!pool){
throw bsl::NullPointerException() << BSL_EARG;
}
cmd* tmp=(cmd*)pool->malloc(sizeof(*tmp));
if(!tmp){
throw bsl::BadAllocException() << BSL_EARG;
}
new(tmp)cmd(pool);
return tmp;
}
inline void cmd::destroy(cmd* v){
if(v){
bsl::mempool *pool=v->_pool;
v->~cmd();
pool->free(v,sizeof(*v));
}
}
inline cmd::cmd(bsl::mempool *pool): 
::idl::McpackBean(pool),
_pool(pool)
,_m_rf(0)
,_m_username(_pool)
,_m_uid(0)
,_m_baiduid(_pool)
,_m_pc(0)
,_m_fc(0)
,_m_mc(0)
,_m_cc(0)
,_m_lc(0)
,_m_chlc(0)
,_m_plc(0)
,_m_pac(0)
,_m_crc(0)
,_m_cslc(0)
,_m_nuc(0)
,_m_utag_cmd(0)
,_m_tic(0)
,_m_piao(0)
,_unknown(_pool){
_m_pc=::idl::playercmd::create(_pool);
_m_fc=::idl::findcmd::create(_pool);
_m_mc=::idl::mgrcmd::create(_pool);
_m_cc=::idl::cntcmd::create(_pool);
_m_lc=::idl::listcmd::create(_pool);
_m_chlc=::idl::chlistcmd::create(_pool);
_m_plc=::idl::playlistcmd::create(_pool);
_m_pac=::idl::playactioncmd::create(_pool);
_m_crc=::idl::coldstartreqcmd::create(_pool);
_m_cslc=::idl::coldstartsingerlistcmd::create(_pool);
_m_nuc=::idl::newusercmd::create(_pool);
_m_utag_cmd=::idl::usertagscmd::create(_pool);
_m_tic=::idl::ticketcmd::create(_pool);
_m_piao=::idl::piaocmd::create(_pool);
memset(_flag,0,sizeof(_flag));
}
inline cmd::cmd(const cmd& v): 
::idl::McpackBean(v._pool),
_pool(v._pool)
,_m_rf(0)
,_m_username(_pool)
,_m_uid(0)
,_m_baiduid(_pool)
,_m_pc(0)
,_m_fc(0)
,_m_mc(0)
,_m_cc(0)
,_m_lc(0)
,_m_chlc(0)
,_m_plc(0)
,_m_pac(0)
,_m_crc(0)
,_m_cslc(0)
,_m_nuc(0)
,_m_utag_cmd(0)
,_m_tic(0)
,_m_piao(0)
,_unknown(_pool){
_m_pc=::idl::playercmd::create(_pool);
_m_fc=::idl::findcmd::create(_pool);
_m_mc=::idl::mgrcmd::create(_pool);
_m_cc=::idl::cntcmd::create(_pool);
_m_lc=::idl::listcmd::create(_pool);
_m_chlc=::idl::chlistcmd::create(_pool);
_m_plc=::idl::playlistcmd::create(_pool);
_m_pac=::idl::playactioncmd::create(_pool);
_m_crc=::idl::coldstartreqcmd::create(_pool);
_m_cslc=::idl::coldstartsingerlistcmd::create(_pool);
_m_nuc=::idl::newusercmd::create(_pool);
_m_utag_cmd=::idl::usertagscmd::create(_pool);
_m_tic=::idl::ticketcmd::create(_pool);
_m_piao=::idl::piaocmd::create(_pool);
assign(v);
}
inline cmd::~cmd(){
if(_m_pc){
::idl::playercmd::destroy(_m_pc);
_m_pc=0;
}
if(_m_fc){
::idl::findcmd::destroy(_m_fc);
_m_fc=0;
}
if(_m_mc){
::idl::mgrcmd::destroy(_m_mc);
_m_mc=0;
}
if(_m_cc){
::idl::cntcmd::destroy(_m_cc);
_m_cc=0;
}
if(_m_lc){
::idl::listcmd::destroy(_m_lc);
_m_lc=0;
}
if(_m_chlc){
::idl::chlistcmd::destroy(_m_chlc);
_m_chlc=0;
}
if(_m_plc){
::idl::playlistcmd::destroy(_m_plc);
_m_plc=0;
}
if(_m_pac){
::idl::playactioncmd::destroy(_m_pac);
_m_pac=0;
}
if(_m_crc){
::idl::coldstartreqcmd::destroy(_m_crc);
_m_crc=0;
}
if(_m_cslc){
::idl::coldstartsingerlistcmd::destroy(_m_cslc);
_m_cslc=0;
}
if(_m_nuc){
::idl::newusercmd::destroy(_m_nuc);
_m_nuc=0;
}
if(_m_utag_cmd){
::idl::usertagscmd::destroy(_m_utag_cmd);
_m_utag_cmd=0;
}
if(_m_tic){
::idl::ticketcmd::destroy(_m_tic);
_m_tic=0;
}
if(_m_piao){
::idl::piaocmd::destroy(_m_piao);
_m_piao=0;
}
}
inline cmd& cmd::operator=(const cmd& v){
assign(v);
return *this;
}
inline void cmd::clear(){
// _m_rf=0;
_m_username.clear();
// _m_uid=0;
_m_baiduid.clear();
if(_m_pc){
_m_pc->clear();
}
if(_m_fc){
_m_fc->clear();
}
if(_m_mc){
_m_mc->clear();
}
if(_m_cc){
_m_cc->clear();
}
if(_m_lc){
_m_lc->clear();
}
if(_m_chlc){
_m_chlc->clear();
}
if(_m_plc){
_m_plc->clear();
}
if(_m_pac){
_m_pac->clear();
}
if(_m_crc){
_m_crc->clear();
}
if(_m_cslc){
_m_cslc->clear();
}
if(_m_nuc){
_m_nuc->clear();
}
if(_m_utag_cmd){
_m_utag_cmd->clear();
}
if(_m_tic){
_m_tic->clear();
}
if(_m_piao){
_m_piao->clear();
}
memset(_flag,0,sizeof(_flag));
_unknown.clear(); 
::idl::McpackBean::clear();
}
// @@CF(constraint functions).
inline void cmd::check() const{
// @@int32_t rf=default(-1);
if(!(_flag[0 >> 3] & (1 << (0 & 0x7)))){
throw bsl::KeyNotFoundException() << BSL_EARG << "key '" << "rf" << "' not found";
}
{
__attribute__((unused)) int32_t item=_m_rf;

}
// @@string username=default("");
if(!(_flag[1 >> 3] & (1 << (1 & 0x7)))){
throw bsl::KeyNotFoundException() << BSL_EARG << "key '" << "username" << "' not found";
}
{
__attribute__((unused)) const char* item=_m_username.get();

}
// @@uint32_t uid=default(0);
if(!(_flag[2 >> 3] & (1 << (2 & 0x7)))){
throw bsl::KeyNotFoundException() << BSL_EARG << "key '" << "uid" << "' not found";
}
{
__attribute__((unused)) uint32_t item=_m_uid;

}
// @@string baiduid=default("");
if(!(_flag[3 >> 3] & (1 << (3 & 0x7)))){
throw bsl::KeyNotFoundException() << BSL_EARG << "key '" << "baiduid" << "' not found";
}
{
__attribute__((unused)) const char* item=_m_baiduid.get();

}
// @@playercmd pc=optional();
if((_flag[4 >> 3] & (1 << (4 & 0x7)))){
{
::idl::playercmd& item=const_cast< ::idl::playercmd& >(*_m_pc);
item.check();

}
}    
// @@findcmd fc=optional();
if((_flag[5 >> 3] & (1 << (5 & 0x7)))){
{
::idl::findcmd& item=const_cast< ::idl::findcmd& >(*_m_fc);
item.check();

}
}    
// @@mgrcmd mc=optional();
if((_flag[6 >> 3] & (1 << (6 & 0x7)))){
{
::idl::mgrcmd& item=const_cast< ::idl::mgrcmd& >(*_m_mc);
item.check();

}
}    
// @@cntcmd cc=optional();
if((_flag[7 >> 3] & (1 << (7 & 0x7)))){
{
::idl::cntcmd& item=const_cast< ::idl::cntcmd& >(*_m_cc);
item.check();

}
}    
// @@listcmd lc=optional();
if((_flag[8 >> 3] & (1 << (8 & 0x7)))){
{
::idl::listcmd& item=const_cast< ::idl::listcmd& >(*_m_lc);
item.check();

}
}    
// @@chlistcmd chlc=optional();
if((_flag[9 >> 3] & (1 << (9 & 0x7)))){
{
::idl::chlistcmd& item=const_cast< ::idl::chlistcmd& >(*_m_chlc);
item.check();

}
}    
// @@playlistcmd plc=optional();
if((_flag[10 >> 3] & (1 << (10 & 0x7)))){
{
::idl::playlistcmd& item=const_cast< ::idl::playlistcmd& >(*_m_plc);
item.check();

}
}    
// @@playactioncmd pac=optional();
if((_flag[11 >> 3] & (1 << (11 & 0x7)))){
{
::idl::playactioncmd& item=const_cast< ::idl::playactioncmd& >(*_m_pac);
item.check();

}
}    
// @@coldstartreqcmd crc=optional();
if((_flag[12 >> 3] & (1 << (12 & 0x7)))){
{
::idl::coldstartreqcmd& item=const_cast< ::idl::coldstartreqcmd& >(*_m_crc);
item.check();

}
}    
// @@coldstartsingerlistcmd cslc=optional();
if((_flag[13 >> 3] & (1 << (13 & 0x7)))){
{
::idl::coldstartsingerlistcmd& item=const_cast< ::idl::coldstartsingerlistcmd& >(*_m_cslc);
item.check();

}
}    
// @@newusercmd nuc=optional();
if((_flag[14 >> 3] & (1 << (14 & 0x7)))){
{
::idl::newusercmd& item=const_cast< ::idl::newusercmd& >(*_m_nuc);
item.check();

}
}    
// @@usertagscmd utag_cmd=optional();
if((_flag[15 >> 3] & (1 << (15 & 0x7)))){
{
::idl::usertagscmd& item=const_cast< ::idl::usertagscmd& >(*_m_utag_cmd);
item.check();

}
}    
// @@ticketcmd tic=optional();
if((_flag[16 >> 3] & (1 << (16 & 0x7)))){
{
::idl::ticketcmd& item=const_cast< ::idl::ticketcmd& >(*_m_tic);
item.check();

}
}    
// @@piaocmd piao=optional();
if((_flag[17 >> 3] & (1 << (17 & 0x7)))){
{
::idl::piaocmd& item=const_cast< ::idl::piaocmd& >(*_m_piao);
item.check();

}
}    

::idl::McpackBean::check();
}
inline void cmd::detach(){
_m_username.detach();
_m_baiduid.detach();
if(_m_pc){
_m_pc->detach();
}
if(_m_fc){
_m_fc->detach();
}
if(_m_mc){
_m_mc->detach();
}
if(_m_cc){
_m_cc->detach();
}
if(_m_lc){
_m_lc->detach();
}
if(_m_chlc){
_m_chlc->detach();
}
if(_m_plc){
_m_plc->detach();
}
if(_m_pac){
_m_pac->detach();
}
if(_m_crc){
_m_crc->detach();
}
if(_m_cslc){
_m_cslc->detach();
}
if(_m_nuc){
_m_nuc->detach();
}
if(_m_utag_cmd){
_m_utag_cmd->detach();
}
if(_m_tic){
_m_tic->detach();
}
if(_m_piao){
_m_piao->detach();
}
_unknown.clear();

::idl::McpackBean::detach();
}
inline cmd& cmd::assign(const cmd& v){
_m_rf=v._m_rf;
_m_username=v._m_username;
_m_uid=v._m_uid;
_m_baiduid=v._m_baiduid;
if(!v._m_pc){
if(_m_pc){
::idl::playercmd::destroy(_m_pc);
}
_m_pc=0;
}else{
if(!_m_pc){
_m_pc=::idl::playercmd::create(_pool);
}
*_m_pc=*v._m_pc;
}
if(!v._m_fc){
if(_m_fc){
::idl::findcmd::destroy(_m_fc);
}
_m_fc=0;
}else{
if(!_m_fc){
_m_fc=::idl::findcmd::create(_pool);
}
*_m_fc=*v._m_fc;
}
if(!v._m_mc){
if(_m_mc){
::idl::mgrcmd::destroy(_m_mc);
}
_m_mc=0;
}else{
if(!_m_mc){
_m_mc=::idl::mgrcmd::create(_pool);
}
*_m_mc=*v._m_mc;
}
if(!v._m_cc){
if(_m_cc){
::idl::cntcmd::destroy(_m_cc);
}
_m_cc=0;
}else{
if(!_m_cc){
_m_cc=::idl::cntcmd::create(_pool);
}
*_m_cc=*v._m_cc;
}
if(!v._m_lc){
if(_m_lc){
::idl::listcmd::destroy(_m_lc);
}
_m_lc=0;
}else{
if(!_m_lc){
_m_lc=::idl::listcmd::create(_pool);
}
*_m_lc=*v._m_lc;
}
if(!v._m_chlc){
if(_m_chlc){
::idl::chlistcmd::destroy(_m_chlc);
}
_m_chlc=0;
}else{
if(!_m_chlc){
_m_chlc=::idl::chlistcmd::create(_pool);
}
*_m_chlc=*v._m_chlc;
}
if(!v._m_plc){
if(_m_plc){
::idl::playlistcmd::destroy(_m_plc);
}
_m_plc=0;
}else{
if(!_m_plc){
_m_plc=::idl::playlistcmd::create(_pool);
}
*_m_plc=*v._m_plc;
}
if(!v._m_pac){
if(_m_pac){
::idl::playactioncmd::destroy(_m_pac);
}
_m_pac=0;
}else{
if(!_m_pac){
_m_pac=::idl::playactioncmd::create(_pool);
}
*_m_pac=*v._m_pac;
}
if(!v._m_crc){
if(_m_crc){
::idl::coldstartreqcmd::destroy(_m_crc);
}
_m_crc=0;
}else{
if(!_m_crc){
_m_crc=::idl::coldstartreqcmd::create(_pool);
}
*_m_crc=*v._m_crc;
}
if(!v._m_cslc){
if(_m_cslc){
::idl::coldstartsingerlistcmd::destroy(_m_cslc);
}
_m_cslc=0;
}else{
if(!_m_cslc){
_m_cslc=::idl::coldstartsingerlistcmd::create(_pool);
}
*_m_cslc=*v._m_cslc;
}
if(!v._m_nuc){
if(_m_nuc){
::idl::newusercmd::destroy(_m_nuc);
}
_m_nuc=0;
}else{
if(!_m_nuc){
_m_nuc=::idl::newusercmd::create(_pool);
}
*_m_nuc=*v._m_nuc;
}
if(!v._m_utag_cmd){
if(_m_utag_cmd){
::idl::usertagscmd::destroy(_m_utag_cmd);
}
_m_utag_cmd=0;
}else{
if(!_m_utag_cmd){
_m_utag_cmd=::idl::usertagscmd::create(_pool);
}
*_m_utag_cmd=*v._m_utag_cmd;
}
if(!v._m_tic){
if(_m_tic){
::idl::ticketcmd::destroy(_m_tic);
}
_m_tic=0;
}else{
if(!_m_tic){
_m_tic=::idl::ticketcmd::create(_pool);
}
*_m_tic=*v._m_tic;
}
if(!v._m_piao){
if(_m_piao){
::idl::piaocmd::destroy(_m_piao);
}
_m_piao=0;
}else{
if(!_m_piao){
_m_piao=::idl::piaocmd::create(_pool);
}
*_m_piao=*v._m_piao;
}
_unknown=v._unknown;
bsl::xmemcpy(_flag,v._flag,sizeof(v._flag));
return *this;
}
inline bool cmd::has_rf() const{
return (_flag[0 >> 3] & (1 << (0 & 0x7)));
}
inline int32_t cmd::rf() const{
return _m_rf;
}
inline cmd& cmd::set_rf(int32_t v){
_flag[0 >> 3] |= (1 << (0 & 0x7));
 _m_rf=v;
return *this;
}
inline bool cmd::has_username() const{
return (_flag[1 >> 3] & (1 << (1 & 0x7)));
}
inline const char* cmd::username(unsigned int* size) const{
return _m_username.get(size);
}
inline cmd& cmd::set_username(const char* s,ssize_t size){
_flag[1 >> 3] |= (1 << (1 & 0x7));
 _m_username.set(s,(size==-1)?strlen(s):(size_t)size);
return *this;
}
inline cmd& cmd::set_ptr_username(const char* s,ssize_t size){
_flag[1 >> 3] |= (1 << (1 & 0x7));
 _m_username.set_ptr(s,(size==-1)?strlen(s):(size_t)size);
return *this;
}
inline bool cmd::has_uid() const{
return (_flag[2 >> 3] & (1 << (2 & 0x7)));
}
inline uint32_t cmd::uid() const{
return _m_uid;
}
inline cmd& cmd::set_uid(uint32_t v){
_flag[2 >> 3] |= (1 << (2 & 0x7));
 _m_uid=v;
return *this;
}
inline bool cmd::has_baiduid() const{
return (_flag[3 >> 3] & (1 << (3 & 0x7)));
}
inline const char* cmd::baiduid(unsigned int* size) const{
return _m_baiduid.get(size);
}
inline cmd& cmd::set_baiduid(const char* s,ssize_t size){
_flag[3 >> 3] |= (1 << (3 & 0x7));
 _m_baiduid.set(s,(size==-1)?strlen(s):(size_t)size);
return *this;
}
inline cmd& cmd::set_ptr_baiduid(const char* s,ssize_t size){
_flag[3 >> 3] |= (1 << (3 & 0x7));
 _m_baiduid.set_ptr(s,(size==-1)?strlen(s):(size_t)size);
return *this;
}
inline bool cmd::has_pc() const{
return (_flag[4 >> 3] & (1 << (4 & 0x7)));
}
inline const ::idl::playercmd& cmd::pc() const{
if(!(_flag[4 >> 3] & (1 << (4 & 0x7)))){
throw bsl::KeyNotFoundException() << BSL_EARG;
}
 return *_m_pc;
}
inline ::idl::playercmd* cmd::mutable_pc(){
_flag[4 >> 3] |= (1 << (4 & 0x7));
 if(!_m_pc){
_m_pc=::idl::playercmd::create(_pool);
}
return _m_pc;
}
inline ::idl::playercmd* cmd::m_pc(){
_flag[4 >> 3] |= (1 << (4 & 0x7));
 if(!_m_pc){
_m_pc=::idl::playercmd::create(_pool);
}
return _m_pc;
}
inline bool cmd::has_fc() const{
return (_flag[5 >> 3] & (1 << (5 & 0x7)));
}
inline const ::idl::findcmd& cmd::fc() const{
if(!(_flag[5 >> 3] & (1 << (5 & 0x7)))){
throw bsl::KeyNotFoundException() << BSL_EARG;
}
 return *_m_fc;
}
inline ::idl::findcmd* cmd::mutable_fc(){
_flag[5 >> 3] |= (1 << (5 & 0x7));
 if(!_m_fc){
_m_fc=::idl::findcmd::create(_pool);
}
return _m_fc;
}
inline ::idl::findcmd* cmd::m_fc(){
_flag[5 >> 3] |= (1 << (5 & 0x7));
 if(!_m_fc){
_m_fc=::idl::findcmd::create(_pool);
}
return _m_fc;
}
inline bool cmd::has_mc() const{
return (_flag[6 >> 3] & (1 << (6 & 0x7)));
}
inline const ::idl::mgrcmd& cmd::mc() const{
if(!(_flag[6 >> 3] & (1 << (6 & 0x7)))){
throw bsl::KeyNotFoundException() << BSL_EARG;
}
 return *_m_mc;
}
inline ::idl::mgrcmd* cmd::mutable_mc(){
_flag[6 >> 3] |= (1 << (6 & 0x7));
 if(!_m_mc){
_m_mc=::idl::mgrcmd::create(_pool);
}
return _m_mc;
}
inline ::idl::mgrcmd* cmd::m_mc(){
_flag[6 >> 3] |= (1 << (6 & 0x7));
 if(!_m_mc){
_m_mc=::idl::mgrcmd::create(_pool);
}
return _m_mc;
}
inline bool cmd::has_cc() const{
return (_flag[7 >> 3] & (1 << (7 & 0x7)));
}
inline const ::idl::cntcmd& cmd::cc() const{
if(!(_flag[7 >> 3] & (1 << (7 & 0x7)))){
throw bsl::KeyNotFoundException() << BSL_EARG;
}
 return *_m_cc;
}
inline ::idl::cntcmd* cmd::mutable_cc(){
_flag[7 >> 3] |= (1 << (7 & 0x7));
 if(!_m_cc){
_m_cc=::idl::cntcmd::create(_pool);
}
return _m_cc;
}
inline ::idl::cntcmd* cmd::m_cc(){
_flag[7 >> 3] |= (1 << (7 & 0x7));
 if(!_m_cc){
_m_cc=::idl::cntcmd::create(_pool);
}
return _m_cc;
}
inline bool cmd::has_lc() const{
return (_flag[8 >> 3] & (1 << (8 & 0x7)));
}
inline const ::idl::listcmd& cmd::lc() const{
if(!(_flag[8 >> 3] & (1 << (8 & 0x7)))){
throw bsl::KeyNotFoundException() << BSL_EARG;
}
 return *_m_lc;
}
inline ::idl::listcmd* cmd::mutable_lc(){
_flag[8 >> 3] |= (1 << (8 & 0x7));
 if(!_m_lc){
_m_lc=::idl::listcmd::create(_pool);
}
return _m_lc;
}
inline ::idl::listcmd* cmd::m_lc(){
_flag[8 >> 3] |= (1 << (8 & 0x7));
 if(!_m_lc){
_m_lc=::idl::listcmd::create(_pool);
}
return _m_lc;
}
inline bool cmd::has_chlc() const{
return (_flag[9 >> 3] & (1 << (9 & 0x7)));
}
inline const ::idl::chlistcmd& cmd::chlc() const{
if(!(_flag[9 >> 3] & (1 << (9 & 0x7)))){
throw bsl::KeyNotFoundException() << BSL_EARG;
}
 return *_m_chlc;
}
inline ::idl::chlistcmd* cmd::mutable_chlc(){
_flag[9 >> 3] |= (1 << (9 & 0x7));
 if(!_m_chlc){
_m_chlc=::idl::chlistcmd::create(_pool);
}
return _m_chlc;
}
inline ::idl::chlistcmd* cmd::m_chlc(){
_flag[9 >> 3] |= (1 << (9 & 0x7));
 if(!_m_chlc){
_m_chlc=::idl::chlistcmd::create(_pool);
}
return _m_chlc;
}
inline bool cmd::has_plc() const{
return (_flag[10 >> 3] & (1 << (10 & 0x7)));
}
inline const ::idl::playlistcmd& cmd::plc() const{
if(!(_flag[10 >> 3] & (1 << (10 & 0x7)))){
throw bsl::KeyNotFoundException() << BSL_EARG;
}
 return *_m_plc;
}
inline ::idl::playlistcmd* cmd::mutable_plc(){
_flag[10 >> 3] |= (1 << (10 & 0x7));
 if(!_m_plc){
_m_plc=::idl::playlistcmd::create(_pool);
}
return _m_plc;
}
inline ::idl::playlistcmd* cmd::m_plc(){
_flag[10 >> 3] |= (1 << (10 & 0x7));
 if(!_m_plc){
_m_plc=::idl::playlistcmd::create(_pool);
}
return _m_plc;
}
inline bool cmd::has_pac() const{
return (_flag[11 >> 3] & (1 << (11 & 0x7)));
}
inline const ::idl::playactioncmd& cmd::pac() const{
if(!(_flag[11 >> 3] & (1 << (11 & 0x7)))){
throw bsl::KeyNotFoundException() << BSL_EARG;
}
 return *_m_pac;
}
inline ::idl::playactioncmd* cmd::mutable_pac(){
_flag[11 >> 3] |= (1 << (11 & 0x7));
 if(!_m_pac){
_m_pac=::idl::playactioncmd::create(_pool);
}
return _m_pac;
}
inline ::idl::playactioncmd* cmd::m_pac(){
_flag[11 >> 3] |= (1 << (11 & 0x7));
 if(!_m_pac){
_m_pac=::idl::playactioncmd::create(_pool);
}
return _m_pac;
}
inline bool cmd::has_crc() const{
return (_flag[12 >> 3] & (1 << (12 & 0x7)));
}
inline const ::idl::coldstartreqcmd& cmd::crc() const{
if(!(_flag[12 >> 3] & (1 << (12 & 0x7)))){
throw bsl::KeyNotFoundException() << BSL_EARG;
}
 return *_m_crc;
}
inline ::idl::coldstartreqcmd* cmd::mutable_crc(){
_flag[12 >> 3] |= (1 << (12 & 0x7));
 if(!_m_crc){
_m_crc=::idl::coldstartreqcmd::create(_pool);
}
return _m_crc;
}
inline ::idl::coldstartreqcmd* cmd::m_crc(){
_flag[12 >> 3] |= (1 << (12 & 0x7));
 if(!_m_crc){
_m_crc=::idl::coldstartreqcmd::create(_pool);
}
return _m_crc;
}
inline bool cmd::has_cslc() const{
return (_flag[13 >> 3] & (1 << (13 & 0x7)));
}
inline const ::idl::coldstartsingerlistcmd& cmd::cslc() const{
if(!(_flag[13 >> 3] & (1 << (13 & 0x7)))){
throw bsl::KeyNotFoundException() << BSL_EARG;
}
 return *_m_cslc;
}
inline ::idl::coldstartsingerlistcmd* cmd::mutable_cslc(){
_flag[13 >> 3] |= (1 << (13 & 0x7));
 if(!_m_cslc){
_m_cslc=::idl::coldstartsingerlistcmd::create(_pool);
}
return _m_cslc;
}
inline ::idl::coldstartsingerlistcmd* cmd::m_cslc(){
_flag[13 >> 3] |= (1 << (13 & 0x7));
 if(!_m_cslc){
_m_cslc=::idl::coldstartsingerlistcmd::create(_pool);
}
return _m_cslc;
}
inline bool cmd::has_nuc() const{
return (_flag[14 >> 3] & (1 << (14 & 0x7)));
}
inline const ::idl::newusercmd& cmd::nuc() const{
if(!(_flag[14 >> 3] & (1 << (14 & 0x7)))){
throw bsl::KeyNotFoundException() << BSL_EARG;
}
 return *_m_nuc;
}
inline ::idl::newusercmd* cmd::mutable_nuc(){
_flag[14 >> 3] |= (1 << (14 & 0x7));
 if(!_m_nuc){
_m_nuc=::idl::newusercmd::create(_pool);
}
return _m_nuc;
}
inline ::idl::newusercmd* cmd::m_nuc(){
_flag[14 >> 3] |= (1 << (14 & 0x7));
 if(!_m_nuc){
_m_nuc=::idl::newusercmd::create(_pool);
}
return _m_nuc;
}
inline bool cmd::has_utag_cmd() const{
return (_flag[15 >> 3] & (1 << (15 & 0x7)));
}
inline const ::idl::usertagscmd& cmd::utag_cmd() const{
if(!(_flag[15 >> 3] & (1 << (15 & 0x7)))){
throw bsl::KeyNotFoundException() << BSL_EARG;
}
 return *_m_utag_cmd;
}
inline ::idl::usertagscmd* cmd::mutable_utag_cmd(){
_flag[15 >> 3] |= (1 << (15 & 0x7));
 if(!_m_utag_cmd){
_m_utag_cmd=::idl::usertagscmd::create(_pool);
}
return _m_utag_cmd;
}
inline ::idl::usertagscmd* cmd::m_utag_cmd(){
_flag[15 >> 3] |= (1 << (15 & 0x7));
 if(!_m_utag_cmd){
_m_utag_cmd=::idl::usertagscmd::create(_pool);
}
return _m_utag_cmd;
}
inline bool cmd::has_tic() const{
return (_flag[16 >> 3] & (1 << (16 & 0x7)));
}
inline const ::idl::ticketcmd& cmd::tic() const{
if(!(_flag[16 >> 3] & (1 << (16 & 0x7)))){
throw bsl::KeyNotFoundException() << BSL_EARG;
}
 return *_m_tic;
}
inline ::idl::ticketcmd* cmd::mutable_tic(){
_flag[16 >> 3] |= (1 << (16 & 0x7));
 if(!_m_tic){
_m_tic=::idl::ticketcmd::create(_pool);
}
return _m_tic;
}
inline ::idl::ticketcmd* cmd::m_tic(){
_flag[16 >> 3] |= (1 << (16 & 0x7));
 if(!_m_tic){
_m_tic=::idl::ticketcmd::create(_pool);
}
return _m_tic;
}
inline bool cmd::has_piao() const{
return (_flag[17 >> 3] & (1 << (17 & 0x7)));
}
inline const ::idl::piaocmd& cmd::piao() const{
if(!(_flag[17 >> 3] & (1 << (17 & 0x7)))){
throw bsl::KeyNotFoundException() << BSL_EARG;
}
 return *_m_piao;
}
inline ::idl::piaocmd* cmd::mutable_piao(){
_flag[17 >> 3] |= (1 << (17 & 0x7));
 if(!_m_piao){
_m_piao=::idl::piaocmd::create(_pool);
}
return _m_piao;
}
inline ::idl::piaocmd* cmd::m_piao(){
_flag[17 >> 3] |= (1 << (17 & 0x7));
 if(!_m_piao){
_m_piao=::idl::piaocmd::create(_pool);
}
return _m_piao;
}
inline ::idl::Unknown* cmd::mutable_unknown(){
return &_unknown;
}
inline const ::idl::Unknown& cmd::unknown() const{
return _unknown;
}
inline ::idl::Unknown& cmd::unknown(){
return _unknown;
}
inline size_t cmd::unknown_size() const{
return _unknown.size();
}
} // namespace idl
#endif // IDL_GENERATED_FILE_RLS2_IDL_H_
