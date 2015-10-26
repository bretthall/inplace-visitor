#pragma once

#include "overload_set.h"
#include <boost/variant.hpp>

template <typename Result, typename... Fs>
struct inplace_visitor : boost::static_visitor<Result>, overload_set<Fs...>
{
   inplace_visitor (Fs... fs):
      overload_set<Fs...> (std::move (fs)...)
   {}

   using overload_set<Fs...>::operator();
};

template<typename Result, typename... Fs>
inplace_visitor<Result, typename std::decay<Fs>::type...> make_visitor(Fs&&...fs)
{
   return inplace_visitor<Result, typename std::decay<Fs>::type...>{std::forward<Fs>(fs)...};
}
