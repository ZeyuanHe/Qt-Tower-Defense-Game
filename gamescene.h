#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <QGraphicsScene>
#include <QTimer>
#include <QPoint>
#include <QVector>
#include "enemy.h"
#include "tower.h"
#include "towerbutton.h"
#include "upgradebutton.h"

class GameScene : public QGraphicsScene {
    Q_OBJECT

public:
    GameScene(int width, int height, QObject *parent = nullptr);
    void startGame();
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void createTowerButtons(int row, int col);  // 显示建塔按钮
    void createUpgradeButtons(int row, int col, Tower* tower); // 显示升级按钮
    void placeTower(const QString& towerType, const QPoint& gridPos);  // 放置塔
    void upgradeTower(const QString& upgradePath, const QPoint& gridPos); // 升级塔
private slots:
    void spawnEnemy();

private:
    QTimer *enemyTimer;
    QList<QPoint> enemyPath;
    QVector<QVector<int>> grid;
    int rows, columns;
    int cellWidth, cellHeight;
    void createPath();
    void drawGrid();
    void highlightPath();
    QPoint mapToGrid(const QPointF &point);
    bool isOccupied(const QPoint &gridPos);
    QVector<QVector<QVector<TowerButton*>>> buttons;  // 按钮集合，用来存放建塔按钮
    QVector<QVector<QVector<UpgradeButton*>>> buttons2; // 按钮集合，用来存放升级按钮
    QVector<QVector<Tower*>> towers; // 防御塔集合
};

#endif // GAMESCENE_H
