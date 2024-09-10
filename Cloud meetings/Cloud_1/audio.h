#ifndef AUDIO_H
#define AUDIO_H

#include <QObject>
#include <QThread>
#include <QDebug>

#include <QAudio>
#include <QAudioFormat>
#include <QAudioInput>
#include <QAudioOutput>
#include <QIODevice>
#include <QTcpSocket>
#include <QHostAddress>
#include <QDataStream>
class Audio : public QThread
{
    Q_OBJECT
public:
    explicit Audio(QTcpSocket *socket,QObject *parent = nullptr);
    ~Audio();

    QTcpSocket  *tcpSocket;
    QAudioInput *input;
    QIODevice *inputDevice;
    QAudioFormat format;
    QString id;

    struct video{
        int lens;
        char data[960];
    };
    void setaudioformat(int samplerta,int channelcount,int samplesize);
    void mystart();
    void mystop();
public slots:
    void onReadyRead();
signals:

};

#endif // AUDIO_H
