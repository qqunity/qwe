#ifndef LAB_2_VECTORFIELD_HPP
#define LAB_2_VECTORFIELD_HPP

#include <QWidget>
#include <QTextEdit>
#include <QGridLayout>
#include <QPushButton>
#include <QString>
#include <QLabel>
#include "SparseVector.hpp"

class VectorField : public QWidget {
    Q_OBJECT

public:
    explicit VectorField(QWidget *mainWindow = nullptr);

private:
    void updateVectorOutputLabel();

private slots:

    void OnQuitClick();

    void OnSubmitVectorInput();

    void OnSubmitTypeOfDictionaryInput();

    void OnSubmitTypeOfSequenceInput();

    void OnSubmitCommandInput();


private:
    QWidget *mainWindow;
    QTextEdit *vectorInput;
    QTextEdit *typeOfDictionary;
    QTextEdit *typeOfSequence;
    QTextEdit *command;
    QLabel *vectorOutputLabel;
    QLabel *subMessage;
    std::string baseTypeOfDictionary;
    std::string baseTypeOfSequence;
    vector::SparseVector<int> *vector;
};


#endif
