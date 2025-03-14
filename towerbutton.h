#ifndef TOWERBUTTON_H
#define TOWERBUTTON_H

#include <QPushButton>
#include <QString>
#include <QGraphicsView>

class GameScene;  // 前向声明 GameScene 类

class TowerButton : public QPushButton {
    Q_OBJECT

public:
    // 构造函数，接收父对象，塔的类型，和对应格子的位置
    explicit TowerButton(GameScene* scene, const QString& towerType, const QPoint& gridPos, QGraphicsView* view);

private slots:
    // 按钮点击事件处理函数
    void onClicked();

private:
    GameScene* gameScene;
    QString towerType;      // 当前按钮对应的塔类型
    QPoint gridPos; //对应格子的位置
};

#endif // TOWERBUTTON_H
