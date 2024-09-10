#ifndef REVISE_H
#define REVISE_H

#include <QWidget>
#include <QTableView>
#include <QStandardItemModel>
#include <QDebug>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QSqlQuery>
namespace Ui {
class revise;
}

class revise : public QWidget
{
    Q_OBJECT

public:
    explicit revise(QWidget *parent = nullptr);
    ~revise();
    void setname(QString name);
public slots:
    void set(const QModelIndex &index);
private:
    Ui::revise *ui;
    QStandardItemModel *model;
    QStringList headers;
    QString name;
    QSqlDatabase db;
    int row;
};

#endif // REVISE_H
