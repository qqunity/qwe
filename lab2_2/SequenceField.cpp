#include "SequenceField.hpp"

SequenceField::SequenceField(QWidget *mainWindow) {
    this->mainWindow = mainWindow;
    auto *grid = new QGridLayout(this);

    auto typeOfDictionaryLabel = new QLabel("Enter base type of dictionary\n(BTreeDictionary/AVLTreeDictionary):");
    typeOfDictionaryLabel->setStyleSheet("QLabel{color: white;}");
    grid->addWidget(typeOfDictionaryLabel, 0, 0);

    this->typeOfDictionary = new QTextEdit();
    this->typeOfDictionary->setFixedSize(300, 25);
    grid->addWidget(this->typeOfDictionary, 0, 1);

    auto submitInputTypeOfDictionaryButton = new QPushButton("Submit", this);
    SequenceField::connect(submitInputTypeOfDictionaryButton, &QPushButton::clicked, this, &SequenceField::OnSubmitTypeOfDictionaryInput);
    grid->addWidget(submitInputTypeOfDictionaryButton, 0, 2);

    auto typeOfSequenceLabel = new QLabel("Enter base type of sequence\n(ArraySequence/LinkedListSequence):");
    typeOfSequenceLabel->setStyleSheet("QLabel{color: white;}");
    grid->addWidget(typeOfSequenceLabel, 1, 0);

    this->typeOfSequence = new QTextEdit();
    this->typeOfSequence->setFixedSize(300, 25);
    grid->addWidget(this->typeOfSequence, 1, 1);

    auto submitInputTypeOfSequenceButton = new QPushButton("Submit", this);
    SequenceField::connect(submitInputTypeOfSequenceButton, &QPushButton::clicked, this, &SequenceField::OnSubmitTypeOfSequenceInput);
    grid->addWidget(submitInputTypeOfSequenceButton, 1, 2);

    auto lLabel = new QLabel("Enter lmin and lmax(1,2):");
    lLabel->setStyleSheet("QLabel{color: white;}");
    grid->addWidget(lLabel, 2, 0);

    this->lValues = new QTextEdit();
    this->lValues->setFixedSize(300, 25);
    grid->addWidget(this->lValues, 2, 1);

    auto submitInputLValues = new QPushButton("Submit", this);
    SequenceField::connect(submitInputLValues, &QPushButton::clicked, this, &SequenceField::OnSubmitLValues);
    grid->addWidget(submitInputLValues, 2, 2);

    auto sequenceLabel = new QLabel("Enter some text sequence:");
    sequenceLabel->setStyleSheet("QLabel{color: white;}");
    grid->addWidget(sequenceLabel, 3, 0);

    this->sequence = new QTextEdit();
    this->sequence->setFixedSize(300, 25);
    grid->addWidget(this->sequence, 3, 1);

    auto submitInputSequenceButton = new QPushButton("Submit", this);
    SequenceField::connect(submitInputSequenceButton, &QPushButton::clicked, this, &SequenceField::OnSubmitInputSequence);
    grid->addWidget(submitInputSequenceButton, 3, 2);


    this->message = new QLabel("");
    this->message->setStyleSheet("QLabel{color: white;}");
    grid->addWidget(this->message, 4, 0, 1, 3);

    this->subMessage = new QLabel("");
    this->subMessage->setStyleSheet("QLabel{color: white;}");
    this->subMessage->setWordWrap(true);
    grid->addWidget(this->subMessage, 5, 0, 1, 3);

    auto quitButton = new QPushButton("Quit", this);
    SequenceField::connect(quitButton, &QPushButton::clicked, this, &SequenceField::OnQuitClick);
    grid->addWidget(quitButton, 6, 0);

    this->setLayout(grid);
}

void SequenceField::OnQuitClick() {
    this->close();
    this->mainWindow->show();
}

void SequenceField::OnSubmitTypeOfDictionaryInput() {
    this->baseTypeOfDictionary = !this->typeOfDictionary->toPlainText().toStdString().empty() ? this->typeOfDictionary->toPlainText().toStdString() : "AVLTreeDictionary";
    this->typeOfDictionary->setUpdatesEnabled(false);
}

void SequenceField::OnSubmitTypeOfSequenceInput() {
    this->baseTypeOfSequence = !this->typeOfSequence->toPlainText().toStdString().empty() ? this->typeOfSequence->toPlainText().toStdString() : "ArraySequence";
    this->typeOfSequence->setUpdatesEnabled(false);
}

void SequenceField::OnSubmitInputSequence() {
    QString s = this->sequence->toPlainText();
    if (this->baseTypeOfDictionary == "BTreeDictionary") {
        this->dict = new dictionary::BTreeDictionary<QString, QString>(2, this->baseTypeOfSequence, QString(), QString());
    } else if (this->baseTypeOfDictionary == "AVLTreeDictionary") {
        this->dict = new dictionary::AVLTreeDictionary<QString, QString>(this->baseTypeOfSequence, QString(), QString());
    } else {
        this->subMessage->setText("Invalid type of dictionary");
        this->subMessage->setStyleSheet("QLabel{color: red;}");
        sleep(5);
        this->close();
    }
    try {
        for (int i = 0; i < s.length(); ++i) {
            for (int j = this->lmin; j <= this->lmax; ++j) {
                QString ss;
                if (i + j >= s.length()) {
                    ss = s.mid(i, s.length() - i);
                    if (ss.length() < this->lmin) {
                        ss = "";
                    }
                } else if (j == 0) {
                    ss = "";
                } else {
                    ss = s.mid(i, j);
                }
                if (!ss.isEmpty()) {
                    if (!this->dict->contains(ss)) {
                        auto *prefixes = new QString();
                        this->dict->insert(ss, *prefixes);
                    }
                    if (!this->dict->get(ss).getValue().contains(QString::number(i))){
                        this->dict->get(ss).getValue() += QString::number(i) + " ";
                    }
                }
            }
        }
        QString output;
        for (auto key: this->dict->keys()) {
            output += key.getValue() + ":\t" + this->dict->get(key.getValue()).getValue() + '\n';
        }
        this->message->setText(output);
    } catch (std::exception &exception){
        this->subMessage->setText(exception.what());
        this->subMessage->setStyleSheet("QLabel{color: red;}");
    }
}

void SequenceField::OnSubmitLValues() {
    this->lmin = this->lValues->toPlainText().split(",")[0].toInt();
    this->lmax = this->lValues->toPlainText().split(",")[1].toInt();
    this->lValues->setUpdatesEnabled(false);
}
