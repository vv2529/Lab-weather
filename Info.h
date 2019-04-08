// Shymanovych Vladyslav
#pragma once
#include "DateContainer.h"
#include <string>
#include <iostream>

class Info {
public:
    void load(int year, double month, double day);
    void load(
        int year,
        double dayTempAvg,
        double dayTempMin,
        double humidity,
        double month,
        double day,
        int downfall,
        std::string stationCode,
        double dayTempMax,
        double wind
    );
    void setMaxDownfall(int) noexcept;
    void setDateCount(size_t) noexcept;
    int getMaxDownfall() const noexcept;
    size_t getDateCount() const noexcept;
private:
    int maxDownfall;
    size_t dateCount;
    DateContainer dates;
};
