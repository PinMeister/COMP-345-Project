#include <iostream>
using namespace std;
#pragma once

class Order{

friend ostream& operator << (ostream &, const Order &); //stream insertion operator added to be inherited 

//validate and execute methods to be inherited by the order subclasses
void validate(); 
void execute();

};

class Deploy : Order { //class Deploy inherits from Order

    private:
        int armies;  //number of armies to be deployed
        string destination; //region where army is to be deployed

    Deploy(int a, string d); //constructor for class Deploy

};