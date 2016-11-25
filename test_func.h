#ifndef TEST_FUNC_H
#define TEST_FUNC_H

#include <QWidget>
#include "google_analytics.h"

namespace Ui {
class test_func;
}

class test_func : public QWidget
{
    Q_OBJECT

public:
    explicit test_func(QWidget *parent = 0);
    ~test_func();

private slots:
    void on_back_clicked();
    void on_add_clicked();
    void on_subtract_clicked();
    void on_multiply_clicked();
    void on_divide_clicked();
    void on_mod_clicked();

private:
    Ui::test_func *ui;
    //[22-11-2016] added google analytics to this page
    google_analytics ga;
};

#endif // TEST_FUNC_H
