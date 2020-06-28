#include "enemy.h"
#include "waypoint.h"
#include "tower.h"
#include "utility.h"
#include "mainwindow.h"

#include <QPainter>
#include <QColor>
#include <QDebug>
#include <QMatrix>
#include <QVector2D>
#include <QtMath>
static const int Health_Bar_Width = 20;
const QSize Enemy::ms_fixedSize(50, 50);
Enemy::Enemy(int num,int _type,QPoint pos,WayPoint *startWayPoint, MainWindow *game)

    : QObject(0)

    , m_pos(pos)



{
    m_game = game;
    no=num;
    m_destinationWayPoint = startWayPoint;
    type=_type;
   if(type==1){
    m_maxHp = 60;
    m_currentHp = 60;
    m_active = false;
    m_walkingSpeed = 2.0;
    m_pic=m_game->epic[no];
m_gold=15;
}

   else if(type==2){
    m_maxHp = 80;
    m_currentHp = 80;
    m_active = false;
    m_walkingSpeed = 2.0;
m_gold=20;
    m_pic=m_game->wolfpic[no];
}
  else if(type==3){
    m_maxHp = 150;
    m_currentHp = 150;
    m_active = false;
    m_walkingSpeed = 2.0;
m_gold=50;
    m_pic=m_game->dragonpic[no];
}
}

void Enemy::draw(QPainter *painter,QLabel **enemylabel)

{
    if (!m_active)
        return;


    // 血条的长度

    // 其实就是2个方框,红色方框表示总生命,固定大小不变

    // 绿色方框表示当前生命,受m_currentHp / m_maxHp的变化影响

    static const int Health_Bar_Width = 20;

    painter->save();

    QPoint healthBarPoint = m_pos + QPoint(-Health_Bar_Width / 2 - 5, -ms_fixedSize.height() / 3)+QPoint(12,-15);

    // 绘制血条

    painter->setPen(Qt::NoPen);

    painter->setBrush(Qt::red);

    QRect healthBarBackRect(healthBarPoint, QSize(Health_Bar_Width, 2));

    painter->drawRect(healthBarBackRect);

    painter->setBrush(Qt::green);

    QRect healthBarRect(healthBarPoint, QSize((double)m_currentHp / m_maxHp * Health_Bar_Width, 2));

    painter->drawRect(healthBarRect);

    // 绘制偏转坐标,由中心+偏移=左上

    static const QPoint offsetPoint(-ms_fixedSize.width() / 2, -ms_fixedSize.height() / 2);

    painter->translate(m_pos);



    // 绘制敌人

 if(type==1)   enemylabel[no]->setGeometry(m_pos.x()-25,m_pos.y()-25,50,50);
 else if(type==2) enemylabel[no]->setGeometry(m_pos.x()-25,m_pos.y()-25,70,70);
 else if(type==3) enemylabel[no]->setGeometry(m_pos.x()-40,m_pos.y()-50,100,100);
    enemylabel[no]->setScaledContents(true);
    enemylabel[no]->setMovie(m_pic);
    m_pic->start();

    painter->restore();

}


void Enemy::move()

{

    if (!m_active)
        return;



    if (collisionWithCircle(m_pos, 1, m_destinationWayPoint->pos(), 1))
    {
        // 敌人抵达了一个航点
        if (m_destinationWayPoint->nextWayPoint())
        {
            // 还有下一个航点
            m_pos = m_destinationWayPoint->pos();
            m_destinationWayPoint = m_destinationWayPoint->nextWayPoint();
        }
        else
        {
            // 表示进入基地
            m_game->getHpDamage();
            m_game->removedEnemy(this);
            return;
        }
    }

    // 还在前往航点的路上
    // 目标航点的坐标
    QPoint targetPoint = m_destinationWayPoint->pos();
    // 未来修改这个可以添加移动状态,加快,减慢,m_walkingSpeed是基准值

    // 向量标准化
    qreal movementSpeed = m_walkingSpeed;
    QVector2D normalized(targetPoint - m_pos);
    normalized.normalize();
    m_pos = m_pos + normalized.toPoint() * movementSpeed;


}


void Enemy::doActivate()

{

    m_active = true;

}
void Enemy::getRemoved()
{


    foreach (Tower *attacker, m_attackedTowersList)
        attacker->targetKilled();
    // 通知game,此敌人已经阵亡
    m_game->removedEnemy(this);
}

void Enemy::getDamage(int damage)
{

    m_currentHp -= damage;

    // 阵亡,需要移除
    if (m_currentHp <= 0)
    {

m_game->awardGold(m_gold);
        getRemoved();
    }
}

void Enemy::getAttacked(Tower *attacker)
{
    m_attackedTowersList.push_back(attacker);
}

// 表明敌人已经逃离了攻击范围
void Enemy::gotLostSight(Tower *attacker)
{
    m_attackedTowersList.removeOne(attacker);
}



