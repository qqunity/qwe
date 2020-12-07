#include "TestsField.hpp"


TestsField::TestsField(QWidget *mainWindow){
    this->mainWindow = mainWindow;
    QProcess proc;
    proc.start("/Users/denis.maksimov/CLionProjects/qwe/lab2_2/run_tests");
    proc.waitForStarted(-1);
    proc.waitForFinished(-1);
    QString text = proc.readAll();
    text.replace("[32m", "");
    text.replace("[0m", "");
    auto label = new QLabel(text);
    label->setStyleSheet("QLabel{color: white;}");
    auto verticalLayout = new QVBoxLayout(this);
    verticalLayout->addWidget(label);
    auto quitButton = new QPushButton("Quit", this);
    TestsField::connect(quitButton, &QPushButton::clicked, this, &TestsField::OnQuitClick);
    verticalLayout->addWidget(quitButton);
    this->setLayout(verticalLayout);
}

void TestsField::OnQuitClick() {
    this->close();
    this->mainWindow->show();
}
