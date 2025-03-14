#include "tower.h"
#include "bullet.h"
#include "globals.h"
#include <QPainter>
#include <QGraphicsScene>
#include <cmath>
#include <QGraphicsSceneMouseEvent>
#include <QPixmap>
#include <QDebug>
#include <QTimer>
#include <QGraphicsOpacityEffect>
#include<mainwindow.h>

Tower::Tower(const QString &imagePath, QGraphicsItem *parent)
    : QObject(), QGraphicsItem(parent),
    attackInterval(1000),
    damageOfTower(10),
    type(0),
    pathOfTower(0),
    level(1),
    maxLevel(3),
    attackRange(250),
    attackTimer(new QTimer(this)),
    showAttackRange(false),
    imagePath(imagePath) {  // 初始化图片路径
    connect(attackTimer, &QTimer::timeout, this, &Tower::attackEnemy);
    attackTimer->start(attackInterval);  // 使用 attackInterval 进行攻击
}

QRectF Tower::boundingRect() const {
    return QRectF(0, 0, 120, 110);
}

void Tower::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) {
    if (!imagePath.isEmpty()) {
        QPixmap pixmap(imagePath);
        if (!pixmap.isNull()) {
            painter->drawPixmap(boundingRect().toRect(), pixmap);
        } else {
            qDebug() << "Failed to load tower image:" << imagePath;
        }
    } else {
        painter->setBrush(Qt::blue);
        painter->drawRect(boundingRect());
    }

    if (showAttackRange) {
        QColor rangeColor(255, 0, 0, 50); // 红色，透明度为50
        painter->setBrush(rangeColor);
        painter->setPen(Qt::NoPen);
        painter->drawEllipse(QPointF(60, 55), attackRange, attackRange); // 以塔中心为圆心绘制攻击范围
    }
    painter->setPen(Qt::red);
    painter->drawText(boundingRect(), Qt::AlignCenter, QString("Lv %1").arg(level));
}

void Tower::setAttackInterval(int interval) {
    attackInterval = interval;
    attackTimer->setInterval(attackInterval); // 更新攻击定时器的间隔
}

void Tower::setDamage(int dmg) {
    damageOfTower = dmg;
}

void Tower::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    if (canUpgrade()) {
        upgrade(0);  // 默认升级路径
    }
    showAttackRange = !showAttackRange;  // 切换攻击范围显示状态
    update();  // 重新绘制塔
    QGraphicsItem::mousePressEvent(event);  // 保持默认事件处理
}

void Tower::attackEnemy() {
    Enemy *target = findClosestEnemy();
    if (target) {
        shootAt(target);
    }
}

void Tower::upgrade(int path) {
    if (level < maxLevel) {
        level++;  // 增加等级
        // 提升塔的属性
        setDamage(damageOfTower + 5);  // 每次升级增加5点攻击力
        setAttackInterval(qMax(200, attackInterval - 200));  // 减少攻击间隔，每次减少200毫秒，最小到200毫秒
        attackRange += 20;  // 增加攻击范围



        // 刷新塔的显示
        update();  // 立即触发 paint() 方法
    }
}

Enemy* Tower::findClosestEnemy() {
    QList<QGraphicsItem *> items = scene()->items();
    Enemy *closestEnemy = nullptr;
    qreal closestDistance = attackRange; // 以攻击范围作为初始最大距离

    for (QGraphicsItem *item : items) {
        Enemy *enemy = dynamic_cast<Enemy *>(item);
        if (enemy) {
            QPointF theCenter = enemy->pos() + enemy->boundingRect().center();
            qreal distance = QLineF(pos(), theCenter).length();
            if (distance < closestDistance) {
                closestDistance = distance;
                closestEnemy = enemy;
            }
        }
    }
    return closestEnemy; // 返回在攻击范围内的最近敌人
}

void Tower::shootAt(Enemy *target) {
    Bullet *bullet = new Bullet(target);
    bullet->damageOfBullet = damageOfTower;
    bullet->bulletPath = pathOfTower;
    bullet->poison = false;
    bullet->slowdown = false;
    if (type == 1) {
        bullet->poison = true;
    } else if (type == 2) {
        bullet->slowdown = true;
    } else if (type == 3) {
        bullet->fast = true;
    }

    bullet->setPos(boundingRect().center() + pos()); // 从塔的中心发射
    scene()->addItem(bullet);
}

bool Tower::canUpgrade() const {
    if(level < maxLevel && globalMoney >= this->upgradeCost()){
        return true;
    }
    else{
        return false;
    }
}

int Tower::upgradeCost() const {
    return 50 + level * 50;  // 假设每次升级的费用增加
}
