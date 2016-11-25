#ifndef QUICK_CALC_H
#define QUICK_CALC_H

#include <QWidget>

namespace Ui {
class quick_calc;
}

class quick_calc : public QWidget
{
    Q_OBJECT

public:
    explicit quick_calc(QWidget *parent = 0);
    ~quick_calc();

private slots:
    void on_back_clicked();
    void on_expression_textChanged();

private:
    Ui::quick_calc *ui;
};

#endif // QUICK_CALC_H
