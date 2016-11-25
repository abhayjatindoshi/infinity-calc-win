#ifndef DASHBOARD_H
#define DASHBOARD_H

#include <QMainWindow>
#include "google_analytics.h"

namespace Ui {
class dashboard;
}

class dashboard : public QMainWindow
{
    Q_OBJECT

public:
    //[22-11-2016] added google analytics to this page
    google_analytics ga;
    explicit dashboard(QWidget *parent = 0);
    ~dashboard();

private slots:
    void on_test_func_clicked();

    void on_quick_calc_clicked();

    void on_source_code_clicked();

    void on_bugs_feedback_clicked();

    void on_settings_clicked();

    void on_about_me_clicked();

private:
    Ui::dashboard *ui;
};

#endif // DASHBOARD_H
