#pragma once

#include <algorithm>
#include <functional>
#include <string>
#include <vector>

struct TestInfo
{
  std::string               CategoryName;
  std::function<void()>     Function;
  std::vector<std::string>  Parameters;
  std::string               TestName;
};

class TestFramework
{
public: // data

  std::vector<std::string> Excludes;
  std::vector<std::string> Includes;
  std::vector<std::string> Logs;
  std::vector<TestInfo> Tests;

public:

  int Run()
  {
    auto testsToRun = std::vector<TestInfo*>(Tests.size());
    for (auto& test : tests)
    {
      testsToRun.push_back(&test);
    }
    
    for (auto& include : includes)
    {
      testsToRun.erase(std::remove_if(
        testsToRun.begin(),
        testsToRun.end(),
        [&](TestInfo* test) 
        { 
          return test->CategoryName != include || test->TestName != include;
        }));
    }

    for (auto& exclude : excludes)
    {
      testsToRun.erase(std::remove_if(
        testsToRun.begin(),
        testsToRun.end(),
        [&](TestInfo* test) 
        { 
          return test->CategoryName == exclude || test->TestName == exclude;
        }));
    }

    for (auto& test : testsToRun)
    {
      try
      {
        test->Function();

        Logs.push_back("");
      }
      catch (std::exception& ex)
      {
        Logs.push_back()
      }
    }
  }
};

class FooTests
{
public:

  TestFact(ConstructFoo)
  {
    
  }
  
  TestTheory(PurchaseGame, float cashOnHand, string gameName)
  {
    
  }
  
  TestTheoryData(PurchaseGame, 10.0f, "LegendOfGrimrock2");
  TestTheoryData(PurchaseGame, 5.0f, "ShovelKnight");
};