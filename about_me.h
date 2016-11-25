#ifndef ABOUT_ME_H
#define ABOUT_ME_H

#include <QWidget>
#include "google_analytics.h"

namespace Ui {
class about_me;
}

class about_me : public QWidget
{
    Q_OBJECT

public:
    explicit about_me(QWidget *parent = 0);
    ~about_me();
    //[22-11-2016] added google analytics to this page
    google_analytics ga;

private slots:
    void on_back_clicked();

private:
    Ui::about_me *ui;
};

#endif // ABOUT_ME_H
