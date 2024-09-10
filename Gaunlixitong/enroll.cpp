#include "enroll.h"
#include "ui_enroll.h"
#include <QDebug>
#include "widget.h"
enroll::enroll(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::enroll)
{
    ui->setupUi(this);
}

enroll::~enroll()
{
    delete ui;
}

void enroll::on_pushButton_clicked()
{
    QSqlQuery db_cursor(db);
    if(ui->radioButton->isChecked()==false&&ui->radioButton_2->isChecked()==false){
        QMessageBox::information(this,"提示","请选择身份");
        return;
    }
    if(ui->lineEdit_3->text()==""){
        QMessageBox::information(this,"提示","姓名不能为空");
        return;
    }
    if(ui->lineEdit->text()==""){
        QMessageBox::information(this,"提示","工号/学号不能为空");
        return;
    }
    if(ui->lineEdit_2->text()==""){
        QMessageBox::information(this,"提示","密码不能为空");
        return;
    }
    QString s=ui->lineEdit->text();
    QString s1=ui->lineEdit_2->text();
    QString s2=ui->lineEdit_3->text();
    if(ui->radioButton->isChecked()){
        QString cmd = QString("select teacher_password from teacher where teacher_name = '"+s2+"'");
        db_cursor.exec(cmd);
        db_cursor.next();
        if(db_cursor.size() == 1){
            QMessageBox::information(this,"提示","账号已存在");
            return;
        }else if(db_cursor.size() == 0){
            cmd = QString("insert into teacher values('"+s+"', '"+s1+"', '"+s2+"')");
            bool re = db_cursor.exec(cmd);
                if(!re){
                    qDebug() << "操作数据库失败！" ;
                }else{
                    qDebug() << "操作数据库成功！" ;
                    QMessageBox::information(this,"提示","注册成功");
                }
        }
    }
    if(ui->radioButton_2->isChecked()){
        QString cmd = QString("select student_password from student where student_name = '"+s2+"'");
        db_cursor.exec(cmd);
        db_cursor.next();
        if(db_cursor.size() == 1){
            QMessageBox::information(this,"提示","账号已存在");
            return;
        }else if(db_cursor.size() == 0){
            cmd = QString("insert into student values('"+s+"', '"+s1+"', '"+s2+"')");
            bool re = db_cursor.exec(cmd);
                if(!re){
                    qDebug() << "操作数据库失败！" ;
                    return;
                }else{
                    qDebug() << "操作数据库成功！" ;
                    QMessageBox::information(this,"提示","注册成功");
                }
        }
    }
    emit this->back();
    this->hide();
}

void enroll::on_pushButton_2_clicked()
{
    emit this->back();
    this->hide();
}
