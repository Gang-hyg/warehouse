#include "grade.h"
#include "ui_grade.h"

grade::grade(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::grade)
{
    ui->setupUi(this);
    ui->tableWidget->setColumnCount(4);
    QStringList header;
    header<<"序号"<<"课程名"<<"课程成绩"<<"排名";
    ui->tableWidget->setHorizontalHeaderLabels(header);
    ui->tableWidget->setColumnWidth(0,100);
    ui->tableWidget->setColumnWidth(1,100);
    ui->tableWidget->setColumnWidth(2,100);
    ui->tableWidget->setColumnWidth(3,100);
    ui->tableWidget->verticalHeader()->setVisible(false);
}

grade::~grade()
{
    delete ui;
}

void grade::setname(QString name)
{
    this->name=name;
    int nCount;
    QSqlQuery db_cursor(db);
    QString cmd = QString("SELECT * FROM(SELECT name,student,grades,DENSE_RANK() OVER (PARTITION BY name ORDER BY grades DESC) AS s FROM grade) AS a WHERE student = '"+name+"'");
    db_cursor.exec(cmd);
    while(db_cursor.next()){
        QTableWidgetItem *item[4];
        nCount = ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(nCount);
        item[0] = new QTableWidgetItem(QString::number(nCount+1));
        ui->tableWidget->setItem(nCount,0,item[0]);
        item[1] = new QTableWidgetItem(db_cursor.value(0).toString());
        ui->tableWidget->setItem(nCount,1,item[1]);
        item[2] = new QTableWidgetItem(db_cursor.value(2).toString());
        ui->tableWidget->setItem(nCount,2,item[2]);
        item[3] = new QTableWidgetItem(db_cursor.value(3).toString());
        ui->tableWidget->setItem(nCount,3,item[3]);
    }
}
