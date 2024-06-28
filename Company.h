#pragma once
#include "Customer.h"

class Company : public Customer {

private:
    string ruc;

public:
    Company(string username, string email, string password, string ruc) : Customer(username, email, password, "Company"), ruc(ruc) {}
    ~Company() {}

    //Setter and Getter
    void setRuc(string _ruc) { ruc = _ruc; }
    string getRuc() { return ruc; }

    void showAdditionalInfo() override {
        cout << "RUC: " << ruc << endl;
    }

};