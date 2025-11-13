#include "Customer.h"

// Default constructor
Customer::Customer(){
    fName = "";
    lName = "";
    address = "";
    phone = "";
    email = "";
}
// Parameterized constructor
Customer::Customer(const string & _fName, const string & _lName, const string & _address, const string & _phone, const string & _email){
    fName = _fName;
    lName = _lName;
    address = _address;
    phone = _phone;
    email = _email;
}
// Setters
void Customer::setFname(const string & _fName){
    fName = _fName;
}
void Customer::setLname(const string & _lName){
    lName = _lName;
}
void Customer::setAddress(const string & _address){
    address = _address;
}
void Customer::setPhone(const string & _phone){
    phone = _phone;
}
void Customer::setEmail(const string & _email){
    email = _email;
}
// Sets all attributes at once
void Customer::setAll(const string & _fName, const string & _lName, const string & _address, const string & _phone, const string & _email){
    setFname(_fName);
    setLname(_lName);
    setAddress(_address);
    setPhone(_phone);
    setEmail(_email);
}
// Getters 
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
// Prints all customer information
void Customer::PrintInfo() const {
    if(fName != ""){
        cout << setw(15) << left << "Customer: " << fName << " " << lName << endl;
        cout << setw(15) << left << "Address: " << address << endl;
        cout << setw(15) << left << "Phone: " << phone << endl;
        cout << setw(15) << left << "Email: " << email << endl;
    }
}
