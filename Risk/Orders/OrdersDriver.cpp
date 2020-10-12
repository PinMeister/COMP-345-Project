#include <iostream>
#include <iterator>
#include <vector>
#include "Orders.h"

using namespace std;

int main(){

    //creating pointers of user defined class type

    Deploy *deploy = new Deploy(2, "usa");
    Advance *advance = new Advance();
    Bomb *bomb = new Bomb();
    Blockade *blockade = new Blockade();
    Airlift *airlift = new Airlift(); 
    Negotiate *negotiate = new Negotiate();

    //creating vector of Order* objects

    vector<Order*> vec;

    // placing elements in list

    vec.push_back(deploy);
    vec.push_back(advance);
    vec.push_back(bomb);
    vec.push_back(blockade);
    vec.push_back(airlift);
    vec.push_back(negotiate);

    //placing the list in OrdersList object (which is a pointer type)

    OrdersList *olist = new OrdersList(vec);
   
    delete deploy; 
    delete advance;
    delete bomb;
    delete blockade;
    delete airlift;
    delete negotiate;
    delete olist; 


    return 0;
};
