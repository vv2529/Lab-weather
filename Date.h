// Shymanovych Vladyslav
#pragma once
#include "Container.h"
#include "Station.h"
#include <string>
#include <iostream>

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
    bool operator == (const Date&) const noexcept;
    bool operator != (const Date&) const noexcept;
    bool operator < (const Date&) const noexcept;
    bool operator <= (const Date&) const noexcept;
    bool operator > (const Date&) const noexcept;
    bool operator >= (const Date&) const noexcept;
    operator std::string() const;

    Container<Station> stations;
private:
    int year, month, day;
    // aggregated data
    double
        humidityMin = 0,
        humidityMax = 0,
        downfallAvg = 0;

    static bool isValidYear(int); // 4 digits
    static bool isValidMonth(int); // 1 <= month <= 12
    static bool isValidDay(int); // 1 <= day <= 31

    void updateData() noexcept;
};
