#ifndef GRAPHIC_H
#define GRAPHIC_H
#include <iostream>
#include <vector>
#include "observer.h"
#include "stat.h"
#include "window.h"
class chess;

class GraphicsDisplay : public Observer {
    Xwindow w;

public:
    GraphicsDisplay();
    void notify(Command com, Subject &chess) override;
    void clear();
};
#endif
