#include <iostream>
#include "Orders.h"
#include <vector>
#include <algorithm>
using namespace std;


    OrdersList::OrdersList(std::vector<Order*> vl){
         orders = vl;
    }

    void OrdersList::Delete(int index){

          orders.erase (orders.begin()+(index-1));

     } 


    void OrdersList::move(int start, int end){

        //first iterator for the order that has to be moved

        std::vector<Order *>::iterator itr1 = orders.begin();
        std::advance(itr1, start-1);

        //second iterator for the order that is to be swapped with
        std::vector<Order *>::iterator itr2 = orders.begin();
        std::advance(itr2, end-1);

        //swapping the two orders the iterators point to

        std::iter_swap(*itr1, *itr2);

        }

     Deploy::Deploy(int a, string l){
           armies = a;
           location = l;
       }

     ostream& operator << (ostream & os, const Deploy &o){
          return os << "Deploy " << o.armies << "to " << o.location << endl;
     }


