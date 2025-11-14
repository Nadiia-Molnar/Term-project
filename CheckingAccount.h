#pragma once
#ifndef _CHECKINGACCOUNT_
#define _CHECKINGACCOUNT_
#include "Account.h"

class CheckingAccount:public Account{
    double overDraftLimit;
public:
    CheckingAccount();
    CheckingAccount(int, double, Customer *, Customer *, double);
    
    void setOverDraftLimit(double);
    void setAll(int, double, Customer *, Customer *, double);
    
    double getOverDraftLimit() const;
    
    virtual void WithdrawMoney(const double&);
};


#endif // !_CHECKINGACCOUNT_

