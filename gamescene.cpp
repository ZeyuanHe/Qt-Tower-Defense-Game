#include "gamescene.h"
#include "enemy.h"
#include "tower.h"
#include <QGraphicsSceneMouseEvent>
#include <QRandomGenerator>
#include <QDebug>
#include "towerbutton.h"
#include "fasttower.h"
#include "poisontower.h"
#include "slowtower.h"
#include "powertower.h"
#include "mainwindow.h"
#include "upgradebutton.h"
#include<QDebug>
#include "globals.h"
GameScene::GameScene(int width, int height,QObject  *parent)
    : QGraphicsScene(parent),rows(6), columns(13) {
    setSceneRect(0, 0, width, height);

    // 设置背景图片
    QPixmap background(":/map_images/map_images/map.jpg");
    setBackgroundBrush(background.scaled(width, height, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));

    cellWidth = 170;
    cellHeight = 160;
    grid.resize(columns);
    for (int i = 0; i < columns; ++i) {
        grid[i].resize(rows);
    }

    createPath();
    drawGrid();

    enemyTimer = new QTimer(this);
    connect(enemyTimer, &QTimer::timeout, this, &GameScene::spawnEnemy);
    buttons.resize(11);
    for(int i = 0;i < 11;i++){
        buttons[i].resize(11);
    }
    for(int i = 0;i < 11;i++){
        for(int j = 0;j < 11;j++){
            buttons[i][j].resize(7);
        }
    }
    towers.resize(11);
    for(int i = 0; i < 11; i++){
        towers[i].resize(11);
    }
    buttons2.resize(11);
    for(int i = 0;i < 11;i++){
        buttons2[i].resize(11);
    }
    for(int i = 0;i < 11;i++){
        for(int j = 0;j < 11;j++){
            buttons2[i][j].resize(3);
        }
    }
}


void GameScene::startGame() {
    enemyTimer->start(3000); // 每X秒生成一个敌人
}

void GameScene::createPath() {
    // 定义敌人的路径 (基于网格坐标)
    enemyPath << QPoint(1, 0) << QPoint(1, 1) << QPoint(1, 2)
              << QPoint(1, 3) << QPoint(2, 3) << QPoint(3, 3)
              << QPoint(4, 3) << QPoint(4, 2) << QPoint(5,2)
              << QPoint(6, 2) << QPoint(7, 2) << QPoint(8, 2)
              <<QPoint(9,2)<<QPoint(10,2)<<QPoint(10,3)<<QPoint(11,3);
}

void GameScene::highlightPath() {
    // 用特殊的颜色框住敌人的路径
    QPen pathPen(Qt::transparent, 2); // 红色边框，线宽 2
    for (const QPoint &point : enemyPath) {
        addRect(46+point.x() * 170, point.y() * 160, 170, 160, pathPen);
    }
}
void GameScene::drawGrid() {
    // 绘制普通网格
    for (int x = 0; x < 13; ++x) {
        for (int y = 0; y < 5; ++y) {
            if ((x==1&&(y==0 or y==1 or y==2 or y==3) ) or (y==3 and(x==2 or x==3 or x==4 or x==10 or x==11)) or (y==2 and (x==4 or x==5 or x==6
           or x==7 or x==8 or x==9 or x==10)) or (y==0 and (x<=10 and x>=2))){
                continue;
            }
            addRect(46+x * 170, y * 160, 170, 160, QPen(Qt::gray));

        }
    }
    MainWindow::updateGoldDisplay();
    highlightPath();
}

QPoint GameScene::mapToGrid(const QPointF &point) {
    return QPoint(static_cast<int>(point.x()) / 170, static_cast<int>(point.y()) / 160);
}

bool GameScene::isOccupied(const QPoint &gridPos) {
    return grid[gridPos.x()][gridPos.y()] == 1;
}

void GameScene::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    QPoint gridPos = mapToGrid(event->scenePos());
    if ((gridPos.x()==1&&(gridPos.y()==0 or gridPos.y()==1 or gridPos.y()==2 or gridPos.y()==3) ) or (gridPos.y()==3
     and(gridPos.x()==2 or gridPos.x()==3 or gridPos.x()==4 or gridPos.x()==10 or gridPos.x()==11)) or (gridPos.y()==2 and (gridPos.x()==4 or gridPos.x()==5 or gridPos.x()==6
   or gridPos.x()==7 or gridPos.x()==8 or gridPos.x()==9 or gridPos.x()==10)) or (gridPos.y()==0 and (gridPos.x()>=2 and gridPos.x()<=10))){
        return;
    }
    if (gridPos.x() >= 0 && gridPos.x() < 13 && gridPos.y() >= 0 && gridPos.y() < 6) {
        if (!isOccupied(gridPos)) {
            /*
            Tower *tower = new Tower();
            tower->setPos(70+gridPos.x() * 170, 23+gridPos.y() * 160);
            addItem(tower);
            grid[gridPos.x()][gridPos.y()] = 1; // 标记为已占用
            */
            qDebug() << "creating tower buttons";
            createTowerButtons(gridPos.x(), gridPos.y());//创建四个按钮，用于建造防御塔
        }
        else{
            Tower* tower = towers[gridPos.x()][gridPos.y()];
            if(tower && tower->canUpgrade()){
                qDebug() << "creating upgrade buttons";
                createUpgradeButtons(gridPos.x(), gridPos.y(), tower);
            }
        }
    }
}

void GameScene::createUpgradeButtons(int row, int col, Tower* tower){
    QStringList upgradePaths = {"Path 1", "Path 2"};
    for (int i = 0; i < 2; i++) {
        QGraphicsView* view = this->views().first();
        UpgradeButton* button = new UpgradeButton(this, upgradePaths[i], tower, QPoint(row, col), view);

        int offsetX = (i % 2) * 60;
        int offsetY = (i / 2) * 60;

        button->setGeometry(70 + row * (cellWidth) + offsetX, 23 + col * (cellHeight) + offsetY, 50, 50);
        button->show();
        buttons2[row][col].append(button);
    }
}

void GameScene::upgradeTower(const QString& upgradePath, const QPoint& gridPos){
    if (gridPos.x() >= 0 && gridPos.x() < columns && gridPos.y() >= 0 && gridPos.y() < rows){
        Tower* tower = towers[gridPos.x()][gridPos.y()];
        if(tower->canUpgrade()){
            if(upgradePath == "Path 1" and globalMoney>=tower->upgradeCost()){

                globalMoney-=tower->upgradeCost();
                tower->upgrade(1);
                MainWindow::updateGoldDisplay();
            }
            else if(upgradePath=="Path 2" and globalMoney>=tower->upgradeCost()){

                globalMoney-=tower->upgradeCost();
                tower->upgrade(2);
                MainWindow::updateGoldDisplay();
            }
            else
            {
                qDebug()<<"Need more gold to upgrade a tower";
            }
            for (UpgradeButton* button : buttons2[gridPos.x()][gridPos.y()]) {
                if (button) {
                    button->hide();
                }
            }
        }
    }
}
void GameScene::createTowerButtons(int row, int col){
    QStringList towerTypes = {"fast", "poison", "slow", "power"};
    for (int i = 0; i < 4; ++i) {
        QGraphicsView* view = this->views().first();
        TowerButton* button = new TowerButton(this, towerTypes[i], QPoint(row, col), view);
        int offsetX = (i % 2) * 60;
        int offsetY = (i / 2) * 60;
        button->setGeometry(70 + row * (cellWidth) + offsetX, 23 + col * (cellHeight) + offsetY, 50, 50);
        button->show();
        buttons[row][col].append(button);
    }
}

void GameScene::placeTower(const QString& towerType, const QPoint& gridPos) {
    // 判断位置是否有效
    if (gridPos.x() >= 0 && gridPos.x() < columns && gridPos.y() >= 0 && gridPos.y() < rows) {
        Tower* tower = nullptr;
        if (!isOccupied(gridPos)) {
            // 创建指定类型的塔
            bool able_to_buy=false;
            if(towerType == "fast" and globalMoney>=200){
                able_to_buy=true;
                tower = new FastTower();
            }
            else if(towerType == "poison" and globalMoney>=200){
                able_to_buy=true;
                tower = new PoisonTower();
            }
            else if(towerType == "slow" and globalMoney>=200){
                able_to_buy=true;
                tower = new SlowTower();
            }
            else if(towerType=="power" and globalMoney>=200){
                able_to_buy=true;
                tower = new PowerTower();
            }
            if(able_to_buy)
            {
                towers[gridPos.x()][gridPos.y()] = tower;
                // 设置塔的位置
                globalMoney-=200;
                MainWindow::updateGoldDisplay();
                tower->setPos(70 + gridPos.x() * cellWidth, 23 + gridPos.y() * cellHeight);
                addItem(tower);
                grid[gridPos.x()][gridPos.y()] = 1;  // 标记为已占用
            }
            else
            {
                qDebug()<<"Need 200 gold to buy a tower";
            }
            for (TowerButton* button : buttons[gridPos.x()][gridPos.y()]) {
                if (button) {
                    button->hide();
                }
            }
        }
    }
}

void GameScene::spawnEnemy() {
    QRandomGenerator generator = QRandomGenerator::securelySeeded();
    int a = generator.bounded(10);
    Enemy *enemy = new Enemy(enemyPath, a);
    addItem(enemy);
    enemy->setPos(enemyPath.first().x() * 170, enemyPath.first().y() * 160);
}
