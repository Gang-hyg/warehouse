#ifndef AUDIO_RECEPTION_H
#define AUDIO_RECEPTION_H

#include <QThread>
#include <QAudioFormat>
#include <QAudioOutput>
#include <QMutex>
#include <QMutexLocker>
#include <QByteArray>
//这是接收线程
#include <QTcpServer>
#include <QTcpSocket>
#include <QHostAddress>
#include <QNetworkInterface>
#include <QDataStream>
#include <QDebug>
#define MAX_AUDIO_LEN 960000//如果接收缓冲区大于这个数值就剪掉
#define FRAME_LEN_60ms 960//每一个语音帧长度是960字节
class Audio_Reception : public QThread
{
    Q_OBJECT
public:
    explicit Audio_Reception(QObject *parent = nullptr);
    ~Audio_Reception();
    void addAudioBuffer(char * pData,int len);
    void cleanAllAudioBuffer(void);
    void setCurrentSampleInfo(int sampleRate,int sampleSize,int channelCount);
    virtual void run(void) override;
    void setCurrentVolumn(qreal volumn);
    void stop();
    QByteArray data;
signals:
private:
    QAudioOutput *m_OutPut = nullptr;
    QIODevice *m_AudioIO = nullptr;
    QByteArray m_PCMDataBuffer;
    int m_CurrentPlayIndex = 0;
    QMutex m_Mutex;
    volatile bool m_IsPlaying = true;
    struct video{
        int lens;
        char data[960];
    };
public slots:
    void readyReadSlot();
};

#endif // AUDIO_RECEPTION_H
