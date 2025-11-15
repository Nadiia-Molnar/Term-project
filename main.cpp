#include "SavingAccount.h"
#include "CheckingAccount.h"
#include <cstdlib>  //For srand(), rand()
#include <ctime>    //For time()

//Function prototypes
void menu();
int existingCustomer(bool);
int createNewCustomer(string, string, string);
void createCheckingAccount(int, int);
void createSavingAccount(int, int);
void viewInfo(int);
void deleteAccount();
void modifyAccount();
void transferMoney();
void jointAccountChecking();
void jointAccountSavings();
// Helper function prototypes
int getSavingAccountIndex(string, string);
int getCheckingAccountIndex(string, string);
int getNextEmptyCheckingAccountIndex();
int getNextEmptySavingAccountIndex();
int getNextEmptyCustomerListIndex();

//Global Constants and Variables
const int INVALID_INDEX = -1;                // Constant used to indicate invalid index
const int NUM_OF_ACCOUNT = 5;                // Maximum number of saving/checking accounts
int ID_COUNTER = (rand() % 100) + 100;       // Counter for assigning unique account IDs
Customer customerList[NUM_OF_ACCOUNT*2];     //Array to store customers' information
SavingAccount savingAccount[NUM_OF_ACCOUNT]; //Array for saving account
CheckingAccount checkingAccount[NUM_OF_ACCOUNT]; //Array for checking account

int main()
{
    string _fName, _lName, _address, _phone, _email;
    int opt;

    // Main loop
    do{
        menu();
        cin >> opt;
        cout << endl;
        while(cin.fail() || opt>7 || opt<1){
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input. Please select a number between 1 and 7: ";
            cin >> opt;
        }
        
        
        switch(opt){
                //Create checking account
            case 1: {
                int customerIndex = existingCustomer(true);
                createCheckingAccount(customerIndex, INVALID_INDEX);
                break;
            }
                //Create a saving account
            case 2: {
                int customerIndex = existingCustomer(true);
                createSavingAccount(customerIndex, INVALID_INDEX);
                break;
            }
                //View account info
            case 3: {
                int customerIndex = existingCustomer(false);
                viewInfo(customerIndex);
                break;
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
                //Create a join account
            case 6:
            {
                char ans;
                //Ask the user what action they want to create
                cout << "Do you want to create a joint saving account or a joint checking account (C/S)?: ";
                cin >> ans;
                while(cin.fail()){
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << "Bad data, try again." << endl;
                    cout << "Do you want to create a joint saving account or a joint checking account (C/S)?: ";
                    cin >> ans;
                }
                
                //If user chooses saving
                if (ans == 's' || ans == 'S'){
                    jointAccountSavings();
                }
                //If user chooses checking
                else if (ans == 'c' || ans == 'C'){
                    jointAccountChecking();
                }
                //If user enters an invalid option
                else{
                    cout << "Invalid option." << endl;
                }
                break;
            }
                //Exit the program
            case 7:{
                cout << "Exiting program. Goodbye!"<< endl;
                break;
            }
        }
        cout << "\n\n";
        
    }while(opt<7 && opt>=1);
    
//    system("pause");
    return 0;
}

void menu(){
    //display the menu
    cout << "\n=============================================" << endl;
    cout << "           WELCOME TO THE BANK        " << endl;
    cout << "=============================================" << endl;
    cout << "1.  Create a Checking Account" << endl;
    cout << "2.  Create a Saving Account" << endl;
    cout << "3.  View Account Information" << endl;
    cout << "4.  Modify or Delete an Account" << endl;
    cout << "5.  Transfer Money" << endl;
    cout << "6.  Create a Joint Account" << endl;
    cout << "7.  Exit Program" << endl;
    cout << "=============================================" << endl;
    cout << "Please enter your choice (1-7): ";
}

// Function: Checks if a customer already exists in the system
int existingCustomer(bool needNewCustomer){
    string _fName, _lName, _phone;
    int customerIndex = INVALID_INDEX;
    
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
void createCheckingAccount(int customerIndex1, int customerIndex2){
    
    int CAIndex1 = INVALID_INDEX;
    int CAIndex2 = INVALID_INDEX;
    
    //If customer already has a checking account
    if (customerIndex1 != INVALID_INDEX) {
        CAIndex1 = getCheckingAccountIndex(customerList[customerIndex1].getPhone(), customerList[customerIndex1].getLname());
    }
    if(CAIndex1 != INVALID_INDEX && customerIndex2 == INVALID_INDEX){
        cout << "\nThere is an existing checking account with the following information.\n" << endl;
        checkingAccount[CAIndex1].PrintInfo();
        return;
    } //Joint account adds to this one
    else if (CAIndex1 != INVALID_INDEX && customerIndex2 != INVALID_INDEX) {
        cout << "\nA checking account already exists for this customer: " << customerList[customerIndex1].getFname() << " " <<  customerList[customerIndex1].getLname() << endl;
        if(CAIndex1 != INVALID_INDEX && customerIndex2 == INVALID_INDEX){
            cout << "A new one will be added as a joint account." << endl;
        }
        
    }
    //If customer already has a checking account
    if (customerIndex2 != INVALID_INDEX) {
        CAIndex2 = getCheckingAccountIndex(customerList[customerIndex2].getPhone(), customerList[customerIndex2].getLname());
    }
    if(CAIndex2 != INVALID_INDEX && customerIndex1 == INVALID_INDEX){
        cout << "\nThere is an existing checking account with the following information.\n" << endl;
        checkingAccount[CAIndex2].PrintInfo();
        return;
    }//Joint account adds to this one
    else if (CAIndex2 != INVALID_INDEX && customerIndex1 != INVALID_INDEX && (CAIndex1 != CAIndex2)) {
        cout << "\nA checking account already exists for this customer: " << customerList[customerIndex2].getFname() << " " <<  customerList[customerIndex2].getLname() << endl;
        if(CAIndex2 != INVALID_INDEX && customerIndex1 == INVALID_INDEX){
            cout << "A new one will be added as a joint account." << endl;
        }
        
    }//Both customers already have their own checking accounts
    if (CAIndex1 != INVALID_INDEX && CAIndex2 != INVALID_INDEX && CAIndex1 != CAIndex2) {
        cout << "\nYou cannot create a joint checking account because each customer already has a checking account:" << endl;
        checkingAccount[CAIndex1].PrintInfo();
        checkingAccount[CAIndex2].PrintInfo();
        
        cout << "Please delete one of the existing accounts first." << endl;
        return;
    }
    else if (CAIndex1 != INVALID_INDEX && CAIndex2 != INVALID_INDEX && CAIndex1 == CAIndex2) {
        cout << "\nThese customers already share a joint checking account.\n";
        checkingAccount[CAIndex1].PrintInfo();
    }
    
    int SAIndex1 = INVALID_INDEX;
    int SAIndex2 = INVALID_INDEX;
    
    if (customerIndex1 != INVALID_INDEX) {
        SAIndex1 = getSavingAccountIndex(customerList[customerIndex1].getPhone(), customerList[customerIndex1].getLname());
    }
    if (customerIndex2 != INVALID_INDEX) {
        SAIndex2 = getSavingAccountIndex(customerList[customerIndex2].getPhone(), customerList[customerIndex2].getLname());
    }
    
    // Customer has a saving account but no checking account
    if(SAIndex1 != INVALID_INDEX || SAIndex2 != INVALID_INDEX) {
        char ans;
        string customerInfoCA = "";
        
        if (SAIndex1 != INVALID_INDEX) {
            customerInfoCA = customerList[customerIndex1].getFname() + " " + customerList[customerIndex1].getLname();
        }
        if (SAIndex2 != INVALID_INDEX) {
            customerInfoCA = customerList[customerIndex2].getFname() + " " + customerList[customerIndex2].getLname();
        }
        cout << "\nA saving account already exists for this customer: " << customerInfoCA << endl;
        cout << "\nDo you still want to create a new checking account(Enter Y for yes or N for no)?: ";
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
            cout << "\nNo checking account was created.\n" << endl;
            return;
        }
    }
    
    int newCAIndex = INVALID_INDEX;
    if(CAIndex1 != INVALID_INDEX){
        newCAIndex = CAIndex1;
    }
    else if(CAIndex2 != INVALID_INDEX){
        newCAIndex = CAIndex2;
    }
    else {
        newCAIndex = getNextEmptyCheckingAccountIndex();
    }
    
    if (customerIndex1 != INVALID_INDEX) {
        checkingAccount[newCAIndex].setAccountCustomer1(&customerList[customerIndex1]);
    }
    if (customerIndex2 != INVALID_INDEX) {
        checkingAccount[newCAIndex].setAccountCustomer2(&customerList[customerIndex2]);
    }
    
    int newID = checkingAccount[newCAIndex].getID();
    if (CAIndex1 == INVALID_INDEX && CAIndex2 == INVALID_INDEX) {
        //Generate unique ID
        newID = ID_COUNTER + 1;
        ID_COUNTER++;
        checkingAccount[newCAIndex].setID(newID);
    }
    
    //Deposit setup
    double firstDeposit, limit;
    cout << "Enter your first deposit amount: ";
    cin >> firstDeposit;
    while(cin.fail() || firstDeposit <= 0){
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Bad data, try again." << endl;
        cout << "The amount must be positive number. Try again: ";
        cin >> firstDeposit;
    }
    checkingAccount[newCAIndex].setBalance(checkingAccount[newCAIndex].getBalance() + firstDeposit);
    
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
    checkingAccount[newCAIndex].setOverDraftLimit(limit);
    
    //Confirm successful creation
    string customerInfo1 = "";
    string customerInfo2 = "";
    
    if (customerIndex1 != INVALID_INDEX) {
        customerInfo1 = customerList[customerIndex1].getFname() + " " + customerList[customerIndex1].getLname();
    }
    if (customerIndex2 != INVALID_INDEX) {
        customerInfo2 = " and " + customerList[customerIndex1].getFname() + " " + customerList[customerIndex1].getLname();
    }
    cout << "\nNew checking account created successfully for " << customerInfo1 << customerInfo2 << "!\n" << endl;
    checkingAccount[newCAIndex].PrintInfo();
    cout << setw(20) << left << "Over Draft Limit" << setw(50) << left << checkingAccount[newCAIndex].getOverDraftLimit() << endl;
}

//Function: Creates a new saving account for a customer
void createSavingAccount(int customerIndex1, int customerIndex2){
    
    int SAIndex1 = INVALID_INDEX;
    int SAIndex2 = INVALID_INDEX;
    
    //If customer alresdy has a saving account
    if (customerIndex1 != INVALID_INDEX) {
        SAIndex1 = getSavingAccountIndex(customerList[customerIndex1].getPhone(), customerList[customerIndex1].getLname());
    }
    if(SAIndex1 != INVALID_INDEX && customerIndex2 == INVALID_INDEX){
        cout << "\nThere is an existing saving account with the following information.\n" << endl;
        savingAccount[SAIndex1].PrintInfo();
        return;
    }//Joint account adds to this one
    else if (SAIndex1 != INVALID_INDEX && customerIndex2 != INVALID_INDEX) {
        cout << "\nA saving account already exists for this customer: " << customerList[customerIndex1].getFname() << " " <<  customerList[customerIndex1].getLname() << endl;
        cout << "\nA new one will be added as a joint account." << endl;
        
    }
    //If customer already has a checking account
    if (customerIndex2 != INVALID_INDEX) {
        SAIndex2 = getSavingAccountIndex(customerList[customerIndex2].getPhone(), customerList[customerIndex2].getLname());
    }
    if (SAIndex2 != INVALID_INDEX && customerIndex1 == INVALID_INDEX){
        cout << "\nThere is an existing saving account with the following information.\n" << endl;
        savingAccount[SAIndex2].PrintInfo();
        return;
    }//Joint account adds to this one
    else if (SAIndex2 != INVALID_INDEX && customerIndex1 != INVALID_INDEX && (SAIndex1!=SAIndex2)){
        cout << "\nA saving account already exists for this customer: " << customerList[customerIndex2].getFname() << " " <<  customerList[customerIndex2].getLname() << endl;
        cout << "\nA new one will be added as a joint account." << endl;
        
    }//Both customers already have their own checking accounts
    if (SAIndex1 != INVALID_INDEX && SAIndex2 != INVALID_INDEX && SAIndex1!=SAIndex2) {
        cout << "\nYou cannot create a joint checking account because each customer already has a saving account:" << endl;
        savingAccount[SAIndex1].PrintInfo();
        savingAccount[SAIndex2].PrintInfo();
        
        cout << "\nPlease delete one of the existing accounts first." << endl;
        return;
    }
    else if (SAIndex1 != INVALID_INDEX && SAIndex2 != INVALID_INDEX && SAIndex1==SAIndex2){
        cout << "\nThese customers already share a joint saving account.\n";
        savingAccount[SAIndex1].PrintInfo();
    }
    
    int CAIndex1 = INVALID_INDEX;
    int CAIndex2 = INVALID_INDEX;
    
    if (customerIndex1 != INVALID_INDEX) {
        CAIndex1 = getCheckingAccountIndex(customerList[customerIndex1].getPhone(), customerList[customerIndex1].getLname());
    }
    if (customerIndex2 != INVALID_INDEX) {
        CAIndex2 = getCheckingAccountIndex(customerList[customerIndex2].getPhone(), customerList[customerIndex2].getLname());
    }

    //Customer has a checking account but no saving account
    if(CAIndex1 != INVALID_INDEX || CAIndex2 != INVALID_INDEX) {
        char ans;
        string customerInfoSA = "";
        
        if (CAIndex1 != INVALID_INDEX) {
            customerInfoSA = customerList[customerIndex1].getFname() + " " + customerList[customerIndex1].getLname();
        }
        if (CAIndex2 != INVALID_INDEX) {
            customerInfoSA = customerList[customerIndex2].getFname() + " " + customerList[customerIndex2].getLname();
        }
        cout << "\nA checking account already exists for this customer: " << customerInfoSA << endl;
        cout << "\nDo you still want to create a new saving account(Enter Y for yes or N for no)?: ";
        cin >> ans;
        while(cin.fail()){
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Bad data, try again." << endl;
            cout << "Do you still want to create a new saving account(Enter Y for yes or N for no)?: ";
            cin >> ans;
        }

        // Exit to main menu
        if(ans != 'Y' && ans != 'y'){
            cout << "\nNo saving account was created.\n" << endl;
            return;
        }
    }
    
    int newSAIndex = INVALID_INDEX;
    if(SAIndex1 != INVALID_INDEX){
        newSAIndex = SAIndex1;
    }
    else if(SAIndex2 != INVALID_INDEX){
        newSAIndex = SAIndex2;
    }
    else {
        newSAIndex = getNextEmptySavingAccountIndex();
    }
    
    if (customerIndex1 != INVALID_INDEX) {
        savingAccount[newSAIndex].setAccountCustomer1(&customerList[customerIndex1]);
    }
    if (customerIndex2 != INVALID_INDEX) {
        savingAccount[newSAIndex].setAccountCustomer2(&customerList[customerIndex2]);
    }
    
    int newID = savingAccount[newSAIndex].getID();
    if (SAIndex1 == INVALID_INDEX && SAIndex2 == INVALID_INDEX) {
        //Generate unique ID
        newID = ID_COUNTER + 1;
        ID_COUNTER++;
        savingAccount[newSAIndex].setID(newID);
    }
    
    //Deposit setup
    double firstDeposit, rate;
    cout << "Enter initial deposit: ";
    cin >> firstDeposit;
    while(cin.fail() || firstDeposit <= 0){
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Bad data, try again." << endl;
        cout << "The amount must be positive number. Try again: ";
        cin >> firstDeposit;
    }
    savingAccount[newSAIndex].setBalance(savingAccount[newSAIndex].getBalance()+firstDeposit);
    
    //Interest rate setup
    cout << "Enter interest rate: ";
    cin >> rate;
    while(cin.fail() || rate <= 0){
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Bad data, try again." << endl;
        cout << "The interest rate must be positive number. Try again: ";
        cin >> rate;
    }
    savingAccount[newSAIndex].setInterestRate(rate);
    
    //Confirm successful creation
    string customerInfo1 = "";
    string customerInfo2 = "";
    
    if (customerIndex1 != INVALID_INDEX) {
        customerInfo1 = customerList[customerIndex1].getFname() + " " + customerList[customerIndex1].getLname();
    }
    if (customerIndex2 != INVALID_INDEX) {
        customerInfo2 = " and " + customerList[customerIndex2].getFname() + " " + customerList[customerIndex2].getLname();
    }
    
    cout << "\nNew saving account created successfully for "<< customerInfo1 << customerInfo2 << "!\n" << endl;
    savingAccount[newSAIndex].PrintInfo();
    cout << setw(20) << left << "Interest Rate" << setw(50) << left << savingAccount[newSAIndex].getInterestRate() << endl;
}

//Function: Display all information about a customer
void viewInfo(int index){
    //No matching customer was found.
    if (index == INVALID_INDEX){
        cout << "\nCustomer not found." << endl;
        return;
    }
    
    //Formatted header
    cout << endl;
    cout << "=============================================" << endl;
    cout << setw(15) << left << "Field" << setw(30) << left << "Information" << endl;
    cout << "---------------------------------------------" << endl;
    cout << setw(15) << left << "Name" << customerList[index].getFname() << " " << customerList[index].getLname() << endl;
    cout << setw(15) << left << "Phone" << setw(30) << left << customerList[index].getPhone() << endl;
    cout << setw(15) << left << "Email" << setw(30) << left << customerList[index].getEmail() << endl;
    cout << setw(15) << left << "Address" << setw(30) << left << customerList[index].getAddress() << endl;
    
    // Checking Account info
    int CAIndex = getCheckingAccountIndex(customerList[index].getPhone(), customerList[index].getLname());
    if (checkingAccount[CAIndex].getID() != 0){
        cout << endl;
        cout << "Checking Account:" << endl;
        cout << "---------------------------------------------" << endl;
        cout << setw(15) << left << "Account ID" << setw(30) << left << checkingAccount[CAIndex].getID() << endl;
        cout << setw(15) << left << "Balance" << setw(30) << left << checkingAccount[CAIndex].getBalance() << endl;
        cout << setw(15) << left << "Overdraft" << setw(30) << left << checkingAccount[CAIndex].getOverDraftLimit() << endl;
    }
    
    // Saving Account info
    int SAIndex = getSavingAccountIndex(customerList[index].getPhone(), customerList[index].getLname());
    if (savingAccount[SAIndex].getID() != 0){
        cout << endl;
        cout << "Saving Account:" << endl;
        cout << "---------------------------------------------" << endl;
        cout << setw(15) << left << "Account ID" << setw(30) << left << savingAccount[SAIndex].getID() << endl;
        cout << setw(15) << left << "Balance" << setw(30) << left << savingAccount[SAIndex].getBalance() << endl;
        cout << setw(15) << left << "Interest Rate" << setw(30) << left << savingAccount[SAIndex].getInterestRate() << endl;
    }
    
}

//Function: Deletes an account
void deleteAccount(){
    char ans;
    int customerIndex = existingCustomer(false); //Find the index of the existing customer

    //If customer does not exist
    if (customerIndex == INVALID_INDEX) {
        cout << "Customer not found." << endl;
        return;
    }
    
    //Delete checking account
    int CAIndex = getCheckingAccountIndex(customerList[customerIndex].getPhone(), customerList[customerIndex].getLname());
    if(CAIndex != INVALID_INDEX){
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
                cout << "You cannot delete this account because it has an outstanding overdraft balance. \nPlease pay off your debt before closing the account.\n" << endl;
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
    if(SAIndex != INVALID_INDEX){
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
            cout << "\nSaving account deleted successfully." << endl;
        }
        else{
            cout << "Account deletion canceled. No changes were made." << endl;
        }
    }
    
    //Delete all customer info
    cout << "\nDo you want to delete all your information completely?" << endl;
    cout << "Your checking and saving accounts will be deleted as well." << endl;
    cout << "Enter (Y for yes or N for n): ";
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
                cout << "\nYou cannot delete this account because it has an outstanding overdraft balance.\nPlease pay off your debt before closing the account.\n" << endl;
            }
            else{
                customerList[customerIndex].setFname("");
                customerList[customerIndex].setLname("");
                customerList[customerIndex].setPhone("");
                customerList[customerIndex].setEmail("");
                customerList[customerIndex].setAddress("");
                
                
                checkingAccount[CAIndex].setAll(0, 0.0, nullptr, nullptr, 0.0);
                savingAccount[SAIndex].setAll(0, 0.0, nullptr, nullptr, 0.0);
                
                cout << "\nAccount deleted successfully." << endl;
            }
        }
        else{
            cout << "\nAccount deletion canceled. No changes were made." << endl;
        }
        
    }

//Function: Modifies an account
void modifyAccount(){
    // Find the customer
    int customerIndex = existingCustomer(false);

    //If customer does not exist
    if (customerIndex == INVALID_INDEX) {
        cout << "\nCustomer not found." << endl;
        return;
    }
    
    //Modification menu
    int ans;
    cout << "\n=============================================\n";
    cout << "            MODIFY ACCOUNT MENU              \n";
    cout << "=============================================\n";
    cout << " Option    | Description                      \n";
    cout << "---------------------------------------------\n";
    cout << "    1      | Personal Information             \n";
    cout << "    2      | Checking Account Details         \n";
    cout << "    3      | Saving Account Details           \n";
    cout << "=============================================\n";
    cout << "Enter your choice (1-3): ";
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

            cout << "\nPersonal information updated successfully." << endl;
            break;
        }
        // Modify checking account
        case 2:
        {
            // Check if customer has a checking account
            int CAIndex = getCheckingAccountIndex(customerList[customerIndex].getPhone(), customerList[customerIndex].getLname());
            if (CAIndex == INVALID_INDEX){
                cout << "\nNo checking account found for this customer." << endl;
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
                cout << "\nChecking account updated successfully." << endl;
            }
            break;
        }
        // Modify saving account
        case 3:
        {
            int SAIndex = getSavingAccountIndex(customerList[customerIndex].getPhone(), customerList[customerIndex].getLname());
            if(SAIndex == INVALID_INDEX){
                cout << "\nNo saving account found for this customer." << endl;
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
                cout << "\nSaving account updated successfully." << endl;
            }
            break;
        }
        //Invalid choice
        default:
            cout << "\nInvalid choice." << endl;
    }
}

//Function: Transfer money
void transferMoney(){
    char ans;
    double amount;
    
    //Ask if the transfer is between the same customer's accounts
    cout << "\nDo you want to transfer money between your own accounts(Y or N)?: ";
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
        if (customerIndex == INVALID_INDEX){
            cout << "\nCustomer not found." << endl;
            return;
        }
        
        //Check if both accounts exist
        int CAIndex = getCheckingAccountIndex(customerList[customerIndex].getPhone(), customerList[customerIndex].getLname());
        int SAIndex = getSavingAccountIndex(customerList[customerIndex].getPhone(), customerList[customerIndex].getLname());
        if(CAIndex == INVALID_INDEX){
            cout << "\nYour checking account does not exist." << endl;
            return;
        }
        else if (SAIndex == INVALID_INDEX){
            cout << "\nYour saving account does not exist." << endl;
            return;
        }

        //Ask from which account the transfer should come
        cout << "\nTransfer from checking or from saving(C/S)?: ";
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
            cout << "\nEnter amount to transfer: ";
            cin >> amount;
            while(cin.fail()){
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Bad data, try again." << endl;
                cout << "Enter a positive number for the amount to transfer: ";
                cin >> ans;
            }
            if (amount > 0 && amount <= (checkingAccount[CAIndex].getBalance()+checkingAccount[CAIndex].getOverDraftLimit())){
                checkingAccount[CAIndex].WithdrawMoney(amount);
                savingAccount[SAIndex].DepositMoney(amount);
                cout << "\nTransfer successful!" << endl;
            }
            else{
                cout << "\nInvalid amount or insufficient funds." << endl;
            }
        }
        //Transfer from saving to checking
        else if (ans == 's' || ans == 'S') {
            cout << "\nEnter amount to transfer: ";
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
                cout << "\nTransfer successful!" << endl;
            }
            else{
                cout << "\nInvalid amount or insufficient funds." << endl;
            }
        }
        else{
            cout << "\nInvalid option." << endl;
            return;
        }
    }
    //Transfer to another customer
    else if (ans == 'N' || ans == 'n'){
        cout << "\nEnter your account info: " << endl;
        int senderIndex = existingCustomer(false);
        if (senderIndex == INVALID_INDEX) {
            cout << "Sender not found." << endl;
            return;
        }

        cout << "\nEnter recipient's account info: " << endl;
        int recipientIndex = existingCustomer(false);
        if (recipientIndex == INVALID_INDEX) {
            cout << "Recipient not found." << endl;
            return;
        }

        cout << "\nWhich account to transfer from(C/S)?: ";
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
        if ((ans == 'c' || ans == 'C') && senderCAIndex != INVALID_INDEX){
            cout << "\nEnter amount to transfer: ";
            cin >> amount;
            while(cin.fail()){
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Bad data, try again." << endl;
                cout << "Enter a positive number for the amount to transfer: ";
                cin >> ans;
            }
            if (amount > 0 && amount <= (checkingAccount[senderCAIndex].getBalance()+checkingAccount[senderCAIndex].getOverDraftLimit())) { //idk if i hae to check all of these
                //Deposit to recipient's checking or saving account
                if (recipientCAIndex != INVALID_INDEX){
                    checkingAccount[senderCAIndex].WithdrawMoney(amount);
                    checkingAccount[recipientCAIndex].DepositMoney(amount);
                }
                else if(recipientSAIndex != INVALID_INDEX) {
                    checkingAccount[senderCAIndex].WithdrawMoney(amount);
                    savingAccount[recipientSAIndex].DepositMoney(amount);
                }
                else{
                    cout << "\nRecipient has no account to receive money!" << endl;
                    return;
                }
                cout << "\nTransfer successful!" << endl;
            }
            else {
                cout << "\nInvalid amount or insufficient funds." << endl;
            }
        }
        //Transfer from sender's saving account
        else if((ans == 's' || ans == 'S') && senderSAIndex != INVALID_INDEX){
            cout << "\nEnter amount to transfer: ";
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
                if (recipientCAIndex != INVALID_INDEX){
                    savingAccount[senderSAIndex].WithdrawMoney(amount);
                    checkingAccount[recipientCAIndex].DepositMoney(amount);
                }
                else if (recipientSAIndex != INVALID_INDEX){
                    savingAccount[senderSAIndex].WithdrawMoney(amount);
                    savingAccount[recipientSAIndex].DepositMoney(amount);
                }
                else{
                    cout << "\nRecipient has no account to receive money!" << endl;
                    return;
                }
                cout << "\nTransfer successful!" << endl;
            }
            else{
                cout << "\nInvalid amount or insufficient funds." << endl;
            }
        }
        else{
            cout << "\nYour selected account does not exist." << endl;
        }
    }
    else{
        cout << "Invalid choice." << endl;
    }
}

//Function: Creates a joint checking account for two customers
void jointAccountChecking()
{
    int customerIndex1 = existingCustomer(true);
    
    cout << "\nEnter second customers information.\n";
    int customerIndex2 = existingCustomer(true);
    createCheckingAccount(customerIndex1, customerIndex2);
}

//Function: Creates a joint saving account for two customers
void jointAccountSavings()
{
    int customerIndex1 = existingCustomer(true);
    
    cout << "Enter second customers information.\n";
    int customerIndex2 = existingCustomer(true);
    createSavingAccount(customerIndex1, customerIndex2);
}


// Functions to help to find an empty index and account
// ====================================================
int getSavingAccountIndex(string _phone, string _lName){
    for (int i = 0; i < NUM_OF_ACCOUNT; i++) {
        if(savingAccount[i].getAccountCustomer1() != nullptr && (savingAccount[i].getAccountCustomer1()->getPhone() == _phone && savingAccount[i].getAccountCustomer1()->getLname() == _lName)){
            return i;
        }
        else if (savingAccount[i].getAccountCustomer2() != nullptr && (savingAccount[i].getAccountCustomer2()->getPhone() == _phone && savingAccount[i].getAccountCustomer2()->getLname() == _lName)){
            return i;
        }
    }
    return INVALID_INDEX;
}

int getCheckingAccountIndex(string _phone, string _lName){
    for (int i = 0; i < NUM_OF_ACCOUNT; i++) {
        if(checkingAccount[i].getAccountCustomer1() != nullptr && (checkingAccount[i].getAccountCustomer1()->getPhone() == _phone && checkingAccount[i].getAccountCustomer1()->getLname() == _lName)){
            return i;
        }
        else if (checkingAccount[i].getAccountCustomer2() != nullptr && (checkingAccount[i].getAccountCustomer2()->getPhone() == _phone && checkingAccount[i].getAccountCustomer2()->getLname() == _lName)){
            return i;
        }
    }
    return INVALID_INDEX;
}

int getNextEmptyCheckingAccountIndex() {
    for (int i = 0; i < NUM_OF_ACCOUNT; i++) {
        if (checkingAccount[i].getID() == 0) {
            return i;
        }
    }
    return INVALID_INDEX;
}

int getNextEmptySavingAccountIndex(){
    for (int i = 0; i < NUM_OF_ACCOUNT; i++) {
        if (savingAccount[i].getID() == 0) {
            return i;
        }
    }
    return INVALID_INDEX;
}

int getNextEmptyCustomerListIndex(){
    for (int i = 0; i < (NUM_OF_ACCOUNT*2); i++) {
        if (customerList[i].getLname() == "" && customerList[i].getFname() == "") {
            return i;
        }
    }
    return INVALID_INDEX;
}
