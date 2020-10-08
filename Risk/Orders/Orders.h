#include <iostream>
using namespace std;
#pragma once


class OrdersList{

    private:
        Order order;

    public:
        OrdersList();

    OrdersList(Order ord);

    list<Order> list;

};




class Order{

friend ostream& operator << (ostream &, const Order &); //stream insertion operator added to be inherited 

//validate and execute methods to be inherited by the order subclasses
void validate(); 
void execute();

};

class Deploy : public Order { //class Deploy inherits from Order

    private:
        int armies;  //number of armies to be deployed
        string destination; //region where army is to be deployed

    public:
    Deploy();  //constructor
    Deploy(int a, string d); //parametrized constructor for class Deploy

};

class Advance : public Order{

    private:
        string source;
        string target;


    public:
        Advance(); //constructor


};

class Bomb : public Order{

    public:
        Bomb(); //constructor


};

class Blockade : public Order{

    public:
        Blockade(); //constructor


};

class Airlift : public Order{

    public:
        Airlift(); //constructor


};

class Negotiate : public Order{

    public:
        Negotiate(); //constructor


};