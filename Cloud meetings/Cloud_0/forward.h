#ifndef FORWARD_H
#define FORWARD_H

#include <QObject>
#include <QThread>
#include <QTcpSocket>
#include <QHostAddress>
#include <QByteArray>
class Forward : public QThread
{
    Q_OBJECT
public:
    explicit Forward(QObject *parent = nullptr);
    void message(QTcpSocket *clientSocket, QMap<int,QList<QTcpSocket*>> clients,QByteArray data);
signals:
    void tomessage(QString line);
};

#endif // FORWARD_H
