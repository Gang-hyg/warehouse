#ifndef TEAACHER_H
#define TEAACHER_H

#include <QWidget>
#include "initialize.h"
#include "course.h"
#include "selection.h"
#include "password.h"
#include "revise.h"
namespace Ui {
class teaacher;
}

class teaacher : public QWidget
{
    Q_OBJECT

public:
    explicit teaacher(QWidget *parent = nullptr);
    ~teaacher();
    void setname(QString name);

private slots:
    void on_toolButton_clicked();

    void on_toolButton_2_clicked();
    void on_toolButton_4_clicked();

    void on_toolButton_3_clicked();

signals:
    void getname(QString name);
private:
    Ui::teaacher *ui;
    initialize *z;
    course *c;
    password *p;
    selection *se;
    revise *r;
    QString name;
};

#endif // TEAACHER_H
