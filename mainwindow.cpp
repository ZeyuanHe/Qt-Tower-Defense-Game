#include "mainwindow.h"
#include "gamescene.h"
#include <QPushButton>
#include <QVBoxLayout>
#include "globals.h"
#include <QLabel>
#include <QDebug>

// 静态成员变量的初始化
QLabel *MainWindow::goldLabel = nullptr;  // 初始化为 nullptr

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    int width = 2000;
    int height = 1000;
    scene = new GameScene(width, height, this);  // 将当前 MainWindow 传给 GameScene
    view = new QGraphicsView(scene);

    setFixedSize(width, height);  // 固定窗口大小
    view->setFixedSize(width, height);

    // 初始化静态 QLabel
    goldLabel = new QLabel(this); // 初始化goldLabel
    goldLabel->setGeometry(20, 20, 200, 50);  // 设置位置和大小
    goldLabel->setAlignment(Qt::AlignLeft);  // 设置文本左对齐
    goldLabel->setStyleSheet("color: white; font-size: 30px;");  // 设置字体和颜色样式

    // 创建开始游戏按钮
    QPushButton *startButton = new QPushButton("开始游戏", this);
    connect(startButton, &QPushButton::clicked, scene, &GameScene::startGame);

    // 设置布局
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(view);
    layout->addWidget(startButton);

    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);
    updateGoldDisplay();
}

MainWindow::~MainWindow() {}

// 静态成员函数用于更新金币显示
void MainWindow::updateGoldDisplay() {
    if (goldLabel) {
        goldLabel->setText("Gold: " + QString::number(globalMoney));
        goldLabel->raise();
        qDebug() << globalMoney;
    }
}
