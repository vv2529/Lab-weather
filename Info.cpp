// Shymanovych Vladyslav
#include "Info.h"

Date& Info::load(int year, int month, int day) {
    auto _findDate = [=](const Date& date) -> bool {
        return date.getYear() == year &&
            date.getMonth() == month &&
            date.getDay() == day;
    };
    Date* date = dates.find(_findDate);
    if (date) {
        return *date;
    }
    else {
        Date* date = new Date(year, month, day);
        dates.push(date);
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
    const std::string stationCode,
    double dayTempMax,
    double wind
) {
    load(year, month, day)
        .load(dayTempAvg, dayTempMin, humidity, downfall, stationCode, dayTempMax, wind);
}

void Info::prepareData() {
    dates.sort();
    iterate([&] (Date& date) {
        date.prepareData();
    });
}

void Info::iterate(Container<Date>::FIteration f) {
    dates.iterate(f);
}

void Info::setMaxDownfall(int value) noexcept { maxDownfall = value; }
int Info::getMaxDownfall() const noexcept { return maxDownfall; }
size_t Info::getDateCount() const noexcept { return dates.size(); }
