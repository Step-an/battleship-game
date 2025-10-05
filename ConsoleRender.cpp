#include "ConsoleRender.h"

#include <stdexcept>

ConsoleRender::ConsoleRender(uint32_t width, uint32_t height) : width(width), height(height) {
    buffer = new char32_t[width * height * 1]();
}

char32_t ConsoleRender::getChar(uint32_t x, uint32_t y) {
    return buffer[y * width + x];
}

void ConsoleRender::setChar(uint32_t x, uint32_t y, char32_t c) {
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
            if (getChar(x, y) == U'\0') {
                putchar(' ');
            } else {
                char buff[5];
                char_utf32_to_utf8(getChar(x, y), buff);
                printf("%s", buff);
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

char* ConsoleRender::char_utf32_to_utf8(char32_t utf32, const char* buffer) {
    char* end = const_cast<char*>(buffer);
    if(utf32 < 0x7F) *(end++) = static_cast<unsigned>(utf32);
    else if(utf32 < 0x7FF) {
        *(end++) = 0b1100'0000 + static_cast<unsigned>(utf32 >> 6);
        *(end++) = 0b1000'0000 + static_cast<unsigned>(utf32 & 0b0011'1111);
    }
    else if(utf32 < 0x10000){
        *(end++) = 0b1110'0000 + static_cast<unsigned>(utf32 >> 12);
        *(end++) = 0b1000'0000 + static_cast<unsigned>((utf32 >> 6) & 0b0011'1111);
        *(end++) = 0b1000'0000 + static_cast<unsigned>(utf32 & 0b0011'1111);
    } else if(utf32 < 0x110000) {
        *(end++) = 0b1111'0000 + static_cast<unsigned>(utf32 >> 18);
        *(end++) = 0b1000'0000 + static_cast<unsigned>((utf32 >> 12) & 0b0011'1111);
        *(end++) = 0b1000'0000 + static_cast<unsigned>((utf32 >> 6) & 0b0011'1111);
        *(end++) = 0b1000'0000 + static_cast<unsigned>(utf32 & 0b0011'1111);
    }
    else throw std::runtime_error("something went wrong");
    *end = '\0';
    return end;
}

