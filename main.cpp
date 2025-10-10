#include <filesystem>
#include <fstream>

#include "BoardWidget.h"
#include "ConsoleRender.h"
#include "GameEngine.h"
#include "TextWidget.h"

int main() {
    std::shared_ptr<ConsoleRender> render = std::make_shared<ConsoleRender>(350, 30);
    std::vector<BoardWidget> boards;
    TextWidget battleshipWriting(render, 50, 100, 0);
    TextWidget frstPlayer(render, 20, 35, 1);
    frstPlayer.setText("First Player");
    TextWidget secondPlayer(render, 85, 95, 1);
    secondPlayer.setText("Second Player");
    battleshipWriting.setText("Battleship Game");
    boards.emplace_back(render, 0, 2);
    boards.emplace_back(render, boards[0].getWidth() + 10, 2);
    std::shared_ptr<TextWidget> widget3 = std::make_shared<TextWidget>(render, 3, 200, boards[0].getHeight() + 5);
    std::shared_ptr<TextWidget> widget4 = std::make_shared<TextWidget>(render, 3, 350 - 3 - 1, boards[0].getHeight() + 4);
    TextWidget legenda(render, 7, 200, boards[0].getHeight() + 3);
    legenda.setText(U"╳╳ - ship destroyed, □□ - ship placed, ** - cell was shot but no ship was damaged, xx - ship damaged");
    render->setPosToRead(3, boards[0].getHeight() + 7);
    GameEngine game(render, boards, widget3, widget4);
    game.start();
}
