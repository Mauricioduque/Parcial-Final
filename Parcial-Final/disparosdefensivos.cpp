#include "disparosdefensivos.h"

disparosDefensivos::disparosDefensivos(float rdetonacion,float Xd,float Hd,float Ho)
{
    x=Xd;
    y=Hd;
    direccion=-1;
    r=rdetonacion;
    Xd_=Xd;
    Hd_=Hd;
    Ho_=Ho;
    disDefensivos();
    Vx=vels[0];
    w=angs[0]*(pi/180);
    w=-w;
    Vy=Vx*tan(w);
    QTimer *timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(generar_Defensivos()));
    timer->start(int(1000*T));


}


QRectF disparosDefensivos::boundingRect() const
{
    return QRectF(-4,-4,8,8);
}


//Se grafica la bala y el sensor ofensivo
void disparosDefensivos::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(Qt::blue);
    painter->drawEllipse(boundingRect().center(),r,r);
    Q_UNUSED(widget)
    Q_UNUSED(option)
}

void  disparosDefensivos::disDefensivos()
{
    int impacto=0;
    float x=0, y=0;
    float Vxini,Vyini;
    int V0=0,Vini=5;
    for (V0=Vini;V0<=400;V0+=4){
        for (int angle=0;angle<90;angle++){
            for (int t=0;;t++){
                //Calculo de las velocidades en X y Y de la bala defensiva
                Vxini=V0*cos((angle)*pi/180);
                Vyini=V0*sin((angle)*pi/180);
                //Calculo de las posiciones en X y Y de la bala defensiva
                x=Xd_-Vxini*t;
                y=Hd_+ Vyini*t-(0.5*G*t*t);
                //Se verifica la condicion de impacto sobre el cañon ofensivo
                if(sqrt(pow((0-x),2)+pow((Ho_-y),2))<=r){
                    if(y<0) y=0;
                    //Se guardan los parametros de los disparos efectivos
                    angs[impacto]=angle;
                    vels[impacto]=V0;
                    ImprimirDatos(angle,V0,x,y,t);
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
    if (impacto==0) cout<<"No impacto sobre el canion Ofensivo"<<endl;
}


void disparosDefensivos::generar_Defensivos()
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

void disparosDefensivos::ImprimirDatos(float angle, float V0, float x, float y, float t)
{
    cout<<endl;
    cout<<"Impacto con un angulo de: "<<angle<<" grados"<<endl;
    cout<<"Impacto con una velocidad incial: "<<V0<<" m/s"<<endl;
    cout<<"Impacto con posicion en X: "<<x <<" m"<<endl;
    cout<<"Impacto con posicion en Y: "<<y <<" m"<<endl;
    cout<<"Con tiempo: "<<t<<" s"<<endl<<endl;
}


