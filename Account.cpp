#include "Account.h"

int Account::withdrawalCounter = 0;
int Account::depositsCounter = 0;

Account::Account(){
    ID = 0;
    balance = 0.0;
    accountCustomer = 0; // check if it works
}

Account::Account(int _id, double _balance, Customer * _accountCustomer){
    if (_id > 0)
        ID = _id;
    else
        ID = 0;
    if (_balance > 0.0)
        balance = _balance;
    else
        balance = 0.0;
    accountCustomer = _accountCustomer;
}

void Account::setID (int _id){
    if (_id > 0)
        ID = _id;
    else
        ID = 0;
}
void Account::setBalance(double _balance){
    if (_balance > 0.0)
        balance = _balance;
    else
        balance = 0.0;
}
void Account::setAccountCustomer(Customer * _accountCustomer){
    accountCustomer = _accountCustomer;
}
void Account::setWithdrawalCounter(int _withdrawalCounter){
    if (_withdrawalCounter > 0)
        withdrawalCounter = _withdrawalCounter;
}
void Account::setDepositCounter(int _depositCounter){
    if (_depositCounter > 0)
        depositsCounter = _depositCounter;
}
void Account::setAll(int _id, double _balance, Customer * _accountCustomer){
    setID(_id);
    setBalance(_balance);
    accountCustomer = _accountCustomer;
}

int Account::getID() const {
    return ID;
}
double Account::getBalance() const {
    return balance;
}
Customer * Account::getAccountCustomer() const {
    return accountCustomer;
}
int Account::getWithdrawalCounter() {
    return withdrawalCounter;
}
int Account::getDepositsCounter() {
    return depositsCounter;
}

void Account::DepositMoney(double & _amount) {
    if (_amount > 0.0){
        balance = balance + _amount;
        depositsCounter = depositsCounter + 1;
    }
}
void Account::WithdrawMoney(double & _amount) {
    if (_amount < 0.0){
        cout << "Error: Amount must be positive." << endl;
        return;
    }
    if (_amount > balance){
        cout << "Error: Insufficient funds." << endl;
        return;
    }
        
    balance = balance - _amount;
    withdrawalCounter = withdrawalCounter + 1;
    cout << "Withdrawal successful. New balance: " << balance << endl;
}
void Account::PrintInfo(){
    cout << setw(10) << left << "Account ID: " << ID << endl;
    cout << setw(10) << left << "Balance: " << balance << endl;
    if (accountCustomer != 0) {
        accountCustomer->PrintInfo();
    }
}
