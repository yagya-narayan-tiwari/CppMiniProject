#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <windows.h>
#include <stdlib.h>

using namespace std;

void login();
void registr();
void forgot();

// ------------------------  Account  ---------------------------------


class Account
{
private:

    string AccountNo, Password, HolderName, PhoneNo, Address;
    double Balance;

    // account constructor

public:
    Account() : AccountNo(""), Password(""), Balance(0), HolderName(""), PhoneNo(""), Address("") {}

    //setter methods

    void setAccountNo(string id)
    {
        AccountNo = id;
    }

    void setHolderName(string hname)
    {
        HolderName = hname;
    }

    void setPhoneNo(string phone)
    {
        PhoneNo = phone;
    }
    void setAddress(string add)
    {
        Address = add;
    }

    void setPassword(string pw)
    {
        Password = pw;
    }

    void setBalance(double balance)
    {
        Balance = balance;
    }


//getter methods

    string getAccountNo() const
    {
        return AccountNo;
    }

    string getHolderName() const
    {
        return HolderName;
    }

    string getPhoneNo() const
    {
        return PhoneNo;
    }

    string getAddress() const
    {
        return Address;
    }

    string getPassword() const
    {
        return Password;
    }

    double getBalance() const
    {
        return Balance;
    }

    // -------------------- setting account details  -------------------

    void setAccountDetails()
    {
        system("cls");  // window.h se handled
        string AccountNo, Password, HolderName, PhoneNo, Address;
        double Balance;

        cout << "\tEnter Account Holder Name    :       ";
        cin >> HolderName;
        setHolderName(HolderName);
        // cin.ignore();
        cout << "\tEnter Account Number    :     ";
        // getline(cin, AccountNo);
        cin >> AccountNo;
        setAccountNo(AccountNo);
        cout << "\tEnter Account Password   :     ";
        // getline(cin, Password);
        cin >> Password;
        setPassword(Password);
        cout << "\tEnter Phone Number   :       ";
        // getline(cin, PhoneNo);
        cin >> PhoneNo;
        setPhoneNo(PhoneNo);
        cout << "\tEnter Address    :       ";
        // getline(cin, Address);
        cin >> Address;
        setAddress(Address);
    }

    // Print account details
    void printDetails() const
    {
        cout << "\tHolder Name  :       " << HolderName << endl;
        cout << "\tAccount No   :       " << AccountNo << endl;
        cout << "\tPhone No     :       " << PhoneNo << endl;
        cout << "\tAddress      :       " << Address << endl;
        cout << "\tBalance      :       " << Balance << endl;
    }
};





// ------------------------------------  Bank ---------------------------------------



class Bank
{
private:

    vector<Account> accounts;  // 

public:
    // constructor

    Bank() {}

    // -------------------------------- opening the account -----------------------------

    void openAccount(const Account &account)
    {
        accounts.push_back(account); // Add account to vector
        saveAccountsToFile();        // Save accounts to file after adding new account
        cout << "\tAccount created successfully!" << endl;
        cout << "\tWelcome to the State Bank Of CDAC :) " << endl;
        Sleep(2000);
    }

    // -----------------------  method to Add cash  -----------------------------

    void addCash(const string &accNo, double amount)
    {
        for (Account &acc : accounts)
        {
            if (acc.getAccountNo() == accNo)
            {
                acc.setBalance(acc.getBalance() + amount); // Add amount to account balance
                saveAccountsToFile();                      // Save accounts to file after updating balance
                cout << "\tMoney Deposited Successfully!" << endl;
                Sleep(2000); // windows.h se handled
                return;
            }
        }
        cout << "Account not found!" << endl;
        Sleep(2000);
    }

    //    -----------------  method to widthdrwal money ------------------

    void withdrawCash(const string &accNo, double amount)
    {
        for (Account &acc : accounts)
        {
            if (acc.getAccountNo() == accNo)
            {
                if (acc.getBalance() >= amount)
                {
                    acc.setBalance(acc.getBalance() - amount);
                    saveAccountsToFile();
                    cout << "\tCash withdrawn successfully!" << endl;
                    Sleep(2000);
                }
                else
                {
                    cout << "\tInsufficient balance :( " << endl;
                }
                Sleep(2000);
                return;
            }
        }
        cout << "\tAccount not found!" << endl;
    }

    // --------------------------------  transfer cash --------------------

    void transferMoney(const string &denaWalaAccNo, double amount)
    {
        string leneWalaAccNo;
        cout << "\tEnter receiver Account Number: ";
        cin >> leneWalaAccNo;

        bool senderFound = false;
        bool receiverFound = false;

        // checking dene wala account hai ya nahi

        for (Account &acc : accounts)
        {
            if (acc.getAccountNo() == denaWalaAccNo)
            {
                if (acc.getBalance() < amount)
                {
                    cout << "\tInsufficient balance in sender's account!" << endl;
                    Sleep(2000);
                    return;
                }
                acc.setBalance(acc.getBalance() - amount);
                senderFound = true;
                break;
            }
        }

        if (!senderFound)
        {
            cout << "\tSender's account not found!" << endl;
            Sleep(2000);
            return;
        }

        // checking for the lenawalaAccount

        for (Account &acc : accounts)
        {
            if (acc.getAccountNo() == leneWalaAccNo)
            {
                acc.setBalance(acc.getBalance() + amount);
                receiverFound = true;
                break;
            }
        }

        if (!receiverFound)
        {
            cout << "\tReceiver's account not found!" << endl;
            // ager lene wala nahi mila to dene wale ke paise wapis karege

            for (Account &acc : accounts)
            {
                if (acc.getAccountNo() == denaWalaAccNo)
                {
                    acc.setBalance(acc.getBalance() + amount);
                    break;
                }
            }
            Sleep(2000);
            return;
        }

        saveAccountsToFile();
        cout << "\tMoney transferred successfully!" << endl;
        Sleep(2000);
    }

    // --------------------------  printing all accounts -------------------------------------

    void printAllAccounts() const
    {
        for (const Account &acc : accounts)
        {
            acc.printDetails();
            cout << endl;
        }
        
    }

    // Save accounts to file

    void saveAccountsToFile() const
    {
        ofstream outfile("E:/CppMiniProject/BankData/Account.txt");
        if (!outfile)
        {
            cout << "\tError: File can't be opened!" << endl;
            return;
        }

        for (const Account &acc : accounts)
        {
            outfile << "\tAccount No    :   " << acc.getAccountNo() << endl;
            outfile << "\tHolder Name   :  " << acc.getHolderName() << endl;
            outfile << "\tPhone No  :  " << acc.getPhoneNo() << endl;
            outfile << "\tAddress   :  " << acc.getAddress() << endl;
            // Update balance only if it's changed
            double currentBalance = getCurrentBalance(acc.getAccountNo());
            outfile << "\tBalance:  " << currentBalance << endl;
            outfile << endl;
        }
        outfile.close();
    }

    // Get current balance for the given account number

    double getCurrentBalance(const string &accNo) const
    {
        for (const Account &acc : accounts)
        {
            if (acc.getAccountNo() == accNo)
            {
                return acc.getBalance();
            }
        }
        return 0; // Return 0 if account is not found
    }
};


// --------------------------------- Bank class end -------------------------

int menuList()
{
    // system("cls");
    int choice;
    cout << "\t **************************************************** " << endl;
    cout << "\t             Welcome to State Bank Of CDAC          " << endl;
    cout << "\t **************************************************** " << endl;
    cout << "\t  How Can I Help You :)  " << endl;
    cout << "\t-------------------------" << endl;
    cout << "\t0.   Exit. " << endl;
    cout << "\t1.   Open New Account. " << endl;
    cout << "\t2.   Deposite Money. " << endl;
    cout << "\t3.   Withdraw Money. " << endl;
    cout << "\t4.   Transfer Money. " << endl;
    cout << "\t5.   Print Account Details. " << endl;
    cout<<endl<<endl;
    cout << "\tWhat do you want , please enter you choice :   ";
    cin >> choice;
    return choice;
}



main()
{

    // ---------------------------- login & registration -----------------------------------

    int option;

    cout << "\t **************************************************** " << endl;
    cout << "\t                   Welcome to Login Page              " << endl;
    cout << "\t **************************************************** " << endl;
    cout << endl;
    cout << "\t  -----------    MENU    -----------\n\n";
    cout << "\t1.REGISTER AS BANKER" << endl;
    cout << "\t2.LOGIN" << endl;
    cout << "\t3.FORGOT PASSWORD (or) USERNAME" << endl;
    cout << "\t4.Exit" << endl;
    cout << "\n\tEnter your choice :    ";
    cin >> option;
    cout << endl;
    switch (option)
    {
    case 1:
        registr();
        break;

    case 2:
        login();
        break;

    case 3:
        forgot();
        break;

    case 4:
        cout << "\tThank You for joining State Bank Of CDAC !!" << endl;
        break;

    default:
        system("cls");
        cout << "\tYou've made a mistake , Try again..\n"
             << endl;
        main();
    }

    // return 0;
}

// ------------------------------------------------------

// Login and registration :

void login()
{

    Bank bank;
    int choice;
    Account acc;
    string accNo;

    int count;
    string user, pass, u, p;
    system("cls");
    cout << "\tplease enter the following details - " << endl;
    cout << "USERNAME :     ";
    cin >> user;
    cout << "PASSWORD :     ";
    cin >> pass;

    ifstream input("E:/CppMiniProject/UserData/UserData.txt");
    while (input >> u >> p)
    {
        if (u == user && p == pass)

        {
            count = 1;
            system("cls");
        }
    }
    input.close();

    if (count == 1)
    {
        cout << "\n\tHello,  " << user << "\n\t< LOGIN SUCCESSFUL >\n\tThanks for logging in..\n";
        cin.get();
        cin.get();
        while ((choice = menuList()) != 0)
        {
            switch (choice)
            {
            case 1:
                acc.setAccountDetails();
                bank.openAccount(acc);
                break;

            case 2:
                double amt;
                cout << "\tEnter Account Number:  ";
                cin >> accNo;
                cout << "\tEnter Amount to Deposit:   ";
                cin >> amt;
                bank.addCash(accNo, amt);
                break;

            case 3:
                double amount;
                cout << "\tEnter Account Number :    ";
                cin >> accNo;
                cout << "\tEnter Amount to Withdraw :    ";
                cin >> amount;
                bank.withdrawCash(accNo, amount);
                break;


                //  -------------------- transfer money  ---------------------
            case 4:
                double paisa;
                cout << "\tEnter Account Number :    ";
                cin >> accNo;
                cout << "\tEnter Amount to Transfer :    ";
                cin >> paisa;
                bank.transferMoney(accNo , paisa);
                break;
                // -----------------------------------------------------

                
            case 5:
                bank.printAllAccounts();
                break;


            default:
                cout << "\tInvalid choice :( " << endl;
                break;
            }
        }

        // cout << "Press Enter to exit...";
        // cin.ignore();
        // cin.get();
        main();
    }
    else
    {
        cout << "\nLOGIN ERROR\nPlease check your username and password\n";
        main();
    }
}

void registr()
{

    string reguser, regpass;
    system("cls");
    cout << "\tEnter the username :       ";
    cin >> reguser;
    cout << "\n\tEnter the password :     ";
    cin >> regpass;

    ofstream reg("E:/CppMiniProject/UserData/UserData.txt", ios::app);
    reg << reguser << ' ' << regpass << endl;
    cout << endl;
    system("cls");
    cout << "\n\tRegistration Sucessful\n";
    main();
}

void forgot()
{
    int ch;
    system("cls");
    cout << "\tForgotten ? We're here for help\n";
    cout << "\t1.Search your id by username" << endl;
    cout << "\t2.Search your id by password" << endl;
    cout << "\t3.Main menu" << endl;
    cout << "\tEnter your choice :        ";
    cin >> ch;
    switch (ch)
    {
    case 1:
    {
        int count = 0;
        string searchuser, su, sp;
        cout << "\n\tEnter your remembered username :       ";
        cin >> searchuser;

        ifstream searchu("E:/CppMiniProject/UserData/UserData.txt");
        while (searchu >> su >> sp)
        {
            if (su == searchuser)
            {
                count = 1;
            }
        }
        searchu.close();
        
        if (count == 1)
        {
            cout << "\n\n\tBadhaii Ho !!, account found\n";
            cout << "\n\tYour password is :       " << sp;
            cin.get();
            cin.get();
            system("cls");
            main();
        }
        else
        {
            cout << "\n\tSorry, Your userID is not found in our database\n";
            cout << "\n\tPlease kindly contact your system administrator for more details \n";
            cin.get();
            cin.get();
            main();
        }
        break;
    }
    case 2:
    {
        int count = 0;
        string searchpass, su2, sp2;
        cout << "\n\tEnter the remembered password :      ";
        cin >> searchpass;

        ifstream searchp("E:/CppMiniProject/UserData/UserData.txt");
        while (searchp >> su2 >> sp2)
        {
            if (sp2 == searchpass)
            {
                count = 1;
            }
        }
        searchp.close();
        if (count == 1)
        {
            cout << "\n\tYour password is found in the database \n";
            cout << "\n\tYour Id is :   " << su2;
            cin.get();
            cin.get();
            system("cls");
            main();
        }
        else
        {
            cout << "\tSorry, We cannot found your password in our database \n";
            cout << "\n\tkindly contact your administrator for more information\n";
            cout << "\tEnter Any Key to continue...." << endl;
            cin.get();
            cin.get();
            main();
        }

        break;
    }

    case 3:
    {
        cin.get();
        main();
    }
    default:
        cout << "\tSorry, You entered wrong choice. Kindly try again" << endl;
        forgot();
    }
}






























