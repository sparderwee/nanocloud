#include "nonoyun.h"
#include <QDir>
#include<QDomDocument>
#include<QDomElement>
nonoyun::nonoyun(QObject *parent) :
    QObject(parent)
{

    xmlfile = new QFile(QDir::currentPath()+QString("/config.xml"));
    if(!xmlfile->open(QIODevice::ReadOnly| QIODevice::Text))
    {
        qDebug("not find the xml");
        xmlFile_exist=false;

         return;
    }
   const QByteArray file_get=xmlfile->readAll();
    xmlfile->close();
    qDebug(file_get);
    QDomDocument xmlreader("xmlfile");
    if (!xmlreader.setContent(file_get)){
        return;
    }
    QDomElement get_root=xmlreader.documentElement();
    QDomElement get_appkey=get_root.firstChildElement("APPKEY");
    APPKEY=get_appkey.text();
    qDebug(APPKEY.toUtf8());
    QDomElement get_appscert=get_appkey.nextSiblingElement("APPSECRET");
    APPSCRECT=get_appscert.text();
    qDebug(APPSCRECT.toUtf8());
     QDomElement get_space=get_appscert.nextSiblingElement("SPACENAME");
     APPSPACE=get_space.text();
     qDebug(APPSPACE.toUtf8());
     emit info_get_finished();
}
