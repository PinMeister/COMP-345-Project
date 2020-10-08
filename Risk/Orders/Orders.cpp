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

 private:
    int armies;  //number of armies to be deployed
    string destination; //region where army is to be deployed

public:

    Deploy(){                 //constructor

    }
    Deploy(int a, string d){ //parametrized constructor for class Deploy
        armies = a;
        destination = d;
    }

    friend ostream& operator << (ostream &strm, const Deploy &d){

        return strm << "Deploy " << d.armies << "armies to " << d.destination; 

    }

};

//classes inheriting from order. yet to be implemented
class Advance : public Order {

    private:
        string source;
        string target;


    public:
        Advance(){

        }

};

class Bomb : public Order {

    public:
        Bomb(){

        }

};

class Blockade : public Order {

    public:
        Blockade(){

        }

};

class Airlift : public Order {

    public:
        Airlift(){

        }

};

class Negotiate : public Order {

    public: Negotiate(){

    }

};