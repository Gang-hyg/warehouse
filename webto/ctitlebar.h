#ifndef CTITLEBAR_H
#define CTITLEBAR_H
#pragma once
#include <QWidget>

namespace Ui {
class CTitleBar;
}

class CTitleBar : public QWidget
{
    Q_OBJECT

public:
    explicit CTitleBar(QWidget *parent = nullptr);
    ~CTitleBar();
protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseDoubleClickEvent(QMouseEvent *event) override;
signals:
    void sig_close();
    void sig_max(bool isMax);
private slots:
    void on_Click();
private:
    Ui::CTitleBar *ui;
};

#endif // CTITLEBAR_H
