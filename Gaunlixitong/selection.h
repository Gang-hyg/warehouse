#ifndef SELECTION_H
#define SELECTION_H

#include <QWidget>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QDebug>
#include <QSqlQuery>
namespace Ui {
class selection;
}

class selection : public QWidget
{
    Q_OBJECT

public:
    explicit selection(QWidget *parent = nullptr);
    ~selection();
    void setname(QString name);

private:
    Ui::selection *ui;
    QSqlDatabase db;
    QString name;
};

#endif // SELECTION_H
