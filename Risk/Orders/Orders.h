#ifndef HEADERFILE_H
#define HEADERFILE_H
#include <iostream>
#include <vector>

using namespace std;

class Order{

    public:
        Order(); //constructor
        Order(const Order &order); //copy constructor
        ~Order(); //destructor
        Order& operator=(const Order &order); //assignment operator

        friend ostream& operator << (ostream &os, const Order &order); //stream insertion operator for Order
         

    //validate and execute methods to be inherited by the Order subclasses
    void validate(); 
    void execute();

};

class OrdersList{
    
    private:
        vector<Order*> orders;

    public:

        OrdersList(vector<Order*> ord); //constructor
        OrdersList(const OrdersList &ordersList); //copy constructor
        ~OrdersList(); //destructor
        OrdersList& operator=(const OrdersList &ordersList); //assignment operator

        friend ostream& operator << (ostream &os, const OrdersList &ordersList); //stream insertion operator for OrdersList

        void Delete(int index);
        void move(int start, int end);
    

};

class Deploy : public Order { //class Deploy inherits from Order

    private:
        int armies;
        string location;

    public:
        Deploy(int a, string l);  //constructor
        Deploy(const Deploy &deploy); //copy constructor
        ~Deploy(); //destructor
        Deploy& operator=(const Deploy &deploy); //assignment operator

        friend ostream& operator << (ostream &os, const Deploy &deploy); //stream insertion operator for Deploy 
        
};

class Advance : public Order{

    public:
        Advance(); //constructor
        Advance(const Advance &advance); //copy constructor
        ~Advance(); //destructor
        Advance& operator=(const Advance &advance); //assignment operator

        friend ostream& operator << (ostream &os, const Advance &advance); //stream insertion operator for Advance         

};

class Bomb : public Order{

    public:
        Bomb(); //constructor
        Bomb(const Bomb &bomb); //copy constructor
        ~Bomb(); //destructor
        Bomb& operator=(const Bomb &bomb); //assignment operator

        friend ostream& operator << (ostream &os, const Bomb &bomb); //stream insertion operator for Bomb

};

class Blockade : public Order{

    public:
        Blockade(); //constructor
        Blockade(const Blockade &blockade); //copy constructor
        ~Blockade(); //destructor
        Blockade& operator=(const Blockade &blockade); //assignment operator
        
        friend ostream& operator << (ostream &os, const Blockade &blockade); //stream insertion operator for Blockade

};

class Airlift : public Order{

    public:
        Airlift(); //constructor
        Airlift(const Airlift &airlift); //copy constructor
        ~Airlift(); //destructor
        Airlift& operator=(const Airlift &airlift); //assignment operator

        friend ostream& operator << (ostream &os, const Airlift &airlift); //stream insertion operator for Airlift

};

class Negotiate : public Order{

    public:
       Negotiate(); //constructor
       Negotiate(const Negotiate &negotiate); //copy constructor
       ~Negotiate(); //destructor
       Negotiate& operator=(const Negotiate &negotiate); //assignment operator

       friend ostream& operator << (ostream &os, const Negotiate &negotiate); //stream insertion operator for Negotiate

};

#endif

