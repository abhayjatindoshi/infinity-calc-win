#include "about_me.h"
#include "ui_about_me.h"
#include "dashboard.h"
#include <QFile>

about_me::about_me(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::about_me)
{
    ui->setupUi(this);
    //[14-11-2016] To disable window resize and maximise button
    this->setWindowFlags(this->windowFlags() | Qt::MSWindowsFixedSizeDialogHint);

    //[21-11-2016] read file license.txt
    QFile file(":/sources/license.txt");
    //[21-11-2016] opens the file and reads to line
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QByteArray line="";
    while(!file.atEnd()) line+= file.read(1024);
    //[21-11-2016] sets the dialog with variable line
    ui->license->setText(QString(line));
}

about_me::~about_me()
{
    delete ui;
}

void about_me::on_back_clicked()
{
    //[15-11-2016] connects back button to dashboard
    dashboard *dash = new dashboard();
    this->close();
    dash->show();
}
