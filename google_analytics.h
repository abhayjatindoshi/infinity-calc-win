#ifndef GOOGLE_ANALYTICS_H
#define GOOGLE_ANALYTICS_H

#include<QNetworkAccessManager>

class google_analytics : public QObject
{
private:
    QNetworkAccessManager *nam;
    QString tid,cid,filename;

public:
    google_analytics();
    void initiate();
    void terminate();
    void hit_event(QString category, QString action);
    void hit_page(QString path, QString title);
};

#endif // GOOGLE_ANALYTICS_H
