#pragma once

#include "overload_set.h"
#include <boost/variant.hpp>

template <typename Result, typename... Fs>
struct inplace_visitor : boost::static_visitor<Result>
{
   overload_set<Fs...> m_overloads;

   inplace_visitor (Fs... fs):
      m_overloads (std::move (fs)...)
   {}

   template<typename... Args>
   Result operator()(Args&&... as) const
   {
      return m_overloads (std::forward<Args>(as)...);
   }
};

template<typename Result, typename... Fs>
inplace_visitor<Result, typename std::decay<Fs>::type...> make_visitor(Fs&&...fs)
{
   return inplace_visitor<Result, typename std::decay<Fs>::type...>{std::forward<Fs>(fs)...};
}
