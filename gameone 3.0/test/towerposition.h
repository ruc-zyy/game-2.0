#ifndef TOWERPOSITION_H
#define TOWERPOSITION_H
#include<QMainWindow>
#include<tower.h>
#include"tower.h"
class Tower;
class TowerPosition
{
public:
    TowerPosition();
    TowerPosition(QPoint pos, const QPixmap &sprite = QPixmap(":/image/pos5.png"));
    void setHasTower(Tower *tower);
    bool hasTower() const;
    const QPoint centerPos() const;
    bool containPoint(const QPoint &pos) const;
    void draw(QPainter *painter) const;
    Tower       *m_tower=NULL;
    bool		t_hasTower;
    int numoft=0;
    QPoint		t_pos;
private:


    QPixmap		t_sprite;
    static const QSize t_fixedSize;
};

#endif // TOWERPOSITION_H
