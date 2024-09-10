#include "audioplauthread.h"

AudioPlauThread::AudioPlauThread(QTcpSocket *socket,QObject *parent) : QThread(parent),tcpSocket(socket)
{
    m_PCMDataBuffer.clear();
    connect(socket,SIGNAL(readyRead()),this,SLOT(readyReadSlot()));
//    m_s=new QTcpServer(this);
//    QString msg="8899";
//    unsigned short port = msg.toUShort();
//    m_s->listen(QHostAddress::Any,port);
//    connect(m_s,&QTcpServer::newConnection,this,&AudioPlauThread::onNewConnection);
}
AudioPlauThread::~AudioPlauThread()
{
    tcpSocket->close();
    delete m_OutPut;
    delete m_AudioIO;
}

void AudioPlauThread::addAudioBuffer(char *pData, int len)
{
    QMutexLocker locker(&m_Mutex);
    m_PCMDataBuffer.append(pData,len);
}

void AudioPlauThread::cleanAllAudioBuffer(void)
{
    QMutexLocker locker(&m_Mutex);
    m_CurrentPlayIndex = 0;
    m_PCMDataBuffer.clear();
    m_IsPlaying = false;
}

void AudioPlauThread::setCurrentSampleInfo(int sampleRate, int sampleSize, int channelCount)
{
    QMutexLocker locker(&m_Mutex);
    QAudioFormat nFormat;
    nFormat.setSampleRate(sampleRate);
    nFormat.setSampleSize(sampleSize);
    nFormat.setChannelCount(channelCount);
    nFormat.setCodec("audio/pcm");
    nFormat.setSampleType(QAudioFormat::SignedInt);
    nFormat.setByteOrder(QAudioFormat::LittleEndian);
    if(m_OutPut != nullptr)delete m_OutPut;
    m_OutPut = new QAudioOutput(nFormat);
    m_AudioIO = m_OutPut->start();
}

void AudioPlauThread::run(void)
{
    while(!this->isInterruptionRequested())
    {
        if(!m_IsPlaying)
        {
            break;
        }
        QMutexLocker locker(&m_Mutex);
        if(m_PCMDataBuffer.size()<m_CurrentPlayIndex + FRAME_LEN_60ms){
            continue;
        }
        else{
            char *writeData = new char[FRAME_LEN_60ms];
            memcpy(writeData,&m_PCMDataBuffer.data()[m_CurrentPlayIndex],FRAME_LEN_60ms);
            m_AudioIO->write(writeData,FRAME_LEN_60ms);
            m_CurrentPlayIndex +=FRAME_LEN_60ms;
            qDebug()<<m_CurrentPlayIndex;
            delete []writeData;
            if(m_CurrentPlayIndex > MAX_AUDIO_LEN){
                m_PCMDataBuffer = m_PCMDataBuffer.right(m_PCMDataBuffer.size()-MAX_AUDIO_LEN);
                m_CurrentPlayIndex -= MAX_AUDIO_LEN;
            }
        }
    }
    m_PCMDataBuffer.clear();
    qDebug()<<"audio receiver stop!";
}

void AudioPlauThread::setCurrentVolumn(qreal volumn)
{
    m_OutPut->setVolume(volumn);
}

void AudioPlauThread::stop()
{
    tcpSocket->close();
    m_OutPut->stop();
    cleanAllAudioBuffer();
}

void AudioPlauThread::readyReadSlot()
{
    qDebug()<<"audio is being received..."<<endl;
    QByteArray data = tcpSocket->readAll();
    int startIndex = data.indexOf("AUDIO:");
    int endIndex = data.indexOf(';', startIndex);
    QByteArray receivedData = data.mid(endIndex + 1);
    QDataStream in(&receivedData,QIODevice::ReadOnly);
    in.setVersion(QDataStream::Qt_5_0);
    int dataSize;
    in >>dataSize;
    if (dataSize <= 0 || dataSize > receivedData.size() - sizeof(int)) {
        qDebug() << "Invalid or incomplete audio data received";
        return;
    }
     in.skipRawData(sizeof(int));
     // 分配足够的内存来存储音频数据
         char audioData[960]; // 假设最大为960字节
         memset(audioData, 0, sizeof(audioData));

         // 读取音频数据
         if (dataSize <= sizeof(audioData)) {
             in.readRawData(audioData, dataSize);

             // 将读取的数据封装到一个video结构体中（仅为了与addAudioBuffer函数兼容）
             video vp;
             vp.lens = dataSize;
             memcpy(vp.data, audioData, dataSize);

             // 调用函数处理音频数据
             addAudioBuffer(vp.data, vp.lens);
         } else {
             qDebug() << "Audio data is larger than expected";
         }
//    video vp;
//    memset(&vp,0,sizeof (vp));
//    QDataStream in(tcpSocket);
//    in>>vp;
//    addAudioBuffer(vp.data,vp.lens);
}

