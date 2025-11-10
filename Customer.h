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
    Customer(const string&, const string&, const string&, const string&, const string&);
    
    void setFname(const string&);
    void setLname(const string&);
    void setAddress(const string&);
    void setPhone (const string&);
    void setEmail(const string&);
    void setAll(const string&, const string&, const string&, const string&, const string&);
    
    string getFname() const;
    string getLname() const;
    string getAddress() const;
    string getPhone() const;
    string getEmail() const;
    
    virtual void PrintInfo() const;
};



#endif // !_CUSTOMER_
