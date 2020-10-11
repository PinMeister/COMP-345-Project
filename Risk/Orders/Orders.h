#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Order{

    public:
        Order(); //constructor
        ~Order(); //destructor
        friend ostream& operator << (ostream &, const Order &); //stream insertion operator added to be inherited 

    //validate and execute methods to be inherited by the order subclasses
    void validate(); 
    void execute();

};

class OrdersList{
    
    private:
        std::vector<Order*> orders;

    public:

        OrdersList(std::vector<Order*> vl); //constructor
        ~OrdersList(); //destructor

        void Delete(int index);

        void move(int start, int end);
    

};

class Deploy : public Order { //class Deploy inherits from Order

    private:
        int armies;
        string location;

    public:
        Deploy(int a, string l);  //constructor
        ~Deploy(); //destructor
        friend ostream& operator << (ostream &, const Deploy &); //stream insertion operator added to be inherited 

};

class Advance : public Order{

    public:
        Advance(); //constructor
        ~Advance(); //destructor


};

class Bomb : public Order{

    public:
        Bomb(); //constructor
        ~Bomb(); //destructor

};

class Blockade : public Order{

    public:
        Blockade(); //constructor
        ~Blockade(); //destructor


};

class Airlift : public Order{

    public:
        Airlift(); //constructor
        ~Airlift(); //destructor


};

class Negotiate : public Order{

    public:
       Negotiate(); //constructor
       ~Negotiate(); //destructor


};

