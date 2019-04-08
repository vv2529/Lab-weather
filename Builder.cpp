// Shymanovych Vladyslav
#include "Builder.h"

void Builder::loadData(Info& info, const char* _fname) {
    try {

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
                if (headerLine != -1) error(101);
                if (state != Start) saveError(300);
                headerLine = lineCount;
                state = Header;
            } catch (...) { error(104); }
            break;
        case LineType::Line:
            try {
                ++recordCount;
                if (state == Start || state == Footer) saveError(300);
                state = Line;
            } catch (...) { error(303); }
            break;
        case LineType::Footer:
            try {
                if (footerLine != -1) saveError(201);
                footerLine = lineCount;
                state = Footer;
            } catch (...) { error(204); }
            break;
        }
    }

    if (headerLine == -1) error(100);
    if (footerLine == -1) saveError(200);

    checkErrors();

    } catch (std::bad_alloc& _error) {
        error(500);
    }
}
void Builder::reset() {
    if (f.is_open()) f.close();
    f.clear();
    f.open(filename);
    if (f) state = Start;
    else if (f.eof()) state = End;
    else {
        state = IOError;
        error(400);
    }
}

bool Builder::readline() {
    f >> line;
    if (!f) {
        if (f.eof()) state = End;
        else state = IOError;
        return false;
    }
    return true;
}

void Builder::saveError(int code) noexcept {
    if (code < savedError) savedError = code;
}
void Builder::checkErrors() {
    if (savedError != -1) error(savedError);
}
void Builder::error(int code) {
    throw Error(filename, lineCount, code);
}

Error::Error(const char* _filename, int _line, int _code):
    filename(_filename),
    line(_line),
    code(_code),
    desc(findDesc())
{
}
const char* Error::what() const noexcept {
    return ("ERROR " + std::to_string(code) + " (line " + std::to_string(line) + "): " + desc).c_str();
}
const char* Error::findDesc() const noexcept {
    switch (code) {
        case 100: return "No header";
        case 101: return "Multiple headers";
        case 102: return "Incorrect header content";
        case 103: return "Incorrect number of fields in header";
        case 104: return "Unknown error in header";

        case 200: return "No footer";
        case 201: return "Multiple footers";
        case 202: return "Incorrect footer content";
        case 203: return "Incorrect number of fields in footer";
        case 204: return "Unknown error in footer";

        case 300: return "Wrong line order";
        case 301: return "Wrong indexes";
        case 302: return "Incorrect number of fields in a line";
        case 303: return "Unknown error in a line";

        case 400: return "File error";
        case 500: return "bad_alloc";
    }
    return "Unknown error";
}
