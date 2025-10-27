#include "CheckingAccount.h"

CheckingAccount::CheckingAccount():Account(0, 0.0, 0){
    overDraftLimit = 0.0;
}
CheckingAccount::CheckingAccount(int _id, double _balance, Customer * _accountCustomer, double _overDraftLimit):Account(_id, _balance, _accountCustomer){
    if(_overDraftLimit > 0.0)
        overDraftLimit = _overDraftLimit;
    else
        overDraftLimit = 0.0;
}

void CheckingAccount::setOverDraftLimit(double _overDraftLimit){
    if(_overDraftLimit > 0.0)
        overDraftLimit = _overDraftLimit;
    else
        overDraftLimit = 0.0;
}
void CheckingAccount::setAll(int _id, double _balance, Customer * _accountCustomer, double _overDraftLimit){
    Account::setAll(_id, _balance, _accountCustomer);
    setOverDraftLimit(_overDraftLimit);
}

double CheckingAccount::getOverDraftLimit() const {
    return overDraftLimit;
}

void CheckingAccount::WithdrawMoney(double _amount){
    if (_amount < 0.0){
        cout << "Error: Amount must be positive." << endl;
        return;
    }
    
    if (_amount < getBalance()){
        double newBalance;
        newBalance = getBalance() - _amount;
        setBalance(newBalance);
        
        int counter;
        counter = getWithdrawalCounter() + 1;
        setWithdrawalCounter(counter);
        cout << "Withdrawal successful. New balance: " << getBalance() << endl;
    }
    
    if (_amount > getBalance()){
        double shortfall = _amount - getBalance();
        if (shortfall <= overDraftLimit){
            double newBalance = getBalance() - _amount;
            setBalance(newBalance);
            overDraftLimit = overDraftLimit - _amount;
            int counter;
            counter = getWithdrawalCounter() + 1;
            setWithdrawalCounter(counter);
            cout << "Withdrawal successful. New balance: " << getBalance() << endl;
        }
        else{
            cout << "Error: Insufficient funds." << endl;
            return;
        }
    }
}
