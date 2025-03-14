#include "bullet.h"
#include <QPainter>
#include <QGraphicsScene>
#include <QTimer>
#include <cmath>
#include <QtMath>
#include <enemy.h>
#include <QLineF>

Bullet::Bullet(Enemy *target)
    : QObject(), QGraphicsItem(), moveTimer(new QTimer(this)), target(target) {
    connect(moveTimer, &QTimer::timeout, this, &Bullet::move);
    moveTimer->start(50); // Adjust movement interval if needed
}

QRectF Bullet::boundingRect() const {
    return QRectF(0, 0, 10, 10);
}

void Bullet::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) {
    if (poison) {
        painter->setBrush(Qt::green);
    } else if (slowdown) {
        painter->setBrush(Qt::blue);

    } else if (fast == true) {
        painter->setBrush(Qt::yellow);
    } else {
        painter->setBrush(Qt::black);
    }

    painter->drawEllipse(boundingRect());
}

void Bullet::move() {
    if (!target || !scene()->items().contains(target)) {
        // If the target is invalid or removed from the scene, delete the bullet
        scene()->removeItem(this);
        delete this;
        return;
    }

    // Calculate the center of the target
    QPointF targetCenter = target->pos() + target->boundingRect().center();

    // Calculate the direction to the target's center
    QLineF lineToTarget(pos(), targetCenter);
    qreal angleToTarget = -lineToTarget.angle(); // QGraphics uses clockwise rotation

    // Update position to move toward the target
    qreal dx = 10 * cos(angleToTarget * M_PI / 180);
    qreal dy = 10 * sin(angleToTarget * M_PI / 180);
    setPos(x() + dx, y() + dy);

    // Check if the bullet hits the target center
    if (lineToTarget.length() <= 5) { // Collision tolerance
        target->reduceHealth(damageOfBullet); // Inflict damage
        if(target->isAddHealth == true){
            target->addHealth(10);
        }

        // Handle special effects
        if (this->poison == true) {
            if (bulletPath == 0) {
                target->poisonReduceHealth(5, 7);
            } else if (bulletPath == 1) {
                target->poisonReduceHealth(5, 9);
            } else if (bulletPath == 2) {
                target->poisonReduceHealth(5, 11);
            } else if (bulletPath == 3) {
                target->poisonReduceHealth(8, 7);
            } else if (bulletPath == 4) {
                target->poisonReduceHealth(8, 9);
            } else if (bulletPath == 6) {
                target->poisonReduceHealth(11, 7);
            }
        }
        if(this->slowdown == true){
            if(bulletPath == 0){
                target->enemyStop(-1);
                target->slowDown(target->initialSpeed/2, 6);

            }
            else if(bulletPath == 1){
                target->slowDown(target->initialSpeed/2,9);
            }
            else if(bulletPath == 2){
                target->slowDown(target->initialSpeed/2, -1);
                target->enemyStop(4);
            }
        }
        scene()->removeItem(this);
        delete this;
        return;
    }

    // Delete bullet if it goes out of bounds
    if (x() < 0 || x() > 2000 || y() < 0 || y() > 1000) {
        scene()->removeItem(this);
        delete this;
    }
}
