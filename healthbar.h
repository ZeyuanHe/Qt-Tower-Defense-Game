#ifndef HEALTHBAR_H
#define HEALTHBAR_H

#include <QGraphicsItem>
#include <QPainter>
#include <QObject>

class HealthBar : public QObject, public QGraphicsItem {
    Q_OBJECT
public:
    HealthBar(int maxHealth);
    ~HealthBar();
    void updateHealth(int currentHealth);

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
    int maxHealth;
    int currentHealth;
};

#endif // HEALTHBAR_H
