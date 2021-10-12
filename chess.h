#ifndef CHESS_H
#define CHESS_H
#include "observer.h"
#include "stat.h"
#include "subject.h"

class Chess : public Subject {
    Pos position;
    Colour colour;
    bool noMove = true;
    char type = 0;
    Side side = Side::Down;
protected:
    // return true if the chess in position p and chess this is in the diagonal direction to each other
    // and there is no chess between the chess in p and this diagonally. False otherwise.
    bool isPieced(Pos p);
    // return true if the chess in position p and chess this is in the horizontal direction to each other
    // and there is no chess between the chess in p and this horizontally. False otherwise.
    bool isPieceh(Pos p);
    // return true if the chess in position p and chess this is in the vertical direction to each other
    // and there is no chess between the chess in p and this vertically. False otherwise.
    bool isPiecev(Pos p);
    Chess(Pos p, Colour c, char t, ChessBoard *b, Side s);
public:
    Pos getPos();
    Colour getColo();
    void setnoMove(bool n);
    bool getnoMove();
    char getType();
    virtual bool isLegalmove(Pos p) = 0;
    Side getSide();
};

class Pawn : public Chess{
public:
  Pawn(Pos p, Colour c, char t, ChessBoard *b, Side s);
  bool isLegalmove(Pos p) override;
};

class King: public Chess {
public:
  King(Pos p, Colour c, char t, ChessBoard *b, Side s);
  bool isLegalmove(Pos p) override;
  /*add more public or private method if nedded.*/
};


class Rook: public Chess {
public:
  Rook(Pos p, Colour c, char t, ChessBoard *b, Side s);
  bool isLegalmove(Pos p) override;
};

class Queen: public Chess {
public:
  Queen(Pos p, Colour c, char t, ChessBoard *b, Side s);
  bool isLegalmove(Pos p) override;
};


class Bishop: public Chess {
public:
  Bishop(Pos p, Colour c, char t, ChessBoard *b, Side s);
  bool isLegalmove(Pos p) override;
};

class Knight: public Chess {
public:
  Knight(Pos p, Colour c, char t, ChessBoard *b, Side s);
  bool isLegalmove(Pos p) override;
};

#endif
