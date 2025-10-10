#ifndef BATTLESHIP_GAME_TEXTWIDGET_H
#define BATTLESHIP_GAME_TEXTWIDGET_H
#include <memory>
#include <string>

#include "ConsoleRender.h"


class TextWidget {
    int xStart;
    int xEnd;
    int y;
    std::u32string text;
    std::shared_ptr<ConsoleRender> render;
public:
    TextWidget(std::shared_ptr<ConsoleRender> render, int xStart, int xEnd, int y);

    void setText(std::u32string _text);

    void setText(std::string _text);

    void appendText(std::string _text);

    std::u32string_view getText() const;
};


#endif //BATTLESHIP_GAME_TEXTWIDGET_H