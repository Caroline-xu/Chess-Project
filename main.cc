#include <string>
#include <climits>
#include <ctype.h>
#include <iostream>
#include "chessboard.h"
#include "chess.h"
#include "stat.h"
#include "exception.h"
#include "textdisplay.h"
#include "subject.h"
#include "graphic.h"
using namespace std;

int main(int argc, char *argv[]) {
    string cmd;
    Pos f;
    Pos t;
    string from;
    string to;
    string PlayW;// represent which player is white side chess
    string PlayB;// represent which player id black side chess
    Pos checkedPos = Pos{-1, -1};
    Colour incheckc = Colour::NoColour;
    Colour startcol = Colour::White;
    ChessBoard cb;
    shared_ptr <GraphicsDisplay> gd = nullptr;
    if (argc > 2) {
      cerr << "incorrect command, please check ! chess [text]" << endl;
      return 0;
    }
    if (argc != 2) {
      gd = make_shared<GraphicsDisplay> ();
      cb.setGraphic(gd.get());
    }
    int wscore = 0;
    int bscore = 0;
    char promot = 0;
    int levelW = 0;
    int levelB = 0;
    try {
        while (true) {
            while (true) {
                levelW = 0;
                levelB = 0;
                cb.intiBoard();
                cout << "Do you want to play the game or start setting up your own chessboard? (choose game [white-player] [black-player] or setup)" << endl;
                cout << "The fields can be replaced by either [human] or [computer]" << endl;
                cin >> cmd;
                if (cmd == "game") {
                    cin >> PlayW;
                    cin >> PlayB;
                    if ((PlayW != "human" && PlayW != "computer") || (PlayW != "human" && PlayW != "computer")) {
                        cout << "Incorrect initial Board setup" << endl;
                        continue;
                    }
                    if (PlayB == "human") {
                        cb.intiGame(Colour::Black);
                        cout << cb << endl;
                        break;
                    } else {
                        cb.intiGame();
                        cout << cb << endl;
                        break;
                    }
                    cout << cb << endl;
                } else if (cmd == "setup") {
                    string sign;
                    int numwking = 0; //number of white king
                    int numbking = 0; //number of black king
                    int r = 0, n = 0, b = 0, q = 0, p = 0, R = 0, N = 0, B = 0, Q = 0, P = 0;
                    cb.intiBoard();
                    cout << cb << endl;
                    Pos pos_internal;
                    while (true) {
                        try {
                            cin >> sign; // we have four signs "+", "-", "=" and "done"
                            if (sign == "+") {
                                char role;
                                string pos;
                                cin >> role;
                                cin >> pos;
                                if (pos.at(0) < 'a' || pos.at(0) > 'h' || pos.at(1) < '1' || pos.at(1) > '8') throw OutOfRange{};
                                pos_internal = getPos(pos);
                                char type = cb.getTypeinboard(pos_internal);
                                if (type != 0) { // there is already a piece on this position, need to replace
                                    decreaseChessCount(type, r, n, b, q, p, R, N, B, Q, P, numwking, numbking); // decrease the count for this type
                                }
                                if (role == 'P') {
                                    if (P == 8) continue;
                                    if (!(cb.setMove(Pos{-1, -1}, pos_internal, role))) continue;
                                    ++P;
                                    cout << cb << endl;
                                    continue;
                                }
                                if (role == 'p') {
                                    if (p == 8) continue;
                                    if (!(cb.setMove(Pos{-1, -1}, pos_internal, role))) continue;
                                    ++p;
                                    cout << cb << endl;
                                    continue;
                                }
                                if (role == 'K') {
                                    if (numwking == 1) continue;
                                    if (!(cb.setMove(Pos{-1, -1}, pos_internal, role))) continue;
                                    ++numwking;
                                    if (pos_internal == Pos {0, 4}) {
                                      cout << "Do you want to set the king as never moved ? If yes, enter Y, otherwise, enter N" << endl;
                                      string ans = "";
                                      cin >> ans;
                                      if (ans == "N") {
                                          cb.changeNomove(pos_internal, false);
                                      }
                                      cout << cb << endl;
                                      continue;
                                    }
                                    cb.changeNomove(pos_internal, false);
                                    cout << cb << endl;
                                    continue;
                                }
                                if (role == 'k') {
                                    if (numbking == 1) continue;
                                    if (!(cb.setMove(Pos{-1, -1}, pos_internal, role))) continue;
                                    ++numbking;
                                    if (pos_internal == Pos {7, 4}) {
                                      cout << "Do you want to set the king as never moved ? If yes, enter Y, otherwise, enter N" << endl;
                                      string ans = "";
                                      cin >> ans;
                                      if (ans == "N") {
                                          cb.changeNomove(pos_internal, false);
                                      }
                                      cout << cb << endl;
                                      continue;
                                    }
                                    cb.changeNomove(pos_internal, false);
                                    cout << cb << endl;
                                    continue;
                                }
                                if (role == 'R') {
                                    if (R == 2) continue;
                                    if (!(cb.setMove(Pos{-1, -1}, pos_internal, role))) continue;
                                    ++R;
                                    if (pos_internal == Pos {0, 0} || pos_internal == Pos {0, 7}) {
                                      cout << "Do you want to set the Rook as never moved ? If yes, enter Y, otherwise, enter N" << endl;
                                      string ans = "";
                                      cin >> ans;
                                      if (ans == "N") {
                                          cb.changeNomove(pos_internal, false);
                                      }
                                      cout << cb << endl;
                                      continue;
                                    }
                                    cb.changeNomove(pos_internal, false);
                                    cout << cb << endl;
                                    continue;
                                }
                                if (role == 'r') {
                                    if (r == 2) continue;
                                    if (!(cb.setMove(Pos{-1, -1}, pos_internal, role))) continue;
                                    ++r;
                                    if (pos_internal == Pos {7, 0} || pos_internal == Pos {7, 7}) {
                                      cout << "Do you want to set the Rook as never moved ? If yes, enter Y; otherwise, enter N" << endl;
                                      string ans = "";
                                      cin >> ans;
                                      if (ans == "N") {
                                          cb.changeNomove(pos_internal, false);
                                      }
                                      cout << cb << endl;
                                      continue;
                                    }
                                    cb.changeNomove(pos_internal, false);
                                    cout << cb << endl;
                                    continue;
                                }
                                if (role == 'N') {
                                    if (N == 2) continue;
                                    if (!(cb.setMove(Pos{-1, -1}, pos_internal, role))) continue;
                                    ++N;
                                    cout << cb << endl;
                                    continue;
                                }
                                if (role == 'n') {
                                    if (n == 2) continue;
                                    if (!(cb.setMove(Pos{-1, -1}, pos_internal, role))) continue;
                                    ++n;
                                    cout << cb << endl;
                                    continue;
                                }
                                if (role == 'B') {
                                    if (B == 2) continue;
                                    if (!(cb.setMove(Pos{-1, -1}, pos_internal, role))) continue;
                                    ++B;
                                    cout << cb << endl;
                                    continue;
                                }
                                if (role == 'b') {
                                    if (b == 2) continue;
                                    if (!(cb.setMove(Pos{-1, -1}, pos_internal, role))) continue;
                                    ++b;
                                    cout << cb << endl;
                                    continue;
                                }
                                if (role == 'Q') {
                                    if (Q == 1) continue;
                                    if (!(cb.setMove(Pos{-1, -1}, pos_internal, role))) continue;
                                    ++Q;
                                    cout << cb << endl;
                                    continue;
                                }
                                if (role == 'q') {
                                    if (q == 1) continue;
                                    if (!(cb.setMove(Pos{-1, -1}, pos_internal, role))) continue;
                                    ++q;
                                    cout << cb << endl;
                                    continue;
                                }
                            } else if (sign == "-") {
                                string pos;
                                cin >> pos;
                                if (pos.at(0) < 'a' || pos.at(0) > 'h' || pos.at(1) < '1' || pos.at(1) > '8') throw OutOfRange{};
                                pos_internal = getPos(pos);
                                char tempchar = cb.getTypeinboard(pos_internal);
                                if (!(cb.setMove(pos_internal, Pos{-1,-1}))) continue;
                                if (tempchar == 'P') {
                                    if (P < 1) {
                                        //cerr << "Cannot remove chess: the number of chess is already 0" << endl;
                                        continue;
                                    }
                                    --P;
                                }
                                if (tempchar == 'p') {
                                    if (p < 1) {
                                        //cerr << "Cannot remove chess: the number of chess is already 0" << endl;
                                        continue;
                                    }
                                    --p;
                                }
                                if (tempchar == 'K') {
                                    if (numwking < 1) {
                                        //cerr << "Cannot remove chess: the number of chess is already 0" << endl;
                                        continue;
                                    }
                                    --numwking;
                                }
                                if (tempchar == 'k') {
                                    if (numbking < 1) {
                                        //cerr << "Cannot remove chess: the number of chess is already 0" << endl;
                                        continue;
                                    }
                                    --numbking;
                                }
                                if (tempchar == 'R') {
                                    if (R < 1) {
                                        //cerr << "Cannot remove chess: the number of chess is already 0" << endl;
                                        continue;
                                    }
                                    --R;
                                }
                                if (tempchar == 'r') {
                                    if (r < 1) {
                                        //cerr << "Cannot remove chess: the number of chess is already 0" << endl;
                                        continue;
                                    }
                                    --r;
                                }
                                if (tempchar == 'B') {
                                    if (B < 1) {
                                        //cerr << "Cannot remove chess: the number of chess is already 0" << endl;
                                        continue;
                                    }
                                    --B;
                                }
                                if (tempchar == 'b') {
                                    if (b < 1) {
                                        //cerr << "Cannot remove chess: the number of chess is already 0" << endl;
                                        continue;
                                    }
                                    --b;
                                }
                                if (tempchar == 'Q') {
                                    if (Q < 1) {
                                        //cerr << "Cannot remove chess: the number of chess is already 0" << endl;
                                        continue;
                                    }
                                    --Q;
                                }
                                if (tempchar == 'q') {
                                    if (q < 1) {
                                        //cerr << "Cannot remove chess: the number of chess is already 0" << endl;
                                        continue;
                                    }
                                    --q;
                                }
                                if (tempchar == 'N') {
                                    if (N < 1) {
                                        //cerr << "Cannot remove chess: the number of chess is already 0" << endl;
                                        continue;
                                    }
                                    --N;
                                }
                                if (tempchar == 'n') {
                                    if (n < 1) {
                                        //cerr << "Cannot remove chess: the number of chess is already 0" << endl;
                                        continue;
                                    }
                                    --n;
                                }
                                cout << cb << endl;
                                continue;
                            } else if (sign == "=") {
                                string colour;
                                cin >> colour;
                                if (colour == "black") {
                                    startcol = Colour::Black;
                                    cout << "Black will be the next." << endl;
                                } else if (colour == "white") {
                                    startcol = Colour::White;
                                    cout << "White will be the next." << endl;
                                } else {
                                    cout << "Incorrect colour. Please provide colour [black] or [white]." << endl;
                                }
                                continue;
                            } else if (sign == "done") {
                                if (numbking == 1 && numwking == 1) {
                                    cout << "You left the setup mode!" << endl;
                                    break;
                                    // leave setup mode
                                } else {
                                    cout << "Sorry, your setup mode does not follow the rule." << endl;
                                    if (cin.eof()) throw EOFException{};
                                    throw IncorrectSetup{};
                                }
                            } else if (cin.eof() || stoi(sign) == EOF) {
                                throw EOFException{};
                            } else {
                                cout << "Incorrect command" << endl;
                            }
                        } catch  (OutOfRange out) {
                            cout << "The position is out of range" << endl;
                        } catch (IncorrectSetup s) {
                            cout << "Please set up a Black king and a White king to play the game" << endl;
                        } catch (EOFException eof) {
                            cout << "Final Score:" << endl;
                            cout << "White: " << wscore << endl;
                            cout << "Black: " << bscore << endl;
                            return 0;
                        }
                    }
                    cout << "Do you want to keep playing with your own setup game? If Yes, please enter Y; if No, enter N" << endl;
                    string ans = "";
                    cin >> ans;
                    if (ans == "N") {
                        cout << "Exits current setup game and you need to make a new game to start" << endl;
                        continue;
                    }
                    cout << "Who play as White? [computer] or [human]" << endl;
                    while (cin >> ans && ans != "computer" && ans != "human") {
                        cout << "Who play as White? Please enter either [computer] or [human]" << endl;
                    }
                    if (ans == "computer") PlayW = "computer";
                    if (ans == "human") PlayW = "human";

                    cout << "Who play as Black? [computer] or [human]" << endl;
                    while (cin >> ans && ans != "computer" && ans != "human") {
                        cout << "Who play as Black? Please enter either [computer] or [human]" << endl;
                    }
                    if (ans == "computer") PlayB = "computer";
                    if (ans == "human") PlayB = "human";
                    break;
                }
                else if (cin.eof()) {
                    cout << "Final Score:" << endl;
                    cout << "White: " << wscore << endl;
                    cout << "Black: " << bscore << endl;
                    return 0;
                }
                else {
                    cout << "Incorrect command, please choose game or setup." << endl;
                }
            }
            if (PlayW == "computer") {
                cout << "Choose the difficulty level for White chess: please enter 1, 2, or 3" << endl;
                while (cin.fail() || (levelW != 1 && levelW != 2 && levelW != 3)) {
                    cout << "Please enter an integer: 1, 2, or 3" << endl;
                    if (cin.eof()) {
                            cout << "Final Score:" << endl;
                            cout << "White: " << wscore << endl;
                            cout << "Black: " << bscore << endl;
                            return 0;
                    }
                    cin.clear();
                    cin.ignore(INT_MAX,'\n');
                    cin >> levelW;
                }
            }
            if (PlayB == "computer") {
                cout << "Choose the difficulty level for Black chess: please enter 1, 2, or 3" << endl;
                while (cin.fail() || (levelB != 1 && levelB != 2 && levelB != 3)) {
                    cout << "Please enter an integer: 1, 2, or 3" << endl;
                    if (cin.eof()) {
                            cout << "Final Score:" << endl;
                            cout << "White: " << wscore << endl;
                            cout << "Black: " << bscore << endl;
                            return 0;
                    }
                    cin.clear();
                    cin.ignore(INT_MAX,'\n');
                    cin >> levelB;
                }
            }
            Colour Win_colour = Colour::NoColour;
            while (true) {
                if (Win_colour != Colour::NoColour) {
                    if (Win_colour == Colour::White){
                        cout << "resign result: White wins!" << endl;
                        cout << endl;
                        ++wscore;
                        Win_colour = Colour::NoColour;
                        startcol = Colour::White;
                        break;
                    }
                    cout << "resign result: Black wins!" << endl;
                    cout << endl;
                    ++bscore;
                    Win_colour = Colour::NoColour;
                    startcol = Colour::White;
                    break;
                }
                else if (cb.isOver(Win_colour) != 0) {
                    if (Win_colour == Colour::Black) {
                        cout << "Checkmate! Black wins!" << endl;
                        cout << endl;
                        ++bscore;
                        Win_colour = Colour::NoColour;
                        startcol = Colour::White;
                        break;
                    }
                    if (Win_colour == Colour::White) {
                        cout << "Checkmate! White wins!" << endl;
                        cout << endl;
                        ++wscore;
                        Win_colour = Colour::NoColour;
                        startcol = Colour::White;
                        break;
                    }
                    cout << "Stalemate!" << endl;
                    cout << endl;
                    Win_colour = Colour::NoColour;
                    startcol = Colour::White;
                    break;
                }
                checkedPos = cb.kingInCheck();
                incheckc = Colour::NoColour; // the colour that in check
                if (checkedPos != Pos{-1, -1}) {  // some king is in check
                    incheckc = cb.getChess(checkedPos);
                    cout << incheckc << " is in check." << endl;
                    cout << endl;
                }
                Pos fromb = Pos{-1, -1};
                Pos tob = Pos{-1, -1};
                if (startcol == Colour::White) {
                    cout << "White turn: ";
                    if (PlayW == "computer") {
                        if (incheckc == Colour::White) fromb = checkedPos; // force the computer to move from the position that be checked!
                        if (levelW == 1) cb.level1(fromb,tob,startcol, promot);
                        if (levelW == 2) cb.level2(fromb,tob,startcol, promot);
                        if (levelW == 3) cb.level3(fromb,tob,startcol, promot);
                        //cout << "computer move from " << getMove(fromb) << " to " << getMove(tob) << endl;
                        if (!(cb.setMove(fromb, tob, 0, promot))) throw InvalidPos{};
                        startcol = Colour::Black;
                        cout << "computer move from " << getMove(fromb) << " to " << getMove(tob) << endl;
                        cout << cb << endl;
                    }
                    if (PlayW == "human") {
                        while (true) {
                            cout << "Player needs to enter the move for white chess" << endl;
                            cin >> cmd;
                            if (cmd == "help") {
                                cb.level3(fromb,tob,startcol, promot);
                                cout << "Suggest you to move from " << getMove(fromb) << " to " << getMove(tob) << endl;
                                continue;
                            }
                            if (cmd == "move") {
                                try {
                                    if (cin.eof()) throw EOFException{};
                                    cin >> from;
                                    cin >> to;
                                    fromb = getPos(from);
                                    tob = getPos(to);
                                    if (cb.getChess(fromb) != Colour::White) {
                                        cout << "You can only move white chess!" <<endl;
                                        continue;
                                    }
                                    if (incheckc == Colour::White) {
                                      if (fromb != checkedPos) {
                                        cout << "You are in check, please move your king!" << endl;
                                        continue;
                                      }
                                    }
                                    if (cb.getTypeinboard(fromb) == 'P') {
                                      if (cb.getsideinboard(fromb) == Side::Down) {
                                        if (tob.getRow() == 7) cin >> promot;
                                      }
                                      else if (cb.getsideinboard(fromb) == Side::Up) {
                                        if (tob.getRow() == 0) cin >> promot;
                                      }
                                    }
                                    if (!(cb.setMove(fromb, tob, 0, promot))) throw InvalidPos{};
                                    else cout << cb << endl;
                                    startcol = Colour::Black;
                                    break;
                                } catch (InvalidPos) {
                                    cout << "Invalid move" << endl;
                                    continue;
                                } catch (EOFException) {
                                    cout << "Final Score:" << endl;
                                    cout << "White: " << wscore << endl;
                                    cout << "Black: " << bscore << endl;
                                    return 0;
                                }
                            }
                            if (cmd == "resign") {
                                Win_colour = Colour::Black;
                                break;
                            }
                            if (cin.eof()) {
                                cout << "Final Score:" << endl;
                                cout << "White: " << wscore << endl;
                                cout << "Black: " << bscore << endl;
                                return 0;
                            }
                            cout << "Incorrect command, please only move the chess or resign" << endl;
                        }
                    }
                }
                else if (startcol == Colour::Black) {
                    cout << "Black turn: ";
                    if (PlayB == "computer") {
                        if (incheckc == Colour::White) fromb = checkedPos;
                        if (levelB == 1) cb.level1(fromb,tob,startcol, promot);
                        if (levelB == 2) cb.level2(fromb,tob,startcol, promot);
                        if (levelB == 3) cb.level3(fromb,tob,startcol, promot);
                        cout << "computer move from " << getMove(fromb) << " to " << getMove(tob) << endl;
                        if (!(cb.setMove(fromb, tob, 0, promot))) throw InvalidPos{};
                        startcol = Colour::White;
                        cout << "computer move from " << getMove(fromb) << " to " << getMove(tob) << endl;
                        cout << cb << endl;
                    }
                    if (PlayB == "human") {
                        while (true) {
                            cout << "Player needs to enter the move for black chess" << endl;
                            cin >> cmd;
                            if (cmd == "help") {
                                cb.level2(fromb,tob,startcol, promot);
                                cout << "Suggest you to move from " << getMove(fromb) << " to " << getMove(tob) << endl;
                                continue;
                            }
                            if (cmd == "move") {
                                try {
                                    if (cin.eof()) throw EOFException{};
                                    cin >> from;
                                    cin >> to;
                                    fromb = getPos(from);
                                    tob = getPos(to);
                                    if (cb.getChess(fromb) != Colour::Black) {
                                        cout << "You can only move Black chess!" <<endl;
                                        continue;
                                    }
                                    if (incheckc == Colour::Black) {
                                      if (fromb != checkedPos) {
                                        cout << "You are in check, please move your king!" << endl;
                                        continue;
                                      }
                                    }
                                    if (cb.getTypeinboard(fromb) == 'p') {
                                      if (cb.getsideinboard(fromb) == Side::Down) {
                                        if (tob.getRow() == 7) cin >> promot;
                                      }
                                      else if (cb.getsideinboard(fromb) == Side::Up) {
                                        if (tob.getRow() == 0) cin >> promot;
                                      }
                                    }
                                    if (!(cb.setMove(fromb, tob, 0, promot + 32))) throw InvalidPos{};
                                    else cout << cb << endl;
                                    startcol = Colour::White;
                                    break;
                                } catch (InvalidPos) {
                                    cout << "Invalid move" << endl;
                                    continue;
                                } catch (EOFException) {
                                    cout << "Final Score:" << endl;
                                    cout << "White: " << wscore << endl;
                                    cout << "Black: " << bscore << endl;
                                    return 0;
                                }
                            }
                            if (cmd == "resign") {
                                Win_colour = Colour::White;
                                break;
                            }
                            if (cin.eof()) {
                                cout << "Final Score:" << endl;
                                cout << "White: " << wscore << endl;
                                cout << "Black: " << bscore << endl;
                                return 0;
                            }
                            cout << "Incorrect command, please only move the chess or resign" << endl;
                        }
                    }
                }
            }
        }
    }
    catch (ios::failure &) {
        return 0;
    } // Any I/O failure quits
    return 0;
}
