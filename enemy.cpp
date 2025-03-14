#include "enemy.h"
#include <QMovie>
#include <QLabel>
#include <QPainter>
#include <QGraphicsScene>
#include <QPointF>
#include <cmath>
#include <healthbar.h>
#include <QObject>
#include "mainwindow.h"
#include "gamescene.h"
#include "globals.h"
#include <QDebug>

Enemy::Enemy(const QList<QPoint> &path, float a) : path(path), currentIndex(0), isBeingDeleted(false) {
    // 初始化当前位置和目标位置
    poisoning = false;
    slowing = false;
    freezing = false;
    isaddinghealth = false;
    addinghealthtime = 1;
    currentPos = QPointF(46 + path[0].x() * 170, path[0].y() * 160);
    updateTargetPosition();

    // 根据 a 的值初始化敌人属性
    if (a >= 4 && a < 7) {
        imagepath = ":/new/prefix1/enemyB.png";
        maxHealth = 100;
        health = 100;
        speed = 2.0;
        money = 100;
        isAddHealth = false;
    } else if (0 <= a && a < 4) {
        imagepath = ":/new/prefix1/enemyD.png";
        maxHealth = 50;
        health = 50;
        speed = 3.0;
        money = 50;
        isAddHealth = false;
    } else if (a == 7) {
        imagepath = ":/new/prefix1/enemyA.png";
        maxHealth = 500;
        health = 500;
        speed = 0.4;
        money = 500;
        isAddHealth = false;
    } else {
        imagepath = ":/new/prefix1/enemyC.png";
        maxHealth = 150;
        health = 150;
        speed = 1.5;
        money = 200;
        isAddHealth = true;
    }

    initialSpeed = speed;

    // 初始化定时器
    healthBar = new HealthBar(maxHealth);
    poisonTimer = new QTimer(this);
    slowDownTimer = new QTimer(this);
    stopTimer = new QTimer(this);
    addHealthTimer = new QTimer(this);
    moveTimer = new QTimer(this);

    // 连接定时器信号
    connect(moveTimer, &QTimer::timeout, this, &Enemy::move);
    moveTimer->start(30);
}

QRectF Enemy::boundingRect() const {
    return QRectF(0, 0, 170, 160);
}

void Enemy::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) {
    if (!imagepath.isEmpty()) {
        QPixmap pixMap;
        pixMap.load(imagepath);
        if (!pixMap.isNull()) {
            painter->drawPixmap(boundingRect().toRect(), pixMap);
        } else {
            qDebug() << "Failed to load enemy image:" << imagepath;
        }
        if(slowing == true){
            QPixmap slowPicture;
            slowPicture.load(":/new/prefix4/slow.png");
            painter->drawPixmap(40, 82, 75, 38, slowPicture);
        }
        if(poisoning == true){
            QPixmap poisonPicture;
            poisonPicture.load(":/new/prefix4/poisonn.png");
            painter->drawPixmap(40, 82, 75, 38, poisonPicture);
        }
        if(freezing == true){
            QPixmap freezPicture;
            freezPicture.load(":/new/prefix4/freez.png");
            painter->drawPixmap(40, 82, 75, 38, freezPicture);
        }
        if(isaddinghealth == true){
            QPixmap addHealthPicture;
            addHealthPicture.load(":/new/prefix4/addinghealthh.png");
            painter->drawPixmap(75, 0, 20, 20, addHealthPicture);
        }
    } else {
        painter->setBrush(Qt::blue);
        painter->drawRect(boundingRect());
    }
}

void Enemy::reduceHealth(int amount) {
    health -= amount;
    if (healthBar) {
        healthBar->updateHealth(health);
    }

    if (health <= 0 && !isBeingDeleted) {
        isBeingDeleted = true;
        this->deleteLater();
        globalMoney += this->getmoney();
        MainWindow::updateGoldDisplay();
    }
}

bool Enemy::isDead() const {
    return health <= 0;
}

void Enemy::updateTargetPosition() {
    if (currentIndex + 1 < path.size()) {
        currentIndex++;
        targetPos = QPointF(46 + path[currentIndex].x() * 170, path[currentIndex].y() * 160);
    }
}

void Enemy::poisonReduceHealth(int damageperpoison, int duration) {
    poisonnumber = duration;
    poisoning = true;
    connect(poisonTimer, &QTimer::timeout, [=] {
        health -= damageperpoison;
        poisonnumber -= 1;
        if (poisonnumber <= 0) {
            poisoning = false;
            poisonTimer->stop();
        }
        if (healthBar) {
            healthBar->updateHealth(health);
        }
        if (health <= 0 && !isBeingDeleted) {
            isBeingDeleted = true;
            globalMoney += this->getmoney();
            MainWindow::updateGoldDisplay();
            this->deleteLater();
        }
    });
    poisonTimer->start(1000);
}

void Enemy::slowDown(float speedAfterSlowdown, int duration) {
    if(duration >= 0){
        slowdownnumber = duration;
        slowing = true;
        speed = speedAfterSlowdown;
        connect(slowDownTimer, &QTimer::timeout, [=] {
            slowdownnumber -= 1;
            if (slowdownnumber <= 0) {
                slowing = false;
                slowDownTimer->stop();
                speed = initialSpeed;
            }
        });
        slowDownTimer->start(500);
    }
}

void Enemy::enemyStop(int duration) {
    if(duration >= 0){
        stopnumber = duration;
        freezing = true;
        speed = 0;
        connect(stopTimer, &QTimer::timeout, [=] {
            stopnumber -= 1;
            if (stopnumber <= 0) {
                freezing = false;
                stopTimer->stop();
                speed = initialSpeed;
            }
        });
        stopTimer->start(500);
    }

}

void Enemy::addHealth(int amount) {
    QList<QGraphicsItem *> items = scene()->items();

    for (QGraphicsItem *item : items) {
        Enemy *enemy = dynamic_cast<Enemy *>(item);
        if (enemy) {
            QPointF enemyCenter = enemy->pos() + enemy->boundingRect().center();
            qreal distance = QLineF(pos(), enemyCenter).length();
            if (distance < 150) {
                enemy->isaddinghealth = true;
                if (enemy->health < enemy->maxHealth - amount) {
                    enemy->health += amount;
                } else {
                    enemy->health = enemy->maxHealth;
                }

                if (enemy->healthBar) {
                    enemy->healthBar->updateHealth(enemy->health);
                }
                connect(addHealthTimer, &QTimer::timeout, [=] {
                    addinghealthtime -= 1;
                    if (addinghealthtime <= 0) {
                        enemy->isaddinghealth = false;
                        addHealthTimer->stop();
                    }
                });
                addHealthTimer->start(1000);
            }
        }
    }
}

void Enemy::move() {
    if (isBeingDeleted || !scene() || health <= 0) return;

    if (currentIndex + 1 >= path.size()) {
        if (!isBeingDeleted) {
            isBeingDeleted = true;
            this->deleteLater();
        }
        return;
    }

    qreal dx = targetPos.x() - currentPos.x();
    qreal dy = targetPos.y() - currentPos.y();
    qreal distance = std::sqrt(dx * dx + dy * dy);

    if (distance < speed) {
        currentPos = targetPos;
        updateTargetPosition();
    } else {
        qreal moveX = speed * (dx / distance);
        qreal moveY = speed * (dy / distance);
        currentPos.setX(currentPos.x() + moveX);
        currentPos.setY(currentPos.y() + moveY);
    }

    setPos(currentPos);
    if (healthBar && !healthBar->scene() && scene()) {
        scene()->addItem(healthBar);
    }
    healthBar->setPos(currentPos.x(), currentPos.y() - 10);
}

int Enemy::getmoney() {
    return money;
}

Enemy::~Enemy() {
    if (moveTimer) {
        moveTimer->stop();
        disconnect(moveTimer, nullptr, nullptr, nullptr);
        delete moveTimer;
        moveTimer = nullptr;
    }
    if (poisonTimer) {
        poisonTimer->stop();
        disconnect(poisonTimer, nullptr, nullptr, nullptr);
        delete poisonTimer;
        poisonTimer = nullptr;
    }
    if (slowDownTimer) {
        slowDownTimer->stop();
        disconnect(slowDownTimer, nullptr, nullptr, nullptr);
        delete slowDownTimer;
        slowDownTimer = nullptr;
    }
    if (stopTimer) {
        stopTimer->stop();
        disconnect(stopTimer, nullptr, nullptr, nullptr);
        delete stopTimer;
        stopTimer = nullptr;
    }
    if (scene()) {
        scene()->removeItem(this);
    }
    if (healthBar) {
        delete healthBar;
        healthBar = nullptr;
    }
}
