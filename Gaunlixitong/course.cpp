#include "course.h"
#include "ui_course.h"
course::course(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::course)
{
    ui->setupUi(this);
    ui->tableWidget->setColumnCount(3);
    QStringList header;
    header<<"序号"<<"教师名"<<"教授课程";
    ui->tableWidget->setHorizontalHeaderLabels(header);
    ui->tableWidget->setColumnWidth(0,100);
    ui->tableWidget->setColumnWidth(1,100);
    ui->tableWidget->verticalHeader()->setVisible(false);
}

course::~course()
{
    delete ui;
}

void course::setname(QString name)
{
    this->name = name;
    QSqlQuery db_cursor(db);
    QString cmd = QString("select name from class where teacher = '"+name+"'");
    db_cursor.exec(cmd);
    while(db_cursor.next()){
        QTableWidgetItem *item[3];
        nCount = ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(nCount);
        item[0] = new QTableWidgetItem(QString::number(nCount+1));
        ui->tableWidget->setItem(nCount,0,item[0]);
        item[1] = new QTableWidgetItem(name+"老师");
        ui->tableWidget->setItem(nCount,1,item[1]);
        item[2] = new QTableWidgetItem(db_cursor.value(0).toString());
        ui->tableWidget->setItem(nCount,2,item[2]);
    }
}

void course::on_pushButton_clicked()
{
    QString s = ui->lineEdit->text();
    QSqlQuery db_cursor(db);
    QString cmd = QString("select name,teacher from class where teacher = '"+name+"' and name = '"+s+"'");
    db_cursor.exec(cmd);
    db_cursor.next();
    if(db_cursor.size() > 0){
        QMessageBox::information(this,"提示","已存在课程无需添加");
    }else{
        cmd = QString("insert into class (name,teacher) values ('"+s+"','"+name+"')");
        db_cursor.exec(cmd);
        QTableWidgetItem *item[3];
        nCount = ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(nCount);
        item[0] = new QTableWidgetItem(QString::number(nCount+1));
        ui->tableWidget->setItem(nCount,0,item[0]);
        item[1] = new QTableWidgetItem(name+"老师");
        ui->tableWidget->setItem(nCount,1,item[1]);
        item[2] = new QTableWidgetItem(s);
        ui->tableWidget->setItem(nCount,2,item[2]);
        QMessageBox::information(this,"提示","添加成功");
    }
}
