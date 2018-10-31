#pragma once
#include <tuple>

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
namespace
{
  template <class T, std::size_t N, class... Args>
  struct get_first_impl
  {
      static constexpr auto value = N;
  };

  template <class T, std::size_t N, class... Args>
  struct get_first_impl<T, N, T, Args...>
  {
      static constexpr auto value = N;
  };

  template <class T, std::size_t N, class U, class... Args>
  struct get_first_impl<T, N, U, Args...>
  {
      static constexpr auto value = get_first_impl<T, N + 1, Args...>::value;
  };

  template<typename T, typename ... Ts>
  T get_first(const std::tuple<Ts...>& t)
  {
    return std::get<get_first_impl<T, 0, Ts...>::value>(t);
  }
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
template<typename ... DefaultTypes>
struct DefaultArguments
{
  std::tuple<DefaultTypes...> mDefaultArgs;
};

template<typename ... DefaultTypes>
DefaultArguments<DefaultTypes...> make_default_args(DefaultTypes ... Args)
{
  return {{Args...}};
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
template <typename T>
class Getter
{
  public:

    template <typename ... ArgTypes>
    Getter(const std::tuple<ArgTypes...>& Args)
    : mT(get_first<T>(Args))
    {
    }

    T Get()
    {
      return mT;
    }

  private:

    T mT;
};

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
template<typename ... Types>
class FactoryFactory : public Getter<Types>...
{
  public:

    template <typename ... ArgTypes>
    FactoryFactory(ArgTypes ... Args)
    : Getter<Types>(std::make_tuple(Args...))...
    {
    }

    template <typename ... DefaultTypes, typename ... ArgTypes>
    FactoryFactory(DefaultArguments<DefaultTypes...> DefaultValues, ArgTypes... Args)
    : Getter<Types>(std::tuple_cat(std::make_tuple(Args...), DefaultValues.mDefaultArgs))...
    {
    }

    template <typename U>
    U Get()
    {
      return Getter<U>::Get();
    }
};

