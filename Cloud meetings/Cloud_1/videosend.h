#ifndef VIDEOSEND_H
#define VIDEOSEND_H

#include <QObject>
#include <QThread>
class VideoSend : public QThread
{
    Q_OBJECT
public:
    explicit VideoSend(QObject *parent = nullptr);

signals:

};

#endif // VIDEOSEND_H
