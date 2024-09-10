#ifndef VIDEO_RECEPTION_H
#define VIDEO_RECEPTION_H

#include <QObject>
#include <QThread>
#include <QTimer>
#include <QImageReader>
#include <QPixmap>
#include <QBuffer>
#include <opencv2/opencv.hpp>
#include "opencv2/imgproc/types_c.h"
using namespace cv;
class Video_reception : public QThread
{
    Q_OBJECT
public:
    explicit Video_reception(QObject *parent = nullptr);
    ~Video_reception();
    void video_receive_show(QByteArray data);
signals:
    void finsh(QImage image);
private:
    QImage image;
};

#endif // VIDEO_RECEPTION_H
