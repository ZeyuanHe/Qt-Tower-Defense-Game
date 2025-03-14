#ifndef ENEMY_H
#define ENEMY_H

#include <QObject>
#include <QGraphicsItem>
#include <QTimer>
#include <QList>
#include <QPoint>
#include <QGraphicsScene>
#include <QPointF>
#include <healthbar.h>

class Enemy : public QObject, public QGraphicsItem {
    Q_OBJECT

public:
    Enemy(const QList<QPoint> &path, float a); // 构造函数
    ~Enemy(); // 析构函数

    QRectF boundingRect() const override; // 定义边界框
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override; // 绘制敌人

    void reduceHealth(int amount); // 减少血量
    void poisonReduceHealth(int damageperpoison, int duration); // 毒伤害
    void slowDown(float speedAfterSlowdown, int duration); // 减速效果
    void enemyStop(int duration); // 停止移动
    void addHealth(int amount); // 增加血量

    bool isDead() const; // 判断敌人是否死亡
    int getmoney(); // 获取击杀敌人后获得的金钱
    float initialSpeed; // 初始速度
    bool isAddHealth; // 是否为加血怪

protected slots:
    void move(); // 敌人移动逻辑

protected:
    QTimer *moveTimer; // 控制移动的定时器
    QTimer *poisonTimer; // 毒伤害定时器
    QTimer *slowDownTimer; // 减速定时器
    QTimer *stopTimer; // 停止移动定时器
    QTimer *addHealthTimer;

    QList<QPoint> path; // 敌人路径
    int currentIndex; // 当前路径点索引
    int maxHealth; // 最大血量
    int health; // 当前血量
    int money; // 击杀后奖励的金钱
    int poisonnumber; // 毒伤害剩余次数
    int slowdownnumber; // 减速持续时间
    int stopnumber; // 停止移动持续时间
    int addinghealthtime;
    bool poisoning;
    bool slowing;
    bool freezing;
    bool isaddinghealth;
    QString imagepath; // 敌人的图片路径

    QPointF currentPos; // 当前坐标
    QPointF targetPos; // 目标坐标
    float speed; // 移动速度

    HealthBar *healthBar; // 血条对象
    void updateTargetPosition(); // 更新目标位置

private:
    bool isBeingDeleted; // 防止重复销毁的标志位
};

#endif // ENEMY_H
