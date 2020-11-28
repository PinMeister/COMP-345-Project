#include "../include/MapLoader.h"
#include "../include/Map.h"

using namespace std;

int main(){
    ConquestFileReader *conquestLoader = new ConquestFileReader("Warzone/maps/Montreal.map");
    conquestLoader->parse();
    conquestLoader->showResult();
    return 0;
}
