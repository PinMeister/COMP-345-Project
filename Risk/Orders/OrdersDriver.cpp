#include <iostream>
#include <iterator>
#include <vector>
#include "Orders.h"

using namespace std;

int main(){

    //creating pointers of user defined class type

    Deploy *deploy = new Deploy(2, "canada");
    Advance *advance = new Advance("canada", "usa", 2);
    Bomb *bomb = new Bomb("mexico");
    Blockade *blockade = new Blockade("canada");
    Airlift *airlift = new Airlift("canada", "usa", 2); 
    Negotiate *negotiate = new Negotiate(6);

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
