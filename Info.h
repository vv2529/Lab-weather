// Shymanovych Vladyslav
#pragma once
#include "Container.h"
#include "Date.h"
#include <string>

class Info {
public:
    Date& load(int year, int month, int day);
    void load(
        int year,
        double dayTempAvg,
        double dayTempMin,
        double humidity,
        int month,
        int day,
        int downfall,
        const std::string stationCode,
        double dayTempMax,
        double wind
    );
    void setMaxDownfall(int) noexcept;
    int getMaxDownfall() const noexcept;
    size_t getDateCount() const noexcept;
    void prepareData();
    void iterate(Container<Date>::FIteration f);
private:
    int maxDownfall = 0;
    Container<Date> dates;
};
