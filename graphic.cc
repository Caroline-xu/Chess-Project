#include "graphic.h"
#include "chess.h"
GraphicsDisplay::GraphicsDisplay() {
  std::string temps = "";
  for (int i = 6; i < 14; ++i) w.drawString(125, 27 * i, temps.assign(1, 9 - (i - 5) + '0'));
  for (int i = 6; i < 14; ++i) w.drawString(26 * i, 375, temps.assign(1, i - 6 + 'A'));
  for (int i = 6; i < 14; ++i) {
        if (i % 2 == 0) {  // 2,4,6,8th row
            for (int j = 6; j < 14; ++j) {
                if (j % 2 == 0) {
                    w.fillRectangle(25 * j, 25 * i, 25, 25, Xwindow::White);
                } else {
                    w.fillRectangle(25 * j, 25 * i, 25, 25, Xwindow::Blue);
                }
            }
        } else {  // 3,5,7,9th row
            for (int j = 6; j < 14; ++j) {
                if (j % 2 == 0) {
                    w.fillRectangle(25 * j, 25 * i, 25, 25, Xwindow::Blue);
                } else {
                    w.fillRectangle(25 * j, 25 * i, 25, 25, Xwindow::White);
                }
            }
        }
    }
}



void GraphicsDisplay::notify(Command com, Subject &chess) {
  std::string temps = "";
  Subject *tmp = &chess;
  Colour colour = tmp->getColo();
  char type = tmp->getType();
  Pos p = tmp->getPos();
  int r = 7 - p.getRow();
  int c = p.getCol();
  if (com == Command::Set) {
      if (colour == Colour::Black) {
          w.drawString(160 + c * 25, 164 + r * 25, temps.assign(1, type + ('a' - 'A')));
      } else if (colour == Colour::White) {
          w.drawString(160 + c * 25, 164 + r * 25, temps.assign(1, type));
      }
  } else if (com == Command::Remove) {
    if (r % 2 == 0) {
      if (c % 2 == 0) w.fillRectangle(150 + 25 * c, 150 + 25 * r, 25, 25, Xwindow::White);
      else w.fillRectangle(150 + 25 * c, 150 + 25 * r, 25, 25, Xwindow::Blue);
    }
    else {
      if (c % 2 == 0) w.fillRectangle(150 + 25 * c, 150 + 25 * r, 25, 25, Xwindow::Blue);
      else w.fillRectangle(150 + 25 * c, 150 + 25 * r, 25, 25, Xwindow::White);
    }
  }
}

void GraphicsDisplay::clear() {
  for (int i = 6; i < 14; ++i) {
        if (i % 2 == 0) {  // 2,4,6,8th row
            for (int j = 6; j < 14; ++j) {
                if (j % 2 == 0) {
                    w.fillRectangle(25 * j, 25 * i, 25, 25, Xwindow::White);
                } else {
                    w.fillRectangle(25 * j, 25 * i, 25, 25, Xwindow::Blue);
                }
            }
        } else {  // 3,5,7,9th row
            for (int j = 6; j < 14; ++j) {
                if (j % 2 == 0) {
                    w.fillRectangle(25 * j, 25 * i, 25, 25, Xwindow::Blue);
                } else {
                    w.fillRectangle(25 * j, 25 * i, 25, 25, Xwindow::White);
                }
            }
        }
    }
}
