#pragma once

#include <algorithm>
#include <functional>
#include <string>
#include <vector>

using namespace std;

struct TestInfo
{
  string CategoryName;
  function<void()> Function;
  vector<string> Parameters;
  string TestName;
};

class TestFramework
{
public:

  int Run(vector<TestInfo> tests, vector<string> excludes, vector<string> includes)
  {
    auto testsToRun = vector<TestInfo*>(tests.size());
    
    if (includes.empty())
    {
      testsToRun = tests;
    }
    else
    {
      copy_if(
        tests.begin(), 
        tests.end(),
        testsToRun.begin(),
        [](auto& test) 
        { 
          for (auto& include : includes)
          {
            if (test.CategoryName == include || test.TestName == include)
            {
              return true;
            }
          }
          
          return false;
        }));
    }
    
    if (!excludes.empty())
    {
      testsToRun.erase(remove_if(
        testsToRun.begin(), 
        testsToRun.end(), 
        [](auto& test) 
        { 
          for (auto& exclude : excludes)
          {
            if (test.CategoryName == exclude || test.TestName == exclude)
            {
              return true;
            }
          }
          
          return false;
        }));
    }
    
    for (auto& test : testsToRun)
    {
      try
      {
        test.Function();
      }
      catch (...)
      {
        
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