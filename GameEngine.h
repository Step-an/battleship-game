#ifndef BATTLESHIP_GAME_GAMEENGINE_H
#define BATTLESHIP_GAME_GAMEENGINE_H
#include <set>

#include "BoardWidget.h"
#include "ConsoleRender.h"
#include "Ship.h"
#include "TextWidget.h"

class GameEngine {
    std::shared_ptr<ConsoleRender> render;
    std::vector<BoardWidget> &boards;
    std::shared_ptr<TextWidget> text;
    std::shared_ptr<TextWidget> text2;
    std::vector<Ship> ships1;
    std::vector<Ship> ships2;
    std::pair<int, int> parseCoord(const std::string& coord);
    std::array<std::array<bool, 10>, 10> isCellShot1{{false}};
    std::array<std::array<bool, 10>, 10> isCellShot2{{false}};

    std::set<std::pair<int, int>> pointsOfShip(std::pair<int, int> coord1, std::pair<int, int> coord2);

    bool validateCoord(std::pair<int, int> coord1, std::pair<int, int> coord2, const std::set<std::pair<int, int>> &coordsTaken, int lengthExpected);

    std::pair<std::pair<int, int>, std::pair<int, int>> getCoords();

    void inputShips(std::vector<Ship> &ships, BoardWidget &widget);



    void flashBoards();

    std::pair<int, int> getOneCoord();

    void processDestroyedShip(BoardWidget &widget, Ship &ship, std::array<std::array<bool, 10>, 10> *destroyedCells);

    void checkForEndingOfGameAndEnd(std::vector<Ship> *ships, int whoIsLooser);
    void fillArr(std::array<std::array<bool, 10>, 10> &arr);

public:
    GameEngine(std::shared_ptr<ConsoleRender> render, std::vector<BoardWidget> &boards,
               std::shared_ptr<TextWidget> text,
               std::shared_ptr<TextWidget> text2);


    void start();
};


#endif //BATTLESHIP_GAME_GAMEENGINE_H