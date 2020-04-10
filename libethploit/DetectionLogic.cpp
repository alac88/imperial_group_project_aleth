
#include "souffle/CompiledSouffle.h"

extern "C" {
}

namespace souffle {
static const RamDomain RAM_BIT_SHIFT_MASK = RAM_DOMAIN_SIZE - 1;
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
low[0] = MIN_RAM_SIGNED;
high[0] = MAX_RAM_SIGNED;
low[2] = MIN_RAM_SIGNED;
high[2] = MAX_RAM_SIGNED;
low[3] = MIN_RAM_SIGNED;
high[3] = MAX_RAM_SIGNED;
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
void printStatistics(std::ostream& o) const {
o << " arity 4 direct b-tree index 0 lex-order [1,0,2,3]\n";
ind_0.printStats(o);
}
};
struct t_btree_2__0_1__1__3 {
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
range<t_ind_0::iterator> equalRange_1(const t_tuple& t, context& h) const {
t_tuple low(t); t_tuple high(t);
low[1] = MIN_RAM_SIGNED;
high[1] = MAX_RAM_SIGNED;
return make_range(ind_0.lower_bound(low, h.hints_0), ind_0.upper_bound(high, h.hints_0));
}
range<t_ind_0::iterator> equalRange_1(const t_tuple& t) const {
context h;
return equalRange_1(t, h);
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
void printStatistics(std::ostream& o) const {
o << " arity 2 direct b-tree index 0 lex-order [0,1]\n";
ind_0.printStats(o);
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
low[0] = MIN_RAM_SIGNED;
high[0] = MAX_RAM_SIGNED;
low[3] = MIN_RAM_SIGNED;
high[3] = MAX_RAM_SIGNED;
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
void printStatistics(std::ostream& o) const {
o << " arity 4 direct b-tree index 0 lex-order [1,2,0,3]\n";
ind_0.printStats(o);
}
};
struct t_btree_3__0_1_2__7 {
using t_tuple = Tuple<RamDomain, 3>;
using t_ind_0 = btree_set<t_tuple, index_utils::comparator<0,1,2>>;
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
RamDomain data[3];
std::copy(ramDomain, ramDomain + 3, data);
const t_tuple& tuple = reinterpret_cast<const t_tuple&>(data);
context h;
return insert(tuple, h);
}
bool insert(RamDomain a0,RamDomain a1,RamDomain a2) {
RamDomain data[3] = {a0,a1,a2};
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
range<t_ind_0::iterator> equalRange_7(const t_tuple& t, context& h) const {
auto pos = ind_0.find(t, h.hints_0);
auto fin = ind_0.end();
if (pos != fin) {fin = pos; ++fin;}
return make_range(pos, fin);
}
range<t_ind_0::iterator> equalRange_7(const t_tuple& t) const {
context h;
return equalRange_7(t, h);
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
void printStatistics(std::ostream& o) const {
o << " arity 3 direct b-tree index 0 lex-order [0,1,2]\n";
ind_0.printStats(o);
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
void printStatistics(std::ostream& o) const {
o << " arity 2 direct b-tree index 0 lex-order [0,1]\n";
ind_0.printStats(o);
}
};
struct t_btree_2__1_0__2__3 {
using t_tuple = Tuple<RamDomain, 2>;
using t_ind_0 = btree_set<t_tuple, index_utils::comparator<1,0>>;
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
range<t_ind_0::iterator> equalRange_2(const t_tuple& t, context& h) const {
t_tuple low(t); t_tuple high(t);
low[0] = MIN_RAM_SIGNED;
high[0] = MAX_RAM_SIGNED;
return make_range(ind_0.lower_bound(low, h.hints_0), ind_0.upper_bound(high, h.hints_0));
}
range<t_ind_0::iterator> equalRange_2(const t_tuple& t) const {
context h;
return equalRange_2(t, h);
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
void printStatistics(std::ostream& o) const {
o << " arity 2 direct b-tree index 0 lex-order [1,0]\n";
ind_0.printStats(o);
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
void printStatistics(std::ostream& o) const {
o << " arity 4 direct b-tree index 0 lex-order [0,1,2,3]\n";
ind_0.printStats(o);
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
void printStatistics(std::ostream& o) const {
o << " arity 1 direct b-tree index 0 lex-order [0]\n";
ind_0.printStats(o);
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
void printStatistics(std::ostream& o) const {
o << " arity 5 direct b-tree index 0 lex-order [0,1,2,3,4]\n";
ind_0.printStats(o);
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
   try { result = RamSignedFromString(str); } catch(...) { 
     std::cerr << "error: wrong string provided by to_number(\"";
     std::cerr << str << "\") functor.\n";
     raise(SIGFPE);
   } return result;
}
public:
// -- initialize symbol table --
SymbolTable symTable;// -- initialize record table --
RecordTable recordTable;
// -- Table: @delta_call
std::unique_ptr<t_btree_4__1_0_2_3__2__15> rel_1_delta_call = std::make_unique<t_btree_4__1_0_2_3__2__15>();
// -- Table: @delta_depends
std::unique_ptr<t_btree_2__0_1__1__3> rel_2_delta_depends = std::make_unique<t_btree_2__0_1__1__3>();
// -- Table: @new_call
std::unique_ptr<t_btree_4__1_0_2_3__2__15> rel_3_new_call = std::make_unique<t_btree_4__1_0_2_3__2__15>();
// -- Table: @new_depends
std::unique_ptr<t_btree_2__0_1__1__3> rel_4_new_depends = std::make_unique<t_btree_2__0_1__1__3>();
// -- Table: call
std::unique_ptr<t_btree_4__1_2_0_3__6__15> rel_5_call = std::make_unique<t_btree_4__1_2_0_3__6__15>();
souffle::RelationWrapper<0,t_btree_4__1_2_0_3__6__15,Tuple<RamDomain,4>,4,0> wrapper_rel_5_call;
// -- Table: call_entry
std::unique_ptr<t_btree_3__0_1_2__7> rel_6_call_entry = std::make_unique<t_btree_3__0_1_2__7>();
souffle::RelationWrapper<1,t_btree_3__0_1_2__7,Tuple<RamDomain,3>,3,0> wrapper_rel_6_call_entry;
// -- Table: call_exit
std::unique_ptr<t_btree_2__0_1__3> rel_7_call_exit = std::make_unique<t_btree_2__0_1__3>();
souffle::RelationWrapper<2,t_btree_2__0_1__3,Tuple<RamDomain,2>,2,0> wrapper_rel_7_call_exit;
// -- Table: call_result
std::unique_ptr<t_btree_2__1_0__2__3> rel_8_call_result = std::make_unique<t_btree_2__1_0__2__3>();
souffle::RelationWrapper<3,t_btree_2__1_0__2__3,Tuple<RamDomain,2>,2,0> wrapper_rel_8_call_result;
// -- Table: depends
std::unique_ptr<t_btree_2__0_1__3> rel_9_depends = std::make_unique<t_btree_2__0_1__3>();
souffle::RelationWrapper<4,t_btree_2__0_1__3,Tuple<RamDomain,2>,2,0> wrapper_rel_9_depends;
// -- Table: direct_call
std::unique_ptr<t_btree_4__0_1_2_3__15> rel_10_direct_call = std::make_unique<t_btree_4__0_1_2_3__15>();
souffle::RelationWrapper<5,t_btree_4__0_1_2_3__15,Tuple<RamDomain,4>,4,0> wrapper_rel_10_direct_call;
// -- Table: in_condition
std::unique_ptr<t_btree_1__0__1> rel_11_in_condition = std::make_unique<t_btree_1__0__1>();
souffle::RelationWrapper<6,t_btree_1__0__1,Tuple<RamDomain,1>,1,0> wrapper_rel_11_in_condition;
// -- Table: influences_condition
std::unique_ptr<t_btree_1__0__1> rel_12_influences_condition = std::make_unique<t_btree_1__0__1>();
souffle::RelationWrapper<7,t_btree_1__0__1,Tuple<RamDomain,1>,1,0> wrapper_rel_12_influences_condition;
// -- Table: is_output
std::unique_ptr<t_btree_2__0_1__3> rel_13_is_output = std::make_unique<t_btree_2__0_1__3>();
souffle::RelationWrapper<8,t_btree_2__0_1__3,Tuple<RamDomain,2>,2,0> wrapper_rel_13_is_output;
// -- Table: locked_ether
std::unique_ptr<t_btree_3__0_1_2__7> rel_14_locked_ether = std::make_unique<t_btree_3__0_1_2__7>();
souffle::RelationWrapper<9,t_btree_3__0_1_2__7,Tuple<RamDomain,3>,3,0> wrapper_rel_14_locked_ether;
// -- Table: reentrancy
std::unique_ptr<t_btree_5__0_1_2_3_4__31> rel_15_reentrancy = std::make_unique<t_btree_5__0_1_2_3_4__31>();
souffle::RelationWrapper<10,t_btree_5__0_1_2_3_4__31,Tuple<RamDomain,5>,5,0> wrapper_rel_15_reentrancy;
// -- Table: unhandled_exception
std::unique_ptr<t_btree_1__0__1> rel_16_unhandled_exception = std::make_unique<t_btree_1__0__1>();
souffle::RelationWrapper<11,t_btree_1__0__1,Tuple<RamDomain,1>,1,0> wrapper_rel_16_unhandled_exception;
public:
Sf_DetectionLogic() : 
wrapper_rel_5_call(*rel_5_call,symTable,"call",std::array<const char *,4>{{"i:CallNum","s:EthAddress","s:EthAddress","i:IntSet[i:number]"}},std::array<const char *,4>{{"c","a1","a2","p"}}),

wrapper_rel_6_call_entry(*rel_6_call_entry,symTable,"call_entry",std::array<const char *,3>{{"i:identifier","i:gas","s:EthAddress"}},std::array<const char *,3>{{"id","g1","a"}}),

wrapper_rel_7_call_exit(*rel_7_call_exit,symTable,"call_exit",std::array<const char *,2>{{"i:identifier","i:gas"}},std::array<const char *,2>{{"id","g2"}}),

wrapper_rel_8_call_result(*rel_8_call_result,symTable,"call_result",std::array<const char *,2>{{"i:result[i:number]","i:NatNum[i:number]"}},std::array<const char *,2>{{"a","v"}}),

wrapper_rel_9_depends(*rel_9_depends,symTable,"depends",std::array<const char *,2>{{"i:result[i:number]","i:opcodeArg[i:number]"}},std::array<const char *,2>{{"a","b"}}),

wrapper_rel_10_direct_call(*rel_10_direct_call,symTable,"direct_call",std::array<const char *,4>{{"i:CallNum","s:EthAddress","s:EthAddress","i:NatNum[i:number]"}},std::array<const char *,4>{{"c","a1","a2","p"}}),

wrapper_rel_11_in_condition(*rel_11_in_condition,symTable,"in_condition",std::array<const char *,1>{{"i:result[i:number]"}},std::array<const char *,1>{{"a"}}),

wrapper_rel_12_influences_condition(*rel_12_influences_condition,symTable,"influences_condition",std::array<const char *,1>{{"i:result[i:number]"}},std::array<const char *,1>{{"a"}}),

wrapper_rel_13_is_output(*rel_13_is_output,symTable,"is_output",std::array<const char *,2>{{"i:result[i:number]","i:opcodeArg[i:number]"}},std::array<const char *,2>{{"a","b"}}),

wrapper_rel_14_locked_ether(*rel_14_locked_ether,symTable,"locked_ether",std::array<const char *,3>{{"i:identifier","i:gas","s:EthAddress"}},std::array<const char *,3>{{"id","g1","a"}}),

wrapper_rel_15_reentrancy(*rel_15_reentrancy,symTable,"reentrancy",std::array<const char *,5>{{"i:CallNum","s:EthAddress","s:EthAddress","i:IntSet[i:number]","i:IntSet[i:number]"}},std::array<const char *,5>{{"c","a1","a2","p","p2"}}),

wrapper_rel_16_unhandled_exception(*rel_16_unhandled_exception,symTable,"unhandled_exception",std::array<const char *,1>{{"i:opcodeArg[i:number]"}},std::array<const char *,1>{{"a"}}){
addRelation("call",&wrapper_rel_5_call,false,false);
addRelation("call_entry",&wrapper_rel_6_call_entry,true,false);
addRelation("call_exit",&wrapper_rel_7_call_exit,true,false);
addRelation("call_result",&wrapper_rel_8_call_result,true,false);
addRelation("depends",&wrapper_rel_9_depends,false,false);
addRelation("direct_call",&wrapper_rel_10_direct_call,true,false);
addRelation("in_condition",&wrapper_rel_11_in_condition,true,false);
addRelation("influences_condition",&wrapper_rel_12_influences_condition,false,false);
addRelation("is_output",&wrapper_rel_13_is_output,true,false);
addRelation("locked_ether",&wrapper_rel_14_locked_ether,false,true);
addRelation("reentrancy",&wrapper_rel_15_reentrancy,false,true);
addRelation("unhandled_exception",&wrapper_rel_16_unhandled_exception,false,true);
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
try {std::map<std::string, std::string> directiveMap({{"IO","file"},{"filename","./direct_call.facts"},{"name","direct_call"},{"operation","input"},{"types","{\"direct_call\": {\"arity\": 4, \"auxArity\": 0, \"types\": [\"i:CallNum\", \"s:EthAddress\", \"s:EthAddress\", \"i:NatNum[i:number]\"]}, \"records\": {}}"}});
if (!inputDirectory.empty() && directiveMap["filename"].front() != '/') {directiveMap["filename"] = inputDirectory + "/" + directiveMap["filename"];}
RWOperation rwOperation(directiveMap);
IOSystem::getInstance().getReader(rwOperation, symTable, recordTable)->readAll(*rel_10_direct_call);
} catch (std::exception& e) {std::cerr << "Error loading data: " << e.what() << '\n';}
}
SignalHandler::instance()->setMsg(R"_(call(C,A1,A2,P) :- 
   direct_call(C,A1,A2,P).
in file /vol/project/2019/530/g1953010/newSouffle/souffle/MarkT/DetectionLogic.dl [30:1-30:49])_");
if(!(rel_10_direct_call->empty())) {
[&](){
CREATE_OP_CONTEXT(rel_5_call_op_ctxt,rel_5_call->createContext());
CREATE_OP_CONTEXT(rel_10_direct_call_op_ctxt,rel_10_direct_call->createContext());
for(const auto& env0 : *rel_10_direct_call) {
Tuple<RamDomain,4> tuple{{ramBitCast(env0[0]),ramBitCast(env0[1]),ramBitCast(env0[2]),ramBitCast(env0[3])}};
rel_5_call->insert(tuple,READ_OP_CONTEXT(rel_5_call_op_ctxt));
}
}
();}
[&](){
CREATE_OP_CONTEXT(rel_1_delta_call_op_ctxt,rel_1_delta_call->createContext());
CREATE_OP_CONTEXT(rel_5_call_op_ctxt,rel_5_call->createContext());
for(const auto& env0 : *rel_5_call) {
Tuple<RamDomain,4> tuple{{ramBitCast(env0[0]),ramBitCast(env0[1]),ramBitCast(env0[2]),ramBitCast(env0[3])}};
rel_1_delta_call->insert(tuple,READ_OP_CONTEXT(rel_1_delta_call_op_ctxt));
}
}
();iter = 0;
for(;;) {
SignalHandler::instance()->setMsg(R"_(call(C,A1,A2,P) :- 
   direct_call(C,A1,A3,P),
   call(_,A3,A2,_).
in file /vol/project/2019/530/g1953010/newSouffle/souffle/MarkT/DetectionLogic.dl [31:1-31:71])_");
if(!(rel_10_direct_call->empty()) && !(rel_1_delta_call->empty())) {
[&](){
CREATE_OP_CONTEXT(rel_1_delta_call_op_ctxt,rel_1_delta_call->createContext());
CREATE_OP_CONTEXT(rel_5_call_op_ctxt,rel_5_call->createContext());
CREATE_OP_CONTEXT(rel_3_new_call_op_ctxt,rel_3_new_call->createContext());
CREATE_OP_CONTEXT(rel_10_direct_call_op_ctxt,rel_10_direct_call->createContext());
for(const auto& env0 : *rel_10_direct_call) {
const Tuple<RamDomain,4> key{{0,ramBitCast(env0[2]),0,0}};
auto range = rel_1_delta_call->equalRange_2(key,READ_OP_CONTEXT(rel_1_delta_call_op_ctxt));
for(const auto& env1 : range) {
if( !(rel_5_call->contains(Tuple<RamDomain,4>{{ramBitCast(env0[0]),ramBitCast(env0[1]),ramBitCast(env1[2]),ramBitCast(env0[3])}},READ_OP_CONTEXT(rel_5_call_op_ctxt)))) {
Tuple<RamDomain,4> tuple{{ramBitCast(env0[0]),ramBitCast(env0[1]),ramBitCast(env1[2]),ramBitCast(env0[3])}};
rel_3_new_call->insert(tuple,READ_OP_CONTEXT(rel_3_new_call_op_ctxt));
}
}
}
}
();}
if(rel_3_new_call->empty()) break;
[&](){
CREATE_OP_CONTEXT(rel_5_call_op_ctxt,rel_5_call->createContext());
CREATE_OP_CONTEXT(rel_3_new_call_op_ctxt,rel_3_new_call->createContext());
for(const auto& env0 : *rel_3_new_call) {
Tuple<RamDomain,4> tuple{{ramBitCast(env0[0]),ramBitCast(env0[1]),ramBitCast(env0[2]),ramBitCast(env0[3])}};
rel_5_call->insert(tuple,READ_OP_CONTEXT(rel_5_call_op_ctxt));
}
}
();std::swap(rel_1_delta_call, rel_3_new_call);
rel_3_new_call->purge();
iter++;
}
iter = 0;
rel_1_delta_call->purge();
rel_3_new_call->purge();
if (performIO) rel_10_direct_call->purge();
SignalHandler::instance()->setMsg(R"_(reentrancy(C2,A1,A2,P,P2) :- 
   call(C2,A1,A2,P),
   call(_,A2,A1,P2),
   A1 != A2.
in file /vol/project/2019/530/g1953010/newSouffle/souffle/MarkT/DetectionLogic.dl [33:1-33:86])_");
if(!(rel_5_call->empty())) {
[&](){
CREATE_OP_CONTEXT(rel_5_call_op_ctxt,rel_5_call->createContext());
CREATE_OP_CONTEXT(rel_15_reentrancy_op_ctxt,rel_15_reentrancy->createContext());
for(const auto& env0 : *rel_5_call) {
if( (ramBitCast<RamDomain>(env0[1]) != ramBitCast<RamDomain>(env0[2]))) {
const Tuple<RamDomain,4> key{{0,ramBitCast(env0[2]),ramBitCast(env0[1]),0}};
auto range = rel_5_call->equalRange_6(key,READ_OP_CONTEXT(rel_5_call_op_ctxt));
for(const auto& env1 : range) {
Tuple<RamDomain,5> tuple{{ramBitCast(env0[0]),ramBitCast(env0[1]),ramBitCast(env0[2]),ramBitCast(env0[3]),ramBitCast(env1[3])}};
rel_15_reentrancy->insert(tuple,READ_OP_CONTEXT(rel_15_reentrancy_op_ctxt));
}
}
}
}
();}
if (performIO) {
try {std::map<std::string, std::string> directiveMap({{"IO","file"},{"attributeNames","c\ta1\ta2\tp\tp2"},{"filename","./reentrancy.csv"},{"name","reentrancy"},{"operation","output"},{"types","{\"records\": {}, \"reentrancy\": {\"arity\": 5, \"auxArity\": 0, \"types\": [\"i:CallNum\", \"s:EthAddress\", \"s:EthAddress\", \"i:IntSet[i:number]\", \"i:IntSet[i:number]\"]}}"}});
if (!outputDirectory.empty() && directiveMap["filename"].front() != '/') {directiveMap["filename"] = outputDirectory + "/" + directiveMap["filename"];}
RWOperation rwOperation(directiveMap);
IOSystem::getInstance().getWriter(rwOperation, symTable, recordTable)->writeAll(*rel_15_reentrancy);
} catch (std::exception& e) {std::cerr << e.what();exit(1);}
}
if (performIO) rel_5_call->purge();
if (performIO) {
try {std::map<std::string, std::string> directiveMap({{"IO","file"},{"filename","./call_entry.facts"},{"name","call_entry"},{"operation","input"},{"types","{\"call_entry\": {\"arity\": 3, \"auxArity\": 0, \"types\": [\"i:identifier\", \"i:gas\", \"s:EthAddress\"]}, \"records\": {}}"}});
if (!inputDirectory.empty() && directiveMap["filename"].front() != '/') {directiveMap["filename"] = inputDirectory + "/" + directiveMap["filename"];}
RWOperation rwOperation(directiveMap);
IOSystem::getInstance().getReader(rwOperation, symTable, recordTable)->readAll(*rel_6_call_entry);
} catch (std::exception& e) {std::cerr << "Error loading data: " << e.what() << '\n';}
}
if (performIO) {
try {std::map<std::string, std::string> directiveMap({{"IO","file"},{"filename","./call_exit.facts"},{"name","call_exit"},{"operation","input"},{"types","{\"call_exit\": {\"arity\": 2, \"auxArity\": 0, \"types\": [\"i:identifier\", \"i:gas\"]}, \"records\": {}}"}});
if (!inputDirectory.empty() && directiveMap["filename"].front() != '/') {directiveMap["filename"] = inputDirectory + "/" + directiveMap["filename"];}
RWOperation rwOperation(directiveMap);
IOSystem::getInstance().getReader(rwOperation, symTable, recordTable)->readAll(*rel_7_call_exit);
} catch (std::exception& e) {std::cerr << "Error loading data: " << e.what() << '\n';}
}
SignalHandler::instance()->setMsg(R"_(locked_ether(ID,G2,A) :- 
   call_entry(ID,G2,A),
   call_exit(ID,G2).
in file /vol/project/2019/530/g1953010/newSouffle/souffle/MarkT/DetectionLogic.dl [62:1-62:76])_");
if(!(rel_6_call_entry->empty()) && !(rel_7_call_exit->empty())) {
[&](){
CREATE_OP_CONTEXT(rel_6_call_entry_op_ctxt,rel_6_call_entry->createContext());
CREATE_OP_CONTEXT(rel_14_locked_ether_op_ctxt,rel_14_locked_ether->createContext());
CREATE_OP_CONTEXT(rel_7_call_exit_op_ctxt,rel_7_call_exit->createContext());
for(const auto& env0 : *rel_6_call_entry) {
if( rel_7_call_exit->contains(Tuple<RamDomain,2>{{ramBitCast(env0[0]),ramBitCast(env0[1])}},READ_OP_CONTEXT(rel_7_call_exit_op_ctxt))) {
Tuple<RamDomain,3> tuple{{ramBitCast(env0[0]),ramBitCast(env0[1]),ramBitCast(env0[2])}};
rel_14_locked_ether->insert(tuple,READ_OP_CONTEXT(rel_14_locked_ether_op_ctxt));
}
}
}
();}
if (performIO) {
try {std::map<std::string, std::string> directiveMap({{"IO","file"},{"attributeNames","id\tg1\ta"},{"filename","./locked_ether.csv"},{"name","locked_ether"},{"operation","output"},{"types","{\"locked_ether\": {\"arity\": 3, \"auxArity\": 0, \"types\": [\"i:identifier\", \"i:gas\", \"s:EthAddress\"]}, \"records\": {}}"}});
if (!outputDirectory.empty() && directiveMap["filename"].front() != '/') {directiveMap["filename"] = outputDirectory + "/" + directiveMap["filename"];}
RWOperation rwOperation(directiveMap);
IOSystem::getInstance().getWriter(rwOperation, symTable, recordTable)->writeAll(*rel_14_locked_ether);
} catch (std::exception& e) {std::cerr << e.what();exit(1);}
}
if (performIO) rel_6_call_entry->purge();
if (performIO) rel_7_call_exit->purge();
if (performIO) {
try {std::map<std::string, std::string> directiveMap({{"IO","file"},{"filename","./is_output.facts"},{"name","is_output"},{"operation","input"},{"types","{\"is_output\": {\"arity\": 2, \"auxArity\": 0, \"types\": [\"i:result[i:number]\", \"i:opcodeArg[i:number]\"]}, \"records\": {}}"}});
if (!inputDirectory.empty() && directiveMap["filename"].front() != '/') {directiveMap["filename"] = inputDirectory + "/" + directiveMap["filename"];}
RWOperation rwOperation(directiveMap);
IOSystem::getInstance().getReader(rwOperation, symTable, recordTable)->readAll(*rel_13_is_output);
} catch (std::exception& e) {std::cerr << "Error loading data: " << e.what() << '\n';}
}
SignalHandler::instance()->setMsg(R"_(depends(A,B) :- 
   is_output(A,B).
in file /vol/project/2019/530/g1953010/newSouffle/souffle/MarkT/DetectionLogic.dl [110:1-110:34])_");
if(!(rel_13_is_output->empty())) {
[&](){
CREATE_OP_CONTEXT(rel_9_depends_op_ctxt,rel_9_depends->createContext());
CREATE_OP_CONTEXT(rel_13_is_output_op_ctxt,rel_13_is_output->createContext());
for(const auto& env0 : *rel_13_is_output) {
Tuple<RamDomain,2> tuple{{ramBitCast(env0[0]),ramBitCast(env0[1])}};
rel_9_depends->insert(tuple,READ_OP_CONTEXT(rel_9_depends_op_ctxt));
}
}
();}
[&](){
CREATE_OP_CONTEXT(rel_2_delta_depends_op_ctxt,rel_2_delta_depends->createContext());
CREATE_OP_CONTEXT(rel_9_depends_op_ctxt,rel_9_depends->createContext());
for(const auto& env0 : *rel_9_depends) {
Tuple<RamDomain,2> tuple{{ramBitCast(env0[0]),ramBitCast(env0[1])}};
rel_2_delta_depends->insert(tuple,READ_OP_CONTEXT(rel_2_delta_depends_op_ctxt));
}
}
();iter = 0;
for(;;) {
SignalHandler::instance()->setMsg(R"_(depends(A,B) :- 
   is_output(A,C),
   depends(C,B).
in file /vol/project/2019/530/g1953010/newSouffle/souffle/MarkT/DetectionLogic.dl [111:1-111:49])_");
if(!(rel_13_is_output->empty()) && !(rel_2_delta_depends->empty())) {
[&](){
CREATE_OP_CONTEXT(rel_2_delta_depends_op_ctxt,rel_2_delta_depends->createContext());
CREATE_OP_CONTEXT(rel_9_depends_op_ctxt,rel_9_depends->createContext());
CREATE_OP_CONTEXT(rel_4_new_depends_op_ctxt,rel_4_new_depends->createContext());
CREATE_OP_CONTEXT(rel_13_is_output_op_ctxt,rel_13_is_output->createContext());
for(const auto& env0 : *rel_13_is_output) {
const Tuple<RamDomain,2> key{{ramBitCast(env0[1]),0}};
auto range = rel_2_delta_depends->equalRange_1(key,READ_OP_CONTEXT(rel_2_delta_depends_op_ctxt));
for(const auto& env1 : range) {
if( !(rel_9_depends->contains(Tuple<RamDomain,2>{{ramBitCast(env0[0]),ramBitCast(env1[1])}},READ_OP_CONTEXT(rel_9_depends_op_ctxt)))) {
Tuple<RamDomain,2> tuple{{ramBitCast(env0[0]),ramBitCast(env1[1])}};
rel_4_new_depends->insert(tuple,READ_OP_CONTEXT(rel_4_new_depends_op_ctxt));
}
}
}
}
();}
if(rel_4_new_depends->empty()) break;
[&](){
CREATE_OP_CONTEXT(rel_9_depends_op_ctxt,rel_9_depends->createContext());
CREATE_OP_CONTEXT(rel_4_new_depends_op_ctxt,rel_4_new_depends->createContext());
for(const auto& env0 : *rel_4_new_depends) {
Tuple<RamDomain,2> tuple{{ramBitCast(env0[0]),ramBitCast(env0[1])}};
rel_9_depends->insert(tuple,READ_OP_CONTEXT(rel_9_depends_op_ctxt));
}
}
();std::swap(rel_2_delta_depends, rel_4_new_depends);
rel_4_new_depends->purge();
iter++;
}
iter = 0;
rel_2_delta_depends->purge();
rel_4_new_depends->purge();
if (performIO) rel_13_is_output->purge();
if (performIO) {
try {std::map<std::string, std::string> directiveMap({{"IO","file"},{"filename","./in_condition.facts"},{"name","in_condition"},{"operation","input"},{"types","{\"in_condition\": {\"arity\": 1, \"auxArity\": 0, \"types\": [\"i:result[i:number]\"]}, \"records\": {}}"}});
if (!inputDirectory.empty() && directiveMap["filename"].front() != '/') {directiveMap["filename"] = inputDirectory + "/" + directiveMap["filename"];}
RWOperation rwOperation(directiveMap);
IOSystem::getInstance().getReader(rwOperation, symTable, recordTable)->readAll(*rel_11_in_condition);
} catch (std::exception& e) {std::cerr << "Error loading data: " << e.what() << '\n';}
}
SignalHandler::instance()->setMsg(R"_(influences_condition(A) :- 
   in_condition(A).
in file /vol/project/2019/530/g1953010/newSouffle/souffle/MarkT/DetectionLogic.dl [115:1-115:44])_");
if(!(rel_11_in_condition->empty())) {
[&](){
CREATE_OP_CONTEXT(rel_11_in_condition_op_ctxt,rel_11_in_condition->createContext());
CREATE_OP_CONTEXT(rel_12_influences_condition_op_ctxt,rel_12_influences_condition->createContext());
for(const auto& env0 : *rel_11_in_condition) {
Tuple<RamDomain,1> tuple{{ramBitCast(env0[0])}};
rel_12_influences_condition->insert(tuple,READ_OP_CONTEXT(rel_12_influences_condition_op_ctxt));
}
}
();}
SignalHandler::instance()->setMsg(R"_(influences_condition(A) :- 
   depends(B,A),
   in_condition(B).
in file /vol/project/2019/530/g1953010/newSouffle/souffle/MarkT/DetectionLogic.dl [116:1-116:59])_");
if(!(rel_9_depends->empty()) && !(rel_11_in_condition->empty())) {
[&](){
CREATE_OP_CONTEXT(rel_11_in_condition_op_ctxt,rel_11_in_condition->createContext());
CREATE_OP_CONTEXT(rel_12_influences_condition_op_ctxt,rel_12_influences_condition->createContext());
CREATE_OP_CONTEXT(rel_9_depends_op_ctxt,rel_9_depends->createContext());
for(const auto& env0 : *rel_9_depends) {
if( rel_11_in_condition->contains(Tuple<RamDomain,1>{{ramBitCast(env0[0])}},READ_OP_CONTEXT(rel_11_in_condition_op_ctxt))) {
Tuple<RamDomain,1> tuple{{ramBitCast(env0[1])}};
rel_12_influences_condition->insert(tuple,READ_OP_CONTEXT(rel_12_influences_condition_op_ctxt));
}
}
}
();}
if (performIO) rel_11_in_condition->purge();
if (performIO) rel_9_depends->purge();
if (performIO) {
try {std::map<std::string, std::string> directiveMap({{"IO","file"},{"filename","./call_result.facts"},{"name","call_result"},{"operation","input"},{"types","{\"call_result\": {\"arity\": 2, \"auxArity\": 0, \"types\": [\"i:result[i:number]\", \"i:NatNum[i:number]\"]}, \"records\": {}}"}});
if (!inputDirectory.empty() && directiveMap["filename"].front() != '/') {directiveMap["filename"] = inputDirectory + "/" + directiveMap["filename"];}
RWOperation rwOperation(directiveMap);
IOSystem::getInstance().getReader(rwOperation, symTable, recordTable)->readAll(*rel_8_call_result);
} catch (std::exception& e) {std::cerr << "Error loading data: " << e.what() << '\n';}
}
SignalHandler::instance()->setMsg(R"_(unhandled_exception(A) :- 
   call_result(A,0),
   !influences_condition(A).
in file /vol/project/2019/530/g1953010/newSouffle/souffle/MarkT/DetectionLogic.dl [120:1-120:71])_");
if(!(rel_8_call_result->empty())) {
[&](){
CREATE_OP_CONTEXT(rel_16_unhandled_exception_op_ctxt,rel_16_unhandled_exception->createContext());
CREATE_OP_CONTEXT(rel_12_influences_condition_op_ctxt,rel_12_influences_condition->createContext());
CREATE_OP_CONTEXT(rel_8_call_result_op_ctxt,rel_8_call_result->createContext());
const Tuple<RamDomain,2> key{{0,ramBitCast(RamSigned(0))}};
auto range = rel_8_call_result->equalRange_2(key,READ_OP_CONTEXT(rel_8_call_result_op_ctxt));
for(const auto& env0 : range) {
if( !(rel_12_influences_condition->contains(Tuple<RamDomain,1>{{ramBitCast(env0[0])}},READ_OP_CONTEXT(rel_12_influences_condition_op_ctxt)))) {
Tuple<RamDomain,1> tuple{{ramBitCast(env0[0])}};
rel_16_unhandled_exception->insert(tuple,READ_OP_CONTEXT(rel_16_unhandled_exception_op_ctxt));
}
}
}
();}
if (performIO) {
try {std::map<std::string, std::string> directiveMap({{"IO","file"},{"attributeNames","a"},{"filename","./unhandled_exception.csv"},{"name","unhandled_exception"},{"operation","output"},{"types","{\"records\": {}, \"unhandled_exception\": {\"arity\": 1, \"auxArity\": 0, \"types\": [\"i:opcodeArg[i:number]\"]}}"}});
if (!outputDirectory.empty() && directiveMap["filename"].front() != '/') {directiveMap["filename"] = outputDirectory + "/" + directiveMap["filename"];}
RWOperation rwOperation(directiveMap);
IOSystem::getInstance().getWriter(rwOperation, symTable, recordTable)->writeAll(*rel_16_unhandled_exception);
} catch (std::exception& e) {std::cerr << e.what();exit(1);}
}
if (performIO) rel_8_call_result->purge();
if (performIO) rel_12_influences_condition->purge();

// -- relation hint statistics --
SignalHandler::instance()->reset();
}
public:
void run() override { runFunction(".", ".", false); }
public:
void runAll(std::string inputDirectory = ".", std::string outputDirectory = ".") override { runFunction(inputDirectory, outputDirectory, true);
}
public:
void printAll(std::string outputDirectory = ".") override {
try {std::map<std::string, std::string> directiveMap({{"IO","file"},{"attributeNames","id\tg1\ta"},{"filename","./locked_ether.csv"},{"name","locked_ether"},{"operation","output"},{"types","{\"locked_ether\": {\"arity\": 3, \"auxArity\": 0, \"types\": [\"i:identifier\", \"i:gas\", \"s:EthAddress\"]}, \"records\": {}}"}});
if (!outputDirectory.empty() && directiveMap["IO"] == "file" && directiveMap["filename"].front() != '/') {directiveMap["filename"] = outputDirectory + "/" + directiveMap["filename"];}
RWOperation rwOperation(directiveMap);
IOSystem::getInstance().getWriter(rwOperation, symTable, recordTable)->writeAll(*rel_14_locked_ether);
} catch (std::exception& e) {std::cerr << e.what();exit(1);}
try {std::map<std::string, std::string> directiveMap({{"IO","file"},{"attributeNames","c\ta1\ta2\tp\tp2"},{"filename","./reentrancy.csv"},{"name","reentrancy"},{"operation","output"},{"types","{\"records\": {}, \"reentrancy\": {\"arity\": 5, \"auxArity\": 0, \"types\": [\"i:CallNum\", \"s:EthAddress\", \"s:EthAddress\", \"i:IntSet[i:number]\", \"i:IntSet[i:number]\"]}}"}});
if (!outputDirectory.empty() && directiveMap["IO"] == "file" && directiveMap["filename"].front() != '/') {directiveMap["filename"] = outputDirectory + "/" + directiveMap["filename"];}
RWOperation rwOperation(directiveMap);
IOSystem::getInstance().getWriter(rwOperation, symTable, recordTable)->writeAll(*rel_15_reentrancy);
} catch (std::exception& e) {std::cerr << e.what();exit(1);}
try {std::map<std::string, std::string> directiveMap({{"IO","file"},{"attributeNames","a"},{"filename","./unhandled_exception.csv"},{"name","unhandled_exception"},{"operation","output"},{"types","{\"records\": {}, \"unhandled_exception\": {\"arity\": 1, \"auxArity\": 0, \"types\": [\"i:opcodeArg[i:number]\"]}}"}});
if (!outputDirectory.empty() && directiveMap["IO"] == "file" && directiveMap["filename"].front() != '/') {directiveMap["filename"] = outputDirectory + "/" + directiveMap["filename"];}
RWOperation rwOperation(directiveMap);
IOSystem::getInstance().getWriter(rwOperation, symTable, recordTable)->writeAll(*rel_16_unhandled_exception);
} catch (std::exception& e) {std::cerr << e.what();exit(1);}
}
public:
void loadAll(std::string inputDirectory = ".") override {
try {std::map<std::string, std::string> directiveMap({{"IO","file"},{"filename","./direct_call.facts"},{"name","direct_call"},{"operation","input"},{"types","{\"direct_call\": {\"arity\": 4, \"auxArity\": 0, \"types\": [\"i:CallNum\", \"s:EthAddress\", \"s:EthAddress\", \"i:NatNum[i:number]\"]}, \"records\": {}}"}});
if (!inputDirectory.empty() && directiveMap["IO"] == "file" && directiveMap["filename"].front() != '/') {directiveMap["filename"] = inputDirectory + "/" + directiveMap["filename"];}
RWOperation rwOperation(directiveMap);
IOSystem::getInstance().getReader(rwOperation, symTable, recordTable)->readAll(*rel_10_direct_call);
} catch (std::exception& e) {std::cerr << "Error loading data: " << e.what() << '\n';}
try {std::map<std::string, std::string> directiveMap({{"IO","file"},{"filename","./call_result.facts"},{"name","call_result"},{"operation","input"},{"types","{\"call_result\": {\"arity\": 2, \"auxArity\": 0, \"types\": [\"i:result[i:number]\", \"i:NatNum[i:number]\"]}, \"records\": {}}"}});
if (!inputDirectory.empty() && directiveMap["IO"] == "file" && directiveMap["filename"].front() != '/') {directiveMap["filename"] = inputDirectory + "/" + directiveMap["filename"];}
RWOperation rwOperation(directiveMap);
IOSystem::getInstance().getReader(rwOperation, symTable, recordTable)->readAll(*rel_8_call_result);
} catch (std::exception& e) {std::cerr << "Error loading data: " << e.what() << '\n';}
try {std::map<std::string, std::string> directiveMap({{"IO","file"},{"filename","./call_exit.facts"},{"name","call_exit"},{"operation","input"},{"types","{\"call_exit\": {\"arity\": 2, \"auxArity\": 0, \"types\": [\"i:identifier\", \"i:gas\"]}, \"records\": {}}"}});
if (!inputDirectory.empty() && directiveMap["IO"] == "file" && directiveMap["filename"].front() != '/') {directiveMap["filename"] = inputDirectory + "/" + directiveMap["filename"];}
RWOperation rwOperation(directiveMap);
IOSystem::getInstance().getReader(rwOperation, symTable, recordTable)->readAll(*rel_7_call_exit);
} catch (std::exception& e) {std::cerr << "Error loading data: " << e.what() << '\n';}
try {std::map<std::string, std::string> directiveMap({{"IO","file"},{"filename","./call_entry.facts"},{"name","call_entry"},{"operation","input"},{"types","{\"call_entry\": {\"arity\": 3, \"auxArity\": 0, \"types\": [\"i:identifier\", \"i:gas\", \"s:EthAddress\"]}, \"records\": {}}"}});
if (!inputDirectory.empty() && directiveMap["IO"] == "file" && directiveMap["filename"].front() != '/') {directiveMap["filename"] = inputDirectory + "/" + directiveMap["filename"];}
RWOperation rwOperation(directiveMap);
IOSystem::getInstance().getReader(rwOperation, symTable, recordTable)->readAll(*rel_6_call_entry);
} catch (std::exception& e) {std::cerr << "Error loading data: " << e.what() << '\n';}
try {std::map<std::string, std::string> directiveMap({{"IO","file"},{"filename","./in_condition.facts"},{"name","in_condition"},{"operation","input"},{"types","{\"in_condition\": {\"arity\": 1, \"auxArity\": 0, \"types\": [\"i:result[i:number]\"]}, \"records\": {}}"}});
if (!inputDirectory.empty() && directiveMap["IO"] == "file" && directiveMap["filename"].front() != '/') {directiveMap["filename"] = inputDirectory + "/" + directiveMap["filename"];}
RWOperation rwOperation(directiveMap);
IOSystem::getInstance().getReader(rwOperation, symTable, recordTable)->readAll(*rel_11_in_condition);
} catch (std::exception& e) {std::cerr << "Error loading data: " << e.what() << '\n';}
try {std::map<std::string, std::string> directiveMap({{"IO","file"},{"filename","./is_output.facts"},{"name","is_output"},{"operation","input"},{"types","{\"is_output\": {\"arity\": 2, \"auxArity\": 0, \"types\": [\"i:result[i:number]\", \"i:opcodeArg[i:number]\"]}, \"records\": {}}"}});
if (!inputDirectory.empty() && directiveMap["IO"] == "file" && directiveMap["filename"].front() != '/') {directiveMap["filename"] = inputDirectory + "/" + directiveMap["filename"];}
RWOperation rwOperation(directiveMap);
IOSystem::getInstance().getReader(rwOperation, symTable, recordTable)->readAll(*rel_13_is_output);
} catch (std::exception& e) {std::cerr << "Error loading data: " << e.what() << '\n';}
}
public:
void dumpInputs(std::ostream& out = std::cout) override {
try {RWOperation rwOperation;
rwOperation.set("IO", "stdout");
rwOperation.set("name", "direct_call");
rwOperation.set("types","{\"direct_call\": {\"arity\": 4, \"auxArity\": 0, \"types\": [\"i:CallNum\", \"s:EthAddress\", \"s:EthAddress\", \"i:NatNum[i:number]\"]}}");
IOSystem::getInstance().getWriter(rwOperation, symTable, recordTable)->writeAll(*rel_10_direct_call);
} catch (std::exception& e) {std::cerr << e.what();exit(1);}
try {RWOperation rwOperation;
rwOperation.set("IO", "stdout");
rwOperation.set("name", "call_result");
rwOperation.set("types","{\"call_result\": {\"arity\": 2, \"auxArity\": 0, \"types\": [\"i:result[i:number]\", \"i:NatNum[i:number]\"]}}");
IOSystem::getInstance().getWriter(rwOperation, symTable, recordTable)->writeAll(*rel_8_call_result);
} catch (std::exception& e) {std::cerr << e.what();exit(1);}
try {RWOperation rwOperation;
rwOperation.set("IO", "stdout");
rwOperation.set("name", "call_exit");
rwOperation.set("types","{\"call_exit\": {\"arity\": 2, \"auxArity\": 0, \"types\": [\"i:identifier\", \"i:gas\"]}}");
IOSystem::getInstance().getWriter(rwOperation, symTable, recordTable)->writeAll(*rel_7_call_exit);
} catch (std::exception& e) {std::cerr << e.what();exit(1);}
try {RWOperation rwOperation;
rwOperation.set("IO", "stdout");
rwOperation.set("name", "call_entry");
rwOperation.set("types","{\"call_entry\": {\"arity\": 3, \"auxArity\": 0, \"types\": [\"i:identifier\", \"i:gas\", \"s:EthAddress\"]}}");
IOSystem::getInstance().getWriter(rwOperation, symTable, recordTable)->writeAll(*rel_6_call_entry);
} catch (std::exception& e) {std::cerr << e.what();exit(1);}
try {RWOperation rwOperation;
rwOperation.set("IO", "stdout");
rwOperation.set("name", "in_condition");
rwOperation.set("types","{\"in_condition\": {\"arity\": 1, \"auxArity\": 0, \"types\": [\"i:result[i:number]\"]}}");
IOSystem::getInstance().getWriter(rwOperation, symTable, recordTable)->writeAll(*rel_11_in_condition);
} catch (std::exception& e) {std::cerr << e.what();exit(1);}
try {RWOperation rwOperation;
rwOperation.set("IO", "stdout");
rwOperation.set("name", "is_output");
rwOperation.set("types","{\"is_output\": {\"arity\": 2, \"auxArity\": 0, \"types\": [\"i:result[i:number]\", \"i:opcodeArg[i:number]\"]}}");
IOSystem::getInstance().getWriter(rwOperation, symTable, recordTable)->writeAll(*rel_13_is_output);
} catch (std::exception& e) {std::cerr << e.what();exit(1);}
}
public:
void dumpOutputs(std::ostream& out = std::cout) override {
try {RWOperation rwOperation;
rwOperation.set("IO", "stdout");
rwOperation.set("name", "locked_ether");
rwOperation.set("types","{\"locked_ether\": {\"arity\": 3, \"auxArity\": 0, \"types\": [\"i:identifier\", \"i:gas\", \"s:EthAddress\"]}}");
IOSystem::getInstance().getWriter(rwOperation, symTable, recordTable)->writeAll(*rel_14_locked_ether);
} catch (std::exception& e) {std::cerr << e.what();exit(1);}
try {RWOperation rwOperation;
rwOperation.set("IO", "stdout");
rwOperation.set("name", "reentrancy");
rwOperation.set("types","{\"reentrancy\": {\"arity\": 5, \"auxArity\": 0, \"types\": [\"i:CallNum\", \"s:EthAddress\", \"s:EthAddress\", \"i:IntSet[i:number]\", \"i:IntSet[i:number]\"]}}");
IOSystem::getInstance().getWriter(rwOperation, symTable, recordTable)->writeAll(*rel_15_reentrancy);
} catch (std::exception& e) {std::cerr << e.what();exit(1);}
try {RWOperation rwOperation;
rwOperation.set("IO", "stdout");
rwOperation.set("name", "unhandled_exception");
rwOperation.set("types","{\"unhandled_exception\": {\"arity\": 1, \"auxArity\": 0, \"types\": [\"i:opcodeArg[i:number]\"]}}");
IOSystem::getInstance().getWriter(rwOperation, symTable, recordTable)->writeAll(*rel_16_unhandled_exception);
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
1);
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
