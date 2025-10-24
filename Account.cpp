#include "Account.h"

int Account::withdrawalCounter = 0;
int Account::depositsCounter = 0;

Account::Account(){
    ID = 0;
    balance = 0.0;
//    * accountCustomer;
}
Account::Account(int _id, double _balance, Customer * _accountCustomer){
    ID = _id;
    double balance;
    static int withdrawalCounter, depositsCounter;
    Customer * accountCustomer;
}
