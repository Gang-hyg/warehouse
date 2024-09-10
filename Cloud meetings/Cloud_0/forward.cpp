#include "forward.h"
Forward::Forward(QObject *parent) : QThread(parent)
{

}

void Forward::message(QTcpSocket *clientSocket, QMap<int,QList<QTcpSocket*>> clients,QByteArray data)
{
    QHostAddress clientAddress = clientSocket->peerAddress();
    QString ipAddress = clientAddress.toString();
    QString line =QString::fromUtf8(data);
    int separatorIndex = line.indexOf(':');
    int separatorIndex1 = line.indexOf(';');
    QString groupIdString;
    for(int i=separatorIndex+1;i<separatorIndex1;i++){
        groupIdString+=line[i];
    }
    bool ok;
    int groupId = groupIdString.toInt(&ok);
    if(line.startsWith("Message")){
        QStringList parts = line.split(";");
        line=ipAddress+':'+parts[1];
        line.replace(QRegExp("^::ffff:"),"");
        line = line.trimmed(); // 移除字符串两端的空白字符
        QList<QTcpSocket*> clientsList = clients[groupId];
        for (QTcpSocket *clientSocket1 : clientsList) {
            if (clientSocket1 != clientSocket && clientSocket1->isOpen()) {
                clientSocket1->write(line.toUtf8());
            }
        }
        emit tomessage(line);
    }else{
        QList<QTcpSocket*> clientsList = clients[groupId];
        for (QTcpSocket *clientSocket1 : clientsList) {
            if (clientSocket1 != clientSocket && clientSocket1->isOpen()) {
                clientSocket1->write(data);
            }
        }
    }
}
