#ifndef LAB_2_TESTSFIELD_HPP
#define LAB_2_TESTSFIELD_HPP

#include <QWidget>
#include <QProcess>
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>

class TestsField : public QWidget {
Q_OBJECT

public:
    explicit TestsField(QWidget *mainWindow = nullptr);

private slots:

    void OnQuitClick();

private:
    QWidget *mainWindow;
};

#endif
