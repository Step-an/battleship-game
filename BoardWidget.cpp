#include "BoardWidget.h"

#include <iostream>

BoardWidget::BoardWidget(ConsoleRender &render, uint32_t left_top_x, uint32_t left_top_y): render(render) {
    std::basic_ifstream<char32_t> mf("/home/stepan/school/programming_school/battleship-game/board.txt");
    int size = std::filesystem::file_size("/home/stepan/school/programming_school/battleship-game/board.txt");
    std::u32string content(size/4+1, '\0');
    mf.read(&content[0], size/4+1);
    uint32_t curx = left_top_x, cury = left_top_y;
    for (int i = 0; i < content.size(); i++) {
        if (content[i] == U'\n') {
            cury++;
            width = std::max(width, curx - left_top_x + 1);
            curx = left_top_x;
        } else {
            render.setChar(curx, cury, content[i]);
            curx++;
        }
    }
    height = cury - left_top_y + 1;
    render.reRender();
}
