#ifndef BATTLESHIP_GAME_CONSOLERENDER_H
#define BATTLESHIP_GAME_CONSOLERENDER_H
#include <cstdint>
#include <functional>
#include <string>


class ConsoleRender {
    char32_t *buffer;
    uint32_t width;
    uint32_t height;

    void cursorOn();

    void cursorOff();

    void setPosition(uint32_t x, uint32_t y);

    char* char_utf32_to_utf8(char32_t utf32, const char* buffer);
public:
    ConsoleRender(uint32_t width, uint32_t height);
    char32_t getChar(uint32_t x, uint32_t y);
    void setChar(uint32_t x, uint32_t y, char32_t c);
    void sePosToRead(uint32_t x, uint32_t y);
    void onRead(std::function<void(const std::string&)> callback);
    void setCanvas(char *data);
    void reRender();
    ~ConsoleRender();
};


#endif //BATTLESHIP_GAME_CONSOLERENDER_H