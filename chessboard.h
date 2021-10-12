#ifndef CHESSBOARD_H
#define CHESSBOARD_H
#include <vector>
#include <string>
#include <memory>
#include <iostream>
#include <stack> // The explationation of stack, please check http://www.cplusplus.com/reference/stack/stack/ for more details.
#include <stdexcept>
#include <algorithm>
#include <random>
#include <chrono>
#include "exception.h"
#include "stat.h"
#include "chess.h"
class Subject;
class HistoryMove;
class TextDisplay;
class GraphicsDisplay;

class ChessBoard { // All the pointer type are smart pointer in this class, we do not need to free memory mamually.
    std::vector<std::vector<std::shared_ptr<Subject>>> theBoard; //the actuall borad that store the current status of the chess game;
    std::shared_ptr<TextDisplay> td = nullptr; // The text display.
    GraphicsDisplay *gd = nullptr; // The graphic display
    int whitePoint = 0; // use to count the score of the white piece
    int blackPoint = 0; // use to count the score of the black piece
    std::stack<std::shared_ptr<HistoryMove>> history;
    Pos firstMove = Pos{-1, -1};
protected:
    bool isCapature(Pos nextp, std::shared_ptr<Subject> ch); // this is used to check whether ch move to "Pos" can be capatured by the other chess.
    // we might add more method //

public:
    //~ChessBoard(); do not need this!

    void setChess(Pos p, Colour c, char t, Side s);
    void moveChess(Pos p);
    void setGraphic(GraphicsDisplay *gd); // Sets up the graphic observer.
    int isOver(Colour &c); // Return 0 if the game is not over(none of these king are being checked or checkmate)),
                                // return 1 if the game over because of the checkmate and store the NoColour in c.
                                // return 2 if the game is over because of the check and store the winnig side colour in c.
    void intiBoard(); // Sets up the empty board.
    void intiGame(Colour down = Colour::White); // Sets up the initial game.
    bool setMove(Pos from, Pos to, char settype = 0, char type = 0); // Move the piece from the position from to to.
    void backMove(); // move back to last step;
    Colour getChess(Pos p);//return the colour of the chess in p, if these is no chess in p, just simply return NoColour.
    char getChess_type(Pos p);//return the type of the chess
    Pos getFirst();//return the position of the Pawn that move two squares once.
    bool isNevermove(Pos p);//return true if the chess in p does never move.
    bool isChecked(Pos pf, Pos p, Colour c);//return true if the p is be checked
    void changeNomove(Pos p, bool f);
    char getTypeinboard(Pos p);
    Side getsideinboard (Pos p);
    bool isnoMove(Colour colo);// check whether or not the chess in c colour has no legal move in board
    Pos kingInCheck(); // Return the pos of the king being checkes if one of two king are being checked. return Pos{-1, -1} if no king are being checked.
    void level1(Pos &from, Pos &to, Colour c, char &promot);
    void level2(Pos &from, Pos &to, Colour c, char &promot);
    void level3(Pos &from, Pos &to, Colour c, char &promot);


    friend std::ostream &operator<<(std::ostream &out, const ChessBoard &cb);
};


#endif
