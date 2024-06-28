#pragma once
#include <iostream>
#include <chrono>
#include <ctime>
using namespace std;
using namespace std::chrono;

class Register {
private:
    tm timeStruct;

public:
    Register() {
        updateDateTime();
    }

    void updateDateTime() {
        auto now = system_clock::now();
        time_t now_time = system_clock::to_time_t(now);
        localtime_s(&timeStruct, &now_time);
    }

    void printDate() const {
        cout << timeStruct.tm_mday << '-'
            << (timeStruct.tm_mon + 1) << '-'
            << (timeStruct.tm_year + 1900);
    }

    void printHour() const {
        cout << "Hora registrada: " << timeStruct.tm_hour << ':'
            << timeStruct.tm_min << ':'
            << timeStruct.tm_sec << endl;
    }

};
