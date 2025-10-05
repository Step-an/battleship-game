#include "ConsoleRender.h"

ConsoleRender::ConsoleRender(uint32_t width, uint32_t height) : width(width), height(height) {
    buffer = new char[width * height * 1]();
}

char ConsoleRender::getChar(uint32_t x, uint32_t y) {
    return buffer[y * width + x];
}

void ConsoleRender::setChar(uint32_t x, uint32_t y, char c) {
    buffer[y*width + x] = c;
}

void ConsoleRender::sePosToRead(uint32_t x, uint32_t y) {
}

void ConsoleRender::onRead(std::function<void(const std::string&)> callback) {

}

void ConsoleRender::setCanvas(char *data) {

}

void ConsoleRender::reRender() {
    cursorOff();
    setPosition(1, 1);
    for (uint32_t y = 0; y < height; y++) {
        for (uint32_t x = 0; x < width; x++) {
            if (getChar(x, y) == '\0') {
                putchar(' ');
            } else {
                putchar(getChar(x, y));
            }
            if (x == width - 1) {
                setPosition(1, y + 2);
            }
        }
    }
}

ConsoleRender::~ConsoleRender() {
    delete[] buffer;
}

void ConsoleRender::setPosition(uint32_t x, uint32_t y) {
    printf("\x1b[%i;%iH", y, x);
}

void ConsoleRender::cursorOn()
{
    printf("\x1b[?25h");
}

void ConsoleRender::cursorOff() {
    printf("\x1b[?25l");
}


