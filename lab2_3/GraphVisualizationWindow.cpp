#define PI 3.14159265358979323846f

#include "GraphVisualizationWindow.hpp"
#include "UIGraphVisualizationWindow.hpp"


GraphVisualizationWindow::GraphVisualizationWindow(QWidget *parent, graph::UndirectedGraph<int, std::string> *graph) :
        ui(new Ui::GraphVisualizationWindow) {
    this->ui->setupUi(this);
    this->graph = nullptr;
    this->setGraph(graph);
    GraphVisualizationWindow::connect(this->ui->quitButton, &QPushButton::clicked, this,
                                      &GraphVisualizationWindow::OnQuitClick);
}

GraphVisualizationWindow::~GraphVisualizationWindow() {
    delete this->ui;
}

void GraphVisualizationWindow::OnQuitClick() {
    this->close();
}

std::pair<int, int> GraphVisualizationWindow::getNodeCoordinates(float phi) {
    int x = qAbs(static_cast<int>(std::floor(200 * std::cos(phi))) - this->width() / 2);
    int y = qAbs(static_cast<int>(std::floor(200 * std::sin(phi))) - this->height() / 2);
    return std::make_pair(x, y);
}

void GraphVisualizationWindow::setGraph(graph::UndirectedGraph<int, std::string> *graph) {
    this->graph = graph;
    this->update();
}

graph::UndirectedGraph<int, std::string> *GraphVisualizationWindow::getGraph() {
    return this->graph;
}

void GraphVisualizationWindow::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
    if (this->getGraph() != nullptr) {
        QPainter painter(this);
        unsigned int nodesQuantity = this->graph->getNodesQuantity();
        float step = (2.0f * PI) / static_cast<float>(nodesQuantity);
        auto someNodePtr = this->graph->getNodes().begin();
        unsigned int i = 0;
        if(!this->nodes.empty()) {
            this->nodes.clear();
        }
        for (float phi = 0; phi <= 2 * PI && i < nodesQuantity; phi += step) {
            int posX = this->getNodeCoordinates(phi).first;
            int posY = this->getNodeCoordinates(phi).second;
            painter.setPen(Qt::white);
            QFont font;
            font.setBold(true);
            font.setPixelSize(20);
            painter.setFont(font);
            painter.drawText(posX, posY, QString::fromStdString(*someNodePtr));
            this->nodes[*someNodePtr] = std::make_pair(posX, posY);
            ++someNodePtr;
            ++i;
        }
        std::map<std::pair<std::string, std::string>, int> edges = this->graph->getEdges();
        for (auto &edge : edges) {
            QPen pen;
            QPoint pos1 = QPoint(this->nodes[edge.first.first].first, this->nodes[edge.first.first].second);
            pos1 += QPoint(10, 35);
            QPoint pos2 = QPoint(this->nodes[edge.first.second].first, this->nodes[edge.first.second].second);
            pos2 += QPoint(10, 35);
            pen.setColor(Qt::red);
            pen.setWidth(3);
            painter.setPen(pen);
            painter.drawLine(pos1, pos2);
            pen.setColor(Qt::white);
            pen.setWidth(1);
            QFont font;
            font.setBold(false);
            font.setPixelSize(15);
            painter.setPen(pen);
            painter.setFont(font);
            painter.drawText(QPoint((pos1.x() + pos2.x()) / 2, (pos1.y() + pos2.y()) / 2),
                             QString::number(edge.second));
        }
        someNodePtr = this->graph->getNodes().begin();
        for (unsigned int i = 0; i < this->graph->getNodesQuantity(); ++i) {
            QPoint pos = QPoint(this->nodes[*someNodePtr].first, this->nodes[*someNodePtr].second);
            pos += QPoint(10, 35);
            QPen pen;
            QBrush brush(Qt::blue);
            pen.setColor(Qt::white);
            pen.setWidth(1);
            painter.setPen(pen);
            painter.setBrush(brush);
            painter.drawEllipse(pos, 12, 12);
            ++someNodePtr;
        }
        painter.end();
    }
}

QLabel *GraphVisualizationWindow::getInfoLabel() {
    return this->ui->infoLabel;
}
