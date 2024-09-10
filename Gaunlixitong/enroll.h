#ifndef ENROLL_H
#define ENROLL_H

#include <QWidget>
#include <QMessageBox>
#include <QSqlDatabase>
namespace Ui {
class enroll;
}

class enroll : public QWidget
{
    Q_OBJECT

public:
    explicit enroll(QWidget *parent = nullptr);
    ~enroll();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

signals:
    void back();
private:
    Ui::enroll *ui;
    QSqlDatabase db;
};

#endif // ENROLL_H
