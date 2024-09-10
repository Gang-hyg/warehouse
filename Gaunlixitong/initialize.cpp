#include "initialize.h"
#include "ui_initialize.h"

initialize::initialize(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::initialize)
{
    ui->setupUi(this);
}

initialize::~initialize()
{
    delete ui;
}
