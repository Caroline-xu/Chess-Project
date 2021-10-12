#include <iostream>
#include <vector>
#include <string>
#include "chess.h"
#include "stat.h"
#include "subject.h"
#include "textdisplay.h"
using namespace std;

TextDisplay::TextDisplay() { // 10 x 10 board including indices a-h, 1-8
    for (int i = 0; i < 10; ++i) theDisplay.emplace_back(10, 0);
    theDisplay[9][0] = ' '; // 0th row, a-h
    theDisplay[9][1] = ' ';
    theDisplay[9][2] = 'a';
    theDisplay[9][3] = 'b';
    theDisplay[9][4] = 'c';
    theDisplay[9][5] = 'd';
    theDisplay[9][6] = 'e';
    theDisplay[9][7] = 'f';
    theDisplay[9][8] = 'g';
    theDisplay[9][9] = 'h';

    for (int j = 0; j < 10; ++j) theDisplay[8][j] = ' ';
    for (int i = 0; i < 8; ++i) theDisplay[i][0] = (8 - i) + '0';
    for (int i = 0; i < 10; ++i) theDisplay[i][1] = ' ';

    for (int i = 0; i < 8; ++i) {
        if (i % 2 == 0) {  // 2,4,6,8th row
            for (int j = 2; j < 10; ++j) {
                if (j % 2 == 0) {
                    theDisplay[i][j] = ' ';
                } else {
                    theDisplay[i][j] = '_';
                }
            }
        } else {  // 3,5,7,9th row
            for (int j = 2; j < 10; ++j) {
                if (j % 2 == 0) {
                    theDisplay[i][j] = '_';
                } else {
                    theDisplay[i][j] = ' ';
                }
            }
        }
    }
}

void TextDisplay::notify(Command com, Subject &chess) {
    Subject *tmp = &chess;
    Colour colour = tmp->getColo();
    char type = tmp->getType();
    Pos p = tmp->getPos();
    int r = 7 - p.getRow();
    int c = 2 + p.getCol();
    if (com == Command::Set) {
        if (colour == Colour::Black) {
            theDisplay[r][c] = type + ('a' - 'A');
        } else if (colour == Colour::White) {
            theDisplay[r][c] = type;
        }
    } else if (com == Command::Remove) {
        if (r % 2 == 0) {
          if (c % 2 == 0) theDisplay[r][c] = ' ';
          else theDisplay[r][c] = '_';
        }
        else {
          if (c % 2 == 0) theDisplay[r][c] = '_';
          else theDisplay[r][c] = ' ';
        }
    }
}

ostream &operator<<(ostream &out, const TextDisplay &td) {
    for (auto i : td.theDisplay) {
        for (auto j : i) {
            out << j;
        }
        out << endl;
    }
    return out;
}
