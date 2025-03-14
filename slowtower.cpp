#include "slowtower.h"
#include "enemy.h"
#include <QDebug>

SlowTower::SlowTower()
    : Tower(":/new/prefix6/slowTower.png") {  // Pass the image path to the base class
    setAttackInterval(1500);  // Set attack interval to 1500 milliseconds
    setDamage(8);  // Moderate attack damage for slowing tower
    attackRange = 250;  // Initialize attack range
    type = 2;  // Identify tower type for special effects
    maxLevel = 2;  // Maximum upgrade level
}

void SlowTower::upgrade(int path) {
    if (level < maxLevel) {
        level++;  // 增加等级

        if (path == 1) {
            // 路径1：增加减速时间
            pathOfTower = 1;
            attackRange += 50;  // 每次升级增加攻击范围
            qDebug() << "SlowTower upgraded on path 1. New range:" << attackRange;
        } else if (path == 2) {
            // 路径2：增加伤害或添加冰冻效果
            pathOfTower = 2;
            setDamage(damageOfTower + 5);  // 每次升级增加5点攻击力
            setAttackInterval(5000);  // 设置攻击频率为 5000 毫秒
            qDebug() << "SlowTower upgraded on path 2. New damage:" << damageOfTower;
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

        update();  // 请求重新绘制塔
    } else {
        qDebug() << "SlowTower is already at max level!";
    }
}


