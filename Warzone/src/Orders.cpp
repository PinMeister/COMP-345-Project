#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "../include/Orders.h"
#include <time.h>
#include <random>

using namespace std;

     // for OrdersList
    OrdersList::OrdersList(vector<Order*> orderslist){   //constructor
         this->orderslist = orderslist;
    }


     OrdersList::OrdersList(const OrdersList &ordersList){ //copy constructor
          this->orderslist= ordersList.orderslist;
     }

     OrdersList::~OrdersList(){ //destructor
          this->orderslist.clear();
     }

     OrdersList& OrdersList::operator=(const OrdersList &ordersList){ //assignment operator

          this->orderslist = ordersList.orderslist;
          
          return *this;
     }

    void OrdersList::Delete(vector<Order*> orderslist, int index){                         

          orderslist.erase(orderslist.begin() + index);

     } 

//     void OrdersList::move(vector<Order*> orderslist, int start, int end){                  

//         //first iterator for the order that has to be moved

//         std::vector<Order *>::iterator itr1 = orderslist.begin();
//         std::advance(itr1, start-1);

//         //second iterator for the order that is to be swapped with
//         std::vector<Order *>::iterator itr2 = orderslist.begin();
//         std::advance(itr2, end-1);

//         //swapping the two orders the iterators point to

//         std::iter_swap(*itr1, *itr2);

//         } 

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
     Deploy::Deploy(Player* player, int armies, Territory* territory){ //constructor
           this->player = player;
           this->armies = armies;
           this->territory = territory;
       }

     Deploy::Deploy(const Deploy &deploy){ //copy constructor
          this->player = deploy.player;
          this->armies = deploy.armies;
          this->territory = deploy.territory;
     }

     Deploy& Deploy::operator=(const Deploy &deploy){ //assignment operator
          this->player = deploy.player;
          this->armies= deploy.armies;
          this->territory=deploy.territory;

           return *this;
     }

     ostream& operator << (ostream & os, const Deploy &deploy){  //stream insertion operator for Deploy
          return os << "Deploy " << deploy.armies << " to " << deploy.territory << endl;
     }

     bool Deploy  :: validate() {
          bool isValid;
          vector<Territory*> playerTerritories;
          playerTerritories = player->getTerritories(); //getting the territories of the player that issues this order
         if (std::find(playerTerritories.begin(), playerTerritories.end(), territory) != playerTerritories.end()){
            cout << "The deploy order is valid." << endl;
            isValid = true;
         }
         else {
           cout << "The deploy order is invalid." << endl;
           isValid = false;
         }
          return isValid;
     }

     void Deploy  :: execute() {
          bool orderValid = this->validate();
          if (orderValid) {       
               int pool = player->getReinforcementPool();
		     this->territory->addArmyNum(armies);
               pool -= armies; 
		     player->setReinforcementPool(pool);
		     cout << "Troops have been deployed" << endl;  
               }
       }      

     // for Advance
     Advance::Advance(Player* player, Territory* start, Territory* target, int armies){ //constructor
               this->player = player;
               this->start = start;
               this->target = target;
               armies = armies;
          }

     Advance::Advance(const Advance &advance){ //copy constructor
          this->player = advance.player;
          this->start = advance.start;
          this->target = advance.target;
          this->armies = advance.armies;

     }

     Advance& Advance::operator=(const Advance &advance){ //assignment operator
          this->player = advance.player;
          this->start = advance.start;
          this->target = advance.target;
          this->armies = advance.armies;

          return *this;
     }

     ostream& operator << (ostream &os, const Advance &advance){ //stream insertion operator for Advance
          return os << "Advance " << advance.armies << " armies from " << advance.start << " to " << advance.target <<endl;
     }

     void Advance  :: validate() {
          vector<Territory*> playerTerritories;
          playerTerritories = player->getTerritories();
          if (std::find(playerTerritories.begin(), playerTerritories.end(), start) != playerTerritories.end()){
            cout << "The advance order is valid." << endl;
         }
          else {
           cout << "The advance order is invalid." << endl;
         }         
     }

     void Advance  :: execute() {
          validate();
          vector<Territory*> playerTerritories;
          playerTerritories = player->getTerritories();   //getting territories of player that issued the order
          vector<Territory*> adjacent; 
          adjacent = start->neighbours;       //getting the neighbouring territories of the start territory 
          armyNumAttack = start ->getArmyNum();    //getting number of armies of player that issued the order
          armyNumDefend = target ->getArmyNum();
          //executes if target territory is adjacent to start 
          if(std::find(adjacent.begin(), adjacent.end(), target) != adjacent.end()){ 
               //checks if the target is from the player's territories
               if(std::find(playerTerritories.begin(), playerTerritories.end(), target) != playerTerritories.end()){
                    target->addArmyNum(armies);
                    start->subtractArmyNum(armies);
               }
               else{
                    if(armyNumAttack > armyNumDefend){
                         for(int i = 0; i < armyNumAttack; i++){
                         random_device rd;     
                         mt19937 gen(rd());
                         uniform_real_distribution<> dis(0, 1);
                         float randomNumberAttack = dis(gen);
                         if(randomNumberAttack > 0.4){
                              target->setArmyNum(armyNumDefend-1);
                         }
                         float randomNumberDefend = dis(gen);
                         if(randomNumberDefend > 0.3){
                              start->subtractArmyNum(armyNumAttack-1);
                            }
                         }
                    }
               }    
          }         
     }

     // for Bomb
     Bomb::Bomb(Player* player, Territory* target){ //constructor
               this->player=player;
               this->target=target;
          }

     Bomb::Bomb(const Bomb &bomb){ //copy constructor
          this->player=bomb.player;
          this->target=bomb.target;
     }

     Bomb& Bomb::operator=(const Bomb &bomb){ //assignment operator
          this->player=bomb.player;
          this->target=bomb.target;

          return *this;
     }

      ostream& operator << (ostream &os, const Bomb &bomb){ //stream insertion operator for Bomb
          return os << "Bomb "<< bomb.target <<endl;
     }

     bool Bomb  :: validate() {
     //      vector<Territory*> playerTerritories;
     //      playerTerritories = player->getTerritories(); //getting the territories of player issuing the order
     //     if (std::find(playerTerritories.begin(), playerTerritories.end(), this->target) != playerTerritories.end()){
     //        cout << "The bomb order is invalid." << endl;
     //     }
     //     else{
     //          cout << "The bomb order is valid." << endl;
     //     }
          bool isValid;
          isValid = true;
          vector<Territory*> playerTerritories;
          playerTerritories = player->getTerritories(); //getting the territories of the player that issues this order
         if (std::find(playerTerritories.begin(), playerTerritories.end(), this->target) != playerTerritories.end()){
            cout << "The bomb order is invalid." << endl;
            isValid = false;
         }
         else{
              cout << "The bomb order is valid." << endl;
              isValid = true;
         }
          return isValid;
     }  

     void Bomb  :: execute() {
          validate();
          bool neighbour = false;
          vector<Territory*> playerTerritories;
          vector<Territory*>::iterator iter;
          playerTerritories = player->getTerritories();   //getting the territories of player issuing the order
          vector<Territory*> adjacent; 
          adjacent = target->neighbours;     //adjacent is the list of target's neighboring territories
          int targetArmies = target->getArmyNum(); //number of armies of target territory

          //executes if target is not part of player's territories
         if (!(std::find(playerTerritories.begin(), playerTerritories.end(), target) != playerTerritories.end())){
            for(iter = playerTerritories.begin(); iter != playerTerritories.end(); iter++){ //looping through player's territories
            //if the any of the player's territory is a neighbour of target territory
               if(std::find(adjacent.begin(), adjacent.end(), (*iter)) != adjacent.end()){  
                    neighbour = true;
               }
               break; 
            }
            if(neighbour){    //if it is a neighbour, it executes bomb order and sets a new army number for target territory
               int newArmyNum = targetArmies/2;
               target->setArmyNum(newArmyNum);
            }
         }
     }   

     // for Blockade

     Blockade::Blockade(Player* player, Territory* territory){ //constructor
               this->player = player;
               this->territory = territory;
          }

     Blockade::Blockade(const Blockade &blockade){ //copy constructor
          this->player = blockade.player;
          this->territory = blockade.territory;
     }

     Blockade& Blockade::operator=(const Blockade &blockade){ //assignment operator
          this->player = blockade.player;
          this->territory=blockade.territory;

          return *this;
     }

     ostream& operator << (ostream &os, const Blockade &blockade){ //stream insertion operator for Blockade
               return os << "Blockade "<< blockade.territory <<endl;
          }

     void Blockade  :: validate() {
          vector<Territory*> playerTerritories;
          playerTerritories = player->getTerritories(); //getting the territories of player issuing the order
         if (std::find(playerTerritories.begin(), playerTerritories.end(), territory) != playerTerritories.end()){
            cout << "The blockade order is valid." << endl;
         }
         else{
              cout << "The blockade order is invalid." << endl;
         }    
     }  

     void Blockade  :: execute() {
          validate();
          vector<Territory*> playerTerritories;
          playerTerritories = player->getTerritories(); //getting the territories of player issuing the order
          int territoryArmies = territory->getArmyNum(); //number of armies of target territory
          vector<Territory*>::iterator iter; //iterator to iterate through player territories
          //only executes if territory is a player's territory
         if (std::find(playerTerritories.begin(), playerTerritories.end(), territory) != playerTerritories.end()){
               int newArmyNum = territoryArmies * 2;
               territory->setArmyNum(newArmyNum);
             for(iter = playerTerritories.begin(); iter != playerTerritories.end(); iter++){   //iterating through each player's list of orders
                    if((*iter) == territory){
                         playerTerritories.erase(iter);     //erase the territory from player's territories, making it neutral
                    }
                    break;    //ends loop after erasing the territory
               }     
         }
     }   

     // for Airlift

     Airlift::Airlift(Player* player, Territory* start, Territory* target, int armies){ //constructor
               this->player = player;
               this->start = start;
               this->target = target;
               this->armies = armies;
          }

     Airlift::Airlift(const Airlift &airlift){ //copy constructor
          this->player= airlift.player;
          this->start = airlift.start;
          this->target = airlift.target;
          this->armies = airlift.armies;
     }

     Airlift& Airlift::operator=(const Airlift &airlift){ //assignment operator
          this->player = airlift.player;
          this->start = airlift.start;
          this->target = airlift.target;
          this->armies = airlift.armies;

          return *this;
     }

     ostream& operator << (ostream &os, const Airlift &airlift){ //stream insertion operator for Airlift
               return os << "Airlift "<< airlift.armies<< " from " << airlift.start << " to "<< airlift.target <<endl;
          }


     void Airlift  :: validate() {
          vector<Territory*> playerTerritories;
          playerTerritories = player->getTerritories(); //getting the territories of player issuing the order
         if ((!(std::find(playerTerritories.begin(), playerTerritories.end(), start) != playerTerritories.end()))||(!(std::find(playerTerritories.begin(), playerTerritories.end(), target) != playerTerritories.end()))){
              cout << "The airlift order is invalid." << endl;
         }
         else{
             cout << "The airlift order is valid." << endl; 
         }
     }  

     void Airlift  :: execute() {
          
     }   

     // for Negotiate

     Negotiate::Negotiate(Player* player, Player* targetPlayer){ //constructor
               this->player = player;
               this->targetPlayer = targetPlayer;
          }

     Negotiate::Negotiate(const Negotiate &negotiate){ //copy constructor
          this->player = negotiate.player;
          this->targetPlayer = negotiate.targetPlayer;
     }

     Negotiate& Negotiate::operator=(const Negotiate &negotiate){ //assignment operator
          this->player = negotiate.player;
          this->targetPlayer = negotiate.targetPlayer;

          return *this;
     }

     ostream& operator << (ostream &os, const Negotiate &negotiate){ //stream insertion operator for Negotiate
               return os << "Negotiate "<< " with " << negotiate.targetPlayer <<endl;
          }

     void Negotiate  :: validate() {
          
     }  

     void Negotiate  :: execute() {
          
     }   
