// Shymanovych Vladyslav
#include "Builder.h"

void Builder::loadData(Info* _info, const char* _fname) {
    try {

    info = _info;
    int headerLine = -1, footerLine = -1;
    filename = _fname;
    reset();
    while (readline()) {
        ++lineCount;
        switch (lexer.load(line)) {
        case LineType::Empty:
            break;
        case LineType::Header:
            try {
                if (headerLine != -1) error(101, lineCount);
                if (state != Start) saveError(300);
                headerLine = lineCount;
                state = Header;
                processHeader();
            } catch (const Error& err) { throw err; }
            catch (...) { saveError(104); }
            break;
        case LineType::Line:
            try {
                ++recordCount;
                if (state == Start || state == Footer) saveError(300);
                state = Line;
                processLine();
            } catch (const std::exception& err) { error(303, lineCount, err.what()); }
            catch (...) { saveError(303); }
            break;
        case LineType::Footer:
            try {
                if (footerLine != -1) saveError(201);
                footerLine = lineCount;
                state = Footer;
                processFooter();
            } catch (const Error& err) { throw err; }
            catch (...) { saveError(204); }
            break;
        }
    }

    if (headerLine == -1) error(100, lineCount);
    if (realMaxDownfall != info->getMaxDownfall()) error(102, lineCount);
    if (footerLine == -1) saveError(200);

    checkErrors();

    info->test();

    } catch (std::bad_alloc& _error) {
        error(500, -1);
    }
}
void Builder::processHeader() {
    int _maxDownfall;
    processField(_maxDownfall, FieldType::Int, 102, 103);
    info->setMaxDownfall(_maxDownfall);
    if (checkExtraFields()) saveError(103);
}
void Builder::processFooter() {
    size_t _dateCount;
    processField(_dateCount, FieldType::Unsigned, 202, 203);
    if (_dateCount != info->getDateCount()) saveError(202);
    if (checkExtraFields()) saveError(203);
}

void Builder::processLine() {
    int index;
    int year, month, day;
    double dayTempAvg, dayTempMin, humidity;
    int downfall;
    std::string stationCode;
    double dayTempMax, wind;

    processField(index, FieldType::Unsigned, 301, 302);
    if (index != recordCount) saveError(301);

    processField(year, FieldType::Int, 303, 302);
    processField(dayTempAvg, FieldType::Double1, 303, 302);
    processField(dayTempMin, FieldType::Double1, 303, 302);
    processField(humidity, FieldType::Double1, 303, 302);
    processField(month, FieldType::Int, 303, 302);
    processField(day, FieldType::Int, 303, 302);
    processField(downfall, FieldType::Int, 303, 302);
    if (downfall > realMaxDownfall) realMaxDownfall = downfall;
    stationCode = processField(stationCode, FieldType::String, 303, 302);
    processField(dayTempMax, FieldType::Double1, 303, 302);
    processField(wind, FieldType::Double, 303, 302);

    if (checkExtraFields()) saveError(302);
    info->load(year, dayTempAvg, dayTempMin, humidity, month, day, downfall, stationCode, dayTempMax, wind);
}

std::string Builder::processField(auto& dest, FieldType type, int codeWrong, int codeEOF) {
    if (lexer.eof()) saveError(codeEOF);
    std::string field;
    FieldType realType = lexer.next(field);
    if (type == FieldType::Double1) type = FieldType::Double;
    if (realType == FieldType::Double1) realType = FieldType::Double;
    if (!(realType == type
        || (type == FieldType::Int && realType == FieldType::Unsigned)
        || (type == FieldType::Double && realType == FieldType::Int)
        || (type == FieldType::Double && realType == FieldType::Unsigned)
        || (type == FieldType::String && realType != FieldType::Empty)))
        saveError(codeWrong);
    convert(dest, field, type);
    return field;
}
void Builder::convert(auto& dest, const std::string& src, FieldType type) {
    switch (type) {
        case FieldType::Unsigned:
            dest = std::stoul(src);
            break;
        case FieldType::Int:
            dest = std::stoi(src);
            break;
        case FieldType::Double1:
        case FieldType::Double:
            dest = std::stod(src);
            break;
        case FieldType::String:
            break;
        default:
            saveError(303);
    }
}
bool Builder::checkExtraFields() {
    std::string field;
    return lexer.next(field) != FieldType::None;
}

void Builder::reset() {
    if (f.is_open()) f.close();
    f.clear();
    f.open(filename);
    if (f) state = Start;
    else if (f.eof()) state = End;
    else {
        state = IOError;
        error(400, -1);
    }
}

bool Builder::readline() {
    std::getline(f, line);
    if (!f) {
        if (f.eof()) state = End;
        else state = IOError;
        return false;
    }
    return true;
}

void Builder::saveError(int code) noexcept {
    if (code < savedError){
        savedError = code;
        savedLine = lineCount;
    }
}
void Builder::checkErrors() {
    if (savedError != INT_MAX) error(savedError, savedLine);
}
void Builder::error(int code, int line, const char* msg) {
    throw Error(filename, line, code, msg);
}
