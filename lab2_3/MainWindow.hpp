#ifndef LAB2_3_MAINWINDOW_HPP
#define LAB2_3_MAINWINDOW_HPP

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QWidget {
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

    void setGraphInteractionWindow(QWidget *graphInteractionWindow);

    ~MainWindow() override;

private slots:
    void OnQuitClick();

    void OnGraphInteractionButtonClick();


private:
    QWidget *graphInteractionWindow;
    Ui::MainWindow *ui;
};

#endif
