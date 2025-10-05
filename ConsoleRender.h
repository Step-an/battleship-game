#ifndef BATTLESHIP_GAME_CONSOLERENDER_H
#define BATTLESHIP_GAME_CONSOLERENDER_H
#include <cstdint>
#include <functional>
#include <string>


class ConsoleRender {
    char *buffer;
    uint32_t width;
    uint32_t height;

    void cursorOn();

    void cursorOff();

    void setPosition(uint32_t x, uint32_t y);
public:
    ConsoleRender(uint32_t width, uint32_t height);
    char getChar(uint32_t x, uint32_t y);
    void setChar(uint32_t x, uint32_t y, char c);
    void sePosToRead(uint32_t x, uint32_t y);
    void onRead(std::function<void(const std::string&)> callback);
    void setCanvas(char *data);
    void reRender();
    ~ConsoleRender();
};


#endif //BATTLESHIP_GAME_CONSOLERENDER_H