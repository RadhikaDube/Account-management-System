//
//  StockAccount_Radhika.cpp
//  FinalProject_Radhika
//
//  Created by Radhika Dube on 12/3/19.
//  Copyright © 2019 Radhika Dube. All rights reserved.
//

#include<iostream>
#include<iomanip>
#include<stdlib.h>
#include<string>
#include<fstream>
#include<sstream>
#include<map>
#include<time.h>
#include"Stock_Radhika.h"
#include"Account_Radhika.h"
#include"StockAccount_Radhika.h"

/*#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

//#include <yvals.h>
#if (_MSC_VER >= 1600)
#include <yvals.h>
//#include "mex.h"
//#include<engine.h>
#define __STDC_UTF_16__
#endif

#pragma comment( lib, "libmx.lib" )
#pragma comment( lib, "libmex.lib" )
#pragma comment( lib, "libeng.lib" )
*/



using namespace std;

//Default Constructor
Stockaccount::Stockaccount()
{
    no1 = 0;
    no2 = 0;

    size = 0;

    set_cashbalance();
    cash_balance = get_cashbalance();


    read1.open("Result_1.txt");
    read2.open("Result_2.txt");

    //Retrieve and store data into STL map
    if (read1.is_open() && read2.is_open())
    {
        while (!read1.eof() && !read2.eof())
        {
            getline(read1, line1);
            s_1 << line1;
            s_1 >> symbol_1 >> price1;
            result_1.insert(pair<string, double>(symbol_1, price1));
            s_1.str(" ");
            s_1.clear();

            getline(read2, line1);
            s_1 << line1;
            s_1 >> symbol_1 >> price1;
            result_2.insert(pair<string, double>(symbol_1, price1));
            s_1.str(" ");
            s_1.clear();
        }
    }

    read1.close();
    read2.close();

    //Retrieve existing portfolio
    this->readportfolio();
    this->readportvalue();
}

//Default Destructor
Stockaccount::~Stockaccount()
{
    //Empty Destructor
}

//Randomly select between two stock files
sym Stockaccount::select(sym file1, sym file2)
{
    srand(time(NULL));   //Current time as seed for random number generator
    int r_n;            //Random Number
    r_n = rand() % 2;    //Random number for the 2 different stock files

    if (r_n == 1)        //Return either of the two file choices based on random number
    {
        return file1;
    }
    else
    {
        return file2;
    }
}

//Display stock price on input symbol
void Stockaccount::displaystock()
{
    int flag = 0;
    cout << "\n Enter Stock Symbol to be Displayed : ";
    cin >> stocksymbol;

    sym copy;
    sym::iterator it1;
    copy = select(result_1, result_2);            //Randomly select file

    for (it1 = copy.begin(); it1 != copy.end(); it1++)
    {
        if (stocksymbol == it1->first)
        {
            cout << "\nSymbol";
            cout << setw(15) << " Price/Share($)" << endl;
            cout << it1->first;
            cout << setw(15) << it1->second << endl;
            flag = 1;

        }
    }

    if (flag == 0)
    {
        cout << "\nSymbol not found, Enter a valid symbol\n";

    }

}

//check if list is empty or not
bool Stockaccount::isEmpty() const
{
    return(head == 0 && tail == 0);

}

//Search if stock exists in the portfolio
Stocknode * Stockaccount::find(string a)
{
    Stocknode *current = head;

    while (current != NULL)
    {
        if (current->symbol == a)
        {
            return current;
        }

        current = current->next;
    }

    return NULL;        //Return NULL if symbol not found
}

//Sort the list using bubble sort
void Stockaccount::sort_portfolio()
{
    double x=0, y=0;

    if (head != NULL)
    {
        int flag = 0;
        Stocknode *current = head;
        Stocknode *prev = 0;
        Stocknode *temp = NULL;
        sym temp_sym;

        for (int i = 0; i < size; i++)
        {
            while (current->next != 0)
            {
                temp_sym = select(result_1, result_2);
                temp = current->next;

                sym::iterator it1;

                for (it1 = temp_sym.begin(); it1 != temp_sym.end(); it1++)
                {
                    if (current->symbol == it1->first)
                    {
                        x = it1->second;
                    }
                    if (temp->symbol == it1->first)
                    {
                        y = it1->second;
                    }
                }

                //comparing stock value
                if ((current->noofstocks)*x < (temp->noofstocks)*y)
                {
                    temp->previous = current->previous;
                    current->previous = temp;
                    current->next = temp->next;

                    flag = 1;

                    if (current->next != NULL)
                    {
                        current->next->previous = current;
                    }
                    temp->next = current;

                    if (prev != 0)
                    {
                        prev->next = temp;
                    }
                    prev = temp;

                    if (head == current)
                    {
                        head = temp;
                    }
                    if (current->next == 0)
                    {
                        tail = current;
                    }
                }
                else
                {
                    prev = current;
                    current = current->next;
                }
            }

            if (flag == 0)
            {
                break;
            }
            else
            {
                prev = NULL;
                current = head;
                flag = 0;
            }
        }

    }
}

//Update portfolio after buying stock
void Stockaccount::buyupdate(string a, int n)
{
    Stocknode *temp;
    temp = new Stocknode(a, n);

    Stocknode *found = find(a);            //Check if Stock Symbol is in portfolio list

    if (found == NULL)            //Symbol not found
    {
        if (tail == NULL && head == NULL)        //if list is empty
        {
            temp->previous = NULL;
            temp->next = NULL;
            head = temp;
            tail = temp;
        }
        else //add to end of list
        {
            Stocknode *cpy = tail;
            tail->next = temp;
            tail = temp;
            tail->previous = cpy;

        }
        size++;
    }
    else            //Increse number of stock if symbol exists
    {
        found->noofstocks= temp->noofstocks + found->noofstocks;
    }
    sort_portfolio();
}

//Update portfolio after selling shares
void Stockaccount::sellupdate(Stocknode *f, int n)
{
    f->noofstocks = f->noofstocks - n;        //Subtract the shares

    //Delete node if number of shares is zero
    if (f->noofstocks == 0)
    {
        if (f == head)
        {
            if (f == tail)        //If its the only node in list
            {
                head = NULL;
                tail = NULL;
                delete f;
                size--;
                return;
            }
            Stocknode *temp1 = f->next;
            head = f->next;
            temp1->previous = NULL;
            delete f;
            size--;
            return;
        }
        else if (f == tail)
        {
            if (f == head)        //If its the only node in list
            {
                head = NULL;
                tail = NULL;
                delete f;
                size--;
                return;
            }
            Stocknode *temp2 = f->previous;
            tail = f->previous;
            temp2->next = NULL;
            delete f;
            size--;
            return;
        }
        else
        {
            Stocknode *temp3 = f->previous;
            Stocknode *temp4 = f->next;
            temp3->next = f->next;
            temp4->previous = f->previous;
            delete f;
            size--;
            return;
        }
    }

}

// Buying Shares
void Stockaccount::buyshares()
{
    int flag = 0;
    sym copy;

    cout << "Enter the Stock Symbol you want to buy : "<<endl;
    cin >> stocksymbol;

    copy = select(result_1, result_2);
    for (sym::iterator it1 = copy.begin(); it1 != copy.end(); it1++)
    {
        if (stocksymbol == it1->first)
        {
            flag = 1;
            stockprice = it1->second;
        }
    }
    if (flag == 0)
    {
        cout << "Symbol not found, Enter a valid symbol"<<endl;
        return;
    }
    cout << "Enter the number of Stocks you want to buy : "<<endl;
    cin >> numberstock;
    cout << "Enter the Maximum Amount willing to pay per stock : "<<endl;
    cin >> maxamount;

    //Check if Stock price is less than max amount
    if (maxamount > stockprice)
    {
        totalamount = numberstock * stockprice;
    }
    else
    {
        cout << "Transaction Incomplete! Stock price is too high, cant buy stock at this price"<<endl;
        return;
    }

    //Get recent cash balance
    set_cashbalance();
    cash_balance = get_cashbalance();

    //check if sufficient funds are available
    if (totalamount <= cash_balance)
    {
        cash_balance = cash_balance - totalamount;
        writebalance();
        cout <<endl<< "Transaction Complete! You have purchased " << numberstock << " shares of " << stocksymbol << " for amount $" << totalamount << endl;

        //get transaction time
        time_t rawtime;
        struct tm timeinfo;
        char buffer[80];
        time(&rawtime);
        localtime_s(&timeinfo, &rawtime);
        strftime(buffer, 80, "%d-%m-%Y %I:%M:%S", &timeinfo);
        string str(buffer);

        //record stock transaction
        stock_history.open("stock_transaction_history.txt", ios::app);
        stock_history << left << setw(20) << "Buy";
        stock_history << left << setw(20) << stocksymbol;
        stock_history << left << setw(20) << numberstock;
        stock_history << left << setw(20) << stockprice;
        stock_history << left << setw(20) << totalamount;
        stock_history << left << setw(20) << str << endl;
        stock_history.close();

        //record bank transaction
        bank_history.open("bank_transaction_history.txt", ios::app);
        bank_history << left << setw(20) << "withdraw(stock)";
        bank_history << left << setw(20) << totalamount;
        bank_history << left << setw(20) << str;
        bank_history << left << setw(20) << cash_balance<< endl;
        bank_history.close();
    }
    else
    {
        cout << "Invalid Transaction! Insufficient Balance"<<endl;
        return;
    }

    //update the list
    buyupdate(stocksymbol, numberstock);
    sort_portfolio();
    writeportvalue();
}


//Sell shares
void Stockaccount::sellshares()
{
    int flag = 0;
    Stocknode *temp = NULL;

    cout << "\nEnter Stock Symbol to sell:\n";
    cin >> stocksymbol;
    temp = find(stocksymbol);

    if (temp != NULL)
    {
        flag = 1;
    }

    if (flag == 0)
    {
        cout << "\nSymbol not found!\n";
        return;
    }

    cout << "\nEnter the number of shares you want to sell : ";
    cin >> numberstock;

    if (numberstock > temp->noofstocks)
    {
        cout << "Number of shares is out of range\n";
        return;
    }

    cout << "\Enter minimum amount you want to sell per share : ";
    cin >> minamount;

    sym sym_temp;
    sym_temp = select(result_1, result_2);
    sym::iterator it1;
    for (it1 = sym_temp.begin(); it1 != sym_temp.end(); it1++)
    {
        if (stocksymbol == it1->first)
        {
            stockprice = it1->second;
        }
    }

    if (stockprice < minamount)
    {
        cout << "\nSell price is high, Transaction Incomplete!\n";
        return;
    }

    //Get recent cash balance
    set_cashbalance();
    cash_balance = get_cashbalance();
    totalamount = numberstock * stockprice;
    cash_balance = cash_balance + totalamount;
    writebalance();
    cout << "\nTransaction Complete! You have sold " << numberstock << " shares of " << stocksymbol << " for amount $" << totalamount << endl;

    //get transaction time
    time_t rawtime;
    struct tm timeinfo;
    char buffer[80];
    time(&rawtime);
    localtime_s(&timeinfo, &rawtime);
    strftime(buffer, 80, "%d-%m-%Y %I:%M:%S", &timeinfo);
    string str(buffer);

    //record stock transaction
    stock_history.open("stock_transaction_history.txt", ios::app);
    stock_history << left << setw(20) << "Sell";
    stock_history << left << setw(20) << stocksymbol;
    stock_history << left << setw(20) << numberstock;
    stock_history << left << setw(20) << stockprice;
    stock_history << left << setw(20) << totalamount;
    stock_history << left << setw(20) << str << endl;
    stock_history.close();

    //record bank transaction
    bank_history.open("bank_transaction_history.txt", ios::app);
    bank_history << left << setw(20) << "deposit(stock)";
    bank_history << left << setw(20) << totalamount;
    bank_history << left << setw(20) << str;
    bank_history << left << setw(20) << cash_balance << endl;
    bank_history.close();

    sellupdate(temp, numberstock);
    sort_portfolio();
    writeportvalue();
}


//Display Portfolio
void Stockaccount::displayportfolio()
{
    set_cashbalance();
    cash_balance = get_cashbalance();
    sort_portfolio();

    Stocknode *current = head;
    sym copy;

    double pr, val, port_val;
    double stock_val = 0;

    copy = select(result_1, result_2);

    if (size > 0)
    {
        cout << endl << left << setw(20) << "Symbol";
        cout << left << setw(20) << "Shares";
        cout << left << setw(20) << "Price/Share($)";
        cout << left << setw(20) << "Total Value($)" << endl;
    }
    while (current != NULL)
    {
        for (sym::iterator it1 = copy.begin(); it1 != copy.end(); it1++)
        {
            if (current->symbol == it1->first)
            {
                pr = it1->second;
                val = current->noofstocks*pr;

                cout << left << setw(20) << current->symbol;
                cout << left << setw(20) << current->noofstocks;
                cout << left << setw(20) << pr;
                cout << left << setw(20) << val << endl;
                stock_val = stock_val + val;
            }
        }
        current = current->next;
    }

    if (size > 0)
    {
        cout << "\n Cash : $" << cash_balance;
        cout << "\n Stock : $" << stock_val;
        port_val = cash_balance + stock_val;
        cout << "\n Total Portfolio value : $" << port_val << endl;
    }
    else if (size == 0)
    {
        port_val = cash_balance;
        cout << "\n Total portfolio value : $" << port_val << endl;
        cout << "\n You don't have any shares currently\n";
    }

}


//Print stock transaction history
void Stockaccount::print_history()
{
    ifstream myfile;
    myfile.open("stock_transaction_history.txt", ios::app);

    cout << left << setw(20) << "Event";
    cout << left << setw(20) << "CompSymbol";
    cout << left << setw(20) << "Shares";
    cout << left << setw(20) << "Price/Share";
    cout << left << setw(20) << "Value($)";
    cout << left << setw(20) << "Date & Time" << endl;

    while (!myfile.eof())
    {
        getline(myfile, line1);
        cout << line1 << endl;
    }
}

//Write Portfolio
void Stockaccount::writeportfolio()
{
    sort_portfolio();
    Stocknode *temp = head;
    ofstream myfile;
    myfile.open("portfolio.txt", ios_base::out);
    while (temp != NULL)
    {
        myfile << temp->symbol << "\t" << temp->noofstocks << endl;
        temp = temp->next;
    }
    myfile.close();
}

void Stockaccount::readportfolio()
{
    string p;
    int flag = 0;
    int n;
    sym temp;
    string temp_symb;
    int temp_share;
    ifstream myfile;
    myfile.open("portfolio.txt", ios_base::in);
    if (myfile.is_open())
    {
        while (!myfile.eof())
        {
            getline(myfile, line1);
            s_1 << line1;
            s_1 >> temp_symb >> temp_share;
            temp.insert(pair<string, int>(temp_symb, temp_share));
            s_1.clear();
            flag = 1;
        }
    }

    myfile.close();

    if (flag == 1)
    {
        for (sym::iterator it1 = temp.begin(); it1 != temp.end(); it1++)
        {
            p = it1->first;
            n = it1->second;

            buyupdate(p, n);
        }
    }
}

//write cash balance
void Stockaccount::writebalance()
{
    ofstream myfile;
    myfile.open("CashBalance.txt", ios_base::out);
    myfile << endl << cash_balance;
    myfile.close();
}

//Write portfolio value
void Stockaccount::writeportvalue()
{
    Stocknode *ptr = head;
    double cost = 0;
    double total = 0;
    double port_val = 0;

    sym copy;
    sym::iterator it1;
    ofstream write;
    copy = select(result_1, result_2);

    while (ptr != NULL)
    {
        for (it1 = copy.begin(); it1 != copy.end(); it1++)
        {
            if (ptr->symbol == it1->first)
            {
                cost = it1->second;
                total = total + ptr->noofstocks*cost;
            }
        }

        ptr = ptr->next;
    }

    set_cashbalance();
    cash_balance = get_cashbalance();
    port_val = total + cash_balance;

    if (no1 < 100)
    {
        portarray[no1] = port_val;        //Store portfolio value in array for graph
    }

    //generating the current date and time
    time_t rawtime;
    struct tm timeinfo;
    char buffer[80];
    time(&rawtime);
    localtime_s(&timeinfo, &rawtime);
    strftime(buffer, 80, "%d-%m-%Y %I:%M:%S", &timeinfo);
    std::string str(buffer);

    if (no2 < 100)
    {
        timearray[no2] = str;            //store time in time array
    }

    if (size == 0)
    {
        port_val = cash_balance;
    }

    write.open("portfoliovalue.txt", ios::app);
    write << port_val << "  " << str << endl;
    write.close();
    no1++;
    no2++;

}

//Read port folio value

void Stockaccount::readportvalue()
{
    string t;
    read1.open("portfolio.txt", ios_base::in);
    while (!read1.eof())
    {
        getline(read1, line1);
        s_1 << line1;
        s_1 >> portarray[no1] >> timearray[no2] >> t;

        if (timearray[no2] == "")
        {
            continue;
        }
        else
        {
            timearray[no1].append(" ");
            timearray[no1].append(t);
        }
        no1++;
        no2++;
        s_1.clear();
    }
    read1.close();

}


//Plot graph using MATLAB
void Stockaccount::plot_graph()
{

    cout << "Potfolio Value" << "\t\t" << "Date & Time" << endl;
    for (int i = 0; i < no1; i++)
    {
        cout << "$" << portarray[i] << "\t\t" << timearray[i] << endl;
    }

    Engine *ep;
    ep = engOpen(NULL);
    if (ep == NULL)
    {
        cout << "Error: Not Found." << endl;
        exit(1);
    }

    // create mxArray and copy arrays into it
    mxArray *A;
    A = mxCreateDoubleMatrix(1, num1, mxREAL);
    memcpy((void *)mxGetPr(A), (void *)portarray, no1 * sizeof(double));
    engPutVariable(ep, "yy", A);

    // plotting function.
    engEvalString(ep, "plot(yy);");

    //  title for graph
    engEvalString(ep, "title('Portfolio Variation graph');");

    mxDestroyArray(A); // destroy mxArray

}

