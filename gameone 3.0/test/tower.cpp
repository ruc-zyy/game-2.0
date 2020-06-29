#include "tower.h"
#include "enemy.h"
#include "bullet.h"
#include "mainwindow.h"
#include "utility.h"
#include <QPainter>
#include <QColor>
#include <QTimer>
#include <QVector2D>
#include <QtMath>
#include<QMovie>
#include<QLabel>
Tower::Tower(int t,QPoint pos,int n,MainWindow *game, const QPixmap &sprite):m_pos(pos),m_sprite(sprite)

    , m_chooseEnemy(NULL)
    , m_game(game)
,m_attacking(false)
{type=t;
    no=n;
    if(type==1){
    m_attackrange=200;
    m_fireRate=800;
    m_damage=10;
    connect(m_fireRateTimer, SIGNAL(timeout()), this, SLOT(shootWeapon()));}
    if(type==2){
        m_attackrange=200;
        m_fireRate=500;
        m_damage=3;
        connect(m_fireRateTimer, SIGNAL(timeout()), this, SLOT(type2attack()));
        m_fireRateTimer->start(m_fireRate);
    }
}

void Tower::draw(QLabel **towerlabel,QMovie *pic,QPainter *painter) const{
if(type==1&&level==1){
    towerlabel[no]->setGeometry(m_pos.x()-20,m_pos.y()-75,50,84);
towerlabel[no]->setScaledContents(true);
towerlabel[no]->setMovie(pic);
pic->start();}
if(type==1&&level==2){
    towerlabel[no]->setGeometry(m_pos.x()-30,m_pos.y()-80,70,100);
towerlabel[no]->setScaledContents(true);
towerlabel[no]->setMovie(m_game->pic2[no]);
m_game->pic2[no]->start();}
if(type==2&&level==1){
    painter->drawPixmap(m_pos.x()-20,m_pos.y()-80,m_sprite);
}
if(type==2&&level==2){
    painter->drawPixmap(m_pos.x()-30,m_pos.y()-80,m_sprite2);
}
}

void Tower::checkEnemyInRange()
{
    if (m_chooseEnemy)
    {
        // 如果敌人脱离攻击范围
        if (!collisionWithCircle(m_pos, m_attackrange, m_chooseEnemy->m_pos, 1))
            lostSightOfEnemy();
    }
    else
    {
        // 遍历敌人,看是否有敌人在攻击范围内

        foreach (Enemy *enemy, m_game->m_enemyList)
        {
            if (collisionWithCircle(m_pos, m_attackrange, enemy->m_pos, 1))
            {
                chooseEnemyForAttack(enemy);
                break;
            }
        }
    }
}
void Tower::attackEnemy()

{

    // 启动打炮模式



}

void Tower::chooseEnemyForAttack(Enemy *enemy)

{

    // 选择敌人,同时设置对敌人开火

    m_chooseEnemy = enemy;

    // 这里启动timer,开始打炮
m_fireRateTimer->start(m_fireRate);


    // 敌人自己要关联一个攻击者,这个用QList管理攻击者,因为可能有多个

    m_chooseEnemy->getAttacked(this);

}

void Tower::shootWeapon()
{
    Bullet *bullet = new Bullet(1,m_pos+QPoint(0,-80), m_chooseEnemy->m_pos, m_damage, m_chooseEnemy, m_game);
bullet->move();
    m_game->addBullet(bullet);

}

void Tower::targetKilled()

{

    // 目标死亡时,也需要取消关联

    // 取消攻击

    if (m_chooseEnemy)

        m_chooseEnemy = NULL;

    m_fireRateTimer->stop();



}

void Tower::lostSightOfEnemy()

{

    // 当敌人脱离炮塔攻击范围,要将炮塔攻击的敌人关联取消

    // 同时取消攻击

    m_chooseEnemy->gotLostSight(this);

    if (m_chooseEnemy)

        m_chooseEnemy = NULL;

    m_fireRateTimer->stop();



}
void Tower::starttimer(){
    m_fireRateTimer->start(m_fireRate);
}
void Tower::type2attack(){
    foreach (Enemy *enemy, m_game->m_enemyList)
    {
        if (collisionWithCircle(m_pos, m_attackrange, enemy->m_pos, 1))
        {
            Bullet *bullet = new Bullet(2,m_pos+QPoint(0,-80),enemy->m_pos, m_damage, enemy, m_game);
        bullet->move();
            m_game->addBullet(bullet);

        }
    }
}

void Tower::up(){
    level=2;
    if(type==2){
        m_damage=4;
        m_fireRate=300;
        m_fireRateTimer->setInterval(m_fireRate);

    }
    if(type==1){
        m_damage=30;
        m_attackrange=250;
    }
}
