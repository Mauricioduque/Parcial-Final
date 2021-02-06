#ifndef DISPAROSDEFENSIVOS_H
#define DISPAROSDEFENSIVOS_H

#include <QGraphicsItem>
#include <QPainter>
#include <math.h>
#include <iostream>
#include <QTimer>
#include <QThread>
#include <QGraphicsScene>


using namespace std;

class disparosDefensivos :public QObject,public QGraphicsItem
{
    Q_OBJECT
public:
    disparosDefensivos(float rdetonacion,float Xd,float Hd,float Ho,int punto,QGraphicsItem *parent= nullptr);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,QWidget *widget);
    void disDefensivos();
    void ImprimirDatos(float angle,float V0,float x,float y,float t);
    void disDefensa(float anglei,float V2ini);
    float distanciaEuclidiana(float x1,float x2,float y1,float y2);
public slots:
    void generar_Defensivos();

private:
    float r;     //radio;
    float Xd_=0;
    float Hd_=0;
    float Ho_;
    float w;
    float pi=3.1416;
    float G=9.81;
    float angs[2]={};
    float vels[2]={};
    float Vx,Vy;
    float  T=0.05;
    float x,y;
    int direccion;
    int cont=0;
    float angs1[4]={};
    float vels1[4]={};
    QPixmap sprite;
    QPixmap sprite1;
    QPixmap sprite2;
    int posSprite;
};

#endif // DISPAROSDEFENSIVOS_H
