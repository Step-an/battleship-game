#include "GameEngine.h"

#include <cmath>
#include <regex>
#include <set>

std::pair<int, int> GameEngine::parseCoord(const std::string &coord) {
    int row = 0;
    size_t idx = 0;
    while (idx < coord.size() && std::isdigit(static_cast<unsigned char>(coord[idx]))) {
        row = row * 10 + (coord[idx] - '0');
        ++idx;
    }
    char letter = std::toupper(static_cast<unsigned char>(coord[idx]));
    int col = letter - 'A' + 1;
    return {col, row};
}
std::set<std::pair<int, int>> GameEngine::pointsOfShip(std::pair<int, int> coord1, std::pair<int, int> coord2) {
    std::set<std::pair<int, int>> coordsToTake;
    if (coord1.first == coord2.first) {
        for (int i = std::min(coord1.second, coord2.second); i <= std::max(coord1.second, coord2.second); ++i) {
            coordsToTake.insert({coord1.first, i});
        }
    } else if (coord1.second == coord2.second) {
        for (int i = std::min(coord1.first, coord2.first); i <= std::max(coord1.first, coord2.first); ++i) {
            coordsToTake.insert({i, coord1.second});
        }
    }
    return coordsToTake;
}
bool GameEngine::validateCoord(std::pair<int, int> coord1, std::pair<int, int> coord2, const std::set<std::pair<int, int>> &coordsTaken,
                               int lengthExpected) {
    int length = 0;
    std::set<std::pair<int, int>> coordsToTake;
    if (coord1.first == coord2.first) {
        length = std::abs(coord1.second - coord2.second) + 1;
    } else if (coord1.second == coord2.second) {
        length = std::abs(coord1.first - coord2.first) + 1;
    } else {
        return false;
    }

    if (length != lengthExpected) {
        return false;
    }

    coordsToTake = pointsOfShip(coord1, coord2);

    for (auto i : coordsToTake) {
        for (auto j : coordsTaken) {
            if (std::pow(i.first - j.first, 2) + std::pow(i.second - j.second, 2) <= 2) {
                return false;
            }
        }
    }

    return true;
}

std::pair<std::pair<int, int>, std::pair<int, int>> GameEngine::getCoords() {
    std::string coordinates = render->readValue();
    std::regex coordreg("(?:[1-9]|10)[A-J] (?:[1-9]|10)[A-J]");
    while (!std::regex_match(coordinates, coordreg)) {
        text->setText(U"Incorrect input. Try again:");
        coordinates = render->readValue();
    }
    std::stringstream coordStream(coordinates);
    std::string firstCoord;
    std::string secondCoord;
    coordStream >> firstCoord;
    coordStream >> secondCoord;

    return std::make_pair(parseCoord(firstCoord), parseCoord(secondCoord));
}

void GameEngine::inputShips(std::vector<Ship> &ships, BoardWidget &widget) {
    std::vector<int> shipsSizes{1, 1, 1, 1, 2, 2, 2, 3, 3, 4};
    std::set<std::pair<int, int>> coordsTaken;
    for (int i : shipsSizes) {
        std::stringstream stringStream;
        stringStream << "Input ship coordinates(start and end) with length " << i << "(like 1D 2D)(if length is one then the are equal:";
        text->setText(stringStream.str());
        auto coords = getCoords();
        while (!(validateCoord(coords.first, coords.second, coordsTaken, i))) {
            text->setText(U"Incorrect coordinates. Try again:");
            coords = getCoords();
        }
        auto dots = pointsOfShip(coords.first, coords.second);
        for (auto i : dots) {
            widget.setCellState(i.first, i.second, CellState::ship);
        }
        ships.emplace_back(dots);
        coordsTaken.insert(dots.begin(), dots.end());
    }

}

GameEngine::GameEngine(std::shared_ptr<ConsoleRender> render,
                       std::vector<BoardWidget> &boards, std::shared_ptr<TextWidget> text, std::shared_ptr<TextWidget> text2): render(render), boards(boards),
text(text), text2(text2) {
    fillArr(isCellShot1);
    fillArr(isCellShot2);
};

void GameEngine::flashBoards() {
    for (auto &board : boards) {
        for (int x = 1; x <= 10; ++x) {
            for (int y = 1; y <= 10; ++y) {
                board.setCellState(x, y, CellState::untouched);
            }
        }
    }
}

std::pair<int, int> GameEngine::getOneCoord() {
    std::string input = render->readValue();
    std::regex coordreg("(?:[1-9]|10)[A-J]");
    while (!std::regex_match(input, coordreg)) {
        text->setText(U"Incorrect input. Try again:");
        input = render->readValue();
    }
    return parseCoord(input);
}

void GameEngine::processDestroyedShip(BoardWidget &widget, Ship &ship, std::array<std::array<bool, 10>, 10> *destroyedCells) {
    for (auto &coord: ship.getCells()) {
        for (int i = -1; i <= 1; ++i) {
            for (int j = -1; j <= 1; ++j) {
                if (coord.first + i > 0  && coord.first + i < 11 && coord.second + j > 0 && coord.second + j < 11) {
                    if (!ship.getCells().contains({coord.first + i, coord.second + j})) {
                        widget.setCellState(coord.first + i, coord.second + j, CellState::shotNoShip);
                        (*destroyedCells)[coord.first + i - 1][coord.second + j - 1] = true;
                    }
                }

            }
        }
    }
    for (auto &coord: ship.getCells()) {
        widget.setCellState(coord.first, coord.second, CellState::destroyed);
        (*destroyedCells)[coord.first - 1][coord.second - 1] = true;
    }
}
void GameEngine::checkForEndingOfGameAndEnd(std::vector<Ship> *ships, int whoIsLooser) {
    for (auto &ship : *ships) {
        if (!ship.isDestroyed()) {
            return;
        }
    }
    if (whoIsLooser == 1) {
        text->setText(U"Second player has won. Congratulations!");
    } else {
        text->setText(U"First player has won. Congratulations!");
    }
    exit(0);
}

void GameEngine::fillArr(std::array<std::array<bool, 10>, 10> &arr) {
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            arr[i][j] = false;
        }
    }
}

bool GameEngine::turn(std::vector<Ship> *ships, BoardWidget *widget, std::array<std::array<bool, 10>, 10> *destroyedCells, int playerNumber) {
    auto coord = getOneCoord();
    text2->setText("");
    while ((*destroyedCells)[coord.first - 1][coord.second - 1]) {
        text->setText(U"Already shot this cell. Try again:");
        coord = getOneCoord();
    }
    bool damage = false;
    for (auto &ship : *ships) {
        if (ship.getCells().contains(coord)) {
            damage = true;
            ship.addDamagedCell(coord);
            text2->setText(U"Enemy ship is damaged!");
            widget->setCellState(coord.first, coord.second, CellState::shotShip);
            (*destroyedCells)[coord.first - 1][coord.second - 1] = true;
            if (ship.isDestroyed()) {
                text2->setText(U"Enemy ship is destroyed!");
                processDestroyedShip(*widget, ship, destroyedCells);
                checkForEndingOfGameAndEnd(ships, playerNumber == 1 ? 2 : 1);
            }
        }
    }
    if (!damage) {
        widget->setCellState(coord.first, coord.second, CellState::shotNoShip);
        (*destroyedCells)[coord.first - 1][coord.second - 1] = true;
        text2->setText("Miss");
        return false;
    } else {
        return true;
    }
}
void GameEngine::start() {
    text->setText(U"Enter start to start placing ships");
    std::string input;
    while (input != "start") {
            input = render->readValue();
    }
    text->setText(U"Let the first player choose ship positions. Enter start to start setting positions of ships");
    input = "";
    while (input != "start") {
        input = render->readValue();
    }
    inputShips(ships1, boards[0]);
    flashBoards();
    text->setText(U"The first player has ended placement of his ships. Type start to let the second player do it:");
    input = "";
    while (input != "start") {
        input = render->readValue();
    }
    inputShips(ships2, boards[1]);
    flashBoards();
    text->setText(U"Placement of ships has ended. Type start to start the game:");
    input = "";
    while (input != "start") {
        input = render->readValue();
    }
    bool turnOfFirst = true;
    while (true) {
        int curBoardInd = 0;
        std::vector<Ship>* ships;
        std::array<std::array<bool, 10>, 10> *destroyedCells;
        std::u32string label;
        if (turnOfFirst) {
            curBoardInd = 1;
            ships = &ships2;
            destroyedCells = &isCellShot2;
            label = U"Turn of the first player. Type coordinates where to shoot:";
        } else {
            curBoardInd = 0 ;
            ships = &ships1;
            destroyedCells = &isCellShot1;
            label = U"Turn of the second player. Type coordinates where to shoot:";
        }
        text->setText(label);
        while (turn(ships, &boards[curBoardInd], destroyedCells, curBoardInd + 1)) {
            text->setText(label);
        }

        turnOfFirst = !turnOfFirst;
    }

}
