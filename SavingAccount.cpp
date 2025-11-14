#include "SavingAccount.h"

// Default constructor
SavingAccount::SavingAccount():Account(0, 0.0, nullptr, nullptr){
    interestRate = 0.0;
}
// Parameterized constructor
SavingAccount::SavingAccount(int _id, double _balance, Customer * _accountCustomer1, Customer * _accountCustomer2, double _interestRate):Account(_id, _balance, _accountCustomer1, _accountCustomer2){
    setInterestRate(_interestRate);
}
//Setter
void SavingAccount::setInterestRate(double _interestRate){
    if (_interestRate > 0)
        interestRate = _interestRate;
}
// Set all attributes
void SavingAccount::setAll(int _id, double _balance, Customer * _accountCustomer1, Customer * _accountCustomer2, double _interestRate){
    Account::setAll(_id, _balance, _accountCustomer1, _accountCustomer2);
    setInterestRate(_interestRate);
}
// Getter
double SavingAccount::getInterestRate() const{
    return interestRate;
}
// Function to apply interest to the saving account balance
void SavingAccount::payInterest(){
    // Check if interest rate is positive and balance is positive
    if(interestRate > 0 && balance > 0){
        double interest = balance * interestRate;
        balance += interest;
        
        cout << fixed << setprecision(2) << "Interest of $" << interest << " added. New balance: $" << balance << endl;
    }
    else{
        // If balance or interest rate is zero or negative
        cout << "No interest applied (balance or rate invalid)." << endl;
    }
}
// Transfers money from this SavingAccount to another SavingAccount
void SavingAccount::transfer(double _amount, SavingAccount * destinationAccount){
    // Check if destination account pointer is valid
    if (destinationAccount == nullptr){
        cout << "Error! Destination account is invalid." << endl;
        return;
    }
    // Invalid negative transfer
    if (_amount <= 0) {
            cout << "You cannot transfer a negative or zero value." << endl;
            return;
    }
    // Check if there is enough balance
    if (balance >= _amount){
        destinationAccount->setBalance(destinationAccount->getBalance()+_amount);
        balance -= _amount;
        cout << "Transfer was made successfully!" << endl;
        cout << fixed << setprecision(2) << "The current balance: $" << balance << "." << endl;
    }
    // Not enough money to transfer
    else{
        cout << "Insufficient funds for transfer." << endl;
        cout << fixed << setprecision(2) << "The current balance: $" << balance << "." << endl;
    }
}
