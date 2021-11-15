#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QMenu>
#include <QLabel>
#include <QDebug>
#include <QMouseEvent>
#include <QPoint>
#include <QPainter>
#include <QPen>
#include <QPainterPath>
#include <QtCore/qmath.h>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
public:
    explicit MainWindow(QWidget *parent = 0);

    ~MainWindow();
    void paintEvent(QPaintEvent*);
    void mousePressEvent(QMouseEvent *ev);
private:

    Ui::MainWindow *ui;
    int nbPoints=0;
    QPoint points[2];
    int xLeft;

    int xRight;

    int yTop;

    int yBottom;
    int borderx;

    int bordery;

    void calculateBorderPoint(int x0, int y0, int x1, int y1);

    int calculateCode(int x, int y);
};

#endif // MAINWINDOW_H
