#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QCamera>
#include<QLabel>
#include<QCameraImageCapture>
#include<QPainter>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    QCamera *curCamera  = Q_NULLPTR;
    QCameraImageCapture *imageCapture;  //抓图
    QLabel *LabCameraState;
    QList<QCameraInfo>  cameras;
    QCamera *cameralist[2];
    int index;
    void inicamera(QList<QCameraInfo>  cameras);   //初始化
    void iniImageCapture();

private slots:
    void on_cameraStateChanged(QCamera::State state);
    void on_action_open_triggered();

    void on_action_close_triggered();
#if 1
    void on_imageReadyForCapture(bool ready);
    void on_imageCapture(int id, const QImage &preview);
    void on_imageSaved(int id,const QString &fileName);

    void on_action_capture_triggered();
#endif
    void on_refresh_clicked();

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
