#include <evoting.hpp>

ACTION evoting::add_candidate(string name) {
  require_auth(from);
  
}

EOSIO_DISPATCH(evoting, (hi)(clear))