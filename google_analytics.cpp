#include "google_analytics.h"
#include <QFileInfo>
#include <QFile>
#include <QTextStream>
#include <QUuid>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QUrlQuery>
#include <QDesktopWidget>
#include <QDebug>
#include <QObject>


/*
 * [22-11-2016]
 * constructor used to initiate parameters like
 * analytics id, client id and create if required
 */
google_analytics::google_analytics()
{
    nam = new QNetworkAccessManager(this);
    tid = "UA-87935289-1";
    filename = "cid";

    //checking if client id exists
    QFileInfo check_file(filename);
    if(check_file.exists() && check_file.isFile()){
        QFile file(filename);
        if(file.open(QIODevice::ReadOnly | QIODevice::Text)){
            QByteArray line;
            while(!file.atEnd()){
                line+=file.read(1024);
            }
            cid = QString(line);
        }
        else
            qDebug()<<"cid read failed";
    }
    //client id not found so creating another
    else {
        QUuid uid = QUuid::createUuid();
        QFile file(filename);
        if(file.open(QIODevice::ReadWrite)){
            QTextStream input(&file);
            input<<uid.toString();
            cid = uid.toString();
        }
        else
            qDebug()<<"cid write failed";
    }
}

/*
 * [22-11-2016]
 * initiate function used to send a session start request to
 * analytics server with user details
 */
void google_analytics::initiate(){
    //creates a request string with initial parameters
    QNetworkRequest req(QUrl("http://www.google-analytics.com/collect"));
    req.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");

    //initiates a session start request
    QUrlQuery query;
    query.addQueryItem("v","1");
    query.addQueryItem("tid",tid);
    query.addQueryItem("cid",cid);
    query.addQueryItem("t","event");
    query.addQueryItem("sc","start");
    query.addQueryItem("cd","appstart");

    //gets the desktop resolution information
    QDesktopWidget desktop;
    QString sr = QString::number(desktop.geometry().width())+"x"+QString::number(desktop.geometry().height());
    query.addQueryItem("sr",sr);

    //names the event start
    query.addQueryItem("ec","start");
    //names the action appstart
    query.addQueryItem("ea","appstart");
    //gets the username/system name
    QString name = qgetenv("USER");
    if (name.isEmpty())
        name = qgetenv("USERNAME");
    query.addQueryItem("el",name);

    //adds app specific details name, version, id
    query.addQueryItem("an","infinity-calc-app");
    query.addQueryItem("av","0.9.11306");
    query.addQueryItem("aid","com.encryptorcode.infinitycalc");

    //binds all the data in single request
    QByteArray data;
    data.append(query.query());
//    nam->post(req,data);
}

/*
 * [22-11-2016]
 * terminate function is used to send session end
 * request to analytics server
 */
void google_analytics::terminate(){
    //creates a network string with initial parameters
    QNetworkRequest req(QUrl("http://www.google-analytics.com/collect"));
    req.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");

    //initiates a session end request
    QUrlQuery query;
    query.addQueryItem("v","1");
    query.addQueryItem("tid",tid);
    query.addQueryItem("cid",cid);
    query.addQueryItem("t","event");
    query.addQueryItem("sc","end");

    //binds all the data in a single request
    QByteArray data;
    data.append(query.query());
//    nam->post(req,data);
}

/*
 * [22-11-2016]
 * hit_event function is used to hit the analytics
 * server with event details from the client
 */
void google_analytics::hit_event(QString category, QString action){
    //creates a request string with initial parameters
    QNetworkRequest req(QUrl("http://www.google-analytics.com/collect"));
    req.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");

    //initiate an event request
    QUrlQuery query;
    query.addQueryItem("v","1");
    query.addQueryItem("tid",tid);
    query.addQueryItem("cid",cid);
    query.addQueryItem("t","event");

    //gets the details of the event
    query.addQueryItem("ec",category);
    query.addQueryItem("ea",action);

    //gets the username/system name and sets as the host
    QString name = qgetenv("USER");
    if (name.isEmpty())
        name = qgetenv("USERNAME");
    query.addQueryItem("el",name);

    //binds all the event details in a single request
    QByteArray data;
    data.append(query.query());
//    nam->post(req,data);
}

/*
 * [22-11-2016]
 * hit_page function is used to hit the analytics
 * server with page details from the client
 */
void google_analytics::hit_page(QString path, QString title){
    //creates a request steing with initial parameters
    QNetworkRequest req(QUrl("http://www.google-analytics.com/collect"));
    req.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");

    //initiates a page request
    QUrlQuery query;
    query.addQueryItem("v","1");
    query.addQueryItem("tid",tid);
    query.addQueryItem("cid",cid);
    query.addQueryItem("t","screenview");

    //gets the name of the user and sets as hostname
    QString name = qgetenv("USER");
    if (name.isEmpty())
        name = qgetenv("USERNAME");
    query.addQueryItem("dh",name);
    //gets other details of the page
    query.addQueryItem("cg1",path);
    query.addQueryItem("cd",title);

    //binds all the page details in a single request
    QByteArray data;
    data.append(query.query());
//    nam->post(req,data);
}
