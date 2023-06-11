#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#ifndef GRAPHWIDGET_H
#define GRAPHWIDGET_H

#include <QWidget>
#include <QPushButton>

class GraphWidget : public QWidget {
    Q_OBJECT

public:
    GraphWidget(QWidget* parent = nullptr);

    void addVertex();
    void removeVertex();
    void addEdge();
    void removeEdge();

protected:
    void paintEvent(QPaintEvent* event) override;

private:
    std::vector<std::vector<int>> graph;
    QPushButton* addVertexButton;
    QPushButton* removeVertexButton;
    QPushButton* addEdgeButton;
    QPushButton* removeEdgeButton;
};

#endif // GRAPHWIDGET_H
class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private:
    QPushButton* addVertexButton;
    QPushButton* removeVertexButton;
    QPushButton* addEdgeButton;
    QPushButton* removeEdgeButton;
    QVBoxLayout* layout;
    QWidget* centralWidget;

private slots:
    void addVertex();
    void removeVertex();
    void addEdge();
    void removeEdge();
};

#endif // MAINWINDOW_H
