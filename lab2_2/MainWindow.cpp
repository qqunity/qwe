#include "MainWindow.hpp"

MainWindow::MainWindow(QWidget *parent) {
    auto verticalLayout = new QVBoxLayout(this);

    this->gameButton = new QPushButton("Start game", this);
    MainWindow::connect(this->gameButton, &QPushButton::clicked, this, &MainWindow::OnGameButtonClick);
    verticalLayout->addWidget(this->gameButton);

    this->vectorButton = new QPushButton("Vector interaction", this);
    MainWindow::connect(this->vectorButton, &QPushButton::clicked, this, &MainWindow::OnVectorButtonClick);
    verticalLayout->addWidget(this->vectorButton);

    this->sequenceButton = new QPushButton("Sequence interaction", this);
    MainWindow::connect(this->sequenceButton, &QPushButton::clicked, this, &MainWindow::OnSequenceButtonClick);
    verticalLayout->addWidget(this->sequenceButton);

    this->testsButton = new QPushButton("Start tests", this);
    MainWindow::connect(this->testsButton, &QPushButton::clicked, this, &MainWindow::OnTestsButtonClick);
    verticalLayout->addWidget(this->testsButton);

    this->quitButton = new QPushButton("Quit", this);
    MainWindow::connect(this->quitButton, &QPushButton::clicked, this, &MainWindow::OnQuitClick);
    verticalLayout->addWidget(this->quitButton);

    this->setLayout(verticalLayout);
}

void MainWindow::OnGameButtonClick() {
    this->close();
    this->game->show();
}

void MainWindow::setGameField(GameFiled *game) {
    this->game = game;
}

void MainWindow::OnQuitClick() {
    this->close();
}

void MainWindow::OnTestsButtonClick() {
    this->close();
    this->tests->show();
}

void MainWindow::setTestsField(TestsField *tests) {
    this->tests = tests;
}

void MainWindow::setVectorField(VectorField *vector) {
    this->vector = vector;
}

void MainWindow::OnVectorButtonClick() {
    this->close();
    this->vector->show();
}

void MainWindow::setSequenceField(SequenceField *sequence) {
    this->sequence = sequence;
}

void MainWindow::OnSequenceButtonClick() {
    this->close();
    this->sequence->show();
}
