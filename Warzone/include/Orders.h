#ifndef ORDER_H
#define ORDER_H

#include <iostream>
#include <vector>
#include <string>
#include "../include/Map.h"
#include "../include/Player.h"
#include <time.h>

using namespace std;

class Territory;
class Player;
class Order{
    public:
        Order(); //constructor
        Order(const Order &order); //copy constructor
        ~Order(); //destructor
        Order& operator=(const Order &order); //assignment operator 
        friend ostream& operator << (ostream &os, const Order &order); //stream insertion operator for Order
        //validate and execute methods to be inherited by the Order subclasses
        void validate(); 
        virtual void execute() = 0;
        Territory* territory;
        Territory* start;
        Territory* target;
        Player* player;
        Player* targetPlayer;
        vector<Territory*> territories;
        int armies;
        int armyNumAttack;
        int armyNumDefend;
};

class OrdersList{

    public:

        OrdersList(vector<Order*> orderslist); //constructor
        OrdersList(const OrdersList &ordersList); //copy constructor
        ~OrdersList(); //destructor
        OrdersList& operator=(const OrdersList &ordersList); //assignment operator

        friend ostream& operator << (ostream &os, const OrdersList &ordersList); //stream insertion operator for OrdersList
        void add(Order* order);
        void Delete(vector<Order*> ord, int index);
        void move(vector<Order*> ord, int start, int end);
    private:
        vector<Order*> orderslist; //list of orders
    
};

class Deploy : public Order { //class Deploy inherits from Order
    public:
        Deploy(Player* player, int armies, Territory* territory);  //constructor
        Deploy(const Deploy &deploy); //copy constructor
        // ~Deploy(); //destructor
        Deploy& operator=(const Deploy &deploy); //assignment operator
        friend ostream& operator << (ostream &os, const Deploy &deploy); //stream insertion operator for Deploy 
        bool validate(); 
        void execute();         
};

class Advance : public Order{

    public:
        Advance(Player* player, Territory* start, Territory* target, int armies); //constructor
        Advance(const Advance &advance); //copy constructor
        ~Advance(); //destructor
        Advance& operator=(const Advance &advance); //assignment operator
        friend ostream& operator << (ostream &os, const Advance &advance); //stream insertion operator for Advance  
        void validate(); 
        void execute();

};

class Bomb : public Order{

    public:
        Bomb(Player* player, Territory* target); //constructor
        Bomb(const Bomb &bomb); //copy constructor
        ~Bomb(); //destructor
        Bomb& operator=(const Bomb &bomb); //assignment operator
        friend ostream& operator << (ostream &os, const Bomb &bomb); //stream insertion operator for Bomb
        bool validate(); 
        void execute();
};

class Blockade : public Order{

    public:
        Blockade(Player* player, Territory* territory); //constructor
        Blockade(const Blockade &blockade); //copy constructor
        ~Blockade(); //destructor
        Blockade& operator=(const Blockade &blockade); //assignment operator
        friend ostream& operator << (ostream &os, const Blockade &blockade); //stream insertion operator for Blockade
        bool validate(); 
        void execute();
};

class Airlift : public Order{

    public:
        Airlift(Player* player, Territory* start, Territory* target, int armies); //constructor
        Airlift(const Airlift &airlift); //copy constructor
        ~Airlift(); //destructor
        Airlift& operator=(const Airlift &airlift); //assignment operator
        friend ostream& operator << (ostream &os, const Airlift &airlift); //stream insertion operator for Airlift
        void validate(); 
        void execute();
};

class Negotiate : public Order{

    public:
       Negotiate(Player* player, Player* targetPlayer); //constructor
       Negotiate(const Negotiate &negotiate); //copy constructor
       ~Negotiate(); //destructor
       Negotiate& operator=(const Negotiate &negotiate); //assignment operator
       friend ostream& operator << (ostream &os, const Negotiate &negotiate); //stream insertion operator for Negotiate
        void validate(); 
        void execute();
};

#endif
