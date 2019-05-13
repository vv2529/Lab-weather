// Shymanovych Vladyslav
#include "Date.h"

Date::Date(int _year, int _month, int _day):
    year(_year),
    month(_month),
    day(_day)
{
    if (!Date::isValidYear(year) || !Date::isValidMonth(month) || !Date::isValidDay(day))
        throw std::invalid_argument("Invalid date: " + std::to_string(day) + '.' + std::to_string(month) + '.' + std::to_string(year));
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
    Station* station = new Station(dayTempAvg, dayTempMin, humidity, downfall, stationCode, dayTempMax, wind);
    std::cout << std::string(*station) << "\n";
    stations.push(station);
    std::cout << "size: " << std::to_string(stations.size()) << "\n";
    updateData();
}

bool Date::isValidYear(int year) {
    return (year >= 1000) && (year <= 9999);
}
bool Date::isValidMonth(int month) {
    return (month >= 1) && (month <= 12);
}
bool Date::isValidDay(int day) {
    return (day >= 1) && (day <= 31);
}

void Date::updateData() noexcept {
    if (stations.size() == 1) {
        humidityMin = humidityMax = stations.top().getHumidity();
        downfallAvg = stations.top().getDownfall();
    } else if (stations.size() > 1) {
        if (humidityMin > stations.top().getHumidity())
            humidityMin = stations.top().getHumidity();
        else if (humidityMax < stations.top().getHumidity())
            humidityMax = stations.top().getHumidity();
        downfallAvg = (downfallAvg * (stations.size() - 1) + stations.top().getDownfall()) / stations.size();
        // Station::roundDouble(downfallAvg, 1);
    }
    std::cout << "Aggregated (size=" << std::to_string(stations.size()) << "): " << std::to_string(humidityMin)
        << " | " << std::to_string(humidityMax)
        << " | " << std::to_string(getdownfallAvg());
}

int Date::getYear() const noexcept { return year; }
int Date::getMonth() const noexcept { return month; }
int Date::getDay() const noexcept { return day; }
double Date::gethumidityMin() const noexcept { return humidityMin; }
double Date::gethumidityMax() const noexcept { return humidityMax; }
double Date::getdownfallAvg() const noexcept {
    double d = downfallAvg;
    Station::roundDouble(d, 1);
    return d;
}

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
        + "/" + std::to_string(day);
}
