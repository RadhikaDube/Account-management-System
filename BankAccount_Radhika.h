//
//  BankAccount_Radhika.h
//  FinalProject_Radhika
//
//  Created by Radhika Dube on 12/3/19.
//  Copyright © 2019 Radhika Dube. All rights reserved.
//

#ifndef BankAccount_Radhika_h
#define BankAccount_Radhika_h

#include<iostream>
#include<fstream>
#include<string>
#include<map>
#include<time.h>

#include"Account_Radhika.h"
#include"Stock_Radhika.h"
using namespace std;

class Bank_Account : public Account
{
public:
    //Default Contrsuctor 
    Bank_Account();
    //Default Destructor
    ~Bank_Account();

    //Transactions functions
    void viewbalance();
    void deposit();
    void withdraw();
    void write_balance();

    //Virtual function to print history
    virtual void printhistory();

private:

    double depositcash;
    double withdrawcash;

    ofstream bank_history;
    ifstream read_history;

};

#endif /* BankAccount_Radhika_h */
