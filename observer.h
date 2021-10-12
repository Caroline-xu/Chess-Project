#ifndef OBSERVER_H_
#define OBSERVER_H_
#include "stat.h"
class Subject;
class Chess;

class Observer {
public:
    virtual void notify(Command com, Subject &chess) = 0; // pass the Subject that called
    // the notify method
};
#endif
