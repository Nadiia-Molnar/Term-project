#include "SavingAccount.h"

void SavingAccount::setInterestRate(double _interestRate){
    if (_interestRate > 0)
        interestRate = _interestRate;
}
void SavingAccount::setAll(int _id, double _balance, Customer * _accountCustomer, double _interestRate){
    Account::setAll(_id, _balance, _accountCustomer);
    setInterestRate(_interestRate);
}

double SavingAccount::getInterestRate() const{
    return interestRate;
}

SavingAccount::SavingAccount():Account(){
    interestRate = 0.0;
}

SavingAccount::SavingAccount(int _id, double _balance, Customer * _accountCustomer, double _interestRate):Account(_id, _balance, _accountCustomer){
    if (_interestRate > 0)
        interestRate = _interestRate;
}
