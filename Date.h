// Shymanovych Vladyslav
#pragma once
#include <string>
#include <iostream>

class Date {
public:
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
private:
    int year;
    double month, day;
    // aggregated data
    double
        humidityMin,
        humidityMax,
        downfallAvg;

    class Station {
    public:
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
    private:
        std::string stationCode;
        int downfall;
        double
            dayTempMin,
            dayTempMax,
            dayTempAvg,
            humidity,
            wind;
    };

    class StationContainer {
    } stations;
};
