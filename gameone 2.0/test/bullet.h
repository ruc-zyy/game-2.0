#ifndef BULLET_H
#define BULLET_H

#include <QPoint>
#include <QSize>
#include <QPixmap>
#include <QObject>

class QPainter;
class Enemy;
class MainWindow;

class Bullet : QObject
{
    Q_OBJECT
    Q_PROPERTY(QPoint m_currentPos READ currentPos WRITE setCurrentPos)

public:
    Bullet(int type,QPoint startPos, QPoint targetPoint, int damage, Enemy *target,
           MainWindow *game, const QPixmap &sprite = QPixmap(":/image/fire3.png"),const QPixmap &sprite2 = QPixmap(":/image/fire2.png"));

    void draw(QPainter *painter) const;
    void move();
    void setCurrentPos(QPoint pos);
    QPoint currentPos() const;

private slots:
    void hitTarget();

private:
    int mtype;
    const QPoint	m_startPos;
    const QPoint	m_targetPos;
    const QPixmap	m_sprite;
    const QPixmap	m_sprite2;
    QPoint			m_currentPos;
    Enemy *			m_target;
    MainWindow *	m_game;
    int				m_damage;

    static const QSize ms_fixedSize;
};

#endif // BULLET_H
