#ifndef HISTORY_H
#define HISTORY_H
#include "stat.h"
#include <memory>
class Subject;

class HistoryMove {
    Pos from = Pos{-1, -1};
    Pos to = Pos{-1, -1};
    std::shared_ptr<Subject> chess;
    std::shared_ptr<Subject> beside; //it is used to store the information bout the special rule for Pawn
    std::shared_ptr<Subject> end;
public:
    HistoryMove(Pos from, Pos to, std::shared_ptr<Subject> chess, std::shared_ptr<Subject> beside = nullptr, std::shared_ptr<Subject> end = nullptr);
};

 #endif
