#ifndef MAINWINDOW_H
#define MAINWINDOW_H
//服务器端
#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>
#include <QList>
#include <QMap>
#include <QSet>
#include "forward.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void onNewConnection();
    void setline(QString line);
private:
    Ui::MainWindow *ui;
    QTcpServer *m_s;
    QMap<int,QList<QTcpSocket*>> clients;
    int id=123;
    QSet<int> release;
    Forward *forward1,*forward2,*forward3;
signals:
    void tomessage1(QTcpSocket *clientSocket, QMap<int,QList<QTcpSocket*>> clients,QByteArray data);
    void tomessage2(QTcpSocket *clientSocket, QMap<int,QList<QTcpSocket*>> clients,QByteArray data);
    void tomessage3(QTcpSocket *clientSocket, QMap<int,QList<QTcpSocket*>> clients,QByteArray data);
};
#endif // MAINWINDOW_H
