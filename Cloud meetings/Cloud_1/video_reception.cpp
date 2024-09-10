#include "video_reception.h"

Video_reception::Video_reception(QObject *parent) : QThread(parent)
{

}

Video_reception::~Video_reception()
{

}

void Video_reception::video_receive_show(QByteArray data)
{

    int startIndex = data.indexOf("VIDEO:");
    int endIndex = data.indexOf(';', startIndex);
    QByteArray compressedImage = data.mid(endIndex + 1);
    QByteArray decompressedData = qUncompress(compressedImage);
    QBuffer buffer(&decompressedData);
    buffer.open(QIODevice::ReadOnly);
    QImageReader reader(&buffer, "JPEG");
    image = reader.read();
    emit finsh(image);
}

