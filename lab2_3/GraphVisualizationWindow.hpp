#ifndef LAB2_3_GRAPHVISUALIZATIONWINDOW_HPP
#define LAB2_3_GRAPHVISUALIZATIONWINDOW_HPP

#include <QWidget>
#include <QLabel>
#include <QPainter>
#include <QPaintEvent>
#include <QPoint>
#include <QtMath>
#include "UndirectedGraph.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class GraphVisualizationWindow; }
QT_END_NAMESPACE

class GraphVisualizationWindow : public QWidget {
Q_OBJECT


private:
    std::pair<int, int> getNodeCoordinates(float phi);

public:
    explicit GraphVisualizationWindow(QWidget *parent = nullptr, graph::UndirectedGraph<int, std::string> *graph = nullptr);

    void setGraph(graph::UndirectedGraph<int, std::string> *graph);

    graph::UndirectedGraph<int, std::string> *getGraph();

    QLabel *getInfoLabel();

    ~GraphVisualizationWindow() override;

private slots:
    void OnQuitClick();

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    Ui::GraphVisualizationWindow *ui;
    graph::UndirectedGraph<int, std::string> *graph;
    std::map<std::string, std::pair<int, int>> nodes;
};

#endif
