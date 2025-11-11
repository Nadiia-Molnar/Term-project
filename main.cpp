#include "SavingAccount.h"
#include "CheckingAccount.h"
#include <cstdlib>  // for srand(), rand()
#include <ctime>    // for time()

void menu();
void newCustomer();
void newAccount(int accountOpt);
void transferMenu();
int existingCustomer(Customer customerList[], const int NUM_OF_CUST);
void createCheckingAccount(CheckingAccount checkingAccount[], Customer customerList[], const int NUM_OF_CUST);
void createSavingAccount(SavingAccount savingAccount[], Customer customerList[], const int NUM_OF_CUST);
void deleteAccount(Customer customerList[], CheckingAccount checkingAccount[], SavingAccount savingAccount[], const int NUM_OF_CUST);
void modifyAccount(Customer customerList[], CheckingAccount checkingAccount[], SavingAccount savingAccount[], const int NUM_OF_CUST);
void transferMoney(Customer customerList[], CheckingAccount checkingAccount[], SavingAccount savingAccount[], const int NUM_OF_CUST);

int main()
{
    srand(time_t(0)); // seed random generator, srand(time(0)) on windows
    
    int customerCounter = 0;
    const int NUM_OF_CUST = 5;
    string _fName, _lName, _address, _phone, _email;
    char ans;
    int opt = 0;
    
    Customer customerList[NUM_OF_CUST]; // creating an array to store customers' information
    SavingAccount savingAccount[NUM_OF_CUST]; // array for saving account
    CheckingAccount checkingAccount[NUM_OF_CUST]; //array for checking account

    menu();
    cin >> opt;
    
    while (opt != 6)
    {
        switch (opt){
            case 1:
            {
                // Create checking account
                cout << "Do you have an account(Y or N)?: " ;
                cin >> ans;
                if (ans == 'Y' || ans == 'y')
                {
                    int customerIndex = existingCustomer(customerList, NUM_OF_CUST);
                    if (customerIndex == -1){
                        cout << "Customer not found. Please create a new account first." << endl;
                        break;
                    }
                    
                    if (checkingAccount[customerIndex].getID() != 0) {
                        cout << "There is an existing checking account with the following information." << endl;
                        checkingAccount[customerIndex].PrintInfo();
                    }
                    else{
                        double firstDeposit, limit;
                        // Create checking account for existing customer
                        checkingAccount[customerIndex].setAccountCustomer(&customerList[customerIndex]);
                        // Deposit
                        cout << "Enter your first deposit amount: ";
                        cin >> firstDeposit;
                        while (firstDeposit <= 0){
                            cout << "The amount must be positive. Try again: ";
                            cin >> firstDeposit;
                        }
                        checkingAccount[customerIndex].setBalance(firstDeposit);
                        cout << "Your balance: $" << checkingAccount[customerIndex].getBalance() << endl;
                        
                        
                        cout << "Enter overdraft limit for this checking account: ";
                        cin >> limit;
                        while (limit < 0){
                            cout << "Overdraft limit cannot be negative. Try again: ";
                            cin >> limit;
                        }
                        checkingAccount[customerIndex].setOverDraftLimit(limit);
                        
                        cout << "New checking account created for " << customerList[customerIndex].getFname() << " " << customerList[customerIndex].getLname()  << "!" << endl;
                    }
                }
                else{
                    // Create new customer
                    createCheckingAccount(checkingAccount, customerList, NUM_OF_CUST);
                }
                break;
            }
            case 2:
            {
                //create saving
                cout << "Does customer have an account? (Y or N)";
                cin >> ans;
                if (ans == 'Y' || ans == 'y')
                {
                    int customerIndex = existingCustomer(customerList, NUM_OF_CUST);
                    if (customerIndex == -1){
                        cout << "Customer not found. Please create a new account first." << endl;
                        break;
                    }
                    if (savingAccount[customerIndex].getID() != 0) {
                        cout << "There is an existing saving account with the following information." << endl;
                        savingAccount[customerIndex].PrintInfo();
                    }
                    else{
                        double firstDeposit, rate;
                        savingAccount[customerIndex].setAccountCustomer(&customerList[customerIndex]);
                        
                        cout << "Enter initial deposit: ";
                        cin >> firstDeposit;
                        savingAccount[customerIndex].setBalance(firstDeposit);
                        
                        cout << "Enter interest rate: ";
                        cin >> rate;
                        savingAccount[customerIndex].setInterestRate(rate);
                        
                        
                        cout << "Saving account created successfully!" <<endl;
                        savingAccount[customerIndex].PrintInfo();
                    }
                }
                else
                {
                    createSavingAccount(savingAccount, customerList, NUM_OF_CUST);
                }
                break;
            }
            case 3:
            {
                //View account info
                int customerIndex = existingCustomer(customerList, NUM_OF_CUST);
                
                if (customerIndex == -1){
                    cout << "Customer not found." << endl;
                    break;
                }
                
                cout << endl;
                cout << "=============================================" << endl;
                cout << setw(15) << left << "Field" << setw(30) << left << "Information" << endl;
                cout << "---------------------------------------------" << endl;
                cout << setw(15) << left << "Name" << setw(30) << left << customerList[customerIndex].getFname() + " " + customerList[customerIndex].getLname() << endl;
                cout << setw(15) << left << "Phone" << setw(30) << left << customerList[customerIndex].getPhone() << endl;
                cout << setw(15) << left << "Email" << setw(30) << left << customerList[customerIndex].getEmail() << endl;
                cout << setw(15) << left << "Address" << setw(30) << left << customerList[customerIndex].getAddress() << endl;
                
                // Checking Account
                if (checkingAccount[customerIndex].getID() != 0){
                    cout << endl;
                    cout << "Checking Account:" << endl;
                    cout << setw(15) << left << "Account ID" << setw(30) << left << checkingAccount[customerIndex].getID() << endl;
                    cout << setw(15) << left << "Balance" << setw(30) << left << checkingAccount[customerIndex].getBalance() << endl;
                    cout << setw(15) << left << "Overdraft" << setw(30) << left << checkingAccount[customerIndex].getOverDraftLimit() << endl;
                }
                
                // Saving Account
                if (savingAccount[customerIndex].getID() != 0){
                    cout << endl;
                    cout << "Saving Account:" << endl;
                    cout << setw(15) << left << "Account ID" << setw(30) << left << savingAccount[customerIndex].getID() << endl;
                    cout << setw(15) << left << "Balance" << setw(30) << left << savingAccount[customerIndex].getBalance() << endl;
                    cout << setw(15) << left << "Interest Rate" << setw(30) << left << savingAccount[customerIndex].getInterestRate() << endl;
                }
                
                cout << "=============================================" << endl;
                break;
            }
            case 4:
            {
                // Modify or delete the account
                char choice;
                cout << "Do you want to delete or modify the account (m - modify, d - delete): ";
                cin >> choice;
                
                if (choice == 'd' || choice == 'D'){
                    // Delete account
                    deleteAccount(customerList, checkingAccount, savingAccount, NUM_OF_CUST);
                }
                else if (choice == 'm' || choice == 'M'){
                    // Modify account
                    modifyAccount(customerList, checkingAccount, savingAccount, NUM_OF_CUST);
                }
                else{
                    cout << "Invalid option." << endl;
                }
                break;
            case 5:
            {
                //Transfer money
                transferMoney(customerList, checkingAccount, savingAccount, NUM_OF_CUST);
                break;
            }
            case 6:
                //exit the program
                cout << "Exiting......" << endl;
                break;
            }
        }
        system("pause");
        
        menu();
        cin >> opt;
    }
    
    system("pause");
    return 0;

}

void menu(){
    //display the menu
    cout << "========= MAIN MENU =========" << endl;
    cout << "1. Create a checking account." << endl;
    cout << "2. Create a saving account." << endl;
    cout << "3. View account information." << endl;
    cout << "4. Modify or delete the account." << endl;
    cout << "5. Transfer between accounts." << endl;
    cout << "6. Exit the program." << endl;
    cout << "Please select between the following options(1-6): ";
}

int existingCustomer(Customer customerList[], const int NUM_OF_CUST){
    string _fName, _lName, _phone;
    
    cout << "Enter first name: ";
    cin >> _fName;
    cout << "Enter last name: ";
    cin >> _lName;
    cout << "Enter phone number: ";
    cin >> _phone;
    
    int customerIndex = -1;
    for (int i = 0; i < NUM_OF_CUST; i++)
    {
        if (customerList[i].getFname() == _fName && customerList[i].getLname() == _lName && customerList[i].getPhone() == _phone){
            customerIndex = i;
            break;
        }
    }
    return customerIndex;
}

void createCheckingAccount(CheckingAccount checkingAccount[], Customer customerList[], const int NUM_OF_CUST){
    string _fName, _lName, _address, _phone, _email;
    double firstDeposit, limit;
    bool newCheckingAccount = false;
    
    for(int i = 0; i < NUM_OF_CUST; i++){
        if(checkingAccount[i].getID() == 0){
            cout << "Enter first name: ";
            cin >> _fName;
            cout << "Enter last name: ";
            cin >> _lName;
            cout << "Enter phone number: ";
            cin >> _phone;
            cout << "Enter email: ";
            cin >> _email;
            cout << "Enter address: ";
            cin.ignore();
            getline(cin, _address);
            
            customerList[i].setAll(_fName, _lName, _address, _phone, _email);
            checkingAccount[i].setAccountCustomer(&customerList[i]);
            
            // Generate unique random ID
            int newID;
            bool unique = true;
            do {
                newID = rand() % 1000;
                for (int j = 0; j < NUM_OF_CUST; j++){
                    if (checkingAccount[j].getID() == newID){
                        unique = false;
                        break;
                    }
                }
            } while (!unique);
            checkingAccount[i].setID(newID);
            cout << "Your Account ID: " << checkingAccount[i].getID() << endl;
            
            // Deposit
            cout << "Enter your first deposit amount: ";
            cin >> firstDeposit;
            while (firstDeposit <= 0){
                cout << "The amount must be positive. Try again: ";
                cin >> firstDeposit;
            }
            checkingAccount[i].setBalance(firstDeposit);
            cout << "Your balance: $" << checkingAccount[i].getBalance() << endl;
            
            
            cout << "Enter overdraft limit for this checking account: ";
            cin >> limit;
            while (limit < 0){
                cout << "Overdraft limit cannot be negative. Try again: ";
                cin >> limit;
            }
            checkingAccount[i].setOverDraftLimit(limit);
            
            newCheckingAccount = true;
            cout << "Checking account created successfully!" << endl;
            break;
        }
    }
    if (!newCheckingAccount){
        cout << "No available space to create a new checking account." << endl;
    }
}

void createSavingAccount(SavingAccount savingAccount[], Customer customerList[], const int NUM_OF_CUST){
    string _fName, _lName, _address, _phone, _email;
    double firstDeposit, rate;
    bool created = false;

    for (int i = 0; i < NUM_OF_CUST; i++) {
        if (savingAccount[i].getID() == 0) {
            cout << "Enter first name: ";
            cin >> _fName;
            cout << "Enter last name: ";
            cin >> _lName;
            cout << "Enter phone number: ";
            cin >> _phone;
            cout << "Enter email: ";
            cin >> _email;
            cout << "Enter address: ";
            cin.ignore();
            getline(cin, _address);

            customerList[i].setAll(_fName, _lName, _address, _phone, _email);
            savingAccount[i].setAccountCustomer(&customerList[i]);

            // Generate unique random ID
            int newID;
            bool unique = true;
            do {
                newID = rand() % 1000;
                for (int j = 0; j < NUM_OF_CUST; j++){
                    if (savingAccount[j].getID() == newID){
                        unique = false;
                        break;
                    }
                }
            } while (!unique);
            savingAccount[i].setID(newID);

            cout << "Enter initial deposit: ";
            cin >> firstDeposit;
            while (firstDeposit <= 0) {
                cout << "Deposit must be positive. Try again: ";
                cin >> firstDeposit;
            }
            savingAccount[i].setBalance(firstDeposit);

            cout << "Enter interest rate (%): ";
            cin >> rate;
            while (rate < 0) {
                cout << "Interest rate cannot be negative. Try again: ";
                cin >> rate;
            }
            savingAccount[i].setInterestRate(rate);

            cout << "Saving account created successfully!" << endl;
            savingAccount[i].PrintInfo();
            created = true;
            break;
        }
    }
    if (!created) {
        cout << "No available slot to create new saving account!" << endl;
    }
}

void deleteAccount(Customer customerList[], CheckingAccount checkingAccount[], SavingAccount savingAccount[], const int NUM_OF_CUST){
    string _fName, _lName, _phone;
    cout << "Enter first name: ";
    cin >> _fName;
    cout << "Enter last name: ";
    cin >> _lName;
    cout << "Enter phone number: ";
    cin >> _phone;

    int customerIndex = -1;
    // Find the customer
    for (int i = 0; i < NUM_OF_CUST; i++) {
        if (customerList[i].getFname() == _fName && customerList[i].getLname() == _lName && customerList[i].getPhone() == _phone) {
            customerIndex = i;
            break;
        }
    }

    if (customerIndex == -1) {
        cout << "Customer not found." << endl;
        return;
    }

    // Delete checking account if exists
    if (checkingAccount[customerIndex].getID() != 0) {
        checkingAccount[customerIndex].setID(0);
        checkingAccount[customerIndex].setBalance(0.0);
        checkingAccount[customerIndex].setOverDraftLimit(0.0);
        checkingAccount[customerIndex].setAccountCustomer(nullptr);
        cout << "Checking account deleted successfully." << endl;
    }

    // Delete saving account if exists
    if (savingAccount[customerIndex].getID() != 0) {
        savingAccount[customerIndex].setID(0);
        savingAccount[customerIndex].setBalance(0.0);
        savingAccount[customerIndex].setAccountCustomer(nullptr);
        cout << "Saving account deleted successfully." << endl;
    }

    // Optionally, delete customer info
    customerList[customerIndex].setFname("");
    customerList[customerIndex].setLname("");
    customerList[customerIndex].setPhone("");
    customerList[customerIndex].setEmail("");
    customerList[customerIndex].setAddress("");

    cout << "Customer record deleted successfully." << endl;
}

void modifyAccount(Customer customerList[], CheckingAccount checkingAccount[], SavingAccount savingAccount[], const int NUM_OF_CUST){
    string _fName, _lName, _phone;
    cout << "Enter first name: ";
    cin >> _fName;
    cout << "Enter last name: ";
    cin >> _lName;
    cout << "Enter phone number: ";
    cin >> _phone;

    int customerIndex = -1;
    // Find the customer
    for (int i = 0; i < NUM_OF_CUST; i++) {
        if (customerList[i].getFname() == _fName && customerList[i].getLname() == _lName && customerList[i].getPhone() == _phone){
            customerIndex = i;
            break;
        }
    }

    if (customerIndex == -1) {
        cout << "Customer not found." << endl;
        return;
    }

    int choice;
    cout << "What do you want to modify?" << endl;
    cout << "1. Personal information." << endl;
    cout << "2. Checking account details." << endl;
    cout << "3. Saving account details." << endl;
    cout << "Enter your choice (1-3): " << endl;
    cin >> choice;

    switch (choice){
        case 1:
        {
            // Modify personal info
            string newFname, newLname, newPhone, newEmail, newAddress;
            cout << "Enter new first name: ";
            cin >> newFname;
            cout << "Enter new last name: ";
            cin >> newLname;
            cout << "Enter new phone number: ";
            cin >> newPhone;
            cout << "Enter new email: ";
            cin >> newEmail;
            cout << "Enter new address: ";
            cin.ignore();
            getline(cin, newAddress);

            customerList[customerIndex].setFname(newFname);
            customerList[customerIndex].setLname(newLname);
            customerList[customerIndex].setPhone(newPhone);
            customerList[customerIndex].setEmail(newEmail);
            customerList[customerIndex].setAddress(newAddress);

            cout << "Personal information updated successfully." << endl;
            break;
        }
        case 2:
        {
            // Modify checking account if exists
            if (checkingAccount[customerIndex].getID() == 0){
                cout << "No checking account found for this customer." << endl;
            }
            else{
                double newBalance, newLimit;
                cout << "Enter new balance: ";
                cin >> newBalance;
                checkingAccount[customerIndex].setBalance(newBalance);

                cout << "Enter new overdraft limit: ";
                cin >> newLimit;
                checkingAccount[customerIndex].setOverDraftLimit(newLimit);

                cout << "Checking account updated successfully." << endl;
            }
            break;
        }
        case 3:
        {
            // Modify saving account if exists
            if (savingAccount[customerIndex].getID() == 0){
                cout << "No saving account found for this customer." << endl;
            }
            else{
                double newBalance;
                cout << "Enter new balance: ";
                cin >> newBalance;
                savingAccount[customerIndex].setBalance(newBalance);

                cout << "Saving account updated successfully." << endl;
            }
            break;
        }
        default:
            cout << "Invalid choice." << endl;
            break;
    }
}

void transferMoney(Customer customerList[], CheckingAccount checkingAccount[], SavingAccount savingAccount[], const int NUM_OF_CUST){
    char ans;
    cout << "Do you want to transfer money between your own accounts? (Y or N): ";
    cin >> ans;

    if (ans == 'Y' || ans == 'y') {
        int customerIndex = existingCustomer(customerList, NUM_OF_CUST);
        if (customerIndex == -1) {
            cout << "Customer not found." << endl;
            return;
        }

        cout << "Transfer from checking or from saving(C/S)?: ";
        cin >> ans;
        double amount;
        if ((ans == 'c' || ans == 'C') && checkingAccount[customerIndex].getID() != 0 && savingAccount[customerIndex].getID() != 0){
            cout << "Enter amount to transfer: ";
            cin >> amount;
            if (amount > 0 && amount <= checkingAccount[customerIndex].getBalance()){
                checkingAccount[customerIndex].WithdrawMoney(amount);
                savingAccount[customerIndex].DepositMoney(amount);
                cout << "Transfer successful!" << endl;
            }
            else{
                cout << "Invalid amount or insufficient funds." << endl;
            }
        }
        else if ((ans == 's' || ans == 'S') && savingAccount[customerIndex].getID() != 0 && checkingAccount[customerIndex].getID() != 0){
            cout << "Enter amount to transfer: ";
            cin >> amount;
            if (amount > 0 && amount <= savingAccount[customerIndex].getBalance()){
                savingAccount[customerIndex].WithdrawMoney(amount);
                checkingAccount[customerIndex].DepositMoney(amount);
                cout << "Transfer successful!" << endl;
            }
            else{
                cout << "Invalid amount or insufficient funds." << endl;
            }
        }
        else{
            cout << "One of your accounts does not exist." << endl;
        }
    }
    else{
        // Transfer to another customer
        cout << "Enter your account info: " << endl;
        int senderIndex = existingCustomer(customerList, NUM_OF_CUST);
        if (senderIndex == -1) {
            cout << "Sender not found." << endl;
            return;
        }

        cout << "Enter recipient's account info: " << endl;
        int recipientIndex = existingCustomer(customerList, NUM_OF_CUST);
        if (recipientIndex == -1) {
            cout << "Recipient not found." << endl;
            return;
        }

        cout << "Which account to transfer from? (C - checking or S - saving): ";
        cin >> ans;
        double amount;

        if((ans == 'c' || ans == 'C') && checkingAccount[senderIndex].getID() != 0){
            cout << "Enter amount to transfer: ";
            cin >> amount;
            if(amount > 0 && amount <= checkingAccount[senderIndex].getBalance()){
                checkingAccount[senderIndex].WithdrawMoney(amount);

                if(checkingAccount[recipientIndex].getID() != 0){
                    checkingAccount[recipientIndex].DepositMoney(amount);
                }
                else if(savingAccount[recipientIndex].getID() != 0) {
                    savingAccount[recipientIndex].DepositMoney(amount);
                }
                else{
                    cout << "Recipient has no account to receive money!" << endl;
                    checkingAccount[senderIndex].DepositMoney(amount); // revert
                    return;
                }
                cout << "Transfer successful!" << endl;
            }
            else{
                cout << "Invalid amount or insufficient funds." << endl;
            }
        }
        else if((ans == 's' || ans == 'S') && savingAccount[senderIndex].getID() != 0){
            cout << "Enter amount to transfer: ";
            cin >> amount;
            if(amount > 0 && amount <= savingAccount[senderIndex].getBalance()){
                savingAccount[senderIndex].WithdrawMoney(amount);

                if (checkingAccount[recipientIndex].getID() != 0){
                    checkingAccount[recipientIndex].DepositMoney(amount);
                }
                else if(savingAccount[recipientIndex].getID() != 0){
                    savingAccount[recipientIndex].DepositMoney(amount);
                }
                else{
                    cout << "Recipient has no account to receive money!" << endl;
                    savingAccount[senderIndex].DepositMoney(amount); // revert
                    return;
                }
                cout << "Transfer successful!" << endl;
            }
            else{
                cout << "Invalid amount or insufficient funds." << endl;
            }
        }
        else{
            cout << "Your selected account does not exist." << endl;
        }
    }
}
