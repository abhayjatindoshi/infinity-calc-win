#include "source_code.h"
#include "ui_source_code.h"
#include "dashboard.h"
#include <QFile>
#include <QDir>
#include <QFileInfo>
#include <QFileDialog>

source_code::source_code(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::source_code)
{
    ui->setupUi(this);
    //[14-11-2016] To disable window resize and maximise button
    this->setWindowFlags(this->windowFlags() | Qt::MSWindowsFixedSizeDialogHint);

    //[21-11-2016] read file INT.h
    QFile file(":/sources/INT.h");
    //[21-11-2016] reads the file and stores in line
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QByteArray line;
    while(!file.atEnd()) line += file.read(1024);
    //[21-11-2016] sets the box with the text that was read
    ui->code->setText(QString(line));
}

source_code::~source_code()
{
    delete ui;
}

void source_code::on_back_clicked()
{
    //[21-11-2016] links to dashboard
    dashboard *dash = new dashboard();
    this->close();
    dash->show();
}

void source_code::on_save_clicked()
{
    //[22-11-2016] hits the google with event
    ga.hit_event("Source Code","Save");
    // [15-11-2016] when source button is clicked the save dialog box appears
    QDir d = QFileDialog::getExistingDirectory(this,"Select folder to save",
                                                QDir::homePath()+"/Desktop/",
                                                QFileDialog::ShowDirsOnly);
    // [15-11-2016] the source file is copied to the path retireved from save dialog box
    QFile::copy(":/sources/INT.h",d.absolutePath()+"/INT.h");
    QFile::copy(":/sources/INT.cpp",d.absolutePath()+"/INT.cpp");
}
