#include <iostream>
#include <iterator>
#include <list>
#include "Orders.h"

using namespace std;

int main(){

    Deploy *deploy = new Deploy(2, "america");

    OrdersList *ordl = new OrdersList(*deploy);







return 0;
};
