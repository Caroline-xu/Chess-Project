#ifndef SUBJECT_H
#define SUBJECT_H
#include <vector>
#include "stat.h"
#include <memory>
#include "observer.h"
class ChessBoard;
//class Observer;


class Subject {
    std::vector<Observer *> observers;
    ChessBoard *board = nullptr;
protected:
    void setBoard(ChessBoard *b);
    ChessBoard* getBoard();
public:
    virtual void setnoMove(bool n) = 0;
    virtual bool isLegalmove(Pos p) = 0;
    virtual char getType() = 0;
    virtual Colour getColo() = 0;
    virtual bool getnoMove() = 0;
    virtual Side getSide() = 0;
    virtual Pos getPos() = 0;
    void attach(Observer *);
    void notifyObservers(Command com);
};


#endif
