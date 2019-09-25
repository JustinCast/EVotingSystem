#include <eosio/eosio.hpp>

using namespace eosio;
using namespace std;

class [[eosio::contract("vote")]] vote : public eosio::contract {

  public:
    vote(name receiver, name code, datastream<const char*> ds):contract(receiver, code, ds) {}

    [[eosio::action]]
    void upsert(
      name user, 
      string first_name, 
      std::string last_name
    ) 
    {
      require_auth( user );
      
      vote_index votes( get_self(), get_first_receiver().value );
      auto iterator = votes.find(user.value);
      
      if( iterator == votes.end() )
      {
        votes.emplace(user, [&]( auto& row ) {
         row.key = user;
         row.first_name = first_name;
         row.last_name = last_name;
        });
      }
      else {
        votes.modify(iterator, user, [&]( auto& row ) {
          row.key = user;
          row.first_name = first_name;
          row.last_name = last_name;
        });
      }
    }

    [[eosio::action]]
    void erase(name user) {
      require_auth(user);

      vote_index addresses( get_self(), get_first_receiver().value);

      auto iterator = votes.find(user.value);
      check(iterator != votes.end(), "Record does not exist");
      votes.erase(iterator);
    }
    
  private:
    class [[eosio::table]] voter {
      name key;
      std::string first_name;
      std::string last_name;

      uint64_t primary_key() const { return key.value;}
    };
  
    typedef eosio::multi_index<"voters"_n, voter> vote_index;
};