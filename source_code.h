#ifndef SOURCE_CODE_H
#define SOURCE_CODE_H

#include <QWidget>
#include "google_analytics.h"

namespace Ui {
class source_code;
}

class source_code : public QWidget
{
    Q_OBJECT

public:
    explicit source_code(QWidget *parent = 0);
    ~source_code();
    //[22-11-2016] added google analytics to this page
    google_analytics ga;

private slots:
    void on_back_clicked();

    void on_save_clicked();

private:
    Ui::source_code *ui;
};

#endif // SOURCE_CODE_H
