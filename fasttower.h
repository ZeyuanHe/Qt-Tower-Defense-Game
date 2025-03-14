#ifndef FASTTOWER_H
#define FASTTOWER_H

#include "tower.h"

class FastTower : public Tower {
public:
    FastTower();
    void upgrade(int path) override;  // 重载升级方法
};

#endif // FASTTOWER_H
