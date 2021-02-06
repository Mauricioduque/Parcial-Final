#include "disparosdefensivos.h"

disparosDefensivos::disparosDefensivos(float rdetonacion,float Xd,float Hd,float Ho,int punto,QGraphicsItem *parent): QGraphicsItem(parent)
{
    x=Xd;
    y=Hd;
    direccion=-1;
    r=rdetonacion;
    Xd_=Xd;
    Hd_=Hd;
    Ho_=Ho;
    setFlag(ItemClipsToShape);
    sprite=QPixmap(":/imagenes/bala.png");
    sprite1=sprite.scaledToHeight(2*r);
    sprite2=sprite1.scaledToWidth(2*r);
    if (punto==2){
        disDefensivos();
        Vx=vels[0];
        w=angs[0]*(pi/180);
        w=-w;
        Vy=Vx*tan(w);
    }
    else if(punto==3){
        disDefensa(30,80);
            Vx=vels1[2]; //velocidad inicial en x
            w=angs1[2];
            w=-w;
            Vy=Vx*tan(w); //vy

    }
    QTimer *timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(generar_Defensivos()));
    timer->start(int(1000*T));


}


QRectF disparosDefensivos::boundingRect() const
{
    return QRectF(0,0,2*r,2*r);
}


//Se grafica la bala y el sensor ofensivo
void disparosDefensivos::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(0,0, sprite2, posSprite, 0,2*r, 2*r);
    setTransformOriginPoint(boundingRect().center());
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
            for (int t=2;;t++){
                //Calculo de las velocidades en X y Y de la bala defensiva
                Vxini=V0*cos((angle)*pi/180);
                Vyini=V0*sin((angle)*pi/180);
                //Calculo de las posiciones en X y Y de la bala defensiva
                x=Xd_-Vxini*(t-2);
                y=Hd_+ Vyini*(t-2)-(0.5*G*(t-2)*(t-2));
//                x=Xd_-Vxini*t;
//                y=Hd_+ Vyini*t-(0.5*G*t*t);
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

   y=y+Vy*t-(0.5*G*t*t); //tener en cuenta Vy y Vx para el angulo de disp
   Vy=Vy+G*t;
   x=x+Vx*t*direccion;
   setPos(x,y);
   cont++;
   if(cont%3==0){
       scene()->addEllipse(x,y,2*r,2*r);

   }



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

void disparosDefensivos::disDefensa(float anglei,float V2ini)
{

    int impacto;
    float x=0, y=0,t2;
    float t=0,thetaD,Vd;
    //intervalo de tiempo donde se puede disparar
    float t1=(2*V2ini*cos((anglei)*pi/180))/(Xd_-0.05*Xd_);
    x=V2ini*cos((anglei)*pi/180)*2;
    y=Ho_ +V2ini*sin((anglei)*pi/180)*2-(0.5*G*2*2);
    //se comprueba si en t=2 la bala ya tiene el radio de explosion cerca del objetivo
    if(distanciaEuclidiana(Xd_,x,Hd_,y)>Xd_*0.05){
        for(impacto=1;impacto<4;impacto++){
            //Se particiona el tiempo en donde se impactara a la bala ofensiva,segun los rangos establecidos 1<t<t1
            t2=t1+((1-t1)/4.0)*impacto;
            //se calcula el tiempo cuando chocan las balas teniendo el cuendo el radio de destruccion
            t=(Xd_-0.05*Xd_)*t2/(V2ini*cos((anglei)*pi/180));
            //se calcula la velocidad y el angulo para el cual se impacta en la bala ofensiva
            //a partir de las ec, cinematicas xo=xd y yd=yo
            thetaD=atan((Ho_-Hd_+V2ini*t*sin((anglei)*pi/180)-2*G*t+2*G)/(Xd_-V2ini*t*cos((anglei)*pi/180)));
            Vd=((Ho_-Hd_+V2ini*t*sin((anglei)*pi/180))-2*G*t+2*G)/((t-2)*sin(thetaD));
            angs1[impacto]=thetaD;
            vels1[impacto]=Vd;
            //se halla las posiciones a las que impacta la bala
            x=V2ini*cos((anglei)*pi/180)*t;
            y=Ho_ +V2ini*sin((anglei)*pi/180)*t-(0.5*G*t*t);
            ImprimirDatos(thetaD*180/pi,Vd,x,y,t);
            }
    }
}

float disparosDefensivos::distanciaEuclidiana(float x1, float x2, float y1, float y2)
{
    return sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
}

