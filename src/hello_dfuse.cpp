#include <eosio/eosio.hpp>
#include <eosio/print.hpp>

using namespace eosio;

class[[eosio::contract("hello_dfuse")]] hello : public contract
{
public:
   using contract::contract;

   [[eosio::action]] void hi(name user) {
      require_auth(user);
      print("Hello, ", user);
      // Send an inline context-free action `dfuseiohooks:event` to index transaction in context of order_id
      eosio::action(
          std::vector<eosio::permission_level>(),
          "dfuseiohooks"_n,
          "event"_n,
          std::make_tuple(
              // Parameter `auth_key`
              std::string(""),
              // Parameter `data` (ensures to escape `&` and `=` in values if you use user-provided strings!)
              std::string("user=test")))
          .send_context_free();
   }
};
