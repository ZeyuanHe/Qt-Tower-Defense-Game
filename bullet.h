#ifndef BULLET_H
#define BULLET_H

#include <QObject>
#include <QGraphicsItem>
#include <QTimer>
#include <QPainter>
#include <enemy.h>

class Bullet : public QObject, public QGraphicsItem {
    Q_OBJECT

public:
    Bullet(Enemy *target);
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    bool poison;
    bool slowdown;
    bool fast;
    int damageOfBullet;
    int bulletPath;
private slots:
    void move();
private:
    QTimer *moveTimer;
    Enemy *target;

};

#endif // BULLET_H
