#ifndef BATTLESHIP_GAME_SHIP_H
#define BATTLESHIP_GAME_SHIP_H
#include <set>
#include <vector>


class Ship {
    std::set<std::pair<int, int>> dots;
    std::set<std::pair<int, int>> damegedDots;
    bool destroyed = false;
public:
    Ship(std::set<std::pair<int, int>> _dots);
    bool isDestroyed();
    void addDamagedCell(std::pair<int, int> cell);

    std::set<std::pair<int, int>> const &getCells();
};


#endif //BATTLESHIP_GAME_SHIP_H