#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "../include/Orders.h"

using namespace std;

     // for OrdersList
    OrdersList::OrdersList(vector<Order*> orderslist){   //constructor
         orderslist = orderslist;
    }


     OrdersList::OrdersList(const OrdersList &ordersList){ //copy constructor
          orderslist= ordersList.orderslist;
     }

     OrdersList::~OrdersList(){ //destructor
          orderslist.clear();
     }

     OrdersList& OrdersList::operator=(const OrdersList &ordersList){ //assignment operator

          orderslist = ordersList.orderslist;
          
          return *this;
     }

    void OrdersList::Delete(vector<Order*> orderslist, int index){                          //Delete method

          orderslist.erase(orderslist.begin() + index);

     } 

    void OrdersList::move(vector<Order*> ord, int start, int end){                   //move method

        //first iterator for the order that has to be moved

        std::vector<Order *>::iterator itr1 = orderslist.begin();
        std::advance(itr1, start-1);

        //second iterator for the order that is to be swapped with
        std::vector<Order *>::iterator itr2 = orderslist.begin();
        std::advance(itr2, end-1);

        //swapping the two orders the iterators point to

        std::iter_swap(*itr1, *itr2);

        } 

     ostream& operator << (ostream &os, const OrdersList &ordersList){ //stream insertion operator for OrdersList

               os << "["; 
                    for (int i = 0; i < ordersList.orderslist.size(); ++i) { 
                         cout << *(ordersList.orderslist[i]) << endl;
                         if (i != ordersList.orderslist.size() - 1) 
                              os << ", "; 
                    } 
               os << "]\n"; 
               return os; 
         
     }

     // for Order
     Order::Order(){ //constructor
           
       }

     Order::Order(const Order &order){ //copy constructor
          
     }

     Order::~Order(){  //destructor
          
     }
     
     Order& Order::operator=(const Order &order){ //assignment operator
           return *this;
     }

     ostream& operator << (ostream &os, const Order &order){ //stream insertion operator for Order
          return os << "Order"<< endl;
     }

     // for Deploy
     Deploy::Deploy(int armies, Territory* territory){ //constructor
           armies = armies;
           territory = territory;
       }

     Deploy::Deploy(const Deploy &deploy){ //copy constructor
          armies = deploy.armies;
          this->territory = deploy.territory;
     }

     Deploy& Deploy::operator=(const Deploy &deploy){ //assignment operator
          armies= deploy.armies;
          this->territory=deploy.territory;

           return *this;
     }

     ostream& operator << (ostream & os, const Deploy &deploy){  //stream insertion operator for Deploy
          return os << "Deploy " << deploy.armies << " to " << deploy.territory << endl;
     }

     void Deploy  :: validate() {
         if (std::find(territories.begin(), territories.end(), territory) != territories.end()){
            cout << "The deploy order is valid.";
         }
         else {
           cout << "The deploy order is invalid.";
         }
     }

     void Deploy  :: execute() {
          validate();
          if (std::find(territories.begin(), territories.end(), territory) != territories.end()){
            territory->addArmyNum(armies);
         }         
     }


     // for Advance

     Advance::Advance(Territory* start, Territory* target, int armies){ //constructor
               start = start;
               target = target;
               armies = armies;
          }

     Advance::Advance(const Advance &advance){ //copy constructor
          start = advance.start;
          target = advance.target;
          armies = advance.armies;

     }

     Advance& Advance::operator=(const Advance &advance){ //assignment operator
          start = advance.start;
          target = advance.target;
          armies = advance.armies;

          return *this;
     }

     ostream& operator << (ostream &os, const Advance &advance){ //stream insertion operator for Advance
          return os << "Advance " << advance.armies << " armies from " << advance.start << " to " << advance.target <<endl;
     }

     void Advance  :: validate() {
          if (std::find(territories.begin(), territories.end(), start) != territories.end()){
            cout << "The advance order is valid.";
         }
          else {
           cout << "The advance order is invalid.";
         }         
     }

     void Advance  :: execute() {
          validate();
          if ((std::find(territories.begin(), territories.end(), start) != territories.end()) && (std::find(territories.begin(), territories.end(), target) != territories.end())){
            
         }          
     }

     // for Bomb

     Bomb::Bomb(string t){ //constructor
               target = t;
          }

     Bomb::Bomb(const Bomb &bomb){ //copy constructor
          target=bomb.target;
     }

     Bomb::~Bomb(){  //destructor
          target="";
     }

     Bomb& Bomb::operator=(const Bomb &bomb){ //assignment operator
          target=bomb.target;

          return *this;
     }

      ostream& operator << (ostream &os, const Bomb &bomb){ //stream insertion operator for Bomb
          return os << "Bomb "<< bomb.target <<endl;
     }

     void Bomb  :: validate() {
          
     }  

     void Bomb  :: execute() {
          
     }   

     // for Blockade

     Blockade::Blockade(string t){ //constructor
               territory = t;
          }

     Blockade::Blockade(const Blockade &blockade){ //copy constructor
          territory=blockade.territory;
     }

     Blockade::~Blockade(){  //destructor
          territory="";
     }

     Blockade& Blockade::operator=(const Blockade &blockade){ //assignment operator
          territory=blockade.territory;

          return *this;
     }

     ostream& operator << (ostream &os, const Blockade &blockade){ //stream insertion operator for Blockade
               return os << "Blockade "<< blockade.territory <<endl;
          }

     void Blockade  :: validate() {
          
     }  

     void Blockade  :: execute() {
          
     }   

     // for Airlift

     Airlift::Airlift(string o, string d, int a){ //constructor
               origin = o;
               destination = d;
               armies = a;
          }

     Airlift::Airlift(const Airlift &airlift){ //copy constructor
          origin = airlift.origin;
          destination = airlift.destination;
          armies = airlift.armies;
     }

     Airlift::~Airlift(){  //destructor
          origin="";
          destination="";
          armies = 0;
     }

     Airlift& Airlift::operator=(const Airlift &airlift){ //assignment operator
          origin=airlift.origin;
          destination = airlift.destination;
          armies = airlift.armies;

          return *this;
     }

     ostream& operator << (ostream &os, const Airlift &airlift){ //stream insertion operator for Airlift
               return os << "Airlift "<< airlift.armies<< " from " << airlift.origin << " to "<< airlift.destination <<endl;
          }


     void Airlift  :: validate() {
          
     }  

     void Airlift  :: execute() {
          
     }   

     // for Negotiate

     Negotiate::Negotiate(int p){ //constructor
               playerID = p;
          }

     Negotiate::Negotiate(const Negotiate &negotiate){ //copy constructor
          playerID = negotiate.playerID;
     }

     Negotiate::~Negotiate(){  //destructor
          playerID= 0;
     }

     Negotiate& Negotiate::operator=(const Negotiate &negotiate){ //assignment operator
          playerID=negotiate.playerID;

          return *this;
     }

     ostream& operator << (ostream &os, const Negotiate &negotiate){ //stream insertion operator for Negotiate
               return os << "Negotiate "<< " with " << negotiate.playerID <<endl;
          }

     void Negotiate  :: validate() {
          
     }  

     void Negotiate  :: execute() {
          
     }   
