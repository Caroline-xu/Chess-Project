#ifndef TEXTDISPLAY_H
#define TEXTDISPLAY_H
#include <iostream>
#include <vector>
#include "observer.h"

class TextDisplay : public Observer {
    std::vector<std::vector<char>> theDisplay;

public:
    TextDisplay();

    void notify(Command com, Subject &chess) override;

    friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td);
};
#endif
