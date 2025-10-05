#ifndef BATTLESHIP_GAME_BOARDWIDGET_H
#define BATTLESHIP_GAME_BOARDWIDGET_H
#include <filesystem>
#include <fstream>

#include "ConsoleRender.h"


class BoardWidget {
    ConsoleRender &render;
    uint32_t width = 0, height = 0;
public:
    BoardWidget(ConsoleRender &render, uint32_t left_top_x, uint32_t left_top_y);
    uint32_t getWidth() { return width; }
    uint32_t getHeight() { return height; }
};


#endif //BATTLESHIP_GAME_BOARDWIDGET_H