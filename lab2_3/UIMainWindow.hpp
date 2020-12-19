#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QPushButton *quitButton;
    QPushButton *graphInteractionButton;
    QLabel *label;

    void setupUi(QWidget *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(500, 500);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        quitButton = new QPushButton(MainWindow);
        quitButton->setObjectName(QStringLiteral("quitButton"));
        quitButton->setGeometry(QRect(460, 460, 41, 41));
        quitButton->setCursor(QCursor(Qt::PointingHandCursor));
        QIcon icon;
        icon.addFile(QStringLiteral("/Users/denis.maksimov/CLionProjects/qwe/lab2_3/resources/quitIcon.png"), QSize(), QIcon::Normal, QIcon::Off);
        quitButton->setIcon(icon);
        quitButton->setIconSize(QSize(25, 25));
        quitButton->setCheckable(false);
        quitButton->setFlat(true);
        graphInteractionButton = new QPushButton(MainWindow);
        graphInteractionButton->setObjectName(QStringLiteral("graphInteractionButton"));
        graphInteractionButton->setGeometry(QRect(140, 190, 221, 111));
        graphInteractionButton->setCursor(QCursor(Qt::PointingHandCursor));
        QIcon icon1;
        icon1.addFile(QStringLiteral("/Users/denis.maksimov/CLionProjects/qwe/lab2_3/resources/boxIcon.png"), QSize(), QIcon::Normal, QIcon::Off);
        graphInteractionButton->setIcon(icon1);
        graphInteractionButton->setIconSize(QSize(200, 200));
        graphInteractionButton->setCheckable(false);
        graphInteractionButton->setAutoRepeat(false);
        graphInteractionButton->setAutoExclusive(false);
        graphInteractionButton->setFlat(true);
        label = new QLabel(MainWindow);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(180, 230, 131, 20));
        QFont font;
        font.setPointSize(16);
        label->setFont(font);
        quitButton->raise();
        label->raise();
        graphInteractionButton->raise();

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QWidget *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        quitButton->setText(QString());
        graphInteractionButton->setText(QString());
        label->setText(QApplication::translate("MainWindow", "Graph interaction", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // MAINWINDOW_H
