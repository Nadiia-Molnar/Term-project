#pragma once
#ifndef _SAVINGACCOUNT_
#define _SAVINGACCOUNT_
#include "Account.h"

class SavingAccount:public Account{
    double interestRate;
public:
    SavingAccount();
    SavingAccount(int, double, Customer *, double);
    
    void setInterestRate(double);
    void setAll(int, double, Customer *, double);
    
    double getInterestRate() const;
    
    void payInterest();
    void transfer(double, SavingAccount *);
};


#endif // !_SAVINGACCOUNT_
