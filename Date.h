// Shymanovych Vladyslav
#pragma once
#include "Container.h"
#include "Station.h"
#include <string>

class Date {
public:
    Date() = default;
    Date(int year, int month, int day);
    void load(
        double dayTempAvg,
        double dayTempMin,
        double humidity,
        int downfall,
        const std::string& stationCode,
        double dayTempMax,
        double wind
    );
    int getYear() const noexcept;
    int getMonth() const noexcept;
    int getDay() const noexcept;
    double gethumidityMin() const noexcept;
    double gethumidityMax() const noexcept;
    double getdownfallAvg() const noexcept;
    double getdayTempMaxAvg() const noexcept;
    bool operator == (const Date&) const noexcept;
    bool operator != (const Date&) const noexcept;
    bool operator < (const Date&) const noexcept;
    bool operator <= (const Date&) const noexcept;
    bool operator > (const Date&) const noexcept;
    bool operator >= (const Date&) const noexcept;
    operator std::string() const;
    void prepareData();
    void iterate(Container<Station>::FIteration f);
private:
    int year, month, day;
    // aggregated data
    double
        humidityMin = 0,
        humidityMax = 0,
        downfallAvg = 0,
        dayTempMaxAvg = 0;

    static bool isValidYear(int); // 4 digits
    static bool isValidMonth(int); // 1 <= month <= 12
    static bool isValidDay(int); // 1 <= day <= 31

    Container<Station> stations;

    void updateData() noexcept;
};
