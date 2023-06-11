#include <QApplication>
#include <QMainWindow>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QInputDialog>
#include <QPainter>
#include <QPaintEvent>
#include <QPoint>
#include <QStringList>
#include <vector>
#include <cmath>
#include <iostream>
#include <QDebug>
struct Branch {
    int currentVertex;
    std::vector<int> path;
    int distance;

    Branch(int vertex, const std::vector<int>& p, int dist)
        : currentVertex(vertex), path(p), distance(dist) {}
};

std::pair<int, std::vector<int>> solveTravelingSalesmanProblem(const std::vector<std::vector<int>>& graph) {
    int n = graph.size();
    std::vector<int> vertexIndices(n);
    for (int i = 0; i < n; ++i) {
        vertexIndices[i] = i;
    }
    int minDistance = INT_MAX;
    std::vector<int> minPath;

    std::vector<Branch> branches;
    branches.emplace_back(vertexIndices[0], std::vector<int>{vertexIndices[0]}, 0);

    while (!branches.empty()) {

        auto currentState = branches.back();
        branches.pop_back();

        if (currentState.path.size() == n) {
            int finalDistance = currentState.distance + graph[currentState.currentVertex][vertexIndices[0]];
            if (finalDistance < minDistance) {
                minDistance = finalDistance;
                minPath = currentState.path;
                minPath.push_back(vertexIndices[0]);
            }
        } else {
            for (int i = 1; i < n; ++i) {
                int nextVertex = vertexIndices[i];
                if (std::find(currentState.path.begin(), currentState.path.end(), nextVertex) == currentState.path.end()) {
                    int distanceToNext = graph[currentState.currentVertex][nextVertex];
                    if (distanceToNext != 0 && currentState.distance + distanceToNext < minDistance) {
                        std::vector<int> newPath = currentState.path;
                        newPath.push_back(nextVertex);

                        branches.emplace_back(nextVertex, newPath, currentState.distance + distanceToNext);
                    }
                }
            }
        }
    }

    return std::make_pair(minDistance, minPath);
}

class GraphWidget : public QWidget {


public:
    GraphWidget(QWidget* parent = nullptr) : QWidget(parent) {
        addVertexButton = new QPushButton("Добавить вершину", this);
        connect(addVertexButton, &QPushButton::clicked, this, &GraphWidget::addVertex);

        removeVertexButton = new QPushButton("Удалить вершину", this);
        connect(removeVertexButton, &QPushButton::clicked, this, &GraphWidget::removeVertex);

        addEdgeButton = new QPushButton("Добавить ребро", this);
        connect(addEdgeButton, &QPushButton::clicked, this, &GraphWidget::addEdge);

        removeEdgeButton = new QPushButton("Удалить ребро", this);
        connect(removeEdgeButton, &QPushButton::clicked, this, &GraphWidget::removeEdge);
    }

    void addVertex() {
        int n = graph.size();
        for (int i = 0; i < n; ++i) {
            graph[i].push_back(0);
        }
        std::vector<int> newRow(n + 1, 0);
        graph.push_back(newRow);
        update();
    }

    void removeVertex() {
            bool ok;
            int vertexIndex = QInputDialog::getInt(this, tr("Удалить вершину"), tr("Введите индекс вершины:"), 0, 0, INT_MAX, 1, &ok);
            if (ok && vertexIndex >= 0 && vertexIndex <= graph.size()) {
                graph.erase(graph.begin() + vertexIndex);
                for (auto& row : graph) {
                    row.erase(row.begin() + vertexIndex);
                }
                update();
            }
        }

    void addEdge() {
           bool ok;
           int vertexIndex1 = QInputDialog::getInt(this, tr("Добавить ребро"), tr("Введите индекс первой вершины:"), 0, 0, INT_MAX, 1, &ok);
           if (ok && vertexIndex1 >= 0 && vertexIndex1 <= graph.size()) {
               int vertexIndex2 = QInputDialog::getInt(this, tr("Добавить ребро"), tr("Введите индекс второй вершины:"), 0, 0, INT_MAX, 1, &ok);
               if (ok && vertexIndex2 >= 0 && vertexIndex2 <= graph.size()) {
                   int weight = QInputDialog::getInt(this, tr("Добавить ребро"), tr("Введите вес ребра:"), 0, 0, INT_MAX, 1, &ok);
                   if (ok) {
                       graph[vertexIndex1][vertexIndex2] = weight;
                       graph[vertexIndex2][vertexIndex1] = weight;
                       update();
                   }
               }
           }
       }

    void removeEdge() {
            bool ok;
            int vertexIndex1 = QInputDialog::getInt(this, tr("Удалить ребро"), tr("Введите индекс первой вершины:"), 0, 0, INT_MAX, 1, &ok);
            if (ok && vertexIndex1 >= 0 && vertexIndex1 < graph.size()) {
                int vertexIndex2 = QInputDialog::getInt(this, tr("Удалить ребро"), tr("Введите индекс второй вершины:"), 0, 0, INT_MAX, 1, &ok);
                if (ok && vertexIndex2 >= 0 && vertexIndex2 < graph.size()) {
                    graph[vertexIndex1][vertexIndex2] = 0;
                    graph[vertexIndex2][vertexIndex1] = 0;
                    update();
                }
            }
        }

    void update() {
            auto pair = solveTravelingSalesmanProblem(graph);
            distance = pair.first;
            branches = pair.second;
            QWidget::update();
        }
    void paintEvent(QPaintEvent* event) override {
       qDebug()<<23;
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);
        painter.fillRect(rect(), Qt::white);

        int n = graph.size();
        if (n > 0) {
            double angle = 2 * M_PI / n;
            int centerX = width() / 2;
            int centerY = height() / 2;
            int radius = std::min(centerX, centerY) - 20;

            std::vector<QPoint> vertices;
            for (int i = 0; i < n; ++i) {
                int x = centerX + radius * std::cos(i * angle);
                int y = centerY + radius * std::sin(i * angle);
                vertices.push_back(QPoint(x, y));
            }

            for (int i = 0; i < n; ++i) {
                for (int j = i; j < n; ++j) {
                    int weight = graph[i][j];
                    if (weight > 0) {
                        int x1 = vertices[i].x();
                        int y1 = vertices[i].y();
                        int x2 = vertices[j].x();
                        int y2 = vertices[j].y();
                        bool f= false;

                        for(int k=0; k<branches.size()-1; k++){
                            f=(branches[k]== i&&branches[k+1]==j)|| (branches[k]== j&&branches[k+1]==i);
                            if(f)break;
                        }

                        if(f) {

                            painter.setPen(Qt::red);
                            painter.drawLine(QPoint(x1, y1), QPoint(x2, y2));
                        }
                        else{

                        painter.setPen(Qt::black);
                        painter.drawLine(QPoint(x1, y1), QPoint(x2, y2));}
                        painter.setPen(Qt::red);
                        painter.drawText(QRect((x1 + x2) / 2 - 10, (y1 + y2) / 2 - 10, 20, 20), Qt::AlignCenter,
                                         QString::number(weight));
                        painter.setPen(Qt::green);
 painter.drawText(QRectF(0, 0, 300, 30), Qt::AlignLeft, "Минимальная дистанция: " + QString::number(distance));

 QString pathText = "Кратчайший путь: ";
      for (int i = 0; i < int(branches.size()); ++i) {
          pathText += QString::number(branches[i]);
          if (i != int(branches.size()) - 1) {
              pathText += " -> ";
          }
      }
      painter.drawText(QRectF(0, 20, 300, 30), Qt::AlignLeft, pathText);
                    }
                }
            }

            for (int i = 0; i < n; ++i) {
                painter.setPen(Qt::black);
                painter.setBrush(Qt::white);
                painter.drawEllipse(vertices[i], 20, 20);
                painter.drawText(QRect(vertices[i].x() - 10, vertices[i].y() - 10, 20, 20), Qt::AlignCenter,
                                 QString::number(i));
            }
        }
    }

public:
    std::vector <int> branches;
    int distance;
    std::vector<std::vector<int>> graph;
    QPushButton* addVertexButton;
    QPushButton* removeVertexButton;
    QPushButton* addEdgeButton;
    QPushButton* removeEdgeButton;
};

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    GraphWidget widget;
    QHBoxLayout* layout = new QHBoxLayout;
    layout->addWidget(widget.addVertexButton);
    layout->addWidget(widget.removeVertexButton);
    layout->addWidget(widget.addEdgeButton);
    layout->addWidget(widget.removeEdgeButton);

    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->addLayout(layout);
    mainLayout->addWidget(&widget);

    QMainWindow window;
    QWidget* centralWidget = new QWidget(&window);
    centralWidget->setLayout(mainLayout);
    window.setCentralWidget(centralWidget);
    window.show();

    return app.exec();
}
