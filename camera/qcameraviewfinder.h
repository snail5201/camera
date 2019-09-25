#ifndef QCAMERAVIEWFINDER_H
#define QCAMERAVIEWFINDER_H

#include<QVideoWidget>

class QCameraViewfinder : public QVideoWidget
{
public:
    QCameraViewfinder(QWidget *parent = nullptr);
};

#endif // QCAMERAVIEWFINDER_H
