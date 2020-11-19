#pragma once
#include "Observer.h"
#include <list>
using namespace std;

class Subject {
    public:
        virtual void Attach (Observer *observer);
        virtual void Detach (Observer *observer);
        virtual void Notify (Observer *observer);
        Subject();
        ~Subject();
    private:
        list<Observer*> *observers;
};
