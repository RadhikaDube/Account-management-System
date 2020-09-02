//
//  BankAccount_Radhika.cpp
//  FinalProject_Radhika
//
//  Created by Radhika Dube on 12/3/19.
//  Copyright © 2019 Radhika Dube. All rights reserved.
//

#include<iostream>
#include<cstdlib>
#include<string>
#include<time.h>
#include<fstream>
#include<sstream>
#include<map>
#include<iomanip>

#include"Account_Radhika.h"
#include"BankAccount_Radhika.h"

using namespace std;


//Default Constructor Definition
Bank_Account::Bank_Account()
{
    set_cashbalance();
    cash_balance = get_cashbalance();
    depositcash = 0;
    withdrawcash = 0;

}

//Default Destructor Definition
Bank_Account::~Bank_Account()
{

}

//View Account Balance
void Bank_Account::viewbalance()
{
    set_cashbalance();
    cash_balance = get_cashbalance();
    cout << "\n You have $" << cash_balance << " in your bank account\n";

}

//Write Balance into account
void Bank_Account::write_balance()
{
    ofstream myfile;

    myfile.open("CashBal.txt", ios_base::out);
    myfile << endl << cash_balance;
    myfile.close();

}

//Deposit money into account
void Bank_Account::deposit()
{
    cout << "\nPlease select the Amount to be deposited : ";
    cin >> depositcash;

    //Valid Deposit check
    while (depositcash < 0)
    {
        cout << "\nPlease Enter a valid deposit greater than $0\n";
        cin >> depositcash;
    }

    //Update Cash Balance
    set_cashbalance();
    cash_balance = get_cashbalance();
    cash_balance = cash_balance+ depositcash;
    write_balance();
    cout << "\n Amount $" << depositcash << " was deposited to your Account\n";

    //Get current time and date
    time_t rawtime;
    struct tm timeinfo;
    char buffer[80];
    time(&rawtime);
    localtime_s(&timeinfo, &rawtime);
    strftime(buffer, 80, "%d-%m-%Y %I:%M:%S", &timeinfo);
    string str(buffer);

    //Store transaction history
    bank_history.open("bank_transaction_history.txt", ios::app);
    bank_history << left << setw(20) << "Deposit";
    bank_history << left << setw(20) << depositcash;
    bank_history << left << setw(20) << str;
    bank_history << left << setw(20) << cash_balance<< endl;
    bank_history.close();

}

//Withdraw money from account
void Bank_Account::withdraw()
{
    cout << "\nPlease enter the amount to withdraw : ";
    cin >> withdrawcash;

    set_cashbalance();
    cash_balance = get_cashbalance();

    if (cash_balance > 0)
    {
        if (withdrawcash <= cash_balance)
        {
            //Update and write cash balance
            cash_balance = cash_balance - withdrawcash;
            write_balance();

            //Get current time and date
            time_t rawtime;
            struct tm timeinfo;
            char buffer[80];
            time(&rawtime);
           localtime_s(&timeinfo, &rawtime);
            strftime(buffer, 80, "%d-%m-%Y %I:%M:%S", &timeinfo);
            string str(buffer);

            //Store transaction history
            bank_history.open("bank_transaction_history.txt", ios::app);
            bank_history << left << setw(20) << "Withdraw";
            bank_history << left << setw(20) << withdrawcash;
            bank_history << left << setw(20) << str;
            bank_history << left << setw(20) << cash_balance << endl;
            bank_history.close();
        }
        else
        {
            cout << "\nError! Insufficient Funds in Account \n";
            
        }
    }
    else
    {
        cout << "\nAccount Balance is Zero\n";
    }
}

//Print Transaction History
void Bank_Account::printhistory()
{
    string line;
    read_history.open("bank_transaction_history.txt", ios_base::in);
    cout << left << setw(20) << " Event ";
    cout << left << setw(20) << "Amount $";
    cout << left << setw(20) << "Date & Time";
    cout << left << setw(20) << "Balance $" << endl;

    while (!read_history.eof())
    {
        getline(read_history, line);
        cout << line << endl;
    }
}
