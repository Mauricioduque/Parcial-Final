#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //se crea la escena odnde ocurrirán los sucesos
    scene = new QGraphicsScene;
    scene->setSceneRect(0,0,ui->graphicsView->width()-10,ui->graphicsView->height()-10);
    ui->graphicsView->setScene(scene);


}

MainWindow::~MainWindow()
{
    delete ui;
}

int MainWindow::referencia_Y(int y, int max)
{
    return max-y;
}


//configurar el frente de batalla
void MainWindow::on_pushButton_clicked()
{
    //Se verifica si va configurar el frente de batalla por n-esima vez
    if(reinicio){
        delete baseCanionDefensivo;
        delete baseCanionOfensivo;
        delete canionDefensivo;
        delete canionOfensivo;
        delete vulnerableDefensivo;
        delete vulnerableOfensivo;
    };

    //Se obtiene los valores de los doubleSpinbox
    Ho=ui->Ho->value();
    Hd=ui->Hd->value();
    Xd=ui->Xd->value();
    Rd=0.025*Xd;
    Ro=0.05*Xd;

//------------- Apartir de los datos ingresados se grafica el frente de batalla-----------
    //altura de los cañones
    baseCanionDefensivo=new QGraphicsRectItem;
    baseCanionDefensivo->setRect(Xd,referencia_Y(Hd-50,max_),50,Hd-50);
    scene-> addItem(baseCanionDefensivo);

    baseCanionOfensivo=new QGraphicsRectItem;
    baseCanionOfensivo->setRect(0,referencia_Y(Ho-50,max_),50,Ho-50);
    scene-> addItem(baseCanionOfensivo);

    //cañones
    canionOfensivo=new QGraphicsEllipseItem;
    canionOfensivo->setRect(0,referencia_Y(Ho,max_),50,50);
    canionOfensivo->setBrush(Qt::blue);
    scene-> addItem(canionOfensivo);

    canionDefensivo=new QGraphicsEllipseItem;
    canionDefensivo->setRect(Xd,referencia_Y(Hd,max_),50,50);
    canionDefensivo->setBrush(Qt::green);
    scene-> addItem(canionDefensivo);

    //regiones de vulnerabilidad de cada cañon
    vulnerableOfensivo=new QGraphicsEllipseItem;
    vulnerableOfensivo->setRect(-(Rd),referencia_Y(Ho+Rd,max_),2*(Rd+25),2*(Rd+25));
    QPen pen(Qt::red, 3, Qt::DashDotLine, Qt::RoundCap, Qt::RoundJoin);
    vulnerableOfensivo->setPen(pen);
    scene-> addItem(vulnerableOfensivo);

    vulnerableDefensivo=new QGraphicsEllipseItem;
    vulnerableDefensivo->setRect(Xd-Ro,referencia_Y(Hd+Ro,max_),2*(Ro+25),2*(Ro+25));
    QPen pen1(Qt::red, 3, Qt::DashDotLine, Qt::RoundCap, Qt::RoundJoin);
    vulnerableDefensivo->setPen(pen1);
    scene-> addItem(vulnerableDefensivo);

    reinicio=true;

}

//Se generan disparos ofensivos
void MainWindow::on_pushButton_2_clicked()
{
    bala=new disparosOfensivos(Ro,Xd,Hd,referencia_Y(Ho,max_));
    bala->setPos(0,referencia_Y(Ho,max_));
    scene->update();
    scene-> addItem(bala);
}


void MainWindow::on_pushButton_3_clicked()
{
    bala=new disparosOfensivos(Ro,Xd,Hd,referencia_Y(Ho,max_));
    bala->setPos(0,referencia_Y(Ho,max_));
    scene->update();
    scene-> addItem(bala);


    balaDe=new disparosDefensivos(Rd,Xd,referencia_Y(Hd,max_),Ho);
    balaDe->setPos(Xd,referencia_Y(Hd,max_));
    scene->update();
    scene-> addItem(balaDe);


}


void MainWindow::on_pushButton_4_clicked()
{
    scene = new QGraphicsScene;
    scene->setSceneRect(0,0,ui->graphicsView->width()-10,ui->graphicsView->height()-10);
    ui->graphicsView->setScene(scene);
}
