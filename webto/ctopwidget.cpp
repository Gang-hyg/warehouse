#include "ctopwidget.h"
#include "ctitlebar.h"
#include <QVBoxLayout>
#include <QFrame>
#include <QApplication>
CTopWidget::CTopWidget(QWidget *parent) : QWidget(parent)
{
    setAttribute(Qt::WA_StyledBackground);
       this->setStyleSheet("QWidget{background-color:rgb(255, 254, 253);border-radius:10px;}");
       /*this->setStyleSheet("QWidget{background-color:rgb(255, 254, 253); \
           border-bottom-left-radius:15px; \
           border-bottom-right-radius:15px;}");*/

       QVBoxLayout* pVLay = new QVBoxLayout(this);
       CTitleBar* pTitle = new CTitleBar(this);
       QWidget* pWidget = new QWidget(this);
       QFrame *frame = new QFrame;
       m_webView = new QWebEngineView(this);



       QStackedLayout *layoutt = new QStackedLayout(frame);

       frame->setLayout(layoutt);
       layoutt->addWidget(m_webView);
       QString url = "https://www.baidu.com";
       m_webView->load(url);

       pWidget->setLayout(layoutt);


       //需要指定pWidget最小尺寸，或最大尺寸
       pWidget->setMinimumSize(1200, 800);


       pVLay->addWidget(pTitle);
       pVLay->addWidget(pWidget);
       pVLay->setContentsMargins(0, 0, 0, 0);
       setLayout(pVLay);

       connect(pTitle, &CTitleBar::sig_close, this, &CTopWidget::sig_close);
       connect(pTitle, &CTitleBar::sig_max, this, &CTopWidget::sig_max);
}

CTopWidget::~CTopWidget()
{

}
