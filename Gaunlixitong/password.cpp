#include "password.h"
#include "ui_password.h"

password::password(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::password)
{
    ui->setupUi(this);
}

password::~password()
{
    delete ui;
}

void password::setname(QString name)
{
    this->name = name;
}

void password::setidentity(QString identity)
{
    this->identity=identity;
}

void password::on_pushButton_clicked()
{
    QString s1=ui->lineEdit->text();
    QString s2=ui->lineEdit_2->text();
    if(s1==s2){
        QSqlQuery db_cursor(db);
        QString cmd = QString("update "+identity+" set student_password='"+s1+"' where student_name='"+name+"'");
        db_cursor.exec(cmd);
        QMessageBox::information(this,"提示","修改密码成功");
    }else{
        QMessageBox::information(this,"提示","两次密码不一致");
    }
}
