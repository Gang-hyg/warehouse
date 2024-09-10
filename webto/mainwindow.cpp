#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : CFrameLessWidghtBase(parent)
{
    //设置窗体透明
      this->setAttribute(Qt::WA_TranslucentBackground, true);

      m_pMainVLay = new QVBoxLayout(this);
      m_pTopWidget = new CTopWidget(this);
      m_pMainVLay->addWidget(m_pTopWidget);

      int shadow_width = 30;
      m_pMainVLay->setContentsMargins(shadow_width, shadow_width, shadow_width, shadow_width);
      setLayout(m_pMainVLay);

      //给顶层widget设置背景颜色，不然看不见，因为底层widget已经透明了
      m_pTopWidget->setStyleSheet("background-color:rgb(255, 254, 253)");
      m_pShadow = new QGraphicsDropShadowEffect(this);

      //设置阴影距离
      m_pShadow->setOffset(0, 0);

      //设置阴影颜色  686868
      m_pShadow->setColor(QColor("#0000FF"));

      //设置阴影区域
      m_pShadow->setBlurRadius(shadow_width - 5);

      //给顶层QWidget设置阴影
      m_pTopWidget->setGraphicsEffect(m_pShadow);

      connect(m_pTopWidget, &CTopWidget::sig_close, this, &MainWindow::onClose);
      connect(m_pTopWidget, &CTopWidget::sig_max, this, &MainWindow::onDoMax);

}
void MainWindow::onClose()
{
    close();
}

void MainWindow::onDoMax(bool isMax)
{
    int shadow_width = 25;
    if (isMax)
    {
        shadow_width = 0;
    }
    else
    {

    }

    m_pMainVLay->setContentsMargins(shadow_width, shadow_width, shadow_width, shadow_width);

    //设置阴影区域
    m_pShadow->setBlurRadius(shadow_width);

    //给顶层QWidget设置阴影
    m_pTopWidget->setGraphicsEffect(m_pShadow);
}
MainWindow::~MainWindow()
{
}

