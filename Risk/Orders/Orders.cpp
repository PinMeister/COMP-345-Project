#include <iostream>
#include <vector>
#include "Orders.h"

using namespace std;


     // for OrdersList

    OrdersList::OrdersList(std::vector<Order*> ord){   //constructor
         orders = ord;
    }


     OrdersList::OrdersList(const OrdersList &ordersList){ //copy constructor
          orders= ordersList.orders;
     }

     OrdersList::~OrdersList(){ //destructor
          orders.clear();
     }

    void OrdersList::Delete(int index){

          orders.erase (orders.begin()+(index-1));

     } 

     OrdersList& OrdersList::operator=(const OrdersList &ordersList){ //assignment operator

          orders = ordersList.orders;
          
          return *this;
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

     ostream& operator << (ostream &os, const OrdersList &ordersList){ //stream insertion operator for OrdersList
          return os << "Order List contains " << ordersList.orders<< endl;
     }

     // for Order

     ostream& operator << (ostream &os, const Order &order){ //stream insertion operator for Order
          return os << "Order"<< endl;
     }

     // for Deploy

     Deploy::Deploy(int a, string l){ //constructor
           armies = a;
           location = l;
       }

     Deploy::Deploy(const Deploy &deploy){ //copy constructor
          armies= deploy.armies;
          location=deploy.location;
     }

     Deploy::~Deploy(){  //destructor
          armies = 0;
          location="";
     }

     Deploy& Deploy::operator=(const Deploy &deploy){ //assignment operator
          armies= deploy.armies;
          location=deploy.location;

           return *this;
     }

     ostream& operator << (ostream & os, const Deploy &deploy){  //stream insertion operator for Deploy
          return os << "Deploy " << deploy.armies << "to " << deploy.location << endl;
     }


     // for Advance

     ostream& operator << (ostream &os, const Advance &advance){ //stream insertion operator for Advance
          return os << "Advance"<< endl;
     }

     // for Bomb

      ostream& operator << (ostream &os, const Bomb &bomb){ //stream insertion operator for Bomb
          return os << "Bomb"<< endl;
     }

     // for Blockade

     ostream& operator << (ostream &os, const Blockade &blockade){ //stream insertion operator for Blockade
               return os << "Blockade"<< endl;
          }

     // for Airlift

     ostream& operator << (ostream &os, const Airlift &airlift){ //stream insertion operator for Airlift
               return os << "Airlift"<< endl;
          }

     // for Negotiate

     ostream& operator << (ostream &os, const Negotiate &negotiate){ //stream insertion operator for Negotiate
               return os << "Negotiate"<< endl;
          }