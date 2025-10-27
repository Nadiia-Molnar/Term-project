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
    
    void setID (int);
    void setBalance(double);
    void setAccountCustomer(Customer *);
    static void setWithdrawalCounter(int);
    static void setDepositCounter(int);
    void setAll(int, double, Customer *);

    
    int getID() const;
    double getBalance() const;
    Customer * getAccountCustomer() const;
    static int getWithdrawalCounter();
    static int getDepositsCounter();
    
    void DepositMoney(double &);
    virtual void WithdrawMoney(double &);
    void PrintInfo();
};

#endif // !_ACCOUNT_

