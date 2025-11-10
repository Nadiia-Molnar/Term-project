#include "SavingAccount.h"
#include "CheckingAccount.h"
void menu();
void newCustomer();
void newAccount(int accountOpt);
void transferMenu();

int customerCounter = 0;
const int NUM_OF_CUST = 5;

Customer customerList[NUM_OF_CUST]; // creating an array
SavingAccount savingAccount[NUM_OF_CUST]; // array for saving account
CheckingAccount checkingAccount[NUM_OF_CUST]; //array for checking account


int main()
{
    string _fName, _lName, _address, _phone, _email;
    char ans;
    int opt = 0;
    
    menu();
    cin >> opt;
    
    while (opt != 6)
    {
        switch (opt)
        {
            case 1:
                //create checking
                cout << "Do you have an account(Y or N)?: " ;
                cin >> ans;
                if (ans == 'Y' || ans == 'y')
                {
                    cout << "Perfect! Can you provide your last name please: "; // continue creating checking
                    cin >> _lName;
                    cout << "Can you provide your phone number please: ";
                    cin >> _phone;
                    
                    //added
                    // create a checking account funct. to be created
                    newAccount(opt); // incomplete type void error?
                }
                else if (ans == 'N' || ans == 'n')
                {
                    //create a customer
                    newCustomer();
                    newAccount(opt);
                    //create a checking account. This will be a void function that takes in an arguement which indicates which account to be created
                }
                else{
                    cout << "Error, incorrect input. Try again!" << endl;
                }
                break;
            case 2:
                //create saving
                cout << "Does customer have an account? (Y or N)";
                cin >> ans;
                if (ans == 'Y' || ans == 'y')
                {
                    newAccount(opt);
                    cout << "" << endl; // continue creating checking
                }
                else
                {
                    newCustomer();
                }
                break;
            case 3:
                // view account info
                for (int i = 0; i < NUM_OF_CUST; i++)
                {
                    cout << customerList[i].getFname() << endl;
                    cout << customerList[i].getLname() << endl;
                    cout << customerList[i].getPhone() << endl;
                    cout << customerList[i].getEmail() << endl;
                    cout << customerList[i].getAddress() << endl;
                }
                
                customerList[NUM_OF_CUST].PrintInfo();
                //                Customer::PrintInfo;  //you have to provide the variable.PrintInfo();
                //                Account::PrintInfo;
                //
                break;
            case 4:
                //modify or delete the account
                char opt;
                cout << "Do you want to delete or modify the account(m - modify, d - delete): ";
                cin >> opt;
                if(opt == 'd' || opt == 'D'){
                    
                }
                break;
            case 5:
                // transfer between accounts
                break;
            case 6:
                //exit the program
                cout << "Exiting......" << endl;
                break;
        }
        
        
        cout << endl;
        cout << endl;
        cout << endl;
        cout << endl;
        cout << endl;
        cout << endl;
        //cout << "========== practice ===============";
        Customer customerList[] = {Customer("Liz", "Lawton", "205 Apple ST.", "904-568-4398", "bob@gmail.com"), Customer("Karrie", "Skowyra", "495 orange st.", "589-325-0934", "Kskowyra@gmail.com")};
        for (int i=0; i < NUM_OF_CUST; i++){
            customerList[i].PrintInfo();
        }
        system("pause");
        return 0;

    }
}

void menu(){
    //display the manu
        cout << "1. Create a checking account." << endl;
        cout << "2. Create a saving account." << endl;
        cout << "3. View account information." << endl;
        cout << "4. Modify or delete the account." << endl;
        cout << "5. Transfer between accounts." << endl;
        cout << "6. Exit the program." << endl;
        cout << "Please select between the following options(1-6): ";
}


void newCustomer(){
    string _fName;
    string _lName;
    string _address;
    string _phone;
    string _email;
    
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
    
    //create a bool variable to check if all values are faulse, and then at the end
    
    //check if the customer with the same last name and the phone number alredy exist
    for (int i = 0; i < NUM_OF_CUST; i++)
    {
        if (customerList[i].getPhone() == _phone &&
            customerList[i].getLname() == _lName)
        {
            cout << "There is an existing account with the folowing " << _lName << " and " << _phone << endl;
            //make sure that account is yours and keep working with it
        }
        else
        {
            //create an account we are using this counter because it matches with the index
            customerList[customerCounter].setFname(_fName);
            customerList[customerCounter].setLname(_lName);
            customerList[customerCounter].setPhone(_phone);
            customerList[customerCounter].setAddress(_address);
            customerList[customerCounter].setEmail(_email);
            
            //keep track of numbers of customers
            customerCounter=customerCounter+1;
        }
    }
    //        //create a new account
    //        else if (customerList[i].getPhone() == ""){
    //            customerList[i].setFname(_fName);
    //            customerList[i].setLname(_lName);
    //            customerList[i].setPhone(_phone);
    //            customerList[i].setEmail(_email);
    //            customerList[i].setAddress(_address);
    //
    //            //keep track of numbers of customers
    //            customerCounter=customerCounter+1;
    //        }
    
}

void newAccount(int accountOpt) //this variable tells which account the customer wants to create
{
    //create ID number, add a balance

    cout << "You will add specific account info here" << endl;
    cout << accountOpt;
}
void transferMenu()
{
    char ans;
    cout << "Do you wish to transfer? (Y or y to continue): ";
    cin >> ans;
    if (ans == 'Y' || ans == 'y')
    {
        cout << endl;
    }

}
void deleteAccount(){
    string _lName;
    string _address;
    string _phone;
    bool foundAccount = false;
    
    cout << "Enter last name: ";
    cin >> _lName;
    cout << "Enter phone number: ";
    cin >> _phone;
    cout << "Enter address: ";
    cin.ignore();
    getline(cin, _address);
    
    
    for (int i = 0; i < NUM_OF_CUST; i++){
        if(customerList
    }
}
