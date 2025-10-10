#ifndef BATTLESHIP_GAME_BOARDWIDGET_H
#define BATTLESHIP_GAME_BOARDWIDGET_H
#include <filesystem>
#include <fstream>

#include "ConsoleRender.h"


enum class CellState {
    untouched,
    shotNoShip,
    ship,
    destroyed,
    shotShip,
};

class BoardWidget {
    std::shared_ptr<ConsoleRender> render;
    uint32_t width = 0, height = 0;
    uint32_t left_top_x;
    uint32_t left_top_y;
    static int readUTF32Char(std::ifstream &file, char32_t& output);

public:
    BoardWidget(std::shared_ptr<ConsoleRender> render, uint32_t left_top_x, uint32_t left_top_y);
    uint32_t getWidth() { return width; }
    uint32_t getHeight() { return height; }
    void setCellState(int column, int raw, CellState state);
};

#endif //BATTLESHIP_GAME_BOARDWIDGET_H