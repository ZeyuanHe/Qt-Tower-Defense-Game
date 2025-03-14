#ifndef TOWER_H
#define TOWER_H

#include <QObject>
#include <QGraphicsItem>
#include <QTimer>
#include "enemy.h"
#include <QGraphicsPixmapItem>

class Tower : public QObject, public QGraphicsItem {
    Q_OBJECT

public:
    explicit Tower(const QString &imagePath = "", QGraphicsItem *parent = nullptr);
    virtual void upgrade(int path);  // 声明为虚函数，允许子类重载
    virtual void shootAt(Enemy *target);  // 声明为虚函数，允许子类重载
    QRectF boundingRect() const override;
    void setAttackInterval(int interval);  // 设置攻击频率
    void setDamage(int dmg);  // 设置攻击力
    bool canUpgrade() const;  // 检查是否可以升级
    int upgradeCost() const;  // 升级的费用，每次不同
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;


protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;  // 处理鼠标点击事件
    Enemy* findClosestEnemy(); // 查找最近的敌人
    void attackEnemy();  // 执行攻击
    int level;  // 塔的等级
    int maxLevel;  // 最大等级
    int attackInterval;  // 攻击频率
    int damageOfTower;  // 攻击力
    int type;
    int pathOfTower;
    qreal attackRange;  // 攻击范围
    QTimer *attackTimer;  // 攻击定时器
    bool showAttackRange;  // 是否显示攻击范围

private:
    QString imagePath;  // 图片路径
};

#endif // TOWER_H
