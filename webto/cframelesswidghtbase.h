#ifndef CFRAMELESSWIDGHTBASE_H
#define CFRAMELESSWIDGHTBASE_H
#pragma once
#include <QWidget>

class CFrameLessWidghtBase : public QWidget
{
    Q_OBJECT
public:
    explicit CFrameLessWidghtBase(QWidget *parent = nullptr);
    ~CFrameLessWidghtBase();
protected:
    bool nativeEvent(const QByteArray &eventType, void *message, long *result) override;
private:
    int mouse_margin=5;

};

#endif // CFRAMELESSWIDGHTBASE_H
