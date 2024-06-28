#pragma once
#include "Employee.h"

class Driver : public Employee {

private:
    string driverLicense, model;

public:
    Driver(string username, string email, string password, string driverLicense, string model)
        : Employee(username, email, password, "Driver"), driverLicense(driverLicense), model(model) {}
    ~Driver() {}

    // Setters and Getters
    void setName(string _name) { username = _name; }
    string getName() { return username; }

    void setDriverLicense(string _driverLicense) { driverLicense = _driverLicense; }
    string getDriverLicense() { return driverLicense; }

    void setModel(string _model) { model = _model; }
    string getModel() { return model; }

    string getEmail() { return email; }

    void showAdditionalInfo() override {
        cout << "Licencia de conducir: " << driverLicense << endl;
        cout << "Modelo de auto: " << model << endl;
    }
};