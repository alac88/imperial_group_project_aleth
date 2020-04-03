
#include "souffle/CompiledSouffle.h"

extern "C" {
}

namespace souffle {
using namespace ram;
struct t_btree_4__1_0_2_3__2__15 {
using t_tuple = Tuple<RamDomain, 4>;
using t_ind_0 = btree_set<t_tuple, index_utils::comparator<1,0,2,3>>;
t_ind_0 ind_0;
using iterator = t_ind_0::iterator;
struct context {
t_ind_0::operation_hints hints_0;
};
context createContext() { return context(); }
bool insert(const t_tuple& t) {
context h;
return insert(t, h);
}
bool insert(const t_tuple& t, context& h) {
if (ind_0.insert(t, h.hints_0)) {
return true;
} else return false;
}
bool insert(const RamDomain* ramDomain) {
RamDomain data[4];
std::copy(ramDomain, ramDomain + 4, data);
const t_tuple& tuple = reinterpret_cast<const t_tuple&>(data);
context h;
return insert(tuple, h);
}
bool insert(RamDomain a0,RamDomain a1,RamDomain a2,RamDomain a3) {
RamDomain data[4] = {a0,a1,a2,a3};
return insert(data);
}
bool contains(const t_tuple& t, context& h) const {
return ind_0.contains(t, h.hints_0);
}
bool contains(const t_tuple& t) const {
context h;
return contains(t, h);
}
std::size_t size() const {
return ind_0.size();
}
iterator find(const t_tuple& t, context& h) const {
return ind_0.find(t, h.hints_0);
}
iterator find(const t_tuple& t) const {
context h;
return find(t, h);
}
range<iterator> equalRange_0(const t_tuple& t, context& h) const {
return range<iterator>(ind_0.begin(),ind_0.end());
}
range<iterator> equalRange_0(const t_tuple& t) const {
return range<iterator>(ind_0.begin(),ind_0.end());
}
range<t_ind_0::iterator> equalRange_2(const t_tuple& t, context& h) const {
t_tuple low(t); t_tuple high(t);
low[0] = MIN_RAM_DOMAIN;
high[0] = MAX_RAM_DOMAIN;
low[2] = MIN_RAM_DOMAIN;
high[2] = MAX_RAM_DOMAIN;
low[3] = MIN_RAM_DOMAIN;
high[3] = MAX_RAM_DOMAIN;
return make_range(ind_0.lower_bound(low, h.hints_0), ind_0.upper_bound(high, h.hints_0));
}
range<t_ind_0::iterator> equalRange_2(const t_tuple& t) const {
context h;
return equalRange_2(t, h);
}
range<t_ind_0::iterator> equalRange_15(const t_tuple& t, context& h) const {
auto pos = ind_0.find(t, h.hints_0);
auto fin = ind_0.end();
if (pos != fin) {fin = pos; ++fin;}
return make_range(pos, fin);
}
range<t_ind_0::iterator> equalRange_15(const t_tuple& t) const {
context h;
return equalRange_15(t, h);
}
bool empty() const {
return ind_0.empty();
}
std::vector<range<iterator>> partition() const {
return ind_0.getChunks(400);
}
void purge() {
ind_0.clear();
}
iterator begin() const {
return ind_0.begin();
}
iterator end() const {
return ind_0.end();
}
void printHintStatistics(std::ostream& o, const std::string prefix) const {
const auto& stats_0 = ind_0.getHintStatistics();
o << prefix << "arity 4 direct b-tree index [1,0,2,3]: (hits/misses/total)\n";
o << prefix << "Insert: " << stats_0.inserts.getHits() << "/" << stats_0.inserts.getMisses() << "/" << stats_0.inserts.getAccesses() << "\n";
o << prefix << "Contains: " << stats_0.contains.getHits() << "/" << stats_0.contains.getMisses() << "/" << stats_0.contains.getAccesses() << "\n";
o << prefix << "Lower-bound: " << stats_0.lower_bound.getHits() << "/" << stats_0.lower_bound.getMisses() << "/" << stats_0.lower_bound.getAccesses() << "\n";
o << prefix << "Upper-bound: " << stats_0.upper_bound.getHits() << "/" << stats_0.upper_bound.getMisses() << "/" << stats_0.upper_bound.getAccesses() << "\n";
}
};
struct t_btree_4__1_2_0_3__6__15 {
using t_tuple = Tuple<RamDomain, 4>;
using t_ind_0 = btree_set<t_tuple, index_utils::comparator<1,2,0,3>>;
t_ind_0 ind_0;
using iterator = t_ind_0::iterator;
struct context {
t_ind_0::operation_hints hints_0;
};
context createContext() { return context(); }
bool insert(const t_tuple& t) {
context h;
return insert(t, h);
}
bool insert(const t_tuple& t, context& h) {
if (ind_0.insert(t, h.hints_0)) {
return true;
} else return false;
}
bool insert(const RamDomain* ramDomain) {
RamDomain data[4];
std::copy(ramDomain, ramDomain + 4, data);
const t_tuple& tuple = reinterpret_cast<const t_tuple&>(data);
context h;
return insert(tuple, h);
}
bool insert(RamDomain a0,RamDomain a1,RamDomain a2,RamDomain a3) {
RamDomain data[4] = {a0,a1,a2,a3};
return insert(data);
}
bool contains(const t_tuple& t, context& h) const {
return ind_0.contains(t, h.hints_0);
}
bool contains(const t_tuple& t) const {
context h;
return contains(t, h);
}
std::size_t size() const {
return ind_0.size();
}
iterator find(const t_tuple& t, context& h) const {
return ind_0.find(t, h.hints_0);
}
iterator find(const t_tuple& t) const {
context h;
return find(t, h);
}
range<iterator> equalRange_0(const t_tuple& t, context& h) const {
return range<iterator>(ind_0.begin(),ind_0.end());
}
range<iterator> equalRange_0(const t_tuple& t) const {
return range<iterator>(ind_0.begin(),ind_0.end());
}
range<t_ind_0::iterator> equalRange_6(const t_tuple& t, context& h) const {
t_tuple low(t); t_tuple high(t);
low[0] = MIN_RAM_DOMAIN;
high[0] = MAX_RAM_DOMAIN;
low[3] = MIN_RAM_DOMAIN;
high[3] = MAX_RAM_DOMAIN;
return make_range(ind_0.lower_bound(low, h.hints_0), ind_0.upper_bound(high, h.hints_0));
}
range<t_ind_0::iterator> equalRange_6(const t_tuple& t) const {
context h;
return equalRange_6(t, h);
}
range<t_ind_0::iterator> equalRange_15(const t_tuple& t, context& h) const {
auto pos = ind_0.find(t, h.hints_0);
auto fin = ind_0.end();
if (pos != fin) {fin = pos; ++fin;}
return make_range(pos, fin);
}
range<t_ind_0::iterator> equalRange_15(const t_tuple& t) const {
context h;
return equalRange_15(t, h);
}
bool empty() const {
return ind_0.empty();
}
std::vector<range<iterator>> partition() const {
return ind_0.getChunks(400);
}
void purge() {
ind_0.clear();
}
iterator begin() const {
return ind_0.begin();
}
iterator end() const {
return ind_0.end();
}
void printHintStatistics(std::ostream& o, const std::string prefix) const {
const auto& stats_0 = ind_0.getHintStatistics();
o << prefix << "arity 4 direct b-tree index [1,2,0,3]: (hits/misses/total)\n";
o << prefix << "Insert: " << stats_0.inserts.getHits() << "/" << stats_0.inserts.getMisses() << "/" << stats_0.inserts.getAccesses() << "\n";
o << prefix << "Contains: " << stats_0.contains.getHits() << "/" << stats_0.contains.getMisses() << "/" << stats_0.contains.getAccesses() << "\n";
o << prefix << "Lower-bound: " << stats_0.lower_bound.getHits() << "/" << stats_0.lower_bound.getMisses() << "/" << stats_0.lower_bound.getAccesses() << "\n";
o << prefix << "Upper-bound: " << stats_0.upper_bound.getHits() << "/" << stats_0.upper_bound.getMisses() << "/" << stats_0.upper_bound.getAccesses() << "\n";
}
};
struct t_btree_2__0_1__3 {
using t_tuple = Tuple<RamDomain, 2>;
using t_ind_0 = btree_set<t_tuple, index_utils::comparator<0,1>>;
t_ind_0 ind_0;
using iterator = t_ind_0::iterator;
struct context {
t_ind_0::operation_hints hints_0;
};
context createContext() { return context(); }
bool insert(const t_tuple& t) {
context h;
return insert(t, h);
}
bool insert(const t_tuple& t, context& h) {
if (ind_0.insert(t, h.hints_0)) {
return true;
} else return false;
}
bool insert(const RamDomain* ramDomain) {
RamDomain data[2];
std::copy(ramDomain, ramDomain + 2, data);
const t_tuple& tuple = reinterpret_cast<const t_tuple&>(data);
context h;
return insert(tuple, h);
}
bool insert(RamDomain a0,RamDomain a1) {
RamDomain data[2] = {a0,a1};
return insert(data);
}
bool contains(const t_tuple& t, context& h) const {
return ind_0.contains(t, h.hints_0);
}
bool contains(const t_tuple& t) const {
context h;
return contains(t, h);
}
std::size_t size() const {
return ind_0.size();
}
iterator find(const t_tuple& t, context& h) const {
return ind_0.find(t, h.hints_0);
}
iterator find(const t_tuple& t) const {
context h;
return find(t, h);
}
range<iterator> equalRange_0(const t_tuple& t, context& h) const {
return range<iterator>(ind_0.begin(),ind_0.end());
}
range<iterator> equalRange_0(const t_tuple& t) const {
return range<iterator>(ind_0.begin(),ind_0.end());
}
range<t_ind_0::iterator> equalRange_3(const t_tuple& t, context& h) const {
auto pos = ind_0.find(t, h.hints_0);
auto fin = ind_0.end();
if (pos != fin) {fin = pos; ++fin;}
return make_range(pos, fin);
}
range<t_ind_0::iterator> equalRange_3(const t_tuple& t) const {
context h;
return equalRange_3(t, h);
}
bool empty() const {
return ind_0.empty();
}
std::vector<range<iterator>> partition() const {
return ind_0.getChunks(400);
}
void purge() {
ind_0.clear();
}
iterator begin() const {
return ind_0.begin();
}
iterator end() const {
return ind_0.end();
}
void printHintStatistics(std::ostream& o, const std::string prefix) const {
const auto& stats_0 = ind_0.getHintStatistics();
o << prefix << "arity 2 direct b-tree index [0,1]: (hits/misses/total)\n";
o << prefix << "Insert: " << stats_0.inserts.getHits() << "/" << stats_0.inserts.getMisses() << "/" << stats_0.inserts.getAccesses() << "\n";
o << prefix << "Contains: " << stats_0.contains.getHits() << "/" << stats_0.contains.getMisses() << "/" << stats_0.contains.getAccesses() << "\n";
o << prefix << "Lower-bound: " << stats_0.lower_bound.getHits() << "/" << stats_0.lower_bound.getMisses() << "/" << stats_0.lower_bound.getAccesses() << "\n";
o << prefix << "Upper-bound: " << stats_0.upper_bound.getHits() << "/" << stats_0.upper_bound.getMisses() << "/" << stats_0.upper_bound.getAccesses() << "\n";
}
};
struct t_btree_1__0__1 {
using t_tuple = Tuple<RamDomain, 1>;
using t_ind_0 = btree_set<t_tuple, index_utils::comparator<0>>;
t_ind_0 ind_0;
using iterator = t_ind_0::iterator;
struct context {
t_ind_0::operation_hints hints_0;
};
context createContext() { return context(); }
bool insert(const t_tuple& t) {
context h;
return insert(t, h);
}
bool insert(const t_tuple& t, context& h) {
if (ind_0.insert(t, h.hints_0)) {
return true;
} else return false;
}
bool insert(const RamDomain* ramDomain) {
RamDomain data[1];
std::copy(ramDomain, ramDomain + 1, data);
const t_tuple& tuple = reinterpret_cast<const t_tuple&>(data);
context h;
return insert(tuple, h);
}
bool insert(RamDomain a0) {
RamDomain data[1] = {a0};
return insert(data);
}
bool contains(const t_tuple& t, context& h) const {
return ind_0.contains(t, h.hints_0);
}
bool contains(const t_tuple& t) const {
context h;
return contains(t, h);
}
std::size_t size() const {
return ind_0.size();
}
iterator find(const t_tuple& t, context& h) const {
return ind_0.find(t, h.hints_0);
}
iterator find(const t_tuple& t) const {
context h;
return find(t, h);
}
range<iterator> equalRange_0(const t_tuple& t, context& h) const {
return range<iterator>(ind_0.begin(),ind_0.end());
}
range<iterator> equalRange_0(const t_tuple& t) const {
return range<iterator>(ind_0.begin(),ind_0.end());
}
range<t_ind_0::iterator> equalRange_1(const t_tuple& t, context& h) const {
auto pos = ind_0.find(t, h.hints_0);
auto fin = ind_0.end();
if (pos != fin) {fin = pos; ++fin;}
return make_range(pos, fin);
}
range<t_ind_0::iterator> equalRange_1(const t_tuple& t) const {
context h;
return equalRange_1(t, h);
}
bool empty() const {
return ind_0.empty();
}
std::vector<range<iterator>> partition() const {
return ind_0.getChunks(400);
}
void purge() {
ind_0.clear();
}
iterator begin() const {
return ind_0.begin();
}
iterator end() const {
return ind_0.end();
}
void printHintStatistics(std::ostream& o, const std::string prefix) const {
const auto& stats_0 = ind_0.getHintStatistics();
o << prefix << "arity 1 direct b-tree index [0]: (hits/misses/total)\n";
o << prefix << "Insert: " << stats_0.inserts.getHits() << "/" << stats_0.inserts.getMisses() << "/" << stats_0.inserts.getAccesses() << "\n";
o << prefix << "Contains: " << stats_0.contains.getHits() << "/" << stats_0.contains.getMisses() << "/" << stats_0.contains.getAccesses() << "\n";
o << prefix << "Lower-bound: " << stats_0.lower_bound.getHits() << "/" << stats_0.lower_bound.getMisses() << "/" << stats_0.lower_bound.getAccesses() << "\n";
o << prefix << "Upper-bound: " << stats_0.upper_bound.getHits() << "/" << stats_0.upper_bound.getMisses() << "/" << stats_0.upper_bound.getAccesses() << "\n";
}
};
struct t_btree_4__0_1_2_3__15 {
using t_tuple = Tuple<RamDomain, 4>;
using t_ind_0 = btree_set<t_tuple, index_utils::comparator<0,1,2,3>>;
t_ind_0 ind_0;
using iterator = t_ind_0::iterator;
struct context {
t_ind_0::operation_hints hints_0;
};
context createContext() { return context(); }
bool insert(const t_tuple& t) {
context h;
return insert(t, h);
}
bool insert(const t_tuple& t, context& h) {
if (ind_0.insert(t, h.hints_0)) {
return true;
} else return false;
}
bool insert(const RamDomain* ramDomain) {
RamDomain data[4];
std::copy(ramDomain, ramDomain + 4, data);
const t_tuple& tuple = reinterpret_cast<const t_tuple&>(data);
context h;
return insert(tuple, h);
}
bool insert(RamDomain a0,RamDomain a1,RamDomain a2,RamDomain a3) {
RamDomain data[4] = {a0,a1,a2,a3};
return insert(data);
}
bool contains(const t_tuple& t, context& h) const {
return ind_0.contains(t, h.hints_0);
}
bool contains(const t_tuple& t) const {
context h;
return contains(t, h);
}
std::size_t size() const {
return ind_0.size();
}
iterator find(const t_tuple& t, context& h) const {
return ind_0.find(t, h.hints_0);
}
iterator find(const t_tuple& t) const {
context h;
return find(t, h);
}
range<iterator> equalRange_0(const t_tuple& t, context& h) const {
return range<iterator>(ind_0.begin(),ind_0.end());
}
range<iterator> equalRange_0(const t_tuple& t) const {
return range<iterator>(ind_0.begin(),ind_0.end());
}
range<t_ind_0::iterator> equalRange_15(const t_tuple& t, context& h) const {
auto pos = ind_0.find(t, h.hints_0);
auto fin = ind_0.end();
if (pos != fin) {fin = pos; ++fin;}
return make_range(pos, fin);
}
range<t_ind_0::iterator> equalRange_15(const t_tuple& t) const {
context h;
return equalRange_15(t, h);
}
bool empty() const {
return ind_0.empty();
}
std::vector<range<iterator>> partition() const {
return ind_0.getChunks(400);
}
void purge() {
ind_0.clear();
}
iterator begin() const {
return ind_0.begin();
}
iterator end() const {
return ind_0.end();
}
void printHintStatistics(std::ostream& o, const std::string prefix) const {
const auto& stats_0 = ind_0.getHintStatistics();
o << prefix << "arity 4 direct b-tree index [0,1,2,3]: (hits/misses/total)\n";
o << prefix << "Insert: " << stats_0.inserts.getHits() << "/" << stats_0.inserts.getMisses() << "/" << stats_0.inserts.getAccesses() << "\n";
o << prefix << "Contains: " << stats_0.contains.getHits() << "/" << stats_0.contains.getMisses() << "/" << stats_0.contains.getAccesses() << "\n";
o << prefix << "Lower-bound: " << stats_0.lower_bound.getHits() << "/" << stats_0.lower_bound.getMisses() << "/" << stats_0.lower_bound.getAccesses() << "\n";
o << prefix << "Upper-bound: " << stats_0.upper_bound.getHits() << "/" << stats_0.upper_bound.getMisses() << "/" << stats_0.upper_bound.getAccesses() << "\n";
}
};
struct t_btree_5__0_1_2_3_4__31 {
using t_tuple = Tuple<RamDomain, 5>;
using t_ind_0 = btree_set<t_tuple, index_utils::comparator<0,1,2,3,4>>;
t_ind_0 ind_0;
using iterator = t_ind_0::iterator;
struct context {
t_ind_0::operation_hints hints_0;
};
context createContext() { return context(); }
bool insert(const t_tuple& t) {
context h;
return insert(t, h);
}
bool insert(const t_tuple& t, context& h) {
if (ind_0.insert(t, h.hints_0)) {
return true;
} else return false;
}
bool insert(const RamDomain* ramDomain) {
RamDomain data[5];
std::copy(ramDomain, ramDomain + 5, data);
const t_tuple& tuple = reinterpret_cast<const t_tuple&>(data);
context h;
return insert(tuple, h);
}
bool insert(RamDomain a0,RamDomain a1,RamDomain a2,RamDomain a3,RamDomain a4) {
RamDomain data[5] = {a0,a1,a2,a3,a4};
return insert(data);
}
bool contains(const t_tuple& t, context& h) const {
return ind_0.contains(t, h.hints_0);
}
bool contains(const t_tuple& t) const {
context h;
return contains(t, h);
}
std::size_t size() const {
return ind_0.size();
}
iterator find(const t_tuple& t, context& h) const {
return ind_0.find(t, h.hints_0);
}
iterator find(const t_tuple& t) const {
context h;
return find(t, h);
}
range<iterator> equalRange_0(const t_tuple& t, context& h) const {
return range<iterator>(ind_0.begin(),ind_0.end());
}
range<iterator> equalRange_0(const t_tuple& t) const {
return range<iterator>(ind_0.begin(),ind_0.end());
}
range<t_ind_0::iterator> equalRange_31(const t_tuple& t, context& h) const {
auto pos = ind_0.find(t, h.hints_0);
auto fin = ind_0.end();
if (pos != fin) {fin = pos; ++fin;}
return make_range(pos, fin);
}
range<t_ind_0::iterator> equalRange_31(const t_tuple& t) const {
context h;
return equalRange_31(t, h);
}
bool empty() const {
return ind_0.empty();
}
std::vector<range<iterator>> partition() const {
return ind_0.getChunks(400);
}
void purge() {
ind_0.clear();
}
iterator begin() const {
return ind_0.begin();
}
iterator end() const {
return ind_0.end();
}
void printHintStatistics(std::ostream& o, const std::string prefix) const {
const auto& stats_0 = ind_0.getHintStatistics();
o << prefix << "arity 5 direct b-tree index [0,1,2,3,4]: (hits/misses/total)\n";
o << prefix << "Insert: " << stats_0.inserts.getHits() << "/" << stats_0.inserts.getMisses() << "/" << stats_0.inserts.getAccesses() << "\n";
o << prefix << "Contains: " << stats_0.contains.getHits() << "/" << stats_0.contains.getMisses() << "/" << stats_0.contains.getAccesses() << "\n";
o << prefix << "Lower-bound: " << stats_0.lower_bound.getHits() << "/" << stats_0.lower_bound.getMisses() << "/" << stats_0.lower_bound.getAccesses() << "\n";
o << prefix << "Upper-bound: " << stats_0.upper_bound.getHits() << "/" << stats_0.upper_bound.getMisses() << "/" << stats_0.upper_bound.getAccesses() << "\n";
}
};

class Sf_DetectionLogic : public SouffleProgram {
private:
static inline bool regex_wrapper(const std::string& pattern, const std::string& text) {
   bool result = false; 
   try { result = std::regex_match(text, std::regex(pattern)); } catch(...) { 
     std::cerr << "warning: wrong pattern provided for match(\"" << pattern << "\",\"" << text << "\").\n";
}
   return result;
}
private:
static inline std::string substr_wrapper(const std::string& str, size_t idx, size_t len) {
   std::string result; 
   try { result = str.substr(idx,len); } catch(...) { 
     std::cerr << "warning: wrong index position provided by substr(\"";
     std::cerr << str << "\"," << (int32_t)idx << "," << (int32_t)len << ") functor.\n";
   } return result;
}
private:
static inline RamDomain wrapper_tonumber(const std::string& str) {
   RamDomain result=0; 
   try { result = stord(str); } catch(...) { 
     std::cerr << "error: wrong string provided by to_number(\"";
     std::cerr << str << "\") functor.\n";
     raise(SIGFPE);
   } return result;
}
public:
// -- initialize symbol table --
SymbolTable symTable
;// -- initialize record table --
RecordTable recordTable;
// -- Table: @delta_call
std::unique_ptr<t_btree_4__1_0_2_3__2__15> rel_1_delta_call = std::make_unique<t_btree_4__1_0_2_3__2__15>();
// -- Table: @new_call
std::unique_ptr<t_btree_4__1_0_2_3__2__15> rel_2_new_call = std::make_unique<t_btree_4__1_0_2_3__2__15>();
// -- Table: call
std::unique_ptr<t_btree_4__1_2_0_3__6__15> rel_3_call = std::make_unique<t_btree_4__1_2_0_3__6__15>();
souffle::RelationWrapper<0,t_btree_4__1_2_0_3__6__15,Tuple<RamDomain,4>,4,0> wrapper_rel_3_call;
// -- Table: call_entry
std::unique_ptr<t_btree_2__0_1__3> rel_4_call_entry = std::make_unique<t_btree_2__0_1__3>();
souffle::RelationWrapper<1,t_btree_2__0_1__3,Tuple<RamDomain,2>,2,0> wrapper_rel_4_call_entry;
// -- Table: call_exit
std::unique_ptr<t_btree_1__0__1> rel_5_call_exit = std::make_unique<t_btree_1__0__1>();
souffle::RelationWrapper<2,t_btree_1__0__1,Tuple<RamDomain,1>,1,0> wrapper_rel_5_call_exit;
// -- Table: direct_call
std::unique_ptr<t_btree_4__0_1_2_3__15> rel_6_direct_call = std::make_unique<t_btree_4__0_1_2_3__15>();
souffle::RelationWrapper<3,t_btree_4__0_1_2_3__15,Tuple<RamDomain,4>,4,0> wrapper_rel_6_direct_call;
// -- Table: locked_ether
std::unique_ptr<t_btree_2__0_1__3> rel_7_locked_ether = std::make_unique<t_btree_2__0_1__3>();
souffle::RelationWrapper<4,t_btree_2__0_1__3,Tuple<RamDomain,2>,2,0> wrapper_rel_7_locked_ether;
// -- Table: reentrancy
std::unique_ptr<t_btree_5__0_1_2_3_4__31> rel_8_reentrancy = std::make_unique<t_btree_5__0_1_2_3_4__31>();
souffle::RelationWrapper<5,t_btree_5__0_1_2_3_4__31,Tuple<RamDomain,5>,5,0> wrapper_rel_8_reentrancy;
public:
Sf_DetectionLogic() : 
wrapper_rel_3_call(*rel_3_call,symTable,"call",std::array<const char *,4>{{"i:CallNum","s:EthAddress","s:EthAddress","i:IntSet[i:number]"}},std::array<const char *,4>{{"c","a1","a2","p"}}),

wrapper_rel_4_call_entry(*rel_4_call_entry,symTable,"call_entry",std::array<const char *,2>{{"i:gas","s:EthAddress"}},std::array<const char *,2>{{"g1","a1"}}),

wrapper_rel_5_call_exit(*rel_5_call_exit,symTable,"call_exit",std::array<const char *,1>{{"i:gas"}},std::array<const char *,1>{{"g2"}}),

wrapper_rel_6_direct_call(*rel_6_direct_call,symTable,"direct_call",std::array<const char *,4>{{"i:CallNum","s:EthAddress","s:EthAddress","i:NatNum[i:number]"}},std::array<const char *,4>{{"c","a1","a2","p"}}),

wrapper_rel_7_locked_ether(*rel_7_locked_ether,symTable,"locked_ether",std::array<const char *,2>{{"s:EthAddress","i:gas"}},std::array<const char *,2>{{"a1","g1"}}),

wrapper_rel_8_reentrancy(*rel_8_reentrancy,symTable,"reentrancy",std::array<const char *,5>{{"i:CallNum","s:EthAddress","s:EthAddress","i:IntSet[i:number]","i:IntSet[i:number]"}},std::array<const char *,5>{{"c","a1","a2","p","p2"}}){
addRelation("call",&wrapper_rel_3_call,false,false);
addRelation("call_entry",&wrapper_rel_4_call_entry,true,false);
addRelation("call_exit",&wrapper_rel_5_call_exit,true,false);
addRelation("direct_call",&wrapper_rel_6_direct_call,true,false);
addRelation("locked_ether",&wrapper_rel_7_locked_ether,false,true);
addRelation("reentrancy",&wrapper_rel_8_reentrancy,false,true);
}
~Sf_DetectionLogic() {
}
private:
void runFunction(std::string inputDirectory = ".", std::string outputDirectory = ".", bool performIO = false) {
SignalHandler::instance()->set();
std::atomic<size_t> iter(0);

#if defined(_OPENMP)
if (getNumThreads() > 0) {omp_set_num_threads(getNumThreads());}
#endif

// -- query evaluation --
if (performIO) {
try {std::map<std::string, std::string> directiveMap({{"IO","file"},{"filename","./direct_call.facts"},{"name","direct_call"}});
if (!inputDirectory.empty() && directiveMap["IO"] == "file" && directiveMap["filename"].front() != '/') {directiveMap["filename"] = inputDirectory + "/" + directiveMap["filename"];}
IODirectives ioDirectives(directiveMap);
IOSystem::getInstance().getReader(std::vector<RamTypeAttribute>({RamTypeAttribute::Signed,RamTypeAttribute::Symbol,RamTypeAttribute::Symbol,RamTypeAttribute::Signed}), symTable, ioDirectives, 0)->readAll(*rel_6_direct_call);
} catch (std::exception& e) {std::cerr << "Error loading data: " << e.what() << '\n';}
}
SignalHandler::instance()->setMsg(R"_(call(C,A1,A2,P) :- 
   direct_call(C,A1,A2,P).
in file /vol/project/2019/530/g1953010/souffle/MarkT/DetectionLogic.dl [30:1-30:98])_");
if(!(rel_6_direct_call->empty())) {
[&](){
CREATE_OP_CONTEXT(rel_3_call_op_ctxt,rel_3_call->createContext());
CREATE_OP_CONTEXT(rel_6_direct_call_op_ctxt,rel_6_direct_call->createContext());
for(const auto& env0 : *rel_6_direct_call) {
Tuple<RamDomain,4> tuple{{static_cast<RamDomain>(env0[0]),static_cast<RamDomain>(env0[1]),static_cast<RamDomain>(env0[2]),static_cast<RamDomain>(env0[3])}};
rel_3_call->insert(tuple,READ_OP_CONTEXT(rel_3_call_op_ctxt));
}
}
();}
[&](){
CREATE_OP_CONTEXT(rel_3_call_op_ctxt,rel_3_call->createContext());
CREATE_OP_CONTEXT(rel_1_delta_call_op_ctxt,rel_1_delta_call->createContext());
for(const auto& env0 : *rel_3_call) {
Tuple<RamDomain,4> tuple{{static_cast<RamDomain>(env0[0]),static_cast<RamDomain>(env0[1]),static_cast<RamDomain>(env0[2]),static_cast<RamDomain>(env0[3])}};
rel_1_delta_call->insert(tuple,READ_OP_CONTEXT(rel_1_delta_call_op_ctxt));
}
}
();iter = 0;
for(;;) {
SignalHandler::instance()->setMsg(R"_(call(C,A1,A2,P) :- 
   direct_call(C,A1,A3,P),
   call(_,A3,A2,_).
in file /vol/project/2019/530/g1953010/souffle/MarkT/DetectionLogic.dl [30:1-30:98])_");
if(!(rel_6_direct_call->empty()) && !(rel_1_delta_call->empty())) {
[&](){
CREATE_OP_CONTEXT(rel_2_new_call_op_ctxt,rel_2_new_call->createContext());
CREATE_OP_CONTEXT(rel_3_call_op_ctxt,rel_3_call->createContext());
CREATE_OP_CONTEXT(rel_1_delta_call_op_ctxt,rel_1_delta_call->createContext());
CREATE_OP_CONTEXT(rel_6_direct_call_op_ctxt,rel_6_direct_call->createContext());
for(const auto& env0 : *rel_6_direct_call) {
const Tuple<RamDomain,4> key{{0,env0[2],0,0}};
auto range = rel_1_delta_call->equalRange_2(key,READ_OP_CONTEXT(rel_1_delta_call_op_ctxt));
for(const auto& env1 : range) {
if( !(rel_3_call->contains(Tuple<RamDomain,4>{{env0[0],env0[1],env1[2],env0[3]}},READ_OP_CONTEXT(rel_3_call_op_ctxt)))) {
Tuple<RamDomain,4> tuple{{static_cast<RamDomain>(env0[0]),static_cast<RamDomain>(env0[1]),static_cast<RamDomain>(env1[2]),static_cast<RamDomain>(env0[3])}};
rel_2_new_call->insert(tuple,READ_OP_CONTEXT(rel_2_new_call_op_ctxt));
}
}
}
}
();}
if(rel_2_new_call->empty()) break;
[&](){
CREATE_OP_CONTEXT(rel_2_new_call_op_ctxt,rel_2_new_call->createContext());
CREATE_OP_CONTEXT(rel_3_call_op_ctxt,rel_3_call->createContext());
for(const auto& env0 : *rel_2_new_call) {
Tuple<RamDomain,4> tuple{{static_cast<RamDomain>(env0[0]),static_cast<RamDomain>(env0[1]),static_cast<RamDomain>(env0[2]),static_cast<RamDomain>(env0[3])}};
rel_3_call->insert(tuple,READ_OP_CONTEXT(rel_3_call_op_ctxt));
}
}
();std::swap(rel_1_delta_call, rel_2_new_call);
if (!isHintsProfilingEnabled()) rel_2_new_call->purge();
iter++;
}
iter = 0;
if (!isHintsProfilingEnabled()) rel_1_delta_call->purge();
if (!isHintsProfilingEnabled()) rel_2_new_call->purge();
if (!isHintsProfilingEnabled()&& performIO) rel_6_direct_call->purge();
SignalHandler::instance()->setMsg(R"_(reentrancy(C2,A1,A2,P,P2) :- 
   call(C2,A1,A2,P),
   call(_,A2,A1,P2),
   A1 != A2.
in file /vol/project/2019/530/g1953010/souffle/MarkT/DetectionLogic.dl [32:1-32:86])_");
if(!(rel_3_call->empty())) {
[&](){
CREATE_OP_CONTEXT(rel_3_call_op_ctxt,rel_3_call->createContext());
CREATE_OP_CONTEXT(rel_8_reentrancy_op_ctxt,rel_8_reentrancy->createContext());
for(const auto& env0 : *rel_3_call) {
if( ((env0[1]) != (env0[2]))) {
const Tuple<RamDomain,4> key{{0,env0[2],env0[1],0}};
auto range = rel_3_call->equalRange_6(key,READ_OP_CONTEXT(rel_3_call_op_ctxt));
for(const auto& env1 : range) {
Tuple<RamDomain,5> tuple{{static_cast<RamDomain>(env0[0]),static_cast<RamDomain>(env0[1]),static_cast<RamDomain>(env0[2]),static_cast<RamDomain>(env0[3]),static_cast<RamDomain>(env1[3])}};
rel_8_reentrancy->insert(tuple,READ_OP_CONTEXT(rel_8_reentrancy_op_ctxt));
}
}
}
}
();}
if (performIO) {
try {std::map<std::string, std::string> directiveMap({{"IO","file"},{"attributeNames","c\ta1\ta2\tp\tp2"},{"filename","./reentrancy.csv"},{"name","reentrancy"}});
if (!outputDirectory.empty() && directiveMap["IO"] == "file" && directiveMap["filename"].front() != '/') {directiveMap["filename"] = outputDirectory + "/" + directiveMap["filename"];}
IODirectives ioDirectives(directiveMap);
IOSystem::getInstance().getWriter(std::vector<RamTypeAttribute>({RamTypeAttribute::Signed,RamTypeAttribute::Symbol,RamTypeAttribute::Symbol,RamTypeAttribute::Signed,RamTypeAttribute::Signed}), symTable, ioDirectives, 0)->writeAll(*rel_8_reentrancy);
} catch (std::exception& e) {std::cerr << e.what();exit(1);}
}
if (!isHintsProfilingEnabled()&& performIO) rel_3_call->purge();
if (performIO) {
try {std::map<std::string, std::string> directiveMap({{"IO","file"},{"filename","./call_entry.facts"},{"name","call_entry"}});
if (!inputDirectory.empty() && directiveMap["IO"] == "file" && directiveMap["filename"].front() != '/') {directiveMap["filename"] = inputDirectory + "/" + directiveMap["filename"];}
IODirectives ioDirectives(directiveMap);
IOSystem::getInstance().getReader(std::vector<RamTypeAttribute>({RamTypeAttribute::Signed,RamTypeAttribute::Symbol}), symTable, ioDirectives, 0)->readAll(*rel_4_call_entry);
} catch (std::exception& e) {std::cerr << "Error loading data: " << e.what() << '\n';}
}
if (performIO) {
try {std::map<std::string, std::string> directiveMap({{"IO","file"},{"filename","./call_exit.facts"},{"name","call_exit"}});
if (!inputDirectory.empty() && directiveMap["IO"] == "file" && directiveMap["filename"].front() != '/') {directiveMap["filename"] = inputDirectory + "/" + directiveMap["filename"];}
IODirectives ioDirectives(directiveMap);
IOSystem::getInstance().getReader(std::vector<RamTypeAttribute>({RamTypeAttribute::Signed}), symTable, ioDirectives, 0)->readAll(*rel_5_call_exit);
} catch (std::exception& e) {std::cerr << "Error loading data: " << e.what() << '\n';}
}
SignalHandler::instance()->setMsg(R"_(locked_ether(A1,G2) :- 
   call_entry(G2,A1),
   call_exit(G2).
in file /vol/project/2019/530/g1953010/souffle/MarkT/DetectionLogic.dl [60:1-60:66])_");
if(!(rel_4_call_entry->empty()) && !(rel_5_call_exit->empty())) {
[&](){
CREATE_OP_CONTEXT(rel_4_call_entry_op_ctxt,rel_4_call_entry->createContext());
CREATE_OP_CONTEXT(rel_5_call_exit_op_ctxt,rel_5_call_exit->createContext());
CREATE_OP_CONTEXT(rel_7_locked_ether_op_ctxt,rel_7_locked_ether->createContext());
for(const auto& env0 : *rel_4_call_entry) {
if( rel_5_call_exit->contains(Tuple<RamDomain,1>{{env0[0]}},READ_OP_CONTEXT(rel_5_call_exit_op_ctxt))) {
Tuple<RamDomain,2> tuple{{static_cast<RamDomain>(env0[1]),static_cast<RamDomain>(env0[0])}};
rel_7_locked_ether->insert(tuple,READ_OP_CONTEXT(rel_7_locked_ether_op_ctxt));
}
}
}
();}
if (performIO) {
try {std::map<std::string, std::string> directiveMap({{"IO","file"},{"attributeNames","a1\tg1"},{"filename","./locked_ether.csv"},{"name","locked_ether"}});
if (!outputDirectory.empty() && directiveMap["IO"] == "file" && directiveMap["filename"].front() != '/') {directiveMap["filename"] = outputDirectory + "/" + directiveMap["filename"];}
IODirectives ioDirectives(directiveMap);
IOSystem::getInstance().getWriter(std::vector<RamTypeAttribute>({RamTypeAttribute::Symbol,RamTypeAttribute::Signed}), symTable, ioDirectives, 0)->writeAll(*rel_7_locked_ether);
} catch (std::exception& e) {std::cerr << e.what();exit(1);}
}
if (!isHintsProfilingEnabled()&& performIO) rel_4_call_entry->purge();
if (!isHintsProfilingEnabled()&& performIO) rel_5_call_exit->purge();

// -- relation hint statistics --
if(isHintsProfilingEnabled()) {
std::cout << " -- Operation Hint Statistics --\n";
std::cout << "Relation rel_1_delta_call:\n";
rel_1_delta_call->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_2_new_call:\n";
rel_2_new_call->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_3_call:\n";
rel_3_call->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_4_call_entry:\n";
rel_4_call_entry->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_5_call_exit:\n";
rel_5_call_exit->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_6_direct_call:\n";
rel_6_direct_call->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_7_locked_ether:\n";
rel_7_locked_ether->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_8_reentrancy:\n";
rel_8_reentrancy->printHintStatistics(std::cout,"  ");
std::cout << "\n";
}
SignalHandler::instance()->reset();
}
public:
void run() override { runFunction(".", ".", false); }
public:
void runAll(std::string inputDirectory = ".", std::string outputDirectory = ".") override { runFunction(inputDirectory, outputDirectory, true);
}
public:
void printAll(std::string outputDirectory = ".") override {
try {std::map<std::string, std::string> directiveMap({{"IO","file"},{"attributeNames","c\ta1\ta2\tp\tp2"},{"filename","./reentrancy.csv"},{"name","reentrancy"}});
if (!outputDirectory.empty() && directiveMap["IO"] == "file" && directiveMap["filename"].front() != '/') {directiveMap["filename"] = outputDirectory + "/" + directiveMap["filename"];}
IODirectives ioDirectives(directiveMap);
IOSystem::getInstance().getWriter(std::vector<RamTypeAttribute>({RamTypeAttribute::Signed,RamTypeAttribute::Symbol,RamTypeAttribute::Symbol,RamTypeAttribute::Signed,RamTypeAttribute::Signed}), symTable, ioDirectives, 0)->writeAll(*rel_8_reentrancy);
} catch (std::exception& e) {std::cerr << e.what();exit(1);}
try {std::map<std::string, std::string> directiveMap({{"IO","file"},{"attributeNames","a1\tg1"},{"filename","./locked_ether.csv"},{"name","locked_ether"}});
if (!outputDirectory.empty() && directiveMap["IO"] == "file" && directiveMap["filename"].front() != '/') {directiveMap["filename"] = outputDirectory + "/" + directiveMap["filename"];}
IODirectives ioDirectives(directiveMap);
IOSystem::getInstance().getWriter(std::vector<RamTypeAttribute>({RamTypeAttribute::Symbol,RamTypeAttribute::Signed}), symTable, ioDirectives, 0)->writeAll(*rel_7_locked_ether);
} catch (std::exception& e) {std::cerr << e.what();exit(1);}
}
public:
void loadAll(std::string inputDirectory = ".") override {
try {std::map<std::string, std::string> directiveMap({{"IO","file"},{"filename","./direct_call.facts"},{"name","direct_call"}});
if (!inputDirectory.empty() && directiveMap["IO"] == "file" && directiveMap["filename"].front() != '/') {directiveMap["filename"] = inputDirectory + "/" + directiveMap["filename"];}
IODirectives ioDirectives(directiveMap);
IOSystem::getInstance().getReader(std::vector<RamTypeAttribute>({RamTypeAttribute::Signed,RamTypeAttribute::Symbol,RamTypeAttribute::Symbol,RamTypeAttribute::Signed}), symTable, ioDirectives, 0)->readAll(*rel_6_direct_call);
} catch (std::exception& e) {std::cerr << "Error loading data: " << e.what() << '\n';}
try {std::map<std::string, std::string> directiveMap({{"IO","file"},{"filename","./call_entry.facts"},{"name","call_entry"}});
if (!inputDirectory.empty() && directiveMap["IO"] == "file" && directiveMap["filename"].front() != '/') {directiveMap["filename"] = inputDirectory + "/" + directiveMap["filename"];}
IODirectives ioDirectives(directiveMap);
IOSystem::getInstance().getReader(std::vector<RamTypeAttribute>({RamTypeAttribute::Signed,RamTypeAttribute::Symbol}), symTable, ioDirectives, 0)->readAll(*rel_4_call_entry);
} catch (std::exception& e) {std::cerr << "Error loading data: " << e.what() << '\n';}
try {std::map<std::string, std::string> directiveMap({{"IO","file"},{"filename","./call_exit.facts"},{"name","call_exit"}});
if (!inputDirectory.empty() && directiveMap["IO"] == "file" && directiveMap["filename"].front() != '/') {directiveMap["filename"] = inputDirectory + "/" + directiveMap["filename"];}
IODirectives ioDirectives(directiveMap);
IOSystem::getInstance().getReader(std::vector<RamTypeAttribute>({RamTypeAttribute::Signed}), symTable, ioDirectives, 0)->readAll(*rel_5_call_exit);
} catch (std::exception& e) {std::cerr << "Error loading data: " << e.what() << '\n';}
}
public:
void dumpInputs(std::ostream& out = std::cout) override {
try {IODirectives ioDirectives;
ioDirectives.setIOType("stdout");
ioDirectives.setRelationName("direct_call");
IOSystem::getInstance().getWriter(std::vector<RamTypeAttribute>({RamTypeAttribute::Signed,RamTypeAttribute::Symbol,RamTypeAttribute::Symbol,RamTypeAttribute::Signed}), symTable, ioDirectives, 0)->writeAll(*rel_6_direct_call);
} catch (std::exception& e) {std::cerr << e.what();exit(1);}
try {IODirectives ioDirectives;
ioDirectives.setIOType("stdout");
ioDirectives.setRelationName("call_entry");
IOSystem::getInstance().getWriter(std::vector<RamTypeAttribute>({RamTypeAttribute::Signed,RamTypeAttribute::Symbol}), symTable, ioDirectives, 0)->writeAll(*rel_4_call_entry);
} catch (std::exception& e) {std::cerr << e.what();exit(1);}
try {IODirectives ioDirectives;
ioDirectives.setIOType("stdout");
ioDirectives.setRelationName("call_exit");
IOSystem::getInstance().getWriter(std::vector<RamTypeAttribute>({RamTypeAttribute::Signed}), symTable, ioDirectives, 0)->writeAll(*rel_5_call_exit);
} catch (std::exception& e) {std::cerr << e.what();exit(1);}
}
public:
void dumpOutputs(std::ostream& out = std::cout) override {
try {IODirectives ioDirectives;
ioDirectives.setIOType("stdout");
ioDirectives.setRelationName("reentrancy");
IOSystem::getInstance().getWriter(std::vector<RamTypeAttribute>({RamTypeAttribute::Signed,RamTypeAttribute::Symbol,RamTypeAttribute::Symbol,RamTypeAttribute::Signed,RamTypeAttribute::Signed}), symTable, ioDirectives, 0)->writeAll(*rel_8_reentrancy);
} catch (std::exception& e) {std::cerr << e.what();exit(1);}
try {IODirectives ioDirectives;
ioDirectives.setIOType("stdout");
ioDirectives.setRelationName("locked_ether");
IOSystem::getInstance().getWriter(std::vector<RamTypeAttribute>({RamTypeAttribute::Symbol,RamTypeAttribute::Signed}), symTable, ioDirectives, 0)->writeAll(*rel_7_locked_ether);
} catch (std::exception& e) {std::cerr << e.what();exit(1);}
}
public:
SymbolTable& getSymbolTable() override {
return symTable;
}
};
SouffleProgram *newInstance_DetectionLogic(){return new Sf_DetectionLogic;}
SymbolTable *getST_DetectionLogic(SouffleProgram *p){return &reinterpret_cast<Sf_DetectionLogic*>(p)->symTable;}

#ifdef __EMBEDDED_SOUFFLE__
class factory_Sf_DetectionLogic: public souffle::ProgramFactory {
SouffleProgram *newInstance() {
return new Sf_DetectionLogic();
};
public:
factory_Sf_DetectionLogic() : ProgramFactory("DetectionLogic"){}
};
static factory_Sf_DetectionLogic __factory_Sf_DetectionLogic_instance;
}
#else
}
int main(int argc, char** argv)
{
try{
souffle::CmdOptions opt(R"(MarkT/DetectionLogic.dl)",
R"(.)",
R"(.)",
false,
R"()",
1,
-1);
if (!opt.parse(argc,argv)) return 1;
souffle::Sf_DetectionLogic obj;
#if defined(_OPENMP) 
obj.setNumThreads(opt.getNumJobs());

#endif
obj.runAll(opt.getInputFileDir(), opt.getOutputFileDir());
return 0;
} catch(std::exception &e) { souffle::SignalHandler::instance()->error(e.what());}
}

#endif
