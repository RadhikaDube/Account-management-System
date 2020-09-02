//
//  Account_Radhika.h
//  FinalProject_Radhika
//
//  Created by Radhika Dube on 12/3/19.
//  Copyright © 2019 Radhika Dube. All rights reserved.
//

#ifndef Account_Radhika_h
#define Account_Radhika_h

class Account
{
public:

    //Get The Balance
    double get_cashbalance();
    //Set Cash balace
    void set_cashbalance ();

    //Virtual Function to print transaction history
    virtual void print_data();

protected:
    //cashbalance declared as protected membe to store the Cash Balance
    double cash_balance;

};


#endif /* Account_Radhika_h */
