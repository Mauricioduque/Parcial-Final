#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QPainter>

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
    int max_=560;


private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QGraphicsRectItem *baseCanionDefensivo;
    QGraphicsRectItem *baseCanionOfensivo;
    QGraphicsEllipseItem *canionDefensivo;
    QGraphicsEllipseItem *canionOfensivo;


};
#endif // MAINWINDOW_H
