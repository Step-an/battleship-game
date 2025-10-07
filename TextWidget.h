#ifndef BATTLESHIP_GAME_TEXTWIDGET_H
#define BATTLESHIP_GAME_TEXTWIDGET_H
#include <string>

#include "ConsoleRender.h"


class TextWidget {
    int xStart;
    int xEnd;
    int y;
    std::u32string text;
    ConsoleRender &render;
public:
    TextWidget(ConsoleRender &render, int xStart, int xEnd, int y);
    void setText(std::u32string _text);
    std::u32string_view getText() const;
};


#endif //BATTLESHIP_GAME_TEXTWIDGET_H