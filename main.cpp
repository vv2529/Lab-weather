// variant 96
// Shymanovych Vladyslav
#include <iostream>
#include "copyright.h"

using namespace std;

void task() {
    cout << "This program reads, analyzes and outputs weather data.\n";
}
void help() {
    cout << "Run this program with arguments:\n> lab.exe <input_file> [-output|-stat <output_file>]*\n\n";
}

int main() {
    copyright();
    task();
    help();

    return 0;
}
