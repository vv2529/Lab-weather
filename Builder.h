// Shymanovych Vladyslav
#pragma once
#include <cstdlib>
#include <string>
#include <fstream>
#include "Info.h"
#include "lexer.h"
#include "Error.h"

class Builder {
public:
    void loadData(Info*, const char* filename);
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
    std::string processField(auto& dest, FieldType type, int codeWrong, int codeEOF);
    void convert(auto& dest, const std::string&, FieldType);
    bool checkExtraFields();
    int realMaxDownfall = 0;
    int savedError = INT_MAX, savedLine = INT_MAX;
    void saveError(int code) noexcept;
    void checkErrors();
    void error(int code, int line);
};
