#ifndef POWERTOWER_H
#define POWERTOWER_H

#include "tower.h"

class PowerTower : public Tower {
public:
    PowerTower();
    void upgrade(int path) override;  // 重载升级方法
};

#endif // POWERTOWER_H
