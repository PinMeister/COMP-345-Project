#include <iostream>
#include <iterator>
#include <list>
#include "Orders.h"

using namespace std;

int main(){

    //creating pointers of user defined class type

     Deploy *deploy = new Deploy(2, "america");
    Advance *advance = new Advance();
    Bomb *bomb = new Bomb();
    Blockade *blockade = new Blockade();
    Airlift *airlift = new Airlift(); 
    Negotiate *negotiate = new Negotiate();

    //creating list of Order* objects

    std::list<Order*> list;

    // placing elements in list
    list.push_back(deploy);
    list.push_back(advance);
    list.push_back(bomb);
    list.push_back(blockade);
    list.push_back(airlift);
    list.push_back(negotiate);

    //placing the list in OrdersList object (which is a pointer type)

    OrdersList *olist = new OrdersList(list);
    

return 0;
};
