#include <filesystem>
#include <fstream>

#include "BoardWidget.h"
#include "ConsoleRender.h"
#include "TextWidget.h"

int main() {
    ConsoleRender render(350, 30);
    BoardWidget widget1(render, 0, 0);
    BoardWidget widget2(render, widget1.getWidth() + 10, 0);
    TextWidget widget3(render, 3, 350 - 3 - 1, widget1.getHeight() + 2);
    widget1.setCellState(1, 1, CellState::shotShip);
    widget1.setCellState(1, 5, CellState::ship);
    widget1.setCellState(4, 8, CellState::shotShip);
    widget1.setCellState(10, 10, CellState::shotShip);
    widget2.setCellState(8, 4, CellState::destroyed);
    render.setOnRead([&](std::string input) {
        std::u32string txt(input.begin(), input.end()); // Assuming only ASCII in input
        widget3.setText(txt);
    });

    render.read(3, widget1.getHeight() + 4);
}
