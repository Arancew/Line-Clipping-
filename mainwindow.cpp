#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"qpainter.h"
#include <stdio.h>
#include <QMessageBox>
#include <math.h>
MainWindow::MainWindow(QWidget *parent): QMainWindow(parent),ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    setWindowTitle("直线裁剪");
    xLeft = 100;
    xRight = 300;

    yTop = 100;

    yBottom = 300;

    borderx = 0;

    borderx = 0;

}
MainWindow::~MainWindow()

{

    delete ui;

}
void MainWindow::mousePressEvent(QMouseEvent *ev)
{
    if(ev->button()==Qt::LeftButton)
    {

        if (nbPoints < 2)
        {

            points[nbPoints]=ev->pos();
            nbPoints++;
        }
        else
        {
            nbPoints=0;
            points[nbPoints]=ev->pos();
            nbPoints++;
        }
    }
    update();
}
void MainWindow::paintEvent(QPaintEvent*)

{
    QPainter painter(this);

    QPen pen;

    pen.setColor(Qt::red);

    painter.setPen(pen);

    painter.fillRect(QRect(xLeft,yTop,(xRight - xLeft),(yBottom - yTop)),Qt::yellow);
    if(nbPoints ==1)
    {
        painter.drawPoint(points[0]);
        return;
    }
    pen.setColor(Qt::black);

    painter.setPen(pen);
    int x0,y0,x1,y1;

    x0=points[0].x();

    y0=points[0].y();

    x1=points[1].x();

    y1=points[1].y();
    if(x1<x0)
    {
        int tmp=x0;
        x0=x1;
        x1=tmp;
        tmp=y0;
        y0=y1;
        y1=tmp;

    }
    painter.drawLine(x0,y0,x1,y1);
    int code0 = calculateCode(x0, y0);

    int code1 = calculateCode(x1, y1);

    if (code0 == 0 && code1 == 0)

    {

    }

    else if ((code0 & code1) !=0)

    {

        x0 = 0;

        y0 = 0;

        x1 = 0;

        y1 = 0;

    }

    else if (code0 == 0)

    {

        calculateBorderPoint(x0, y0, x1, y1);

        x1 = borderx;

        y1 = bordery;

    }
    else if (code1 == 0)

    {
        calculateBorderPoint(x0, y0, x1, y1);

        x0 = borderx;

        y0 = bordery;

    }
    else

    {
        bool repeating = true;

        while (repeating)
        {
            int midx = (int)((x0 + x1) / 2.0 + 0.5);

            int midy = (int)((y0 + y1) / 2.0 + 0.5);

            int codemid = calculateCode(midx, midy);

            if (codemid == 0)

            {
                calculateBorderPoint(x0, y0, midx, midy);

                x0 = borderx;

                y0 = bordery;

                calculateBorderPoint(midx, midy, x1, y1);

                x1 = borderx;

                y1 = bordery;
                repeating = false;
            }
            else if ((code0 & codemid) != 0)

            {
                x0 = midx;

                y0 = midy;

            }
            else if ((code1 & codemid) !=0)

            {
                x1 = midx;

                y1 = midy;

            }
        }
    }
    painter.setPen(QPen(Qt::red, 3));
    painter.drawLine(x0,y0,x1,y1);
}

void MainWindow::calculateBorderPoint(int x0, int y0, int x1, int y1)

{

    int code0 = calculateCode(x0, y0);

    int code1 = calculateCode(x1, y1);

    if (fabs(x0 - x1) <= 1)

    {

        if (code0 == 0)

        {

            borderx = x0;

            bordery = y0;

        }

        else if (code1 == 0)

        {

            borderx = x1;

            bordery = y1;

        }

        else

        {

            borderx = 0;

            bordery = 0;

        }

    }

    else

    {

        int midx = (int)((x0 + x1) / 2.0 + 0.5);

        int midy = (int)((y0 + y1) / 2.0 + 0.5);

        int codemid = calculateCode(midx, midy);



        if (((code0 & codemid) != 0) || (code0 == 0 && codemid == 0))

        {

            calculateBorderPoint(midx, midy, x1, y1);

        }

        else if (((code1 & codemid) !=0) || (code1 == 0 && codemid == 0))

        {

            calculateBorderPoint(x0, y0, midx, midy);

        }

    }

}

int MainWindow::calculateCode(int x, int y)

{

    int code = 0b0000;

    code |= y < yTop ? 0b1000 : 0;

    code |= y > yBottom ? 0b0100 : 0;

    code |= x > xRight ? 0b0010 : 0;

    code |= x < xLeft ? 0b0001 : 0;

    return code;

}
