#ifndef IDL_GENERATED_FILE_RELOAD_IDL_H_
#define IDL_GENERATED_FILE_RELOAD_IDL_H_
#include "cxx/runtime.h"
namespace idl {
class songinfo;
class setcmd;
class reload_cmd;
class songinfo : public ::idl::IDLObject , public ::idl::McpackBean {
public:
    static songinfo* create(bsl::mempool* pool);
    static void destroy(songinfo* v);
    explicit songinfo(bsl::mempool* pool);
    songinfo(const songinfo& v);
    ~songinfo();
    songinfo& operator=(const songinfo& v);
    void clear();
    void check() const;
    void detach();
    songinfo& assign(const songinfo& v);
    // @@uint32_t itemid;
    inline bool has_itemid() const;
    inline uint32_t itemid() const;
    inline songinfo& set_itemid(uint32_t v);
    // @@int32_t weight;
    inline bool has_weight() const;
    inline int32_t weight() const;
    inline songinfo& set_weight(int32_t v);
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
    int32_t _m_weight;
    mutable ::idl::Unknown _unknown;
    char _flag[1];
}; // class songinfo
class setcmd : public ::idl::IDLObject , public ::idl::McpackBean {
public:
    static setcmd* create(bsl::mempool* pool);
    static void destroy(setcmd* v);
    explicit setcmd(bsl::mempool* pool);
    setcmd(const setcmd& v);
    ~setcmd();
    setcmd& operator=(const setcmd& v);
    void clear();
    void check() const;
    void detach();
    setcmd& assign(const setcmd& v);
    // @@int32_t cmd;
    inline bool has_cmd() const;
    inline int32_t cmd() const;
    inline setcmd& set_cmd(int32_t v);
    // @@songinfo iteminfo=optional(),array(0);
    inline bool has_iteminfo() const;
    inline const ::idl::vector< ::idl::songinfo >& iteminfo() const;
    inline ::idl::vector< ::idl::songinfo >* mutable_iteminfo();
    // deprecated.use 'mutable_iteminfo' instead.
    inline ::idl::vector< ::idl::songinfo >* m_iteminfo();
    // deprecated.use 'iteminfo().size()' instead.
    inline size_t iteminfo_size() const;
    inline const ::idl::songinfo& iteminfo(size_t i0) const;
    inline ::idl::songinfo* mutable_iteminfo(size_t i0);
    // deprecated.use 'mutable_iteminfo' instead.
    inline ::idl::songinfo* m_iteminfo(size_t i0);
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
    int32_t _m_cmd;
    ::idl::vector< ::idl::songinfo > _m_iteminfo;
    mutable ::idl::Unknown _unknown;
    char _flag[1];
}; // class setcmd
class reload_cmd : public ::idl::IDLObject , public ::idl::McpackBean {
public:
    static reload_cmd* create(bsl::mempool* pool);
    static void destroy(reload_cmd* v);
    explicit reload_cmd(bsl::mempool* pool);
    reload_cmd(const reload_cmd& v);
    ~reload_cmd();
    reload_cmd& operator=(const reload_cmd& v);
    void clear();
    void check() const;
    void detach();
    reload_cmd& assign(const reload_cmd& v);
    // @@int32_t rf;
    inline bool has_rf() const;
    inline int32_t rf() const;
    inline reload_cmd& set_rf(int32_t v);
    // @@string username;
    inline bool has_username() const;
    inline const char* username(unsigned int* size=0) const;
    inline reload_cmd& set_username(const char* s,ssize_t size=-1);
    inline reload_cmd& set_ptr_username(const char* s,ssize_t size=-1);
    // @@uint32_t uid;
    inline bool has_uid() const;
    inline uint32_t uid() const;
    inline reload_cmd& set_uid(uint32_t v);
    // @@setcmd sc;
    inline bool has_sc() const;
    inline const ::idl::setcmd& sc() const;
    inline ::idl::setcmd* mutable_sc();
    // deprecated.use 'mutable_sc()' instead.
    inline ::idl::setcmd* m_sc();
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
    mutable ::idl::setcmd* _m_sc;
    mutable ::idl::Unknown _unknown;
    char _flag[1];
}; // class reload_cmd
inline songinfo* songinfo::create(bsl::mempool* pool) {
    if(!pool) {
        throw bsl::NullPointerException() << BSL_EARG;
    }
    songinfo* tmp=(songinfo*)pool->malloc(sizeof(*tmp));
    if(!tmp) {
        throw bsl::BadAllocException() << BSL_EARG;
    }
    new(tmp)songinfo(pool);
    return tmp;
}
inline void songinfo::destroy(songinfo* v) {
    if(v) {
        bsl::mempool* pool=v->_pool;
        v->~songinfo();
        pool->free(v,sizeof(*v));
    }
}
inline songinfo::songinfo(bsl::mempool* pool):
    ::idl::McpackBean(pool),
     _pool(pool)
     ,_m_itemid(0)
     ,_m_weight(0)
     ,_unknown(_pool) {
    memset(_flag,0,sizeof(_flag));
}
inline songinfo::songinfo(const songinfo& v):
    ::idl::McpackBean(v._pool),
     _pool(v._pool)
     ,_m_itemid(0)
     ,_m_weight(0)
     ,_unknown(_pool) {
    assign(v);
}
inline songinfo::~songinfo() {
}
inline songinfo& songinfo::operator=(const songinfo& v) {
    assign(v);
    return *this;
}
inline void songinfo::clear() {
    // _m_itemid=0;
    // _m_weight=0;
    memset(_flag,0,sizeof(_flag));
    _unknown.clear();
    ::idl::McpackBean::clear();
}
// @@CF(constraint functions).
inline void songinfo::check() const {
    // @@uint32_t itemid;
    if(!(_flag[0 >> 3] & (1 << (0 & 0x7)))) {
        throw bsl::KeyNotFoundException() << BSL_EARG << "key '" << "itemid" << "' not found";
    }
    {
        __attribute__((unused)) uint32_t item=_m_itemid;
    }
    // @@int32_t weight;
    if(!(_flag[1 >> 3] & (1 << (1 & 0x7)))) {
        throw bsl::KeyNotFoundException() << BSL_EARG << "key '" << "weight" << "' not found";
    }
    {
        __attribute__((unused)) int32_t item=_m_weight;
    }
    ::idl::McpackBean::check();
}
inline void songinfo::detach() {
    _unknown.clear();
    ::idl::McpackBean::detach();
}
inline songinfo& songinfo::assign(const songinfo& v) {
    _m_itemid=v._m_itemid;
    _m_weight=v._m_weight;
    _unknown=v._unknown;
    bsl::xmemcpy(_flag,v._flag,sizeof(v._flag));
    return *this;
}
inline bool songinfo::has_itemid() const {
    return (_flag[0 >> 3] & (1 << (0 & 0x7)));
}
inline uint32_t songinfo::itemid() const {
    return _m_itemid;
}
inline songinfo& songinfo::set_itemid(uint32_t v) {
    _flag[0 >> 3] |= (1 << (0 & 0x7));
    _m_itemid=v;
    return *this;
}
inline bool songinfo::has_weight() const {
    return (_flag[1 >> 3] & (1 << (1 & 0x7)));
}
inline int32_t songinfo::weight() const {
    return _m_weight;
}
inline songinfo& songinfo::set_weight(int32_t v) {
    _flag[1 >> 3] |= (1 << (1 & 0x7));
    _m_weight=v;
    return *this;
}
inline ::idl::Unknown* songinfo::mutable_unknown() {
    return &_unknown;
}
inline const ::idl::Unknown& songinfo::unknown() const {
    return _unknown;
}
inline ::idl::Unknown& songinfo::unknown() {
    return _unknown;
}
inline size_t songinfo::unknown_size() const {
    return _unknown.size();
}
inline setcmd* setcmd::create(bsl::mempool* pool) {
    if(!pool) {
        throw bsl::NullPointerException() << BSL_EARG;
    }
    setcmd* tmp=(setcmd*)pool->malloc(sizeof(*tmp));
    if(!tmp) {
        throw bsl::BadAllocException() << BSL_EARG;
    }
    new(tmp)setcmd(pool);
    return tmp;
}
inline void setcmd::destroy(setcmd* v) {
    if(v) {
        bsl::mempool* pool=v->_pool;
        v->~setcmd();
        pool->free(v,sizeof(*v));
    }
}
inline setcmd::setcmd(bsl::mempool* pool):
    ::idl::McpackBean(pool),
     _pool(pool)
     ,_m_cmd(0)
     ,_m_iteminfo(_pool)
     ,_unknown(_pool) {
    memset(_flag,0,sizeof(_flag));
}
inline setcmd::setcmd(const setcmd& v):
    ::idl::McpackBean(v._pool),
     _pool(v._pool)
     ,_m_cmd(0)
     ,_m_iteminfo(_pool)
     ,_unknown(_pool) {
    assign(v);
}
inline setcmd::~setcmd() {
}
inline setcmd& setcmd::operator=(const setcmd& v) {
    assign(v);
    return *this;
}
inline void setcmd::clear() {
    // _m_cmd=0;
    _m_iteminfo.clear();
    memset(_flag,0,sizeof(_flag));
    _unknown.clear();
    ::idl::McpackBean::clear();
}
// @@CF(constraint functions).
inline void setcmd::check() const {
    // @@int32_t cmd;
    if(!(_flag[0 >> 3] & (1 << (0 & 0x7)))) {
        throw bsl::KeyNotFoundException() << BSL_EARG << "key '" << "cmd" << "' not found";
    }
    {
        __attribute__((unused)) int32_t item=_m_cmd;
    }
    // @@songinfo iteminfo=optional(),array(0);
    if((_flag[1 >> 3] & (1 << (1 & 0x7)))) {
        {
            // level 0 begin
            typeof(_m_iteminfo)& lr0=(_m_iteminfo);
            __attribute__((unused)) size_t size0=lr0.size();
            for(size_t i0=0; i0<size0; i0++) {
                ::idl::songinfo& item=const_cast< ::idl::songinfo& >(lr0.GetWithoutCheck(i0));
                item.check();
            }
        }
    }
    ::idl::McpackBean::check();
}
inline void setcmd::detach() {
    _m_iteminfo.detach();
    _unknown.clear();
    ::idl::McpackBean::detach();
}
inline setcmd& setcmd::assign(const setcmd& v) {
    _m_cmd=v._m_cmd;
    _m_iteminfo=v._m_iteminfo;
    _unknown=v._unknown;
    bsl::xmemcpy(_flag,v._flag,sizeof(v._flag));
    return *this;
}
inline bool setcmd::has_cmd() const {
    return (_flag[0 >> 3] & (1 << (0 & 0x7)));
}
inline int32_t setcmd::cmd() const {
    return _m_cmd;
}
inline setcmd& setcmd::set_cmd(int32_t v) {
    _flag[0 >> 3] |= (1 << (0 & 0x7));
    _m_cmd=v;
    return *this;
}
inline bool setcmd::has_iteminfo() const {
    return (_flag[1 >> 3] & (1 << (1 & 0x7)));
}
inline const ::idl::vector< ::idl::songinfo >& setcmd::iteminfo() const {
    if(!(_flag[1 >> 3] & (1 << (1 & 0x7)))) {
        throw bsl::KeyNotFoundException() << BSL_EARG;
    }
    return _m_iteminfo;
}
inline ::idl::vector< ::idl::songinfo >* setcmd::mutable_iteminfo() {
    _flag[1 >> 3] |= (1 << (1 & 0x7));
    return &(_m_iteminfo);
}
inline ::idl::vector< ::idl::songinfo >* setcmd::m_iteminfo() {
    _flag[1 >> 3] |= (1 << (1 & 0x7));
    return &(_m_iteminfo);
}
inline size_t setcmd::iteminfo_size() const {
    if(!(_flag[1 >> 3] & (1 << (1 & 0x7)))) {
        throw bsl::KeyNotFoundException() << BSL_EARG;
    }
    return _m_iteminfo.size();
}
inline const ::idl::songinfo& setcmd::iteminfo(size_t i0) const {
    if(!(_flag[1 >> 3] & (1 << (1 & 0x7)))) {
        throw bsl::KeyNotFoundException() << BSL_EARG;
    }
    return _m_iteminfo.get(i0);
}
inline ::idl::songinfo* setcmd::mutable_iteminfo(size_t i0) {
    _flag[1 >> 3] |= (1 << (1 & 0x7));
    return _m_iteminfo.mutable_get(i0);
}
inline ::idl::songinfo* setcmd::m_iteminfo(size_t i0) {
    _flag[1 >> 3] |= (1 << (1 & 0x7));
    return _m_iteminfo.mutable_get(i0);
}
inline ::idl::Unknown* setcmd::mutable_unknown() {
    return &_unknown;
}
inline const ::idl::Unknown& setcmd::unknown() const {
    return _unknown;
}
inline ::idl::Unknown& setcmd::unknown() {
    return _unknown;
}
inline size_t setcmd::unknown_size() const {
    return _unknown.size();
}
inline reload_cmd* reload_cmd::create(bsl::mempool* pool) {
    if(!pool) {
        throw bsl::NullPointerException() << BSL_EARG;
    }
    reload_cmd* tmp=(reload_cmd*)pool->malloc(sizeof(*tmp));
    if(!tmp) {
        throw bsl::BadAllocException() << BSL_EARG;
    }
    new(tmp)reload_cmd(pool);
    return tmp;
}
inline void reload_cmd::destroy(reload_cmd* v) {
    if(v) {
        bsl::mempool* pool=v->_pool;
        v->~reload_cmd();
        pool->free(v,sizeof(*v));
    }
}
inline reload_cmd::reload_cmd(bsl::mempool* pool):
    ::idl::McpackBean(pool),
     _pool(pool)
     ,_m_rf(0)
     ,_m_username(_pool)
     ,_m_uid(0)
     ,_m_sc(0)
     ,_unknown(_pool) {
    _m_sc=::idl::setcmd::create(_pool);
    memset(_flag,0,sizeof(_flag));
}
inline reload_cmd::reload_cmd(const reload_cmd& v):
    ::idl::McpackBean(v._pool),
     _pool(v._pool)
     ,_m_rf(0)
     ,_m_username(_pool)
     ,_m_uid(0)
     ,_m_sc(0)
     ,_unknown(_pool) {
    _m_sc=::idl::setcmd::create(_pool);
    assign(v);
}
inline reload_cmd::~reload_cmd() {
    if(_m_sc) {
        ::idl::setcmd::destroy(_m_sc);
        _m_sc=0;
    }
}
inline reload_cmd& reload_cmd::operator=(const reload_cmd& v) {
    assign(v);
    return *this;
}
inline void reload_cmd::clear() {
    // _m_rf=0;
    _m_username.clear();
    // _m_uid=0;
    if(_m_sc) {
        _m_sc->clear();
    }
    memset(_flag,0,sizeof(_flag));
    _unknown.clear();
    ::idl::McpackBean::clear();
}
// @@CF(constraint functions).
inline void reload_cmd::check() const {
    // @@int32_t rf;
    if(!(_flag[0 >> 3] & (1 << (0 & 0x7)))) {
        throw bsl::KeyNotFoundException() << BSL_EARG << "key '" << "rf" << "' not found";
    }
    {
        __attribute__((unused)) int32_t item=_m_rf;
    }
    // @@string username;
    if(!(_flag[1 >> 3] & (1 << (1 & 0x7)))) {
        throw bsl::KeyNotFoundException() << BSL_EARG << "key '" << "username" << "' not found";
    }
    {
        __attribute__((unused)) const char* item=_m_username.get();
    }
    // @@uint32_t uid;
    if(!(_flag[2 >> 3] & (1 << (2 & 0x7)))) {
        throw bsl::KeyNotFoundException() << BSL_EARG << "key '" << "uid" << "' not found";
    }
    {
        __attribute__((unused)) uint32_t item=_m_uid;
    }
    // @@setcmd sc;
    if(!(_flag[3 >> 3] & (1 << (3 & 0x7)))) {
        throw bsl::KeyNotFoundException() << BSL_EARG << "key '" << "sc" << "' not found";
    }
    {
        ::idl::setcmd& item=const_cast< ::idl::setcmd& >(*_m_sc);
        item.check();
    }
    ::idl::McpackBean::check();
}
inline void reload_cmd::detach() {
    _m_username.detach();
    if(_m_sc) {
        _m_sc->detach();
    }
    _unknown.clear();
    ::idl::McpackBean::detach();
}
inline reload_cmd& reload_cmd::assign(const reload_cmd& v) {
    _m_rf=v._m_rf;
    _m_username=v._m_username;
    _m_uid=v._m_uid;
    if(!v._m_sc) {
        if(_m_sc) {
            ::idl::setcmd::destroy(_m_sc);
        }
        _m_sc=0;
    } else {
        if(!_m_sc) {
            _m_sc=::idl::setcmd::create(_pool);
        }
        *_m_sc=*v._m_sc;
    }
    _unknown=v._unknown;
    bsl::xmemcpy(_flag,v._flag,sizeof(v._flag));
    return *this;
}
inline bool reload_cmd::has_rf() const {
    return (_flag[0 >> 3] & (1 << (0 & 0x7)));
}
inline int32_t reload_cmd::rf() const {
    return _m_rf;
}
inline reload_cmd& reload_cmd::set_rf(int32_t v) {
    _flag[0 >> 3] |= (1 << (0 & 0x7));
    _m_rf=v;
    return *this;
}
inline bool reload_cmd::has_username() const {
    return (_flag[1 >> 3] & (1 << (1 & 0x7)));
}
inline const char* reload_cmd::username(unsigned int* size) const {
    return _m_username.get(size);
}
inline reload_cmd& reload_cmd::set_username(const char* s,ssize_t size) {
    _flag[1 >> 3] |= (1 << (1 & 0x7));
    _m_username.set(s,(size==-1)?strlen(s):(size_t)size);
    return *this;
}
inline reload_cmd& reload_cmd::set_ptr_username(const char* s,ssize_t size) {
    _flag[1 >> 3] |= (1 << (1 & 0x7));
    _m_username.set_ptr(s,(size==-1)?strlen(s):(size_t)size);
    return *this;
}
inline bool reload_cmd::has_uid() const {
    return (_flag[2 >> 3] & (1 << (2 & 0x7)));
}
inline uint32_t reload_cmd::uid() const {
    return _m_uid;
}
inline reload_cmd& reload_cmd::set_uid(uint32_t v) {
    _flag[2 >> 3] |= (1 << (2 & 0x7));
    _m_uid=v;
    return *this;
}
inline bool reload_cmd::has_sc() const {
    return (_flag[3 >> 3] & (1 << (3 & 0x7)));
}
inline const ::idl::setcmd& reload_cmd::sc() const {
    return *_m_sc;
}
inline ::idl::setcmd* reload_cmd::mutable_sc() {
    _flag[3 >> 3] |= (1 << (3 & 0x7));
    if(!_m_sc) {
        _m_sc=::idl::setcmd::create(_pool);
    }
    return _m_sc;
}
inline ::idl::setcmd* reload_cmd::m_sc() {
    _flag[3 >> 3] |= (1 << (3 & 0x7));
    if(!_m_sc) {
        _m_sc=::idl::setcmd::create(_pool);
    }
    return _m_sc;
}
inline ::idl::Unknown* reload_cmd::mutable_unknown() {
    return &_unknown;
}
inline const ::idl::Unknown& reload_cmd::unknown() const {
    return _unknown;
}
inline ::idl::Unknown& reload_cmd::unknown() {
    return _unknown;
}
inline size_t reload_cmd::unknown_size() const {
    return _unknown.size();
}
} // namespace idl
#endif // IDL_GENERATED_FILE_RELOAD_IDL_H_
