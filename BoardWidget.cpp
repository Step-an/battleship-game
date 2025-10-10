#include "BoardWidget.h"

#include <iostream>

const std::u32string boardCanvas = UR"(    A    B     C   D     E   F    G    H    I    J
  ╔════╤════╤════╤════╤════╤════╤════╤════╤════╤════╗
 1║    │    │    │    │    │    │    │    │    │    ║
  ╟────┼────┼────┼────┼────┼────┼────┼────┼────┼────╢
 2║    │    │    │    │    │    │    │    │    │    ║
  ╟────┼────┼────┼────┼────┼────┼────┼────┼────┼────╢
 3║    │    │    │    │    │    │    │    │    │    ║
  ╟────┼────┼────┼────┼────┼────┼────┼────┼────┼────╢
 4║    │    │    │    │    │    │    │    │    │    ║
  ╟────┼────┼────┼────┼────┼────┼────┼────┼────┼────╢
 5║    │    │    │    │    │    │    │    │    │    ║
  ╟────┼────┼────┼────┼────┼────┼────┼────┼────┼────╢
 6║    │    │    │    │    │    │    │    │    │    ║
  ╟────┼────┼────┼────┼────┼────┼────┼────┼────┼────╢
 7║    │    │    │    │    │    │    │    │    │    ║
  ╟────┼────┼────┼────┼────┼────┼────┼────┼────┼────╢
 8║    │    │    │    │    │    │    │    │    │    ║
  ╟────┼────┼────┼────┼────┼────┼────┼────┼────┼────╢
 9║    │    │    │    │    │    │    │    │    │    ║
  ╟────┼────┼────┼────┼────┼────┼────┼────┼────┼────╢
10║    │    │    │    │    │    │    │    │    │    ║
  ╚════╧════╧════╧════╧════╧════╧════╧════╧════╧════╝)";


BoardWidget::BoardWidget(std::shared_ptr<ConsoleRender> render, uint32_t left_top_x, uint32_t left_top_y): render(render), left_top_x(left_top_x), left_top_y(left_top_y) {
    uint32_t curx = left_top_x, cury = left_top_y;
    for (auto ch : boardCanvas) {
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