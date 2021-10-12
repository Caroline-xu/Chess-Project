# include "chess.h"
#include <cmath>
#include "chessboard.h"
using namespace std;

//========================================== CHESS ================================================
Pos Chess::getPos() {
    return position;
}

Colour Chess::getColo() {
    return colour;
}
void Chess::setnoMove(bool n) {noMove = n;}

bool Chess::getnoMove() {return noMove;}

char Chess::getType () {return type;}

Side Chess::getSide() {return side;}



bool Chess::isPieced(Pos p) {
    Pos tempP = getPos();
    int toC = p.getCol();
    int toR = p.getRow();
    int fromC = tempP.getCol();
    int fromR = tempP.getRow();
    int Hd = toC - fromC;
    int Vd = toR - fromR;
    if (abs(Hd) != abs(Vd)) return false;
    int i = 0, k = 0;
    if (Hd > 0) i = 1;
    else i = -1;
    if (Vd > 0) k = 1;
    else k = -1;
    fromC += i;
    fromR += k;
    ChessBoard* temp = this->getBoard();
    while (fromC != toC) {
        if (temp->getChess(Pos{fromR, fromC}) != Colour::NoColour) return false;
        fromC += i;
        fromR += k;
    }
    return true;
}


bool Chess::isPieceh(Pos p){
    Pos tempP = getPos();
    int toC = p.getCol();
    int toR = p.getRow();
    int fromC = tempP.getCol();
    int fromR = tempP.getRow();
    int Hd = toC - fromC;
    int Vd = toR - fromR;
    if (Vd != 0) return false;
    int i = 0;
    if (Hd > 0) i = 1;
    else i = -1;
    fromC += i;
    ChessBoard* temp = this->getBoard();
    while (fromC != toC) {
        if (temp->getChess(Pos{fromR, fromC}) != Colour::NoColour) return false;
        fromC += i;
    }
    return true;
}

bool Chess::isPiecev(Pos p) {
    Pos tempP = getPos();
    int toC = p.getCol();
    int toR = p.getRow();
    int fromC = tempP.getCol();
    int fromR = tempP.getRow();
    int Hd = toC - fromC;
    int Vd = toR - fromR;
    if (Hd != 0) return false;
    int k = 0;
    if (Vd > 0) k = 1;
    else k = -1;
    fromR += k;
    ChessBoard* temp = this->getBoard();
    while (fromR != toR) {
        if (temp->getChess(Pos{fromR, fromC}) != Colour::NoColour) return false;
        fromR += k;
    }
    return true;
}

Chess::Chess(Pos p, Colour c, char t, ChessBoard *b, Side s): position{p}, colour{c}, type{t}, side{s} { setBoard(b); }

//====================================== PAWN ==========================================================
Pawn::Pawn(Pos p, Colour c, char t, ChessBoard *b, Side s): Chess{p, c, t, b, s} {}


bool Pawn::isLegalmove(Pos p) {
    if (p == getPos()) return false;
    Pos tempP = getPos();
    int toC = p.getCol();
    int toR = p.getRow();
    int fromC = tempP.getCol();
    int fromR = tempP.getRow();
    int Hd = toC - fromC;
    int Vd = toR - fromR;
    int i = 0, k = 0;
    if (Hd > 0) i = 1;
    else i = -1;
    if (Vd > 0) k = 1;
    else k = -1;
    ChessBoard* temp = this->getBoard();
    if (temp->getChess(p) == this->getColo()) return false;// whether the the pos p has the same colour as this
    if (getSide() == Side::Down) {
        if (Vd < 0) return false;
    } else {
        if (Vd > 0) return false;
    }
    if (this->isPiecev(p)) {
        if (temp->getChess(p) != Colour::NoColour) return false;
        if (p == Pos{fromR + 2 * k, fromC}) {
            if (this->getnoMove()) return true;
            return false;
        }
        if (p == Pos{fromR + k, fromC}) return true;
        return false;
    }
    if (this->isPieced(p)) {
        if (p != Pos{fromR + k, fromC + i}) return false;
        if (temp->getChess(p) != Colour::NoColour) return true;
        if (temp->getFirst() == Pos{fromR, fromC + i}) return true;
        return false;
    }
    return false;
}

//==============================================KING=========================================================
King::King(Pos p, Colour c, char t, ChessBoard *b, Side s): Chess{p, c, t, b, s} {}

bool King::isLegalmove(Pos p) {
    if (p.getCol() > 7 || p.getCol() < 0 || p.getRow() > 7 || p.getRow() < 0) return false;
    if (p == getPos()) return false;
    ChessBoard* temp = this->getBoard();
    if (temp->getChess(p) == this->getColo()) return false;
    Pos tempP = getPos();
    int toC = p.getCol();
    int toR = p.getRow();
    int fromC = tempP.getCol();
    int fromR = tempP.getRow();
    int Hd = toC - fromC;
    int Vd = toR - fromR;
    if (Hd == 2 && Vd == 0 && (fromR == 7 || fromR == 0)) {// right castling
        if (temp->getChess_type(Pos{fromR, 7}) == 'R' && temp->getChess(Pos{fromR, 7}) == getColo() && getnoMove() && temp->isNevermove(Pos{fromR, 7}) && isPieceh(Pos{fromR, 7})) {
            for (int i = fromC; i <= fromC + Hd; ++i) {
                if (temp->isChecked(this->getPos(), Pos{fromR, i}, this->getColo())) return false;
            }
            return true;
        }
        return false;
    }
    if (Hd == -3 && Vd == 0 && (fromR == 7 || fromR == 0)) {
        if (temp->getChess_type(Pos{fromR, 0}) == 'R' && temp->getChess(Pos{fromR, 0}) == getColo() && getnoMove() && temp->isNevermove(Pos{fromR, 0}) && isPieceh(Pos{fromR, 0})) {
            for (int i = fromC; i >= fromC + Hd; --i) {
                if (temp->isChecked(this->getPos(), Pos{fromR, i}, this->getColo())) return false;
            }
            return true;
        }
        return false;
    }
    if (abs(Hd) < 2 && abs(Vd) < 2) {
        if (temp->isChecked(this->getPos(), p, this->getColo())) return false;
        return true;
    }
    return false;
}

//=======================================================ROCK==============================================================================
Rook::Rook(Pos p, Colour c, char t, ChessBoard *b, Side s): Chess{p, c, t, b, s} {}

bool Rook::isLegalmove(Pos p) {
    if (p == getPos()) return false;
    ChessBoard* temp = this->getBoard();
    if (temp->getChess(p) == this->getColo()) return false;
    if (isPieceh(p) || isPiecev(p)) {
        return true;
    }
    return false;
}


//====================================================QUEEN=====================================================================
Queen::Queen(Pos p, Colour c, char t, ChessBoard *b, Side s): Chess{p, c, t, b, s} {}

bool Queen::isLegalmove(Pos p) {
    if (p == getPos()) return false;
    ChessBoard* temp = this->getBoard();
    if (temp->getChess(p) == this->getColo()) return false;
    if (isPieced(p) || isPiecev(p) || isPieceh(p)) {
        return true;
    }
    return false;
}


//=================================================BISHOP======================================================================
Bishop::Bishop(Pos p, Colour c, char t, ChessBoard *b, Side s): Chess{p, c, t, b, s} {}
bool Bishop::isLegalmove(Pos p) {
    if (p == getPos()) return false;
    ChessBoard* temp = this->getBoard();
    if (temp->getChess(p) == this->getColo()) return false;
    if (isPieced(p)) {
        return true;
    }
    return false;
}

//================================================KNIGHT========================================================================

Knight::Knight(Pos p, Colour c, char t, ChessBoard *b, Side s): Chess{p, c, t, b, s} {}
bool Knight::isLegalmove(Pos p) {
    if (p == getPos()) return false;
    ChessBoard* temp = this->getBoard();
    if (temp->getChess(p) == this->getColo()) return false;
    Pos tempP = getPos();
    int toC = p.getCol();
    int toR = p.getRow();
    int fromC = tempP.getCol();
    int fromR = tempP.getRow();
    int Hd = toC - fromC;
    int Vd = toR - fromR;
    if (abs(Hd) != abs(Vd)) {
        if ((abs(Hd) == 2 || abs(Hd) == 1) && (abs(Vd) == 2 || abs(Vd) == 1)) {
            return true;
        }
    }
    return false;
}
