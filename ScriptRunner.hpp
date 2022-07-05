//
//  ScriptRunner.hpp
//  RG_PA9
//
//  Created by rick gessner on 5/26/22.
//

#ifndef ScriptRunner_h
#define ScriptRunner_h

#include <fstream>
#include <sstream>

#include "Application.hpp"

namespace ECE141 {

class ScriptRunner {
 public:
  explicit ScriptRunner(Application &anApp) : app(anApp) {}

  StatusResult run(std::istream &anInput, std::ostream &anOutput) {
    StatusResult theResult{};
    std::string theCommand;
    while (theResult && anInput) {
      std::getline(anInput, theCommand);
      std::stringstream theStream(theCommand);
      anOutput << theCommand << "\n";
      theResult = app.handleInput(theStream);
      if (!theResult) {
        showErrors(theResult, anOutput);
      }
    }
    if (userTerminated == theResult.error) {
      theResult = noError;
    }
    return theResult;
  }

  void showErrors(ECE141::StatusResult &aResult, std::ostream &anOutput) {
    static std::map<ECE141::Errors, std::string> theErrorMessages = {
        {ECE141::illegalIdentifier, "Illegal identifier"},
        {ECE141::unknownIdentifier, "Unknown identifier"},
        {ECE141::databaseExists, "Database exists"},
        {ECE141::tableExists, "Table Exists"},
        {ECE141::syntaxError, "Syntax Error"},
        {ECE141::unknownCommand, "Unknown command"},
        {ECE141::unknownDatabase, "Unknown database"},
        {ECE141::unknownTable, "Unknown table"},
        {ECE141::unknownError, "Unknown error"},
        {ECE141::noDatabaseSpecified, "Use a database before create"}};

    std::string theMessage = "Unknown Error";
    if (theErrorMessages.count(aResult.error)) {
      theMessage = theErrorMessages[aResult.error];
    }
    anOutput << "Error (" << aResult.error << ") " << theMessage << "\n";
  }

 protected:
  Application &app;
};

}  // namespace ECE141

#endif /* ScriptRunner_h */
