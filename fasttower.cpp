#include "fasttower.h"
#include <QTimer>

FastTower::FastTower()
    : Tower(":/new/prefix6/fastTower_new.png") {  // Pass image path to base class
    setAttackInterval(500);  // Set attack interval to 500 milliseconds for rapid attacks
    setDamage(5);  // Initial damage is low for fast attack speed
    type = 3;  // Tower type identifier for special effects
    maxLevel = 3;  // Maximum level for upgrades
}




void FastTower::upgrade(int path) {
    if (level < maxLevel) {
        level++;  // 增加等级

        // 提升快速塔的属性
        setDamage(damageOfTower + 3);  // 每次升级增加3点攻击力
        setAttackInterval(qMax(100, attackInterval - 150));  // 减少攻击间隔
        attackRange += 50;  // 每次升级略微增加攻击范围

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

        // 请求重新绘制塔，以反映升级后的变化
        update();
    }
}
