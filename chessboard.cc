#include "chessboard.h"
#include "subject.h"
#include "history.h"
#include "textdisplay.h"
#include "graphic.h"
using namespace std;
// The rule of how we tranfer out position to our 8 * * array that represent the actually chessboard
// For example the structure of the 8 * 8 array are made by a big outside vector
// let us call it vector o and each element of o is the small inside vector call it i, that contain
// 8 element which is the pointer that point to the actually chess.
// for each i vector we use it to represent the row of the chessboard.
// Let us make some example to demonstrate the relationship: theBoard[0][0] represent the pos(7,0) chess.
// theBoard[0][1] represent the Pos(7, 1) theBoard[0][2] represent Pos(7, 2) ....
// theBoard[1][0] represent the Pos(6, 0), theBoard[1][1] repressent the pos(6, 1).....

//===============================================helper function====================================================
//arrayPos return the correspond row position in the array of the Board if c == 'r', and otherwise
//return the correspond column position in the array of the Board.
int arrayPos(Pos p, char opt){
    if (opt == 'r') return (7 - p.getRow());
    return p.getCol();
}

bool notinside(int c) {
  if (c > 7 || c < 0) return true;
  return false;
}

void ChessBoard::setChess(Pos p, Colour c, char t, Side s) {
    int r = arrayPos(p, 'r');
    int col = arrayPos(p, 'c');
    if (t == 'P') theBoard[r][col] = dynamic_pointer_cast<Subject> (make_shared<Pawn> (p, c, t, this, s));
    else if (t == 'K') theBoard[r][col] = dynamic_pointer_cast<Subject> (make_shared<King> (p, c, t, this, s));
    else if (t == 'R') theBoard[r][col] = dynamic_pointer_cast<Subject> (make_shared<Rook> (p, c, t, this, s));
    else if (t == 'Q') theBoard[r][col] = dynamic_pointer_cast<Subject> (make_shared<Queen> (p, c, t, this, s));
    else if (t == 'B') theBoard[r][col] = dynamic_pointer_cast<Subject> (make_shared<Bishop> (p, c, t, this, s));
    else if (t == 'N') theBoard[r][col] = dynamic_pointer_cast<Subject> (make_shared<Knight> (p, c, t, this, s));
    theBoard[r][col]->attach(dynamic_cast<Observer *> (td.get()));
    if (gd != nullptr) theBoard[r][col]->attach(dynamic_cast<Observer *> (gd));
    theBoard[r][col]->notifyObservers(Command::Set);
    return;
}


void ChessBoard::moveChess(Pos p) {
    int r = arrayPos(p, 'r');
    int col = arrayPos(p, 'c');
    theBoard[r][col]->notifyObservers(Command::Remove);
    theBoard[r][col] = nullptr;
    return;
}

void ChessBoard::setGraphic(GraphicsDisplay *gd) {
    this->gd = gd;
}

int ChessBoard::isOver(Colour &c) {
    if (isnoMove(Colour::White) || isnoMove(Colour::Black)) {
        c = Colour::NoColour;
        return 1;
    }
    for (int i = 0; i < 8; ++i) {
        for (int k = 0; k < 8; ++k) {
            if (theBoard[i][k] == nullptr) continue;
            if (theBoard[i][k]->getType() != 'K') continue;
            else {
                int row_p = 7 - i;
                int col_p = k;
                Colour tempc = theBoard[i][k]->getColo();
                if (!(theBoard[i][k]->isLegalmove(Pos{row_p + 1, col_p}) || theBoard[i][k]->isLegalmove(Pos{row_p - 1, col_p}) ||
                    theBoard[i][k]->isLegalmove(Pos{row_p, col_p + 1}) || theBoard[i][k]->isLegalmove(Pos{row_p, col_p - 1}) ||
                    theBoard[i][k]->isLegalmove(Pos{row_p + 1, col_p + 1}) || theBoard[i][k]->isLegalmove(Pos{row_p - 1, col_p - 1}) ||
                    theBoard[i][k]->isLegalmove(Pos{row_p + 1, col_p - 1}) || theBoard[i][k]->isLegalmove(Pos{row_p - 1, col_p + 1}))) {
                    if (isChecked(Pos{-1, -1}, Pos{row_p, col_p}, tempc)) {
                      if (tempc == Colour::White) c = Colour::Black;
                      else c = Colour::White;
                      return 2;
                    }
                }
            }
        }
    }
    c = Colour::NoColour;
    return 0;
}

bool ChessBoard::isnoMove(Colour colo) {
    for (int r = 0; r < 8; ++r) {
      for (int c = 0; c < 8; ++c) {
        if (theBoard[r][c] == nullptr) continue;
        if (theBoard[r][c]->getColo() != colo) continue;
        for (int i = 0; i < 8; ++i) {
          for (int k = 0; k < 8; ++k) {
            if(theBoard[r][c]->isLegalmove(Pos{7 - i, k})) return false;
          }
        }

      }
    }
    return true;
}


//remeber we must!!! intilize the Board first and then int game.
void ChessBoard::intiBoard() {
    while (!history.empty()) history.pop();
    if (!(theBoard.empty())) {
      for (int i = 0; i < 8; ++i) {
        for (int k = 0; k < 8; ++k) {
          theBoard[i][k] = nullptr;
        }
      }
    }
    if (gd != nullptr) {
      gd->clear();
    }
    for (int r = 0; r < 8; ++r) {
        vector<shared_ptr<Subject>> row;
        for (int c = 0; c < 8; ++c) {
            row.emplace_back(nullptr);
        }
        theBoard.emplace_back(row);
    }
    td = make_shared<TextDisplay> ();
}

void ChessBoard::intiGame(Colour down) {
    Colour up = Colour::Black;
    if (down != Colour::White) {
        up = Colour::White;
    }
    for (int r = 0; r < 8; ++r) {
        if (r == 2 || r == 3 || r == 4 || r ==5) continue;
        if (r == 1) {
            for (int c = 0; c < 8; ++c) setChess(Pos{7 - r, c}, up, 'P', Side::Up);
        }
        if (r == 6) {
            for (int c = 0; c < 8; ++c) setChess(Pos{7 - r, c}, down, 'P', Side::Down);
        }
        if (r == 0 || r == 7) {
            Colour tc = up;
            Side ts = Side::Up;
            if (r == 7) {
                tc = down;
                ts = Side::Down;
            }
            for (int c = 0; c < 3; ++c) {
                if (c == 0) {
                    setChess(Pos{7 - r, c}, tc, 'R', ts);
                    setChess(Pos{7 - r, 7 - c}, tc, 'R', ts);
                }
                if (c == 1) {
                    setChess(Pos{7 - r, c}, tc, 'N', ts);
                    setChess(Pos{7 - r, 7 - c}, tc, 'N', ts);
                }
                if (c == 2) {
                    setChess(Pos{7 - r, c}, tc, 'B', ts);
                    setChess(Pos{7 - r, 7 - c}, tc, 'B', ts);
                }
            }
            setChess(Pos{7 - r, 3}, tc, 'Q', ts);
            setChess(Pos{7 - r, 4}, tc, 'K', ts);
        }
    }
}



bool ChessBoard::setMove(Pos from, Pos to, char settype, char type) {
    if (from == Pos{-1, -1} || to == Pos{-1, -1}) {
        if (from == Pos{-1, -1}) {
            if (to.getCol() > 7 || to.getCol() < 0 || to.getRow() > 7 || to.getRow() < 0) return false;
            int rt = arrayPos(to, 'r');
            int ct = arrayPos(to, 'c');
            if (settype == 'P') {
                if (rt == 0 || rt == 7) return false;
                if (rt == 6) {
                    setChess(to, Colour::White, 'P', Side::Down);
                    theBoard[rt][ct]->setnoMove(true);
                    return true;
                }
                setChess(to, Colour::White, 'P', Side::Down);
                theBoard[rt][ct]->setnoMove(false);
                return true;
            }
            if (settype == 'p') {
                if (rt == 0 || rt == 7) return false;
                if (rt == 1) {
                    setChess(to, Colour::Black, 'P', Side::Up);
                    theBoard[rt][ct]->setnoMove(true);
                    return true;
                }
                setChess(to, Colour::Black, 'P', Side::Up);
                theBoard[rt][ct]->setnoMove(false);
                return true;
            }
            if (settype == 'K') {
                if (isChecked(Pos{-1, -1}, to, Colour::White)) return false; // need to be check again!
                setChess(to, Colour::White, 'K', Side::Down);
                theBoard[rt][ct]->setnoMove(true);
                return true;
            }
            if (settype == 'k') {
                if (isChecked(Pos{-1, -1}, to, Colour::Black)) return false;
                setChess(to, Colour::Black, 'K', Side::Up);
                theBoard[rt][ct]->setnoMove(true);
                return true;
            }
            if (64 < settype && settype < 91) {
                setChess(to, Colour::White, settype, Side::Down);
                theBoard[rt][ct]->setnoMove(true);
                return true;
            }
            setChess(to, Colour::Black, settype - 32, Side::Up);
            theBoard[rt][ct]->setnoMove(true);
            return true;
        }
        if (to == Pos{-1, -1}) {
            if (from.getCol() > 7 || from.getCol() < 0 || from.getRow() > 7 || from.getRow() < 0) return false;
            int rt = arrayPos(from, 'r');
            int ct = arrayPos(from, 'c');
            if (theBoard[rt][ct] == nullptr) return false;
            moveChess(from);
            return true;
        }
    }

    int rf = arrayPos(from, 'r');
    int cf = arrayPos(from, 'c');
    int rt = arrayPos(to, 'r');
    int ct = arrayPos(to, 'c');
    int rfb = from.getRow();
    int cfb = from.getCol();
    int rtb = to.getRow();
    int ctb = to.getCol();
    if (from.getCol() > 7 || from.getCol() < 0 || from.getRow() > 7 || from.getRow() < 0) return false;
    if (to.getCol() > 7 || to.getCol() < 0 || to.getRow() > 7 || to.getRow() < 0) return false;
    if (theBoard[rf][cf]->getType() == 'P') {
         if (!(theBoard[rf][cf]->isLegalmove(to))) return false;// not legal move for pawn!
         if (rt == 7 || rt == 0) {// the case that Pawn reach the end side of the Board
            if (theBoard[rt][ct] == nullptr) {
                setChess(to, theBoard[rf][cf]->getColo(), type, theBoard[rf][cf]->getSide());
                theBoard[rt][ct]->setnoMove(false);
                history.emplace(new HistoryMove{from, to, nullptr, nullptr, theBoard[rf][cf]});
                moveChess(from);
                firstMove = Pos{-1, -1};
                return true;
            }
            else {
                history.emplace(new HistoryMove{from, to, theBoard[rt][ct], nullptr, theBoard[rf][cf]});
                moveChess(to);
                setChess(to, theBoard[rf][cf]->getColo(), type, theBoard[rf][cf]->getSide());
                theBoard[rt][ct]->setnoMove(false);
                moveChess(from);
                firstMove = Pos{-1, -1};
                return true;
            }
         }
         if (abs(to.getCol() - from.getCol()) == abs(to.getRow() - from.getRow())) {
             if (theBoard[rt][ct] != nullptr) {
                 history.emplace(new HistoryMove{from, to, theBoard[rt][ct]});
                 moveChess(to);
                 setChess(to, theBoard[rf][cf]->getColo(), theBoard[rf][cf]->getType(), theBoard[rf][cf]->getSide());
                 theBoard[rt][ct]->setnoMove(false);
                 moveChess(from);
                 firstMove = Pos{-1, -1};
                 return true;
             }
             else {
                 history.emplace(new HistoryMove{from, to, nullptr, theBoard[rf][ct], nullptr});
                 moveChess(Pos{rfb, ctb});
                 setChess(to, theBoard[rf][cf]->getColo(), theBoard[rf][cf]->getType(), theBoard[rf][cf]->getSide());
                 theBoard[rt][ct]->setnoMove(false);
                 moveChess(from);
                 firstMove = Pos{-1, -1};
                 return true;
             }
         }
         if (abs(to.getRow() - from.getRow()) == 2) {
             history.emplace(new HistoryMove{from, to, nullptr});
             setChess(to, theBoard[rf][cf]->getColo(), theBoard[rf][cf]->getType(), theBoard[rf][cf]->getSide());
             theBoard[rt][ct]->setnoMove(false);
             moveChess(from);
             firstMove = to;
             return true;
         }
         history.emplace(new HistoryMove{from, to, nullptr});
         setChess(to, theBoard[rf][cf]->getColo(), theBoard[rf][cf]->getType(), theBoard[rf][cf]->getSide());
         theBoard[rt][ct]->setnoMove(false);
         moveChess(from);
         firstMove = Pos{-1, -1};
         return true;
    }
    if (theBoard[rf][cf]->getType() == 'K') {
        if (!(theBoard[rf][cf]->isLegalmove(to))) return false;
        if (abs(ctb - cfb) == 1 || abs(ctb - cfb) == 0) {
            if (theBoard[rt][ct] != nullptr) {
                 history.emplace(new HistoryMove{from, to, theBoard[rt][ct]});
                 moveChess(to);
                 setChess(to, theBoard[rf][cf]->getColo(), theBoard[rf][cf]->getType(), theBoard[rf][cf]->getSide());
                 theBoard[rt][ct]->setnoMove(false);
                 moveChess(from);
                 firstMove = Pos{-1, -1};
                 return true;
             }
             history.emplace(new HistoryMove{from, to, nullptr});
             setChess(to, theBoard[rf][cf]->getColo(), theBoard[rf][cf]->getType(), theBoard[rf][cf]->getSide());
             theBoard[rt][ct]->setnoMove(false);
             moveChess(from);
             firstMove = Pos{-1, -1};
             return true;
        }
        shared_ptr<Subject> temp;
        if (ctb - cfb > 0) {// right castling
            temp = theBoard[rt][ct + 1];
            moveChess(Pos{rtb, ctb + 1});
        }
        if (ctb - cfb < 0) {
            cout << "debug" << endl;
            temp = theBoard[rt][ct - 1];
            moveChess(Pos{rtb, ctb - 1});
        }
        setChess(to, theBoard[rf][cf]->getColo(), theBoard[rf][cf]->getType(), theBoard[rf][cf]->getSide());
        moveChess(from);
        setChess(from, temp->getColo(), temp->getType(), temp->getSide());
        temp = nullptr;
        theBoard[rt][ct]->setnoMove(false);
        theBoard[rf][cf]->setnoMove(false);
        firstMove = Pos{-1, -1};
        return true;
    }
    if (!(theBoard[rf][cf]->isLegalmove(to))) return false;
    if (theBoard[rt][ct] != nullptr) {
        history.emplace(new HistoryMove{from, to, theBoard[rt][ct]});
        moveChess(to);
        setChess(to, theBoard[rf][cf]->getColo(), theBoard[rf][cf]->getType(), theBoard[rf][cf]->getSide());
        theBoard[rt][ct]->setnoMove(false);
        moveChess(from);
        firstMove = Pos{-1, -1};
        return true;
    }
    history.emplace(new HistoryMove{from, to, nullptr});
    setChess(to, theBoard[rf][cf]->getColo(), theBoard[rf][cf]->getType(), theBoard[rf][cf]->getSide());
    theBoard[rt][ct]->setnoMove(false);
    moveChess(from);
    firstMove = Pos{-1, -1};
    return true;
}

void ChessBoard::backMove() {}



Colour ChessBoard::getChess(Pos p) {
    int r = arrayPos(p, 'r');
    int c = arrayPos(p, 'c');
    if (theBoard[r][c] == nullptr) return Colour::NoColour;
    return theBoard[r][c]->getColo();
}


char ChessBoard::getChess_type(Pos p) {
    int r = arrayPos(p, 'r');
    int c = arrayPos(p, 'c');
    if (theBoard[r][c] == nullptr) return 0;
    return theBoard[r][c]->getType();
}

Pos ChessBoard::getFirst() {
    return firstMove;

}
bool ChessBoard::isNevermove(Pos p) {
    int r = arrayPos(p, 'r');
    int c = arrayPos(p, 'c');
    if (theBoard[r][c] == nullptr) return false;
    return theBoard[r][c]->getnoMove();
}




bool ChessBoard::isChecked(Pos pf, Pos pt, Colour c) {
    if (pt.getCol() > 7 || pt.getCol() < 0 || pt.getRow() > 7 || pt.getRow() < 0) return true;
    int rt = arrayPos(pt, 'r');
    int ct = arrayPos(pt, 'c');
    int rf = arrayPos(pf, 'r');
    int cf = arrayPos(pf, 'c');
    shared_ptr<Subject> temp = nullptr;
    temp = theBoard[rt][ct];
    theBoard[rt][ct] = nullptr;
    if (pf != Pos{-1, -1}) {
      theBoard[rt][ct] = theBoard[rf][cf];
      theBoard[rf][cf] = nullptr;
    }
    else {
      theBoard[rt][ct] = dynamic_pointer_cast<Subject> (make_shared<King> (pt, c, 'K', this, Side::Down));
    }
    for (int i = 0; i < 8; ++i) {
        for (int k = 0; k < 8; ++k) {
            if (Pos{7 - i, k} == pt) continue;
            if (theBoard[i][k] == nullptr) continue;
            if (theBoard[i][k]->getColo() == c) continue;
            if (theBoard[i][k]->getType() == 'K') {
                if (!notinside((7 - i) + 1) && !notinside(k + 1)) {
                  if (Pos{(7 - i) + 1, k + 1} == pt) {
                    if (pf != Pos{-1, -1}) theBoard[rf][cf] = theBoard[rt][ct];
                    theBoard[rt][ct] = temp;
                    return true;
                  }
                }
                if (!notinside((7 - i) + 1) && !notinside(k)) {
                  if (Pos{(7 - i) + 1, k} == pt) {
                    if (pf != Pos{-1, -1}) theBoard[rf][cf] = theBoard[rt][ct];
                    theBoard[rt][ct] = temp;
                    return true;
                  }
                }
                if (!notinside((7 - i) + 1) && !notinside(k - 1)) {
                  if (Pos{(7 - i) + 1, k - 1} == pt) {
                    if (pf != Pos{-1, -1}) theBoard[rf][cf] = theBoard[rt][ct];
                    theBoard[rt][ct] = temp;
                    return true;
                  }
                }
                if (!notinside(7 - i) && !notinside(k + 1)) {
                  if (Pos{7 - i, k + 1} == pt) {
                    if (pf != Pos{-1, -1}) theBoard[rf][cf] = theBoard[rt][ct];
                    theBoard[rt][ct] = temp;
                    return true;
                  }
                }
                if (!notinside(7 - i) && !notinside(k - 1)) {
                  if (Pos{7 - i, k - 1} == pt) {
                    if (pf != Pos{-1, -1}) theBoard[rf][cf] = theBoard[rt][ct];
                    theBoard[rt][ct] = temp;
                    return true;
                  }
                }
                if (!notinside((7 - i) - 1) && !notinside(k + 1)) {
                  if (Pos{(7 - i) - 1, k + 1} == pt) {
                    if (pf != Pos{-1, -1}) theBoard[rf][cf] = theBoard[rt][ct];
                    theBoard[rt][ct] = temp;
                    return true;
                  }
                }
                if (!notinside((7 - i) - 1) && !notinside(k)) {
                  if (Pos{(7 - i) - 1, k} == pt) {
                    if (pf != Pos{-1, -1}) theBoard[rf][cf] = theBoard[rt][ct];
                    theBoard[rt][ct] = temp;
                    return true;
                  }
                }
                if (!notinside((7 - i) - 1) && !notinside(k - 1)) {
                  if (Pos{(7 - i) - 1, k - 1} == pt) {
                    if (pf != Pos{-1, -1}) theBoard[rf][cf] = theBoard[rt][ct];
                    theBoard[rt][ct] = temp;
                    return true;
                  }
                }
                continue;
            }
            if (theBoard[i][k]->isLegalmove(pt)) {
              if (pf != Pos{-1, -1}) theBoard[rf][cf] = theBoard[rt][ct];
              theBoard[rt][ct] = temp;
              return true;
           }
      }
    }
    if (pf != Pos{-1, -1}) theBoard[rf][cf] = theBoard[rt][ct];
    theBoard[rt][ct] = temp;
    return false;
}

Pos ChessBoard::kingInCheck() {
    for (int r = 0; r < 8; ++r) {
        for (int c = 0; c < 8; ++c) {
          if (theBoard[r][c] == nullptr) continue;
          if (theBoard[r][c]->getType() != 'K') continue;
          if (isChecked(Pos{-1, -1}, Pos{7 - r, c}, theBoard[r][c]->getColo())) return Pos{7 - r, c};
        }
    }
    return Pos{-1, -1};
}

void ChessBoard::changeNomove(Pos p, bool f) {
    theBoard[7 - p.getRow()][p.getCol()]->setnoMove(f);
}

char ChessBoard::getTypeinboard(Pos p) {
    if (theBoard[7 - p.getRow()][p.getCol()] == nullptr) return 0;
    char temp = theBoard[7 - p.getRow()][p.getCol()]->getType();
    if (theBoard[7 - p.getRow()][p.getCol()]->getColo() == Colour::White) return temp;
    return temp + 32;
}

Side ChessBoard::getsideinboard(Pos p) {
  if (theBoard[7 - p.getRow()][p.getCol()] == nullptr) return Side::Noside;
  return theBoard[7 - p.getRow()][p.getCol()]->getSide();
}


bool ChessBoard::isCapature(Pos nextp, std::shared_ptr<Subject> ch) {
    Colour tempc = ch->getColo();
    for (int r = 0; r < 8; ++r) {
      for (int c = 0; c < 8; ++c) {
        if (theBoard[r][c] != nullptr) {
          if (tempc != theBoard[r][c]->getColo()) {
            if (theBoard[r][c]->isLegalmove(nextp)) return true;
          }
        }
      }
    }
    return false;
}



//=============================================helper function============================================
template <typename V_Type>
void shufflefun(vector<V_Type> &v) {
    // use a time-based seed for the default seed value
	unsigned seed = chrono::system_clock::now().time_since_epoch().count();

    default_random_engine rng{seed};

	for ( int i = 0; i < 1000; i++ ) {
		//std::shuffle( v.begin(), v.end(), std::default_random_engine(seed) );
		shuffle( v.begin(), v.end(), rng );
	} // for

	return;
}


void ChessBoard::level1(Pos &from, Pos &to, Colour c, char &promot) {
    // nothing in from and to at the beginning
    vector< shared_ptr<Subject> > colourSub;
    vector<Pos> wholePos;
    vector<char> promotv = {'Q', 'N', 'B', 'R'};
    vector <Pos> escapecheck;
    if (from != Pos{-1, -1}) {
      int br = arrayPos(from, 'r');
      int bc = arrayPos(from, 'c');
      for (int i = 0; i < 8; ++i) {
          for (int j = 0; j < 8; ++j) {
            if (theBoard[br][bc]->isLegalmove(Pos{7-i, j})) escapecheck.emplace_back(Pos{7 - i, j});
          }
      }
      shufflefun(escapecheck);
      to = escapecheck[0];
      return;
    }
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (theBoard[i][j] == nullptr) {
                wholePos.emplace_back(Pos{7 - i, j});
                continue;
            }
            if (theBoard[i][j] != nullptr && theBoard[i][j]->getColo() == c) {
                colourSub.emplace_back(theBoard[i][j]);
            }
            wholePos.emplace_back(theBoard[i][j]->getPos());
        }
    }
    shufflefun(colourSub);
    shufflefun(wholePos);


    for (auto s : colourSub) {
        for (auto t : wholePos) {
            if (s->isLegalmove(t)) {
                shufflefun(promotv);
                promot = promotv[0];
                from = s->getPos();
                to = t;
                return;
            }
        }
    }
}


void ChessBoard::level2(Pos &from, Pos &to, Colour c, char &promot) {
    vector< shared_ptr<Subject> > colourSub;
    vector<Pos> othercolourPos;
    vector<char> promotv = {'Q', 'N', 'B', 'R'};
    vector <Pos> escapecheck;
    Pos kingpos;
    Colour otherc;
    if (from != Pos{-1, -1}) {
      int br = arrayPos(from, 'r');
      int bc = arrayPos(from, 'c');
      for (int i = 0; i < 8; ++i) {
          for (int j = 0; j < 8; ++j) {
            if (theBoard[br][bc]->isLegalmove(Pos{7-i, j})) escapecheck.emplace_back(Pos{7 - i, j});
          }
      }
      shufflefun(escapecheck);
      to = escapecheck[0];
      return;
    }

    if (c == Colour::Black) { otherc = Colour::White; }
    else if (c == Colour::White) { otherc = Colour::Black; }
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (theBoard[i][j] == nullptr) continue;
            if (theBoard[i][j]->getColo() == c) {
                colourSub.emplace_back(theBoard[i][j]);
            } else if (theBoard[i][j]->getColo() == otherc) {
                othercolourPos.emplace_back(theBoard[i][j]->getPos());
                if (theBoard[i][j]->getType() == 'K') {kingpos = theBoard[i][j]->getPos(); }
            }
        }
    }
    shufflefun(colourSub);
    shufflefun(othercolourPos);

    // check if we can check the king
    for (auto  s : colourSub) {
        if (s->isLegalmove(kingpos)) {
            shufflefun(promotv);
            promot = promotv[0];
            from = s->getPos();
            to = kingpos;
            return;
        }
    }
    // check if we can capature any chess piece
    for (auto s : colourSub) {
        for (auto op : othercolourPos) {
            if (s->isLegalmove(op)) { // the pos has a piece
                shufflefun(promotv);
                promot = promotv[0];
                from = s->getPos();
                to = op;
                return;
            }
        }
    }
    // random choose position
    level1(from, to, c, promot);
}


void ChessBoard::level3(Pos &from, Pos &to, Colour c, char &promot) {
    vector< shared_ptr<Subject> > colourSub;
    vector<shared_ptr<Subject>> othercoloursub;
    vector<Pos> wholePos;
    Pos kingpos;
    shared_ptr<Subject> kingsub;
    Colour otherc;
    vector<char> promotv = {'Q', 'N', 'B', 'R'};
    vector <Pos> escapecheck;
    if (from != Pos{-1, -1}) {
      int br = arrayPos(from, 'r');
      int bc = arrayPos(from, 'c');
      for (int i = 0; i < 8; ++i) {
          for (int j = 0; j < 8; ++j) {
            if (theBoard[br][bc]->isLegalmove(Pos{7-i, j})) escapecheck.emplace_back(Pos{7 - i, j});
          }
      }
      shufflefun(escapecheck);
      to = escapecheck[0];
      return;
    }

    if (c == Colour::Black) { otherc = Colour::White; }
    else if (c == Colour::White) { otherc = Colour::Black; }
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (theBoard[i][j] == nullptr) {
                wholePos.emplace_back(Pos{7-i, j});
                continue;
            }
            if (theBoard[i][j]->getColo() == c) {
                colourSub.emplace_back(theBoard[i][j]);
                if (theBoard[i][j]->getType() == 'K') {
                    kingpos = theBoard[i][j]->getPos();
                    kingsub = theBoard[i][j];
                }
            } else if (theBoard[i][j]->getColo() == otherc) {
                othercoloursub.emplace_back(theBoard[i][j]);
            }
            wholePos.emplace_back(theBoard[i][j]->getPos());
        }
    }
    shufflefun(colourSub);
    shufflefun(othercoloursub);
    shufflefun(wholePos);
    // check if our king will be checked
    for (auto op : othercoloursub) {
        if (op->isLegalmove(kingpos)) { // check if the king will be check in the next step
            for (auto whp : wholePos) { // check the whole position
                if (!isCapature(whp, kingsub) && kingsub->isLegalmove(whp)) { // check which position the king will not be capature
                    shufflefun(promotv);
                    promot = promotv[0];
                    from = kingpos;
                    to = whp;
                    return;
                }
            }
        }
    }

    for (auto s : colourSub) { // check the whole colourSub
        for (auto op : othercoloursub) { // check the other colour position to see if s can be capature
            if (op->isLegalmove(s->getPos())) { // if the s can be capature by any op in the next step, we need to move s
                for (auto whp : wholePos) { // check all the position that s can be moved to
                    if (!isCapature(whp, s) && s->isLegalmove(whp)) { // if the position whp cannot be capature then s will go to whp
                        shufflefun(promotv);
                        promot = promotv[0];
                        from = s->getPos();
                        to = whp;
                        return;
                    }
                }
            }
        }
    }
    level2(from, to, c, promot);
}



std::ostream &operator<<(std::ostream &out, const ChessBoard &cb) {
	out << *(cb.td);
	return out;
}
