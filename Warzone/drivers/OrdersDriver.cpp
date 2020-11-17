#include <iostream>
#include <iterator>
#include <vector>
#include <string>
#include "../include/Orders.h"

using namespace std;
    //will be changed in assignment 2
int main(){

    //creating pointers of user defined class type

   // Deploy *depl = new Deploy(2, "canada");
    Advance *adv = new Advance("canada", "usa", 2);
    Bomb *bmb = new Bomb("mexico");
    Blockade *blckd = new Blockade("canada");
    Airlift *alt= new Airlift("canada", "usa", 2); 
    Negotiate *ngt = new Negotiate(6); 

    //describing the order

    //cout << *depl << endl;  
    cout << *adv << endl; 
    cout << *bmb << endl;
    cout << *blckd << endl;
    cout << *alt << endl;
    cout << *ngt << endl; 

    //creating vector of Order* objects

    vector<Order*> vec;

    // placing elements in list

    //vec.push_back(depl);
    vec.push_back(adv);
    vec.push_back(bmb);
    vec.push_back(blckd);
    vec.push_back(alt);
    vec.push_back(ngt); 

   //placing the list in OrdersList object

   OrdersList *olist = new OrdersList(vec);
   
   //deleting the pointers

    //delete depl; 
    delete adv; 
    delete bmb;
    delete blckd;
    delete alt;
    delete ngt; 

    delete olist; 

    //depl = NULL;
    adv = NULL;
    bmb = NULL;
    blckd = NULL;
    alt = NULL;
    ngt = NULL;

    olist = NULL; 

    return 0;
};
