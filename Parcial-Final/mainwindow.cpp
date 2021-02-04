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
    baseCanionDefensivo=new QGraphicsRectItem;
    baseCanionDefensivo->setRect(0,referencia_Y(0,max_)-100,50,100);
    scene-> addItem(baseCanionDefensivo);

    baseCanionOfensivo=new QGraphicsRectItem;
    baseCanionOfensivo->setRect(800,referencia_Y(0,max_)-100,50,100);
    scene-> addItem(baseCanionOfensivo);

    canionOfensivo=new QGraphicsEllipseItem;
    canionOfensivo->setRect(0,referencia_Y(150,max_),50,50);
    scene-> addItem(canionOfensivo);

    canionDefensivo=new QGraphicsEllipseItem;
    canionDefensivo->setRect(800,referencia_Y(150,max_),50,50);
    scene-> addItem(canionDefensivo);





}

MainWindow::~MainWindow()
{
    delete ui;
}

int MainWindow::referencia_Y(int y, int max)
{
    return max-y;
}

QRectF MainWindow::boundingRect() const {

    return QRectF(0,0,50,50);
}

void MainWindow::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){

    painter->setBrush(Qt::green);
    painter->drawEllipse(boundingRect());
    Q_UNUSED(widget)
    Q_UNUSED(option)
}
