#include <QtWidgets/QGridLayout>
#include <QtGui/QPainter>
#include <QKeyEvent>
#include <unistd.h>
#include "GameField.hpp"

GameFiled::GameFiled(QWidget *parent, unsigned int gridSize, char startSymbol) : QWidget(parent) {
    this->filedButtons.setShape(std::make_pair(gridSize, gridSize));
    this->gridSize = gridSize;
    this->inGame = true;
    this->startSymbol = startSymbol;
    this->currentSymbol = startSymbol;
    this->cntMoves = 0;
    this->isQuitButtonAppeared = false;
    this->isForcedExit = true;
    this->ai = new Minimax(this->getNextSymbol(startSymbol), gridSize);
    for (unsigned int i = 0; i < this->gridSize; ++i) {
        for (unsigned int j = 0; j < this->gridSize; ++j) {
            this->filedButtons[i][j] = new QPushButton(QString(this->symbols.blank), this);
            this->filedButtons[i][j].getValue()->setFixedSize(100, 100);
            QFont font = this->filedButtons[i][j].getValue()->font();
            font.setPointSize(40);
            this->filedButtons[i][j].getValue()->setFont(font);
            this->filedButtons[i][j].getValue()->setStyleSheet("QPushButton{color: white; background: transparent;}");
        }
    }
    this->gameMessage = new QLabel("The game started");
    this->errorMessage = new QLabel("Error: null");
    this->gameMessage->setStyleSheet("QLabel{color: white;}");
    this->errorMessage->setStyleSheet("QLabel{color: white;}");
    this->gameMessage->setWordWrap(true);
    this->errorMessage->setWordWrap(true);
    this->gameMessage->setFixedSize(100, 50);
    this->errorMessage->setFixedSize(100, 50);
    auto *gameGrid = new QGridLayout(this);
    for (unsigned int i = 0; i < this->gridSize; ++i) {
        for (unsigned int j = 0; j < this->gridSize; ++j) {
            gameGrid->addWidget(this->filedButtons[i][j], (int) i, (int) j);
        }
    }
    gameGrid->addWidget(this->gameMessage, (int) this->gridSize, 0, (int) this->gridSize, (int) this->gridSize,
                        Qt::AlignmentFlag::AlignLeft);
    gameGrid->addWidget(this->errorMessage, (int) this->gridSize, 1, (int) this->gridSize, (int) this->gridSize,
                        Qt::AlignmentFlag::AlignRight);

    this->setLayout(gameGrid);
    for (unsigned int i = 0; i < this->gridSize; ++i) {
        for (unsigned int j = 0; j < this->gridSize; ++j) {
            GameFiled::connect(this->filedButtons[i][j].getValue(), &QPushButton::clicked, this, &GameFiled::OnClick);
        }
    }
}

void GameFiled::OnClick() {
    auto button = qobject_cast<QPushButton *>(sender());
    if (this->errorMessage->text() == "Error: This cell is already occupied") {
        this->errorMessage->setText("Error: null");
    }
    if (button->text() == QString(this->symbols.blank)) {
        button->setText(QString(this->currentSymbol));
        this->currentSymbol = this->getNextSymbol(this->currentSymbol);
        if (this->currentSymbol == this->startSymbol) {
            this->gameMessage->setText("The move of the first player");
        } else {
            this->gameMessage->setText("The move of the second player");
        }
        ++this->cntMoves;
        if (this->currentSymbol == this->startSymbol) {
            this->gameMessage->setText("The move of the first player");
        } else {
            this->gameMessage->setText("The move of the second player");
        }
        this->makeMove();
    } else {
        this->errorMessage->setText("Error: This cell is already occupied");
    }
    if (this->inGame) {
        this->repaint();
    }
}

void GameFiled::paintEvent(QPaintEvent *paintEvent) {
    if (this->inGame && this->checkWin()) {
        QPainter painter(this);
        this->gameOver(painter,
                       this->currentSymbol == this->symbols.x ? this->gameOutcome.winX : this->gameOutcome.winO);
    } else if (this->inGame && this->checkDraw()) {
        QPainter painter(this);
        this->gameOver(painter, this->gameOutcome.draw);
    }

}

bool GameFiled::checkWin() {
    if (this->inGame) {
        for (unsigned int i = 0; i < this->gridSize; ++i) {
            bool isWin = true;
            for (unsigned int j = 1; j < this->gridSize; ++j) {
                if (this->filedButtons[i][j].getValue()->text() != this->filedButtons[i][0].getValue()->text() ||
                    this->filedButtons[i][0].getValue()->text() == QString(
                            this->symbols.blank)) {
                    isWin = false;
                    break;
                }
            }
            if (isWin) {
                this->inGame = false;
                for (unsigned int j = 0; j < this->gridSize; ++j) {
                    this->filedButtons[i][j].getValue()->setStyleSheet(
                            "QPushButton{color: red; background: transparent;}");
                }
                auto *event = new QKeyEvent ( QEvent::KeyPress, Qt::Key_Escape, Qt::NoModifier);
                QCoreApplication::postEvent (this, event);
                this->isForcedExit = false;
                return true;
            }
        }
        for (unsigned int j = 0; j < this->gridSize; ++j) {
            bool isWin = true;
            for (unsigned int i = 1; i < this->gridSize; ++i) {
                if (this->filedButtons[i][j].getValue()->text() != this->filedButtons[0][j].getValue()->text() ||
                    this->filedButtons[0][j].getValue()->text() == QString(this->symbols.blank)) {
                    isWin = false;
                    break;
                }
            }
            if (isWin) {
                this->inGame = false;
                for (unsigned int i = 0; i < this->gridSize; ++i) {
                    this->filedButtons[i][j].getValue()->setStyleSheet(
                            "QPushButton{color: red; background: transparent;}");
                }
                auto *event = new QKeyEvent ( QEvent::KeyPress, Qt::Key_Escape, Qt::NoModifier);
                QCoreApplication::postEvent (this, event);
                this->isForcedExit = false;
                return true;
            }
        }
        bool isWin = true;
        for (unsigned int i = 1; i < this->gridSize; ++i) {
            if (this->filedButtons[i][i].getValue()->text() != this->filedButtons[0][0].getValue()->text() ||
                this->filedButtons[0][0].getValue()->text() == QString(this->symbols.blank)) {
                isWin = false;
                break;
            }
        }
        if (isWin) {
            this->inGame = false;
            for (unsigned int i = 0; i < this->gridSize; ++i) {
                this->filedButtons[i][i].getValue()->setStyleSheet("QPushButton{color: red; background: transparent;}");
            }
            auto *event = new QKeyEvent ( QEvent::KeyPress, Qt::Key_Escape, Qt::NoModifier);
            QCoreApplication::postEvent (this, event);
            this->isForcedExit = false;
            return true;
        }
        isWin = true;
        for (unsigned int i = 1; i < this->gridSize; ++i) {
            if (this->filedButtons[i][this->gridSize - 1 - i].getValue()->text() !=
                this->filedButtons[0][this->gridSize - 1].getValue()->text() ||
                this->filedButtons[0][this->gridSize - 1].getValue()->text() == QString(this->symbols.blank)) {
                isWin = false;
                break;
            }
        }
        if (isWin) {
            this->inGame = false;
            for (unsigned int i = 0; i < this->gridSize; ++i) {
                this->filedButtons[i][this->gridSize - 1 - i].getValue()->setStyleSheet(
                        "QPushButton{color: red; background: transparent;}");
            }
            auto *event = new QKeyEvent ( QEvent::KeyPress, Qt::Key_Escape, Qt::NoModifier);
            QCoreApplication::postEvent (this, event);
            this->isForcedExit = false;
            return true;
        }
    }
    return false;
}

void GameFiled::gameOver(QPainter &painter, unsigned int reason) {
    int h = this->height();
    int w = this->width();
    QColor blackFill = Qt::black;
    blackFill.setAlphaF(0.5);
    painter.setPen(QColor(Qt::black));
    QBrush brush(blackFill);
    QRect rect(0, 0, w, h);
    painter.drawRect(rect);
    painter.fillRect(rect, brush);
    QString message = "Game over";
    QString subMessage;
    if (reason == this->gameOutcome.winX) {
        if (this->startSymbol == this->symbols.x) {
            subMessage = "The first player won";
        } else {
            subMessage = "The second player won";
        }
    } else if (reason == this->gameOutcome.winO) {
        if (this->startSymbol == this->symbols.o) {
            subMessage = "The first player won";
        } else {
            subMessage = "The second player won";
        }
    } else {
        subMessage = "Draw";
    }
    QFont font("Courier", 25, QFont::DemiBold);
    QFontMetrics fm(font);
    int textWidthMessage = fm.width(message);
    int textWidthSubMessage = fm.width(subMessage);

    painter.setPen(QColor(Qt::yellow));
    painter.setFont(font);


    painter.translate(QPoint(w / 2, h / 2));
    painter.drawText(-textWidthMessage / 2, 0, message);
    painter.drawText(-textWidthSubMessage / 2, 25, subMessage);
}

void GameFiled::clearWidgets(QLayout *layout) {
    if (!layout)
        return;
    while (auto item = layout->takeAt(0)) {
        delete item->widget();
        this->clearWidgets(item->layout());
    }
}

char GameFiled::getNextSymbol(char symbol) {
    return symbol == this->symbols.x ? this->symbols.o : this->symbols.x;;
}

bool GameFiled::checkDraw() {
    return this->cntMoves >= this->gridSize * this->gridSize;
}

void GameFiled::finish() {
    if (!this->isQuitButtonAppeared) {
        auto *quitButton = new QPushButton("Quit", this);
        quitButton->setGeometry(50, 40, 75, 30);
        this->layout()->addWidget(quitButton);
        GameFiled::connect(quitButton, &QPushButton::clicked, this, &QApplication::quit);
        this->isQuitButtonAppeared = true;
    }
}

bool GameFiled::isEnded() {
    return this->inGame;
}

void GameFiled::keyPressEvent(QKeyEvent *keyEvent) {
    int key = keyEvent->key();
    if (key == Qt::Key_Escape) {
        this->repaint();
        if (!this->isForcedExit) {
            sleep(5);
        }
        this->finish();
    }
    QWidget::keyPressEvent(keyEvent);
}

matrix::Matrix<char> GameFiled::getCurrentStateOfGameGrid() {
    matrix::Matrix<char> mat(this->gridSize, this->gridSize);
    for (unsigned int i = 0; i < this->gridSize; ++i) {
        for (unsigned int j = 0; j < this->gridSize; ++j) {
            mat[i][j] = (char) this->filedButtons[i][j].getValue()->text().toStdString()[0];
        }
    }
    return mat;
}

void GameFiled::makeMove() {
    int move = this->ai->getBestMove(this->getCurrentStateOfGameGrid());
    this->filedButtons[move / this->gridSize][move % this->gridSize].getValue()->setText(QString(this->currentSymbol));
    this->currentSymbol = this->getNextSymbol(this->currentSymbol);
    if (this->currentSymbol == this->startSymbol) {
        this->gameMessage->setText("The move of the first player");
    } else {
        this->gameMessage->setText("The move of the second player");
    }
    ++this->cntMoves;
    this->repaint();
}
