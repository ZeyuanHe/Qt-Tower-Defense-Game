#include "upgradebutton.h"
#include "gamescene.h"
#include <QDebug>
#include <QGraphicsView>

UpgradeButton::UpgradeButton(GameScene* scene, const QString& upgradePath, Tower* tower, const QPoint& gridPos, QGraphicsView* view)
    : QPushButton(view), gameScene(scene), upgradePath(upgradePath), tower(tower), gridPos(gridPos) {
    setText(upgradePath);  // 设置按钮文本为塔的类型

    connect(this, &QPushButton::clicked, this, &UpgradeButton::onClicked);

}

void UpgradeButton::onClicked() {
    // 确保 gameScene 不为空
    if (gameScene) {
        gameScene->upgradeTower(upgradePath, gridPos);
    } else {
        qDebug() << "Error: gameScene is nullptr.";
    }
}
