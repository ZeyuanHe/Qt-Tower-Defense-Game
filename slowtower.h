#ifndef SLOWTOWER_H
#define SLOWTOWER_H

#include "tower.h"
#include <QGraphicsScene>

class SlowTower : public Tower {
public:
    SlowTower();
    void upgrade(int path) override;  // 重载升级方法，增加选择路径


};

#endif // SLOWTOWER_H
