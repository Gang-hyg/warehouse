#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("云会议客户端");
    //连接服务器
    ui->lineEdit_port->setText("8899");
    //禁用按钮
    ui->pushButton_Quit->setDisabled(true);
    ui->pushButton_Join->setDisabled(true);
    ui->pushButton_Create->setDisabled(true);
    ui->pushButton_video->setDisabled(true);
    ui->pushButton_message->setDisabled(true);
    ui->pushButton_disconnect->setDisabled(true);
    ui->pushButton_disvideo->setDisabled(true);
    //创建监听的服务器对象
    m_tcp=new QTcpSocket(this);
    //播放对象初始化
    audio= new Audio(m_tcp,this);
    v=new Video_reception(this);
    //创建初始化视频对象
    audio->start();
    v->start();
    connect(this,&MainWindow::videomessage,v,&Video_reception::video_receive_show);
    connect(v,&Video_reception::finsh,this,&MainWindow::setImage);
    //创建初始化音频对象
    reception = new Audio_Reception(this);
    reception->setCurrentSampleInfo(8000,16,1);
    reception->setCurrentVolumn(100);
    reception->start();
    //接收信息
    connect(m_tcp,&QTcpSocket::readyRead,this,[=]{
        QByteArray data = m_tcp->readAll();
        QString line = QString::fromUtf8(data);
        if(line.startsWith("REQUEST_ID")){
            for(int i=11;i<line.length();i++){
                id=id+line[i];
            }
            ui->lineEdit_numbering->setText(id);
            ui->pushButton_Create->setDisabled(true);
            ui->pushButton_Quit->setEnabled(true);
            ui->pushButton_video->setEnabled(true);
            ui->pushButton_message->setEnabled(true);
            ui->pushButton_Join->setDisabled(true);
        }else if(line.startsWith("JOIN_ID")){
            ui->lineEdit_numbering->setText(id);
            ui->pushButton_Create->setDisabled(true);
            ui->pushButton_Quit->setEnabled(true);
            ui->pushButton_video->setEnabled(true);
            ui->pushButton_message->setEnabled(true);
            ui->pushButton_Join->setDisabled(true);
        }else if(line.startsWith("VIDEO")){
            ui->pushButton_video->setDisabled(true);
            ui->pushButton_disvideo->setDisabled(true);
            v->video_receive_show(data);
        }else if(line.startsWith("AUDIO")){
            reception->data=data;
            reception->readyReadSlot();
        }else if(line.startsWith("FAIL")){
            QMessageBox::information(this,"提示","为查找到该会议请重试");
        }else if(line.startsWith("disvideo")){
            ui->label_video->setPixmap(QPixmap());
            ui->pushButton_video->setEnabled(true);
        }else{
            // 移除可能的 IPv6 映射的 IPv4 地址前缀
            line.replace(QRegExp("^::ffff:"),"");
            line = line.trimmed(); // 移除字符串两端的空白字符
            ui->textEdit_output->append(line);
        }
    });
    connect(m_tcp,&QTcpSocket::connected,this,[=](){
        m_status->setPixmap(QPixmap(":/image/1.png").scaled(20,20));
        QMessageBox::information(this,"提示","服务器连接成功");
        ui->pushButton_disconnect->setEnabled(true);
        ui->pushButton_Connect->setDisabled(true);
        ui->pushButton_Create->setEnabled(true);
        ui->pushButton_Join->setEnabled(true);
    });
    connect(m_tcp,&QTcpSocket::disconnected,this,[=](){
        m_tcp->close();
        m_tcp->deleteLater();
        m_status->setPixmap(QPixmap(":/image/0.png").scaled(20,20));
        QMessageBox::information(this,"提示","服务器已断开");
        ui->pushButton_Quit->setDisabled(true);
        ui->pushButton_Join->setDisabled(true);
        ui->pushButton_Create->setDisabled(true);
        ui->pushButton_video->setDisabled(true);
        ui->pushButton_message->setDisabled(true);
    });
    //状态栏
    m_status = new QLabel;
    m_status->setPixmap(QPixmap(":/image/0.png").scaled(20,20));
    ui->statusbar->addWidget(new QLabel("服务器连接状态"));
    ui->statusbar->addWidget(m_status);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete reception;
    delete v;
    m_tcp->close();
}

//加入按钮:通过会议号加入会议
void MainWindow::on_pushButton_Join_clicked()
{
    id=ui->lineEdit_numbering->text();
    QString msg="JOIN_ID"+id;
    m_tcp->write(msg.toUtf8());
    qDebug()<<"msg";
}
//创建会议按钮:创建会议
void MainWindow::on_pushButton_Create_clicked()
{
    QString msg="REQUEST_ID";
    m_tcp->write(msg.toUtf8());
    qDebug()<<"REQUEST_ID";
}
//退出按钮:退出会议，关闭连接
void MainWindow::on_pushButton_Quit_clicked()
{
    id=nullptr;
    ui->pushButton_Join->setEnabled(true);
    ui->pushButton_Create->setEnabled(true);
    ui->pushButton_Quit->setDisabled(true);
    ui->pushButton_message->setDisabled(true);
    ui->pushButton_video->setDisabled(true);
    ui->pushButton_disvideo->setDisabled(true);
    ui->lineEdit_numbering->setText(nullptr);
    ui->textEdit_input->setText(nullptr);
    ui->textEdit_output->setText(nullptr);
}
//连接按钮:连接服务器
void MainWindow::on_pushButton_Connect_clicked()
{
    if(m_tcp && m_tcp->state() == QAbstractSocket::ConnectedState){
        return;
    }
    if(!m_tcp){
        m_tcp = new QTcpSocket(this);// 创建一个新的 QTcpSocket 对象（如果还没有的话）
        //接收信息
        connect(m_tcp,&QTcpSocket::readyRead,this,[=]{
            QByteArray data = m_tcp->readAll();
            QString line = QString::fromUtf8(data);
            if(line.startsWith("REQUEST_ID")){
                for(int i=11;i<line.length();i++){
                    id=id+line[i];
                }
                ui->lineEdit_numbering->setText(id);
                ui->pushButton_Create->setDisabled(true);
                ui->pushButton_Quit->setEnabled(true);
                ui->pushButton_video->setEnabled(true);
                ui->pushButton_message->setEnabled(true);
                ui->pushButton_Join->setDisabled(true);
            }else if(line.startsWith("JOIN_ID")){
                ui->lineEdit_numbering->setText(id);
                ui->pushButton_Create->setDisabled(true);
                ui->pushButton_Quit->setEnabled(true);
                ui->pushButton_video->setEnabled(true);
                ui->pushButton_message->setEnabled(true);
                ui->pushButton_Join->setDisabled(true);
            }else if(line.startsWith("VIDEO")){
                v->video_receive_show(data);
            }else if(line.startsWith("AUDIO")){
                reception->data=data;
                reception->readyReadSlot();
            }else if(line.startsWith("FAIL")){
                QMessageBox::information(this,"提示","为查找到该会议请重试");
            }else if(line.startsWith("disvideo")){
                ui->label_video->setPixmap(QPixmap());
                ui->pushButton_video->setEnabled(true);
            }else{
                // 移除可能的 IPv6 映射的 IPv4 地址前缀
                line.replace(QRegExp("^::ffff:"),"");
                line = line.trimmed(); // 移除字符串两端的空白字符
                ui->textEdit_output->append(line);
            }
            reception->stop();
        });
        connect(m_tcp,&QTcpSocket::connected,this,[=](){
            m_status->setPixmap(QPixmap(":/image/1.png").scaled(20,20));
            QMessageBox::information(this,"提示","服务器连接成功");
            ui->pushButton_disconnect->setEnabled(true);
            ui->pushButton_Connect->setDisabled(true);
            ui->pushButton_Create->setEnabled(true);
            ui->pushButton_Join->setEnabled(true);
        });
        connect(m_tcp,&QTcpSocket::disconnected,this,[=](){
            m_tcp->close();
            m_tcp->deleteLater();
            m_status->setPixmap(QPixmap(":/image/0.png").scaled(20,20));
            QMessageBox::information(this,"提示","服务器已断开");
            ui->pushButton_Quit->setDisabled(true);
            ui->pushButton_Join->setDisabled(true);
            ui->pushButton_Create->setDisabled(true);
            ui->pushButton_video->setDisabled(true);
            ui->pushButton_message->setDisabled(true);
            ui->pushButton_Connect->setEnabled(true);
            ui->pushButton_disconnect->setDisabled(true);
            m_status->setPixmap(QPixmap(":/image/0.png").scaled(20,20));
        });
    }
    QString ip = ui->lineEdit_ip->text();
    unsigned short port = ui->lineEdit_port->text().toUShort();
    m_tcp->connectToHost(QHostAddress(ip),port);
}
//发送按钮:发送信息
void MainWindow::on_pushButton_message_clicked()
{
    QString msg="Message:"+id+';'+ui->textEdit_input->toPlainText();
    m_tcp->write(msg.toUtf8());
    ui->textEdit_output->append("我:"+ui->textEdit_input->toPlainText());
}
//打开视频
void MainWindow::on_pushButton_video_clicked()
{
    connect(&fps_timer,SIGNAL(timeout()),this,SLOT(VideoSend()));
    if(!camera.open(0)){
        QMessageBox::information(this,"提示","未查找摄像头");
        return;
    }
    fps_timer.start(33);
    audio->id=id;
    audio->setaudioformat(8000,1,16);
    audio->mystart();
    ui->pushButton_video->setDisabled(true);
    ui->pushButton_disvideo->setEnabled(true);
}
//静音按钮
void MainWindow::on_pushButton_mute_clicked()
{
    ui->pushButton_mute->setStyleSheet("QPushButton{border-image: url(:/image/video0.png);border:none;color:rgb(255, 255, 255);}");
    reception->setCurrentVolumn(0);
}
//断开服务器连接
void MainWindow::on_pushButton_disconnect_clicked()
{
    if(m_tcp){
        m_tcp->close();
        m_tcp->deleteLater();
        m_tcp = nullptr;
        ui->pushButton_Connect->setDisabled(false);
        ui->pushButton_disconnect->setEnabled(false);
    }
}

//关闭视频
void MainWindow::on_pushButton_disvideo_clicked()
{
    fps_timer.stop();
    camera.release();
    audio->mystop();
    ui->pushButton_video->setEnabled(true);
    ui->pushButton_disvideo->setDisabled(true);
    ui->label_video->setPixmap(QPixmap());
    QString msg="disvideo:"+id;
    m_tcp->write(msg.toUtf8());
    v->quit();
    v->wait();
}
//初始化视频传输
void MainWindow::VideoSend()
{
    Mat frame,frame1;
    camera.read(frame);
    cvtColor(frame,frame1,CV_BGR2RGB);
    QImage image((unsigned char *)(frame1.data),frame1.cols,frame1.rows,QImage::Format_RGB888);
    ui->label_video->setPixmap(QPixmap::fromImage(image));
    ui->label_video->resize(image.width(),image.height());
    QByteArray byte;
    QBuffer buff(&byte);
    buff.open(QIODevice::WriteOnly);
    image.save(&buff,"JPEG");
    QByteArray ss = qCompress(byte,5);
    if(m_tcp->state() == QAbstractSocket::ConnectedState){
        QString msg="VIDEO:"+id+";";
        m_tcp->write(msg.toUtf8());
        m_tcp->write(ss);
    }
}

void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    reception->setCurrentVolumn(value);
}

void MainWindow::setImage(QImage image)
{
    ui->label_video->setPixmap(QPixmap::fromImage(image));
    ui->label_video->setScaledContents(true);
}
