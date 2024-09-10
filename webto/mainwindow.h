#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#pragma once
#include <QMainWindow>
#include <QWidget>
#include "cframelesswidghtbase.h"
#include "ctopwidget.h"
#include <QVBoxLayout>
#include <QGraphicsDropShadowEffect>
class MainWindow : public CFrameLessWidghtBase
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = Q_NULLPTR);
    ~MainWindow();
private slots:
    void onClose();
    void onDoMax(bool isMax);

private:
    QVBoxLayout* m_pMainVLay = nullptr;
    CTopWidget* m_pTopWidget = nullptr;
    QGraphicsDropShadowEffect* m_pShadow = nullptr;
};
#endif // MAINWINDOW_H
