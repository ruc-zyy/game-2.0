#ifndef ENEMY_H
#define ENEMY_H

#include <QObject>
#include <QPoint>
#include <QSize>
#include <QPixmap>
#include <QLabel>
#include <QMovie>

class WayPoint;
class QPainter;
class MainWindow;
class Tower;
class Enemy:public QObject
{Q_OBJECT
public:
    Enemy(int num,int _type,QPoint pos,WayPoint *startWayPoint, MainWindow *game);
    void draw(QPainter *painter,QLabel **enemylabel);
    void move();
    void getDamage(int damage);
    void getRemoved();
    void getAttacked(Tower *attacker);
    void gotLostSight(Tower *attacker);
    int no;
    QPoint			m_pos;
    int type;
    WayPoint *		m_destinationWayPoint;
    QList<Tower *>	m_attackedTowersList;
public slots:
    void doActivate();
private:
    int m_gold;
   QMovie     *m_pic;
    bool			m_active;
    int				m_maxHp;
    int				m_currentHp;
    double			m_walkingSpeed;
    MainWindow *	m_game;
    static   const QSize ms_fixedSize;
};

#endif // ENEMY_H
