#include "qcameraviewfinder.h"

QCameraViewfinder::QCameraViewfinder(QWidget *parent):QVideoWidget(parent)
{

}

/************************************************************************/

//绘制光标
QmyCursor::QmyCursor(QWidget *parent) : QWidget(parent)
{

}

void QmyCursor::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);		//添加this，否则报错"....not active"
    painter.setWindow(0,0,20,20);

    QPen pen;
    pen.setWidth(1);
    pen.setColor(mColorline);
    pen.setStyle(Qt::SolidLine);
    pen.setCapStyle(Qt::FlatCap);   //不覆盖直线终点的方形直线末端。
    pen.setJoinStyle(Qt::BevelJoin);//连接样式设置
    painter.setPen(pen);

    QBrush brush;
    brush.setColor(mColorBack);
    brush.setStyle(Qt::SolidPattern);
    painter.setBrush(brush);

    painter.drawLine(0,10,20,10);
    painter.drawLine(10,0,10,20);
}

void QmyCursor::disp()
{
    update();	//与repaint()用法一样，进一步调用paintEvent()虚函数
}
