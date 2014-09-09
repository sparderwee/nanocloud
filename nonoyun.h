//read a config file
#ifndef NONOYUN_H
#define NONOYUN_H

#include <QObject>
#include <QFile>
class nonoyun : public QObject
{
    Q_OBJECT
public:

    explicit nonoyun(QObject *parent = 0);
private:
    QFile *xmlfile;
    QString APPKEY;
    QString APPSCRECT;
    QString APPSPACE;
public:

    bool xmlFile_exist;
    QString APPKEY1() {return APPKEY;}
    QString APPSCRECT1(){return APPSCRECT;}
    QString APPSPACE1(){return APPSPACE;}
signals:
    void xmlFile_notexisted();//xml file error
    bool info_get_finished();
public slots:

};

#endif // NONOYUN_H
