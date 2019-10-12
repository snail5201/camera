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

    QPainter painter(this);
    painter.setWindow(0,0,300,300);

    QPen pen;
    pen.setWidth(1);
    pen.setColor(mColorline);
    pen.setStyle(Qt::SolidLine);
    pen.setCapStyle(Qt::FlatCap);   //不覆盖直线终点的方形直线末端。
    pen.setJoinStyle(Qt::BevelJoin);//连接样式设置
    painter.setPen(pen);

    painter.drawLine(155,150,145,150);      //横
    painter.drawLine(150,157,150,143);       //纵

    QBrush brush;
    brush.setColor(mColorBack);
    brush.setStyle(Qt::SolidPattern);
    //使用画刷
    painter.setBrush(brush);
    //定义四个点
    static const QPointF points[4] = {
        QPointF(0, 0),
        QPointF(0, 300),
        QPointF(300, 300),
        QPointF(300, 0)
    };

    //边框
    pen.setColor(mColoroutline);
    painter.setPen(pen);
    painter.drawPolygon(points,4);

    //使用四个点绘制多边形
    painter.drawPolygon(points, 4);
}

void QmyCursor::disp()
{
    update();
}

void QmyCursor::changelinecolor(bool flag,bool screen_open)
{
    if(flag == true && screen_open == true) //屏幕打开，开启光标
    {
        mColorline = Qt::green;
        mColorBack = Qt::transparent;
        mColoroutline = Qt::transparent;
    }
    else if(flag == false && screen_open == true)  //屏幕打开，光标关闭
    {
        mColorline = Qt::transparent;
        mColorBack = Qt::transparent;
        mColoroutline = Qt::transparent;
    }
    else if(flag == true && screen_open == false)  //屏幕关闭，光标打开
    {
        mColorline = Qt::black;
        mColorBack = Qt::black;
        mColoroutline = Qt::black;
    }
    else if(flag == true && screen_open == false)  //屏幕关闭，光标关闭
    {
        mColorline = Qt::black;
        mColorBack = Qt::black;
        mColoroutline = Qt::black;
    }
}

void QmyCursor::close_screen(bool flag)
{
    if(flag)
    {
        mColorline = Qt::black;
        mColorBack = Qt::black;
        mColoroutline = Qt::black;
    }
    else
    {
        mColorline = Qt::transparent;
        mColorBack = Qt::transparent;
        mColoroutline = Qt::transparent;
    }
}
