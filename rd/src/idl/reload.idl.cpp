#include "reload.idl.h"
__attribute__((unused)) extern bsl::syspool _common_pool;
namespace idl {
// @@class songinfo
static void _mcpack2_load_songinfo_itemid(const mc_pack_item_t*,songinfo*);
static void _mcpack2_load_songinfo_weight(const mc_pack_item_t*,songinfo*);
static bsl::readmap<const char*,void (*)(const mc_pack_item_t*,songinfo*),::idl::string_hash,::idl::string_equal> _mcpack2_load_songinfo_readmap;
// static initialization.
static bool _mcpack2_load_songinfo_static_init() {
    std::vector< std::pair<const char*, void (*)(const mc_pack_item_t*,songinfo*)> >_vec;
    _vec.push_back(std::pair<const char*,void (*)(const mc_pack_item_t*,songinfo*)>("itemid",_mcpack2_load_songinfo_itemid));
    _vec.push_back(std::pair<const char*,void (*)(const mc_pack_item_t*,songinfo*)>("weight",_mcpack2_load_songinfo_weight));
    _mcpack2_load_songinfo_readmap.create(16*2);
    _mcpack2_load_songinfo_readmap.assign(_vec.begin(),_vec.end());
    return true;
}
__attribute__((unused)) static bool _mcpack2_load_songinfo_static_inited=_mcpack2_load_songinfo_static_init();
// @@uint32_t itemid;
static void _mcpack2_load_songinfo_itemid(__attribute__((unused)) const mc_pack_item_t* item,songinfo* self) {
    self->_flag[0 >> 3] |= (1 << (0 & 0x7));
    __attribute__((unused)) int res=0;
    __attribute__((unused)) size_t size=0;
    res=mc_pack_get_uint32_from_item(item,&(self->_m_itemid));
    if(res) {
        throw ::idl::McpackWrongTypeException() << BSL_EARG << "itemid";
    }
}
// @@int32_t weight;
static void _mcpack2_load_songinfo_weight(__attribute__((unused)) const mc_pack_item_t* item,songinfo* self) {
    self->_flag[1 >> 3] |= (1 << (1 & 0x7));
    __attribute__((unused)) int res=0;
    __attribute__((unused)) size_t size=0;
    res=mc_pack_get_int32_from_item(item,&(self->_m_weight));
    if(res) {
        throw ::idl::McpackWrongTypeException() << BSL_EARG << "weight";
    }
}
void songinfo::LoadWithoutCheck(const mc_pack_t* pack) {
    if(MC_PACK_PTR_ERR(pack)) {
        throw ::idl::McpackException(pack) << BSL_EARG;
    }
    clear();
    mc_pack_item_t item;
    int res=mc_pack_first_item(pack,&item);
    if(res && res!=MC_PE_NOT_FOUND) {
        throw ::idl::McpackException(res) << BSL_EARG;
    }
    if(res!=MC_PE_NOT_FOUND) {
        void (*func)(const mc_pack_item_t*,songinfo*)=0;
        do {
            if(_mcpack2_load_songinfo_readmap.get(mc_pack_get_subkey(item.key),&func)==bsl::HASH_EXIST) {
                func(&item,this);
            } else {
                bool push=true;
                for(size_t i=0; i<_ext.size(); i++) {
                    if(_ext[i]->load(item)>=0) {
                        push=false;
                    }
                }
                if(push) {
                    unknown().push_back<mc_pack_item_t>(item);
                }
            }
        } while(!mc_pack_next_item(&item,&item));
    }
}
//for compatiblity.return 0 when it accepts item,else return -1
int songinfo::load(const mc_pack_item_t& item) {
    void (*func)(const mc_pack_item_t*,songinfo*)=0;
    if(_mcpack2_load_songinfo_readmap.get(mc_pack_get_subkey(item.key),&func)==bsl::HASH_EXIST) {
        func(&item,this);
        return 0;
    }
    return -1;
}
void songinfo::load(const mc_pack_t* pack) {
    LoadWithoutCheck(pack);
    check();
}
size_t songinfo::save(mc_pack_t* pack) const {
    if(MC_PACK_PTR_ERR(pack)) {
        throw ::idl::McpackException(pack) << BSL_EARG;
    }
    size_t orig_size=mc_pack_get_size(pack);
    // @@uint32_t itemid;
    {
        int res=mc_pack_put_uint32(pack,"itemid",_m_itemid);
        if(res) {
            throw ::idl::McpackException(res) << BSL_EARG;
        }
    }
    // @@int32_t weight;
    {
        int res=mc_pack_put_int32(pack,"weight",_m_weight);
        if(res) {
            throw ::idl::McpackException(res) << BSL_EARG;
        }
    }
    // save '_unknown' field.
    for(size_t i=0; i<_unknown.size(); i++) {
        const mc_pack_item_t& item=_unknown.GetWithoutCheck<mc_pack_item_t>(i);
        if(item.type==MC_PT_OBJ) {
            mc_pack_t* tmp=mc_pack_put_object(pack,mc_pack_get_subkey(item.key));
            if(MC_PACK_PTR_ERR(tmp)) {
                throw ::idl::McpackException(tmp) << BSL_EARG;
            }
            const mc_pack_t* tmppack=0;
            int res=mc_pack_get_pack_from_item(&item,&tmppack);
            if(res<0) {
                throw ::idl::McpackException(res) << BSL_EARG;
            }
            res=mc_pack_copy_item(tmppack,tmp,0);
            if(res<0) {
                throw ::idl::McpackException(res) << BSL_EARG;
            }
            mc_pack_finish(tmp);
        } else if(item.type==MC_PT_ARR) {
            mc_pack_t* tmp=mc_pack_put_array(pack,mc_pack_get_subkey(item.key));
            if(MC_PACK_PTR_ERR(tmp)) {
                throw ::idl::McpackException(tmp) << BSL_EARG;
            }
            const mc_pack_t* tmppack=0;
            int res=mc_pack_get_array_from_item(&item,&tmppack);
            if(res<0) {
                throw ::idl::McpackException(res) << BSL_EARG;
            }
            res=mc_pack_copy_item(tmppack,tmp,0);
            if(res<0) {
                throw ::idl::McpackException(res) << BSL_EARG;
            }
            mc_pack_finish(tmp);
        } else {
            int res=mc_pack_put_item(pack,&item);
            if(res<0) {
                throw ::idl::McpackException(res) << BSL_EARG;
            }
        }
    }
    // save '_ext' field.
    for(size_t i=0; i<_ext.size(); i++) {
        _ext[i]->save(pack);
    }
    return mc_pack_get_size(pack)-orig_size;
}
// @@class setcmd
static void _mcpack2_load_setcmd_cmd(const mc_pack_item_t*,setcmd*);
static void _mcpack2_load_setcmd_iteminfo(const mc_pack_item_t*,setcmd*);
static bsl::readmap<const char*,void (*)(const mc_pack_item_t*,setcmd*),::idl::string_hash,::idl::string_equal> _mcpack2_load_setcmd_readmap;
// static initialization.
static bool _mcpack2_load_setcmd_static_init() {
    std::vector< std::pair<const char*, void (*)(const mc_pack_item_t*,setcmd*)> >_vec;
    _vec.push_back(std::pair<const char*,void (*)(const mc_pack_item_t*,setcmd*)>("cmd",_mcpack2_load_setcmd_cmd));
    _vec.push_back(std::pair<const char*,void (*)(const mc_pack_item_t*,setcmd*)>("iteminfo",_mcpack2_load_setcmd_iteminfo));
    _mcpack2_load_setcmd_readmap.create(16*2);
    _mcpack2_load_setcmd_readmap.assign(_vec.begin(),_vec.end());
    return true;
}
__attribute__((unused)) static bool _mcpack2_load_setcmd_static_inited=_mcpack2_load_setcmd_static_init();
// @@int32_t cmd;
static void _mcpack2_load_setcmd_cmd(__attribute__((unused)) const mc_pack_item_t* item,setcmd* self) {
    self->_flag[0 >> 3] |= (1 << (0 & 0x7));
    __attribute__((unused)) int res=0;
    __attribute__((unused)) size_t size=0;
    res=mc_pack_get_int32_from_item(item,&(self->_m_cmd));
    if(res) {
        throw ::idl::McpackWrongTypeException() << BSL_EARG << "cmd";
    }
}
// @@songinfo iteminfo=optional(),array(0);
static void _mcpack2_load_setcmd_iteminfo(__attribute__((unused)) const mc_pack_item_t* item,setcmd* self) {
    self->_flag[1 >> 3] |= (1 << (1 & 0x7));
    __attribute__((unused)) int res=0;
    __attribute__((unused)) size_t size=0;
    const mc_pack_t* pack0=0;
    res=mc_pack_get_array_from_item(item,&pack0);
    if(res<0) {
        throw ::idl::McpackException(res) << BSL_EARG << "iteminfo";
    }
    // level 0 begin.
    int size0=mc_pack_get_item_count(pack0);
    typeof(&(self->_m_iteminfo)) lp0=&(self->_m_iteminfo);
    lp0->resize(size0);
    if(size0>0) {
        mc_pack_item_t item0;
        int res0=mc_pack_first_item(pack0,&item0);
        if(res0<0) {
            throw ::idl::McpackException(res) << BSL_EARG << "iteminfo";
        }
        for(int i0=0; i0<size0; i0++) {
            const mc_pack_t* pack=0;
            res0=mc_pack_get_pack_from_item(&item0,&pack);
            if(res0<0) {
                throw ::idl::McpackException(res) << BSL_EARG << "iteminfo";
            }
            lp0->MutableGetWithoutCheck(i0)->LoadWithoutCheck(pack);
            if(i0<(size0-1)) {
                res0=mc_pack_next_item(&item0,&item0);
                if(res0<0) {
                    throw ::idl::McpackException(res) << BSL_EARG << "iteminfo";
                }
            }
        } // for(int i0=0;i0<size;i0++)
    } // if(size0>0)
    // level 0 end.
}
void setcmd::LoadWithoutCheck(const mc_pack_t* pack) {
    if(MC_PACK_PTR_ERR(pack)) {
        throw ::idl::McpackException(pack) << BSL_EARG;
    }
    clear();
    mc_pack_item_t item;
    int res=mc_pack_first_item(pack,&item);
    if(res && res!=MC_PE_NOT_FOUND) {
        throw ::idl::McpackException(res) << BSL_EARG;
    }
    if(res!=MC_PE_NOT_FOUND) {
        void (*func)(const mc_pack_item_t*,setcmd*)=0;
        do {
            if(_mcpack2_load_setcmd_readmap.get(mc_pack_get_subkey(item.key),&func)==bsl::HASH_EXIST) {
                func(&item,this);
            } else {
                bool push=true;
                for(size_t i=0; i<_ext.size(); i++) {
                    if(_ext[i]->load(item)>=0) {
                        push=false;
                    }
                }
                if(push) {
                    unknown().push_back<mc_pack_item_t>(item);
                }
            }
        } while(!mc_pack_next_item(&item,&item));
    }
}
//for compatiblity.return 0 when it accepts item,else return -1
int setcmd::load(const mc_pack_item_t& item) {
    void (*func)(const mc_pack_item_t*,setcmd*)=0;
    if(_mcpack2_load_setcmd_readmap.get(mc_pack_get_subkey(item.key),&func)==bsl::HASH_EXIST) {
        func(&item,this);
        return 0;
    }
    return -1;
}
void setcmd::load(const mc_pack_t* pack) {
    LoadWithoutCheck(pack);
    check();
}
size_t setcmd::save(mc_pack_t* pack) const {
    if(MC_PACK_PTR_ERR(pack)) {
        throw ::idl::McpackException(pack) << BSL_EARG;
    }
    size_t orig_size=mc_pack_get_size(pack);
    // @@int32_t cmd;
    {
        int res=mc_pack_put_int32(pack,"cmd",_m_cmd);
        if(res) {
            throw ::idl::McpackException(res) << BSL_EARG;
        }
    }
    // @@songinfo iteminfo=optional(),array(0);
    if((_flag[1 >> 3] & (1 << (1 & 0x7)))) {
        mc_pack_t* pack0=mc_pack_put_array(pack,"iteminfo");
        if(MC_PACK_PTR_ERR(pack0)) {
            throw ::idl::McpackException(pack0) << BSL_EARG;
        }
        // level 0 begin.
        typeof(_m_iteminfo)& lr0=(_m_iteminfo);
        size_t size0=lr0.size();
        for(size_t i0=0; i0<size0; i0++) {
            mc_pack_t* subpack=mc_pack_put_object(pack0,0);
            if(MC_PACK_PTR_ERR(subpack)) {
                throw ::idl::McpackException(subpack) << BSL_EARG;
            }
            lr0.GetWithoutCheck(i0).save(subpack);
            mc_pack_finish(subpack);
        }
        // level 0 end.
        mc_pack_finish(pack0);
    }
    // save '_unknown' field.
    for(size_t i=0; i<_unknown.size(); i++) {
        const mc_pack_item_t& item=_unknown.GetWithoutCheck<mc_pack_item_t>(i);
        if(item.type==MC_PT_OBJ) {
            mc_pack_t* tmp=mc_pack_put_object(pack,mc_pack_get_subkey(item.key));
            if(MC_PACK_PTR_ERR(tmp)) {
                throw ::idl::McpackException(tmp) << BSL_EARG;
            }
            const mc_pack_t* tmppack=0;
            int res=mc_pack_get_pack_from_item(&item,&tmppack);
            if(res<0) {
                throw ::idl::McpackException(res) << BSL_EARG;
            }
            res=mc_pack_copy_item(tmppack,tmp,0);
            if(res<0) {
                throw ::idl::McpackException(res) << BSL_EARG;
            }
            mc_pack_finish(tmp);
        } else if(item.type==MC_PT_ARR) {
            mc_pack_t* tmp=mc_pack_put_array(pack,mc_pack_get_subkey(item.key));
            if(MC_PACK_PTR_ERR(tmp)) {
                throw ::idl::McpackException(tmp) << BSL_EARG;
            }
            const mc_pack_t* tmppack=0;
            int res=mc_pack_get_array_from_item(&item,&tmppack);
            if(res<0) {
                throw ::idl::McpackException(res) << BSL_EARG;
            }
            res=mc_pack_copy_item(tmppack,tmp,0);
            if(res<0) {
                throw ::idl::McpackException(res) << BSL_EARG;
            }
            mc_pack_finish(tmp);
        } else {
            int res=mc_pack_put_item(pack,&item);
            if(res<0) {
                throw ::idl::McpackException(res) << BSL_EARG;
            }
        }
    }
    // save '_ext' field.
    for(size_t i=0; i<_ext.size(); i++) {
        _ext[i]->save(pack);
    }
    return mc_pack_get_size(pack)-orig_size;
}
// @@class reload_cmd
static void _mcpack2_load_reload_cmd_rf(const mc_pack_item_t*,reload_cmd*);
static void _mcpack2_load_reload_cmd_username(const mc_pack_item_t*,reload_cmd*);
static void _mcpack2_load_reload_cmd_uid(const mc_pack_item_t*,reload_cmd*);
static void _mcpack2_load_reload_cmd_sc(const mc_pack_item_t*,reload_cmd*);
static bsl::readmap<const char*,void (*)(const mc_pack_item_t*,reload_cmd*),::idl::string_hash,::idl::string_equal> _mcpack2_load_reload_cmd_readmap;
// static initialization.
static bool _mcpack2_load_reload_cmd_static_init() {
    std::vector< std::pair<const char*, void (*)(const mc_pack_item_t*,reload_cmd*)> >_vec;
    _vec.push_back(std::pair<const char*,void (*)(const mc_pack_item_t*,reload_cmd*)>("rf",_mcpack2_load_reload_cmd_rf));
    _vec.push_back(std::pair<const char*,void (*)(const mc_pack_item_t*,reload_cmd*)>("username",_mcpack2_load_reload_cmd_username));
    _vec.push_back(std::pair<const char*,void (*)(const mc_pack_item_t*,reload_cmd*)>("uid",_mcpack2_load_reload_cmd_uid));
    _vec.push_back(std::pair<const char*,void (*)(const mc_pack_item_t*,reload_cmd*)>("sc",_mcpack2_load_reload_cmd_sc));
    _mcpack2_load_reload_cmd_readmap.create(16*4);
    _mcpack2_load_reload_cmd_readmap.assign(_vec.begin(),_vec.end());
    return true;
}
__attribute__((unused)) static bool _mcpack2_load_reload_cmd_static_inited=_mcpack2_load_reload_cmd_static_init();
// @@int32_t rf;
static void _mcpack2_load_reload_cmd_rf(__attribute__((unused)) const mc_pack_item_t* item,reload_cmd* self) {
    self->_flag[0 >> 3] |= (1 << (0 & 0x7));
    __attribute__((unused)) int res=0;
    __attribute__((unused)) size_t size=0;
    res=mc_pack_get_int32_from_item(item,&(self->_m_rf));
    if(res) {
        throw ::idl::McpackWrongTypeException() << BSL_EARG << "rf";
    }
}
// @@string username;
static void _mcpack2_load_reload_cmd_username(__attribute__((unused)) const mc_pack_item_t* item,reload_cmd* self) {
    self->_flag[1 >> 3] |= (1 << (1 & 0x7));
    __attribute__((unused)) int res=0;
    __attribute__((unused)) size_t size=0;
    if(item->type!=MC_IT_TXT) {
        throw ::idl::McpackWrongTypeException() << BSL_EARG << "username";
    }
    self->_m_username.set_ptr(item->value,item->value_size-1);
}
// @@uint32_t uid;
static void _mcpack2_load_reload_cmd_uid(__attribute__((unused)) const mc_pack_item_t* item,reload_cmd* self) {
    self->_flag[2 >> 3] |= (1 << (2 & 0x7));
    __attribute__((unused)) int res=0;
    __attribute__((unused)) size_t size=0;
    res=mc_pack_get_uint32_from_item(item,&(self->_m_uid));
    if(res) {
        throw ::idl::McpackWrongTypeException() << BSL_EARG << "uid";
    }
}
// @@setcmd sc;
static void _mcpack2_load_reload_cmd_sc(__attribute__((unused)) const mc_pack_item_t* item,reload_cmd* self) {
    self->_flag[3 >> 3] |= (1 << (3 & 0x7));
    __attribute__((unused)) int res=0;
    __attribute__((unused)) size_t size=0;
    const mc_pack_t* pack=0;
    res=mc_pack_get_pack_from_item(item,&pack);
    if(res<0) {
        throw ::idl::McpackException(res) << BSL_EARG;
    }
    if(!self->_m_sc) {
        self->_m_sc=::idl::setcmd::create(self->_pool);
    }
    self->_m_sc->LoadWithoutCheck(pack);
}
void reload_cmd::LoadWithoutCheck(const mc_pack_t* pack) {
    if(MC_PACK_PTR_ERR(pack)) {
        throw ::idl::McpackException(pack) << BSL_EARG;
    }
    clear();
    mc_pack_item_t item;
    int res=mc_pack_first_item(pack,&item);
    if(res && res!=MC_PE_NOT_FOUND) {
        throw ::idl::McpackException(res) << BSL_EARG;
    }
    if(res!=MC_PE_NOT_FOUND) {
        void (*func)(const mc_pack_item_t*,reload_cmd*)=0;
        do {
            if(_mcpack2_load_reload_cmd_readmap.get(mc_pack_get_subkey(item.key),&func)==bsl::HASH_EXIST) {
                func(&item,this);
            } else {
                bool push=true;
                for(size_t i=0; i<_ext.size(); i++) {
                    if(_ext[i]->load(item)>=0) {
                        push=false;
                    }
                }
                if(push) {
                    unknown().push_back<mc_pack_item_t>(item);
                }
            }
        } while(!mc_pack_next_item(&item,&item));
    }
}
//for compatiblity.return 0 when it accepts item,else return -1
int reload_cmd::load(const mc_pack_item_t& item) {
    void (*func)(const mc_pack_item_t*,reload_cmd*)=0;
    if(_mcpack2_load_reload_cmd_readmap.get(mc_pack_get_subkey(item.key),&func)==bsl::HASH_EXIST) {
        func(&item,this);
        return 0;
    }
    return -1;
}
void reload_cmd::load(const mc_pack_t* pack) {
    LoadWithoutCheck(pack);
    check();
}
size_t reload_cmd::save(mc_pack_t* pack) const {
    if(MC_PACK_PTR_ERR(pack)) {
        throw ::idl::McpackException(pack) << BSL_EARG;
    }
    size_t orig_size=mc_pack_get_size(pack);
    // @@int32_t rf;
    {
        int res=mc_pack_put_int32(pack,"rf",_m_rf);
        if(res) {
            throw ::idl::McpackException(res) << BSL_EARG;
        }
    }
    // @@string username;
    {
        int res=mc_pack_put_str(pack,"username",_m_username.c_str());
        if(res) {
            throw ::idl::McpackException(res) << BSL_EARG;
        }
    }
    // @@uint32_t uid;
    {
        int res=mc_pack_put_uint32(pack,"uid",_m_uid);
        if(res) {
            throw ::idl::McpackException(res) << BSL_EARG;
        }
    }
    // @@setcmd sc;
    {
        mc_pack_t* subpack=mc_pack_put_object(pack,"sc");
        if(MC_PACK_PTR_ERR(subpack)) {
            throw ::idl::McpackException(subpack) << BSL_EARG;
        }
        _m_sc->save(subpack);
        mc_pack_finish(subpack);
    }
    // save '_unknown' field.
    for(size_t i=0; i<_unknown.size(); i++) {
        const mc_pack_item_t& item=_unknown.GetWithoutCheck<mc_pack_item_t>(i);
        if(item.type==MC_PT_OBJ) {
            mc_pack_t* tmp=mc_pack_put_object(pack,mc_pack_get_subkey(item.key));
            if(MC_PACK_PTR_ERR(tmp)) {
                throw ::idl::McpackException(tmp) << BSL_EARG;
            }
            const mc_pack_t* tmppack=0;
            int res=mc_pack_get_pack_from_item(&item,&tmppack);
            if(res<0) {
                throw ::idl::McpackException(res) << BSL_EARG;
            }
            res=mc_pack_copy_item(tmppack,tmp,0);
            if(res<0) {
                throw ::idl::McpackException(res) << BSL_EARG;
            }
            mc_pack_finish(tmp);
        } else if(item.type==MC_PT_ARR) {
            mc_pack_t* tmp=mc_pack_put_array(pack,mc_pack_get_subkey(item.key));
            if(MC_PACK_PTR_ERR(tmp)) {
                throw ::idl::McpackException(tmp) << BSL_EARG;
            }
            const mc_pack_t* tmppack=0;
            int res=mc_pack_get_array_from_item(&item,&tmppack);
            if(res<0) {
                throw ::idl::McpackException(res) << BSL_EARG;
            }
            res=mc_pack_copy_item(tmppack,tmp,0);
            if(res<0) {
                throw ::idl::McpackException(res) << BSL_EARG;
            }
            mc_pack_finish(tmp);
        } else {
            int res=mc_pack_put_item(pack,&item);
            if(res<0) {
                throw ::idl::McpackException(res) << BSL_EARG;
            }
        }
    }
    // save '_ext' field.
    for(size_t i=0; i<_ext.size(); i++) {
        _ext[i]->save(pack);
    }
    return mc_pack_get_size(pack)-orig_size;
}
} // namespace idl
