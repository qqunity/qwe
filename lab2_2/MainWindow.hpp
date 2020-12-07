#ifndef LAB_2_MAINWINDOW_HPP
#define LAB_2_MAINWINDOW_HPP

#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include "TestsField.hpp"
#include "GameField.hpp"
#include "VectorField.hpp"
#include "SequenceField.hpp"


class MainWindow : public QWidget {

Q_OBJECT

public:
    explicit MainWindow(QWidget *parent);

    void setGameField(GameFiled *game);

    void setTestsField(TestsField *tests);

    void setVectorField(VectorField *vector);

    void setSequenceField(SequenceField *sequence);


protected:

private slots:

    void OnGameButtonClick();

    void OnTestsButtonClick();

    void OnVectorButtonClick();

    void OnSequenceButtonClick();

    void OnQuitClick();

private:
    GameFiled *game;
    TestsField *tests;
    VectorField *vector;
    SequenceField *sequence;
    QPushButton *quitButton;
    QPushButton *testsButton;
    QPushButton *gameButton;
    QPushButton *vectorButton;
    QPushButton *sequenceButton;
};

#endif
