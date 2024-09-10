#include "selection.h"
#include "ui_selection.h"

selection::selection(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::selection)
{
    ui->setupUi(this);
    ui->tableWidget->setColumnCount(4);
    QStringList header;
    header<<"序号"<<"教授课程"<<"教授教师"<<"已选学生";
    ui->tableWidget->setHorizontalHeaderLabels(header);
    ui->tableWidget->setColumnWidth(0,100);
    ui->tableWidget->setColumnWidth(1,100);
    ui->tableWidget->setColumnWidth(2,100);
    ui->tableWidget->setColumnWidth(3,100);
    ui->tableWidget->verticalHeader()->setVisible(false);
}

selection::~selection()
{
    delete ui;
}

void selection::setname(QString name)
{
    this->name=name;
    QSqlQuery db_cursor(db);
    QString cmd = QString("select name,student from grade where teacher = '"+name+"'");
    db_cursor.exec(cmd);
    int nCount;
    while(db_cursor.next()){
        QTableWidgetItem *item[4];
        nCount = ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(nCount);
        item[0] = new QTableWidgetItem(QString::number(nCount+1));
        ui->tableWidget->setItem(nCount,0,item[0]);
        item[1] = new QTableWidgetItem(db_cursor.value(0).toString());
        ui->tableWidget->setItem(nCount,1,item[1]);
        item[2] = new QTableWidgetItem(name+"老师");
        ui->tableWidget->setItem(nCount,2,item[2]);
        item[3] = new QTableWidgetItem(db_cursor.value(1).toString());
        ui->tableWidget->setItem(nCount,3,item[3]);
    }
    ui->label->setText("已选"+QString::number(nCount+1)+"人");
}
