#include "powertower.h"

PowerTower::PowerTower()
    : Tower(":/new/prefix6/powerTower_new.png") {  // Pass the image path to the base class
    setAttackInterval(2000);  // Set attack interval to 2000 milliseconds
    setDamage(20);  // Set initial high damage
    attackRange = 250;  // Set initial attack range
    type = 0;  // Identify tower type (e.g., standard)
    maxLevel = 3;  // Maximum upgrade level
}

void PowerTower::upgrade(int path) {
    if (level < maxLevel) {
        level++;  // 增加等级

        // 提升高伤害塔的属性
        setDamage(damageOfTower + 10);  // 每次升级增加10点攻击力
        setAttackInterval(qMax(500, attackInterval - 100));  // 减少攻击间隔，但幅度较小，最小不低于500毫秒
        attackRange += 50;  // 每次升级大幅增加攻击范围

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


        // 请求重新绘制塔，以反映升级后的变化
        update();
    }
}
