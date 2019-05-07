// Shymanovych Vladyslav
#include "Station.h"

Station::Station(
    double _dayTempAvg,
    double _dayTempMin,
    double _humidity,
    int _downfall,
    const std::string& _stationCode,
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
    if (!Station::isValidStationCode(stationCode)) throw std::invalid_argument(stationCode + " is an invalid station code");
    normalize();
}

bool Station::isValidStationCode(const std::string& code) {
    return std::regex_match(code, std::regex("\\d{3,11}"));
}
void Station::normalize() noexcept {
    roundDouble(dayTempAvg, 1);
    roundDouble(dayTempMin, 1);
    roundDouble(dayTempMax, 1);
    roundDouble(humidity, 1);
    roundDouble(wind, 1);
}

const std::string& Station::getStationCode() const noexcept { return stationCode; }
int Station::getDownfall() const noexcept { return downfall; }
double Station::getDayTempMin() const noexcept { return dayTempMin; }
double Station::getDayTempMax() const noexcept { return dayTempMax; }
double Station::getDayTempAvg() const noexcept { return dayTempAvg; }
double Station::getHumidity() const noexcept { return humidity; }
double Station::getWind() const noexcept { return wind; }

bool Station::operator == (const Station& other) const noexcept {
    return (humidity == other.humidity)
        && (stationCode == other.stationCode);
}
bool Station::operator != (const Station& other) const noexcept {
    return !(*this == other);
}
bool Station::operator < (const Station& other) const noexcept {
    return humidity < other.humidity
        || (humidity == other.humidity && stationCode < other.stationCode);
}
bool Station::operator <= (const Station& other) const noexcept {
    return (*this < other) || (*this == other);
}
bool Station::operator > (const Station& other) const noexcept {
    return !(*this <= other);
}
bool Station::operator >= (const Station& other) const noexcept {
    return !(*this < other);
}

Station::operator std::string () const {
    return "Station: " + std::to_string(dayTempAvg)
        + " | " + std::to_string(dayTempMin)
        + " | " + std::to_string(humidity)
        + " | " + std::to_string(downfall)
        + " | \"" + stationCode + "\""
        + " | " + std::to_string(dayTempMax)
        + " | " + std::to_string(wind)
        + "\n";
}

void roundDouble(double& d, int n) {
    int n2 = n;
    while (n2--) d *= 10;
    d = std::round(d);
    while (n--) d /= 10;
}
