#ifndef INITIALIZE_H
#define INITIALIZE_H

#include <QWidget>

namespace Ui {
class initialize;
}

class initialize : public QWidget
{
    Q_OBJECT

public:
    explicit initialize(QWidget *parent = nullptr);
    ~initialize();

private:
    Ui::initialize *ui;
};

#endif // INITIALIZE_H
