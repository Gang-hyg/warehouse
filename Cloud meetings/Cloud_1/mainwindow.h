#ifndef MAINWINDOW_H
#define MAINWINDOW_H
//客户端
#include <QMainWindow>
#include <QTcpSocket>
#include <QHostAddress>
#include <QLabel>
#include <QThread>
#include <QMessageBox>
#include <opencv2/opencv.hpp>
#include <QTimer>
#include <QBuffer>
#include "opencv2/imgproc/types_c.h"
#include <QPixmap>
#include <QImageReader>
#include <QFileDialog>
#include "audio.h"
#include "audio_reception.h"
#include "video_reception.h"
using namespace cv;
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_Join_clicked();

    void on_pushButton_Create_clicked();

    void on_pushButton_Quit_clicked();

    void on_pushButton_Connect_clicked();

    void on_pushButton_message_clicked();

    void on_pushButton_video_clicked();

    void on_pushButton_mute_clicked();

    void on_pushButton_disconnect_clicked();

    void VideoSend();

    void on_pushButton_disvideo_clicked();

    void on_horizontalSlider_valueChanged(int value);

    void setImage(QImage image);
signals:
    void videomessage(QByteArray data);
private:
    Ui::MainWindow *ui;
    QTcpSocket *m_tcp;
    QLabel *m_status;
    QString id;
    QTimer fps_timer;
    VideoCapture camera;
    Audio *audio;
    Audio_Reception *reception;
    Video_reception *v;
};
#endif // MAINWINDOW_H
