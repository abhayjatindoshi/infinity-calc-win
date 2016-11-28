#include "dashboard.h"
#include <QApplication>
#include <QSplashScreen>
#include <QTimer>
#include <QStyleFactory>
#include <QPalette>
#include "google_analytics.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //[21-11-2016] Sets default styles and colors for the application
    a.setStyle(QStyleFactory::create("Fusion"));
    a.setStyleSheet("QPlainTextEdit{background-color:white; border-radius:10px; border: 1px solid gray;}"
                    "QTextBrowser{background-color:white; border-radius:10px; border: 1px solid gray;}");
    QPalette p;
    p = qApp->palette();
    //[21-11-2016] background color for all the dialogs
    p.setColor(QPalette::Window,QColor(255,255,255));
    //[21-11-2016] backgrond image for all the dialogs
    QPixmap background("://graphics/common/background.png");
    p.setBrush(QPalette::Background,background);
    qApp->setPalette(p);

    //initiates google analytics by sending a session start ping
    google_analytics ga;
    ga.initiate();

    //[13-11-2016] Creates a splash screen from a PNG image and launches it.
    QSplashScreen *splash_screen = new QSplashScreen;
    splash_screen->setPixmap(QPixmap("://graphics/icon_splash/splash_screen.png"));
    splash_screen->show();

    dashboard dash;
    //[22-11-2016] hits google server with page open ping
    ga.hit_page("\\dashboard","Dashboard");

    //[13-11-2016] Timer for closing splash screen and opening dashboard ui
    QTimer::singleShot(2500,splash_screen,SLOT(close()));
    QTimer::singleShot(2500,&dash,SLOT(show()));

    //[23-11-2016] returns exit code on app exit
    int ret=a.exec();
    //[23-11-2016] hits google server of session terminate
    ga.terminate();
    return ret;
}
