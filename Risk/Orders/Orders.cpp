#include <iostream>
#include "Orders.h"
#include <list>
#include <list>
using namespace std;


class OrdersList {

    private:
        std::list<Order *>  orders;

    public:
        
        OrdersList::OrdersList(std::list<Order *> ol){
            orders = ol;
        }

};

class Order { //parent class

    public:

        Order(){

        }
       
    //validate and execute methods to be inherited by the order subclasses
    void validate(){

    }
    void execute(){
    
    }

};


class Deploy : public Order {  //class Deploy inherits from Order

    public:
        Deploy::Deploy(){                 //constructor

        }

    friend ostream& operator << (ostream &strm, const Deploy &d){

        return strm << "Deploy"; 

    }

};

//classes inheriting from order. yet to be implemented
class Advance : public Order {

    public:
        Advance::Advance(){

        }

};

class Bomb : public Order {

    public:
        Bomb::Bomb(){

        }

};

class Blockade : public Order {

    public:
        Blockade::Blockade(){

        }

};

class Airlift : public Order {

    public:
        Airlift::Airlift(){

        }

};

class Negotiate : public Order {

    public: Negotiate::Negotiate(){

    }

};