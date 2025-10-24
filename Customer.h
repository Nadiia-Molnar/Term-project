#pragma once
#ifndef _CUSTOMER_
#define _CUSTOMER_
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

class Customer {
    string fName, lName, address, phone, email;
public:
    Customer();
    Customer(string, string, string, string, string);
    
    void setFname(string);
    void setLname(string);
    void setAddress(string);
    void setPhone (string);
    void setEmail(string);
    void setAll(string, string, string, string, string);
    
    string getFname() const;
    string getLname() const;
    string getAddress() const;
    string getPhone() const;
    string getEmail() const;
    
    void PrintInfo();
};



#endif // !_CUSTOMER_
