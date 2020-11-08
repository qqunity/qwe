#include "GameField.hpp"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    GameFiled game(nullptr, 3, 120);

    game.setFixedSize(400, 400);
    game.setWindowTitle("Tic-Tac-Toe");
    game.show();

    return app.exec();
}