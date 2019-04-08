// Shymanovych Vladyslav
#pragma once
#include <string>
#include <fstream>
#include "Info.h"
#include "lexer.h"

class Builder {
public:
    void loadData(Info&, const char* filename);
private:
    std::ifstream f;
    std::string line;
    size_t lineCount = 0;
    Info* info = nullptr;
    bool readline();
    enum class State {Start, Header, Line, Footer, End, Error}
        state;
    Lexer lexer;
    void processHeader();
    void processLine();
    void processFooter();
    void error(const std::string&);
};

class Error : public std::exception {
public:
    Error(const char* filename, size_t line, size_t code, const char* msg);
    const char* what() const noexcept;
private:
    const char* filename;
    size_t line, code;
    const char* msg;
    const char* desc;
    const char* findDesc() const noexcept;
};
