#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QObject>
#include <QThread>
#include <QByteArray>
class Message : public QThread
{
    Q_OBJECT
public:
    explicit Message(QObject *parent = nullptr);
    void forwardMessage(const QByteArray &message);
signals:

};

class Video : public QThread
{
    Q_OBJECT
public:
    explicit Video(QObject *parent = nullptr);

signals:

};

class Audio : public QThread
{
    Q_OBJECT
public:
    explicit Audio(QObject *parent = nullptr);

signals:

};

#endif // MYTHREAD_H

