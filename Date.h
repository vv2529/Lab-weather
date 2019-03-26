// Shymanovych Vladyslav
#pragma once
#include <cmath>
#include <string>
#include <regex>
#include <iostream>

class Date {
#ifdef DEBUG
friend class TestStation;
#endif // DEBUG
public:
    Date() = default;
    Date(int year, double month, double day);
    void load(
        double dayTempAvg,
        double dayTempMin,
        double humidity,
        int downfall,
        std::string stationCode,
        double dayTempMax,
        double wind
    );
    int getYear() const noexcept;
    double getMonth() const noexcept;
    double getDay() const noexcept;
    double gethumidityMin() const noexcept;
    double gethumidityMax() const noexcept;
    double getdownfallAvg() const noexcept;
    bool operator == (const Date&) const noexcept;
    bool operator != (const Date&) const noexcept;
    bool operator < (const Date&) const noexcept;
    bool operator <= (const Date&) const noexcept;
    bool operator > (const Date&) const noexcept;
    bool operator >= (const Date&) const noexcept;
    operator std::string();
private:
    int year;
    double month, day;
    // aggregated data
    double
        humidityMin = 0,
        humidityMax = 0,
        downfallAvg = 0;

        static bool isValidYear(int);

    class Station {
    public:
        Station() = default;
        Station(
            double dayTempAvg,
            double dayTempMin,
            double humidity,
            int downfall,
            std::string stationCode,
            double dayTempMax,
            double wind
        );
        std::string getStationCode() const noexcept;
        int getDownfall() const noexcept;
        double getDayTempMin() const noexcept;
        double getDayTempMax() const noexcept;
        double getDayTempAvg() const noexcept;
        double getHumidity() const noexcept;
        double getWind() const noexcept;
        bool operator == (const Station&) const noexcept;
        bool operator != (const Station&) const noexcept;
        bool operator < (const Station&) const noexcept;
        bool operator <= (const Station&) const noexcept;
        bool operator > (const Station&) const noexcept;
        bool operator >= (const Station&) const noexcept;
        operator std::string();
    private:
        std::string stationCode;
        int downfall;
        double
            dayTempMin,
            dayTempMax,
            dayTempAvg,
            humidity,
            wind;

            static bool isValidStationCode(std::string);
            void normalize() noexcept;
    };

    class StationContainer {
    } stations;
};

void roundDouble(double&, int);
