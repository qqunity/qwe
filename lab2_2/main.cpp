#include "GameField.hpp"
#include "MainWindow.hpp"
#include "TestsField.hpp"
#include "VectorField.hpp"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    MainWindow mainWindow(nullptr);
    mainWindow.setMinimumSize(300, 300);
    mainWindow.setWindowTitle("Main");

    GameFiled game(&mainWindow, 3, 120);
    game.setMinimumSize(600, 600);
    game.setWindowTitle("Tic-Tac-Toe");

    TestsField tests(&mainWindow);
    tests.setMinimumSize(400, 400);

    VectorField vector(&mainWindow);
    vector.setMinimumSize(800, 400);

    SequenceField sequence(&mainWindow);
    sequence.setMinimumSize(800, 400);



    mainWindow.setGameField(&game);
    mainWindow.setTestsField(&tests);
    mainWindow.setVectorField(&vector);
    mainWindow.setSequenceField(&sequence);

    mainWindow.show();

    return app.exec();
}