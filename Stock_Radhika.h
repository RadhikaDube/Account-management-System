//
//  Stock_Radhika.h
//  FinalProject_Radhika
//
//  Created by Radhika Dube on 12/3/19.
//  Copyright © 2019 Radhika Dube. All rights reserved.
//

#ifndef Stock_Radhika_h
#define Stock_Radhika_h
#include<iostream>
#include<string>

#include"Account_Radhika.h"

using namespace std;

class Stocknode
{
    friend class Stockaccount;

public:

    Stocknode(string &s, int n)
    :symbol(s), noofstocks(n)
    {
        this->next = NULL;
        this->previous = NULL;
    }

private:
    //For Double Linked List
    Stocknode *next;
    Stocknode *previous;

    //Store Symbol and Number of Stocks
    string symbol;
    int noofstocks;

};

#endif /* Stock_Radhika_h */
