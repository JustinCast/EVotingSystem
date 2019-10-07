#include <eosio/eosio.hpp>

using namespace std;
using namespace eosio;

CONTRACT evoting : public contract {
  public:
    using contract::contract;

    ACTION add_candidate(string name);
    ACTION reset();
    ACTION results();
    ACTION vote(name user, name candidate);
    election(name s) : contract(s), _candidates(s, s), _voters(s, s), _candidates_count(0) {}

  private:
    TABLE candidate {
      name    _candidate;
      uint2_t  _count = 0;
      auto primary_key() const { return _candidate.value }; 
    };
    typedef multi_index<name("candidate"), candidate> candidate_table;
    
    TABLE voter {
      name    _voter;
      name  _candidate;
      auto primary_key() const { return _voter.value; }
      candidate_key() const { return _candidate.value; }
    };
    typedef multi_index<name("voter"), voter> voter_table;
};
