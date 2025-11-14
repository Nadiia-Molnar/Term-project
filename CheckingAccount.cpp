#include "CheckingAccount.h"

// Default constructor
CheckingAccount::CheckingAccount():Account(0, 0.0, nullptr, nullptr){
    overDraftLimit = 0.0;
}
// Parameterized constructor
CheckingAccount::CheckingAccount(int _id, double _balance, Customer * _accountCustomer1, Customer * _accountCustomer2, double _overDraftLimit):Account(_id, _balance, _accountCustomer1, _accountCustomer2){
    setOverDraftLimit(_overDraftLimit);
}
// Setter
void CheckingAccount::setOverDraftLimit(double _overDraftLimit){
    if(_overDraftLimit > 0.0)
        overDraftLimit = _overDraftLimit;
    else
        overDraftLimit = 0.0;
}
// Set all attributes at once
void CheckingAccount::setAll(int _id, double _balance, Customer * _accountCustomer1, Customer * _accountCustomer2, double _overDraftLimit){
    Account::setAll(_id, _balance, _accountCustomer1, _accountCustomer2);
    setOverDraftLimit(_overDraftLimit);
}
// Getter
double CheckingAccount::getOverDraftLimit() const {
    return overDraftLimit;
}
// Withdraw money function
void CheckingAccount::WithdrawMoney(const double & _amount) {
    if (_amount <= 0.0) {
        cout << "Error! Amount must be positive." << endl;
        return;
    }

    double newBalance = balance - _amount;
    
    // Check if the new balance is within the allowed overdraft
    if (newBalance >= -overDraftLimit){
        balance = newBalance;
        setWithdrawalCounter(getWithdrawalCounter() + 1);
        
        // Apply overdraft fee if the balance becomes negative
        if (balance < 0.0){
            balance = balance - 20.0;
            cout << "Withdrawal successful using overdraft. $20 fee applied." << endl;
        }
        else{
            cout << "Withdrawal successful." << endl;
        }
        cout << "New balance: $" << fixed << setprecision(2) << balance << endl;
        cout << "Overdraft limit: $" << fixed << setprecision(2) << overDraftLimit << endl;
    }
    else{
        cout << "Error! Withdrawal would exceed overdraft limit." << endl;
    }
}


    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    

