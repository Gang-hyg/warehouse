#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QButtonGroup>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>
#include "teaacher.h"
#include "student.h"
#include "enroll.h"
QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();
private:
    Ui::Widget *ui;
    teaacher *teacher;
    student *stu;
    enroll *e;
    QButtonGroup *btnGroyp;
    QSqlDatabase db;
};
#endif // WIDGET_H
