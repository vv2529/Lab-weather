// Shymanovych Vladyslav
#include "Builder.h"

void Builder::loadData(Info& info, const char* filename) {
}

Error::Error(const char* _filename, size_t _line, size_t _code, const char* _msg):
    filename(_filename),
    line(_line),
    code(_code),
    msg(_msg),
    desc(findDesc())
{
}

const char* Error::what() const noexcept {
    return ("ERROR " + std::to_string(code) + " (line " + std::to_string(line) + "): " + desc + ": " + msg).c_str();
}
const char* Error::findDesc() const noexcept {
    switch (code) {
        case 100: return "No header";
        case 101: return "Multiple headers";
        case 102: return "Incorrect header";
        case 103: return "Malformed header";
        case 104: return "Unknown error in header";

        case 200: return "No footer";
        case 201: return "Multiple footers";
        case 202: return "Incorrect footer";
        case 203: return "Malformed footer";
        case 204: return "Unknown error in footer";

        case 300: return "Wrong line order";
        case 301: return "Wrong indexes";
        case 302: return "Wrong field count";
        case 303: return "Unknown error in a line";

        case 400: return "File error";
        case 500: return "bad_alloc";
    }
    return "Unknown error";
}
