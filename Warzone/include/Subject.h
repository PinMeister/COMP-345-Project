#pragma once
#include "Observer.h"
#include <list>
using namespace std;

class Subject {
    public:
        virtual void Attach (Observer *observer);
        virtual void Detach (Observer *observer);
        virtual void Notify ();
        Subject();
        ~Subject();
    private:
        list<Observer*> *observers;
};
