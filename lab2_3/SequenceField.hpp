
#ifndef LAB_2_SEQUENCEFIELD_HPP
#define LAB_2_SEQUENCEFIELD_HPP

#include <QWidget>
#include <QTextEdit>
#include <QGridLayout>
#include <QPushButton>
#include <QString>
#include <QLabel>
#include <unistd.h>
#include "IDictionary.hpp"
#include "BTreeDictionary.hpp"
#include "AVLTreeDictionary.hpp"

class SequenceField : public QWidget {
    Q_OBJECT

public:
    explicit SequenceField(QWidget *mainWindow = nullptr);

private slots:

    void OnQuitClick();

    void OnSubmitTypeOfDictionaryInput();

    void OnSubmitTypeOfSequenceInput();

    void OnSubmitInputSequence();

    void OnSubmitLValues();


private:
    QTextEdit *sequence;
    QTextEdit *typeOfDictionary;
    QTextEdit *typeOfSequence;
    QTextEdit *lValues;
    QLabel *subMessage;
    QLabel *message;
    unsigned int lmax;
    unsigned int lmin;
    std::string baseTypeOfDictionary;
    std::string baseTypeOfSequence;
    QWidget *mainWindow;
    dictionary::IDictionary<QString, QString> *dict;
};


#endif
