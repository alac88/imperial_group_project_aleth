
#include "souffle/CompiledSouffle.h"

extern "C" {}

namespace souffle {
using namespace ram;
struct t_btree_2__0_1__3 {
  using t_tuple = Tuple<RamDomain, 2>;
  using t_ind_0 = btree_set<t_tuple, index_utils::comparator<0, 1>>;
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
    } else
      return false;
  }
  bool insert(const RamDomain* ramDomain) {
    RamDomain data[2];
    std::copy(ramDomain, ramDomain + 2, data);
    const t_tuple& tuple = reinterpret_cast<const t_tuple&>(data);
    context h;
    return insert(tuple, h);
  }
  bool insert(RamDomain a0, RamDomain a1) {
    RamDomain data[2] = {a0, a1};
    return insert(data);
  }
  bool contains(const t_tuple& t, context& h) const {
    return ind_0.contains(t, h.hints_0);
  }
  bool contains(const t_tuple& t) const {
    context h;
    return contains(t, h);
  }
  std::size_t size() const { return ind_0.size(); }
  iterator find(const t_tuple& t, context& h) const {
    return ind_0.find(t, h.hints_0);
  }
  iterator find(const t_tuple& t) const {
    context h;
    return find(t, h);
  }
  range<iterator> equalRange_0(const t_tuple& t, context& h) const {
    return range<iterator>(ind_0.begin(), ind_0.end());
  }
  range<iterator> equalRange_0(const t_tuple& t) const {
    return range<iterator>(ind_0.begin(), ind_0.end());
  }
  range<t_ind_0::iterator> equalRange_3(const t_tuple& t, context& h) const {
    auto pos = ind_0.find(t, h.hints_0);
    auto fin = ind_0.end();
    if (pos != fin) {
      fin = pos;
      ++fin;
    }
    return make_range(pos, fin);
  }
  range<t_ind_0::iterator> equalRange_3(const t_tuple& t) const {
    context h;
    return equalRange_3(t, h);
  }
  bool empty() const { return ind_0.empty(); }
  std::vector<range<iterator>> partition() const {
    return ind_0.getChunks(400);
  }
  void purge() { ind_0.clear(); }
  iterator begin() const { return ind_0.begin(); }
  iterator end() const { return ind_0.end(); }
  void printHintStatistics(std::ostream& o, const std::string prefix) const {
    const auto& stats_0 = ind_0.getHintStatistics();
    o << prefix << "arity 2 direct b-tree index [0,1]: (hits/misses/total)\n";
    o << prefix << "Insert: " << stats_0.inserts.getHits() << "/"
      << stats_0.inserts.getMisses() << "/" << stats_0.inserts.getAccesses()
      << "\n";
    o << prefix << "Contains: " << stats_0.contains.getHits() << "/"
      << stats_0.contains.getMisses() << "/" << stats_0.contains.getAccesses()
      << "\n";
    o << prefix << "Lower-bound: " << stats_0.lower_bound.getHits() << "/"
      << stats_0.lower_bound.getMisses() << "/"
      << stats_0.lower_bound.getAccesses() << "\n";
    o << prefix << "Upper-bound: " << stats_0.upper_bound.getHits() << "/"
      << stats_0.upper_bound.getMisses() << "/"
      << stats_0.upper_bound.getAccesses() << "\n";
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
    } else
      return false;
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
  std::size_t size() const { return ind_0.size(); }
  iterator find(const t_tuple& t, context& h) const {
    return ind_0.find(t, h.hints_0);
  }
  iterator find(const t_tuple& t) const {
    context h;
    return find(t, h);
  }
  range<iterator> equalRange_0(const t_tuple& t, context& h) const {
    return range<iterator>(ind_0.begin(), ind_0.end());
  }
  range<iterator> equalRange_0(const t_tuple& t) const {
    return range<iterator>(ind_0.begin(), ind_0.end());
  }
  range<t_ind_0::iterator> equalRange_1(const t_tuple& t, context& h) const {
    auto pos = ind_0.find(t, h.hints_0);
    auto fin = ind_0.end();
    if (pos != fin) {
      fin = pos;
      ++fin;
    }
    return make_range(pos, fin);
  }
  range<t_ind_0::iterator> equalRange_1(const t_tuple& t) const {
    context h;
    return equalRange_1(t, h);
  }
  bool empty() const { return ind_0.empty(); }
  std::vector<range<iterator>> partition() const {
    return ind_0.getChunks(400);
  }
  void purge() { ind_0.clear(); }
  iterator begin() const { return ind_0.begin(); }
  iterator end() const { return ind_0.end(); }
  void printHintStatistics(std::ostream& o, const std::string prefix) const {
    const auto& stats_0 = ind_0.getHintStatistics();
    o << prefix << "arity 1 direct b-tree index [0]: (hits/misses/total)\n";
    o << prefix << "Insert: " << stats_0.inserts.getHits() << "/"
      << stats_0.inserts.getMisses() << "/" << stats_0.inserts.getAccesses()
      << "\n";
    o << prefix << "Contains: " << stats_0.contains.getHits() << "/"
      << stats_0.contains.getMisses() << "/" << stats_0.contains.getAccesses()
      << "\n";
    o << prefix << "Lower-bound: " << stats_0.lower_bound.getHits() << "/"
      << stats_0.lower_bound.getMisses() << "/"
      << stats_0.lower_bound.getAccesses() << "\n";
    o << prefix << "Upper-bound: " << stats_0.upper_bound.getHits() << "/"
      << stats_0.upper_bound.getMisses() << "/"
      << stats_0.upper_bound.getAccesses() << "\n";
  }
};

class Sf_locked_ether : public SouffleProgram {
 private:
  static inline bool regex_wrapper(const std::string& pattern,
                                   const std::string& text) {
    bool result = false;
    try {
      result = std::regex_match(text, std::regex(pattern));
    } catch (...) {
      std::cerr << "warning: wrong pattern provided for match(\"" << pattern
                << "\",\"" << text << "\").\n";
    }
    return result;
  }

 private:
  static inline std::string substr_wrapper(const std::string& str, size_t idx,
                                           size_t len) {
    std::string result;
    try {
      result = str.substr(idx, len);
    } catch (...) {
      std::cerr << "warning: wrong index position provided by substr(\"";
      std::cerr << str << "\"," << (int32_t)idx << "," << (int32_t)len
                << ") functor.\n";
    }
    return result;
  }

 private:
  static inline RamDomain wrapper_tonumber(const std::string& str) {
    RamDomain result = 0;
    try {
      result = stord(str);
    } catch (...) {
      std::cerr << "error: wrong string provided by to_number(\"";
      std::cerr << str << "\") functor.\n";
      raise(SIGFPE);
    }
    return result;
  }

 public:
  // -- initialize symbol table --
  SymbolTable symTable;  // -- initialize record table --
  RecordTable recordTable;
  // -- Table: call_entry
  std::unique_ptr<t_btree_2__0_1__3> rel_1_call_entry =
      std::make_unique<t_btree_2__0_1__3>();
  souffle::RelationWrapper<0, t_btree_2__0_1__3, Tuple<RamDomain, 2>, 2, 0>
      wrapper_rel_1_call_entry;
  // -- Table: call_exit
  std::unique_ptr<t_btree_1__0__1> rel_2_call_exit =
      std::make_unique<t_btree_1__0__1>();
  souffle::RelationWrapper<1, t_btree_1__0__1, Tuple<RamDomain, 1>, 1, 0>
      wrapper_rel_2_call_exit;
  // -- Table: locked_ether
  std::unique_ptr<t_btree_2__0_1__3> rel_3_locked_ether =
      std::make_unique<t_btree_2__0_1__3>();
  souffle::RelationWrapper<2, t_btree_2__0_1__3, Tuple<RamDomain, 2>, 2, 0>
      wrapper_rel_3_locked_ether;

 public:
  Sf_locked_ether()
      : wrapper_rel_1_call_entry(
            *rel_1_call_entry, symTable, "call_entry",
            std::array<const char*, 2>{{"i:ProgCounter", "s:EthAddress"}},
            std::array<const char*, 2>{{"c1", "a1"}}),

        wrapper_rel_2_call_exit(*rel_2_call_exit, symTable, "call_exit",
                                std::array<const char*, 1>{{"i:ProgCounter"}},
                                std::array<const char*, 1>{{"c2"}}),

        wrapper_rel_3_locked_ether(
            *rel_3_locked_ether, symTable, "locked_ether",
            std::array<const char*, 2>{{"s:EthAddress", "i:ProgCounter"}},
            std::array<const char*, 2>{{"a1", "c1"}}) {
    addRelation("call_entry", &wrapper_rel_1_call_entry, true, false);
    addRelation("call_exit", &wrapper_rel_2_call_exit, true, false);
    addRelation("locked_ether", &wrapper_rel_3_locked_ether, false, true);
  }
  ~Sf_locked_ether() {}

 private:
  void runFunction(std::string inputDirectory = ".",
                   std::string outputDirectory = ".", bool performIO = false) {
    SignalHandler::instance()->set();
    std::atomic<size_t> iter(0);

#if defined(_OPENMP)
    if (getNumThreads() > 0) {
      omp_set_num_threads(getNumThreads());
    }
#endif

    // -- query evaluation --
    if (performIO) {
      try {
        std::map<std::string, std::string> directiveMap(
            {{"IO", "file"},
             {"filename", "./call_entry.facts"},
             {"name", "call_entry"}});
        if (!inputDirectory.empty() && directiveMap["IO"] == "file" &&
            directiveMap["filename"].front() != '/') {
          directiveMap["filename"] =
              inputDirectory + "/" + directiveMap["filename"];
        }
        IODirectives ioDirectives(directiveMap);
        IOSystem::getInstance()
            .getReader(
                std::vector<RamTypeAttribute>(
                    {RamTypeAttribute::Signed, RamTypeAttribute::Symbol}),
                symTable, ioDirectives, 0)
            ->readAll(*rel_1_call_entry);
      } catch (std::exception& e) {
        std::cerr << "Error loading data: " << e.what() << '\n';
      }
    }
    if (performIO) {
      try {
        std::map<std::string, std::string> directiveMap(
            {{"IO", "file"},
             {"filename", "./call_exit.facts"},
             {"name", "call_exit"}});
        if (!inputDirectory.empty() && directiveMap["IO"] == "file" &&
            directiveMap["filename"].front() != '/') {
          directiveMap["filename"] =
              inputDirectory + "/" + directiveMap["filename"];
        }
        IODirectives ioDirectives(directiveMap);
        IOSystem::getInstance()
            .getReader(
                std::vector<RamTypeAttribute>({RamTypeAttribute::Signed}),
                symTable, ioDirectives, 0)
            ->readAll(*rel_2_call_exit);
      } catch (std::exception& e) {
        std::cerr << "Error loading data: " << e.what() << '\n';
      }
    }
    SignalHandler::instance()->setMsg(R"_(locked_ether(A1,C1) :- 
   call_entry(C1,A1),
   call_exit(C2),
   (C1+1) = C2.
in file /Users/zijian/Code/group_project/imperial_group_project_aleth/build/souffle/bin/locked_ether.dl [26:1-26:68])_");
    if (!(rel_1_call_entry->empty()) && !(rel_2_call_exit->empty())) {
      [&]() {
        CREATE_OP_CONTEXT(rel_1_call_entry_op_ctxt,
                          rel_1_call_entry->createContext());
        CREATE_OP_CONTEXT(rel_2_call_exit_op_ctxt,
                          rel_2_call_exit->createContext());
        CREATE_OP_CONTEXT(rel_3_locked_ether_op_ctxt,
                          rel_3_locked_ether->createContext());
        for (const auto& env0 : *rel_1_call_entry) {
          if (rel_2_call_exit->contains(
                  Tuple<RamDomain, 1>{{(env0[0]) + (RamSigned(1))}},
                  READ_OP_CONTEXT(rel_2_call_exit_op_ctxt))) {
            Tuple<RamDomain, 2> tuple{{static_cast<RamDomain>(env0[1]),
                                       static_cast<RamDomain>(env0[0])}};
            rel_3_locked_ether->insert(
                tuple, READ_OP_CONTEXT(rel_3_locked_ether_op_ctxt));
          }
        }
      }();
    }
    if (performIO) {
      try {
        std::map<std::string, std::string> directiveMap(
            {{"IO", "file"},
             {"attributeNames", "a1\tc1"},
             {"filename", "./locked_ether.csv"},
             {"name", "locked_ether"}});
        if (!outputDirectory.empty() && directiveMap["IO"] == "file" &&
            directiveMap["filename"].front() != '/') {
          directiveMap["filename"] =
              outputDirectory + "/" + directiveMap["filename"];
        }
        IODirectives ioDirectives(directiveMap);
        IOSystem::getInstance()
            .getWriter(
                std::vector<RamTypeAttribute>(
                    {RamTypeAttribute::Symbol, RamTypeAttribute::Signed}),
                symTable, ioDirectives, 0)
            ->writeAll(*rel_3_locked_ether);
      } catch (std::exception& e) {
        std::cerr << e.what();
        exit(1);
      }
    }
    if (!isHintsProfilingEnabled() && performIO) rel_1_call_entry->purge();
    if (!isHintsProfilingEnabled() && performIO) rel_2_call_exit->purge();

    // -- relation hint statistics --
    if (isHintsProfilingEnabled()) {
      std::cout << " -- Operation Hint Statistics --\n";
      std::cout << "Relation rel_1_call_entry:\n";
      rel_1_call_entry->printHintStatistics(std::cout, "  ");
      std::cout << "\n";
      std::cout << "Relation rel_2_call_exit:\n";
      rel_2_call_exit->printHintStatistics(std::cout, "  ");
      std::cout << "\n";
      std::cout << "Relation rel_3_locked_ether:\n";
      rel_3_locked_ether->printHintStatistics(std::cout, "  ");
      std::cout << "\n";
    }
    SignalHandler::instance()->reset();
  }

 public:
  void run() override { runFunction(".", ".", false); }

 public:
  void runAll(std::string inputDirectory = ".",
              std::string outputDirectory = ".") override {
    runFunction(inputDirectory, outputDirectory, true);
  }

 public:
  void printAll(std::string outputDirectory = ".") override {
    try {
      std::map<std::string, std::string> directiveMap(
          {{"IO", "file"},
           {"attributeNames", "a1\tc1"},
           {"filename", "./locked_ether.csv"},
           {"name", "locked_ether"}});
      if (!outputDirectory.empty() && directiveMap["IO"] == "file" &&
          directiveMap["filename"].front() != '/') {
        directiveMap["filename"] =
            outputDirectory + "/" + directiveMap["filename"];
      }
      IODirectives ioDirectives(directiveMap);
      IOSystem::getInstance()
          .getWriter(std::vector<RamTypeAttribute>(
                         {RamTypeAttribute::Symbol, RamTypeAttribute::Signed}),
                     symTable, ioDirectives, 0)
          ->writeAll(*rel_3_locked_ether);
    } catch (std::exception& e) {
      std::cerr << e.what();
      exit(1);
    }
  }

 public:
  void loadAll(std::string inputDirectory = ".") override {
    try {
      std::map<std::string, std::string> directiveMap(
          {{"IO", "file"},
           {"filename", "./call_entry.facts"},
           {"name", "call_entry"}});
      if (!inputDirectory.empty() && directiveMap["IO"] == "file" &&
          directiveMap["filename"].front() != '/') {
        directiveMap["filename"] =
            inputDirectory + "/" + directiveMap["filename"];
      }
      IODirectives ioDirectives(directiveMap);
      IOSystem::getInstance()
          .getReader(std::vector<RamTypeAttribute>(
                         {RamTypeAttribute::Signed, RamTypeAttribute::Symbol}),
                     symTable, ioDirectives, 0)
          ->readAll(*rel_1_call_entry);
    } catch (std::exception& e) {
      std::cerr << "Error loading data: " << e.what() << '\n';
    }
    try {
      std::map<std::string, std::string> directiveMap(
          {{"IO", "file"},
           {"filename", "./call_exit.facts"},
           {"name", "call_exit"}});
      if (!inputDirectory.empty() && directiveMap["IO"] == "file" &&
          directiveMap["filename"].front() != '/') {
        directiveMap["filename"] =
            inputDirectory + "/" + directiveMap["filename"];
      }
      IODirectives ioDirectives(directiveMap);
      IOSystem::getInstance()
          .getReader(std::vector<RamTypeAttribute>({RamTypeAttribute::Signed}),
                     symTable, ioDirectives, 0)
          ->readAll(*rel_2_call_exit);
    } catch (std::exception& e) {
      std::cerr << "Error loading data: " << e.what() << '\n';
    }
  }

 public:
  void dumpInputs(std::ostream& out = std::cout) override {
    try {
      IODirectives ioDirectives;
      ioDirectives.setIOType("stdout");
      ioDirectives.setRelationName("call_entry");
      IOSystem::getInstance()
          .getWriter(std::vector<RamTypeAttribute>(
                         {RamTypeAttribute::Signed, RamTypeAttribute::Symbol}),
                     symTable, ioDirectives, 0)
          ->writeAll(*rel_1_call_entry);
    } catch (std::exception& e) {
      std::cerr << e.what();
      exit(1);
    }
    try {
      IODirectives ioDirectives;
      ioDirectives.setIOType("stdout");
      ioDirectives.setRelationName("call_exit");
      IOSystem::getInstance()
          .getWriter(std::vector<RamTypeAttribute>({RamTypeAttribute::Signed}),
                     symTable, ioDirectives, 0)
          ->writeAll(*rel_2_call_exit);
    } catch (std::exception& e) {
      std::cerr << e.what();
      exit(1);
    }
  }

 public:
  void dumpOutputs(std::ostream& out = std::cout) override {
    try {
      IODirectives ioDirectives;
      ioDirectives.setIOType("stdout");
      ioDirectives.setRelationName("locked_ether");
      IOSystem::getInstance()
          .getWriter(std::vector<RamTypeAttribute>(
                         {RamTypeAttribute::Symbol, RamTypeAttribute::Signed}),
                     symTable, ioDirectives, 0)
          ->writeAll(*rel_3_locked_ether);
    } catch (std::exception& e) {
      std::cerr << e.what();
      exit(1);
    }
  }

 public:
  SymbolTable& getSymbolTable() override { return symTable; }
};
SouffleProgram* newInstance_locked_ether() { return new Sf_locked_ether; }
SymbolTable* getST_locked_ether(SouffleProgram* p) {
  return &reinterpret_cast<Sf_locked_ether*>(p)->symTable;
}

#ifdef __EMBEDDED_SOUFFLE__
class factory_Sf_locked_ether : public souffle::ProgramFactory {
  SouffleProgram* newInstance() { return new Sf_locked_ether(); };

 public:
  factory_Sf_locked_ether() : ProgramFactory("locked_ether") {}
};
static factory_Sf_locked_ether __factory_Sf_locked_ether_instance;
}
#else
}
int main(int argc, char** argv) {
  try {
    souffle::CmdOptions opt(R"(locked_ether.dl)", R"(.)", R"(.)", false, R"()",
                            1, -1);
    if (!opt.parse(argc, argv)) return 1;
    souffle::Sf_locked_ether obj;
#if defined(_OPENMP)
    obj.setNumThreads(opt.getNumJobs());

#endif
    obj.runAll(opt.getInputFileDir(), opt.getOutputFileDir());
    return 0;
  } catch (std::exception& e) {
    souffle::SignalHandler::instance()->error(e.what());
  }
}

#endif
