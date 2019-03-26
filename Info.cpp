// Shymanovych Vladyslav
#include "Info.h"

void Info::load(int year, double month, double day) {
    std::cout << ">>> Info.load: ";
    Date date(year, month, day);
    std::cout << std::string(date);
}
void Info::load(
    int year,
    double dayTempAvg,
    double dayTempMin,
    double humidity,
    double month,
    double day,
    int downfall,
    std::string stationCode,
    double dayTempMax,
    double wind
) {
    std::cout << ">>> Info.load (+details): ";
    Date date(year, month, day);
    std::cout << std::string(date);
    date.load(dayTempAvg, dayTempMin, humidity, downfall, stationCode, dayTempMax, wind);
}

int Info::getMaxDownfall() const noexcept { return maxDownfall; }
size_t Info::getDateCount() const noexcept { return dateCount; }
