#include "disparosofensivos.h"

disparosOfensivos::disparosOfensivos(int rdetonacion,int max_)
{
    r=rdetonacion;
    max=max_;
}

QRectF disparosOfensivos::boundingRect() const
{
    return QRectF(-4,-4,8,8);
}



void disparosOfensivos::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(Qt::red);
    painter->drawEllipse(boundingRect().center(),r,r);
    painter->setBrush(Qt::yellow);
    painter->drawEllipse(boundingRect());
    Q_UNUSED(widget)
    Q_UNUSED(option)

}


