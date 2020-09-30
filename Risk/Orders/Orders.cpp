#include <iostream>
#include "Orders.h"
using namespace std;


class Order { //parent class

    //validate and execute methods to be inherited by the order subclasses
    void validate(){

    }
    void execute(){
    
    }

};


class Deploy : Order {  //class Deploy inherits from Order

 private:
    int armies;  //number of armies to be deployed
    string destination; //region where army is to be deployed

    Deploy(int a, string d){ //constructor for class Deploy
        armies = a;
        destination = d;
    }

    friend ostream& operator << (ostream &strm, const Deploy &d){

        return strm << "Deploy " << d.armies << "armies to " << d.destination; 

    }

};

//classes inheriting from order. yet to be implemented
class Advance : Order {

};

class Bomb : Order {

};

class Blockade : Order {

};

class Airlift : Order {

};

class Negotiate : Order {

};