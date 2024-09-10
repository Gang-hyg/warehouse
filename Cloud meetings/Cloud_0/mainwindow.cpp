#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "audioplauthread.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("云会议服务器端");
    //与客户端建立连接
    ui->lineEdit_port->setText("8899");
    //初始化客户端列表
    clients.clear();
    forward1 = new Forward(this);
    connect(this,&MainWindow::tomessage1,forward1,&Forward::message);
    connect(forward1,&Forward::tomessage,this,&MainWindow::setline);
    forward1->start();
    forward2 = new Forward(this);
    connect(this,&MainWindow::tomessage2,forward2,&Forward::message);
    forward2->start();
    forward3 = new Forward(this);
    connect(this,&MainWindow::tomessage3,forward3,&Forward::message);
    forward3->start();
    //创建监听的服务器对象
    m_s=new QTcpServer(this);
    connect(m_s,&QTcpServer::newConnection,this,&MainWindow::onNewConnection);
}

MainWindow::~MainWindow()
{
    for (auto it = clients.begin(); it != clients.end(); ++it) {
        QList<QTcpSocket*> clientList = it.value(); // 获取当前值（即 QTcpSocket* 的列表）
        // 遍历列表中的每个 QTcpSocket*
        for (QTcpSocket *client : clientList) {
            // 断开连接
            client->disconnectFromHost();
            // 标记为稍后删除（这将导致 Qt 事件循环在适当的时候删除对象）
            client->deleteLater();
        }
    }
    delete ui;
}

//启动监听
void MainWindow::on_pushButton_clicked()
{
    unsigned short port =ui->lineEdit_port->text().toUShort();
    if(m_s->listen(QHostAddress::Any,port)){
        ui->pushButton->setDisabled(true);
        ui->textEdit->append("监听成功");//更新状态
    }
    else{
        // 处理监听失败的情况
        ui->textEdit->append("监听失败");
    }
}

void MainWindow::onNewConnection()
{
    //建立连接
    QTcpSocket *clientSocket = m_s->nextPendingConnection();
    //获取客户端的ip
    QHostAddress clientAddress = clientSocket->peerAddress();
    QString ipAddress = clientAddress.toString();
    // 检测是否可以接收数据
    connect(clientSocket, &QTcpSocket::readyRead, this, [=]() {
        //信息接收与转码
        QByteArray data = clientSocket->readAll();
        QString line = QString::fromUtf8(data);
        //处理不同类型的消息
        if(line.startsWith("REQUEST_ID")){
            clients[id].append(clientSocket);
            ui->textEdit->append(ipAddress+":"+line);
            if(release.isEmpty()){
                line=QString("REQUEST_ID_%1").arg(id++);
            }else{
                line=QString("REQUEST_ID_%1").arg(*release.begin());
                release.erase(release.begin());
            }
            ui->textEdit->append("服务器:"+line);
            clientSocket->write(line.toUtf8());
        }else if(line.startsWith("JOIN_ID")){
            ui->textEdit->append(ipAddress+":"+line);
            QString toid = line.mid(7).trimmed();
            if(!clients[toid.toInt()].isEmpty()){
                clients[toid.toInt()].append(clientSocket);
                clientSocket->write(data);
                ui->textEdit->append("服务器:"+ipAddress+"加入了组:" + toid);
            }else{
                QString msg="FAIL";
                clientSocket->write(msg.toUtf8());
            }
        }else if(line.startsWith("Message")){
            emit(tomessage1(clientSocket,clients,data));
        }else if(line.startsWith("VIDEO")){
            emit(tomessage2(clientSocket,clients,data));
        }else if(line.startsWith("AUDIO")){
            emit(tomessage3(clientSocket,clients,data));
        }else if(line.startsWith("disvideo")){
            int separatorIndex = line.indexOf(':');
            QString groupIdString;
            for(int i=separatorIndex+1;i<line.length();i++){
                groupIdString+=line[i];
            }
            QList<QTcpSocket*> clientsList = clients[groupIdString.toInt()];
            for (QTcpSocket *clientSocket1 : clientsList) {
                if (clientSocket1 != clientSocket && clientSocket1->isOpen()) {
                    clientSocket1->write(data);
                }
            }
        }
    });
    //客户端断开的处理
    connect(clientSocket, &QTcpSocket::disconnected, this, [=]() {
        // 遍历所有组并移除已断开的客户端
        for (auto it = clients.begin(); it != clients.end(); ) {
            it.value().removeAll(clientSocket);
            if (it.value().isEmpty()) {
                // 如果某个组的客户端列表为空，移除该组
                it = clients.erase(it);
                release.insert(it.key());
            } else {
                ++it;
            }
        }
        clientSocket->deleteLater(); // 确保在事件循环中删除socket
        for (auto it = release.begin(); it !=release.end();it++) {
            qDebug()<<*it;
        }
    });
}

void MainWindow::setline(QString line)
{
    ui->textEdit->append(line);
}
