#include "dashboard.h"
#include "ui_dashboard.h"
#include "quick_calc.h"
#include "test_func.h"
#include "source_code.h"
#include "settings.h"
#include "about_me.h"
#include <QUrl>
#include <QDesktopServices>
#include "google_analytics.h"

dashboard::dashboard(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::dashboard)
{
    ui->setupUi(this);
    //[14-11-2016] To disable window resize and maximise button
    this->setWindowFlags(this->windowFlags() | Qt::MSWindowsFixedSizeDialogHint);
}

dashboard::~dashboard()
{
    delete ui;
}

/*
 * [14-11-2016]
 * linking the buttons to the relevant dialogs
 *   >test-func
 *   >know-me
 * [15-11-2016]
 * linked the other two left buttons
 *   >bug-feed
 *   >quick-calc
 * [21-11-2016]
 * remade the whole layout with the following options
 *   >quick-calc
 *   >test-func
 *   >source-code
 *   >bugs-feedback
 *   >settings
 *   >about-me
 */

void dashboard::on_quick_calc_clicked()
{
    //[15-11-2016] linked with quick calc dialog
    quick_calc *ui = new quick_calc();
    this->close();
    ui->show();
    //[22-11-2016] hits google server with page open ping
    ga.hit_page("\\dashboard\\quick-calc","Quick Calc");
}

void dashboard::on_test_func_clicked()
{
    //[15-11-2016] linked with test func dialog
    test_func *ui = new test_func();
    this->close();
    ui->show();
    //[22-11-2016] hits google server with page open ping
    ga.hit_page("\\dashboard\\test-func","Test Func");
}

void dashboard::on_source_code_clicked()
{
//    //[21-11-2016] linked with the source code dialog
//    source_code *ui = new source_code();
//    this->close();
//    ui->show();
//    //[22-11-2016] hits google server with page open ping
//    ga.hit_page("\\dashboard\\source-code","Source Code");
}

void dashboard::on_bugs_feedback_clicked()
{
    //[22-11-2016] hits google server with page open ping
    ga.hit_page("\\dashboard\\bugs-feedback","Bugs Feedback");
    //[15-11-2016] opens the link of the feedback form that is stored online
    QString link = "https://goo.gl/forms/whELGvlB4hei2I3x1";
    QDesktopServices::openUrl(QUrl(link,QUrl::TolerantMode));
}

void dashboard::on_settings_clicked()
{
//    //[21-11-2016] links to the settings dialog
//    settings *ui = new settings();
//    this->close();
//    ui->show();
//    //[22-11-2016] hits google server with page open ping
//    ga.hit_page("\\dashboard\\settings","Settings");
}

void dashboard::on_about_me_clicked()
{
    //[15-11-2016] linked to about_me dialog
    about_me *ui = new about_me();
    this->close();
    ui->show();
    //[22-11-2016] hits google server with page open ping
    ga.hit_page("\\dashboard\\about-me","About Me");
}
