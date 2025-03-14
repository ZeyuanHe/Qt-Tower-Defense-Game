#ifndef UPGRADEBUTTON_H
#define UPGRADEBUTTON_H


#include <QPushButton>
#include <QString>
#include <QGraphicsView>
#include "tower.h"

class GameScene;  // 前向声明 GameScene 类

class UpgradeButton : public QPushButton {
    Q_OBJECT

public:
    // 构造函数，接收父对象，升级路径，和对应格子的位置
    explicit UpgradeButton(GameScene* scene, const QString& upgradePath, Tower* tower, const QPoint& gridPos, QGraphicsView* view);

private slots:
    // 按钮点击事件处理函数
    void onClicked();

private:
    GameScene* gameScene;
    QString upgradePath;      // 当前按钮对应的升级路径
    QPoint gridPos; //对应格子的位置
    Tower* tower;
};

#endif // UPGRADEBUTTON_H
