﻿#ifndef QCAMERAVIEWFINDER_H
#define QCAMERAVIEWFINDER_H

#include<QVideoWidget>
#include<QPainter>

class QCameraViewfinder : public QVideoWidget
{
public:
    QCameraViewfinder(QWidget *parent = nullptr);
};

class QmyCursor : public QWidget
{
    //Q_OBJECT
public:
    explicit QmyCursor(QWidget *parent = nullptr);
    void disp();
    void changelinecolor(bool flag,bool screen_open);
    void close_screen(bool flag);
private:
    QColor mColorBack=Qt::transparent;   //背景颜色为透明
    QColor mColorline=Qt::green;
    QColor mColoroutline;                //边框
protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
signals:

public slots:
};

#endif // QCAMERAVIEWFINDER_H
