#include "SavingAccount.h"
#include "CheckingAccount.h"
#include <cstdlib>  //For srand(), rand()
#include <ctime>    //For time()

//Function prototypes
void menu();
int existingCustomer(bool);
int createNewCustomer(string, string, string);
void createCheckingAccount();
void createSavingAccount();
void viewInfo(int);
void deleteAccount();
void modifyAccount();
void transferMoney();
int getSavingAccountIndex(string, string);
int getCheckingAccountIndex(string, string);
int getNextEmptyCheckingAccountIndex();
int getNextEmptySavingAccountIndex();
int getNextEmptyCustomerListIndex();

//Global Constants and Variables
const int NUM_OF_ACCOUNT = 5;
int ID_COUNTER = (rand() % 100) + 100;
Customer customerList[NUM_OF_ACCOUNT*2]; //Array to store customers' information
SavingAccount savingAccount[NUM_OF_ACCOUNT]; //Array for saving account
CheckingAccount checkingAccount[NUM_OF_ACCOUNT]; //Array for checking account
//TransactionHistory checkingAccount2[NUM_OF_ACCOUNT][1000]; //Array for transactions

int main()
{
//    srand(time_t(0)); // i'm not sure if i need to keep this or not, seed random generator, srand(time(0)) on windows
    
    string _fName, _lName, _address, _phone, _email;
    char ans;  //Used for Yes/No questions
    int opt;   //Menu option

    menu();
    cin >> opt;
    while(cin.fail() || opt>6 || opt<1){
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Bad data, try again." << endl;
        cout << "Please select between the following options(1-6): ";
        cin >> opt;
    }
    
    do{
        switch(opt){
            //Create checking account
            case 1: {
//                cout << endl;
//                cout << "=============================" << endl;
                createCheckingAccount();
                break;
            }
            //Create a saving account
            case 2: {
//                cout << endl;
//                cout << "=============================" << endl;
                createSavingAccount();
                break;
            }
            //View account info
            case 3: {
                int customerIndex = existingCustomer(false);
                viewInfo(customerIndex);
            }
            //Modify or delete the account
            case 4:
            {
                char ans;
                //Ask the user what action they want to perform
                cout << "Do you want to delete or modify the account (m - modify, d - delete): ";
                cin >> ans;
                while(cin.fail()){
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << "Bad data, try again." << endl;
                    cout << "Do you want to delete or modify the account (m - modify, d - delete)?: ";
                    cin >> ans;
                }
                
                //If user chooses to delete an account
                if (ans == 'd' || ans == 'D'){
                    // Delete account
                    deleteAccount();
                }
                //If user chooses to modify an existing account
                else if (ans == 'm' || ans == 'M'){
                    // Modify account
                    modifyAccount();
                }
                //If user enters an invalid option
                else{
                    cout << "Invalid option." << endl;
                }
                break;
            }
            //Transfer money
            case 5:
            {
                transferMoney();
                break;
            }
            //Exit the program
            case 6:{
                cout << "Exiting......" << endl;
                break;
            }
        }

        cout << "\n" << endl;
        menu();
        cin >> opt;
        while(cin.fail() || opt>6 || opt<1){
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Bad data, try again." << endl;
            cout << "Please select between the following options(1-6): ";
            cin >> opt;
        }
    }while(opt<=6 && opt>=1);
    
//    system("pause");
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

// Function: Checks if a customer already exists in the system
int existingCustomer(bool needNewCustomer){
    string _fName, _lName, _phone;
    int customerIndex = -1;
    
    cout << "Enter first name: ";
    cin >> _fName;
    cout << "Enter last name: ";
    cin >> _lName;
    cout << "Enter phone number: ";
    cin >> _phone;
    
    //Compare name and phone number to identify existing customer
    for (int i = 0; i < NUM_OF_ACCOUNT*2; i++){
        if (customerList[i].getFname() == _fName && customerList[i].getLname() == _lName && customerList[i].getPhone() == _phone){
            return i;
        }
    }
    
    //Create a new customer
    if (needNewCustomer){
        customerIndex = createNewCustomer(_fName, _lName, _phone);
    }
    return customerIndex;
}

//Function: Creates a new customer
int createNewCustomer(string _fName, string _lName, string _phone){
    string _address, _email;
    int index = getNextEmptyCustomerListIndex();
    
    cout << "Enter email: ";
    cin >> _email;
    cout << "Enter address: ";
    cin.ignore();
    getline(cin, _address);
    
    customerList[index].setAll(_fName, _lName, _address, _phone, _email);
    
    return index;
}

//Function: Creates a new checking account for a customer
void createCheckingAccount(){
    // Check if customer exist
    int customerIndex = existingCustomer(true);
    
    //If customer already has a checking account
    int CAIndex = getCheckingAccountIndex(customerList[customerIndex].getPhone(), customerList[customerIndex].getLname());
    if(CAIndex != -1){
        cout << "There is an existing checking account with the following information.\n" << endl;
        cout << "=============================" << endl;
        checkingAccount[CAIndex].PrintInfo();
        return;
    }
    
    // Customer already exists and has a saving account but no checking account
    if(getSavingAccountIndex(customerList[customerIndex].getPhone(), customerList[customerIndex].getLname()) != -1){
        char ans;
        cout << "You alredy have a saving account with us." << endl;
        cout << "Do you still want to create a new checking account(Enter Y for yes or N for no)?: ";
        cin >> ans;
        while(cin.fail()){
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Bad data, try again." << endl;
            cout << "Do you still want to create a new checking account(Enter Y for yes or N for no)?: ";
            cin >> ans;
        }
        
        // Exit to main menu
        if(ans != 'Y' && ans != 'y'){
            cout << "No checking account was created.\n" << endl;
            return;
        }
    }
    
    int nextCAIndex = getNextEmptyCheckingAccountIndex();
    
    checkingAccount[nextCAIndex].setAccountCustomer1(&customerList[customerIndex]);
    
    //Generate unique ID
    int newID = ID_COUNTER + 1;
    ID_COUNTER++;
    checkingAccount[nextCAIndex].setID(newID);
    
    double firstDeposit, limit;
    //Deposit setup
    cout << "Enter your first deposit amount: ";
    cin >> firstDeposit;
    while(cin.fail() || firstDeposit <= 0){
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Bad data, try again." << endl;
        cout << "The amount must be positive number. Try again: ";
        cin >> firstDeposit;
    }
    checkingAccount[nextCAIndex].setBalance(firstDeposit);
    
    //Overdraft setup
    cout << "Enter overdraft limit for this checking account: ";
    cin >> limit;
    while(cin.fail() || limit<0){
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Bad data, try again." << endl;
        cout << "Overdraft limit must be positive number. Try again: ";
        cin >> limit;
    }
    checkingAccount[nextCAIndex].setOverDraftLimit(limit);
    
    cout << "New checking account created successfully for " << customerList[customerIndex].getFname() << " " << customerList[customerIndex].getLname() << "!\n" << endl;
    cout << "=============================" << endl;
    checkingAccount[nextCAIndex].PrintInfo();
}

//Function: Creates a new saving account for a customer
void createSavingAccount(){
//    string _fName, _lName, _address, _phone, _email;
//    double firstDeposit, rate;
//    bool created = false; //Flag to check if account was successfully created
    int customerIndex = existingCustomer(true);
    
    //If customer alresdy has a saving account
    int SAIndex = getSavingAccountIndex(customerList[customerIndex].getPhone(), customerList[customerIndex].getLname());
    if (SAIndex != -1){
        cout << "There is an existing saving account with the following information.\n" << endl;
        cout << "=============================" << endl;
        savingAccount[SAIndex].PrintInfo();
        return;
    }
        //Customer has a checking account but no saving account
    if(getCheckingAccountIndex(customerList[customerIndex].getPhone(), customerList[customerIndex].getLname()) != -1){
        char ans;
        cout << "You alredy have a checking account with us." << endl;
        cout << "Do you want to still want to create a new saving account(Enter Y for yes or N for no)?: ";
        cin >> ans;
        while(cin.fail()){
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Bad data, try again." << endl;
            cout << "Do you want to still want to create a new saving account(Enter Y for yes or N for no)?: ";
            cin >> ans;
        }
        
        //Exit to the main
        if(ans!='Y' || ans!='y'){
            cout << "No saving account was created.\n" << endl;
            return;
        }
    }
            
    int nextSAIndex = getNextEmptySavingAccountIndex();
    double firstDeposit, rate;
    
    savingAccount[nextSAIndex].setAccountCustomer1(&customerList[customerIndex]);
    
    cout << "Enter initial deposit: ";
    cin >> firstDeposit;
    while(cin.fail() || firstDeposit <= 0){
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Bad data, try again." << endl;
        cout << "The amount must be positive number. Try again: ";
        cin >> firstDeposit;
    }
    savingAccount[nextSAIndex].setBalance(firstDeposit);
    
    cout << "Enter interest rate: ";
    cin >> rate;
    while(cin.fail() || rate <= 0){
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Bad data, try again." << endl;
        cout << "The interest rate must be positive number. Try again: ";
        cin >> rate;
    }
    savingAccount[nextSAIndex].setInterestRate(rate);
    
    //Confirm successful creation
    cout << "New saving account created successfully for " << customerList[customerIndex].getFname() << " " << customerList[customerIndex].getLname() << "!\n" << endl;
    cout << "=============================" << endl;
    savingAccount[nextSAIndex].PrintInfo();
}

//Function: Display all information about a customer
void viewInfo(int index){
    //No matching customer was found.
    if (index == -1){
        cout << "Customer not found." << endl;
        return;
    }
    
    //Formatted header
    cout << endl;
    cout << "=============================================" << endl;
    cout << setw(15) << left << "Field" << setw(30) << left << "Information" << endl;
    cout << "---------------------------------------------" << endl;
    cout << setw(15) << left << "Name" << setw(30) << left << customerList[index].getFname() << " " << customerList[index].getLname() << endl;
    cout << setw(15) << left << "Phone" << setw(30) << left << customerList[index].getPhone() << endl;
    cout << setw(15) << left << "Email" << setw(30) << left << customerList[index].getEmail() << endl;
    cout << setw(15) << left << "Address" << setw(30) << left << customerList[index].getAddress() << endl;
    
    // Checking Account info
    int CAIndex = getCheckingAccountIndex(customerList[index].getPhone(), customerList[index].getLname());
    if (checkingAccount[CAIndex].getID() != 0){
        cout << endl;
        cout << "Checking Account:" << endl;
        cout << setw(15) << left << "Account ID" << setw(30) << left << checkingAccount[CAIndex].getID() << endl;
        cout << setw(15) << left << "Balance" << setw(30) << left << checkingAccount[CAIndex].getBalance() << endl;
        cout << setw(15) << left << "Overdraft" << setw(30) << left << checkingAccount[CAIndex].getOverDraftLimit() << endl;
    }
    
    // Saving Account info
    int SAIndex = getSavingAccountIndex(customerList[index].getPhone(), customerList[index].getLname());
    if (savingAccount[SAIndex].getID() != 0){
        cout << endl;
        cout << "Saving Account:" << endl;
        cout << setw(15) << left << "Account ID" << setw(30) << left << savingAccount[SAIndex].getID() << endl;
        cout << setw(15) << left << "Balance" << setw(30) << left << savingAccount[SAIndex].getBalance() << endl;
        cout << setw(15) << left << "Interest Rate" << setw(30) << left << savingAccount[SAIndex].getInterestRate() << endl;
    }
    
    cout << "=============================" << endl;
}

//Function: Deletes an account
void deleteAccount(){
    char ans;
    int customerIndex = existingCustomer(false); //Find the index of the existing customer

    //If customer does not exist
    if (customerIndex == -1) {
        cout << "Customer not found." << endl;
        return;
    }
    
    //Delete checking account
    int CAIndex = getCheckingAccountIndex(customerList[customerIndex].getPhone(), customerList[customerIndex].getLname());
    if(CAIndex != -1){
        cout << "Do you want to delete the checking account(Enter Y for yes or N for no)?: ";
        cin >> ans;
        while(cin.fail()){
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Bad data, try again." << endl;
            cout << "Do you want to delete the checking account(Enter Y for yes or N for no)?: ";
            cin >> ans;
        }
        
        //If user confirms deletion, reset checking account data
        if (ans == 'Y' || ans == 'y'){
            if(checkingAccount[CAIndex].getBalance() < 0){
                cout << "You cannot delete this account because it has an outstanding overdraft balance. Please pay off your debt before closing the account." << endl;
            }
            else{
                checkingAccount[CAIndex].setAll(0, 0.0, nullptr, nullptr, 0.0);
                cout << "Checking account deleted successfully." << endl;
            }
        }
        else{
            cout << "Account deletion canceled. No changes were made." << endl;
        }
    }
    //Delete saving account
    int SAIndex = getSavingAccountIndex(customerList[customerIndex].getPhone(), customerList[customerIndex].getLname());
    if(SAIndex != -1){
        cout << "Do you want to delete the saving account(Enter Y for yes or N for no)?: ";
        cin >> ans;
        while(cin.fail()){
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Bad data, try again." << endl;
            cout << "Do you want to delete the saving account(Enter Y for yes or N for no)?: ";
            cin >> ans;
        }
        
        //If user confirms deletion, reset saving account data
        if (ans == 'Y' || ans == 'y'){
            savingAccount[SAIndex].setAll(0, 0.0, nullptr, nullptr, 0.0);
            cout << "Saving account deleted successfully." << endl;
        }
        else{
            cout << "Account deletion canceled. No changes were made." << endl;
        }
    }
    
    //Delete all customer info
    cout << "Do you want to delete all your information completely(Enter Y for yes or N for no)?: ";
    cout << "Your checking and saving accounts will be deleted as well." << endl;
        cin >> ans;
        while(cin.fail()){
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Bad data, try again." << endl;
            cout << "Do you want to delete all your information completely(Enter Y for yes or N for no)?: ";
            cin >> ans;
        }
        
        //If user confirms deletion, clear all customer data
        if (ans == 'Y' || ans == 'y'){
            if(checkingAccount[CAIndex].getBalance() < 0){
                cout << "You cannot delete this account because it has an outstanding overdraft balance. Please pay off your debt before closing the account." << endl;
            }
            else{
                customerList[customerIndex].setFname("");
                customerList[customerIndex].setLname("");
                customerList[customerIndex].setPhone("");
                customerList[customerIndex].setEmail("");
                customerList[customerIndex].setAddress("");
                
                
                checkingAccount[CAIndex].setAll(0, 0.0, nullptr, nullptr, 0.0);
                savingAccount[SAIndex].setAll(0, 0.0, nullptr, nullptr, 0.0);
                
                cout << "Account deleted successfully." << endl;
            }
        }
        else{
            cout << "Account deletion canceled. No changes were made." << endl;
        }
        
    }

//Function: Modifies an account
void modifyAccount(){
    // Find the customer
    int customerIndex = existingCustomer(false);

    //If customer does not exist
    if (customerIndex == -1) {
        cout << "Customer not found." << endl;
        return;
    }
    
    //Modification menu
    int ans;
    cout << "What do you want to modify?" << endl;
    cout << "1. Personal information." << endl;
    cout << "2. Checking account details." << endl;
    cout << "3. Saving account details." << endl;
    cout << "Enter your choice (1-3): " << endl;
    cin >> ans;
    while(cin.fail()){
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Bad data, try again." << endl;
        cout << "Enter your choice (1-3): ";
        cin >> ans;
    }
    
    switch (ans){
        //Modify personal info
        case 1:
        {
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

            //Update customer information
            customerList[customerIndex].setFname(newFname);
            customerList[customerIndex].setLname(newLname);
            customerList[customerIndex].setPhone(newPhone);
            customerList[customerIndex].setEmail(newEmail);
            customerList[customerIndex].setAddress(newAddress);

            cout << "Personal information updated successfully." << endl;
            break;
        }
        // Modify checking account
        case 2:
        {
            // Check if customer has a checking account
            int CAIndex = getCheckingAccountIndex(customerList[customerIndex].getPhone(), customerList[customerIndex].getLname());
            if (CAIndex == -1){
                cout << "No checking account found for this customer." << endl;
            }
            else{
                double newLimit;
                cout << "Enter new overdraft limit: ";
                cin >> newLimit;
                while(cin.fail() || newLimit <= 0){
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << "Bad data, try again." << endl;
                    cout << "Overdraft limit must be positive number. Try again: ";
                    cin >> newLimit;
                }
                checkingAccount[CAIndex].setOverDraftLimit(newLimit);
                cout << "Checking account updated successfully." << endl;
            }
            break;
        }
        // Modify saving account
        case 3:
        {
            int SAIndex = getSavingAccountIndex(customerList[customerIndex].getPhone(), customerList[customerIndex].getLname());
            if(SAIndex == -1){
                cout << "No saving account found for this customer." << endl;
            }
            else{
                double newRate;
                cout << "Enter new interest rate: ";
                cin >> newRate;
                while(cin.fail() || newRate <= 0){
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << "Bad data, try again." << endl;
                    cout << "The interest rate must be positive number. Try again: ";
                    cin >> newRate;
                }
                savingAccount[SAIndex].setInterestRate(newRate);
                cout << "Saving account updated successfully." << endl;
            }
            break;
        }
        //Invalid choice
        default:
            cout << "Invalid choice." << endl;
    }
}

//Function: Transfer money
void transferMoney(){
    char ans;
    double amount;
    
    //Ask if the transfer is between the same customer's accounts
    cout << "Do you want to transfer money between your own accounts(Y or N)?: ";
    cin >> ans;
    while(cin.fail()){
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Bad data, try again." << endl;
        cout << "Do you want to transfer money between your own accounts(Y or N)?: ";
        cin >> ans;
    }
    
    if (ans == 'Y' || ans == 'y'){
        //Existing customer performing transfer between own accounts
        int customerIndex = existingCustomer(false);
        if (customerIndex == -1){
            cout << "Customer not found." << endl;
            return;
        }
        
        //Check if both accounts exist
        int CAIndex = getCheckingAccountIndex(customerList[customerIndex].getPhone(), customerList[customerIndex].getLname());
        int SAIndex = getSavingAccountIndex(customerList[customerIndex].getPhone(), customerList[customerIndex].getLname());
        if(CAIndex == -1){
            cout << "Your checking account does not exist." << endl;
            return;
        }
        else if (SAIndex == -1){
            cout << "Your saving account does not exist." << endl;
            return;
        }

        //Ask from which account the transfer should come
        cout << "Transfer from checking or from saving(C/S)?: ";
        cin >> ans;
        while(cin.fail()){
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Bad data, try again." << endl;
            cout << "Transfer from checking or from saving(C/S)?: ";
            cin >> ans;
        }
        
        //Transfer from checking to saving
        if (ans == 'c' || ans == 'C'){
            cout << "Enter amount to transfer: ";
            cin >> amount;
            while(cin.fail()){
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Bad data, try again." << endl;
                cout << "Enter a positive number for the amount to transfer: ";
                cin >> ans;
            }
            if (amount > 0 && amount <= checkingAccount[CAIndex].getBalance()){
                checkingAccount[CAIndex].WithdrawMoney(amount);
                savingAccount[SAIndex].DepositMoney(amount);
                cout << "Transfer successful!" << endl;
            }
            else{
                cout << "Invalid amount or insufficient funds." << endl;
            }
        }
        //Transfer from saving to checking
        else if (ans == 's' || ans == 'S') {
            cout << "Enter amount to transfer: ";
            cin >> amount;
            while(cin.fail()){
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Bad data, try again." << endl;
                cout << "Enter a positive number for the amount to transfer: ";
                cin >> ans;
            }
            if (amount > 0 && amount <= savingAccount[SAIndex].getBalance()){
                savingAccount[SAIndex].WithdrawMoney(amount);
                checkingAccount[CAIndex].DepositMoney(amount);
                cout << "Transfer successful!" << endl;
            }
            else{
                cout << "Invalid amount or insufficient funds." << endl;
            }
        }
        else{
            cout << "Invalid option." << endl;
            return;
        }
    }
    else{
        //Transfer to another customer
        cout << "Enter your account info: " << endl;
        int senderIndex = existingCustomer(false);
        if (senderIndex == -1) {
            cout << "Sender not found." << endl;
            return;
        }

        cout << "Enter recipient's account info: " << endl;
        int recipientIndex = existingCustomer(false);
        if (recipientIndex == -1) {
            cout << "Recipient not found." << endl;
            return;
        }

        cout << "Which account to transfer from(C/S)?: ";
        cin >> ans;
        while(cin.fail()){
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Bad data, try again." << endl;
            cout << "Transfer from checking or from saving(C/S)?: ";
            cin >> ans;
        }

        int senderCAIndex = getCheckingAccountIndex(customerList[senderIndex].getPhone(), customerList[senderIndex].getLname());
        int senderSAIndex = getSavingAccountIndex(customerList[senderIndex].getPhone(), customerList[senderIndex].getLname());
        int recipientCAIndex = getCheckingAccountIndex(customerList[recipientIndex].getPhone(), customerList[recipientIndex].getLname());
        int recipientSAIndex = getSavingAccountIndex(customerList[recipientIndex].getPhone(), customerList[recipientIndex].getLname());
            
        //Transfer from sender's checking account
        if((ans == 'c' || ans == 'C') && checkingAccount[senderCAIndex].getID() != 0){
            cout << "Enter amount to transfer: ";
            cin >> amount;
            while(cin.fail()){
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Bad data, try again." << endl;
                cout << "Enter a positive number for the amount to transfer: ";
                cin >> ans;
            }
            if(amount > 0 && amount <= checkingAccount[senderCAIndex].getBalance()){ //idk if i hae to check all of these
                //Deposit to recipient's checking or saving account
                if(checkingAccount[recipientCAIndex].getID() != 0){
                    checkingAccount[senderCAIndex].WithdrawMoney(amount);
                    checkingAccount[recipientCAIndex].DepositMoney(amount);
                }
                else if(savingAccount[recipientSAIndex].getID() != 0) {
                    checkingAccount[senderCAIndex].WithdrawMoney(amount);
                    savingAccount[recipientSAIndex].DepositMoney(amount);
                }
                else{
                    cout << "Recipient has no account to receive money!" << endl;
                    return;
                }
                cout << "Transfer successful!" << endl;
            }
            else{
                cout << "Invalid amount or insufficient funds." << endl;
            }
        }
        //Transfer from sender's saving account
        else if((ans == 's' || ans == 'S') && savingAccount[senderSAIndex].getID() != 0){
            cout << "Enter amount to transfer: ";
            cin >> amount;
            while(cin.fail()){
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Bad data, try again." << endl;
                cout << "Enter a positive number for the amount to transfer: ";
                cin >> ans;
            }
            if(amount > 0 && amount <= savingAccount[senderSAIndex].getBalance()){
                //Deposit to recipient's checking or saving account
                if (checkingAccount[recipientCAIndex].getID() != 0){
                    savingAccount[senderSAIndex].WithdrawMoney(amount);
                    checkingAccount[recipientCAIndex].DepositMoney(amount);
                }
                else if(savingAccount[recipientSAIndex].getID() != 0){
                    savingAccount[senderSAIndex].WithdrawMoney(amount);
                    savingAccount[recipientSAIndex].DepositMoney(amount);
                }
                else{
                    cout << "Recipient has no account to receive money!" << endl;
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










void jointAccountChecking()
{
    //before calling this function ask the user "Do you want to create a joint account? then which one?
    int customerIndex = existingCustomer();

    //If customer does not exist
    if (customerIndex == -1) {
        cout << "Customer not found." << endl;
        return;
    }
    
    if (customerIndex!=-1) //if one party has does an account a joint account can be made
    {
     string lName1, lName2;
     cout << "Enter customers Last name: ";
     cin >> lName1;
     cout << "Enter secondary customers Last name: ";
     cin >> lName2;
     if (lName1 == lName2) //if they have matching last names
     {
         cout << "Eligible to create joint accounts" << endl;
         cout << "Verify marriage license";
         createCheckingAccount(); // create the joint account
       
     }
     else
     {
         cout << "Inelibile to create joint accounts" << endl;
     }
   }
}
void jointAccountSavings(SavingAccount savingAccount[], Customer customerList[], const int NUM_OF_ACCOUNT)
{
    //before calling this function ask the user "Do you want to create a joint account? then which one?
    int customerIndex = existingCustomer();

    //If customer does not exist
    if (customerIndex == -1) {
        cout << "Customer not found." << endl;
        return;
    }
    if (customerIndex!=-1) //if one party has does an account a joint account can be made
    {
        string lName1, lName2;
        cout << "Enter customers Last name: ";
        cin >> lName1;
        cout << "Enter secondary customers Last name; ";
        cin >> lName2;
        if (lName1 == lName2) //if they have matching last names
        {
            cout << "Eligible to create joint accounts";
            cout << "Verify marriage license";
            createSavingAccount(); // create the joint account
        }
        else
        {
            cout << "Inelibile to create joint accounts";
        }
    }
}
void testFunctionChecking()
{
    const int NUM_OF_ACCOUNT = 5;
    Customer customerList[NUM_OF_ACCOUNT]; // creating an array to store customers' information
    SavingAccount savingAccount[NUM_OF_ACCOUNT]; // array for saving account
    CheckingAccount checkingAccount[NUM_OF_ACCOUNT]; //array for checking account
    char ans;
    int index = 0;
    cout << "Do you want to create a joint account?: ";
    cin >> ans;
    while(cin.fail()){
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Bad data, try again." << endl;
        cout << "Do you want to create a joint account?: ";
        cin >> ans;
    }
    if (ans == 'y' || ans == 'Y')
    {
        jointAccountChecking(&checkingAccount[index], &customerList[index], NUM_OF_ACCOUNT);
       
    }
}


// Functions to help to find an empty index and account
// ====================================================
int getSavingAccountIndex(string _phone, string _lName){
    for (int i = 0; i < NUM_OF_ACCOUNT; i++) {
        if ((savingAccount[i].getAccountCustomer1()->getPhone() == _phone && savingAccount[i].getAccountCustomer1()->getLname() == _lName) || (savingAccount[i].getAccountCustomer2()->getPhone() == _phone && savingAccount[i].getAccountCustomer2()->getLname() == _lName)) {
            return i;
        }
    }
    return -1;
}

int getCheckingAccountIndex(string _phone, string _lName){
    for (int i = 0; i < NUM_OF_ACCOUNT; i++) {
        if ((checkingAccount[i].getAccountCustomer1()->getPhone() == _phone && checkingAccount[i].getAccountCustomer1()->getLname() == _lName) || (checkingAccount[i].getAccountCustomer2()->getPhone() == _phone && checkingAccount[i].getAccountCustomer2()->getLname() == _lName)){
            return i;
        }
    }
    return -1;
}

int getNextEmptyCheckingAccountIndex() {
    for (int i = 0; i < NUM_OF_ACCOUNT; i++) {
        if (checkingAccount[i].getID() == 0) {
            return i;
        }
    }
    return -1;
}

int getNextEmptySavingAccountIndex(int id){
    for (int i = 0; i < NUM_OF_ACCOUNT; i++) {
        if (savingAccount[i].getID() == 0) {
            return i;
        }
    }
    return -1;
}

int getNextEmptyCustomerListIndex(int id){
    for (int i = 0; i < (NUM_OF_ACCOUNT*2); i++) {
        if (customerList[i].getLname() == "" && customerList[i].getFname() == "") {
            return i;
        }
    }
    return -1;
}
