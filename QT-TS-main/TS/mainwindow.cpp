#include "mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent) {
    addVertexButton = new QPushButton("Add Vertex");
    removeVertexButton = new QPushButton("Remove Vertex");
    addEdgeButton = new QPushButton("Add Edge");
    removeEdgeButton = new QPushButton("Remove Edge");

    layout = new QVBoxLayout;
    layout->addWidget(addVertexButton);
    layout->addWidget(removeVertexButton);
    layout->addWidget(addEdgeButton);
    layout->addWidget(removeEdgeButton);

    centralWidget = new QWidget;
    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);

    // Подключение сигналов к соответствующим слотам
    connect(addVertexButton, &QPushButton::clicked, this, &MainWindow::addVertex);
    connect(removeVertexButton, &QPushButton::clicked, this, &MainWindow::removeVertex);
    connect(addEdgeButton, &QPushButton::clicked, this, &MainWindow::addEdge);
    connect(removeEdgeButton, &QPushButton::clicked, this, &MainWindow::removeEdge);
}

MainWindow::~MainWindow() {
    // Очистка ресурсов, если требуется
}

void MainWindow::addVertex() {
    // Реализация логики добавления вершины
}

void MainWindow::removeVertex() {
    // Реализация логики удаления вершины
}

void MainWindow::addEdge() {
    // Реализация логики добавления ребра
}

void MainWindow::removeEdge() {
    // Реализация логики удаления ребра
}
