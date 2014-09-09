#include "nanonetwork.h"
#include "qnetwork.h"
#include "qnetworkrequest.h"
#include "qjsondocument.h"
#include <QTextCodec>
#include <QJsonParseError>

nanonetwork *nanonetwork::Instance=NULL;
nanonetwork *nanonetwork::getinstance()
{
    if(NULL==Instance)
    Instance=new nanonetwork;
    return Instance;
}
nanonetwork::nanonetwork(QObject *parent) :
    QObject(parent)
{
    qDebug("network module");
    server_status=QString(tr("ready......"));
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
     QNetworkRequest request;
     request.setUrl(QUrl(QString(_APIServer)));
    request.setRawHeader("User-Agent","Mozilla/5.0 (Windows NT 6.1) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/34.0.1847.116 Safari/537.36");

    reply=manager->get(request);
    connect(reply,SIGNAL(readyRead()),this,SLOT(get_server_status()));
    connect(reply,SIGNAL(finished()),this,SLOT(Auth_require()));
    qDebug("finished");

}
void nanonetwork::get_server_status()
{

   qDebug(reply->readAll());
   server_status.clear();
   if(!reply->readAll().isEmpty())
   {
       server_status=QString(tr("server online"));
   }
  server_status=QString(tr("server offline"));
}
void nanonetwork::Auth_require()
{
  nonoyun appinfo;
  map["appkey"]=appinfo.APPKEY1();
  map["appsecret"]=appinfo.APPSCRECT1();
  map["response_type"]=QString("code");

  QNetworkAccessManager *manager = new QNetworkAccessManager(this);
  QNetworkRequest request;
  QUrl auth_url(_AUTH+QString("appkey=")+map["appkey"]+"&"+QString("appsecret=")+map["appsecret"]+"&"+QString("response_type=")+map["response_type"]);
  request.setUrl(auth_url);
  request.setRawHeader("User-Agent","Mozilla/5.0 (Windows NT 6.1) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/34.0.1847.116 Safari/537.36");
  reply=manager->get(request);
  qDebug("json get");
  disconnect(reply,SIGNAL(readyRead()),this,SLOT(get_server_status()));
  connect(reply,SIGNAL(readyRead()),this,SLOT(get_json()));

}
void nanonetwork::get_json()
{
    QTextCodec *codec = QTextCodec::codecForName("utf-8");
    QString json = codec->toUnicode(reply->readAll());

    disconnect(reply,SIGNAL(finished()),this,SLOT(Auth_require()));
    phraser_json(json);

}
void nanonetwork::phraser_json(const QString &json)
{

 QJsonParseError parseerr;
 QVariant result = QJsonDocument::fromJson(json.toUtf8(), &parseerr).toVariant();
 if (parseerr.error == QJsonParseError::NoError) {
        QVariantMap obj = result.toMap();
        if (obj["r"].toInt() != 0) {
            qDebug() << Q_FUNC_INFO << "ReloginErr: " << obj["err"].toString();
            return;
        }

        access_token = obj["access_token"].toString();
        expires_in = obj["expires_in"].toInt();
        json_finished=true;
    }
 qDebug()<<access_token;

}
void nanonetwork::logout()
{

    reply->deleteLater();
}

void nanonetwork::make_request(QString token, int &method, QString url)
{
    token=this->access_token;
    url=QString("api.nanoyun.com");
    if(token.isEmpty()) {
        qDebug()<<"token empty";
        token=this->access_token;
        return;}
    CURL *make_pos=curl_easy_init();
    switch (method) {
    case 1://post
        curl_easy_setopt(make_pos,CURLOPT_SSL_VERIFYPEER,false);
        curl_easy_setopt(make_pos,CURLOPT_SSL_VERIFYHOST,false);
         curl_easy_setopt(make_pos,CURLOPT_HEADER,false);
          curl_easy_setopt(make_pos,CURLOPT_POST,true);
          curl_easy_setopt(make_pos,CURLOPT_POSTFIELDS,access_token.toStdString().c_str());
           //curl_easy_setopt(make_pos,CURLINFO_HEADER_OUT,true);
            curl_easy_setopt(make_pos,CURLOPT_HEADER,url.toStdString().c_str());
        break;
    case 2: //put

        break;
    default:
        break;
    }


}
