#include "revise.h"
#include "ui_revise.h"

revise::revise(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::revise)
{
    ui->setupUi(this);
}

revise::~revise()
{
    delete ui;
}

void revise::setname(QString name)
{
    this->name=name;
    model = new QStandardItemModel(1, 4);
    headers << "课程名称" << "学生名字" << "学生成绩" << "提交按钮";
    model->setHorizontalHeaderLabels(headers);
    QSqlQuery db_cursor(db);
    QString cmd = QString("select name,student,grades from grade where teacher='"+name+"'");
    db_cursor.exec(cmd);
    while(db_cursor.next()){
        row = model->rowCount();
        model->insertRow(row);
        QStandardItem *idItem = new QStandardItem(QString("%1").arg(db_cursor.value(0).toString()));
        QStandardItem *nameItem = new QStandardItem(QString("%1").arg(db_cursor.value(1).toString()));
        QStandardItem *nameItems = new QStandardItem(QString("%1").arg(db_cursor.value(2).toString()));
        QStandardItem *nameItemss = new QStandardItem(QString("%1").arg("提交"));
        model->setItem(row, 0, idItem);
        model->setItem(row, 1, nameItem);
        model->setItem(row, 2, nameItems);
        model->setItem(row, 3, nameItemss);
    }
    ui->tableView->setModel(model);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    connect(ui->tableView, &QTableView::clicked, this, &revise::set);
}

void revise::set(const QModelIndex &index)
{
    if(index.data().toString()=="提交"){
        QSqlQuery db_cursor(db);
        QString s1 = ui->tableView->model()->index(index.row(),0).data().toString();
        QString s2 = ui->tableView->model()->index(index.row(),1).data().toString();
        QString s3 = ui->tableView->model()->index(index.row(),2).data().toString();
        QString cmd = QString("update grade set grades='"+s3+"' where name='"+s1+"' and student ='"+s2+"'");
        db_cursor.exec(cmd);
        QMessageBox::information(this,"提示","提交成功");
    }
}
