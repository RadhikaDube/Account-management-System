//
//  StockAccount_Radhika.h
//  FinalProject_Radhika
//
//  Created by Radhika Dube on 12/3/19.
//  Copyright © 2019 Radhika Dube. All rights reserved.
//

#ifndef StockAccount_Radhika_h
#define StockAccount_Radhika_h

#include<iostream>
#include<string>
#include<fstream>
#include<map>

#include"Account_Radhika.h"
#include"Stock_Radhika.h"

using namespace std;

//STL map to hash symbol and stock price
typedef map<string, double>sym;
//derived class stockaccount
class Stockaccount :public Account
{
public:
    //Default Constructor
    Stockaccount();
    //Default Destructor
    ~Stockaccount();

    //Stock Functions
    void displaystock();
    void buyshares();
    void sellshares();
    void buyupdate(string, int);
    void sellupdate(Stocknode*, int);

    //Portfolio Functions
    void displayportfolio();
    void readportfolio();
    void writeportfolio();
    void readportvalue();
    void writeportvalue();
    void writebalance();

   
    sym select(sym, sym);                        //Randomly Select any file
    Stocknode *find(string);                   //Search in the portfolio
    void sort_portfolio();                       //sort the portfolio
    virtual void print_history();                //virtual function to print the history
    bool isEmpty() const;                        //check if list the  is empty
    void plot_graph();                        //plot graph in matlab

private:
//Variables
    Stocknode *head;
    Stocknode *tail;
    int no1, no2, numberstock,size;
    string symbol_1,stocksymbol,line1, line2;
    double stockprice,price1,price,maxamount, minamount, totalamount;
    //Array declaration
    double portarray[100];
    string timearray[100];
    
    ofstream stock_history, bank_history;
    ifstream read1, read2;
    sym result_1, result_2;
    stringstream s_1, s_2;
};

#endif /* StockAccount_Radhika_h */
