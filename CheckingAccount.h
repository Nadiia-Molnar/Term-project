#pragma once
#ifndef _CHECKINGACCOUNT_
#define _CHECKINGACCOUNT_
#include "Account.h"

class CheckingAccount:public Account{
    double overDraftLimit;
public:
    CheckingAccount();
    CheckingAccount(int, double, Customer *, double);
    
    void setOverDraftLimit(double);
    void setAll(int, double, Customer *, double);
    
    double getOverDraftLimit() const;
    
    void WithdrawMoney(double);
};


#endif // !_CHECKINGACCOUNT_

