//
//  Account_Radhika.cpp
//  FinalProject_Radhika
//
//  Created by Radhika Dube on 12/3/19.
//  Copyright © 2019 Radhika Dube. All rights reserved.
//

//header files
#include<iostream>
#include<fstream>
#include<sstream>
#include<iomanip>
#include<string>

#include"Account_Radhika.h"

using namespace std;

double Account::get_cashbalance()
{
    return cash_balance;//returns the current cashbalance
}

void Account::set_cashbalance()
{
    int flag = 0;                                    //Flag to check status of file
    ifstream file1;
    ofstream file2;

    file1.open("CashBalance.txt", ios_base::in);        //Open a CashBal.txt File

    if (file1.is_open())                            //Check if any previous cash balance entry is present
    {
        while (!(file1.eof()))
        {
            flag++;
            break;
        }
    }

    file1.close();//close the file

    if (flag == 0)
    {
        double init_balance = 10000.00;            //Initial Balance is set to $10000

        file2.open("CashBalance.txt", ios_base::out);
        file2 << init_balance;                            //Write Initial Balance as $10000
        file2.close();

        ifstream readbal("CashBalance.txt", ios_base::in);        //Read the balance from the file
        readbal >> cash_balance;
        readbal.close();
    }
    else
    {
        ifstream readbal("CashBalance.txt", ios_base::in);  //Read the existing balance from the file
        readbal >> cash_balance;
        readbal.close();

    }
}

void Account::print_data()
{
    string line;
    ifstream read_history;
    read_history.open("banktransaction_history.txt", ios::app);
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
