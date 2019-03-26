// variant 96
// Shymanovych Vladyslav
#include <iostream>
#include <cstring>
#include "copyright.h"
#include "Info.h"
#include "Builder.h"

using namespace std;

void task() {
    cout << "This program reads, analyzes and outputs weather data.\n";
}
void help() {
    cout << "Run this program with arguments:\n> lab.exe <input_file> [-output|-stat <output_file>]*\n\n";
}

void doNothing() {
    cout << "nothing to do\n";
}

void input(Info& info, const char* fname) {
    cout << "input " << fname << " : ";
    Builder builder;
    builder.loadData(info, fname);
    cout << "OK\n";
}
bool output(const Info& info, const char* fname) {
    return true;
}
bool stat(const Info& info, const char* fname) {
    return true;
}

bool isAllowedCommand(const char* cmd) {
    return !(
        strcmp(cmd, "-output")
        && strcmp(cmd, "-stat")
    );
}
bool handleCommand(const char* cmd, const char* arg, Info& info) {
    if (!strcmp(cmd, "-output")) {
        return output(info, arg);
    }
    else if (!strcmp(cmd, "-stat")) {
        return stat(info, arg);
    }
    else return false;
}

void doCommand(int& cur, int argc, char** argv, Info& info) {
    char* cmd = argv[cur];
    char* cmdForOutput = cmd;
    strcpy(cmdForOutput, cmd);
    if (*cmd == '-') ++cmdForOutput;
    cout << cmdForOutput << " ";

    if (isAllowedCommand(cmd)) {
        ++cur;
        if (cur >= argc) {
            cout << "undefined";
        }
        else {
            const char* arg = argv[cur];
            cout << arg << " : ";
            if (strcmp(arg, "#con") != 0) {
                bool res = handleCommand(cmd, arg, info);
                cout << (res ? "OK" : "UPS");
            }
        }
    }
    else {
        cout << ": ignored";
    }
    cout << "\n";
}

class TestStation {
public:
    TestStation() {
        ok();
        trunc();
        badCode1();
        badCode2();
        badCode3();
        compare();
    }
    void ok() {
        cout << "1: ";
        Date::Station s(2.1, 0.5, 18.4, 50, string("2226"), 2.9, 13.8);
        process(s, 2.1, 0.5, 18.4, 50, string("2226"), 2.9, 13.8);
    }
    void trunc() {
        cout << "2: ";
        Date::Station s(2.12, 0.555, 18.4987, 50.9, string("2226"), 2.99999999999999, 13.85);
        process(s, 2.1, 0.5, 18.4, 50, string("2226"), 2.9, 13.8);
    }
    void badCode1() {
        cout << "3: ";
        try {
            Date::Station(2.1, 0.5, 18.4, 50, string("22"), 2.9, 13.8);
            cout << "NO\n";
        } catch(...) { cout << "OK\n"; }
    }
    void badCode2() {
        cout << "4: ";
        try {
            Date::Station(2.1, 0.5, 18.4, 50, string("222622262226"), 2.9, 13.8);
            cout << "NO\n";
        } catch(...) { cout << "OK\n"; }
    }
    void badCode3() {
        cout << "5: ";
        try {
            Date::Station(2.1, 0.5, 18.4, 50, string("22o22"), 2.9, 13.8);
            cout << "NO\n";
        } catch(...) { cout << "OK\n"; }
    }
    void compare() {
        cout << "6: ";
        Date::Station s1(2.1, 0.5, 18.4, 50, string("2226"), 2.9, 13.8),
            s2(2.12, 0.555, 18.4987, 50.9, string("2226"), 2.99999999999999, 13.85),
            s3(22.1, 10.5, 18.4, 500, string("2226"), 22.9, 113.8),
            s4(22.1, 10.5, 118.4, 500, string("12226"), 22.9, 113.8);
        bool OK = (s1 == s2)
            && (s1 == s3)
            && (s1 != s4)
            && (s1 <= s2)
            && (s1 >= s2)
            && (s3 < s4);
        cout << (OK ? "OK" : "NO") << "\n";
    }
    void process(
        Date::Station s,
        double dayTempAvg,
        double dayTempMin,
        double humidity,
        int downfall,
        string stationCode,
        double dayTempMax,
        double wind
    ) {
        roundDouble(dayTempAvg, 1);
        roundDouble(dayTempMin, 1);
        roundDouble(dayTempMax, 1);
        roundDouble(humidity, 1);
        roundDouble(wind, 1);
        bool OK = (s.getDayTempAvg() == dayTempAvg)
            && (s.getDayTempMin() == dayTempMin)
            && (s.getHumidity() == humidity)
            && (s.getDownfall() == downfall)
            && (s.getStationCode() == stationCode)
            && (s.getDayTempMax() == dayTempMax)
            && (s.getWind() == wind);
        cout << (OK ? "OK" : "NO") << "\n";
    }
};
class TestDate {
public:
    TestDate() {
        ok();
        badYear();
        load();
        compare();
    }
    void ok() {
        cout << "1: ";
        Date d(2019, 3, 16.5);
        process(d, 2019, 3, 16.5);
    }
    void badYear() {
        cout << "2: ";
        try {
            Date d(20190, 3, 16);
            cout << "NO\n";
        } catch(...) { cout << "OK\n"; }
    }
    void load() {
        cout << "3: ";
        Date d(2019, 3, 16);
        d.load(2.1, 0.5, 18.4, 50, string("2226"), 2.9, 13.8);
    }
    void compare() {
        cout << "4: ";
        Date d1(2019, 3, 16),
            d2(2019, 3, 16),
            d3(2019, 2, 17);
        bool OK = (d1 == d2)
            && (d1 <= d2)
            && (d1 > d3);
        cout << (OK ? "OK" : "NO") << "\n";
    }
    void process(Date d, int year, double month, double day) {
        bool OK = (d.getYear() == year)
            && (d.getMonth() == month)
            && (d.getDay() == day);
        cout << (OK ? "OK" : "NO") << "\n";
    }
};
class TestInfo {
public:
    TestInfo() {
        load1();
        load2();
    }
    void load1() {
        cout << "1: ";
        Info info;
        info.load(2000, 8, 5);
    }
    void load2() {
        cout << "2: ";
        Info info;
        info.load(2000, 8, 5, 2.1, 0.5, 18.4, 50, string("2226"), 2.9, 13.8);
    }
};
int main(int argc, char **argv) {
    try {
    TestStation();
    cout << "-----\n";
    TestDate();
    cout << "-----\n";
    TestInfo();
    cout << "\n";

    copyright();
    task();
    help();
        Info info;
        cout << "*****\n";
        if (argc == 1) doNothing();
        else {
            input(info, argv[1]);
            int cur = 2;
            while (cur < argc) {
                doCommand(cur, argc, argv, info);
                ++cur;
            }
        }
        cout << "*****\n";
    } catch (const exception& error) {
        cout << "ERROR: " << error.what() << "\n";
    }

    return 0;
}
