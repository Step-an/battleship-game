#ifndef BATTLESHIP_GAME_GAMEENGINE_H
#define BATTLESHIP_GAME_GAMEENGINE_H
#include "ConsoleRender.h"


class GameEngine {
    ConsoleRender& render;

    public:
    GameEngine(ConsoleRender &render) : render(render) {};
};


#endif //BATTLESHIP_GAME_GAMEENGINE_H