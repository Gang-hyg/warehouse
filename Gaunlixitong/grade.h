#ifndef GRADE_H
#define GRADE_H

#include <QWidget>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QDebug>
#include <QSqlQuery>
namespace Ui {
class grade;
}

class grade : public QWidget
{
    Q_OBJECT

public:
    explicit grade(QWidget *parent = nullptr);
    ~grade();
    void setname(QString name);

private:
    Ui::grade *ui;
    QSqlDatabase db;
    QString name;
};

#endif // GRADE_H
