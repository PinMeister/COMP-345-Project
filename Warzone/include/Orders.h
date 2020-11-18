#ifndef ORDER_H
#define ORDER_H

#include <iostream>
#include <vector>
#include <string>

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

    public:

        OrdersList(vector<Order*> ord); //constructor
        OrdersList(const OrdersList &ordersList); //copy constructor
        ~OrdersList(); //destructor
        OrdersList& operator=(const OrdersList &ordersList); //assignment operator

        friend ostream& operator << (ostream &os, const OrdersList &ordersList); //stream insertion operator for OrdersList
        void add(Order* order);
        void Delete(vector<Order*> ord, int index);
        void move(vector<Order*> ord, int start, int end);
    private:
        vector<Order*> orders; //list of orders
    
};

class Deploy : public Order { //class Deploy inherits from Order

    public:
        Deploy(int a, string l);  //constructor
        Deploy(const Deploy &deploy); //copy constructor
        ~Deploy(); //destructor
        Deploy& operator=(const Deploy &deploy); //assignment operator

        friend ostream& operator << (ostream &os, const Deploy &deploy); //stream insertion operator for Deploy 


    private:
        int armies;
        string location;
        void validate(); 
        void execute();
        
};

class Advance : public Order{

    public:
        Advance(string s, string t, int a); //constructor
        Advance(const Advance &advance); //copy constructor
        ~Advance(); //destructor
        Advance& operator=(const Advance &advance); //assignment operator

        friend ostream& operator << (ostream &os, const Advance &advance); //stream insertion operator for Advance  

    private:
        string source;
        string target;
        int armies;
        void validate(); 
        void execute();

};

class Bomb : public Order{

    public:
        Bomb(string t); //constructor
        Bomb(const Bomb &bomb); //copy constructor
        ~Bomb(); //destructor
        Bomb& operator=(const Bomb &bomb); //assignment operator

        friend ostream& operator << (ostream &os, const Bomb &bomb); //stream insertion operator for Bomb

    private:
        string target;
        void validate(); 
        void execute();
};

class Blockade : public Order{

    public:
        Blockade(string t); //constructor
        Blockade(const Blockade &blockade); //copy constructor
        ~Blockade(); //destructor
        Blockade& operator=(const Blockade &blockade); //assignment operator
        
        friend ostream& operator << (ostream &os, const Blockade &blockade); //stream insertion operator for Blockade

    private:
        string territory;
        void validate(); 
        void execute();
};

class Airlift : public Order{

    public:
        Airlift(string o, string d, int a); //constructor
        Airlift(const Airlift &airlift); //copy constructor
        ~Airlift(); //destructor
        Airlift& operator=(const Airlift &airlift); //assignment operator

        friend ostream& operator << (ostream &os, const Airlift &airlift); //stream insertion operator for Airlift

        private:
            string origin;
            string destination;
            int armies;
            void validate(); 
            void execute();
};

class Negotiate : public Order{

    public:
       Negotiate(int p); //constructor
       Negotiate(const Negotiate &negotiate); //copy constructor
       ~Negotiate(); //destructor
       Negotiate& operator=(const Negotiate &negotiate); //assignment operator

       friend ostream& operator << (ostream &os, const Negotiate &negotiate); //stream insertion operator for Negotiate

       private:
        int playerID;
        void validate(); 
        void execute();
};

#endif
