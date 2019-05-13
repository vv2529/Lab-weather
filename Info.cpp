// Shymanovych Vladyslav
#include "Info.h"

Date& Info::load(int year, int month, int day) {
    std::cout << ">>> Info.load: ";

    auto _findDate = [=](const Date& date) -> bool {
        return date.getYear() == year &&
            date.getMonth() == month &&
            date.getDay() == day;
    };
    Date* date = dates.find(_findDate);
    if (date) {
        std::cout << "Duplicate: " << std::string(*date);
        return *date;
    }
    else {
        Date* date = new Date(year, month, day);
        dates.push(date);
        std::cout << std::string(*date);
        return *date;
    }
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
    // std::cout << ">>> Info.load (+details): ";
    load(year, month, day)
        .load(dayTempAvg, dayTempMin, humidity, downfall, stationCode, dayTempMax, wind);
    std::cout << "size: " << std::to_string(dates.size()) << "\n";
    std::cout << std::string(dates.top().stations.top());
}

void Info::setMaxDownfall(int value) noexcept { maxDownfall = value; }
int Info::getMaxDownfall() const noexcept { return maxDownfall; }
size_t Info::getDateCount() const noexcept { return dates.size(); }
