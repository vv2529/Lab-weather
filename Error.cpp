// Shymanovych Vladyslav
#include "Error.h"

Error::Tmap Error::desc({
    { 100, "No header" },
    { 101, "Multiple headers" },
    { 102, "Incorrect header content" },
    { 103, "Incorrect number of fields in header" },
    { 104, "Unknown error in header" },
    { 200, "No footer" },
    { 201, "Multiple footers" },
    { 202, "Incorrect footer content" },
    { 203, "Incorrect number of fields in footer" },
    { 204, "Unknown error in footer" },
    { 300, "Wrong line order" },
    { 301, "Wrong indexes" },
    { 302, "Incorrect number of fields in a line" },
    { 303, "Unknown error in a line" },
    { 400, "File error" },
    { 500, "bad_alloc" }
});



Error::Error(const char* _filename, int _line, int _code):
    filename(_filename),
    line(_line),
    code(_code)
{
    _what = "ERROR " + std::to_string(code) + " (line " + std::to_string(line) + "): " + desc[code];
}
const char* Error::what() const noexcept {
    return _what.c_str();
}
Error::operator std::string () const {
    return _what;
}
