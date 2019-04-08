// Shymanovych Vladyslav
#include "lexer.h"

const std::string Lexer::delimiters = "%?<";
const std::string Lexer::delimEscaped = "%\\?<";

Lexer::Lexer() {
    const std::string sign = "^[\\+-]? ?";
    std::string regArr[] = {
        /* unsigned */ "^\\d+$",
        /* int */ sign+"\\d+$",
        /* double 1 */ sign+"\\d*\\.\\d$",
        /* double */ sign+"(?:\\d+\\.\\d*|\\d*\\.\\d+)$",
        /* string */ ".+"
    };
    regexes.dataTypes = std::regex(makeAlt(regArr, 5));
    const std::string del = delimEscaped;
    // /([^\s&](?:[^&]*[^\s&])?)|([&](?=\s*[&]))|(^\s*$)|(^\s*(?=[&]))|([&]\s*$)/
    regexes.nextField = std::regex(
        "([^\\s"+del+"](?:[^"+del+"]*[^\\s"+del+"])?)|(["+del+"](?=\\s*["+del+"]))|(^\\s*$)|(^\\s*(?=["+del+"]))|(["+del+"]\\s*$)"
    );
    regexes.emptyField = std::regex("[^\\s"+del+"]");
}

LineType Lexer::load(const std::string &source) {
    s = ' ' + source + ' ';
    stream = std::sregex_iterator(s.begin(), s.end(), regexes.nextField);
    _eof = isEmpty();
    return detectLineType();
}
FieldType Lexer::next(std::string& field) {
    if (_eof) return FieldType::None;
    if (stream == streamEnd) {
        _eof = true;
        return FieldType::None;
    }
    field = getField();
    ++stream;
    return detectFieldType(field);
}

bool Lexer::eof() const noexcept {return _eof;}

std::string Lexer::getField() const {
    return !isEmpty() && isMatch(stream->operator[](1))
        ? stream->str()
        : "";
}
bool Lexer::isEmpty() const {
    return stream == streamEnd;
}

LineType Lexer::detectLineType() {
    if (!std::regex_search(s, regexes.emptyField)) {
        return LineType::Empty;
    }
    std::string first = getField();
    if (first == "header") {
        next(first);
        return LineType::Header;
    }
    if (first == "footer") {
        next(first);
        return LineType::Footer;
    }
    return LineType::Line;
}
FieldType Lexer::detectFieldType(const std::string &field) {
    if (field.empty()) return FieldType::Empty;
    std::smatch match;
    if (std::regex_search(field.begin(), field.end(), match, regexes.dataTypes)) {
        if (isMatch(match[1])) return FieldType::Unsigned;
        if (isMatch(match[2])) return FieldType::Int;
        if (isMatch(match[3])) return FieldType::Double1;
        if (isMatch(match[4])) return FieldType::Double;
    }
    return FieldType::String;
}

std::string makeAlt(std::string expArr[], size_t len) {
    std::string exp = "";
    for (size_t i = 0; i < len; ++i) {
        if(i) exp += '|';
        exp += '(' + expArr[i] + ')';
    }
    std::regex reg(exp);
    return exp;
}
bool isMatch(const std::ssub_match &match) {
    return !match.str().empty();
}

std::string getTypeText(LineType type) {
    switch (type) {
        case LineType::Empty : return "Empty";
        case LineType::Header : return "Header";
        case LineType::Footer : return "Footer";
        default : return "Line";
    }
}
std::string getFieldTypeText(FieldType type) {
    switch (type) {
        case FieldType::Unsigned : return "unsigned";
        case FieldType::Int : return "int";
        case FieldType::Double1 : return "double1";
        case FieldType::Double : return "double";
        case FieldType::String : return "string";
        case FieldType::Empty : return "empty";
        default : return "none";
    }
}
