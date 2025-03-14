#include "towerbutton.h"
#include "gamescene.h"
#include <QDebug>
#include <QGraphicsView>

TowerButton::TowerButton(GameScene* scene, const QString& towerType, const QPoint& gridPos, QGraphicsView* view)
    : QPushButton(view), gameScene(scene), towerType(towerType), gridPos(gridPos) {
    setText(towerType);  // 设置按钮文本为塔的类型
    connect(this, &QPushButton::clicked, this, &TowerButton::onClicked);  // 连接点击事件

}

void TowerButton::onClicked() {
    // 确保 gameScene 不为空
    if (gameScene) {
        // 放置塔
        gameScene->placeTower(towerType, gridPos);
    } else {
        qDebug() << "Error: gameScene is nullptr.";
    }
}
