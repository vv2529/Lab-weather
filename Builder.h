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
    int lineCount = 0, recordCount = 0;
    const char* filename;
    Info* info = nullptr;
    void reset();
    bool readline();
    enum State {Start, Header, Line, Footer, End, IOError}
        state;
    Lexer lexer;
    void processHeader();
    void processFooter();
    void processLine();
    void processField(auto& dest, FieldType type, int codeWrong, int codeEOF);
    void convert(auto& dest, const std::string&, FieldType);
    int savedError = -1;
    void saveError(int code) noexcept;
    void checkErrors();
    void error(int code);
};

class Error : public std::exception {
public:
    Error(const char* filename, int line, int code);
    const char* what() const noexcept;
private:
    const char* filename;
    int line, code;
    const char* desc;
    const char* findDesc() const noexcept;
};
