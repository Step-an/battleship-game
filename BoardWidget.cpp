#include "BoardWidget.h"

#include <iostream>

int BoardWidget::readUTF32Char(std::ifstream &file, char32_t &output) {
    char ch[4];
    file.read(ch, 4);
    if (file.fail()) {
        return -1;
    } else {
        std::swap(ch[0], ch[3]);
        std::swap(ch[1], ch[2]);
        output = *reinterpret_cast<char32_t*>(ch);
        return 0;
    }
}

BoardWidget::BoardWidget(std::shared_ptr<ConsoleRender> render, uint32_t left_top_x, uint32_t left_top_y): render(render), left_top_x(left_top_x), left_top_y(left_top_y) {
    std::ifstream mf("/home/stepan/school/programming_school/battleship-game/board.txt");
    uint32_t curx = left_top_x, cury = left_top_y;
    char32_t ch;
    while (readUTF32Char(mf, ch) != -1) {
        if (ch == U'\n') {
            cury++;
            width = std::max(width, curx - left_top_x + 1);
            curx = left_top_x;
        } else {
            render->setChar(curx, cury, ch);
            curx++;
        }
    }
    height = cury - left_top_y + 1;
    render->reRender();
}

void BoardWidget::setCellState(int column, int raw, CellState state) {
    int y = 2 + (raw - 1) * 2 + left_top_y;
    int x = 4 + (column - 1) * 5 + left_top_x;
    char32_t ch;
    switch (state) {
        case CellState::destroyed:
            ch = U'╳';
            break;
        case CellState::untouched:
            ch = U'\0';
            break;
        case CellState::ship:
            ch = U'□';
            break;
        case CellState::shotNoShip:
            ch = U'*';
            break;
        case CellState::shotShip:
            ch = U'x';
            break;
    }
    render->setChar(x, y, ch);
    render->setChar(x + 1, y, ch);
    render->reRender();
}