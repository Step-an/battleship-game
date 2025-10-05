#include <filesystem>
#include <fstream>
#include <iostream>

#include "BoardWidget.h"
#include "ConsoleRender.h"

int main() {
    ConsoleRender render(350, 30);
    BoardWidget widget1(render, 0, 0);
    BoardWidget widget2(render, widget1.getWidth() + 10, 0);
}
