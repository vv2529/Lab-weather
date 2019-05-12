// Shymanovych Vladyslav
#pragma once
#include "Container.h"
#include "Date.h"
#include <string>
#include <iostream>

class Info {
public:
    void load(int year, int month, int day);
    void load(
        int year,
        double dayTempAvg,
        double dayTempMin,
        double humidity,
        int month,
        int day,
        int downfall,
        const std::string& stationCode,
        double dayTempMax,
        double wind
    );
    void setMaxDownfall(int) noexcept;
    void setDateCount(size_t) noexcept;
    int getMaxDownfall() const noexcept;
    size_t getDateCount() const noexcept;
private:
    int maxDownfall = 0;
    size_t dateCount = 0;//dates.size()
    Container<Date> dates;
};
