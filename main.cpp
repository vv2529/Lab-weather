// variant 96
// Shymanovych Vladyslav
#include <iostream>
#include <fstream>
#include <cstring>
#include "copyright.h"
#include "Info.h"
#include "Builder.h"
#include "Date.h"
#include "Station.h"
#include "Lexer.h"

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
    builder.loadData(&info, fname);
    cout << "OK\n";
}
bool output(Info& info, const char* fname) {
    ostream *f;
    if (strcmp(fname, "#con") == 0) f = &cout;
    else {
        ofstream f2(fname);
        f = &f2;
        //(*f).open(fname)
    }
    if (!*f) return false;
    const string del = "\t"s + Lexer::delimiters[0] + "\t"s;
    size_t record = 0;

    auto _output = [&] (const Date& date) {
        date.iterate([&] (const Station& station) {
            *f << ++record <<del<<
                date.getYear() <<del<<
                station.getDayTempAvg() <<del<<
                station.getDayTempMin() <<del<<
                station.getHumidity() <<del<<
                date.getMonth() <<del<<
                date.getDay() <<del<<
                station.getDownfall() <<del<<
                station.getStationCode() <<del<<
                station.getDayTempMax() <<del<<
                station.getWind() << '\n';
        });
    };

    info.iterate(_output);
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
            bool res = handleCommand(cmd, arg, info);
            if (strcmp(arg, "#con") != 0) {
                cout << (res ? "OK" : "UPS");
            }
        }
    }
    else {
        cout << ": ignored";
    }
    cout << "\n";
}

int main(int argc, char **argv) {
    copyright();
    task();
    help();
    try {
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
        cout << error.what() << "\n";
    }

    return 0;
}
