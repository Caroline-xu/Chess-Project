#ifndef STAT_H
#define STAT_H
#include <string>
#include <iostream>
enum class Colour { NoColour, Black, White };
enum class Side {Up, Down, Noside};
enum class Command {Remove, Set};// new class.

class Pos {
    int row;
    int col;
public:
    Pos(int row = 0, int col = 0);
    bool operator== (Pos other);
    bool operator!= (Pos other);
    int getRow();
    int getCol();
};

std::ostream &operator<<(std::ostream &out, const Colour &c);

// Global function: transfer the string (chessboard position) to the position we use for our internal chessboard.
Pos getPos(const std::string &move);
std::string getMove(Pos p);
std::ostream &operator<<(std::ostream &out, const Colour &c);
void decreaseChessCount(char type, int &r, int &n, int &b, int &q, int &p, int &R, int &N, int &B, int &Q, int &P, int &numwking, int &numbking);
#endif
