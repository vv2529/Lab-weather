// Shymanovych Vladyslav
#pragma once
#include <cmath>
#include <string>
#include <regex>
#include <iostream>

class Station {
public:
    Station() = default;
    Station(
        double dayTempAvg,
        double dayTempMin,
        double humidity,
        int downfall,
        const std::string stationCode,
        double dayTempMax,
        double wind
    );
    const std::string& getStationCode() const noexcept;
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
    static void roundDouble(double&, int);
    operator std::string() const;
private:
    double dayTempAvg;
    double dayTempMin;
    double humidity;
    int downfall;
    const std::string stationCode;
    double dayTempMax;
    double wind;

    static bool isValidStationCode(const std::string&);
    void normalize() noexcept;
};
