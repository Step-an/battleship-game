#include "Ship.h"

Ship::Ship(std::set<std::pair<int, int>> _dots):dots(std::move(_dots)) {

}

bool Ship::isDestroyed() {
    return destroyed;
}

void Ship::addDamagedCell(std::pair<int, int> cell) {
    damegedDots.insert(cell);
    if (damegedDots == dots) {
        destroyed = true;
    }
}

std::set<std::pair<int, int>> const &Ship::getCells() {
    return dots;
}

