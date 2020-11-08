#ifndef LAB_2_GAMEFIELD_HPP
#define LAB_2_GAMEFIELD_HPP


#include <QWidget>
#include <QApplication>
#include <QPushButton>
#include <QLabel>
#include <vector>
#include <iostream>
#include "Matrix.hpp"
#include "Minimax.hpp"
#include "Array.hpp"

struct GameOutcome {
    unsigned int draw = 0;
    unsigned int winX = 1;
    unsigned int winO = 2;
};

class GameFiled : public QWidget {

Q_OBJECT

public:
    explicit GameFiled(QWidget *parent = nullptr, unsigned int gridSize = 3, char startSymbol = 120);

    bool checkWin();

    bool checkDraw();

    bool isEnded();

    void finish();


private:
    void gameOver(QPainter &painter, unsigned int reason);

    void clearWidgets(QLayout *layout);

    char getNextSymbol(char symbol);

    matrix::Matrix<char> getCurrentStateOfGameGrid();

    void makeMove();

protected:
    void paintEvent(QPaintEvent *paintEvent) override;

    void keyPressEvent(QKeyEvent *keyEvent) override;

private slots:

    void OnClick();

private:
    QLabel *gameMessage;
    QLabel *errorMessage;
    matrix::Matrix<QPushButton *> filedButtons;
    Symbols symbols;
    GameOutcome gameOutcome;
    Minimax *ai;
    unsigned int gridSize;
    bool inGame{};
    unsigned int cntMoves;
    char currentSymbol;
    char startSymbol;
    bool isForcedExit;
    bool isQuitButtonAppeared;
};


#endif
