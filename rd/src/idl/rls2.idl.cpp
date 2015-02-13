#include "rls2.idl.h"
__attribute__((unused)) extern bsl::syspool _common_pool;
namespace idl {
// @@class action
static void _mcpack2_load_action_itemid(const mc_pack_item_t*,action*);
static void _mcpack2_load_action_action_no(const mc_pack_item_t*,action*);
static bsl::readmap<const char*,void (*)(const mc_pack_item_t*,action*),::idl::string_hash,::idl::string_equal> _mcpack2_load_action_readmap;
// static initialization.
static bool _mcpack2_load_action_static_init(){
std::vector< std::pair<const char*, void (*)(const mc_pack_item_t*,action*)> >_vec;
_vec.push_back(std::pair<const char*,void (*)(const mc_pack_item_t*,action*)>("itemid",_mcpack2_load_action_itemid));
_vec.push_back(std::pair<const char*,void (*)(const mc_pack_item_t*,action*)>("action_no",_mcpack2_load_action_action_no));
_mcpack2_load_action_readmap.create(16*2);
_mcpack2_load_action_readmap.assign(_vec.begin(),_vec.end());
return true;
}
__attribute__((unused)) static bool _mcpack2_load_action_static_inited=_mcpack2_load_action_static_init();
// @@uint32_t itemid;
static void _mcpack2_load_action_itemid(__attribute__((unused)) const mc_pack_item_t* item,action* self){
self->_flag[0 >> 3] |= (1 << (0 & 0x7));
 
__attribute__((unused)) int res=0;
__attribute__((unused)) size_t size=0;
res=mc_pack_get_uint32_from_item(item,&(self->_m_itemid));
if(res){
throw ::idl::McpackWrongTypeException() << BSL_EARG << "itemid";
}
}
// @@int32_t action_no;
static void _mcpack2_load_action_action_no(__attribute__((unused)) const mc_pack_item_t* item,action* self){
self->_flag[1 >> 3] |= (1 << (1 & 0x7));
 
__attribute__((unused)) int res=0;
__attribute__((unused)) size_t size=0;
res=mc_pack_get_int32_from_item(item,&(self->_m_action_no));
if(res){
throw ::idl::McpackWrongTypeException() << BSL_EARG << "action_no";
}
}
void action::LoadWithoutCheck(const mc_pack_t* pack){
if(MC_PACK_PTR_ERR(pack)){
throw ::idl::McpackException(pack) << BSL_EARG;
}
clear();
mc_pack_item_t item;
int res=mc_pack_first_item(pack,&item);
if(res && res!=MC_PE_NOT_FOUND){
throw ::idl::McpackException(res) << BSL_EARG;
}
if(res!=MC_PE_NOT_FOUND){
void (*func)(const mc_pack_item_t*,action*)=0;
do{
if(_mcpack2_load_action_readmap.get(mc_pack_get_subkey(item.key),&func)==bsl::HASH_EXIST){
func(&item,this);
}else{
bool push=true;
for(size_t i=0;i<_ext.size();i++){
if(_ext[i]->load(item)>=0){
push=false;
}
}
if(push){
unknown().push_back<mc_pack_item_t>(item);
}
}
}while(!mc_pack_next_item(&item,&item));
}
}
//for compatiblity.return 0 when it accepts item,else return -1
int action::load(const mc_pack_item_t& item){
void (*func)(const mc_pack_item_t*,action*)=0;
if(_mcpack2_load_action_readmap.get(mc_pack_get_subkey(item.key),&func)==bsl::HASH_EXIST){
func(&item,this);
return 0;
}
return -1;
}
void action::load(const mc_pack_t* pack){
LoadWithoutCheck(pack);
check();
}
size_t action::save(mc_pack_t* pack) const{
if(MC_PACK_PTR_ERR(pack)){
throw ::idl::McpackException(pack) << BSL_EARG;
}
size_t orig_size=mc_pack_get_size(pack);
// @@uint32_t itemid;
{
int res=mc_pack_put_uint32(pack,"itemid",_m_itemid);
if(res){
throw ::idl::McpackException(res) << BSL_EARG;
}
}
// @@int32_t action_no;
{
int res=mc_pack_put_int32(pack,"action_no",_m_action_no);
if(res){
throw ::idl::McpackException(res) << BSL_EARG;
}
}
// save '_unknown' field.
for(size_t i=0;i<_unknown.size();i++){
const mc_pack_item_t& item=_unknown.GetWithoutCheck<mc_pack_item_t>(i);
if(item.type==MC_PT_OBJ){
mc_pack_t* tmp=mc_pack_put_object(pack,mc_pack_get_subkey(item.key));
if(MC_PACK_PTR_ERR(tmp)){
throw ::idl::McpackException(tmp) << BSL_EARG;
}
const mc_pack_t* tmppack=0;
int res=mc_pack_get_pack_from_item(&item,&tmppack);
if(res<0){
throw ::idl::McpackException(res) << BSL_EARG;
}
res=mc_pack_copy_item(tmppack,tmp,0);
if(res<0){
throw ::idl::McpackException(res) << BSL_EARG;
}
mc_pack_finish(tmp);
}else if(item.type==MC_PT_ARR){
mc_pack_t* tmp=mc_pack_put_array(pack,mc_pack_get_subkey(item.key));
if(MC_PACK_PTR_ERR(tmp)){
throw ::idl::McpackException(tmp) << BSL_EARG;
}
const mc_pack_t* tmppack=0;
int res=mc_pack_get_array_from_item(&item,&tmppack);
if(res<0){
throw ::idl::McpackException(res) << BSL_EARG;
}
res=mc_pack_copy_item(tmppack,tmp,0);
if(res<0){
throw ::idl::McpackException(res) << BSL_EARG;
}
mc_pack_finish(tmp);
}else{
int res=mc_pack_put_item(pack,&item);
if(res<0){
throw ::idl::McpackException(res) << BSL_EARG;
}
}
}
// save '_ext' field.
for(size_t i=0;i<_ext.size();i++){
_ext[i]->save(pack);
}
return mc_pack_get_size(pack)-orig_size;
}
// @@class playercmd
static void _mcpack2_load_playercmd_needdata(const mc_pack_item_t*,playercmd*);
static void _mcpack2_load_playercmd_titles(const mc_pack_item_t*,playercmd*);
static bsl::readmap<const char*,void (*)(const mc_pack_item_t*,playercmd*),::idl::string_hash,::idl::string_equal> _mcpack2_load_playercmd_readmap;
// static initialization.
static bool _mcpack2_load_playercmd_static_init(){
std::vector< std::pair<const char*, void (*)(const mc_pack_item_t*,playercmd*)> >_vec;
_vec.push_back(std::pair<const char*,void (*)(const mc_pack_item_t*,playercmd*)>("needdata",_mcpack2_load_playercmd_needdata));
_vec.push_back(std::pair<const char*,void (*)(const mc_pack_item_t*,playercmd*)>("titles",_mcpack2_load_playercmd_titles));
_mcpack2_load_playercmd_readmap.create(16*2);
_mcpack2_load_playercmd_readmap.assign(_vec.begin(),_vec.end());
return true;
}
__attribute__((unused)) static bool _mcpack2_load_playercmd_static_inited=_mcpack2_load_playercmd_static_init();
// @@int32_t needdata;
static void _mcpack2_load_playercmd_needdata(__attribute__((unused)) const mc_pack_item_t* item,playercmd* self){
self->_flag[0 >> 3] |= (1 << (0 & 0x7));
 
__attribute__((unused)) int res=0;
__attribute__((unused)) size_t size=0;
res=mc_pack_get_int32_from_item(item,&(self->_m_needdata));
if(res){
throw ::idl::McpackWrongTypeException() << BSL_EARG << "needdata";
}
}
// @@action titles=array(0);
static void _mcpack2_load_playercmd_titles(__attribute__((unused)) const mc_pack_item_t* item,playercmd* self){
self->_flag[1 >> 3] |= (1 << (1 & 0x7));
 
__attribute__((unused)) int res=0;
__attribute__((unused)) size_t size=0;
const mc_pack_t *pack0=0;
res=mc_pack_get_array_from_item(item,&pack0);
if(res<0){
throw ::idl::McpackException(res) << BSL_EARG << "titles";
}
// level 0 begin.
int size0=mc_pack_get_item_count(pack0);

typeof(&(self->_m_titles)) lp0=&(self->_m_titles);
lp0->resize(size0);
if(size0>0){
mc_pack_item_t item0;
int res0=mc_pack_first_item(pack0,&item0);
if(res0<0){
throw ::idl::McpackException(res) << BSL_EARG << "titles";
}
for(int i0=0;i0<size0;i0++){
const mc_pack_t* pack=0;
res0=mc_pack_get_pack_from_item(&item0,&pack);
if(res0<0){
throw ::idl::McpackException(res) << BSL_EARG << "titles";
}
lp0->MutableGetWithoutCheck(i0)->LoadWithoutCheck(pack);
if(i0<(size0-1)){
res0=mc_pack_next_item(&item0,&item0);
if(res0<0){
throw ::idl::McpackException(res) << BSL_EARG << "titles";
}
}
} // for(int i0=0;i0<size;i0++)
} // if(size0>0)
// level 0 end.

}
void playercmd::LoadWithoutCheck(const mc_pack_t* pack){
if(MC_PACK_PTR_ERR(pack)){
throw ::idl::McpackException(pack) << BSL_EARG;
}
clear();
mc_pack_item_t item;
int res=mc_pack_first_item(pack,&item);
if(res && res!=MC_PE_NOT_FOUND){
throw ::idl::McpackException(res) << BSL_EARG;
}
if(res!=MC_PE_NOT_FOUND){
void (*func)(const mc_pack_item_t*,playercmd*)=0;
do{
if(_mcpack2_load_playercmd_readmap.get(mc_pack_get_subkey(item.key),&func)==bsl::HASH_EXIST){
func(&item,this);
}else{
bool push=true;
for(size_t i=0;i<_ext.size();i++){
if(_ext[i]->load(item)>=0){
push=false;
}
}
if(push){
unknown().push_back<mc_pack_item_t>(item);
}
}
}while(!mc_pack_next_item(&item,&item));
}
}
//for compatiblity.return 0 when it accepts item,else return -1
int playercmd::load(const mc_pack_item_t& item){
void (*func)(const mc_pack_item_t*,playercmd*)=0;
if(_mcpack2_load_playercmd_readmap.get(mc_pack_get_subkey(item.key),&func)==bsl::HASH_EXIST){
func(&item,this);
return 0;
}
return -1;
}
void playercmd::load(const mc_pack_t* pack){
LoadWithoutCheck(pack);
check();
}
size_t playercmd::save(mc_pack_t* pack) const{
if(MC_PACK_PTR_ERR(pack)){
throw ::idl::McpackException(pack) << BSL_EARG;
}
size_t orig_size=mc_pack_get_size(pack);
// @@int32_t needdata;
{
int res=mc_pack_put_int32(pack,"needdata",_m_needdata);
if(res){
throw ::idl::McpackException(res) << BSL_EARG;
}
}
// @@action titles=array(0);
{
mc_pack_t *pack0=mc_pack_put_array(pack,"titles");
if(MC_PACK_PTR_ERR(pack0)){
throw ::idl::McpackException(pack0) << BSL_EARG;
}
// level 0 begin.
typeof(_m_titles)& lr0=(_m_titles);
size_t size0=lr0.size();
for(size_t i0=0;i0<size0;i0++){
mc_pack_t *subpack=mc_pack_put_object(pack0,0);
if(MC_PACK_PTR_ERR(subpack)){
throw ::idl::McpackException(subpack) << BSL_EARG;
}
lr0.GetWithoutCheck(i0).save(subpack);
mc_pack_finish(subpack);
}
// level 0 end.

mc_pack_finish(pack0);
}
// save '_unknown' field.
for(size_t i=0;i<_unknown.size();i++){
const mc_pack_item_t& item=_unknown.GetWithoutCheck<mc_pack_item_t>(i);
if(item.type==MC_PT_OBJ){
mc_pack_t* tmp=mc_pack_put_object(pack,mc_pack_get_subkey(item.key));
if(MC_PACK_PTR_ERR(tmp)){
throw ::idl::McpackException(tmp) << BSL_EARG;
}
const mc_pack_t* tmppack=0;
int res=mc_pack_get_pack_from_item(&item,&tmppack);
if(res<0){
throw ::idl::McpackException(res) << BSL_EARG;
}
res=mc_pack_copy_item(tmppack,tmp,0);
if(res<0){
throw ::idl::McpackException(res) << BSL_EARG;
}
mc_pack_finish(tmp);
}else if(item.type==MC_PT_ARR){
mc_pack_t* tmp=mc_pack_put_array(pack,mc_pack_get_subkey(item.key));
if(MC_PACK_PTR_ERR(tmp)){
throw ::idl::McpackException(tmp) << BSL_EARG;
}
const mc_pack_t* tmppack=0;
int res=mc_pack_get_array_from_item(&item,&tmppack);
if(res<0){
throw ::idl::McpackException(res) << BSL_EARG;
}
res=mc_pack_copy_item(tmppack,tmp,0);
if(res<0){
throw ::idl::McpackException(res) << BSL_EARG;
}
mc_pack_finish(tmp);
}else{
int res=mc_pack_put_item(pack,&item);
if(res<0){
throw ::idl::McpackException(res) << BSL_EARG;
}
}
}
// save '_ext' field.
for(size_t i=0;i<_ext.size();i++){
_ext[i]->save(pack);
}
return mc_pack_get_size(pack)-orig_size;
}
// @@class findcmd
static void _mcpack2_load_findcmd_category(const mc_pack_item_t*,findcmd*);
static void _mcpack2_load_findcmd_keyword(const mc_pack_item_t*,findcmd*);
static bsl::readmap<const char*,void (*)(const mc_pack_item_t*,findcmd*),::idl::string_hash,::idl::string_equal> _mcpack2_load_findcmd_readmap;
// static initialization.
static bool _mcpack2_load_findcmd_static_init(){
std::vector< std::pair<const char*, void (*)(const mc_pack_item_t*,findcmd*)> >_vec;
_vec.push_back(std::pair<const char*,void (*)(const mc_pack_item_t*,findcmd*)>("category",_mcpack2_load_findcmd_category));
_vec.push_back(std::pair<const char*,void (*)(const mc_pack_item_t*,findcmd*)>("keyword",_mcpack2_load_findcmd_keyword));
_mcpack2_load_findcmd_readmap.create(16*2);
_mcpack2_load_findcmd_readmap.assign(_vec.begin(),_vec.end());
return true;
}
__attribute__((unused)) static bool _mcpack2_load_findcmd_static_inited=_mcpack2_load_findcmd_static_init();
// @@int32_t category;
static void _mcpack2_load_findcmd_category(__attribute__((unused)) const mc_pack_item_t* item,findcmd* self){
self->_flag[0 >> 3] |= (1 << (0 & 0x7));
 
__attribute__((unused)) int res=0;
__attribute__((unused)) size_t size=0;
res=mc_pack_get_int32_from_item(item,&(self->_m_category));
if(res){
throw ::idl::McpackWrongTypeException() << BSL_EARG << "category";
}
}
// @@string keyword;
static void _mcpack2_load_findcmd_keyword(__attribute__((unused)) const mc_pack_item_t* item,findcmd* self){
self->_flag[1 >> 3] |= (1 << (1 & 0x7));
 
__attribute__((unused)) int res=0;
__attribute__((unused)) size_t size=0;
if(item->type!=MC_IT_TXT){
throw ::idl::McpackWrongTypeException() << BSL_EARG << "keyword";
}
self->_m_keyword.set_ptr(item->value,item->value_size-1);
}
void findcmd::LoadWithoutCheck(const mc_pack_t* pack){
if(MC_PACK_PTR_ERR(pack)){
throw ::idl::McpackException(pack) << BSL_EARG;
}
clear();
mc_pack_item_t item;
int res=mc_pack_first_item(pack,&item);
if(res && res!=MC_PE_NOT_FOUND){
throw ::idl::McpackException(res) << BSL_EARG;
}
if(res!=MC_PE_NOT_FOUND){
void (*func)(const mc_pack_item_t*,findcmd*)=0;
do{
if(_mcpack2_load_findcmd_readmap.get(mc_pack_get_subkey(item.key),&func)==bsl::HASH_EXIST){
func(&item,this);
}else{
bool push=true;
for(size_t i=0;i<_ext.size();i++){
if(_ext[i]->load(item)>=0){
push=false;
}
}
if(push){
unknown().push_back<mc_pack_item_t>(item);
}
}
}while(!mc_pack_next_item(&item,&item));
}
}
//for compatiblity.return 0 when it accepts item,else return -1
int findcmd::load(const mc_pack_item_t& item){
void (*func)(const mc_pack_item_t*,findcmd*)=0;
if(_mcpack2_load_findcmd_readmap.get(mc_pack_get_subkey(item.key),&func)==bsl::HASH_EXIST){
func(&item,this);
return 0;
}
return -1;
}
void findcmd::load(const mc_pack_t* pack){
LoadWithoutCheck(pack);
check();
}
size_t findcmd::save(mc_pack_t* pack) const{
if(MC_PACK_PTR_ERR(pack)){
throw ::idl::McpackException(pack) << BSL_EARG;
}
size_t orig_size=mc_pack_get_size(pack);
// @@int32_t category;
{
int res=mc_pack_put_int32(pack,"category",_m_category);
if(res){
throw ::idl::McpackException(res) << BSL_EARG;
}
}
// @@string keyword;
{
int res=mc_pack_put_str(pack,"keyword",_m_keyword.c_str());
if(res){
throw ::idl::McpackException(res) << BSL_EARG;
}
}
// save '_unknown' field.
for(size_t i=0;i<_unknown.size();i++){
const mc_pack_item_t& item=_unknown.GetWithoutCheck<mc_pack_item_t>(i);
if(item.type==MC_PT_OBJ){
mc_pack_t* tmp=mc_pack_put_object(pack,mc_pack_get_subkey(item.key));
if(MC_PACK_PTR_ERR(tmp)){
throw ::idl::McpackException(tmp) << BSL_EARG;
}
const mc_pack_t* tmppack=0;
int res=mc_pack_get_pack_from_item(&item,&tmppack);
if(res<0){
throw ::idl::McpackException(res) << BSL_EARG;
}
res=mc_pack_copy_item(tmppack,tmp,0);
if(res<0){
throw ::idl::McpackException(res) << BSL_EARG;
}
mc_pack_finish(tmp);
}else if(item.type==MC_PT_ARR){
mc_pack_t* tmp=mc_pack_put_array(pack,mc_pack_get_subkey(item.key));
if(MC_PACK_PTR_ERR(tmp)){
throw ::idl::McpackException(tmp) << BSL_EARG;
}
const mc_pack_t* tmppack=0;
int res=mc_pack_get_array_from_item(&item,&tmppack);
if(res<0){
throw ::idl::McpackException(res) << BSL_EARG;
}
res=mc_pack_copy_item(tmppack,tmp,0);
if(res<0){
throw ::idl::McpackException(res) << BSL_EARG;
}
mc_pack_finish(tmp);
}else{
int res=mc_pack_put_item(pack,&item);
if(res<0){
throw ::idl::McpackException(res) << BSL_EARG;
}
}
}
// save '_ext' field.
for(size_t i=0;i<_ext.size();i++){
_ext[i]->save(pack);
}
return mc_pack_get_size(pack)-orig_size;
}
// @@class mgrcmd
static void _mcpack2_load_mgrcmd_action(const mc_pack_item_t*,mgrcmd*);
static void _mcpack2_load_mgrcmd_category(const mc_pack_item_t*,mgrcmd*);
static void _mcpack2_load_mgrcmd_itemid(const mc_pack_item_t*,mgrcmd*);
static bsl::readmap<const char*,void (*)(const mc_pack_item_t*,mgrcmd*),::idl::string_hash,::idl::string_equal> _mcpack2_load_mgrcmd_readmap;
// static initialization.
static bool _mcpack2_load_mgrcmd_static_init(){
std::vector< std::pair<const char*, void (*)(const mc_pack_item_t*,mgrcmd*)> >_vec;
_vec.push_back(std::pair<const char*,void (*)(const mc_pack_item_t*,mgrcmd*)>("action",_mcpack2_load_mgrcmd_action));
_vec.push_back(std::pair<const char*,void (*)(const mc_pack_item_t*,mgrcmd*)>("category",_mcpack2_load_mgrcmd_category));
_vec.push_back(std::pair<const char*,void (*)(const mc_pack_item_t*,mgrcmd*)>("itemid",_mcpack2_load_mgrcmd_itemid));
_mcpack2_load_mgrcmd_readmap.create(16*3);
_mcpack2_load_mgrcmd_readmap.assign(_vec.begin(),_vec.end());
return true;
}
__attribute__((unused)) static bool _mcpack2_load_mgrcmd_static_inited=_mcpack2_load_mgrcmd_static_init();
// @@int32_t action;
static void _mcpack2_load_mgrcmd_action(__attribute__((unused)) const mc_pack_item_t* item,mgrcmd* self){
self->_flag[0 >> 3] |= (1 << (0 & 0x7));
 
__attribute__((unused)) int res=0;
__attribute__((unused)) size_t size=0;
res=mc_pack_get_int32_from_item(item,&(self->_m_action));
if(res){
throw ::idl::McpackWrongTypeException() << BSL_EARG << "action";
}
}
// @@int32_t category;
static void _mcpack2_load_mgrcmd_category(__attribute__((unused)) const mc_pack_item_t* item,mgrcmd* self){
self->_flag[1 >> 3] |= (1 << (1 & 0x7));
 
__attribute__((unused)) int res=0;
__attribute__((unused)) size_t size=0;
res=mc_pack_get_int32_from_item(item,&(self->_m_category));
if(res){
throw ::idl::McpackWrongTypeException() << BSL_EARG << "category";
}
}
// @@uint32_t itemid;
static void _mcpack2_load_mgrcmd_itemid(__attribute__((unused)) const mc_pack_item_t* item,mgrcmd* self){
self->_flag[2 >> 3] |= (1 << (2 & 0x7));
 
__attribute__((unused)) int res=0;
__attribute__((unused)) size_t size=0;
res=mc_pack_get_uint32_from_item(item,&(self->_m_itemid));
if(res){
throw ::idl::McpackWrongTypeException() << BSL_EARG << "itemid";
}
}
void mgrcmd::LoadWithoutCheck(const mc_pack_t* pack){
if(MC_PACK_PTR_ERR(pack)){
throw ::idl::McpackException(pack) << BSL_EARG;
}
clear();
mc_pack_item_t item;
int res=mc_pack_first_item(pack,&item);
if(res && res!=MC_PE_NOT_FOUND){
throw ::idl::McpackException(res) << BSL_EARG;
}
if(res!=MC_PE_NOT_FOUND){
void (*func)(const mc_pack_item_t*,mgrcmd*)=0;
do{
if(_mcpack2_load_mgrcmd_readmap.get(mc_pack_get_subkey(item.key),&func)==bsl::HASH_EXIST){
func(&item,this);
}else{
bool push=true;
for(size_t i=0;i<_ext.size();i++){
if(_ext[i]->load(item)>=0){
push=false;
}
}
if(push){
unknown().push_back<mc_pack_item_t>(item);
}
}
}while(!mc_pack_next_item(&item,&item));
}
}
//for compatiblity.return 0 when it accepts item,else return -1
int mgrcmd::load(const mc_pack_item_t& item){
void (*func)(const mc_pack_item_t*,mgrcmd*)=0;
if(_mcpack2_load_mgrcmd_readmap.get(mc_pack_get_subkey(item.key),&func)==bsl::HASH_EXIST){
func(&item,this);
return 0;
}
return -1;
}
void mgrcmd::load(const mc_pack_t* pack){
LoadWithoutCheck(pack);
check();
}
size_t mgrcmd::save(mc_pack_t* pack) const{
if(MC_PACK_PTR_ERR(pack)){
throw ::idl::McpackException(pack) << BSL_EARG;
}
size_t orig_size=mc_pack_get_size(pack);
// @@int32_t action;
{
int res=mc_pack_put_int32(pack,"action",_m_action);
if(res){
throw ::idl::McpackException(res) << BSL_EARG;
}
}
// @@int32_t category;
{
int res=mc_pack_put_int32(pack,"category",_m_category);
if(res){
throw ::idl::McpackException(res) << BSL_EARG;
}
}
// @@uint32_t itemid;
{
int res=mc_pack_put_uint32(pack,"itemid",_m_itemid);
if(res){
throw ::idl::McpackException(res) << BSL_EARG;
}
}
// save '_unknown' field.
for(size_t i=0;i<_unknown.size();i++){
const mc_pack_item_t& item=_unknown.GetWithoutCheck<mc_pack_item_t>(i);
if(item.type==MC_PT_OBJ){
mc_pack_t* tmp=mc_pack_put_object(pack,mc_pack_get_subkey(item.key));
if(MC_PACK_PTR_ERR(tmp)){
throw ::idl::McpackException(tmp) << BSL_EARG;
}
const mc_pack_t* tmppack=0;
int res=mc_pack_get_pack_from_item(&item,&tmppack);
if(res<0){
throw ::idl::McpackException(res) << BSL_EARG;
}
res=mc_pack_copy_item(tmppack,tmp,0);
if(res<0){
throw ::idl::McpackException(res) << BSL_EARG;
}
mc_pack_finish(tmp);
}else if(item.type==MC_PT_ARR){
mc_pack_t* tmp=mc_pack_put_array(pack,mc_pack_get_subkey(item.key));
if(MC_PACK_PTR_ERR(tmp)){
throw ::idl::McpackException(tmp) << BSL_EARG;
}
const mc_pack_t* tmppack=0;
int res=mc_pack_get_array_from_item(&item,&tmppack);
if(res<0){
throw ::idl::McpackException(res) << BSL_EARG;
}
res=mc_pack_copy_item(tmppack,tmp,0);
if(res<0){
throw ::idl::McpackException(res) << BSL_EARG;
}
mc_pack_finish(tmp);
}else{
int res=mc_pack_put_item(pack,&item);
if(res<0){
throw ::idl::McpackException(res) << BSL_EARG;
}
}
}
// save '_ext' field.
for(size_t i=0;i<_ext.size();i++){
_ext[i]->save(pack);
}
return mc_pack_get_size(pack)-orig_size;
}
// @@class cntcmd
static void _mcpack2_load_cntcmd_src(const mc_pack_item_t*,cntcmd*);
static bsl::readmap<const char*,void (*)(const mc_pack_item_t*,cntcmd*),::idl::string_hash,::idl::string_equal> _mcpack2_load_cntcmd_readmap;
// static initialization.
static bool _mcpack2_load_cntcmd_static_init(){
std::vector< std::pair<const char*, void (*)(const mc_pack_item_t*,cntcmd*)> >_vec;
_vec.push_back(std::pair<const char*,void (*)(const mc_pack_item_t*,cntcmd*)>("src",_mcpack2_load_cntcmd_src));
_mcpack2_load_cntcmd_readmap.create(16*1);
_mcpack2_load_cntcmd_readmap.assign(_vec.begin(),_vec.end());
return true;
}
__attribute__((unused)) static bool _mcpack2_load_cntcmd_static_inited=_mcpack2_load_cntcmd_static_init();
// @@int32_t src;
static void _mcpack2_load_cntcmd_src(__attribute__((unused)) const mc_pack_item_t* item,cntcmd* self){
self->_flag[0 >> 3] |= (1 << (0 & 0x7));
 
__attribute__((unused)) int res=0;
__attribute__((unused)) size_t size=0;
res=mc_pack_get_int32_from_item(item,&(self->_m_src));
if(res){
throw ::idl::McpackWrongTypeException() << BSL_EARG << "src";
}
}
void cntcmd::LoadWithoutCheck(const mc_pack_t* pack){
if(MC_PACK_PTR_ERR(pack)){
throw ::idl::McpackException(pack) << BSL_EARG;
}
clear();
mc_pack_item_t item;
int res=mc_pack_first_item(pack,&item);
if(res && res!=MC_PE_NOT_FOUND){
throw ::idl::McpackException(res) << BSL_EARG;
}
if(res!=MC_PE_NOT_FOUND){
void (*func)(const mc_pack_item_t*,cntcmd*)=0;
do{
if(_mcpack2_load_cntcmd_readmap.get(mc_pack_get_subkey(item.key),&func)==bsl::HASH_EXIST){
func(&item,this);
}else{
bool push=true;
for(size_t i=0;i<_ext.size();i++){
if(_ext[i]->load(item)>=0){
push=false;
}
}
if(push){
unknown().push_back<mc_pack_item_t>(item);
}
}
}while(!mc_pack_next_item(&item,&item));
}
}
//for compatiblity.return 0 when it accepts item,else return -1
int cntcmd::load(const mc_pack_item_t& item){
void (*func)(const mc_pack_item_t*,cntcmd*)=0;
if(_mcpack2_load_cntcmd_readmap.get(mc_pack_get_subkey(item.key),&func)==bsl::HASH_EXIST){
func(&item,this);
return 0;
}
return -1;
}
void cntcmd::load(const mc_pack_t* pack){
LoadWithoutCheck(pack);
check();
}
size_t cntcmd::save(mc_pack_t* pack) const{
if(MC_PACK_PTR_ERR(pack)){
throw ::idl::McpackException(pack) << BSL_EARG;
}
size_t orig_size=mc_pack_get_size(pack);
// @@int32_t src;
{
int res=mc_pack_put_int32(pack,"src",_m_src);
if(res){
throw ::idl::McpackException(res) << BSL_EARG;
}
}
// save '_unknown' field.
for(size_t i=0;i<_unknown.size();i++){
const mc_pack_item_t& item=_unknown.GetWithoutCheck<mc_pack_item_t>(i);
if(item.type==MC_PT_OBJ){
mc_pack_t* tmp=mc_pack_put_object(pack,mc_pack_get_subkey(item.key));
if(MC_PACK_PTR_ERR(tmp)){
throw ::idl::McpackException(tmp) << BSL_EARG;
}
const mc_pack_t* tmppack=0;
int res=mc_pack_get_pack_from_item(&item,&tmppack);
if(res<0){
throw ::idl::McpackException(res) << BSL_EARG;
}
res=mc_pack_copy_item(tmppack,tmp,0);
if(res<0){
throw ::idl::McpackException(res) << BSL_EARG;
}
mc_pack_finish(tmp);
}else if(item.type==MC_PT_ARR){
mc_pack_t* tmp=mc_pack_put_array(pack,mc_pack_get_subkey(item.key));
if(MC_PACK_PTR_ERR(tmp)){
throw ::idl::McpackException(tmp) << BSL_EARG;
}
const mc_pack_t* tmppack=0;
int res=mc_pack_get_array_from_item(&item,&tmppack);
if(res<0){
throw ::idl::McpackException(res) << BSL_EARG;
}
res=mc_pack_copy_item(tmppack,tmp,0);
if(res<0){
throw ::idl::McpackException(res) << BSL_EARG;
}
mc_pack_finish(tmp);
}else{
int res=mc_pack_put_item(pack,&item);
if(res<0){
throw ::idl::McpackException(res) << BSL_EARG;
}
}
}
// save '_ext' field.
for(size_t i=0;i<_ext.size();i++){
_ext[i]->save(pack);
}
return mc_pack_get_size(pack)-orig_size;
}
// @@class listcmd
static void _mcpack2_load_listcmd_type(const mc_pack_item_t*,listcmd*);
static void _mcpack2_load_listcmd_page_len(const mc_pack_item_t*,listcmd*);
static void _mcpack2_load_listcmd_page_no(const mc_pack_item_t*,listcmd*);
static void _mcpack2_load_listcmd_src(const mc_pack_item_t*,listcmd*);
static bsl::readmap<const char*,void (*)(const mc_pack_item_t*,listcmd*),::idl::string_hash,::idl::string_equal> _mcpack2_load_listcmd_readmap;
// static initialization.
static bool _mcpack2_load_listcmd_static_init(){
std::vector< std::pair<const char*, void (*)(const mc_pack_item_t*,listcmd*)> >_vec;
_vec.push_back(std::pair<const char*,void (*)(const mc_pack_item_t*,listcmd*)>("type",_mcpack2_load_listcmd_type));
_vec.push_back(std::pair<const char*,void (*)(const mc_pack_item_t*,listcmd*)>("page_len",_mcpack2_load_listcmd_page_len));
_vec.push_back(std::pair<const char*,void (*)(const mc_pack_item_t*,listcmd*)>("page_no",_mcpack2_load_listcmd_page_no));
_vec.push_back(std::pair<const char*,void (*)(const mc_pack_item_t*,listcmd*)>("src",_mcpack2_load_listcmd_src));
_mcpack2_load_listcmd_readmap.create(16*4);
_mcpack2_load_listcmd_readmap.assign(_vec.begin(),_vec.end());
return true;
}
__attribute__((unused)) static bool _mcpack2_load_listcmd_static_inited=_mcpack2_load_listcmd_static_init();
// @@int32_t type;
static void _mcpack2_load_listcmd_type(__attribute__((unused)) const mc_pack_item_t* item,listcmd* self){
self->_flag[0 >> 3] |= (1 << (0 & 0x7));
 
__attribute__((unused)) int res=0;
__attribute__((unused)) size_t size=0;
res=mc_pack_get_int32_from_item(item,&(self->_m_type));
if(res){
throw ::idl::McpackWrongTypeException() << BSL_EARG << "type";
}
}
// @@int32_t page_len;
static void _mcpack2_load_listcmd_page_len(__attribute__((unused)) const mc_pack_item_t* item,listcmd* self){
self->_flag[1 >> 3] |= (1 << (1 & 0x7));
 
__attribute__((unused)) int res=0;
__attribute__((unused)) size_t size=0;
res=mc_pack_get_int32_from_item(item,&(self->_m_page_len));
if(res){
throw ::idl::McpackWrongTypeException() << BSL_EARG << "page_len";
}
}
// @@int32_t page_no;
static void _mcpack2_load_listcmd_page_no(__attribute__((unused)) const mc_pack_item_t* item,listcmd* self){
self->_flag[2 >> 3] |= (1 << (2 & 0x7));
 
__attribute__((unused)) int res=0;
__attribute__((unused)) size_t size=0;
res=mc_pack_get_int32_from_item(item,&(self->_m_page_no));
if(res){
throw ::idl::McpackWrongTypeException() << BSL_EARG << "page_no";
}
}
// @@int32_t src;
static void _mcpack2_load_listcmd_src(__attribute__((unused)) const mc_pack_item_t* item,listcmd* self){
self->_flag[3 >> 3] |= (1 << (3 & 0x7));
 
__attribute__((unused)) int res=0;
__attribute__((unused)) size_t size=0;
res=mc_pack_get_int32_from_item(item,&(self->_m_src));
if(res){
throw ::idl::McpackWrongTypeException() << BSL_EARG << "src";
}
}
void listcmd::LoadWithoutCheck(const mc_pack_t* pack){
if(MC_PACK_PTR_ERR(pack)){
throw ::idl::McpackException(pack) << BSL_EARG;
}
clear();
mc_pack_item_t item;
int res=mc_pack_first_item(pack,&item);
if(res && res!=MC_PE_NOT_FOUND){
throw ::idl::McpackException(res) << BSL_EARG;
}
if(res!=MC_PE_NOT_FOUND){
void (*func)(const mc_pack_item_t*,listcmd*)=0;
do{
if(_mcpack2_load_listcmd_readmap.get(mc_pack_get_subkey(item.key),&func)==bsl::HASH_EXIST){
func(&item,this);
}else{
bool push=true;
for(size_t i=0;i<_ext.size();i++){
if(_ext[i]->load(item)>=0){
push=false;
}
}
if(push){
unknown().push_back<mc_pack_item_t>(item);
}
}
}while(!mc_pack_next_item(&item,&item));
}
}
//for compatiblity.return 0 when it accepts item,else return -1
int listcmd::load(const mc_pack_item_t& item){
void (*func)(const mc_pack_item_t*,listcmd*)=0;
if(_mcpack2_load_listcmd_readmap.get(mc_pack_get_subkey(item.key),&func)==bsl::HASH_EXIST){
func(&item,this);
return 0;
}
return -1;
}
void listcmd::load(const mc_pack_t* pack){
LoadWithoutCheck(pack);
check();
}
size_t listcmd::save(mc_pack_t* pack) const{
if(MC_PACK_PTR_ERR(pack)){
throw ::idl::McpackException(pack) << BSL_EARG;
}
size_t orig_size=mc_pack_get_size(pack);
// @@int32_t type;
{
int res=mc_pack_put_int32(pack,"type",_m_type);
if(res){
throw ::idl::McpackException(res) << BSL_EARG;
}
}
// @@int32_t page_len;
{
int res=mc_pack_put_int32(pack,"page_len",_m_page_len);
if(res){
throw ::idl::McpackException(res) << BSL_EARG;
}
}
// @@int32_t page_no;
{
int res=mc_pack_put_int32(pack,"page_no",_m_page_no);
if(res){
throw ::idl::McpackException(res) << BSL_EARG;
}
}
// @@int32_t src;
{
int res=mc_pack_put_int32(pack,"src",_m_src);
if(res){
throw ::idl::McpackException(res) << BSL_EARG;
}
}
// save '_unknown' field.
for(size_t i=0;i<_unknown.size();i++){
const mc_pack_item_t& item=_unknown.GetWithoutCheck<mc_pack_item_t>(i);
if(item.type==MC_PT_OBJ){
mc_pack_t* tmp=mc_pack_put_object(pack,mc_pack_get_subkey(item.key));
if(MC_PACK_PTR_ERR(tmp)){
throw ::idl::McpackException(tmp) << BSL_EARG;
}
const mc_pack_t* tmppack=0;
int res=mc_pack_get_pack_from_item(&item,&tmppack);
if(res<0){
throw ::idl::McpackException(res) << BSL_EARG;
}
res=mc_pack_copy_item(tmppack,tmp,0);
if(res<0){
throw ::idl::McpackException(res) << BSL_EARG;
}
mc_pack_finish(tmp);
}else if(item.type==MC_PT_ARR){
mc_pack_t* tmp=mc_pack_put_array(pack,mc_pack_get_subkey(item.key));
if(MC_PACK_PTR_ERR(tmp)){
throw ::idl::McpackException(tmp) << BSL_EARG;
}
const mc_pack_t* tmppack=0;
int res=mc_pack_get_array_from_item(&item,&tmppack);
if(res<0){
throw ::idl::McpackException(res) << BSL_EARG;
}
res=mc_pack_copy_item(tmppack,tmp,0);
if(res<0){
throw ::idl::McpackException(res) << BSL_EARG;
}
mc_pack_finish(tmp);
}else{
int res=mc_pack_put_item(pack,&item);
if(res<0){
throw ::idl::McpackException(res) << BSL_EARG;
}
}
}
// save '_ext' field.
for(size_t i=0;i<_ext.size();i++){
_ext[i]->save(pack);
}
return mc_pack_get_size(pack)-orig_size;
}
// @@class ticketcmd
static void _mcpack2_load_ticketcmd_len(const mc_pack_item_t*,ticketcmd*);
static bsl::readmap<const char*,void (*)(const mc_pack_item_t*,ticketcmd*),::idl::string_hash,::idl::string_equal> _mcpack2_load_ticketcmd_readmap;
// static initialization.
static bool _mcpack2_load_ticketcmd_static_init(){
std::vector< std::pair<const char*, void (*)(const mc_pack_item_t*,ticketcmd*)> >_vec;
_vec.push_back(std::pair<const char*,void (*)(const mc_pack_item_t*,ticketcmd*)>("len",_mcpack2_load_ticketcmd_len));
_mcpack2_load_ticketcmd_readmap.create(16*1);
_mcpack2_load_ticketcmd_readmap.assign(_vec.begin(),_vec.end());
return true;
}
__attribute__((unused)) static bool _mcpack2_load_ticketcmd_static_inited=_mcpack2_load_ticketcmd_static_init();
// @@int32_t len;
static void _mcpack2_load_ticketcmd_len(__attribute__((unused)) const mc_pack_item_t* item,ticketcmd* self){
self->_flag[0 >> 3] |= (1 << (0 & 0x7));
 
__attribute__((unused)) int res=0;
__attribute__((unused)) size_t size=0;
res=mc_pack_get_int32_from_item(item,&(self->_m_len));
if(res){
throw ::idl::McpackWrongTypeException() << BSL_EARG << "len";
}
}
void ticketcmd::LoadWithoutCheck(const mc_pack_t* pack){
if(MC_PACK_PTR_ERR(pack)){
throw ::idl::McpackException(pack) << BSL_EARG;
}
clear();
mc_pack_item_t item;
int res=mc_pack_first_item(pack,&item);
if(res && res!=MC_PE_NOT_FOUND){
throw ::idl::McpackException(res) << BSL_EARG;
}
if(res!=MC_PE_NOT_FOUND){
void (*func)(const mc_pack_item_t*,ticketcmd*)=0;
do{
if(_mcpack2_load_ticketcmd_readmap.get(mc_pack_get_subkey(item.key),&func)==bsl::HASH_EXIST){
func(&item,this);
}else{
bool push=true;
for(size_t i=0;i<_ext.size();i++){
if(_ext[i]->load(item)>=0){
push=false;
}
}
if(push){
unknown().push_back<mc_pack_item_t>(item);
}
}
}while(!mc_pack_next_item(&item,&item));
}
}
//for compatiblity.return 0 when it accepts item,else return -1
int ticketcmd::load(const mc_pack_item_t& item){
void (*func)(const mc_pack_item_t*,ticketcmd*)=0;
if(_mcpack2_load_ticketcmd_readmap.get(mc_pack_get_subkey(item.key),&func)==bsl::HASH_EXIST){
func(&item,this);
return 0;
}
return -1;
}
void ticketcmd::load(const mc_pack_t* pack){
LoadWithoutCheck(pack);
check();
}
size_t ticketcmd::save(mc_pack_t* pack) const{
if(MC_PACK_PTR_ERR(pack)){
throw ::idl::McpackException(pack) << BSL_EARG;
}
size_t orig_size=mc_pack_get_size(pack);
// @@int32_t len;
{
int res=mc_pack_put_int32(pack,"len",_m_len);
if(res){
throw ::idl::McpackException(res) << BSL_EARG;
}
}
// save '_unknown' field.
for(size_t i=0;i<_unknown.size();i++){
const mc_pack_item_t& item=_unknown.GetWithoutCheck<mc_pack_item_t>(i);
if(item.type==MC_PT_OBJ){
mc_pack_t* tmp=mc_pack_put_object(pack,mc_pack_get_subkey(item.key));
if(MC_PACK_PTR_ERR(tmp)){
throw ::idl::McpackException(tmp) << BSL_EARG;
}
const mc_pack_t* tmppack=0;
int res=mc_pack_get_pack_from_item(&item,&tmppack);
if(res<0){
throw ::idl::McpackException(res) << BSL_EARG;
}
res=mc_pack_copy_item(tmppack,tmp,0);
if(res<0){
throw ::idl::McpackException(res) << BSL_EARG;
}
mc_pack_finish(tmp);
}else if(item.type==MC_PT_ARR){
mc_pack_t* tmp=mc_pack_put_array(pack,mc_pack_get_subkey(item.key));
if(MC_PACK_PTR_ERR(tmp)){
throw ::idl::McpackException(tmp) << BSL_EARG;
}
const mc_pack_t* tmppack=0;
int res=mc_pack_get_array_from_item(&item,&tmppack);
if(res<0){
throw ::idl::McpackException(res) << BSL_EARG;
}
res=mc_pack_copy_item(tmppack,tmp,0);
if(res<0){
throw ::idl::McpackException(res) << BSL_EARG;
}
mc_pack_finish(tmp);
}else{
int res=mc_pack_put_item(pack,&item);
if(res<0){
throw ::idl::McpackException(res) << BSL_EARG;
}
}
}
// save '_ext' field.
for(size_t i=0;i<_ext.size();i++){
_ext[i]->save(pack);
}
return mc_pack_get_size(pack)-orig_size;
}
// @@class piaocmd
static void _mcpack2_load_piaocmd_sub_cmd(const mc_pack_item_t*,piaocmd*);
static void _mcpack2_load_piaocmd_len(const mc_pack_item_t*,piaocmd*);
static void _mcpack2_load_piaocmd_artist_id(const mc_pack_item_t*,piaocmd*);
static void _mcpack2_load_piaocmd_top_len(const mc_pack_item_t*,piaocmd*);
static void _mcpack2_load_piaocmd_page_size(const mc_pack_item_t*,piaocmd*);
static void _mcpack2_load_piaocmd_page_number(const mc_pack_item_t*,piaocmd*);
static bsl::readmap<const char*,void (*)(const mc_pack_item_t*,piaocmd*),::idl::string_hash,::idl::string_equal> _mcpack2_load_piaocmd_readmap;
// static initialization.
static bool _mcpack2_load_piaocmd_static_init(){
std::vector< std::pair<const char*, void (*)(const mc_pack_item_t*,piaocmd*)> >_vec;
_vec.push_back(std::pair<const char*,void (*)(const mc_pack_item_t*,piaocmd*)>("sub_cmd",_mcpack2_load_piaocmd_sub_cmd));
_vec.push_back(std::pair<const char*,void (*)(const mc_pack_item_t*,piaocmd*)>("len",_mcpack2_load_piaocmd_len));
_vec.push_back(std::pair<const char*,void (*)(const mc_pack_item_t*,piaocmd*)>("artist_id",_mcpack2_load_piaocmd_artist_id));
_vec.push_back(std::pair<const char*,void (*)(const mc_pack_item_t*,piaocmd*)>("top_len",_mcpack2_load_piaocmd_top_len));
_vec.push_back(std::pair<const char*,void (*)(const mc_pack_item_t*,piaocmd*)>("page_size",_mcpack2_load_piaocmd_page_size));
_vec.push_back(std::pair<const char*,void (*)(const mc_pack_item_t*,piaocmd*)>("page_number",_mcpack2_load_piaocmd_page_number));
_mcpack2_load_piaocmd_readmap.create(16*6);
_mcpack2_load_piaocmd_readmap.assign(_vec.begin(),_vec.end());
return true;
}
__attribute__((unused)) static bool _mcpack2_load_piaocmd_static_inited=_mcpack2_load_piaocmd_static_init();
// @@uint32_t sub_cmd;
static void _mcpack2_load_piaocmd_sub_cmd(__attribute__((unused)) const mc_pack_item_t* item,piaocmd* self){
self->_flag[0 >> 3] |= (1 << (0 & 0x7));
 
__attribute__((unused)) int res=0;
__attribute__((unused)) size_t size=0;
res=mc_pack_get_uint32_from_item(item,&(self->_m_sub_cmd));
if(res){
throw ::idl::McpackWrongTypeException() << BSL_EARG << "sub_cmd";
}
}
// @@int32_t len=optional();
static void _mcpack2_load_piaocmd_len(__attribute__((unused)) const mc_pack_item_t* item,piaocmd* self){
self->_flag[1 >> 3] |= (1 << (1 & 0x7));
 
__attribute__((unused)) int res=0;
__attribute__((unused)) size_t size=0;
res=mc_pack_get_int32_from_item(item,&(self->_m_len));
if(res){
throw ::idl::McpackWrongTypeException() << BSL_EARG << "len";
}
}
// @@uint32_t artist_id=optional();
static void _mcpack2_load_piaocmd_artist_id(__attribute__((unused)) const mc_pack_item_t* item,piaocmd* self){
self->_flag[2 >> 3] |= (1 << (2 & 0x7));
 
__attribute__((unused)) int res=0;
__attribute__((unused)) size_t size=0;
res=mc_pack_get_uint32_from_item(item,&(self->_m_artist_id));
if(res){
throw ::idl::McpackWrongTypeException() << BSL_EARG << "artist_id";
}
}
// @@uint32_t top_len=optional();
static void _mcpack2_load_piaocmd_top_len(__attribute__((unused)) const mc_pack_item_t* item,piaocmd* self){
self->_flag[3 >> 3] |= (1 << (3 & 0x7));
 
__attribute__((unused)) int res=0;
__attribute__((unused)) size_t size=0;
res=mc_pack_get_uint32_from_item(item,&(self->_m_top_len));
if(res){
throw ::idl::McpackWrongTypeException() << BSL_EARG << "top_len";
}
}
// @@uint32_t page_size=optional();
static void _mcpack2_load_piaocmd_page_size(__attribute__((unused)) const mc_pack_item_t* item,piaocmd* self){
self->_flag[4 >> 3] |= (1 << (4 & 0x7));
 
__attribute__((unused)) int res=0;
__attribute__((unused)) size_t size=0;
res=mc_pack_get_uint32_from_item(item,&(self->_m_page_size));
if(res){
throw ::idl::McpackWrongTypeException() << BSL_EARG << "page_size";
}
}
// @@int32_t page_number=optional();
static void _mcpack2_load_piaocmd_page_number(__attribute__((unused)) const mc_pack_item_t* item,piaocmd* self){
self->_flag[5 >> 3] |= (1 << (5 & 0x7));
 
__attribute__((unused)) int res=0;
__attribute__((unused)) size_t size=0;
res=mc_pack_get_int32_from_item(item,&(self->_m_page_number));
if(res){
throw ::idl::McpackWrongTypeException() << BSL_EARG << "page_number";
}
}
void piaocmd::LoadWithoutCheck(const mc_pack_t* pack){
if(MC_PACK_PTR_ERR(pack)){
throw ::idl::McpackException(pack) << BSL_EARG;
}
clear();
mc_pack_item_t item;
int res=mc_pack_first_item(pack,&item);
if(res && res!=MC_PE_NOT_FOUND){
throw ::idl::McpackException(res) << BSL_EARG;
}
if(res!=MC_PE_NOT_FOUND){
void (*func)(const mc_pack_item_t*,piaocmd*)=0;
do{
if(_mcpack2_load_piaocmd_readmap.get(mc_pack_get_subkey(item.key),&func)==bsl::HASH_EXIST){
func(&item,this);
}else{
bool push=true;
for(size_t i=0;i<_ext.size();i++){
if(_ext[i]->load(item)>=0){
push=false;
}
}
if(push){
unknown().push_back<mc_pack_item_t>(item);
}
}
}while(!mc_pack_next_item(&item,&item));
}
}
//for compatiblity.return 0 when it accepts item,else return -1
int piaocmd::load(const mc_pack_item_t& item){
void (*func)(const mc_pack_item_t*,piaocmd*)=0;
if(_mcpack2_load_piaocmd_readmap.get(mc_pack_get_subkey(item.key),&func)==bsl::HASH_EXIST){
func(&item,this);
return 0;
}
return -1;
}
void piaocmd::load(const mc_pack_t* pack){
LoadWithoutCheck(pack);
check();
}
size_t piaocmd::save(mc_pack_t* pack) const{
if(MC_PACK_PTR_ERR(pack)){
throw ::idl::McpackException(pack) << BSL_EARG;
}
size_t orig_size=mc_pack_get_size(pack);
// @@uint32_t sub_cmd;
{
int res=mc_pack_put_uint32(pack,"sub_cmd",_m_sub_cmd);
if(res){
throw ::idl::McpackException(res) << BSL_EARG;
}
}
// @@int32_t len=optional();
if((_flag[1 >> 3] & (1 << (1 & 0x7)))){
int res=mc_pack_put_int32(pack,"len",_m_len);
if(res){
throw ::idl::McpackException(res) << BSL_EARG;
}
}
// @@uint32_t artist_id=optional();
if((_flag[2 >> 3] & (1 << (2 & 0x7)))){
int res=mc_pack_put_uint32(pack,"artist_id",_m_artist_id);
if(res){
throw ::idl::McpackException(res) << BSL_EARG;
}
}
// @@uint32_t top_len=optional();
if((_flag[3 >> 3] & (1 << (3 & 0x7)))){
int res=mc_pack_put_uint32(pack,"top_len",_m_top_len);
if(res){
throw ::idl::McpackException(res) << BSL_EARG;
}
}
// @@uint32_t page_size=optional();
if((_flag[4 >> 3] & (1 << (4 & 0x7)))){
int res=mc_pack_put_uint32(pack,"page_size",_m_page_size);
if(res){
throw ::idl::McpackException(res) << BSL_EARG;
}
}
// @@int32_t page_number=optional();
if((_flag[5 >> 3] & (1 << (5 & 0x7)))){
int res=mc_pack_put_int32(pack,"page_number",_m_page_number);
if(res){
throw ::idl::McpackException(res) << BSL_EARG;
}
}
// save '_unknown' field.
for(size_t i=0;i<_unknown.size();i++){
const mc_pack_item_t& item=_unknown.GetWithoutCheck<mc_pack_item_t>(i);
if(item.type==MC_PT_OBJ){
mc_pack_t* tmp=mc_pack_put_object(pack,mc_pack_get_subkey(item.key));
if(MC_PACK_PTR_ERR(tmp)){
throw ::idl::McpackException(tmp) << BSL_EARG;
}
const mc_pack_t* tmppack=0;
int res=mc_pack_get_pack_from_item(&item,&tmppack);
if(res<0){
throw ::idl::McpackException(res) << BSL_EARG;
}
res=mc_pack_copy_item(tmppack,tmp,0);
if(res<0){
throw ::idl::McpackException(res) << BSL_EARG;
}
mc_pack_finish(tmp);
}else if(item.type==MC_PT_ARR){
mc_pack_t* tmp=mc_pack_put_array(pack,mc_pack_get_subkey(item.key));
if(MC_PACK_PTR_ERR(tmp)){
throw ::idl::McpackException(tmp) << BSL_EARG;
}
const mc_pack_t* tmppack=0;
int res=mc_pack_get_array_from_item(&item,&tmppack);
if(res<0){
throw ::idl::McpackException(res) << BSL_EARG;
}
res=mc_pack_copy_item(tmppack,tmp,0);
if(res<0){
throw ::idl::McpackException(res) << BSL_EARG;
}
mc_pack_finish(tmp);
}else{
int res=mc_pack_put_item(pack,&item);
if(res<0){
throw ::idl::McpackException(res) << BSL_EARG;
}
}
}
// save '_ext' field.
for(size_t i=0;i<_ext.size();i++){
_ext[i]->save(pack);
}
return mc_pack_get_size(pack)-orig_size;
}
// @@class chlistcmd
static void _mcpack2_load_chlistcmd_cate_name(const mc_pack_item_t*,chlistcmd*);
static bsl::readmap<const char*,void (*)(const mc_pack_item_t*,chlistcmd*),::idl::string_hash,::idl::string_equal> _mcpack2_load_chlistcmd_readmap;
// static initialization.
static bool _mcpack2_load_chlistcmd_static_init(){
std::vector< std::pair<const char*, void (*)(const mc_pack_item_t*,chlistcmd*)> >_vec;
_vec.push_back(std::pair<const char*,void (*)(const mc_pack_item_t*,chlistcmd*)>("cate_name",_mcpack2_load_chlistcmd_cate_name));
_mcpack2_load_chlistcmd_readmap.create(16*1);
_mcpack2_load_chlistcmd_readmap.assign(_vec.begin(),_vec.end());
return true;
}
__attribute__((unused)) static bool _mcpack2_load_chlistcmd_static_inited=_mcpack2_load_chlistcmd_static_init();
// @@string cate_name;
static void _mcpack2_load_chlistcmd_cate_name(__attribute__((unused)) const mc_pack_item_t* item,chlistcmd* self){
self->_flag[0 >> 3] |= (1 << (0 & 0x7));
 
__attribute__((unused)) int res=0;
__attribute__((unused)) size_t size=0;
if(item->type!=MC_IT_TXT){
throw ::idl::McpackWrongTypeException() << BSL_EARG << "cate_name";
}
self->_m_cate_name.set_ptr(item->value,item->value_size-1);
}
void chlistcmd::LoadWithoutCheck(const mc_pack_t* pack){
if(MC_PACK_PTR_ERR(pack)){
throw ::idl::McpackException(pack) << BSL_EARG;
}
clear();
mc_pack_item_t item;
int res=mc_pack_first_item(pack,&item);
if(res && res!=MC_PE_NOT_FOUND){
throw ::idl::McpackException(res) << BSL_EARG;
}
if(res!=MC_PE_NOT_FOUND){
void (*func)(const mc_pack_item_t*,chlistcmd*)=0;
do{
if(_mcpack2_load_chlistcmd_readmap.get(mc_pack_get_subkey(item.key),&func)==bsl::HASH_EXIST){
func(&item,this);
}else{
bool push=true;
for(size_t i=0;i<_ext.size();i++){
if(_ext[i]->load(item)>=0){
push=false;
}
}
if(push){
unknown().push_back<mc_pack_item_t>(item);
}
}
}while(!mc_pack_next_item(&item,&item));
}
}
//for compatiblity.return 0 when it accepts item,else return -1
int chlistcmd::load(const mc_pack_item_t& item){
void (*func)(const mc_pack_item_t*,chlistcmd*)=0;
if(_mcpack2_load_chlistcmd_readmap.get(mc_pack_get_subkey(item.key),&func)==bsl::HASH_EXIST){
func(&item,this);
return 0;
}
return -1;
}
void chlistcmd::load(const mc_pack_t* pack){
LoadWithoutCheck(pack);
check();
}
size_t chlistcmd::save(mc_pack_t* pack) const{
if(MC_PACK_PTR_ERR(pack)){
throw ::idl::McpackException(pack) << BSL_EARG;
}
size_t orig_size=mc_pack_get_size(pack);
// @@string cate_name;
{
int res=mc_pack_put_str(pack,"cate_name",_m_cate_name.c_str());
if(res){
throw ::idl::McpackException(res) << BSL_EARG;
}
}
// save '_unknown' field.
for(size_t i=0;i<_unknown.size();i++){
const mc_pack_item_t& item=_unknown.GetWithoutCheck<mc_pack_item_t>(i);
if(item.type==MC_PT_OBJ){
mc_pack_t* tmp=mc_pack_put_object(pack,mc_pack_get_subkey(item.key));
if(MC_PACK_PTR_ERR(tmp)){
throw ::idl::McpackException(tmp) << BSL_EARG;
}
const mc_pack_t* tmppack=0;
int res=mc_pack_get_pack_from_item(&item,&tmppack);
if(res<0){
throw ::idl::McpackException(res) << BSL_EARG;
}
res=mc_pack_copy_item(tmppack,tmp,0);
if(res<0){
throw ::idl::McpackException(res) << BSL_EARG;
}
mc_pack_finish(tmp);
}else if(item.type==MC_PT_ARR){
mc_pack_t* tmp=mc_pack_put_array(pack,mc_pack_get_subkey(item.key));
if(MC_PACK_PTR_ERR(tmp)){
throw ::idl::McpackException(tmp) << BSL_EARG;
}
const mc_pack_t* tmppack=0;
int res=mc_pack_get_array_from_item(&item,&tmppack);
if(res<0){
throw ::idl::McpackException(res) << BSL_EARG;
}
res=mc_pack_copy_item(tmppack,tmp,0);
if(res<0){
throw ::idl::McpackException(res) << BSL_EARG;
}
mc_pack_finish(tmp);
}else{
int res=mc_pack_put_item(pack,&item);
if(res<0){
throw ::idl::McpackException(res) << BSL_EARG;
}
}
}
// save '_ext' field.
for(size_t i=0;i<_ext.size();i++){
_ext[i]->save(pack);
}
return mc_pack_get_size(pack)-orig_size;
}
// @@class playlistcmd
static void _mcpack2_load_playlistcmd_ch_name(const mc_pack_item_t*,playlistcmd*);
static bsl::readmap<const char*,void (*)(const mc_pack_item_t*,playlistcmd*),::idl::string_hash,::idl::string_equal> _mcpack2_load_playlistcmd_readmap;
// static initialization.
static bool _mcpack2_load_playlistcmd_static_init(){
std::vector< std::pair<const char*, void (*)(const mc_pack_item_t*,playlistcmd*)> >_vec;
_vec.push_back(std::pair<const char*,void (*)(const mc_pack_item_t*,playlistcmd*)>("ch_name",_mcpack2_load_playlistcmd_ch_name));
_mcpack2_load_playlistcmd_readmap.create(16*1);
_mcpack2_load_playlistcmd_readmap.assign(_vec.begin(),_vec.end());
return true;
}
__attribute__((unused)) static bool _mcpack2_load_playlistcmd_static_inited=_mcpack2_load_playlistcmd_static_init();
// @@string ch_name;
static void _mcpack2_load_playlistcmd_ch_name(__attribute__((unused)) const mc_pack_item_t* item,playlistcmd* self){
self->_flag[0 >> 3] |= (1 << (0 & 0x7));
 
__attribute__((unused)) int res=0;
__attribute__((unused)) size_t size=0;
if(item->type!=MC_IT_TXT){
throw ::idl::McpackWrongTypeException() << BSL_EARG << "ch_name";
}
self->_m_ch_name.set_ptr(item->value,item->value_size-1);
}
void playlistcmd::LoadWithoutCheck(const mc_pack_t* pack){
if(MC_PACK_PTR_ERR(pack)){
throw ::idl::McpackException(pack) << BSL_EARG;
}
clear();
mc_pack_item_t item;
int res=mc_pack_first_item(pack,&item);
if(res && res!=MC_PE_NOT_FOUND){
throw ::idl::McpackException(res) << BSL_EARG;
}
if(res!=MC_PE_NOT_FOUND){
void (*func)(const mc_pack_item_t*,playlistcmd*)=0;
do{
if(_mcpack2_load_playlistcmd_readmap.get(mc_pack_get_subkey(item.key),&func)==bsl::HASH_EXIST){
func(&item,this);
}else{
bool push=true;
for(size_t i=0;i<_ext.size();i++){
if(_ext[i]->load(item)>=0){
push=false;
}
}
if(push){
unknown().push_back<mc_pack_item_t>(item);
}
}
}while(!mc_pack_next_item(&item,&item));
}
}
//for compatiblity.return 0 when it accepts item,else return -1
int playlistcmd::load(const mc_pack_item_t& item){
void (*func)(const mc_pack_item_t*,playlistcmd*)=0;
if(_mcpack2_load_playlistcmd_readmap.get(mc_pack_get_subkey(item.key),&func)==bsl::HASH_EXIST){
func(&item,this);
return 0;
}
return -1;
}
void playlistcmd::load(const mc_pack_t* pack){
LoadWithoutCheck(pack);
check();
}
size_t playlistcmd::save(mc_pack_t* pack) const{
if(MC_PACK_PTR_ERR(pack)){
throw ::idl::McpackException(pack) << BSL_EARG;
}
size_t orig_size=mc_pack_get_size(pack);
// @@string ch_name;
{
int res=mc_pack_put_str(pack,"ch_name",_m_ch_name.c_str());
if(res){
throw ::idl::McpackException(res) << BSL_EARG;
}
}
// save '_unknown' field.
for(size_t i=0;i<_unknown.size();i++){
const mc_pack_item_t& item=_unknown.GetWithoutCheck<mc_pack_item_t>(i);
if(item.type==MC_PT_OBJ){
mc_pack_t* tmp=mc_pack_put_object(pack,mc_pack_get_subkey(item.key));
if(MC_PACK_PTR_ERR(tmp)){
throw ::idl::McpackException(tmp) << BSL_EARG;
}
const mc_pack_t* tmppack=0;
int res=mc_pack_get_pack_from_item(&item,&tmppack);
if(res<0){
throw ::idl::McpackException(res) << BSL_EARG;
}
res=mc_pack_copy_item(tmppack,tmp,0);
if(res<0){
throw ::idl::McpackException(res) << BSL_EARG;
}
mc_pack_finish(tmp);
}else if(item.type==MC_PT_ARR){
mc_pack_t* tmp=mc_pack_put_array(pack,mc_pack_get_subkey(item.key));
if(MC_PACK_PTR_ERR(tmp)){
throw ::idl::McpackException(tmp) << BSL_EARG;
}
const mc_pack_t* tmppack=0;
int res=mc_pack_get_array_from_item(&item,&tmppack);
if(res<0){
throw ::idl::McpackException(res) << BSL_EARG;
}
res=mc_pack_copy_item(tmppack,tmp,0);
if(res<0){
throw ::idl::McpackException(res) << BSL_EARG;
}
mc_pack_finish(tmp);
}else{
int res=mc_pack_put_item(pack,&item);
if(res<0){
throw ::idl::McpackException(res) << BSL_EARG;
}
}
}
// save '_ext' field.
for(size_t i=0;i<_ext.size();i++){
_ext[i]->save(pack);
}
return mc_pack_get_size(pack)-orig_size;
}
// @@class playactioncmd
static void _mcpack2_load_playactioncmd_ch_name(const mc_pack_item_t*,playactioncmd*);
static void _mcpack2_load_playactioncmd_item_id(const mc_pack_item_t*,playactioncmd*);
static void _mcpack2_load_playactioncmd_pack_item_ids(const mc_pack_item_t*,playactioncmd*);
static void _mcpack2_load_playactioncmd_action_no(const mc_pack_item_t*,playactioncmd*);
static bsl::readmap<const char*,void (*)(const mc_pack_item_t*,playactioncmd*),::idl::string_hash,::idl::string_equal> _mcpack2_load_playactioncmd_readmap;
// static initialization.
static bool _mcpack2_load_playactioncmd_static_init(){
std::vector< std::pair<const char*, void (*)(const mc_pack_item_t*,playactioncmd*)> >_vec;
_vec.push_back(std::pair<const char*,void (*)(const mc_pack_item_t*,playactioncmd*)>("ch_name",_mcpack2_load_playactioncmd_ch_name));
_vec.push_back(std::pair<const char*,void (*)(const mc_pack_item_t*,playactioncmd*)>("item_id",_mcpack2_load_playactioncmd_item_id));
_vec.push_back(std::pair<const char*,void (*)(const mc_pack_item_t*,playactioncmd*)>("pack_item_ids",_mcpack2_load_playactioncmd_pack_item_ids));
_vec.push_back(std::pair<const char*,void (*)(const mc_pack_item_t*,playactioncmd*)>("action_no",_mcpack2_load_playactioncmd_action_no));
_mcpack2_load_playactioncmd_readmap.create(16*4);
_mcpack2_load_playactioncmd_readmap.assign(_vec.begin(),_vec.end());
return true;
}
__attribute__((unused)) static bool _mcpack2_load_playactioncmd_static_inited=_mcpack2_load_playactioncmd_static_init();
// @@string ch_name;
static void _mcpack2_load_playactioncmd_ch_name(__attribute__((unused)) const mc_pack_item_t* item,playactioncmd* self){
self->_flag[0 >> 3] |= (1 << (0 & 0x7));
 
__attribute__((unused)) int res=0;
__attribute__((unused)) size_t size=0;
if(item->type!=MC_IT_TXT){
throw ::idl::McpackWrongTypeException() << BSL_EARG << "ch_name";
}
self->_m_ch_name.set_ptr(item->value,item->value_size-1);
}
// @@uint64_t item_id;
static void _mcpack2_load_playactioncmd_item_id(__attribute__((unused)) const mc_pack_item_t* item,playactioncmd* self){
self->_flag[1 >> 3] |= (1 << (1 & 0x7));
 
__attribute__((unused)) int res=0;
__attribute__((unused)) size_t size=0;
res=mc_pack_get_uint64_from_item(item,reinterpret_cast<mc_uint64_t*>(&(self->_m_item_id)));
if(res){
throw ::idl::McpackWrongTypeException() << BSL_EARG << "item_id";
}
}
// @@string pack_item_ids;
static void _mcpack2_load_playactioncmd_pack_item_ids(__attribute__((unused)) const mc_pack_item_t* item,playactioncmd* self){
self->_flag[2 >> 3] |= (1 << (2 & 0x7));
 
__attribute__((unused)) int res=0;
__attribute__((unused)) size_t size=0;
if(item->type!=MC_IT_TXT){
throw ::idl::McpackWrongTypeException() << BSL_EARG << "pack_item_ids";
}
self->_m_pack_item_ids.set_ptr(item->value,item->value_size-1);
}
// @@int32_t action_no;
static void _mcpack2_load_playactioncmd_action_no(__attribute__((unused)) const mc_pack_item_t* item,playactioncmd* self){
self->_flag[3 >> 3] |= (1 << (3 & 0x7));
 
__attribute__((unused)) int res=0;
__attribute__((unused)) size_t size=0;
res=mc_pack_get_int32_from_item(item,&(self->_m_action_no));
if(res){
throw ::idl::McpackWrongTypeException() << BSL_EARG << "action_no";
}
}
void playactioncmd::LoadWithoutCheck(const mc_pack_t* pack){
if(MC_PACK_PTR_ERR(pack)){
throw ::idl::McpackException(pack) << BSL_EARG;
}
clear();
mc_pack_item_t item;
int res=mc_pack_first_item(pack,&item);
if(res && res!=MC_PE_NOT_FOUND){
throw ::idl::McpackException(res) << BSL_EARG;
}
if(res!=MC_PE_NOT_FOUND){
void (*func)(const mc_pack_item_t*,playactioncmd*)=0;
do{
if(_mcpack2_load_playactioncmd_readmap.get(mc_pack_get_subkey(item.key),&func)==bsl::HASH_EXIST){
func(&item,this);
}else{
bool push=true;
for(size_t i=0;i<_ext.size();i++){
if(_ext[i]->load(item)>=0){
push=false;
}
}
if(push){
unknown().push_back<mc_pack_item_t>(item);
}
}
}while(!mc_pack_next_item(&item,&item));
}
}
//for compatiblity.return 0 when it accepts item,else return -1
int playactioncmd::load(const mc_pack_item_t& item){
void (*func)(const mc_pack_item_t*,playactioncmd*)=0;
if(_mcpack2_load_playactioncmd_readmap.get(mc_pack_get_subkey(item.key),&func)==bsl::HASH_EXIST){
func(&item,this);
return 0;
}
return -1;
}
void playactioncmd::load(const mc_pack_t* pack){
LoadWithoutCheck(pack);
check();
}
size_t playactioncmd::save(mc_pack_t* pack) const{
if(MC_PACK_PTR_ERR(pack)){
throw ::idl::McpackException(pack) << BSL_EARG;
}
size_t orig_size=mc_pack_get_size(pack);
// @@string ch_name;
{
int res=mc_pack_put_str(pack,"ch_name",_m_ch_name.c_str());
if(res){
throw ::idl::McpackException(res) << BSL_EARG;
}
}
// @@uint64_t item_id;
{
int res=mc_pack_put_uint64(pack,"item_id",_m_item_id);
if(res){
throw ::idl::McpackException(res) << BSL_EARG;
}
}
// @@string pack_item_ids;
{
int res=mc_pack_put_str(pack,"pack_item_ids",_m_pack_item_ids.c_str());
if(res){
throw ::idl::McpackException(res) << BSL_EARG;
}
}
// @@int32_t action_no;
{
int res=mc_pack_put_int32(pack,"action_no",_m_action_no);
if(res){
throw ::idl::McpackException(res) << BSL_EARG;
}
}
// save '_unknown' field.
for(size_t i=0;i<_unknown.size();i++){
const mc_pack_item_t& item=_unknown.GetWithoutCheck<mc_pack_item_t>(i);
if(item.type==MC_PT_OBJ){
mc_pack_t* tmp=mc_pack_put_object(pack,mc_pack_get_subkey(item.key));
if(MC_PACK_PTR_ERR(tmp)){
throw ::idl::McpackException(tmp) << BSL_EARG;
}
const mc_pack_t* tmppack=0;
int res=mc_pack_get_pack_from_item(&item,&tmppack);
if(res<0){
throw ::idl::McpackException(res) << BSL_EARG;
}
res=mc_pack_copy_item(tmppack,tmp,0);
if(res<0){
throw ::idl::McpackException(res) << BSL_EARG;
}
mc_pack_finish(tmp);
}else if(item.type==MC_PT_ARR){
mc_pack_t* tmp=mc_pack_put_array(pack,mc_pack_get_subkey(item.key));
if(MC_PACK_PTR_ERR(tmp)){
throw ::idl::McpackException(tmp) << BSL_EARG;
}
const mc_pack_t* tmppack=0;
int res=mc_pack_get_array_from_item(&item,&tmppack);
if(res<0){
throw ::idl::McpackException(res) << BSL_EARG;
}
res=mc_pack_copy_item(tmppack,tmp,0);
if(res<0){
throw ::idl::McpackException(res) << BSL_EARG;
}
mc_pack_finish(tmp);
}else{
int res=mc_pack_put_item(pack,&item);
if(res<0){
throw ::idl::McpackException(res) << BSL_EARG;
}
}
}
// save '_ext' field.
for(size_t i=0;i<_ext.size();i++){
_ext[i]->save(pack);
}
return mc_pack_get_size(pack)-orig_size;
}
// @@class coldstartreqcmd
static void _mcpack2_load_coldstartreqcmd_ch_name(const mc_pack_item_t*,coldstartreqcmd*);
static void _mcpack2_load_coldstartreqcmd_lovesinger(const mc_pack_item_t*,coldstartreqcmd*);
static bsl::readmap<const char*,void (*)(const mc_pack_item_t*,coldstartreqcmd*),::idl::string_hash,::idl::string_equal> _mcpack2_load_coldstartreqcmd_readmap;
// static initialization.
static bool _mcpack2_load_coldstartreqcmd_static_init(){
std::vector< std::pair<const char*, void (*)(const mc_pack_item_t*,coldstartreqcmd*)> >_vec;
_vec.push_back(std::pair<const char*,void (*)(const mc_pack_item_t*,coldstartreqcmd*)>("ch_name",_mcpack2_load_coldstartreqcmd_ch_name));
_vec.push_back(std::pair<const char*,void (*)(const mc_pack_item_t*,coldstartreqcmd*)>("lovesinger",_mcpack2_load_coldstartreqcmd_lovesinger));
_mcpack2_load_coldstartreqcmd_readmap.create(16*2);
_mcpack2_load_coldstartreqcmd_readmap.assign(_vec.begin(),_vec.end());
return true;
}
__attribute__((unused)) static bool _mcpack2_load_coldstartreqcmd_static_inited=_mcpack2_load_coldstartreqcmd_static_init();
// @@string ch_name;
static void _mcpack2_load_coldstartreqcmd_ch_name(__attribute__((unused)) const mc_pack_item_t* item,coldstartreqcmd* self){
self->_flag[0 >> 3] |= (1 << (0 & 0x7));
 
__attribute__((unused)) int res=0;
__attribute__((unused)) size_t size=0;
if(item->type!=MC_IT_TXT){
throw ::idl::McpackWrongTypeException() << BSL_EARG << "ch_name";
}
self->_m_ch_name.set_ptr(item->value,item->value_size-1);
}
// @@string lovesinger;
static void _mcpack2_load_coldstartreqcmd_lovesinger(__attribute__((unused)) const mc_pack_item_t* item,coldstartreqcmd* self){
self->_flag[1 >> 3] |= (1 << (1 & 0x7));
 
__attribute__((unused)) int res=0;
__attribute__((unused)) size_t size=0;
if(item->type!=MC_IT_TXT){
throw ::idl::McpackWrongTypeException() << BSL_EARG << "lovesinger";
}
self->_m_lovesinger.set_ptr(item->value,item->value_size-1);
}
void coldstartreqcmd::LoadWithoutCheck(const mc_pack_t* pack){
if(MC_PACK_PTR_ERR(pack)){
throw ::idl::McpackException(pack) << BSL_EARG;
}
clear();
mc_pack_item_t item;
int res=mc_pack_first_item(pack,&item);
if(res && res!=MC_PE_NOT_FOUND){
throw ::idl::McpackException(res) << BSL_EARG;
}
if(res!=MC_PE_NOT_FOUND){
void (*func)(const mc_pack_item_t*,coldstartreqcmd*)=0;
do{
if(_mcpack2_load_coldstartreqcmd_readmap.get(mc_pack_get_subkey(item.key),&func)==bsl::HASH_EXIST){
func(&item,this);
}else{
bool push=true;
for(size_t i=0;i<_ext.size();i++){
if(_ext[i]->load(item)>=0){
push=false;
}
}
if(push){
unknown().push_back<mc_pack_item_t>(item);
}
}
}while(!mc_pack_next_item(&item,&item));
}
}
//for compatiblity.return 0 when it accepts item,else return -1
int coldstartreqcmd::load(const mc_pack_item_t& item){
void (*func)(const mc_pack_item_t*,coldstartreqcmd*)=0;
if(_mcpack2_load_coldstartreqcmd_readmap.get(mc_pack_get_subkey(item.key),&func)==bsl::HASH_EXIST){
func(&item,this);
return 0;
}
return -1;
}
void coldstartreqcmd::load(const mc_pack_t* pack){
LoadWithoutCheck(pack);
check();
}
size_t coldstartreqcmd::save(mc_pack_t* pack) const{
if(MC_PACK_PTR_ERR(pack)){
throw ::idl::McpackException(pack) << BSL_EARG;
}
size_t orig_size=mc_pack_get_size(pack);
// @@string ch_name;
{
int res=mc_pack_put_str(pack,"ch_name",_m_ch_name.c_str());
if(res){
throw ::idl::McpackException(res) << BSL_EARG;
}
}
// @@string lovesinger;
{
int res=mc_pack_put_str(pack,"lovesinger",_m_lovesinger.c_str());
if(res){
throw ::idl::McpackException(res) << BSL_EARG;
}
}
// save '_unknown' field.
for(size_t i=0;i<_unknown.size();i++){
const mc_pack_item_t& item=_unknown.GetWithoutCheck<mc_pack_item_t>(i);
if(item.type==MC_PT_OBJ){
mc_pack_t* tmp=mc_pack_put_object(pack,mc_pack_get_subkey(item.key));
if(MC_PACK_PTR_ERR(tmp)){
throw ::idl::McpackException(tmp) << BSL_EARG;
}
const mc_pack_t* tmppack=0;
int res=mc_pack_get_pack_from_item(&item,&tmppack);
if(res<0){
throw ::idl::McpackException(res) << BSL_EARG;
}
res=mc_pack_copy_item(tmppack,tmp,0);
if(res<0){
throw ::idl::McpackException(res) << BSL_EARG;
}
mc_pack_finish(tmp);
}else if(item.type==MC_PT_ARR){
mc_pack_t* tmp=mc_pack_put_array(pack,mc_pack_get_subkey(item.key));
if(MC_PACK_PTR_ERR(tmp)){
throw ::idl::McpackException(tmp) << BSL_EARG;
}
const mc_pack_t* tmppack=0;
int res=mc_pack_get_array_from_item(&item,&tmppack);
if(res<0){
throw ::idl::McpackException(res) << BSL_EARG;
}
res=mc_pack_copy_item(tmppack,tmp,0);
if(res<0){
throw ::idl::McpackException(res) << BSL_EARG;
}
mc_pack_finish(tmp);
}else{
int res=mc_pack_put_item(pack,&item);
if(res<0){
throw ::idl::McpackException(res) << BSL_EARG;
}
}
}
// save '_ext' field.
for(size_t i=0;i<_ext.size();i++){
_ext[i]->save(pack);
}
return mc_pack_get_size(pack)-orig_size;
}
// @@class coldstartsingerlistcmd
static void _mcpack2_load_coldstartsingerlistcmd_ch_name(const mc_pack_item_t*,coldstartsingerlistcmd*);
static bsl::readmap<const char*,void (*)(const mc_pack_item_t*,coldstartsingerlistcmd*),::idl::string_hash,::idl::string_equal> _mcpack2_load_coldstartsingerlistcmd_readmap;
// static initialization.
static bool _mcpack2_load_coldstartsingerlistcmd_static_init(){
std::vector< std::pair<const char*, void (*)(const mc_pack_item_t*,coldstartsingerlistcmd*)> >_vec;
_vec.push_back(std::pair<const char*,void (*)(const mc_pack_item_t*,coldstartsingerlistcmd*)>("ch_name",_mcpack2_load_coldstartsingerlistcmd_ch_name));
_mcpack2_load_coldstartsingerlistcmd_readmap.create(16*1);
_mcpack2_load_coldstartsingerlistcmd_readmap.assign(_vec.begin(),_vec.end());
return true;
}
__attribute__((unused)) static bool _mcpack2_load_coldstartsingerlistcmd_static_inited=_mcpack2_load_coldstartsingerlistcmd_static_init();
// @@string ch_name;
static void _mcpack2_load_coldstartsingerlistcmd_ch_name(__attribute__((unused)) const mc_pack_item_t* item,coldstartsingerlistcmd* self){
self->_flag[0 >> 3] |= (1 << (0 & 0x7));
 
__attribute__((unused)) int res=0;
__attribute__((unused)) size_t size=0;
if(item->type!=MC_IT_TXT){
throw ::idl::McpackWrongTypeException() << BSL_EARG << "ch_name";
}
self->_m_ch_name.set_ptr(item->value,item->value_size-1);
}
void coldstartsingerlistcmd::LoadWithoutCheck(const mc_pack_t* pack){
if(MC_PACK_PTR_ERR(pack)){
throw ::idl::McpackException(pack) << BSL_EARG;
}
clear();
mc_pack_item_t item;
int res=mc_pack_first_item(pack,&item);
if(res && res!=MC_PE_NOT_FOUND){
throw ::idl::McpackException(res) << BSL_EARG;
}
if(res!=MC_PE_NOT_FOUND){
void (*func)(const mc_pack_item_t*,coldstartsingerlistcmd*)=0;
do{
if(_mcpack2_load_coldstartsingerlistcmd_readmap.get(mc_pack_get_subkey(item.key),&func)==bsl::HASH_EXIST){
func(&item,this);
}else{
bool push=true;
for(size_t i=0;i<_ext.size();i++){
if(_ext[i]->load(item)>=0){
push=false;
}
}
if(push){
unknown().push_back<mc_pack_item_t>(item);
}
}
}while(!mc_pack_next_item(&item,&item));
}
}
//for compatiblity.return 0 when it accepts item,else return -1
int coldstartsingerlistcmd::load(const mc_pack_item_t& item){
void (*func)(const mc_pack_item_t*,coldstartsingerlistcmd*)=0;
if(_mcpack2_load_coldstartsingerlistcmd_readmap.get(mc_pack_get_subkey(item.key),&func)==bsl::HASH_EXIST){
func(&item,this);
return 0;
}
return -1;
}
void coldstartsingerlistcmd::load(const mc_pack_t* pack){
LoadWithoutCheck(pack);
check();
}
size_t coldstartsingerlistcmd::save(mc_pack_t* pack) const{
if(MC_PACK_PTR_ERR(pack)){
throw ::idl::McpackException(pack) << BSL_EARG;
}
size_t orig_size=mc_pack_get_size(pack);
// @@string ch_name;
{
int res=mc_pack_put_str(pack,"ch_name",_m_ch_name.c_str());
if(res){
throw ::idl::McpackException(res) << BSL_EARG;
}
}
// save '_unknown' field.
for(size_t i=0;i<_unknown.size();i++){
const mc_pack_item_t& item=_unknown.GetWithoutCheck<mc_pack_item_t>(i);
if(item.type==MC_PT_OBJ){
mc_pack_t* tmp=mc_pack_put_object(pack,mc_pack_get_subkey(item.key));
if(MC_PACK_PTR_ERR(tmp)){
throw ::idl::McpackException(tmp) << BSL_EARG;
}
const mc_pack_t* tmppack=0;
int res=mc_pack_get_pack_from_item(&item,&tmppack);
if(res<0){
throw ::idl::McpackException(res) << BSL_EARG;
}
res=mc_pack_copy_item(tmppack,tmp,0);
if(res<0){
throw ::idl::McpackException(res) << BSL_EARG;
}
mc_pack_finish(tmp);
}else if(item.type==MC_PT_ARR){
mc_pack_t* tmp=mc_pack_put_array(pack,mc_pack_get_subkey(item.key));
if(MC_PACK_PTR_ERR(tmp)){
throw ::idl::McpackException(tmp) << BSL_EARG;
}
const mc_pack_t* tmppack=0;
int res=mc_pack_get_array_from_item(&item,&tmppack);
if(res<0){
throw ::idl::McpackException(res) << BSL_EARG;
}
res=mc_pack_copy_item(tmppack,tmp,0);
if(res<0){
throw ::idl::McpackException(res) << BSL_EARG;
}
mc_pack_finish(tmp);
}else{
int res=mc_pack_put_item(pack,&item);
if(res<0){
throw ::idl::McpackException(res) << BSL_EARG;
}
}
}
// save '_ext' field.
for(size_t i=0;i<_ext.size();i++){
_ext[i]->save(pack);
}
return mc_pack_get_size(pack)-orig_size;
}
// @@class newusercmd
static void _mcpack2_load_newusercmd_ch_name(const mc_pack_item_t*,newusercmd*);
static bsl::readmap<const char*,void (*)(const mc_pack_item_t*,newusercmd*),::idl::string_hash,::idl::string_equal> _mcpack2_load_newusercmd_readmap;
// static initialization.
static bool _mcpack2_load_newusercmd_static_init(){
std::vector< std::pair<const char*, void (*)(const mc_pack_item_t*,newusercmd*)> >_vec;
_vec.push_back(std::pair<const char*,void (*)(const mc_pack_item_t*,newusercmd*)>("ch_name",_mcpack2_load_newusercmd_ch_name));
_mcpack2_load_newusercmd_readmap.create(16*1);
_mcpack2_load_newusercmd_readmap.assign(_vec.begin(),_vec.end());
return true;
}
__attribute__((unused)) static bool _mcpack2_load_newusercmd_static_inited=_mcpack2_load_newusercmd_static_init();
// @@string ch_name;
static void _mcpack2_load_newusercmd_ch_name(__attribute__((unused)) const mc_pack_item_t* item,newusercmd* self){
self->_flag[0 >> 3] |= (1 << (0 & 0x7));
 
__attribute__((unused)) int res=0;
__attribute__((unused)) size_t size=0;
if(item->type!=MC_IT_TXT){
throw ::idl::McpackWrongTypeException() << BSL_EARG << "ch_name";
}
self->_m_ch_name.set_ptr(item->value,item->value_size-1);
}
void newusercmd::LoadWithoutCheck(const mc_pack_t* pack){
if(MC_PACK_PTR_ERR(pack)){
throw ::idl::McpackException(pack) << BSL_EARG;
}
clear();
mc_pack_item_t item;
int res=mc_pack_first_item(pack,&item);
if(res && res!=MC_PE_NOT_FOUND){
throw ::idl::McpackException(res) << BSL_EARG;
}
if(res!=MC_PE_NOT_FOUND){
void (*func)(const mc_pack_item_t*,newusercmd*)=0;
do{
if(_mcpack2_load_newusercmd_readmap.get(mc_pack_get_subkey(item.key),&func)==bsl::HASH_EXIST){
func(&item,this);
}else{
bool push=true;
for(size_t i=0;i<_ext.size();i++){
if(_ext[i]->load(item)>=0){
push=false;
}
}
if(push){
unknown().push_back<mc_pack_item_t>(item);
}
}
}while(!mc_pack_next_item(&item,&item));
}
}
//for compatiblity.return 0 when it accepts item,else return -1
int newusercmd::load(const mc_pack_item_t& item){
void (*func)(const mc_pack_item_t*,newusercmd*)=0;
if(_mcpack2_load_newusercmd_readmap.get(mc_pack_get_subkey(item.key),&func)==bsl::HASH_EXIST){
func(&item,this);
return 0;
}
return -1;
}
void newusercmd::load(const mc_pack_t* pack){
LoadWithoutCheck(pack);
check();
}
size_t newusercmd::save(mc_pack_t* pack) const{
if(MC_PACK_PTR_ERR(pack)){
throw ::idl::McpackException(pack) << BSL_EARG;
}
size_t orig_size=mc_pack_get_size(pack);
// @@string ch_name;
{
int res=mc_pack_put_str(pack,"ch_name",_m_ch_name.c_str());
if(res){
throw ::idl::McpackException(res) << BSL_EARG;
}
}
// save '_unknown' field.
for(size_t i=0;i<_unknown.size();i++){
const mc_pack_item_t& item=_unknown.GetWithoutCheck<mc_pack_item_t>(i);
if(item.type==MC_PT_OBJ){
mc_pack_t* tmp=mc_pack_put_object(pack,mc_pack_get_subkey(item.key));
if(MC_PACK_PTR_ERR(tmp)){
throw ::idl::McpackException(tmp) << BSL_EARG;
}
const mc_pack_t* tmppack=0;
int res=mc_pack_get_pack_from_item(&item,&tmppack);
if(res<0){
throw ::idl::McpackException(res) << BSL_EARG;
}
res=mc_pack_copy_item(tmppack,tmp,0);
if(res<0){
throw ::idl::McpackException(res) << BSL_EARG;
}
mc_pack_finish(tmp);
}else if(item.type==MC_PT_ARR){
mc_pack_t* tmp=mc_pack_put_array(pack,mc_pack_get_subkey(item.key));
if(MC_PACK_PTR_ERR(tmp)){
throw ::idl::McpackException(tmp) << BSL_EARG;
}
const mc_pack_t* tmppack=0;
int res=mc_pack_get_array_from_item(&item,&tmppack);
if(res<0){
throw ::idl::McpackException(res) << BSL_EARG;
}
res=mc_pack_copy_item(tmppack,tmp,0);
if(res<0){
throw ::idl::McpackException(res) << BSL_EARG;
}
mc_pack_finish(tmp);
}else{
int res=mc_pack_put_item(pack,&item);
if(res<0){
throw ::idl::McpackException(res) << BSL_EARG;
}
}
}
// save '_ext' field.
for(size_t i=0;i<_ext.size();i++){
_ext[i]->save(pack);
}
return mc_pack_get_size(pack)-orig_size;
}
// @@class usertagscmd
static void _mcpack2_load_usertagscmd_src(const mc_pack_item_t*,usertagscmd*);
static bsl::readmap<const char*,void (*)(const mc_pack_item_t*,usertagscmd*),::idl::string_hash,::idl::string_equal> _mcpack2_load_usertagscmd_readmap;
// static initialization.
static bool _mcpack2_load_usertagscmd_static_init(){
std::vector< std::pair<const char*, void (*)(const mc_pack_item_t*,usertagscmd*)> >_vec;
_vec.push_back(std::pair<const char*,void (*)(const mc_pack_item_t*,usertagscmd*)>("src",_mcpack2_load_usertagscmd_src));
_mcpack2_load_usertagscmd_readmap.create(16*1);
_mcpack2_load_usertagscmd_readmap.assign(_vec.begin(),_vec.end());
return true;
}
__attribute__((unused)) static bool _mcpack2_load_usertagscmd_static_inited=_mcpack2_load_usertagscmd_static_init();
// @@uint32_t src;
static void _mcpack2_load_usertagscmd_src(__attribute__((unused)) const mc_pack_item_t* item,usertagscmd* self){
self->_flag[0 >> 3] |= (1 << (0 & 0x7));
 
__attribute__((unused)) int res=0;
__attribute__((unused)) size_t size=0;
res=mc_pack_get_uint32_from_item(item,&(self->_m_src));
if(res){
throw ::idl::McpackWrongTypeException() << BSL_EARG << "src";
}
}
void usertagscmd::LoadWithoutCheck(const mc_pack_t* pack){
if(MC_PACK_PTR_ERR(pack)){
throw ::idl::McpackException(pack) << BSL_EARG;
}
clear();
mc_pack_item_t item;
int res=mc_pack_first_item(pack,&item);
if(res && res!=MC_PE_NOT_FOUND){
throw ::idl::McpackException(res) << BSL_EARG;
}
if(res!=MC_PE_NOT_FOUND){
void (*func)(const mc_pack_item_t*,usertagscmd*)=0;
do{
if(_mcpack2_load_usertagscmd_readmap.get(mc_pack_get_subkey(item.key),&func)==bsl::HASH_EXIST){
func(&item,this);
}else{
bool push=true;
for(size_t i=0;i<_ext.size();i++){
if(_ext[i]->load(item)>=0){
push=false;
}
}
if(push){
unknown().push_back<mc_pack_item_t>(item);
}
}
}while(!mc_pack_next_item(&item,&item));
}
}
//for compatiblity.return 0 when it accepts item,else return -1
int usertagscmd::load(const mc_pack_item_t& item){
void (*func)(const mc_pack_item_t*,usertagscmd*)=0;
if(_mcpack2_load_usertagscmd_readmap.get(mc_pack_get_subkey(item.key),&func)==bsl::HASH_EXIST){
func(&item,this);
return 0;
}
return -1;
}
void usertagscmd::load(const mc_pack_t* pack){
LoadWithoutCheck(pack);
check();
}
size_t usertagscmd::save(mc_pack_t* pack) const{
if(MC_PACK_PTR_ERR(pack)){
throw ::idl::McpackException(pack) << BSL_EARG;
}
size_t orig_size=mc_pack_get_size(pack);
// @@uint32_t src;
{
int res=mc_pack_put_uint32(pack,"src",_m_src);
if(res){
throw ::idl::McpackException(res) << BSL_EARG;
}
}
// save '_unknown' field.
for(size_t i=0;i<_unknown.size();i++){
const mc_pack_item_t& item=_unknown.GetWithoutCheck<mc_pack_item_t>(i);
if(item.type==MC_PT_OBJ){
mc_pack_t* tmp=mc_pack_put_object(pack,mc_pack_get_subkey(item.key));
if(MC_PACK_PTR_ERR(tmp)){
throw ::idl::McpackException(tmp) << BSL_EARG;
}
const mc_pack_t* tmppack=0;
int res=mc_pack_get_pack_from_item(&item,&tmppack);
if(res<0){
throw ::idl::McpackException(res) << BSL_EARG;
}
res=mc_pack_copy_item(tmppack,tmp,0);
if(res<0){
throw ::idl::McpackException(res) << BSL_EARG;
}
mc_pack_finish(tmp);
}else if(item.type==MC_PT_ARR){
mc_pack_t* tmp=mc_pack_put_array(pack,mc_pack_get_subkey(item.key));
if(MC_PACK_PTR_ERR(tmp)){
throw ::idl::McpackException(tmp) << BSL_EARG;
}
const mc_pack_t* tmppack=0;
int res=mc_pack_get_array_from_item(&item,&tmppack);
if(res<0){
throw ::idl::McpackException(res) << BSL_EARG;
}
res=mc_pack_copy_item(tmppack,tmp,0);
if(res<0){
throw ::idl::McpackException(res) << BSL_EARG;
}
mc_pack_finish(tmp);
}else{
int res=mc_pack_put_item(pack,&item);
if(res<0){
throw ::idl::McpackException(res) << BSL_EARG;
}
}
}
// save '_ext' field.
for(size_t i=0;i<_ext.size();i++){
_ext[i]->save(pack);
}
return mc_pack_get_size(pack)-orig_size;
}
// @@class cmd
const int32_t cmd::k_rf(-1);
const ::idl::string cmd::k_username(&_common_pool,"");
const uint32_t cmd::k_uid(0);
const ::idl::string cmd::k_baiduid(&_common_pool,"");
static void _mcpack2_load_cmd_rf(const mc_pack_item_t*,cmd*);
static void _mcpack2_load_cmd_username(const mc_pack_item_t*,cmd*);
static void _mcpack2_load_cmd_uid(const mc_pack_item_t*,cmd*);
static void _mcpack2_load_cmd_baiduid(const mc_pack_item_t*,cmd*);
static void _mcpack2_load_cmd_pc(const mc_pack_item_t*,cmd*);
static void _mcpack2_load_cmd_fc(const mc_pack_item_t*,cmd*);
static void _mcpack2_load_cmd_mc(const mc_pack_item_t*,cmd*);
static void _mcpack2_load_cmd_cc(const mc_pack_item_t*,cmd*);
static void _mcpack2_load_cmd_lc(const mc_pack_item_t*,cmd*);
static void _mcpack2_load_cmd_chlc(const mc_pack_item_t*,cmd*);
static void _mcpack2_load_cmd_plc(const mc_pack_item_t*,cmd*);
static void _mcpack2_load_cmd_pac(const mc_pack_item_t*,cmd*);
static void _mcpack2_load_cmd_crc(const mc_pack_item_t*,cmd*);
static void _mcpack2_load_cmd_cslc(const mc_pack_item_t*,cmd*);
static void _mcpack2_load_cmd_nuc(const mc_pack_item_t*,cmd*);
static void _mcpack2_load_cmd_utag_cmd(const mc_pack_item_t*,cmd*);
static void _mcpack2_load_cmd_tic(const mc_pack_item_t*,cmd*);
static void _mcpack2_load_cmd_piao(const mc_pack_item_t*,cmd*);
static bsl::readmap<const char*,void (*)(const mc_pack_item_t*,cmd*),::idl::string_hash,::idl::string_equal> _mcpack2_load_cmd_readmap;
// static initialization.
static bool _mcpack2_load_cmd_static_init(){
std::vector< std::pair<const char*, void (*)(const mc_pack_item_t*,cmd*)> >_vec;
_vec.push_back(std::pair<const char*,void (*)(const mc_pack_item_t*,cmd*)>("rf",_mcpack2_load_cmd_rf));
_vec.push_back(std::pair<const char*,void (*)(const mc_pack_item_t*,cmd*)>("username",_mcpack2_load_cmd_username));
_vec.push_back(std::pair<const char*,void (*)(const mc_pack_item_t*,cmd*)>("uid",_mcpack2_load_cmd_uid));
_vec.push_back(std::pair<const char*,void (*)(const mc_pack_item_t*,cmd*)>("baiduid",_mcpack2_load_cmd_baiduid));
_vec.push_back(std::pair<const char*,void (*)(const mc_pack_item_t*,cmd*)>("pc",_mcpack2_load_cmd_pc));
_vec.push_back(std::pair<const char*,void (*)(const mc_pack_item_t*,cmd*)>("fc",_mcpack2_load_cmd_fc));
_vec.push_back(std::pair<const char*,void (*)(const mc_pack_item_t*,cmd*)>("mc",_mcpack2_load_cmd_mc));
_vec.push_back(std::pair<const char*,void (*)(const mc_pack_item_t*,cmd*)>("cc",_mcpack2_load_cmd_cc));
_vec.push_back(std::pair<const char*,void (*)(const mc_pack_item_t*,cmd*)>("lc",_mcpack2_load_cmd_lc));
_vec.push_back(std::pair<const char*,void (*)(const mc_pack_item_t*,cmd*)>("chlc",_mcpack2_load_cmd_chlc));
_vec.push_back(std::pair<const char*,void (*)(const mc_pack_item_t*,cmd*)>("plc",_mcpack2_load_cmd_plc));
_vec.push_back(std::pair<const char*,void (*)(const mc_pack_item_t*,cmd*)>("pac",_mcpack2_load_cmd_pac));
_vec.push_back(std::pair<const char*,void (*)(const mc_pack_item_t*,cmd*)>("crc",_mcpack2_load_cmd_crc));
_vec.push_back(std::pair<const char*,void (*)(const mc_pack_item_t*,cmd*)>("cslc",_mcpack2_load_cmd_cslc));
_vec.push_back(std::pair<const char*,void (*)(const mc_pack_item_t*,cmd*)>("nuc",_mcpack2_load_cmd_nuc));
_vec.push_back(std::pair<const char*,void (*)(const mc_pack_item_t*,cmd*)>("utag_cmd",_mcpack2_load_cmd_utag_cmd));
_vec.push_back(std::pair<const char*,void (*)(const mc_pack_item_t*,cmd*)>("tic",_mcpack2_load_cmd_tic));
_vec.push_back(std::pair<const char*,void (*)(const mc_pack_item_t*,cmd*)>("piao",_mcpack2_load_cmd_piao));
_mcpack2_load_cmd_readmap.create(16*18);
_mcpack2_load_cmd_readmap.assign(_vec.begin(),_vec.end());
return true;
}
__attribute__((unused)) static bool _mcpack2_load_cmd_static_inited=_mcpack2_load_cmd_static_init();
// @@int32_t rf=default(-1);
static void _mcpack2_load_cmd_rf(__attribute__((unused)) const mc_pack_item_t* item,cmd* self){
self->_flag[0 >> 3] |= (1 << (0 & 0x7));
 
__attribute__((unused)) int res=0;
__attribute__((unused)) size_t size=0;
res=mc_pack_get_int32_from_item(item,&(self->_m_rf));
if(res){
throw ::idl::McpackWrongTypeException() << BSL_EARG << "rf";
}
}
// @@string username=default("");
static void _mcpack2_load_cmd_username(__attribute__((unused)) const mc_pack_item_t* item,cmd* self){
self->_flag[1 >> 3] |= (1 << (1 & 0x7));
 
__attribute__((unused)) int res=0;
__attribute__((unused)) size_t size=0;
if(item->type!=MC_IT_TXT){
throw ::idl::McpackWrongTypeException() << BSL_EARG << "username";
}
self->_m_username.set_ptr(item->value,item->value_size-1);
}
// @@uint32_t uid=default(0);
static void _mcpack2_load_cmd_uid(__attribute__((unused)) const mc_pack_item_t* item,cmd* self){
self->_flag[2 >> 3] |= (1 << (2 & 0x7));
 
__attribute__((unused)) int res=0;
__attribute__((unused)) size_t size=0;
res=mc_pack_get_uint32_from_item(item,&(self->_m_uid));
if(res){
throw ::idl::McpackWrongTypeException() << BSL_EARG << "uid";
}
}
// @@string baiduid=default("");
static void _mcpack2_load_cmd_baiduid(__attribute__((unused)) const mc_pack_item_t* item,cmd* self){
self->_flag[3 >> 3] |= (1 << (3 & 0x7));
 
__attribute__((unused)) int res=0;
__attribute__((unused)) size_t size=0;
if(item->type!=MC_IT_TXT){
throw ::idl::McpackWrongTypeException() << BSL_EARG << "baiduid";
}
self->_m_baiduid.set_ptr(item->value,item->value_size-1);
}
// @@playercmd pc=optional();
static void _mcpack2_load_cmd_pc(__attribute__((unused)) const mc_pack_item_t* item,cmd* self){
self->_flag[4 >> 3] |= (1 << (4 & 0x7));
 
__attribute__((unused)) int res=0;
__attribute__((unused)) size_t size=0;
const mc_pack_t *pack=0;
res=mc_pack_get_pack_from_item(item,&pack);
if(res<0){
throw ::idl::McpackException(res) << BSL_EARG;
}
if(!self->_m_pc){
self->_m_pc=::idl::playercmd::create(self->_pool);
}
self->_m_pc->LoadWithoutCheck(pack);
}
// @@findcmd fc=optional();
static void _mcpack2_load_cmd_fc(__attribute__((unused)) const mc_pack_item_t* item,cmd* self){
self->_flag[5 >> 3] |= (1 << (5 & 0x7));
 
__attribute__((unused)) int res=0;
__attribute__((unused)) size_t size=0;
const mc_pack_t *pack=0;
res=mc_pack_get_pack_from_item(item,&pack);
if(res<0){
throw ::idl::McpackException(res) << BSL_EARG;
}
if(!self->_m_fc){
self->_m_fc=::idl::findcmd::create(self->_pool);
}
self->_m_fc->LoadWithoutCheck(pack);
}
// @@mgrcmd mc=optional();
static void _mcpack2_load_cmd_mc(__attribute__((unused)) const mc_pack_item_t* item,cmd* self){
self->_flag[6 >> 3] |= (1 << (6 & 0x7));
 
__attribute__((unused)) int res=0;
__attribute__((unused)) size_t size=0;
const mc_pack_t *pack=0;
res=mc_pack_get_pack_from_item(item,&pack);
if(res<0){
throw ::idl::McpackException(res) << BSL_EARG;
}
if(!self->_m_mc){
self->_m_mc=::idl::mgrcmd::create(self->_pool);
}
self->_m_mc->LoadWithoutCheck(pack);
}
// @@cntcmd cc=optional();
static void _mcpack2_load_cmd_cc(__attribute__((unused)) const mc_pack_item_t* item,cmd* self){
self->_flag[7 >> 3] |= (1 << (7 & 0x7));
 
__attribute__((unused)) int res=0;
__attribute__((unused)) size_t size=0;
const mc_pack_t *pack=0;
res=mc_pack_get_pack_from_item(item,&pack);
if(res<0){
throw ::idl::McpackException(res) << BSL_EARG;
}
if(!self->_m_cc){
self->_m_cc=::idl::cntcmd::create(self->_pool);
}
self->_m_cc->LoadWithoutCheck(pack);
}
// @@listcmd lc=optional();
static void _mcpack2_load_cmd_lc(__attribute__((unused)) const mc_pack_item_t* item,cmd* self){
self->_flag[8 >> 3] |= (1 << (8 & 0x7));
 
__attribute__((unused)) int res=0;
__attribute__((unused)) size_t size=0;
const mc_pack_t *pack=0;
res=mc_pack_get_pack_from_item(item,&pack);
if(res<0){
throw ::idl::McpackException(res) << BSL_EARG;
}
if(!self->_m_lc){
self->_m_lc=::idl::listcmd::create(self->_pool);
}
self->_m_lc->LoadWithoutCheck(pack);
}
// @@chlistcmd chlc=optional();
static void _mcpack2_load_cmd_chlc(__attribute__((unused)) const mc_pack_item_t* item,cmd* self){
self->_flag[9 >> 3] |= (1 << (9 & 0x7));
 
__attribute__((unused)) int res=0;
__attribute__((unused)) size_t size=0;
const mc_pack_t *pack=0;
res=mc_pack_get_pack_from_item(item,&pack);
if(res<0){
throw ::idl::McpackException(res) << BSL_EARG;
}
if(!self->_m_chlc){
self->_m_chlc=::idl::chlistcmd::create(self->_pool);
}
self->_m_chlc->LoadWithoutCheck(pack);
}
// @@playlistcmd plc=optional();
static void _mcpack2_load_cmd_plc(__attribute__((unused)) const mc_pack_item_t* item,cmd* self){
self->_flag[10 >> 3] |= (1 << (10 & 0x7));
 
__attribute__((unused)) int res=0;
__attribute__((unused)) size_t size=0;
const mc_pack_t *pack=0;
res=mc_pack_get_pack_from_item(item,&pack);
if(res<0){
throw ::idl::McpackException(res) << BSL_EARG;
}
if(!self->_m_plc){
self->_m_plc=::idl::playlistcmd::create(self->_pool);
}
self->_m_plc->LoadWithoutCheck(pack);
}
// @@playactioncmd pac=optional();
static void _mcpack2_load_cmd_pac(__attribute__((unused)) const mc_pack_item_t* item,cmd* self){
self->_flag[11 >> 3] |= (1 << (11 & 0x7));
 
__attribute__((unused)) int res=0;
__attribute__((unused)) size_t size=0;
const mc_pack_t *pack=0;
res=mc_pack_get_pack_from_item(item,&pack);
if(res<0){
throw ::idl::McpackException(res) << BSL_EARG;
}
if(!self->_m_pac){
self->_m_pac=::idl::playactioncmd::create(self->_pool);
}
self->_m_pac->LoadWithoutCheck(pack);
}
// @@coldstartreqcmd crc=optional();
static void _mcpack2_load_cmd_crc(__attribute__((unused)) const mc_pack_item_t* item,cmd* self){
self->_flag[12 >> 3] |= (1 << (12 & 0x7));
 
__attribute__((unused)) int res=0;
__attribute__((unused)) size_t size=0;
const mc_pack_t *pack=0;
res=mc_pack_get_pack_from_item(item,&pack);
if(res<0){
throw ::idl::McpackException(res) << BSL_EARG;
}
if(!self->_m_crc){
self->_m_crc=::idl::coldstartreqcmd::create(self->_pool);
}
self->_m_crc->LoadWithoutCheck(pack);
}
// @@coldstartsingerlistcmd cslc=optional();
static void _mcpack2_load_cmd_cslc(__attribute__((unused)) const mc_pack_item_t* item,cmd* self){
self->_flag[13 >> 3] |= (1 << (13 & 0x7));
 
__attribute__((unused)) int res=0;
__attribute__((unused)) size_t size=0;
const mc_pack_t *pack=0;
res=mc_pack_get_pack_from_item(item,&pack);
if(res<0){
throw ::idl::McpackException(res) << BSL_EARG;
}
if(!self->_m_cslc){
self->_m_cslc=::idl::coldstartsingerlistcmd::create(self->_pool);
}
self->_m_cslc->LoadWithoutCheck(pack);
}
// @@newusercmd nuc=optional();
static void _mcpack2_load_cmd_nuc(__attribute__((unused)) const mc_pack_item_t* item,cmd* self){
self->_flag[14 >> 3] |= (1 << (14 & 0x7));
 
__attribute__((unused)) int res=0;
__attribute__((unused)) size_t size=0;
const mc_pack_t *pack=0;
res=mc_pack_get_pack_from_item(item,&pack);
if(res<0){
throw ::idl::McpackException(res) << BSL_EARG;
}
if(!self->_m_nuc){
self->_m_nuc=::idl::newusercmd::create(self->_pool);
}
self->_m_nuc->LoadWithoutCheck(pack);
}
// @@usertagscmd utag_cmd=optional();
static void _mcpack2_load_cmd_utag_cmd(__attribute__((unused)) const mc_pack_item_t* item,cmd* self){
self->_flag[15 >> 3] |= (1 << (15 & 0x7));
 
__attribute__((unused)) int res=0;
__attribute__((unused)) size_t size=0;
const mc_pack_t *pack=0;
res=mc_pack_get_pack_from_item(item,&pack);
if(res<0){
throw ::idl::McpackException(res) << BSL_EARG;
}
if(!self->_m_utag_cmd){
self->_m_utag_cmd=::idl::usertagscmd::create(self->_pool);
}
self->_m_utag_cmd->LoadWithoutCheck(pack);
}
// @@ticketcmd tic=optional();
static void _mcpack2_load_cmd_tic(__attribute__((unused)) const mc_pack_item_t* item,cmd* self){
self->_flag[16 >> 3] |= (1 << (16 & 0x7));
 
__attribute__((unused)) int res=0;
__attribute__((unused)) size_t size=0;
const mc_pack_t *pack=0;
res=mc_pack_get_pack_from_item(item,&pack);
if(res<0){
throw ::idl::McpackException(res) << BSL_EARG;
}
if(!self->_m_tic){
self->_m_tic=::idl::ticketcmd::create(self->_pool);
}
self->_m_tic->LoadWithoutCheck(pack);
}
// @@piaocmd piao=optional();
static void _mcpack2_load_cmd_piao(__attribute__((unused)) const mc_pack_item_t* item,cmd* self){
self->_flag[17 >> 3] |= (1 << (17 & 0x7));
 
__attribute__((unused)) int res=0;
__attribute__((unused)) size_t size=0;
const mc_pack_t *pack=0;
res=mc_pack_get_pack_from_item(item,&pack);
if(res<0){
throw ::idl::McpackException(res) << BSL_EARG;
}
if(!self->_m_piao){
self->_m_piao=::idl::piaocmd::create(self->_pool);
}
self->_m_piao->LoadWithoutCheck(pack);
}
void cmd::LoadWithoutCheck(const mc_pack_t* pack){
if(MC_PACK_PTR_ERR(pack)){
throw ::idl::McpackException(pack) << BSL_EARG;
}
clear();
mc_pack_item_t item;
int res=mc_pack_first_item(pack,&item);
if(res && res!=MC_PE_NOT_FOUND){
throw ::idl::McpackException(res) << BSL_EARG;
}
if(res!=MC_PE_NOT_FOUND){
void (*func)(const mc_pack_item_t*,cmd*)=0;
do{
if(_mcpack2_load_cmd_readmap.get(mc_pack_get_subkey(item.key),&func)==bsl::HASH_EXIST){
func(&item,this);
}else{
bool push=true;
for(size_t i=0;i<_ext.size();i++){
if(_ext[i]->load(item)>=0){
push=false;
}
}
if(push){
unknown().push_back<mc_pack_item_t>(item);
}
}
}while(!mc_pack_next_item(&item,&item));
}
}
//for compatiblity.return 0 when it accepts item,else return -1
int cmd::load(const mc_pack_item_t& item){
void (*func)(const mc_pack_item_t*,cmd*)=0;
if(_mcpack2_load_cmd_readmap.get(mc_pack_get_subkey(item.key),&func)==bsl::HASH_EXIST){
func(&item,this);
return 0;
}
return -1;
}
void cmd::load(const mc_pack_t* pack){
LoadWithoutCheck(pack);
check();
}
size_t cmd::save(mc_pack_t* pack) const{
if(MC_PACK_PTR_ERR(pack)){
throw ::idl::McpackException(pack) << BSL_EARG;
}
size_t orig_size=mc_pack_get_size(pack);
// @@int32_t rf=default(-1);
{
int res=mc_pack_put_int32(pack,"rf",_m_rf);
if(res){
throw ::idl::McpackException(res) << BSL_EARG;
}
}
// @@string username=default("");
{
int res=mc_pack_put_str(pack,"username",_m_username.c_str());
if(res){
throw ::idl::McpackException(res) << BSL_EARG;
}
}
// @@uint32_t uid=default(0);
{
int res=mc_pack_put_uint32(pack,"uid",_m_uid);
if(res){
throw ::idl::McpackException(res) << BSL_EARG;
}
}
// @@string baiduid=default("");
{
int res=mc_pack_put_str(pack,"baiduid",_m_baiduid.c_str());
if(res){
throw ::idl::McpackException(res) << BSL_EARG;
}
}
// @@playercmd pc=optional();
if((_flag[4 >> 3] & (1 << (4 & 0x7)))){
mc_pack_t* subpack=mc_pack_put_object(pack,"pc");
if(MC_PACK_PTR_ERR(subpack)){
throw ::idl::McpackException(subpack) << BSL_EARG;
}
_m_pc->save(subpack);
mc_pack_finish(subpack);
}
// @@findcmd fc=optional();
if((_flag[5 >> 3] & (1 << (5 & 0x7)))){
mc_pack_t* subpack=mc_pack_put_object(pack,"fc");
if(MC_PACK_PTR_ERR(subpack)){
throw ::idl::McpackException(subpack) << BSL_EARG;
}
_m_fc->save(subpack);
mc_pack_finish(subpack);
}
// @@mgrcmd mc=optional();
if((_flag[6 >> 3] & (1 << (6 & 0x7)))){
mc_pack_t* subpack=mc_pack_put_object(pack,"mc");
if(MC_PACK_PTR_ERR(subpack)){
throw ::idl::McpackException(subpack) << BSL_EARG;
}
_m_mc->save(subpack);
mc_pack_finish(subpack);
}
// @@cntcmd cc=optional();
if((_flag[7 >> 3] & (1 << (7 & 0x7)))){
mc_pack_t* subpack=mc_pack_put_object(pack,"cc");
if(MC_PACK_PTR_ERR(subpack)){
throw ::idl::McpackException(subpack) << BSL_EARG;
}
_m_cc->save(subpack);
mc_pack_finish(subpack);
}
// @@listcmd lc=optional();
if((_flag[8 >> 3] & (1 << (8 & 0x7)))){
mc_pack_t* subpack=mc_pack_put_object(pack,"lc");
if(MC_PACK_PTR_ERR(subpack)){
throw ::idl::McpackException(subpack) << BSL_EARG;
}
_m_lc->save(subpack);
mc_pack_finish(subpack);
}
// @@chlistcmd chlc=optional();
if((_flag[9 >> 3] & (1 << (9 & 0x7)))){
mc_pack_t* subpack=mc_pack_put_object(pack,"chlc");
if(MC_PACK_PTR_ERR(subpack)){
throw ::idl::McpackException(subpack) << BSL_EARG;
}
_m_chlc->save(subpack);
mc_pack_finish(subpack);
}
// @@playlistcmd plc=optional();
if((_flag[10 >> 3] & (1 << (10 & 0x7)))){
mc_pack_t* subpack=mc_pack_put_object(pack,"plc");
if(MC_PACK_PTR_ERR(subpack)){
throw ::idl::McpackException(subpack) << BSL_EARG;
}
_m_plc->save(subpack);
mc_pack_finish(subpack);
}
// @@playactioncmd pac=optional();
if((_flag[11 >> 3] & (1 << (11 & 0x7)))){
mc_pack_t* subpack=mc_pack_put_object(pack,"pac");
if(MC_PACK_PTR_ERR(subpack)){
throw ::idl::McpackException(subpack) << BSL_EARG;
}
_m_pac->save(subpack);
mc_pack_finish(subpack);
}
// @@coldstartreqcmd crc=optional();
if((_flag[12 >> 3] & (1 << (12 & 0x7)))){
mc_pack_t* subpack=mc_pack_put_object(pack,"crc");
if(MC_PACK_PTR_ERR(subpack)){
throw ::idl::McpackException(subpack) << BSL_EARG;
}
_m_crc->save(subpack);
mc_pack_finish(subpack);
}
// @@coldstartsingerlistcmd cslc=optional();
if((_flag[13 >> 3] & (1 << (13 & 0x7)))){
mc_pack_t* subpack=mc_pack_put_object(pack,"cslc");
if(MC_PACK_PTR_ERR(subpack)){
throw ::idl::McpackException(subpack) << BSL_EARG;
}
_m_cslc->save(subpack);
mc_pack_finish(subpack);
}
// @@newusercmd nuc=optional();
if((_flag[14 >> 3] & (1 << (14 & 0x7)))){
mc_pack_t* subpack=mc_pack_put_object(pack,"nuc");
if(MC_PACK_PTR_ERR(subpack)){
throw ::idl::McpackException(subpack) << BSL_EARG;
}
_m_nuc->save(subpack);
mc_pack_finish(subpack);
}
// @@usertagscmd utag_cmd=optional();
if((_flag[15 >> 3] & (1 << (15 & 0x7)))){
mc_pack_t* subpack=mc_pack_put_object(pack,"utag_cmd");
if(MC_PACK_PTR_ERR(subpack)){
throw ::idl::McpackException(subpack) << BSL_EARG;
}
_m_utag_cmd->save(subpack);
mc_pack_finish(subpack);
}
// @@ticketcmd tic=optional();
if((_flag[16 >> 3] & (1 << (16 & 0x7)))){
mc_pack_t* subpack=mc_pack_put_object(pack,"tic");
if(MC_PACK_PTR_ERR(subpack)){
throw ::idl::McpackException(subpack) << BSL_EARG;
}
_m_tic->save(subpack);
mc_pack_finish(subpack);
}
// @@piaocmd piao=optional();
if((_flag[17 >> 3] & (1 << (17 & 0x7)))){
mc_pack_t* subpack=mc_pack_put_object(pack,"piao");
if(MC_PACK_PTR_ERR(subpack)){
throw ::idl::McpackException(subpack) << BSL_EARG;
}
_m_piao->save(subpack);
mc_pack_finish(subpack);
}
// save '_unknown' field.
for(size_t i=0;i<_unknown.size();i++){
const mc_pack_item_t& item=_unknown.GetWithoutCheck<mc_pack_item_t>(i);
if(item.type==MC_PT_OBJ){
mc_pack_t* tmp=mc_pack_put_object(pack,mc_pack_get_subkey(item.key));
if(MC_PACK_PTR_ERR(tmp)){
throw ::idl::McpackException(tmp) << BSL_EARG;
}
const mc_pack_t* tmppack=0;
int res=mc_pack_get_pack_from_item(&item,&tmppack);
if(res<0){
throw ::idl::McpackException(res) << BSL_EARG;
}
res=mc_pack_copy_item(tmppack,tmp,0);
if(res<0){
throw ::idl::McpackException(res) << BSL_EARG;
}
mc_pack_finish(tmp);
}else if(item.type==MC_PT_ARR){
mc_pack_t* tmp=mc_pack_put_array(pack,mc_pack_get_subkey(item.key));
if(MC_PACK_PTR_ERR(tmp)){
throw ::idl::McpackException(tmp) << BSL_EARG;
}
const mc_pack_t* tmppack=0;
int res=mc_pack_get_array_from_item(&item,&tmppack);
if(res<0){
throw ::idl::McpackException(res) << BSL_EARG;
}
res=mc_pack_copy_item(tmppack,tmp,0);
if(res<0){
throw ::idl::McpackException(res) << BSL_EARG;
}
mc_pack_finish(tmp);
}else{
int res=mc_pack_put_item(pack,&item);
if(res<0){
throw ::idl::McpackException(res) << BSL_EARG;
}
}
}
// save '_ext' field.
for(size_t i=0;i<_ext.size();i++){
_ext[i]->save(pack);
}
return mc_pack_get_size(pack)-orig_size;
}
} // namespace idl
