#include "VectorField.hpp"

void VectorField::OnQuitClick() {
    this->close();
    this->mainWindow->show();
}

VectorField::VectorField(QWidget *mainWindow) {
    this->mainWindow = mainWindow;
    auto *grid = new QGridLayout(this);


    auto typeOfDictionaryLabel = new QLabel("Enter base type of dictionary\n(BTreeDictionary/AVLTreeDictionary):");
    typeOfDictionaryLabel->setStyleSheet("QLabel{color: white;}");
    grid->addWidget(typeOfDictionaryLabel, 0, 0);

    this->typeOfDictionary = new QTextEdit();
    this->typeOfDictionary->setFixedSize(300, 25);
    grid->addWidget(this->typeOfDictionary, 0, 1);

    auto submitInputTypeOfDictionaryButton = new QPushButton("Submit", this);
    VectorField::connect(submitInputTypeOfDictionaryButton, &QPushButton::clicked, this, &VectorField::OnSubmitTypeOfDictionaryInput);
    grid->addWidget(submitInputTypeOfDictionaryButton, 0, 2);

    auto typeOfSequenceLabel = new QLabel("Enter base type of sequence\n(ArraySequence/LinkedListSequence):");
    typeOfSequenceLabel->setStyleSheet("QLabel{color: white;}");
    grid->addWidget(typeOfSequenceLabel, 1, 0);

    this->typeOfSequence = new QTextEdit();
    this->typeOfSequence->setFixedSize(300, 25);
    grid->addWidget(this->typeOfSequence, 1, 1);

    auto submitInputTypeOfSequenceButton = new QPushButton("Submit", this);
    VectorField::connect(submitInputTypeOfSequenceButton, &QPushButton::clicked, this, &VectorField::OnSubmitTypeOfSequenceInput);
    grid->addWidget(submitInputTypeOfSequenceButton, 1, 2);

    auto vectorInputLabel = new QLabel("Enter vector(1,2,0):");
    vectorInputLabel->setStyleSheet("QLabel{color: white;}");
    grid->addWidget(vectorInputLabel, 2, 0);

    this->vectorInput = new QTextEdit();
    this->vectorInput->setFixedSize(300, 50);
    grid->addWidget(this->vectorInput, 2, 1);

    auto submitInputVectorButton = new QPushButton("Submit", this);
    VectorField::connect(submitInputVectorButton, &QPushButton::clicked, this, &VectorField::OnSubmitVectorInput);
    grid->addWidget(submitInputVectorButton, 2, 2);

    auto commandInputLabel = new QLabel("Enter some command:");
    commandInputLabel->setStyleSheet("QLabel{color: white;}");
    grid->addWidget(commandInputLabel, 3, 0);

    this->command = new QTextEdit();
    this->command->setFixedSize(300, 25);
    grid->addWidget(this->command, 3, 1);

    auto submitCommandButton = new QPushButton("Submit", this);
    VectorField::connect(submitCommandButton, &QPushButton::clicked, this, &VectorField::OnSubmitCommandInput);
    grid->addWidget(submitCommandButton, 3, 2);

    this->vectorOutputLabel = new QLabel("Vector: ");
    this->vectorOutputLabel->setStyleSheet("QLabel{color: white;}");
    grid->addWidget(this->vectorOutputLabel, 4, 0, 1, 3);

    this->subMessage = new QLabel("");
    this->subMessage->setStyleSheet("QLabel{color: white;}");
    this->subMessage->setWordWrap(true);
    grid->addWidget(this->subMessage, 5, 0, 1, 3);

    auto quitButton = new QPushButton("Quit", this);
    VectorField::connect(quitButton, &QPushButton::clicked, this, &VectorField::OnQuitClick);
    grid->addWidget(quitButton, 6, 0);

    this->setLayout(grid);
}

void VectorField::OnSubmitVectorInput() {
    this->vector = new vector::SparseVector<int>(this->baseTypeOfDictionary, this->baseTypeOfSequence, 0);
    QString vectorText = this->vectorInput->toPlainText();
    QStringList splitText =  vectorText.split(",");
    for (auto partOfText: splitText) {
        this->vector->append(partOfText.toInt());
    }
    this->updateVectorOutputLabel();
}

void VectorField::OnSubmitTypeOfDictionaryInput() {
    this->baseTypeOfDictionary = !this->typeOfDictionary->toPlainText().toStdString().empty() ? this->typeOfDictionary->toPlainText().toStdString() : "BTreeDictionary";
    this->typeOfDictionary->setUpdatesEnabled(false);
}

void VectorField::OnSubmitTypeOfSequenceInput() {
    this->baseTypeOfSequence = this->typeOfSequence->toPlainText().toStdString() != "" ? this->typeOfSequence->toPlainText().toStdString() : "ArraySequence";
    this->typeOfSequence->setUpdatesEnabled(false);
}

void VectorField::OnSubmitCommandInput() {
    try {
        if (this->command->toPlainText().contains(" ")) {
            QString commandType = this->command->toPlainText().split(" ")[0];
            QString commandText = this->command->toPlainText().split(" ")[1];
            if (commandType == "INSERT") {
                this->vector->insert(commandText.split(",")[0].toInt(), commandText.split(",")[1].toInt());
            } else if (commandType == "APPEND") {
                this->vector->append(commandText.toInt());
            } else if (commandType == "POP") {
                this->vector->pop(commandText.toInt());
            } else if (commandType == "PREPEND") {
                this->vector->prepend(commandText.toInt());
            } else if (commandType == "SWAP") {
                this->vector->swap(commandText.split(",")[0].toInt(), commandText.split(",")[1].toInt());
            } else if (commandType == "GET") {
                this->subMessage->setStyleSheet("QLabel{color: white;}");
                this->subMessage->setText(QString::fromStdString(std::to_string(this->vector->getElement(commandText.toInt()))));
            } else if (commandType == "LENGTH"){
                this->subMessage->setStyleSheet("QLabel{color: white;}");
                this->subMessage->setText(QString::fromStdString(std::to_string(this->vector->length())));
            } else {
                this->subMessage->setText("Invalid command");
                this->subMessage->setStyleSheet("QLabel{color: red;}");
            }
        } else{
            this->subMessage->setText("Invalid command");
            this->subMessage->setStyleSheet("QLabel{color: red;}");
        }
    } catch (exceptions::SparseVectorException &exception) {
        this->subMessage->setText(exception.what());
        this->subMessage->setStyleSheet("QLabel{color: red;}");
    }
    this->updateVectorOutputLabel();
}

void VectorField::updateVectorOutputLabel() {
    std::string baseVectorOutputLabel = "Vector: ";
    this->vectorOutputLabel->setText(QString::fromStdString(baseVectorOutputLabel + this->vector->representation()));
}
