#include "ctitlebar.h"
#include "ui_ctitlebar.h"
#include <QMouseEvent>
#include <QStyleOption>
#include <QPushButton>
#include <QPainter>
#include <qt_windows.h>
#include <QDebug>
#pragma comment(lib, "user32.lib")
CTitleBar::CTitleBar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CTitleBar)
{
    ui->setupUi(this);
    //禁止父窗口影响子窗口样式
        setAttribute(Qt::WA_StyledBackground);

        //左上，右上圆角10；左下，右下圆角0
        this->setStyleSheet("QWidget{background-color:rgb(54,54,54); \
            border-top-left-radius:10px; \
            border-top-right-radius:10px; \
            border-bottom-left-radius:0px; \
            border-bottom-right-radius:0px;}");

        ui->label_title->setText("我是标题");
        ui->label_title->setStyleSheet("QLabel{font-family: Microsoft YaHei; \
            font-size:18px; \
            color:#BDC8E2;background-color:rgb(54,54,54);}");


        ui->btnMin->setFixedSize(32, 32);
        ui->btnMin->setText("");
        ui->btnMin->setFlat(true);
        ui->btnMin->setStyleSheet("QPushButton{border:none}" \
            "QPushButton:hover{" \
            "background-color:rgb(99, 99, 99);" \
            "border:none;}");

        ui->btnMax->setFixedSize(35, 35);
        ui->btnMax->setFlat(true);
        ui->btnMax->setText("");
        ui->btnMax->setStyleSheet("QPushButton{border:none; \
            background-position:center; \
            background-repeat:no-repeat;}  \
            QPushButton:hover{ \
            background-color:rgb(99, 99, 99); \
            border:none;}");

        ui->btnClose->setFixedSize(32, 32);
        ui->btnClose->setFlat(true);
        ui->btnClose->setText("");
        //setPixmap(QPixmap(":/image/1.png").scaled(20,20));
        ui->btnClose->setStyleSheet(" color: white;border:none}" \
            "QPushButton:hover{" \
            "background-color:rgb(99, 99, 99);" \
            "color: white; /* 设置鼠标悬停时的字体颜色为白色 */" \
            "border:none;}");

        connect(ui->btnMin,&QPushButton::clicked, this, &CTitleBar::on_Click);
        connect(ui->btnMax,&QPushButton::clicked, this, &CTitleBar::on_Click);
        connect(ui->btnClose,&QPushButton::clicked, this, &CTitleBar::on_Click);

}

CTitleBar::~CTitleBar()
{
    delete ui;
}

void CTitleBar::paintEvent(QPaintEvent *event)
{
    //决定样式表是否起作用
    /*QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
    QWidget::paintEvent(event);*/
}

void CTitleBar::mousePressEvent(QMouseEvent *event)
{
    if (ReleaseCapture())
    {
        QWidget* pWindow = this->window();
        if (pWindow->isTopLevel())
        {
            SendMessage(HWND(pWindow->winId()), WM_SYSCOMMAND, SC_MOVE + HTCAPTION, 0);
        }
    }

    event->ignore();
}

void CTitleBar::mouseDoubleClickEvent(QMouseEvent *event)
{
    emit ui->btnMax->clicked();
}

void CTitleBar::on_Click()
{
    QPushButton* pButton = qobject_cast<QPushButton*>(sender());

        QWidget* pWindow = this->window();

        if (pWindow->isTopLevel())
        {
            if (pButton == ui->btnMin)
            {
                pWindow->showMinimized();
            }
            else if (pButton == ui->btnMax)
            {
                if (pWindow->isMaximized())
                {
                    pWindow->showNormal();
                    ui->btnMax->setStyleSheet("QPushButton{border:none;  \
                        background-position:center; \
                        background-repeat:no-repeat;}  \
                        QPushButton:hover{ \
                        background-color:rgb(99, 99, 99); \
                        border:none;}");

                    emit sig_max(false);
                }
                else
                {
                    pWindow->showMaximized();
                    ui->btnMax->setStyleSheet("QPushButton{border:none;  \
                        background-position:center; \
                        background-repeat:no-repeat;}  \
                        QPushButton:hover{ \
                        background-color:rgb(99, 99, 99);  \
                        border:none;}");

                    emit sig_max(true);
                }
            }
            else if (pButton == ui->btnClose)
            {
                emit sig_close();
            }
        }

}
