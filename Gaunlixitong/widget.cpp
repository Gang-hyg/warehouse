#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    //界面初始化
    teacher = new teaacher;
    e = new enroll;
    stu = new student;
    //单选初始化
    btnGroyp = new QButtonGroup;
    btnGroyp->addButton(ui->radioButton,0);
    btnGroyp->addButton(ui->radioButton_2,1);
    ui->radioButton->setChecked(1);
    //链接数据库
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("127.0.0.1");
    db.setUserName("root");
    db.setPassword("12345");
    db.setDatabaseName("db_test");
    if(!db.open()){
        qDebug() << "未成功链接到数据库";
    }else{
        qDebug() << "成功链接到数据库";
    }
    //接收返回信号
    connect(e,&enroll::back,[=]{
        this->show();
    });
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_pushButton_clicked()
{
    QString s1=ui->lineEdit->text();
    QString s2=ui->lineEdit_2->text();
    QSqlQuery db_cursor(db);
    //学生端
    if(btnGroyp->checkedId()==1){
        QString cmd = QString("select student_password,student_name from student where student_account = '"+s1+"'");
        db_cursor.exec(cmd);
        db_cursor.next();
        QString s3=db_cursor.value(0).toString();
        if(db_cursor.size() == 0){
            QMessageBox::information(this,"提示","账号错误");
        }else if(db_cursor.size() == 1 && s3!=s2){
            QMessageBox::information(this,"提示","密码错误");
        }else{
            QMessageBox::information(this,"提示","登录成功");
            stu->setname(db_cursor.value(1).toString());
            stu->show();
            this->hide();
        }
    }
    //教师端
    if(btnGroyp->checkedId()==0){
        QString cmd = QString("select teacher_password,teacher_name from teacher where teacher_account = '"+s1+"'");
        db_cursor.exec(cmd);
        db_cursor.next();
        QString s3=db_cursor.value(0).toString();
        if(db_cursor.size() == 0){
            QMessageBox::information(this,"提示","账号错误");
        }else if(db_cursor.size() == 1 && s3!=s2){
            QMessageBox::information(this,"提示","密码错误");
        }else{
            QMessageBox::information(this,"提示","登录成功");
            teacher->setname(db_cursor.value(1).toString());
            teacher->show();
            this->hide();
        }
    }
}
//注册
void Widget::on_pushButton_2_clicked()
{
    e->show();
    this->hide();
}
