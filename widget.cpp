#include "widget.h"
#include <QPainter>
#include <QLine>
#include <QPainterPath>

Widget::Widget(QWidget *parent)
    : QWidget{parent}
{
    setMouseTracking(1);

    points = new QPixmap(rect().width(),rect().height());
    points->fill(Qt::transparent);

    bgimage = new QPixmap(rect().width(),rect().height());
    bgimage->fill();

    prev.rx() = NULL;
    prev.ry() = NULL;
}

void Widget::paintEvent(QPaintEvent *){
    if(isDrawing){
        QPointF temp(mapFromGlobal(cursor().pos()));
        QPainter painter(points);
        if(tool == "eraser"){
            painter.setCompositionMode(QPainter::CompositionMode_Clear);
        }
        painter.setPen(QPen(color,size,Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin));
        if(prev.isNull()){
            painter.drawPoint(temp);
            prev = temp;
        }
        painter.drawLine(temp,prev);
        prev = temp;
    }
    QPainter ppainter(this);
    ppainter.drawPixmap(rect(), *bgimage);
    ppainter.drawPixmap(rect(), *points);
    QPainter curpainter(this);
    curpainter.setPen(QPen(Qt::lightGray,1));
    curpainter.drawEllipse(mapFromGlobal(cursor().pos()),size/2,size/2);
}

void Widget::mousePressEvent(QMouseEvent*){
    isDrawing = 1;
    update();
}

void Widget::mouseMoveEvent(QMouseEvent*){
//    if(isDrawing){
//        update();
//    }
    update();
}

void Widget::mouseReleaseEvent(QMouseEvent*){
    prev.rx() = NULL;
    prev.ry() = NULL;
    isDrawing = 0;
}

void Widget::clear(){
    points = new QPixmap(rect().width(),rect().height());
    points->fill(Qt::transparent);
    prev.rx() = NULL;
    prev.ry() = NULL;
    update();
}

void Widget::saveImage(QString filename){
    QPixmap* temp = new QPixmap(*points);
    QPainter p(temp);
    p.drawPixmap(points->rect(), *bgimage);
    p.drawPixmap(points->rect(), *points);
    temp->save(filename);
}






