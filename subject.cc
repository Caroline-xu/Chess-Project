#include "subject.h"
using namespace std;

void Subject::setBoard(ChessBoard *b) {
        board = b;
}

ChessBoard *Subject::getBoard() {
    return board;
}

void Subject::attach(Observer *o) {
    observers.emplace_back(o);
}

void Subject::notifyObservers(Command com) {
    for (auto &ob : observers) {
        ob->notify(com, *this);
    }
}
