#include "GraphInteractionWindow.hpp"
#include "UIGraphInteractionWindow.hpp"

GraphInteractionWindow::GraphInteractionWindow(QWidget *parent) :
        ui(new Ui::GraphInteractionWindow) {
    this->ui->setupUi(this);
    this->mainWindow = parent;
    this->graph = nullptr;
    GraphInteractionWindow::connect(this->ui->quitButton, &QPushButton::clicked, this,
                                    &GraphInteractionWindow::OnQuitClick);
    GraphInteractionWindow::connect(this->ui->submitsSequenceTypeButton, &QPushButton::clicked, this,
                                    &GraphInteractionWindow::OnSubmitSequenceTypeButtonClick);
    GraphInteractionWindow::connect(this->ui->submitDictionaryTypeButton, &QPushButton::clicked, this,
                                    &GraphInteractionWindow::OnSubmitDictionaryTypeButtonClick);
    GraphInteractionWindow::connect(this->ui->submitGraphCommandsButton, &QPushButton::clicked, this,
                                    &GraphInteractionWindow::OnSubmitGraphCommandsButtonClick);
    GraphInteractionWindow::connect(this->ui->drawGraphButton, &QPushButton::clicked, this,
                                    &GraphInteractionWindow::OnDrawGraphButtonClick);
    GraphInteractionWindow::connect(this->ui->drawSkeletonTreeButton, &QPushButton::clicked, this,
                                    &GraphInteractionWindow::OnDrawSkeletonTreeButtonClick);
    GraphInteractionWindow::connect(this->ui->submitGraphInteractionCommandsButton, &QPushButton::clicked, this,
                                    &GraphInteractionWindow::OnSubmitGraphInteractionCommandButtonClick);
    GraphInteractionWindow::connect(this->ui->getDistanceButton, &QPushButton::clicked, this,
                                    &GraphInteractionWindow::OnSubmitGetDistanceButtonClick);
}

GraphInteractionWindow::~GraphInteractionWindow() {
    delete this->ui;
}

void GraphInteractionWindow::OnQuitClick() {
    this->ui->errorLabel->setText(QString());
    this->close();
    mainWindow->show();
}

void GraphInteractionWindow::OnSubmitSequenceTypeButtonClick() {
    this->ui->errorLabel->setText(QString());
    this->baseTypeOfSequence = this->ui->sequenceTypeFrame->toPlainText().toStdString();
    if (baseTypeOfSequence == "ArraySequence" || this->baseTypeOfSequence == "LinkedListSequence" ||
        this->baseTypeOfSequence.empty()) {
        if (this->baseTypeOfSequence.empty()) {
            this->ui->sequenceTypeFrame->setText(QString("ArraySequence"));
            this->baseTypeOfSequence = "ArraySequence";
        }
        this->ui->sequenceTypeFrame->setUpdatesEnabled(false);
    } else {
        this->ui->errorLabel->setText(QString("Invalid type of sequence!"));
        this->ui->errorLabel->setStyleSheet("color: red");
    }
}

void GraphInteractionWindow::OnSubmitDictionaryTypeButtonClick() {
    this->ui->errorLabel->setText(QString());
    this->baseTypeOfDictionary = this->ui->dictionaryTypeFrame->toPlainText().toStdString();
    if (this->baseTypeOfDictionary == "AVLTreeDictionary" || this->baseTypeOfDictionary == "BTreeDictionary" ||
        this->baseTypeOfDictionary.empty()) {
        if (this->baseTypeOfDictionary.empty()) {
            this->ui->dictionaryTypeFrame->setText(QString("BTreeDictionary"));
            this->baseTypeOfDictionary = "BTreeDictionary";
        }
        this->ui->dictionaryTypeFrame->setUpdatesEnabled(false);
    } else {
        this->ui->errorLabel->setText(QString("Invalid type of dictionary!"));
        this->ui->errorLabel->setStyleSheet("color: red");
    }
}

void GraphInteractionWindow::OnSubmitGraphCommandsButtonClick() {
    this->ui->errorLabel->setText(QString());
    try {
        this->graph = new graph::UndirectedGraph<int, std::string>(this->baseTypeOfDictionary, this->baseTypeOfSequence,
                                                                   0, "null");
        QString commands = this->ui->graphCommandsFrame->toPlainText();
        for (const auto &command: commands.split("\n")) {
            if (command.startsWith(QString("add_vertex"))) {
                QString node = command.split(" ")[1];
                this->graph->addNode(node.toStdString());
            } else if (command.startsWith("add_edge")) {
                QString node1 = command.split(" ")[1];
                QString node2 = command.split(" ")[2];
                QString label = command.split(" ")[3];
                this->graph->addEdge(node1.toStdString(), node2.toStdString(), label.toInt());
            } else {
                this->ui->errorLabel->setText(QString("Invalid type of command!"));
                this->ui->errorLabel->setStyleSheet("color: red");
            }
        }
        this->ui->graphCommandsFrame->setUpdatesEnabled(false);
    } catch (std::exception &exception) {
        this->ui->errorLabel->setText(QString(exception.what()));
        this->ui->errorLabel->setStyleSheet("color: red");
    }
}

void GraphInteractionWindow::OnDrawGraphButtonClick() {
    this->ui->errorLabel->setText(QString());
    if (this->graph != nullptr) {
        this->graphVisualizationWindowForGraph->setGraph(this->graph);
        this->graphVisualizationWindowForGraph->show();
    } else {
        this->ui->errorLabel->setText(QString("Graph is not set!"));
        this->ui->errorLabel->setStyleSheet("color: red");
    }
}

void GraphInteractionWindow::setGraphVisualizationWindowForGraph(GraphVisualizationWindow *graphVisualizationWindow) {
    this->graphVisualizationWindowForGraph = graphVisualizationWindow;
}

void GraphInteractionWindow::OnDrawSkeletonTreeButtonClick() {
    this->ui->errorLabel->setText(QString());
    if (this->graph != nullptr) {
        if (this->graph->isConnected()) {
            auto minSkeletonTree = new graph::UndirectedGraph<int, std::string>(this->baseTypeOfDictionary,
                                                                                this->baseTypeOfSequence, 0, "null");
            dictionary::IDictionary<std::string, bool> *used;
            dictionary::IDictionary<std::string, int> *minWeight;
            dictionary::IDictionary<std::string, std::string> *selWeight;
            sequence::Sequence<std::string> *allNodes;
            if (this->baseTypeOfSequence == "ArraySequence") {
                allNodes = new array::ArraySequence<std::string>();
            } else {
                allNodes = new list::LinkedListSequence<std::string>();
            }
            if (this->baseTypeOfDictionary == "AVLTreeDictionary") {
                used = new dictionary::AVLTreeDictionary<std::string, bool>(this->baseTypeOfSequence, "null", false);
                minWeight = new dictionary::AVLTreeDictionary<std::string, int>(this->baseTypeOfSequence, "null", -1);
                selWeight = new dictionary::AVLTreeDictionary<std::string, std::string>(this->baseTypeOfSequence,
                                                                                        "null", "null");
            } else {
                used = new dictionary::BTreeDictionary<std::string, bool>(2, this->baseTypeOfSequence, "null", false);
                minWeight = new dictionary::BTreeDictionary<std::string, int>(2, this->baseTypeOfSequence, "null", -1);
                selWeight = new dictionary::BTreeDictionary<std::string, std::string>(2, this->baseTypeOfSequence,
                                                                                      "null", "null");
            }
            for (auto graphIt: this->graph->getNodes()) {
                used->insert(graphIt.getValue(), false);
                selWeight->insert(graphIt.getValue(), "null");
                minWeight->insert(graphIt.getValue(), 100000);
                allNodes->append(graphIt.getValue());
            }
            minWeight->get(*this->graph->getNodes().begin()) = 0;
            for (auto graphIt: this->graph->getNodes()) {
                std::string v = "null";
                for (auto nodeIt: sequence::SequenceIterator<std::string>(allNodes)) {
                    if (!used->get(nodeIt.getValue()).getValue() &&
                        (v == "null" || minWeight->get(nodeIt.getValue()).getValue() < minWeight->get(v).getValue())) {
                        v = nodeIt.getValue();
                    }
                }
                used->get(v) = true;
                if (selWeight->get(v).getValue() != "null") {
                    std::string buff = selWeight->get(v).getValue();
                    minSkeletonTree->addNode(v);
                    minSkeletonTree->addNode(buff);
                    minSkeletonTree->addEdge(v, buff, this->graph->getLabel(v, buff));
                }
                for (auto neighbour: this->graph->neighbours(v)) {
                    if (neighbour.getValue().getSecond() < minWeight->get(neighbour.getValue().getFirst()).getValue()) {
                        minWeight->get(neighbour.getValue().getFirst()) = neighbour.getValue().getSecond();
                        selWeight->get(neighbour.getValue().getFirst()) = v;
                    }
                }
            }
            this->graphVisualizationWindowForSkeletonTree->setGraph(minSkeletonTree);
            this->graphVisualizationWindowForSkeletonTree->show();
        } else {
            this->ui->errorLabel->setText(QString("Graph is not connected!"));
            this->ui->errorLabel->setStyleSheet("color: red");
        }
    } else {
        this->ui->errorLabel->setText(QString("Graph is not set!"));
        this->ui->errorLabel->setStyleSheet("color: red");
    }
}

void
GraphInteractionWindow::setGraphVisualizationWindowForSkeletonTree(GraphVisualizationWindow *graphVisualizationWindow) {
    this->graphVisualizationWindowForSkeletonTree = graphVisualizationWindow;
}

void GraphInteractionWindow::OnSubmitGraphInteractionCommandButtonClick() {
    this->ui->errorLabel->setText(QString());
    if (this->graph != nullptr) {
        try {
            QString commands = this->ui->graphInteractionCommandsFrame->toPlainText();
            for (const auto &command: commands.split("\n")) {
                if (command.startsWith(QString("add_vertex"))) {
                    QString node = command.split(" ")[1];
                    this->graph->addNode(node.toStdString());
                } else if (command.startsWith("add_edge")) {
                    QString node1 = command.split(" ")[1];
                    QString node2 = command.split(" ")[2];
                    QString label = command.split(" ")[3];
                    this->graph->addEdge(node1.toStdString(), node2.toStdString(), label.toInt());
                } else if (command.startsWith("delete_vertex")) {
                    QString node = command.split(" ")[1];
                    this->graph->removeNode(node.toStdString());
                } else if (command.startsWith("delete_edge")) {
                    QString node1 = command.split(" ")[1];
                    QString node2 = command.split(" ")[2];
                    this->graph->removeEdge(node1.toStdString(), node2.toStdString());
                } else {
                    this->ui->errorLabel->setText(QString("Invalid type of command!"));
                    this->ui->errorLabel->setStyleSheet("color: red");
                }
            }
            this->graphVisualizationWindowForGraph->update();
            if (this->graphVisualizationWindowForSkeletonTree->getGraph() != nullptr) {
                this->OnDrawSkeletonTreeButtonClick();
            }
        } catch (std::exception &exception) {
            this->ui->errorLabel->setText(QString(exception.what()));
            this->ui->errorLabel->setStyleSheet("color: red");
        }
    } else {
        this->ui->errorLabel->setText(QString("Graph is not set!"));
        this->ui->errorLabel->setStyleSheet("color: red");
    }
}

void GraphInteractionWindow::OnSubmitGetDistanceButtonClick() {
    this->ui->errorLabel->setText(QString());
    QString vertexInfo = this->ui->distanceInfoFrame->toPlainText();
    std::string node1 = vertexInfo.split(",")[0].toStdString();
    std::string node2 = vertexInfo.split(",")[1].toStdString();
    if (this->graph->checkPath(node1, node2)) {
        unsigned int n = this->graph->getNodesQuantity();
        matrix::Matrix<int> W(n, n);
        sequence::Sequence<std::string> *nodeValues;
        if (this->baseTypeOfSequence == "ArraySequence") {
            nodeValues = new array::ArraySequence<std::string>();
        } else {
            nodeValues = new list::LinkedListSequence<std::string>();
        }
        for (auto node: this->graph->getNodes()) {
            nodeValues->append(node.getValue());
        }
        for (unsigned int i = 0; i < n; ++i) {
            for (unsigned int j = 0; j < n; ++j) {
                if (this->graph->isNeighbours(nodeValues->getElement(i), nodeValues->getElement(j))) {
                    W[i][j] = this->graph->getLabel(nodeValues->getElement(i), nodeValues->getElement(j));
                } else {
                    W[i][j] = 100000;
                }
            }
        }
        for (unsigned int k = 0; k < n; ++k) {
            for (unsigned int i = 0; i < n; ++i) {
                for (unsigned int j = 0; j < n; ++j) {
                    W[i][j] = qMin(W[i][j].getValue(), W[i][k].getValue() + W[k][j].getValue());
                }
            }
        }
        auto nodesPath = new graph::UndirectedGraph<int, std::string>(this->baseTypeOfDictionary,
                                                                      this->baseTypeOfSequence, 0, "null");
        nodesPath->addNode(node1);
        nodesPath->addNode(node2);
        nodesPath->addEdge(node1, node2, W[nodeValues->getIndex(node1)][nodeValues->getIndex(node2)]);
        this->graphVisualizationWindowForNodesPath->setGraph(nodesPath);
        this->graphVisualizationWindowForNodesPath->show();
    } else {
        this->ui->errorLabel->setText(QString("The path between nodes does not exist!"));
        this->ui->errorLabel->setStyleSheet("color: red");
    }
}


void
GraphInteractionWindow::setGraphVisualizationWindowForNodesPath(GraphVisualizationWindow *graphVisualizationWindow) {
    this->graphVisualizationWindowForNodesPath = graphVisualizationWindow;
}
