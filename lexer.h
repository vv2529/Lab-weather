// Shymanovych Vladyslav
#pragma once
#include <string>
#include <regex>

enum class LineType {Empty, Footer, Header, Line};
enum class FieldType {Unsigned, Int, Double1, Double, String, Empty, None};

class Lexer {
public:
    Lexer();
    LineType load(const std::string&);
    FieldType next(std::string &field);
    bool eof() const noexcept;
    static const std::string delimiters,
        delimEscaped;
private:
    std::string s;
    std::sregex_iterator stream,
        streamEnd;
    bool _eof = true;
    struct Regexes {
        std::regex dataTypes;
        std::regex nextField;
        std::regex emptyField;
    } regexes;
    std::string getField() const;
    bool isEmpty() const;
    LineType detectLineType();
    FieldType detectFieldType(const std::string&);
};

std::string makeAlt(std::string expArr[], size_t len);
bool isMatch(const std::ssub_match&);

std::string getTypeText(LineType);
std::string getFieldTypeText(FieldType);
