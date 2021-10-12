#include "history.h"
using namespace std;

HistoryMove::HistoryMove(Pos from, Pos to, std::shared_ptr<Subject> chess, std::shared_ptr<Subject> beside, std::shared_ptr<Subject> end):
    from{from}, to{to}, chess{chess}, beside{beside}, end{end} {}
