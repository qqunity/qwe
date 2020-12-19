#include "MainWindow.hpp"
#include "UIMainWindow.hpp"

MainWindow::MainWindow(QWidget *parent) :
        ui(new Ui::MainWindow) {
    this->ui->setupUi(this);
    MainWindow::connect(this->ui->quitButton, &QPushButton::clicked, this, &MainWindow::OnQuitClick);
    MainWindow::connect(this->ui->graphInteractionButton, &QPushButton::clicked, this, &MainWindow::OnGraphInteractionButtonClick);
}

MainWindow::~MainWindow() {
    delete this->ui;
}

void MainWindow::OnQuitClick() {
    this->close();
}

void MainWindow::setGraphInteractionWindow(QWidget *graphInteractionWindow) {
    this->graphInteractionWindow = graphInteractionWindow;
}

void MainWindow::OnGraphInteractionButtonClick() {
    this->close();
    this->graphInteractionWindow->show();
}
