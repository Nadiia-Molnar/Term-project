#pragma once
#ifndef _ACCOUNT_
#define _ACCOUNT_
#include "Customer.h"

class Account {
    int withdrawalCounter, depositsCounter;
    Customer * accountCustomer1;
    Customer * accountCustomer2;
protected:
    int ID;
    double balance;
public:
    Account();
    Account(int, double, Customer *, Customer *);
    
    void setID (int);
    void setBalance(double);
    void setAccountCustomer1(Customer *);
    void setAccountCustomer2(Customer *);
    void setWithdrawalCounter(int);
    void setDepositCounter(int);
    void setAll(int, double, Customer *, Customer *);

    int getID() const;
    double getBalance() const;
    Customer * getAccountCustomer1() const;
    Customer * getAccountCustomer2() const;
    int getWithdrawalCounter() const;
    int getDepositsCounter() const;
    
    void DepositMoney(const double &);
    virtual void WithdrawMoney(const double &);
    virtual void PrintInfo() const;
};

#endif // !_ACCOUNT_

