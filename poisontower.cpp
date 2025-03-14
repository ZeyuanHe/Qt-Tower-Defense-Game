#include "poisontower.h"
#include "bullet.h"
#include "enemy.h"
#include <QTimer>
#include <QDebug>

PoisonTower::PoisonTower()
    : Tower(":/new/prefix6/posionTower_new.png") {  // Pass image path to the base class
    setAttackInterval(1800);  // Set attack interval to 1800 milliseconds
    setDamage(6);  // Initial damage is low to balance poison effect
    attackRange = 250;  // Initialize attack range
    type = 1;  // Tower type identifier for poison effects
    maxLevel = 3;  // Maximum upgrade level
}

void PoisonTower::upgrade(int path) {
    if (level < maxLevel) {
        level++;  // 增加等级

        if (path == 1) {
            // 路径1：增加中毒时间
            pathOfTower += 1;
            attackRange += 50;  // 每次升级增加攻击范围
            qDebug() << "PoisonTower upgraded on path 1. New range:" << attackRange;
        } else if (path == 2) {
            // 路径2：增加中毒伤害
            pathOfTower += 3;
            setDamage(damageOfTower + 6);  // 每次升级增加6点攻击力
            qDebug() << "PoisonTower upgraded on path 2. New damage:" << damageOfTower;
        }

        // 添加闪烁效果
        QTimer* timer = new QTimer(this);
        int* flashCount = new int(0);  // 动态分配计数器，确保每次独立计数
        connect(timer, &QTimer::timeout, [this, timer, flashCount]() {
            setVisible(!isVisible());  // 切换可见状态
            (*flashCount)++;
            if (*flashCount >= 6) {  // 闪烁3次后停止
                timer->stop();
                setVisible(true);  // 确保最终可见
                delete flashCount;  // 释放计数器内存
                timer->deleteLater();  // 释放定时器
            }
        });
        timer->start(100);  // 每100毫秒切换一次可见性

        update();  // 刷新塔的显示
    } else {
        qDebug() << "PoisonTower is already at max level!";
    }
}




void PoisonTower::activateSpecialAbility() {
    // 剧毒爆发：短时间内对所有敌人增加中毒伤害
    QList<QGraphicsItem *> items = scene()->items();
    for (QGraphicsItem *item : items) {
        Enemy *enemy = dynamic_cast<Enemy *>(item);
        if (enemy && QLineF(pos(), enemy->pos()).length() <= attackRange) {
            enemy->poisonReduceHealth(10,5);  // 增强中毒伤害
        }
    }
}
