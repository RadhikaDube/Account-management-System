//
//  main.cpp
//  FinalProject_Radhika
//
//  Created by Radhika Dube on 12/3/19.
//  Copyright © 2019 Radhika Dube. All rights reserved.
//

#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
#include<utility>

#include "Stock_Radhika.h"
#include "Account_Radhika.h"
#include "BankAccount_Radhika.h"
#include "StockAccount_Radhika.h"

using namespace std;

int main()
{
  Stocknode *n ;//= NULL;
    Bank_Account BA;//object for bank account
    Stockaccount SA;//object for stock account
    //initial conditions
    int choice_1 = 0,choice_2 = 0,choice_3 = 0;
   

    cout << " Account Management System! "<<endl;
//Main Menu
   do
    {
        cout <<"1. Stock Portfolio Account"<<endl;
        cout <<"2. Bank Account"<<endl;
        cout <<"3. Exit"<<endl;
        cout <<"Select Account to be Accessed : "<<endl;
        cin >> choice_1;

        switch (choice_1)
        {
        case 1:
            do// Stock Account menu
            {
                cout << "\nStock Portfolio account"
                    << "\n1. Display the price for a Stock Symbol"
                    << "\n2. Display Current Portfolio"
                    << "\n3. Buy Shares"
                    << "\n4. Sell Shares"
                    << "\n5. View a Graph for the Portfolio Value"
                    << "\n6. View Transaction History"
                    << "\n7. Return to the Previous Menu";
                cout << "\nEnter Your Choice : ";
                cin >> choice_2;
                switch (choice_2)
                {
                case 1:
                    SA.displaystock();//to display stocks
                    break;
                case 2:
                    SA.displayportfolio();//to display portfolio
                    break;
                case 3:
                    SA.buyshares();//to buy shares
                    break;
                case 4:
                    SA.sellshares();//to sell shares
                    break;
                case 5:
                    cout << "Display graph here\n";
                    SA.plot_graph();//to plot graph
                    break;
                case 6:
                    SA.print_history();//to print history
                    break;

                case 7:
                    break;
                default:
                    cout << "\nPlease Enter a Valid Option!";
                }
            }while (choice_2 != 7);
            choice_2 = 0;
            break;
        case 2:

           do
            {
                cout<< "Bank Account"<<endl;
                cout<< "1. View Account Balance"<<endl;
                cout << "2. Deposit Money"<<endl;
                cout << "3. Withdraw Money"<<endl;
                cout << "4. Print History"<<endl;
               cout  << "5. Return to Previous Menu"<<endl;
                cout << "Please Enter Your Choice : "<<endl;
                cin >> choice_3;
                switch (choice_3)
                {
                case 1:
                    BA.viewbalance();//to view balance
                    break;
                case 2:
                    BA.deposit(); //to deposit money into account
                        SA.writeportvalue();
                    break;
                case 3:
                    BA.withdraw(); //to withdraw money from account
                        SA.writeportvalue();
                    break;
                case 4:
                    BA.printhistory();//to print transaction history
                    break;
                case 5:
                    break;
                default:
                    cout << "Please Enter a Valid Option!"<<endl;
                }
            }while (choice_3 != 5);
            choice_3 = 0;
            break;

        case 3:
                SA.writeportfolio();//to write porfolio
            break;
        default:
            cout << "Please Enter a Valid Option!"<<endl;
        }
    }while(choice_1!=3);
    return 0;
}// end of main function
