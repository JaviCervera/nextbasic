#ifndef PREPROCESSOR_H
#define PREPROCESSOR_H

#include "token.h"
#include <vector>

enum PreprocOptions {
    OPTION_CONSOLE,
    OPTION_GUI
};

class Preprocessor {
public:
    Preprocessor();
    void Preprocess(const std::vector<Token>& tokens);
    const std::vector<std::string>& Includes() const { return includes; }
    const std::vector<std::string>& Modules() const { return modules; }
    const std::vector<std::string>& Links() const { return links; }
    void AddModule(const std::string& name) { modules.push_back(name); }
    const std::vector<Token>& PreprocessedTokens() const { return preprocessedTokens; }
    bool IsGuiApp() const { return isGui; }
private:
    std::vector<std::string> includes;
    std::vector<std::string> modules;
    std::vector<std::string> links;
    std::vector<Token> preprocessedTokens;
    bool isGui;
};

#endif // PREPROCESSOR_H
