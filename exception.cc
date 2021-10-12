#include "exception.h"


/*string checkPos(string pos) {
    char colpos = pos.at(0);
    char rowpos = pos.at(1);
    string colcheck { "abcdefgh" } ;
    string rowcheck { "12345678" };
    int colcorrect {0};
    int rowcorrect {0};
    for (unsigned i = 0; i < colcheck.length(); ++i) {
        if (colcheck.at(i) == colpos) { colcorrect = 1};
    }
    for (unsigned i = 0; i < rowcheck.length(); ++i) {
        if (rowcheck.at(i) == rowpos) { rowcorrect = 1};
    }
    if (pos.length() == 2 && rowcorrect == 1 && colcorrect == 1) {
        return pos;
    } else {
        throw InvalidPos{pos};
    }
}*/
