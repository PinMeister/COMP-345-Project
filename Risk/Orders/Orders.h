#include <iostream>
using namespace std;
#pragma once


class OrdersList{

    private:
        std::list<Order *>  orders;

    public:
        OrdersList::OrdersList(std::list<Order *> ol);

    

};

class Order{

friend ostream& operator << (ostream &, const Order &); //stream insertion operator added to be inherited 

public:
    Order::Order();

    //validate and execute methods to be inherited by the order subclasses
    void validate(); 
    void execute();

};

class Deploy : public Order { //class Deploy inherits from Order

    public:
    Deploy::Deploy();  //constructor

};

class Advance : public Order{

    public:
        Advance::Advance(); //constructor


};

class Bomb : public Order{

    public:
        Bomb::Bomb(); //constructor


};

class Blockade : public Order{

    public:
        Blockade::Blockade(); //constructor


};

class Airlift : public Order{

    public:
        Airlift::Airlift(); //constructor


};

class Negotiate : public Order{

    public:
        Negotiate::Negotiate(); //constructor


};