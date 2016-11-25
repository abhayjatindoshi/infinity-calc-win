#include "settings.h"
#include "ui_settings.h"
#include "dashboard.h"

settings::settings(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::settings)
{
    ui->setupUi(this);
    //[14-11-2016] To disable window resize and maximise button
    this->setWindowFlags(this->windowFlags() | Qt::MSWindowsFixedSizeDialogHint);
}

settings::~settings()
{
    delete ui;
}

void settings::on_back_clicked()
{
    //[21-11-2016] links the back to dashboard
    dashboard *dash = new dashboard();
    this->close();
    dash->show();
}
