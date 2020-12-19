#ifndef GRAPHVISUALIZATIONWINDOW_H
#define GRAPHVISUALIZATIONWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GraphVisualizationWindow
{
public:
    QPushButton *quitButton;
    QLabel *infoLabel;

    void setupUi(QWidget *GraphVisualizationWindow)
    {
        if (GraphVisualizationWindow->objectName().isEmpty())
            GraphVisualizationWindow->setObjectName(QStringLiteral("GraphVisualizationWindow"));
        GraphVisualizationWindow->resize(600, 600);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(GraphVisualizationWindow->sizePolicy().hasHeightForWidth());
        GraphVisualizationWindow->setSizePolicy(sizePolicy);
        quitButton = new QPushButton(GraphVisualizationWindow);
        quitButton->setObjectName(QStringLiteral("quitButton"));
        quitButton->setGeometry(QRect(560, 560, 31, 32));
        quitButton->setCursor(QCursor(Qt::PointingHandCursor));
        QIcon icon;
        icon.addFile(QStringLiteral("/Users/denis.maksimov/CLionProjects/qwe/lab2_3/resources/quitIcon.png"), QSize(), QIcon::Normal, QIcon::Off);
        quitButton->setIcon(icon);
        quitButton->setIconSize(QSize(25, 25));
        quitButton->setFlat(true);
        infoLabel = new QLabel(GraphVisualizationWindow);
        infoLabel->setObjectName(QStringLiteral("infoLabel"));
        infoLabel->setGeometry(QRect(40, 570, 511, 20));
        infoLabel->setAlignment(Qt::AlignCenter);
        infoLabel->setWordWrap(true);

        retranslateUi(GraphVisualizationWindow);

        quitButton->setDefault(false);


        QMetaObject::connectSlotsByName(GraphVisualizationWindow);
    } // setupUi

    void retranslateUi(QWidget *GraphVisualizationWindow)
    {
        GraphVisualizationWindow->setWindowTitle(QApplication::translate("GraphVisualizationWindow", "GraphVisualizationWindow", Q_NULLPTR));
        quitButton->setText(QString());
        infoLabel->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class GraphVisualizationWindow: public Ui_GraphVisualizationWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // GRAPHVISUALIZATIONWINDOW_H
