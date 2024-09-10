#include "audio.h"

Audio::Audio(QTcpSocket *socket,QObject *parent) : QThread(parent),tcpSocket(socket)
{

}

Audio::~Audio()
{
    tcpSocket->close();
    delete input;
    delete inputDevice;
}

void Audio::setaudioformat(int samplerta, int channelcount, int samplesize)
{
    format.setSampleRate(samplerta);
    format.setChannelCount(channelcount);
    format.setSampleSize(samplesize);
    format.setCodec("audio/pcm");
    format.setSampleType(QAudioFormat::SignedInt);
    format.setByteOrder(QAudioFormat::LittleEndian);
    input = new QAudioInput(format,this);
}

void Audio::mystart()
{
    qDebug()<<"audio begins to send";
    inputDevice = input->start();
    connect(inputDevice,SIGNAL(readyRead()),this,SLOT(onReadyRead()));
}

void Audio::mystop()
{
    qDebug()<<"audio ends!";
    input->stop();
}

void Audio::onReadyRead()
{
    video vp;
    memset(&vp, 0, sizeof(vp));
    // 从输入设备读取音频数据
    vp.lens = inputDevice->read(vp.data, sizeof(vp.data)); // 注意：这里可能需要调整以匹配你的音频数据大小
    QByteArray data;
    QDataStream out(&data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_0);
    out << vp.lens;
    out.writeRawData(vp.data,vp.lens);
    QString msg="AUDIO:"+id+";";
    tcpSocket->write(msg.toUtf8());
    tcpSocket->write(data);
}
