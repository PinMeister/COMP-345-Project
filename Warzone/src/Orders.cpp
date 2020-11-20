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
               this->armies = armies;
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
          armyNumAttack = armies;    //getting number of armies of player that issued the order
          armyNumDefend = target->getArmyNum();
          //executes if target territory is adjacent to start 
          if(std::find(adjacent.begin(), adjacent.end(), target) != adjacent.end()){ 
               //checks if the target is from the player's territories
               if(std::find(playerTerritories.begin(), playerTerritories.end(), target) != playerTerritories.end()){
                    target->addArmyNum(armies);
                    start->subtractArmyNum(armies);
               }
               else{
                    start->subtractArmyNum(armies);
                    random_device rd;     
                    mt19937 gen(rd());
                    uniform_real_distribution<> dis(0, 1);
                    float randomNumberAttack = dis(gen);
                    while(armyNumDefend != 0 && armyNumAttack != 0){
                         // 60% killing 1 defending amry
                         if (randomNumberAttack > 0.4){
                              armyNumDefend -= 1;
                         }
                         // 70% killing 1 attacking amry
                         if (randomNumberAttack > 0.3){
                              armyNumAttack -= 1;
                         }
                         randomNumberAttack = dis(gen);
                    }
                    target->setArmyNum(armyNumDefend); // update defending army num
                    // capture the territory
                    if (armyNumDefend == 0){
                         // add the territory to the player and remove it from its previous owner
                         player->addTerritory(target);
                         target->setArmyNum(armyNumAttack); // move player army to target
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
          bool orderValid = this->validate();
          int targetArmyNum = this->target->getArmyNum();
          if (orderValid) {       
                this->target->setArmyNum(targetArmyNum/2);
                cout << "Bomb order executed" << endl;
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

     bool Blockade  :: validate() {    
          bool isValid;
          isValid = true;
          vector<Territory*> playerTerritories;
          playerTerritories = player->getTerritories(); //getting the territories of player issuing the order
         if (std::find(playerTerritories.begin(), playerTerritories.end(), this->territory) != playerTerritories.end()){
            cout << "The blockade order is valid." << endl;
            isValid = true;
         }
         else{
              cout << "The blockade order is invalid." << endl;
              isValid = false;
         } 
         return isValid;
     }  

     void Blockade  :: execute() {
          bool orderValid = this->validate();
          vector<Territory*> playerTerritories;
          int targetArmyNum = this->territory->getArmyNum();
          vector<Territory*>::iterator iter; //iterator to iterate through player territories
          if (orderValid) {       
                this->territory->setArmyNum(targetArmyNum*2);
               this->territory->getOwner()->removeTerritory(territory);
               this->territory->removeOwner();    //making the territory neutral
               cout << "Blockade order executed" << endl;
               playerTerritories = this->player->getTerritories();
               std::cout << "The vector elements are : " << endl;
               for(int i=0; i < playerTerritories.size(); i++){
                    std::cout << *playerTerritories.at(i) << ' '<< endl;
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


     bool Airlift  :: validate() {
          bool isValid;
          isValid = true;
          vector<Territory*> playerTerritories;
          playerTerritories = player->getTerritories(); //getting the territories of player issuing the order
          if((std::find(playerTerritories.begin(), playerTerritories.end(), this->start) != playerTerritories.end()) && (std::find(playerTerritories.begin(), playerTerritories.end(), this->target) != playerTerritories.end())){
               cout << "The airlift order is valid." << endl;
               isValid = true;
          }
         else{
             cout << "The airlift order is invalid." << endl; 
             isValid = false;
         }
        return isValid;
     }  

     void Airlift  :: execute() {
          bool orderValid = this->validate();
          if (orderValid) {       
               this->start->subtractArmyNum(armies);
               this->target->addArmyNum(armies);
               cout << "airlift order executed" << endl;
          }
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

     bool Negotiate  :: validate() {
          bool isValid;
          isValid = true;
          if(this->player == this->targetPlayer){
               cout << "The airlift order is invalid." << endl;
               isValid = false;
          }
          else{
               isValid = true;
          }
          return isValid;
     }  

     void Negotiate  :: execute() {
          bool orderValid = this->validate();
          if (orderValid) {       



          }
     }   
