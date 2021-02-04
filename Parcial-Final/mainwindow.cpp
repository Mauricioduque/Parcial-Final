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
    };

    //Se obtiene los valores de los doubleSpinbox
    Ho=ui->Ho->value();
    Hd=ui->Hd->value();
    Xd=ui->Xd->value();

    // Apartir de losdatos ingresados se grafica el frente de batalla
    baseCanionDefensivo=new QGraphicsRectItem;
    baseCanionDefensivo->setRect(Xd,referencia_Y(Hd-50,max_),50,Hd-50);
    scene-> addItem(baseCanionDefensivo);

    baseCanionOfensivo=new QGraphicsRectItem;
    baseCanionOfensivo->setRect(0,referencia_Y(Ho-50,max_),50,Ho-50);
    scene-> addItem(baseCanionOfensivo);

    canionOfensivo=new QGraphicsEllipseItem;
    canionOfensivo->setRect(0,referencia_Y(Ho,max_),50,50);
    scene-> addItem(canionOfensivo);

    canionDefensivo=new QGraphicsEllipseItem;
    canionDefensivo->setRect(Xd,referencia_Y(Hd,max_),50,50);
    scene-> addItem(canionDefensivo);

    reinicio=true;

}





//QRectF MainWindow::boundingRect() const {

//    return QRectF(0,0,50,50);
//}

//void MainWindow::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){

//    painter->setBrush(Qt::green);
//    painter->drawEllipse(boundingRect());
//    Q_UNUSED(widget)
//    Q_UNUSED(option)
//}


