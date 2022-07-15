//
//  main.cpp
//  Database2
//
//  Created by rick gessner on 3/17/19.
//  Copyright © 2019 rick gessner. All rights reserved.
//

#include <fstream>
#include <functional>
#include <iostream>
#include <map>
#include <memory>
#include <sstream>
#include <variant>

#include "TestAutomatic.hpp"
#include "TestManually.hpp"

// output colorful "FAIL" and "PASS"
#define WHITE "\033[37m"
#define RED "\033[31m"
#define GREEN "\033[32m"

int main(int argc, const char* argv[]) {
  srand(static_cast<uint32_t>(time(0)));
  if (argc > 1) {
    std::stringstream theOutput;
    ECE141::TestAutomatic theTests(theOutput);

    using TestCall = std::function<bool()>;
    static std::map<std::string, TestCall> theCalls{
        {"App", [&]() { return theTests.doAppTest(); }},
        {"AddColumn", [&]() { return theTests.doAddColumnTest(); }},
        {"BlockCache", [&]() { return theTests.doBlockCacheTest(); }},
        {"Compile", [&]() { return theTests.doCompileTest(); }},
        {"Delete", [&]() { return theTests.doDeleteTest(); }},
        {"DropTable", [&]() { return theTests.doDropTest(); }},
        {"DBCommands", [&]() { return theTests.doDBCommandsTest(); }},
        {"Index", [&]() { return theTests.doIndexTest(); }},
        {"Insert", [&]() { return theTests.doInsertTest(); }},
        {"Joins", [&]() { return theTests.doJoinTest(); }},
        {"Reader", [&]() { return theTests.doReaderTest(); }},
        {"RemoveColumn", [&]() { return theTests.doRemoveColumnTest(); }},
        {"RowCache", [&]() { return theTests.doRowCacheTest(); }},
        {"Select", [&]() { return theTests.doSelectTest(); }},
        {"Tables", [&]() { return theTests.doTablesTest(); }},
        {"Update", [&]() { return theTests.doUpdateTest(); }},
        {"ViewCache", [&]() { return theTests.doViewCacheTest(); }},
    };

    std::string theCmd(argv[1]);
    if (theCalls.count(theCmd)) {
      bool theResult = theCalls[theCmd]();
      const char* theStatus[] = {"FAIL", "PASS"};
      std::cout << theCmd << " test " << theStatus[theResult] << "\n";
      std::cout << "------------------------------\n"
                << theOutput.str() << "\n";
    } else if ("All" == theCmd) {
      const char* theStatus[] = {"FAIL", "PASS"};
      const char* theColor[] = {RED, GREEN};
      for (auto& [str, func] : theCalls) {
        bool theResult = theCalls[str]();
        std::cout << str << " test\t\t" << theColor[theResult]
                  << theStatus[theResult] << WHITE << "\n";
      }
    } else
      std::cout << "Unknown test\n";
  } else {
    doManualTesting();
  }
  return 0;
}
