#include "Account.h"

// Default constructor
Account::Account(){
    ID = 0;
    balance = 0.0;
    accountCustomer1 = nullptr;
    accountCustomer2 = nullptr;
    withdrawalCounter = 0;
    depositsCounter = 0;
}
// Parameterized constructor
Account::Account(int _id, double _balance, Customer * _accountCustomer1, Customer * _accountCustomer2){
    setID(_id);
    setBalance(_balance);
    accountCustomer1 = _accountCustomer1;
    accountCustomer2 = _accountCustomer2;
    withdrawalCounter = 0;
    depositsCounter = 0;
}
//Setters
void Account::setID (int _id){
    if (_id > 0)
        ID = _id;
    else{
        ID = 0;
    }
}
void Account::setBalance(double _balance){
    if (_balance >= 0.0)
        balance = _balance;
    else{
        balance = 0.0;
    }
}
void Account::setAccountCustomer1(Customer * _accountCustomer1){
    accountCustomer1 = _accountCustomer1;
}
void Account::setAccountCustomer2(Customer * _accountCustomer2){
    accountCustomer2 = _accountCustomer2;
}
void Account::setWithdrawalCounter(int _withdrawalCounter) {
    if (_withdrawalCounter >= 0)
        withdrawalCounter = _withdrawalCounter;
}
void Account::setDepositCounter(int _depositCounter){
    if (_depositCounter >= 0)
        depositsCounter = _depositCounter;
}
// Sets all attributes at once
void Account::setAll(int _id, double _balance, Customer * _accountCustomer1, Customer * _accountCustomer2){
    setID(_id);
    setBalance(_balance);
    accountCustomer1 = _accountCustomer1;
    accountCustomer2 = _accountCustomer2;
    withdrawalCounter = 0;
    depositsCounter = 0;
}
// Getters
int Account::getID() const {
    return ID;
}
double Account::getBalance() const {
    return balance;
}
Customer * Account::getAccountCustomer1() const {
    return accountCustomer1;
}
Customer * Account::getAccountCustomer2() const {
    return accountCustomer2;
}
int Account::getWithdrawalCounter() const{
    return withdrawalCounter;
}
int Account::getDepositsCounter() const{
    return depositsCounter;
}
// Deposit Money Function
void Account::DepositMoney(const double & _amount){
    if (_amount > 0.0){
        balance = balance + _amount;
        depositsCounter++;
        cout << fixed << setprecision(2); 
        cout << "Deposit successful." << endl;
        cout << "New balance: $" << balance << endl;
    }
    else{
        cout << "Error! Deposit amount must be positive." << endl;
    }
}
// Withdraw Money Function
void Account::WithdrawMoney(const double & _amount) {
    if (_amount <= 0.0){
        cout << "Error! Amount must be positive." << endl;
        return;
    }
    else if (_amount > balance){
        cout << "Error! Insufficient funds." << endl;
        return;
    }
    else{
        balance = balance - _amount;
        withdrawalCounter++;
        cout << "Withdrawal successful. New balance: " << balance << endl;
    }
}
//Displays all account information
void Account::PrintInfo() const{
    if (accountCustomer1 != nullptr) {
        accountCustomer1->PrintInfo();
    }
    if (accountCustomer2 != nullptr) {
        accountCustomer2->PrintInfo();
    }
    if(ID != 0){
        cout << endl;
        cout << fixed << setprecision(2); // ensure balance shows two decimals
        cout << setw(15) << left << "Account ID" << setw(30) << left << ID << endl;
        cout << setw(15) << left << "Balance" << setw(30) << left << balance << endl;
        cout << setw(15) << left << "Withdrawals" << setw(30) << left<< withdrawalCounter << endl;
        cout << setw(15) << left << "Deposits" << setw(30) << left << depositsCounter << endl;
    }
}

