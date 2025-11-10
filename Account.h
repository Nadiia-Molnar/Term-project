#pragma once
#ifndef _ACCOUNT_
#define _ACCOUNT_
#include "Customer.h"

class Account {
    int withdrawalCounter, depositsCounter;
    Customer * accountCustomer;
protected:
    int ID;
    double balance;
public:
    Account();
    Account(int, double, Customer *);
    
    void setID (int);
    void setBalance(double);
    void setAccountCustomer(Customer *);
    void setWithdrawalCounter(int);
    void setDepositCounter(int);
    void setAll(int, double, Customer *);

    int getID() const;
    double getBalance() const;
    Customer * getAccountCustomer() const;
    int getWithdrawalCounter() const;
    int getDepositsCounter() const;
    
    void DepositMoney(const double &);
    virtual void WithdrawMoney(const double &);
    virtual void PrintInfo() const;
};

#endif // !_ACCOUNT_

