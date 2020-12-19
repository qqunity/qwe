#ifndef LAB2_3_GRAPHINTERACTIONWINDOW_HPP
#define LAB2_3_GRAPHINTERACTIONWINDOW_HPP

#include <QWidget>
#include "Matrix.hpp"
#include "GraphVisualizationWindow.hpp"
#include "UndirectedGraph.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class GraphInteractionWindow; }
QT_END_NAMESPACE

class GraphInteractionWindow : public QWidget {
Q_OBJECT

public:
    explicit GraphInteractionWindow(QWidget *parent);

    void setGraphVisualizationWindowForGraph(GraphVisualizationWindow *graphVisualizationWindow);

    void setGraphVisualizationWindowForSkeletonTree(GraphVisualizationWindow *graphVisualizationWindow);

    void setGraphVisualizationWindowForNodesPath(GraphVisualizationWindow *graphVisualizationWindow);

    ~GraphInteractionWindow() override;

private slots:
    void OnQuitClick();

    void OnSubmitSequenceTypeButtonClick();

    void OnSubmitDictionaryTypeButtonClick();

    void OnSubmitGraphCommandsButtonClick();

    void OnDrawGraphButtonClick();

    void OnDrawSkeletonTreeButtonClick();

    void OnSubmitGraphInteractionCommandButtonClick();

    void OnSubmitGetDistanceButtonClick();

private:
    std::string baseTypeOfSequence;
    std::string baseTypeOfDictionary;
    graph::UndirectedGraph<int, std::string> *graph{};
    QWidget *mainWindow;
    GraphVisualizationWindow *graphVisualizationWindowForGraph{};
    GraphVisualizationWindow *graphVisualizationWindowForSkeletonTree{};
    GraphVisualizationWindow *graphVisualizationWindowForNodesPath{};
    Ui::GraphInteractionWindow *ui;
};

#endif
