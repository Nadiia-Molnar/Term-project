#include "Customer.h"

Customer::Customer(){
    fName = "";
    lName = "";
    address = "";
    phone = "";
    email = "";
}

Customer::Customer(string _fName, string _lName, string _address, string _phone, string _email){
    fName = _fName;
    lName = _lName;
    address = _address;
    phone = _phone;
    email = _email;
}

void Customer::setFname(string _fName){
    fName = _fName;
}
void Customer::setLname(string _lName){
    lName = _lName;
}
void Customer::setAddress(string _address){
    address = _address;
}
void Customer::setPhone(string _phone){
    phone = _phone;
}
void Customer::setEmail(string _email){
    email = _email;
}
void Customer::setAll(string _fName, string _lName, string _address, string _phone, string _email){
    fName = _fName;
    lName = _lName;
    address = _address;
    phone = _phone;
    email = _email;
}

string Customer::getFname() const {
    return fName;
}
string Customer::getLname() const {
    return lName;
}
string Customer::getAddress() const {
    return address;
}
string Customer::getPhone() const {
    return phone;
}
string Customer::getEmail() const {
    return email;
}

void Customer::PrintInfo(){
    cout << setw(10) << left << "Customer: " << fName << " " << lName << setw(10) << left << endl;
    cout << setw(10) << left << "Address: " << address << endl;
    cout << setw(10) << left << "Phone: " << phone << endl;
    cout << setw(10) << left << "Email: " << email << endl;
}
