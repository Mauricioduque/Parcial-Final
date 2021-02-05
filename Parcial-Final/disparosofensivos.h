#ifndef DISPAROSOFENSIVOS_H
#define DISPAROSOFENSIVOS_H
#include <QGraphicsItem>
#include <QPainter>
#include <math.h>
#include <iostream>
#include <QTimer>

using namespace std;

class disparosOfensivos :public QObject,public QGraphicsItem
{
    Q_OBJECT
public:
    disparosOfensivos(float rdetonacion,float Xd,float Hd,float Ho);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,QWidget *widget);
    void disOfensivos();
    void ImprimirDatos(float angle,float V0,float x,float y,float t);

public slots:
    void generar_Ofensivos();

private:
    float r;     //radio;
    float Xd_=0;
    float Hd_;
    float Ho_=0;
    float w;
    float pi=3.1416;
    float G=9.81;
    float angs[2]={};
    float vels[2]={};
    float Vx,Vy=0;
    float  T=0.05;
    float x,y;
    float a,b,c;
    int direccion;



};

#endif // DISPAROSOFENSIVOS_H
