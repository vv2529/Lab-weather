// Shymanovych Vladyslav
#include "Date.h"

int Date::getYear() const noexcept { return year; }
double Date::getMonth() const noexcept { return month; }
double Date::getDay() const noexcept { return day; }
double Date::gethumidityMin() const noexcept { return humidityMin; }
double Date::gethumidityMax() const noexcept { return humidityMax; }
double Date::getdownfallAvg() const noexcept { return downfallAvg; }

std::string Date::Station::getStationCode() const noexcept { return stationCode; }
int Date::Station::getDownfall() const noexcept { return downfall; }
double Date::Station::getDayTempMin() const noexcept { return dayTempMin; }
double Date::Station::getDayTempMax() const noexcept { return dayTempMax; }
double Date::Station::getDayTempAvg() const noexcept { return dayTempAvg; }
double Date::Station::getHumidity() const noexcept { return humidity; }
double Date::Station::getWind() const noexcept { return wind; }
