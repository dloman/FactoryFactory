#include "FactoryFactory.hpp"
#include <iostream>
#include <string>

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
enum class E1
{
  eTrue,
  eFalse
};

enum class E2
{

  eYes,
  eNo
};

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
class Test
{
  public:

    template<typename ... Ts>
    static Test Create(Ts... Args)
    {
      FactoryFactory<std::string, E1, E2, int> F(Args...);

      return Test(F.Get<int>(), F.Get<std::string>(), F.Get<E1>(), F.Get<E2>());
    }

    template<typename ... Ts>
    static Test CreateWithDefaultValues(Ts... Args)
    {
      FactoryFactory<std::string, E1, E2, int> F(make_default_args(E2::eYes, 5), Args...);

      return Test(F.Get<int>(),  F.Get<std::string>(), F.Get<E1>(), F.Get<E2>());
    }

    const std::string mName;

    const E1 mE1;

    const E2 mE2;

    const int mNumber;

  private:

    Test(int Number, const std::string& name, E1 Enum1, E2 Enum2)
    : mName(name),
      mE1(Enum1),
      mE2(Enum2),
      mNumber(Number)
    {
    }
};

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void print(const char* Name, const Test& test)
{
  std::cout
    << Name
    << " Name = " << test.mName
    << " E1 = " << (test.mE1 == E1::eTrue ? "True" : "False")
    << " E2 = " << (test.mE2 == E2::eYes ? "Yes" : "No")
    << " Number = " << test.mNumber << std::endl;
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
int main()
{
  using namespace std::literals;
  auto test = Test::Create("Jim"s, E1::eFalse, E2::eNo, 1);

  auto test1 = Test::Create(1, E2::eNo, "Randy"s, E1::eFalse);

  auto test2 = Test::CreateWithDefaultValues(1, E2::eNo, "Linda"s, E1::eFalse);
  auto test3 = Test::CreateWithDefaultValues(E2::eNo, "Gary"s, E1::eTrue);
  auto test4 = Test::CreateWithDefaultValues("Hello"s, E1::eFalse, 2);
  auto test5 = Test::CreateWithDefaultValues(E1::eTrue, "World"s);

  print("test", test);
  print("test1", test1);
  print("test2", test2);
  print("test3", test3);
  print("test4", test4);
  print("test5", test5);
}
