// Shymanovych Vladyslav
#include "Info.h"

void Info::load(int year, int month, int day) {
    std::cout << ">>> Info.load: ";
    Date date(year, month, day);
    std::cout << std::string(date);
}
void Info::load(
    int year,
    double dayTempAvg,
    double dayTempMin,
    double humidity,
    int month,
    int day,
    int downfall,
    const std::string& stationCode,
    double dayTempMax,
    double wind
) {
    std::cout << ">>> Info.load (+details): ";
    Date date(year, month, day);
    std::cout << std::string(date);
    date.load(dayTempAvg, dayTempMin, humidity, downfall, stationCode, dayTempMax, wind);
}

void Info::setMaxDownfall(int value) noexcept { maxDownfall = value; }
void Info::setDateCount(size_t value) noexcept { dateCount = value; }
int Info::getMaxDownfall() const noexcept { return maxDownfall; }
size_t Info::getDateCount() const noexcept { return dateCount; }
