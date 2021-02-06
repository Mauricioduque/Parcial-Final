#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QPainter>
#include "disparosofensivos.h"
#include "disparosdefensivos.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
     QRectF boundingRect() const;
     void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    int referencia_Y(int y, int max);



private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QGraphicsRectItem *baseCanionDefensivo;
    QGraphicsRectItem *baseCanionOfensivo;
    QGraphicsEllipseItem *canionDefensivo;
    QGraphicsEllipseItem *canionOfensivo;
    QGraphicsEllipseItem *vulnerableDefensivo;
    QGraphicsEllipseItem *vulnerableOfensivo;
    disparosOfensivos *bala;
    disparosDefensivos *balaDe;
    float Ho;
    float Hd;
    float Xd;
    int max_=560;
    float Rd;
    float Ro;
    float ang;
    float vi;
    bool reinicio=false;


};
#endif // MAINWINDOW_H
