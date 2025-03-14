#ifndef POISON_TOWER_H
#define POISON_TOWER_H

#include "tower.h"
#include <QGraphicsScene>

class PoisonTower : public Tower {
public:
    PoisonTower();
    void upgrade(int path) override;  // 重载升级方法，增加选择路径
    void activateSpecialAbility();  // 添加特殊能力方法


};

#endif // POISON_TOWER_H
