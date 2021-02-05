#include "disparosofensivos.h"

disparosOfensivos::disparosOfensivos(float rdetonacion,float Xd,float Hd,float Ho)
{
    x=10;
    y=Ho;
    direccion=1;
    r=rdetonacion;
    Xd_=Xd;
    Hd_=Hd;
    Ho_=Ho;
    disOfensivos();
    Vx=vels[0];
    w=angs[0]*(pi/180);
    w=-w;
    Vy=Vx*tan(w);
    QTimer *timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(generar_Ofensivos()));
    timer->start(int(1000*T));

}


QRectF disparosOfensivos::boundingRect() const
{
    return QRectF(-4,-4,8,8);
}


//Se grafica la bala y el sensor ofensivo
void disparosOfensivos::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(Qt::red);
    painter->drawEllipse(boundingRect().center(),r,r);
    painter->setBrush(Qt::yellow);
    painter->drawEllipse(boundingRect());
    Q_UNUSED(widget)
    Q_UNUSED(option)
}

void  disparosOfensivos::disOfensivos()
{
    int impacto=0;
    float x=0, y=0;
    float Vxini,Vyini;
    int V0=0,Vini=5;
    for (V0=Vini;V0<=500;V0+=4){
        for (int angle=0;angle<90;angle++){
            for (int t=0;;t++){
                //Calculo de las velocidades en X y Y de la bala ofensiva
                Vxini=V0*cos(angle*pi/180);
                Vyini=V0*sin(angle*pi/180);
                //Calculo de las posciones en X y Y de la bala ofensiva
                x=Vxini*t;
                y=Ho_+ Vyini*t-(0.5*G*t*t);
                //Se verifica la condicion de impacto sobre el cañon defensivo
                if(sqrt(pow((Xd_-x),2)+pow((Hd_-y),2))<=r){
                    if(y<0) y=0;
                    //Se guardan los parametros de los disparos efectivos
                    angs[impacto]=angle;
                    vels[impacto]=Vxini;
                    ImprimirDatos(angle,Vxini,x,y,t);
                    impacto+=1;
                    V0+=30;
                    break;
                }
                if(y<0)break;
            }
            if (impacto==3) break;
        }
        if (impacto==3) break;
    }
}

void disparosOfensivos::generar_Ofensivos()
{
    float t=4*T;

     //ECUACIONES DE MOVIMIENTO:Parábolico
     //Y(t)=y(t-1)+v(t-1)*T-g/2*T*T
     //V(t)=V(t-1)-g*T

   y=y+Vy*t+(0.5*G*t*t); //tener en cuenta Vy y Vx para el angulo de disp
   Vy=Vy+G*t;
   x=x+Vx*t*direccion;
   setPos(x,y);

}

void disparosOfensivos::ImprimirDatos(float angle, float V0, float x, float y, float t)
{
    cout<<endl;
    cout<<"Impacto con un angulo de: "<<angle<<" grados"<<endl;
    cout<<"Impacto con una velocidad incial: "<<V0<<" m/s"<<endl;
    cout<<"Impacto con posicion en X: "<<x <<" m"<<endl;
    cout<<"Impacto con posicion en Y: "<<y <<" m"<<endl;
    cout<<"Con tiempo: "<<t<<" s"<<endl<<endl;
}




