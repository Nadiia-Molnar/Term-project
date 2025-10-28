#include "Customer.h"
void menu();

int main() {
    int opt;
    menu();
    cin >> opt;
     
    ////while (opt != 6)
    //{
     
    //}
    Customer cs1("Liz", "Lawton", " 205 Apple ST.", "904-568-4398", "bob@gmail.com"), cs2 ("karrie", "Smith", "495 orange st.", "589-325-0934", "Ksmith@gmail.com");
    cs1.PrintInfo();
     
    return 0;
}

void menu(){
    cout << "Please select between the following options(1-6): " << endl;
    cout << "1. Create a checking account. 2) Create a saving account. 3) View account information. 4) Modify or deleting accounts.5) Transfer between accounts. 6) Exit" << endl;
}
