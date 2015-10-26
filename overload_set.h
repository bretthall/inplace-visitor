#pragma once

#include <type_traits>

// taken from https://github.com/picanumber/CODEine/blob/master/lambda_utils.h

template<class... Fs>
struct overload_set
{
};

template<class F0, class... Fs>
struct overload_set<F0, Fs...>
   : F0, overload_set<Fs...>
{
   overload_set(F0 f0, Fs... fs) :
		F0(std::move(f0)),
		overload_set<Fs...>(std::move(fs)...)
   {}

   using F0::operator();
   using overload_set<Fs...>::operator();
};

template<class F>
struct overload_set<F> : F
{
   overload_set(F f) : F(std::move(f)){};
   using F::operator();
};

template<class... Fs>
overload_set<typename std::decay<Fs>::type...> overload(Fs&&... fs)
{
   return{ std::forward<Fs>(fs)... };
}
