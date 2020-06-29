#ifndef TOWER_H
#define TOWER_H
#include <QTimer>
#include <QPoint>
#include <QSize>
#include <QPixmap>
#include <QObject>
#include<QPainter>
#include<QLabel>
class QPainter;
class Enemy;
class MainWindow;
class QTimer;
#include "bullet.h"
class Tower:public QObject
{
Q_OBJECT
public:
   Tower(int t,QPoint pos,int n,MainWindow *game,const QPixmap &sprite=QPixmap(":/image/tower0.png"));
   void draw(QLabel **towerlabel,QMovie *pic,QPainter *painter) const;
   QPoint m_pos;
   int no;
   int m_cost=60;
   int m_fireRate;
   void checkEnemyInRange();
   void targetKilled();
   void attackEnemy();
   void chooseEnemyForAttack(Enemy *enemy);
   void removeBullet();
   void damageEnemy();
   void lostSightOfEnemy();
   void starttimer();
   void up();
   int type;
   QTimer *		m_fireRateTimer=new QTimer(this);
   Enemy *			m_chooseEnemy;
private slots:
   void shootWeapon();
   void type2attack();
private:
   int level=1;
   bool m_attacking;
   int m_attackrange;
   int m_damage;
   QPixmap m_sprite;
   QPixmap m_sprite2=QPixmap(":/image/lv2tower2.png");
   MainWindow *	m_game;
   QList<Enemy *> m_enemyList() const;
};

#endif // TOWER_H
