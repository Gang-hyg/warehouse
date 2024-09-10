#include "student.h"
#include "ui_student.h"

student::student(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::student)
{
    ui->setupUi(this);
    p = new password;
    z = new initialize;
    c = new Class;
    g = new grade;
    ui->stackedWidget->addWidget(p);
    ui->stackedWidget->addWidget(z);
    ui->stackedWidget->addWidget(c);
    ui->stackedWidget->addWidget(g);
    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->indexOf(z));
}

student::~student()
{
    delete ui;
}

void student::setname(QString name)
{
    this->name=name;
    p->setidentity("student");
    p->setname(name);
    c->setname(name);
    g->setname(name);
}

void student::on_toolButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->indexOf(p));
}

void student::on_toolButton_3_clicked()
{
    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->indexOf(c));
}

void student::on_toolButton_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->indexOf(g));
}
