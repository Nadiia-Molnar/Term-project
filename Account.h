#pragma once
#ifndef _ACCOUNT_
#define _ACCOUNT_
#include "Customer.h"

class Account {
    int ID;
    double balance;
    static int withdrawalCounter, depositsCounter;
    Customer * accountCustomer;
public:
    Account();
    Account(int, double, Customer * );
};

#endif // !_ACCOUNT_

