#ifndef GRAPHINTERACTIONWINDOW_H
#define GRAPHINTERACTIONWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GraphInteractionWindow
{
public:
    QTextEdit *graphCommandsFrame;
    QPushButton *submitGraphCommandsButton;
    QTextEdit *sequenceTypeFrame;
    QPushButton *submitsSequenceTypeButton;
    QTextEdit *dictionaryTypeFrame;
    QPushButton *submitDictionaryTypeButton;
    QPushButton *drawGraphButton;
    QLabel *drawGraphLabel;
    QPushButton *drawSkeletonTreeButton;
    QLabel *drawSkeletonTreeLabel;
    QPushButton *quitButton;
    QLabel *errorLabel;
    QTextEdit *graphInteractionCommandsFrame;
    QPushButton *submitGraphInteractionCommandsButton;
    QPushButton *getDistanceButton;
    QLabel *getDistanceLabel;
    QTextEdit *distanceInfoFrame;

    void setupUi(QWidget *GraphInteractionWindow)
    {
        if (GraphInteractionWindow->objectName().isEmpty())
            GraphInteractionWindow->setObjectName(QStringLiteral("GraphInteractionWindow"));
        GraphInteractionWindow->resize(697, 466);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(GraphInteractionWindow->sizePolicy().hasHeightForWidth());
        GraphInteractionWindow->setSizePolicy(sizePolicy);
        graphCommandsFrame = new QTextEdit(GraphInteractionWindow);
        graphCommandsFrame->setObjectName(QStringLiteral("graphCommandsFrame"));
        graphCommandsFrame->setGeometry(QRect(230, 10, 141, 221));
        graphCommandsFrame->setReadOnly(false);
        graphCommandsFrame->setOverwriteMode(false);
        submitGraphCommandsButton = new QPushButton(GraphInteractionWindow);
        submitGraphCommandsButton->setObjectName(QStringLiteral("submitGraphCommandsButton"));
        submitGraphCommandsButton->setGeometry(QRect(380, 90, 61, 61));
        submitGraphCommandsButton->setCursor(QCursor(Qt::PointingHandCursor));
        QIcon icon;
        icon.addFile(QStringLiteral("/Users/denis.maksimov/CLionProjects/qwe/lab2_3/resources/submitIcon.png"), QSize(), QIcon::Normal, QIcon::Off);
        submitGraphCommandsButton->setIcon(icon);
        submitGraphCommandsButton->setIconSize(QSize(50, 50));
        submitGraphCommandsButton->setFlat(true);
        sequenceTypeFrame = new QTextEdit(GraphInteractionWindow);
        sequenceTypeFrame->setObjectName(QStringLiteral("sequenceTypeFrame"));
        sequenceTypeFrame->setGeometry(QRect(20, 10, 141, 91));
        submitsSequenceTypeButton = new QPushButton(GraphInteractionWindow);
        submitsSequenceTypeButton->setObjectName(QStringLiteral("submitsSequenceTypeButton"));
        submitsSequenceTypeButton->setGeometry(QRect(170, 40, 31, 31));
        submitsSequenceTypeButton->setCursor(QCursor(Qt::PointingHandCursor));
        submitsSequenceTypeButton->setIcon(icon);
        submitsSequenceTypeButton->setIconSize(QSize(30, 30));
        submitsSequenceTypeButton->setFlat(true);
        dictionaryTypeFrame = new QTextEdit(GraphInteractionWindow);
        dictionaryTypeFrame->setObjectName(QStringLiteral("dictionaryTypeFrame"));
        dictionaryTypeFrame->setGeometry(QRect(20, 130, 141, 101));
        submitDictionaryTypeButton = new QPushButton(GraphInteractionWindow);
        submitDictionaryTypeButton->setObjectName(QStringLiteral("submitDictionaryTypeButton"));
        submitDictionaryTypeButton->setGeometry(QRect(170, 160, 31, 32));
        submitDictionaryTypeButton->setCursor(QCursor(Qt::PointingHandCursor));
        submitDictionaryTypeButton->setIcon(icon);
        submitDictionaryTypeButton->setIconSize(QSize(30, 30));
        submitDictionaryTypeButton->setFlat(true);
        drawGraphButton = new QPushButton(GraphInteractionWindow);
        drawGraphButton->setObjectName(QStringLiteral("drawGraphButton"));
        drawGraphButton->setGeometry(QRect(0, 310, 161, 101));
        drawGraphButton->setCursor(QCursor(Qt::PointingHandCursor));
        QIcon icon1;
        icon1.addFile(QStringLiteral("/Users/denis.maksimov/CLionProjects/qwe/lab2_3/resources/boxIcon.png"), QSize(), QIcon::Normal, QIcon::Off);
        drawGraphButton->setIcon(icon1);
        drawGraphButton->setIconSize(QSize(150, 150));
        drawGraphButton->setFlat(true);
        drawGraphLabel = new QLabel(GraphInteractionWindow);
        drawGraphLabel->setObjectName(QStringLiteral("drawGraphLabel"));
        drawGraphLabel->setGeometry(QRect(20, 350, 111, 16));
        drawGraphLabel->setAlignment(Qt::AlignCenter);
        drawSkeletonTreeButton = new QPushButton(GraphInteractionWindow);
        drawSkeletonTreeButton->setObjectName(QStringLiteral("drawSkeletonTreeButton"));
        drawSkeletonTreeButton->setGeometry(QRect(530, 320, 161, 81));
        drawSkeletonTreeButton->setCursor(QCursor(Qt::PointingHandCursor));
        drawSkeletonTreeButton->setIcon(icon1);
        drawSkeletonTreeButton->setIconSize(QSize(150, 150));
        drawSkeletonTreeButton->setFlat(true);
        drawSkeletonTreeLabel = new QLabel(GraphInteractionWindow);
        drawSkeletonTreeLabel->setObjectName(QStringLiteral("drawSkeletonTreeLabel"));
        drawSkeletonTreeLabel->setGeometry(QRect(550, 340, 111, 31));
        QFont font;
        font.setPointSize(10);
        drawSkeletonTreeLabel->setFont(font);
        drawSkeletonTreeLabel->setAlignment(Qt::AlignCenter);
        drawSkeletonTreeLabel->setWordWrap(true);
        quitButton = new QPushButton(GraphInteractionWindow);
        quitButton->setObjectName(QStringLiteral("quitButton"));
        quitButton->setGeometry(QRect(660, 430, 31, 32));
        quitButton->setCursor(QCursor(Qt::PointingHandCursor));
        QIcon icon2;
        icon2.addFile(QStringLiteral("/Users/denis.maksimov/CLionProjects/qwe/lab2_3/resources/quitIcon.png"), QSize(), QIcon::Normal, QIcon::Off);
        quitButton->setIcon(icon2);
        quitButton->setIconSize(QSize(25, 25));
        quitButton->setFlat(true);
        errorLabel = new QLabel(GraphInteractionWindow);
        errorLabel->setObjectName(QStringLiteral("errorLabel"));
        errorLabel->setGeometry(QRect(40, 429, 611, 31));
        errorLabel->setAlignment(Qt::AlignCenter);
        errorLabel->setWordWrap(true);
        graphInteractionCommandsFrame = new QTextEdit(GraphInteractionWindow);
        graphInteractionCommandsFrame->setObjectName(QStringLiteral("graphInteractionCommandsFrame"));
        graphInteractionCommandsFrame->setGeometry(QRect(460, 10, 141, 221));
        submitGraphInteractionCommandsButton = new QPushButton(GraphInteractionWindow);
        submitGraphInteractionCommandsButton->setObjectName(QStringLiteral("submitGraphInteractionCommandsButton"));
        submitGraphInteractionCommandsButton->setGeometry(QRect(610, 90, 61, 61));
        submitGraphInteractionCommandsButton->setCursor(QCursor(Qt::PointingHandCursor));
        submitGraphInteractionCommandsButton->setIcon(icon);
        submitGraphInteractionCommandsButton->setIconSize(QSize(50, 50));
        submitGraphInteractionCommandsButton->setFlat(true);
        getDistanceButton = new QPushButton(GraphInteractionWindow);
        getDistanceButton->setObjectName(QStringLiteral("getDistanceButton"));
        getDistanceButton->setGeometry(QRect(260, 320, 161, 81));
        getDistanceButton->setCursor(QCursor(Qt::PointingHandCursor));
        getDistanceButton->setIcon(icon1);
        getDistanceButton->setIconSize(QSize(150, 150));
        getDistanceButton->setFlat(true);
        getDistanceLabel = new QLabel(GraphInteractionWindow);
        getDistanceLabel->setObjectName(QStringLiteral("getDistanceLabel"));
        getDistanceLabel->setGeometry(QRect(270, 330, 131, 51));
        getDistanceLabel->setFont(font);
        getDistanceLabel->setAlignment(Qt::AlignCenter);
        getDistanceLabel->setWordWrap(true);
        distanceInfoFrame = new QTextEdit(GraphInteractionWindow);
        distanceInfoFrame->setObjectName(QStringLiteral("distanceInfoFrame"));
        distanceInfoFrame->setGeometry(QRect(270, 270, 141, 41));
        drawGraphLabel->raise();
        drawSkeletonTreeLabel->raise();
        graphCommandsFrame->raise();
        submitGraphCommandsButton->raise();
        sequenceTypeFrame->raise();
        submitsSequenceTypeButton->raise();
        dictionaryTypeFrame->raise();
        submitDictionaryTypeButton->raise();
        drawGraphButton->raise();
        drawSkeletonTreeButton->raise();
        quitButton->raise();
        errorLabel->raise();
        graphInteractionCommandsFrame->raise();
        submitGraphInteractionCommandsButton->raise();
        getDistanceLabel->raise();
        distanceInfoFrame->raise();
        getDistanceButton->raise();

        retranslateUi(GraphInteractionWindow);

        QMetaObject::connectSlotsByName(GraphInteractionWindow);
    } // setupUi

    void retranslateUi(QWidget *GraphInteractionWindow)
    {
        GraphInteractionWindow->setWindowTitle(QApplication::translate("GraphInteractionWindow", "GraphInteractionWindow", Q_NULLPTR));
        graphCommandsFrame->setPlaceholderText(QApplication::translate("GraphInteractionWindow", "\320\222\320\262\320\265\320\264\320\270\321\202\320\265  \320\263\321\200\320\260\321\204 \320\270\321\201\320\277\320\276\320\273\321\214\320\267\321\203\321\217 \321\201\321\202\320\260\320\275\320\264\320\260\321\200\321\202\320\275\321\213\320\265 \320\272\320\276\320\274\320\260\320\275\320\264\321\213, \321\200\320\260\320\267\320\264\320\265\320\273\321\217\321\217 \320\270\321\205 \321\201\320\270\320\274\320\262\320\276\320\273\320\276\320\274 \320\277\320\265\321\200\320\265\320\275\320\276\321\201\320\260 \321\201\321\202\321\200\320\276\320\272\320\270(add_vertex v, add_edge v1 v2 label)", Q_NULLPTR));
        submitGraphCommandsButton->setText(QString());
        sequenceTypeFrame->setPlaceholderText(QApplication::translate("GraphInteractionWindow", "\320\222\320\262\320\265\320\264\320\270\321\202\320\265 \320\261\320\260\320\267\320\276\320\262\321\213\320\271 \321\202\320\270\320\277 \320\277\320\276\321\201\320\273\320\265\320\264\320\276\320\262\320\260\321\202\320\265\320\273\321\214\320\275\320\276\321\201\321\202\320\270  (ArraySequence/LinkedListSequence)", Q_NULLPTR));
        submitsSequenceTypeButton->setText(QString());
        dictionaryTypeFrame->setPlaceholderText(QApplication::translate("GraphInteractionWindow", "\320\222\320\262\320\265\320\264\320\270\321\202\320\265 \320\261\320\260\320\267\320\276\320\262\321\213\320\271 \321\202\320\270\320\277 \321\201\320\273\320\276\320\262\320\260\321\200\321\217 (AVLTreeDictionary/BTreeDictionary)", Q_NULLPTR));
        submitDictionaryTypeButton->setText(QString());
        drawGraphButton->setText(QString());
        drawGraphLabel->setText(QApplication::translate("GraphInteractionWindow", "\320\237\320\276\321\201\321\202\321\200\320\276\320\270\321\202\321\214 \320\263\321\200\320\260\321\204", Q_NULLPTR));
        drawSkeletonTreeButton->setText(QString());
        drawSkeletonTreeLabel->setText(QApplication::translate("GraphInteractionWindow", "\320\237\320\276\321\201\321\202\321\200\320\276\320\270\321\202\321\214 \320\274\320\270\320\275\320\270\320\274\320\260\320\273\321\214\320\275\320\276\320\265 \320\276\321\201\321\202\320\276\320\262\320\275\320\276\320\265 \320\264\320\265\321\200\320\265\320\262\320\276", Q_NULLPTR));
        quitButton->setText(QString());
        errorLabel->setText(QString());
        graphInteractionCommandsFrame->setPlaceholderText(QApplication::translate("GraphInteractionWindow", "\320\222\320\262\320\265\320\264\320\270\321\202\320\265 \320\272\320\276\320\274\320\260\320\275\320\264\321\213 \320\264\320\273\321\217 \320\270\320\267\320\274\320\265\320\275\320\265\320\275\320\270\321\217 \320\263\321\200\320\260\321\204\320\260,  \321\200\320\260\320\267\320\264\320\265\320\273\321\217\321\217 \320\270\321\205 \321\201\320\270\320\274\320\262\320\276\320\273\320\276\320\274 \320\277\320\265\321\200\320\265\320\275\320\276\321\201\320\260 \321\201\321\202\321\200\320\276\320\272\320\270(add_vertex v, delete_vertex v, add_edge v1 v2 label, delete_edge v1 v2)", Q_NULLPTR));
        submitGraphInteractionCommandsButton->setText(QString());
        getDistanceButton->setText(QString());
        getDistanceLabel->setText(QApplication::translate("GraphInteractionWindow", "\320\237\320\276\320\273\321\203\321\207\320\270\321\202\321\214 \321\200\320\260\321\201\321\201\321\202\320\276\321\217\320\275\320\270\320\265 \320\274\320\265\320\266\320\264\321\203 \320\262\320\265\321\200\321\210\320\270\320\275\320\260\320\274\320\270", Q_NULLPTR));
        distanceInfoFrame->setPlaceholderText(QApplication::translate("GraphInteractionWindow", "\320\222\320\262\320\265\320\264\320\270\321\202\320\265 \320\264\320\262\320\265 \320\262\320\265\321\200\321\210\320\270\320\275\321\213 (a,b)", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class GraphInteractionWindow: public Ui_GraphInteractionWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // GRAPHINTERACTIONWINDOW_H
