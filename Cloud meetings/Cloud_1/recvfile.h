fndef RECVFILE_H
#define RECVFILE_H

#include <QObject>

class Recvfile : public QObject
{
    Q_OBJECT
public:
    explicit Recvfile(QObject *parent = nullptr);

signals:

};

#endif // RECVFILE_H
