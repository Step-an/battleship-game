#ifndef BATTLESHIP_GAME_CONSOLERENDER_H
#define BATTLESHIP_GAME_CONSOLERENDER_H
#include <cstdint>
#include <functional>
#include <string>


class ConsoleRender {
    char32_t *buffer;
    uint32_t width;
    uint32_t height;
    uint32_t readx = 0;
    uint32_t ready = 0;
    std::function<void(const std::string&)> callback;

    void cursorOn();

    void cursorOff();

    void setPosition(uint32_t x, uint32_t y);

    char* char_utf32_to_utf8(char32_t utf32, const char* buffer);
public:
    ConsoleRender(uint32_t width, uint32_t height);
    char32_t getChar(uint32_t x, uint32_t y);
    void setChar(uint32_t x, uint32_t y, char32_t c);
    void read();
    void setOnRead(std::function<void(const std::string&)> fun);
    void reRender();
    void setPosToRead(uint32_t x, uint32_t y);
    std::string readValue();
    ~ConsoleRender();
};


#endif //BATTLESHIP_GAME_CONSOLERENDER_H