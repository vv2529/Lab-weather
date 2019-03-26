// Shymanovych Vladyslav
#include "Date.h"

Date::Date(int _year, double _month, double _day):
    year(_year),
    month(_month),
    day(_day)
{
    if (!Date::isValidYear(year)) throw invalid_argument(to_string(year) + " is an invalid year");
}

void Date::load(
    double dayTempAvg,
    double dayTempMin,
    double humidity,
    int downfall,
    std::string stationCode,
    double dayTempMax,
    double wind
) {
    cout << ">>> Date.load\n";
    Station station(dayTempAvg, dayTempMin, humidity, downfall, stationCode, dayTempMax, wind);
}

bool Date::isValidYear(int year) {
    return (year >= 1000) && (year <= 9999);
}

int Date::getYear() const noexcept { return year; }
double Date::getMonth() const noexcept { return month; }
double Date::getDay() const noexcept { return day; }
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
    return !(this == other);
}
bool Date::operator < (const Date& other) const noexcept {
    return month < other.getMonth()
        || downfallAvg < other.getdownfallAvg()
        || year < other.getYear()
        || day < other.getDay();
}
bool Date::operator <= (const Date& other) const noexcept {
    return (this < other) || (this == other);
}
bool Date::operator > (const Date& other) const noexcept {
    return !(this <= other);
}
bool Date::operator >= (const Date& other) const noexcept {
    return !(this < other);
}

Date::Station::Station(
    double _dayTempAvg,
    double _dayTempMin,
    double _humidity,
    int _downfall,
    std::string _stationCode,
    double _dayTempMax,
    double _wind
):
    dayTempAvg(_dayTempAvg),
    dayTempMin(_dayTempMin),
    humidity(_humidity),
    downfall(_downfall),
    stationCode(_stationCode),
    dayTempMax(_dayTempMax),
    wind(_wind)
{
    if (!Date::Station::isValidStationCode(stationCode)) throw invalid_argument(stationCode + " is an invalid station code");
    normalize();
}

bool Date::Station::isValidStationCode(std::string code) {
    return std::regex_match(code, std::regex("\\d{3,11}"));
}
void Date::Station::normalize() noexcept {
    roundDouble(dayTempAvg, 1);
    roundDouble(dayTempMin, 1);
    roundDouble(dayTempMax, 1);
    roundDouble(humidity, 1);
    roundDouble(wind, 1);
}

std::string Date::Station::getStationCode() const noexcept { return stationCode; }
int Date::Station::getDownfall() const noexcept { return downfall; }
double Date::Station::getDayTempMin() const noexcept { return dayTempMin; }
double Date::Station::getDayTempMax() const noexcept { return dayTempMax; }
double Date::Station::getDayTempAvg() const noexcept { return dayTempAvg; }
double Date::Station::getHumidity() const noexcept { return humidity; }
double Date::Station::getWind() const noexcept { return wind; }

bool Date::Station::operator == (const Station& other) const noexcept {
    return humidity == other.humidity
        || stationCode == other.stationCode;
}
bool Date::Station::operator != (const Station& other) const noexcept {
    return !(this == other);
}
bool Date::Station::operator < (const Station& other) const noexcept {
    return humidity < other.humidity
        || stationCode < other.stationCode;
}
bool Date::Station::operator <= (const Station& other) const noexcept {
    return (this < other) || (this == other);
}
bool Date::Station::operator > (const Station& other) const noexcept {
    return !(this <= other);
}
bool Date::Station::operator >= (const Station& other) const noexcept {
    return !(this < other);
}

void roundDouble(double& d, int n) {
    d *= pow(10, n);
    d = double(int(d));
    d *= pow(.1, n);
}
