#include "teaacher.h"
#include "ui_teaacher.h"

teaacher::teaacher(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::teaacher)
{
    ui->setupUi(this);
    z = new initialize;
    c = new course;
    se = new selection;
    p = new password;
    r = new revise;
    ui->stackedWidget->addWidget(z);
    ui->stackedWidget->addWidget(c);
    ui->stackedWidget->addWidget(se);
    ui->stackedWidget->addWidget(p);
    ui->stackedWidget->addWidget(r);
    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->indexOf(z));
}

teaacher::~teaacher()
{
    delete ui;
}

void teaacher::setname(QString name)
{
    this->name=name;
    c->setname(name);
    se->setname(name);
    p->setidentity("teacher");
    p->setname(name);
    r->setname(name);
}

void teaacher::on_toolButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->indexOf(se));
}

void teaacher::on_toolButton_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->indexOf(c));
}

void teaacher::on_toolButton_4_clicked()
{
    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->indexOf(p));
}

void teaacher::on_toolButton_3_clicked()
{
    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->indexOf(r));
}
