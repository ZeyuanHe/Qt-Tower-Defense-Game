#include "healthbar.h"
#include <QObject>
#include <QGraphicsScene>

HealthBar::HealthBar(int maxHealth)
    : maxHealth(maxHealth), currentHealth(maxHealth) {}

void HealthBar::updateHealth(int currentHealth) {
    this->currentHealth = currentHealth;
    update(); // 触发重绘
}

QRectF HealthBar::boundingRect() const {
    return QRectF(0, 0, 170, 5);
}

void HealthBar::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) {
    int barWidth = static_cast<int>((currentHealth / static_cast<float>(maxHealth)) * 100);
    painter->setBrush(Qt::green);
    painter->drawRect(35, 30, barWidth, 5);
    painter->setBrush(Qt::gray);
    painter->drawRect(35+barWidth, 30, 100 - barWidth, 5);
}

HealthBar::~HealthBar() {
    if (scene()) {
        scene()->removeItem(this);
    }
}
