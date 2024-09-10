#ifndef CLASS_H
#define CLASS_H

#include <QWidget>
#include <QTableView>
#include <QStandardItemModel>
#include <QDebug>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QSqlQuery>
namespace Ui {
class Class;
}

class Class : public QWidget
{
    Q_OBJECT

public:
    explicit Class(QWidget *parent = nullptr);
    ~Class();
    void setname(QString name);
public slots:
    void set(const QModelIndex &index);
private:
    Ui::Class *ui;
    QStandardItemModel *model;
    QStringList headers;
    QString name;
    QSqlDatabase db;
    int row;
};

#endif // CLASS_H
