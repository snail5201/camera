#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QCameraInfo>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //将QLabel加入到静态状态栏中
    LabCameraState = new QLabel(QStringLiteral("摄像头状态："));
    LabCameraState->setMinimumWidth(150);
    ui->statusBar->addWidget(LabCameraState);

    cameras = QCameraInfo::availableCameras();
    if(cameras.size()>0)
    {
        inicamera(cameras);
        //iniImageCapture();
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::inicamera(QList<QCameraInfo>  cameras)
{
   // QCameraInfo curCameraInfo = QCameraInfo::defaultCamera();

    for(int i=0;i<cameras.size();i++)
    {
        ui->comboBox_camera->addItem(cameras[i].description());
        ui->comboBox_camera->setCurrentIndex(i);
    }

    for(int i=0;i<cameras.size();i++)
    {
        cameralist[i] = new QCamera(cameras[i],this);    //创建摄像头对象
       // cameralist[i]->viewfinderSettings();    //返回相机正在使用的取景器设置。如果相机不支持取景器设置，则始终返回空值
    }

#if 0
    curCamera = new QCamera(curCameraInfo,this);    //创建摄像头对象
    curCamera->viewfinderSettings();    //返回相机正在使用的取景器设置。如果相机不支持取景器设置，则始终返回空值
    curCamera->setViewfinder(ui->widget);       //设置预览框
#endif
#if 0
    //设置摄像头输出模式 这里要注意是摄像头是否支持修改参数信息
    QCameraViewfinderSettings viewfinderSettings;   //创建取景器对象,用于显示摄像头的数据
    viewfinderSettings.setResolution(640,480);
    viewfinderSettings.setMinimumFrameRate(15);
    viewfinderSettings.setMaximumFrameRate(30);
    curCamera->setViewfinderSettings(viewfinderSettings);
#endif


    connect(cameralist[0],SIGNAL(stateChanged(QCamera::State)),
            this,SLOT(on_cameraStateChanged(QCamera::State)));
    connect(cameralist[1],SIGNAL(stateChanged(QCamera::State)),
            this,SLOT(on_cameraStateChanged(QCamera::State)));
}

void MainWindow::on_cameraStateChanged(QCamera::State state)
{
    switch (state) {
    case QCamera::UnloadedState:
        LabCameraState->setText(QStringLiteral("摄像头状态：未发现设备"));
        break;
    case QCamera::LoadedState:
        LabCameraState->setText(QStringLiteral("摄像头状态：已发现设备"));
        break;
    case QCamera::ActiveState:
        LabCameraState->setText(QStringLiteral("摄像头状态：正在运行"));
    }

    ui->action_open->setEnabled(state!=QCamera::ActiveState);
    ui->action_close->setEnabled(state==QCamera::ActiveState);
}

void MainWindow::on_action_open_triggered()
{
    int index = ui->comboBox_camera->currentIndex();
    ui->comboBox_camera->setEnabled(false);
    cameralist[index]->setViewfinder(ui->widget);//设置预览框，设置基于QVideoWidget的相机取景器。先前设置的取景器已分离。放在此处时刷新预览框，因为有多个预览框，一旦刷新就会置顶当前预览框
    cameralist[index]->start();
}

void MainWindow::on_action_close_triggered()
{
    ui->comboBox_camera->setEnabled(true);
    int index = ui->comboBox_camera->currentIndex();
    cameralist[index]->stop();
}

/****************************************************************/
#if 1
void MainWindow::iniImageCapture()
{
    index = ui->comboBox_camera->currentIndex();
    imageCapture = new QCameraImageCapture(cameralist[index],this);
    imageCapture->setBufferFormat(QVideoFrame::Format_Jpeg);
    imageCapture->setCaptureDestination(QCameraImageCapture::CaptureToFile);

    connect(imageCapture,SIGNAL(readyForCaptureChanged(bool)),  //相机拍摄状态改变时发射此信号
            this,SLOT(on_imageReadyForCapture(bool)));
    connect(imageCapture,SIGNAL(imageCaptured(int,const QImage &)), //捕获到帧时发射此信号
            this,SLOT(on_imageCapture(int,const QImage &)));
    connect(imageCapture,SIGNAL(imageSaved(int,const QString &)),   //将捕获的帧保存到文件中时发射此信号
            this,SLOT(on_imageSaved(int,const QString &)));
}

void MainWindow::on_imageReadyForCapture(bool ready)
{
        //ui->action_capture->setEnabled(ready);
    Q_UNUSED(ready);
}

void MainWindow::on_imageCapture(int id,const QImage &preview)
{
    //显示抓取的图片
    Q_UNUSED(id);
    QImage scaledImage = preview.scaled(ui->label_capture->size(),  //返回缩放到由给定大小定义的矩形的图像副本。
                                        Qt::KeepAspectRatio,Qt::SmoothTransformation);
    ui->label_capture->setPixmap(QPixmap::fromImage(scaledImage));
}

void MainWindow::on_imageSaved(int id,const QString &fileName)
{
    //保存图片
    Q_UNUSED(id);
    ui->label_imageinfo->setText(QStringLiteral("图片保存为：")+fileName);
}

void MainWindow::on_action_capture_triggered()
{
    iniImageCapture();
    if(cameralist[index]->captureMode()!=QCamera::CaptureStillImage)
        cameralist[index]->setCaptureMode(QCamera::CaptureStillImage);  //将相机更改为静态帧模式

    imageCapture->capture();    //捕捉图片并保存到文件中，并发射imageCaptured()、imageSaved() 信号
}
#endif
