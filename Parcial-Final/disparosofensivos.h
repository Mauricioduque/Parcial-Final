#ifndef DISPAROSOFENSIVOS_H
#define DISPAROSOFENSIVOS_H
#include <QGraphicsItem>
#include <QPainter>

class disparosOfensivos :public QGraphicsItem
{
public:
    disparosOfensivos(int r_,int max_);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,QWidget *widget);

private:
    int r;     //radio;
    int max;

};

#endif // DISPAROSOFENSIVOS_H
