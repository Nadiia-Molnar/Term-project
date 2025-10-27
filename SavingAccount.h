#pragma once
#ifndef _SAVINGACCOUNT_
#define _SAVINGACCOUNT_
#include "Account.h"

class SavingAccount:public Account{
    double interestRate;
public:
    void setInterestRate(double);
    void setAll(int, double, Customer *, double);
    
    double getInterestRate() const;
    
    SavingAccount();
    SavingAccount(int, double, Customer *, double);
    
    
};


#endif // !_SAVINGACCOUNT_
