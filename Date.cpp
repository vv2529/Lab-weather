// Shymanovych Vladyslav
#include "Date.h"

Date::Date(int _year, int _month, int _day):
    year(_year),
    month(_month),
    day(_day)
{
    if (!Date::isValidYear(year)) throw std::invalid_argument(std::to_string(year) + " is an invalid year");
}

void Date::load(
    double dayTempAvg,
    double dayTempMin,
    double humidity,
    int downfall,
    const std::string& stationCode,
    double dayTempMax,
    double wind
) {
    std::cout << ">>> Date.load: ";
    Station station(dayTempAvg, dayTempMin, humidity, downfall, stationCode, dayTempMax, wind);
    std::cout << std::string(station);
}

bool Date::isValidYear(int year) {
    return (year >= 1000) && (year <= 9999);
}

int Date::getYear() const noexcept { return year; }
int Date::getMonth() const noexcept { return month; }
int Date::getDay() const noexcept { return day; }
double Date::gethumidityMin() const noexcept { return humidityMin; }
double Date::gethumidityMax() const noexcept { return humidityMax; }
double Date::getdownfallAvg() const noexcept { return downfallAvg; }

bool Date::operator == (const Date& other) const noexcept {
    return month == other.getMonth()
        && downfallAvg == other.getdownfallAvg()
        && year == other.getYear()
        && day == other.getDay();
}
bool Date::operator != (const Date& other) const noexcept {
    return !(*this == other);
}
bool Date::operator < (const Date& other) const noexcept {
    return month < other.getMonth()
        || (month == other.getMonth() && downfallAvg < other.getdownfallAvg())
        || (month == other.getMonth() && downfallAvg == other.getdownfallAvg() && year < other.getYear())
        || (month == other.getMonth() && downfallAvg == other.getdownfallAvg() && year == other.getYear() && day < other.getDay());
}
bool Date::operator <= (const Date& other) const noexcept {
    return (*this < other) || (*this == other);
}
bool Date::operator > (const Date& other) const noexcept {
    return !(*this <= other);
}
bool Date::operator >= (const Date& other) const noexcept {
    return !(*this < other);
}
Date::operator std::string () const {
    return "Date: " + std::to_string(year)
        + "/" + std::to_string(month)
        + "/" + std::to_string(day)
        + "\n";
}
