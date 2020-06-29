#include "towerposition.h"
#include<QPainter>
TowerPosition::TowerPosition(){}
TowerPosition::TowerPosition(QPoint pos, const QPixmap &sprite):t_pos(pos),t_sprite(sprite),t_hasTower(false)
{

}
const QSize TowerPosition::t_fixedSize(50, 50);
const QPoint TowerPosition::centerPos() const{
    QPoint width_and_length(t_fixedSize.width()/2,t_fixedSize.height()/2);
    return t_pos+width_and_length;
}
bool TowerPosition::containPoint(const QPoint &pos) const{
    bool isXInHere = t_pos.x() < pos.x() && pos.x() < (t_pos.x() + t_fixedSize.width());
    bool isYInHere = t_pos.y() < pos.y() && pos.y() < (t_pos.y() + t_fixedSize.height());
    return isXInHere && isYInHere;

}
bool TowerPosition::hasTower() const{
    return t_hasTower;
}
void TowerPosition::setHasTower(Tower *tower){
    t_hasTower=true;
    m_tower=tower;
}
void TowerPosition::draw(QPainter *painter) const

{

    painter->drawPixmap(t_pos.x(), t_pos.y(), t_sprite);

}
