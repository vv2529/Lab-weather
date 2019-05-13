// Shymanovych Vladyslav
#pragma once
#include <string>
#include <unordered_map>

class Error : public std::exception {
using Tmap = std::unordered_map<int, std::string>;
public:
    Error(const char* filename, int line, int code, const char* msg="");
    const char* what() const noexcept;
    operator std::string () const;
private:
    const char* filename;
    int line, code;
    std::string _what;
    static Tmap desc;
};
