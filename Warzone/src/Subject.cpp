#include "../include/Subject.h"
#include "../include/Observer.h"

Subject::Subject(){
    observers = new list <Observer*>;
}

Subject::~Subject(){
    delete observers;
}

void Subject::Attach(Observer *observer) {
    observers->push_back(observer);
};

void Subject::Detach(Observer *observer) {
    observers-> remove(observer);
};

void Subject::Notify() {
    for(list<Observer*>::iterator i = observers->begin(); i != observers ->end(); i++){
        (*i)->Update();
    }
};
