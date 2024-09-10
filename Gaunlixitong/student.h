#ifndef STUDENT_H
#define STUDENT_H

#include <QWidget>
#include "password.h"
#include "initialize.h"
#include "class.h"
#include "grade.h"
namespace Ui {
class student;
}

class student : public QWidget
{
    Q_OBJECT

public:
    explicit student(QWidget *parent = nullptr);
    ~student();
    void setname(QString name);
signals:
    void getname(QString name);
private slots:
    void on_toolButton_clicked();

    void on_toolButton_3_clicked();

    void on_toolButton_2_clicked();

private:
    Ui::student *ui;
    QString name;
    password *p;
    initialize *z;
    grade *g;
    Class *c;
};

#endif // STUDENT_H
