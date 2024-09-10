#ifndef COURSE_H
#define COURSE_H

#include <QWidget>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QDebug>
#include <QSqlQuery>
namespace Ui {
class course;
}

class course : public QWidget
{
    Q_OBJECT

public:
    explicit course(QWidget *parent = nullptr);
    ~course();
    void setname(QString name);
private slots:
    void on_pushButton_clicked();

private:
    Ui::course *ui;
    QSqlDatabase db;
    QString name;
    int nCount;
};

#endif // COURSE_H
