#include <iostream>
#include <string>
#include "stat.h"
using namespace std;

Pos::Pos(int row, int col): row{row}, col{col} {};

bool Pos::operator== (Pos other) {
    if ((row == other.row) && (col == other.col)) return true;
    return false;
}

bool Pos::operator!= (Pos other) {
  return !(*this == other);
}

int Pos::getRow() {
    return this->row;
}

int Pos::getCol() {
    return this->col;
}


Pos getPos(const string &move) {
    char first = move[0];
    char second = move[1];
    int row = 0;
    int col = 0;
    if (first == 'a') col = 0;
    else if (first == 'b') col = 1;
    else if (first == 'c') col = 2;
    else if (first == 'd') col = 3;
    else if (first == 'e') col = 4;
    else if (first == 'f') col = 5;
    else if (first == 'g') col = 6;
    else col = 7;
    if (second == '1') row = 0;
    else if (second == '2') row = 1;
    else if (second == '3') row = 2;
    else if (second == '4') row = 3;
    else if (second == '5') row = 4;
    else if (second == '6') row = 5;
    else if (second == '7') row = 6;
    else row = 7;
    return Pos{row, col};
}

std::string getMove(Pos p) {
    string first = "";
    string second = "";
    int col = p.getCol();
    int row = p.getRow();
    if (col == 0) first = "a";
    else if (col == 1) first = "b";
    else if (col == 2) first = "c";
    else if (col == 3) first = "d";
    else if (col == 4) first = "e";
    else if (col == 5) first = "f";
    else if (col == 6) first = "g";
    else first = "h";
    if (row == 0) second = "1";
    else if (row == 1) second = "2";
    else if (row == 2) second = "3";
    else if (row == 3) second = "4";
    else if (row == 4) second = "5";
    else if (row == 5) second = "6";
    else if (row == 6) second = "7";
    else second = "8";
    return first + second;
}



ostream& operator<<(ostream &out, const Colour &c) {
   if (c == Colour::White) out << "White";
   if (c == Colour::Black) out << "Black";
   if (c == Colour::NoColour) out << "NoColour";

   return out;
}

void decreaseChessCount(char type, int &r, int &n, int &b, int &q, int &p, int &R, int &N, int &B, int &Q, int &P, int &numwking, int &numbking) {
    if (type == 'r' && r > 0) {
        r -= 1;
    } else if (type == 'n' && n > 0) {
        n -= 1;
    } else if (type == 'b' && b > 0) {
        b -= 1;
    } else if (type == 'q' && q > 0) {
        q -= 1;
    } else if (type == 'p' && p > 0) {
        p -= 1;
    } else if (type == 'R' && R > 0) {
        R -= 1;
    } else if (type == 'N' && N > 0) {
        N -= 1;
    } else if (type == 'B' && B > 0) {
        B -= 1;
    } else if (type == 'Q' && Q > 0) {
        Q -= 1;
    } else if (type == 'P' && P > 0) {
        P -= 1;
    } else if (type == 'K' && numwking > 0) {
        numwking -= 1;
    } else if (type == 'k' && numbking > 0) {
        numbking -= 1;
    }
}
