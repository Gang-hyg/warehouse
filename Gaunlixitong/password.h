#ifndef PASSWORD_H
#define PASSWORD_H

#include <QWidget>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QDebug>
#include <QSqlQuery>
namespace Ui {
class password;
}

class password : public QWidget
{
    Q_OBJECT

public:
    explicit password(QWidget *parent = nullptr);
    ~password();
    void setname(QString name);
    void setidentity(QString identity);
private slots:
    void on_pushButton_clicked();

private:
    Ui::password *ui;
    QString name;
    QSqlDatabase db;
    QString identity;
};

#endif // PASSWORD_H
