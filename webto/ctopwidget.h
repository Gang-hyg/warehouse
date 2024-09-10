#ifndef CTOPWIDGET_H
#define CTOPWIDGET_H
#pragma once
#include <QWidget>
#include <QWebEngineView>
#include <QStackedLayout>
class CTopWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CTopWidget(QWidget *parent = nullptr);
    ~CTopWidget();
signals:
    void sig_close();
    void sig_max(bool isMax);
private:
    QWebEngineView *m_webView;
};

#endif // CTOPWIDGET_H
