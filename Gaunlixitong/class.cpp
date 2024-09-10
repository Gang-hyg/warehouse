#include "class.h"
#include "ui_class.h"

Class::Class(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Class)
{
    ui->setupUi(this);
}

Class::~Class()
{
    delete ui;
}

void Class::setname(QString name)
{
    this->name=name;
    model = new QStandardItemModel(1, 3);
    headers << "课程名称" << "授课老师" << "选课按钮";
    model->setHorizontalHeaderLabels(headers);
    QSqlQuery db_cursor(db);
    QString cmd = QString("select c.name, c.teacher from class c where not exists(select 1 from grade g where g.student = '"+name+"' AND g.name = c.name)");
    db_cursor.exec(cmd);
    while(db_cursor.next()){
        row = model->rowCount();
        model->insertRow(row);
        QStandardItem *idItem = new QStandardItem(QString("%1").arg(db_cursor.value(0).toString()));
        QStandardItem *nameItem = new QStandardItem(QString("%1").arg(db_cursor.value(1).toString()));
        QStandardItem *nameItems = new QStandardItem(QString("%1").arg("选课"));
        model->setItem(row, 0, idItem);
        model->setItem(row, 1, nameItem);
        model->setItem(row, 2, nameItems);
    }
    ui->tableView->setModel(model);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    connect(ui->tableView, &QTableView::clicked, this, &Class::set);
}

void Class::set(const QModelIndex &index)
{
    if(index.data().toString()=="选课"){
        QSqlQuery db_cursor(db);
        QString s1 = ui->tableView->model()->index(index.row(),0).data().toString();
        QString s2 = ui->tableView->model()->index(index.row(),1).data().toString();
        QString s3 = ui->tableView->model()->index(index.row(),2).data().toString();
        QString cmd = QString("insert into grade (name,teacher,student) values ('"+s1+"','"+s2+"','"+name+"')");
        db_cursor.exec(cmd);
        QMessageBox::information(this,"提示","选课成功");
        for (int i = 0; i < model->rowCount(); /* 不在这里自增 */) {
            QStandardItem *studentItem = model->item(i, 0);
            if (studentItem && studentItem->text() == s1) {
                model->removeRow(i);
            } else {
                // 如果当前行不满足条件，则继续检查下一行
                ++i;
            }
        }
    }
}
