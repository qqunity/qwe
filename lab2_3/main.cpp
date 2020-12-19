#include <QApplication>
#include "MainWindow.hpp"
#include "GraphInteractionWindow.hpp"
#include "GraphVisualizationWindow.hpp"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow mainWindow;
    GraphInteractionWindow graphInteractionWindow(&mainWindow);
    GraphVisualizationWindow graphVisualizationWindowForGraph;
    GraphVisualizationWindow graphVisualizationWindowForSkeletonTree;
    GraphVisualizationWindow graphVisualizationWindowForNodesPath;

    graphInteractionWindow.setGraphVisualizationWindowForGraph(&graphVisualizationWindowForGraph);
    graphInteractionWindow.setGraphVisualizationWindowForSkeletonTree(&graphVisualizationWindowForSkeletonTree);
    graphInteractionWindow.setGraphVisualizationWindowForNodesPath(&graphVisualizationWindowForNodesPath);
    mainWindow.setGraphInteractionWindow(&graphInteractionWindow);

    mainWindow.show();
    return QApplication::exec();
}
