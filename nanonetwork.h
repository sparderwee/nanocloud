#ifndef NANONETWORK_H
#define NANONETWORK_H
//network interaction
#include <QObject>
#include "qnetworkaccessmanager.h"
#include "api.h"
#include "qnetworkreply.h"
#include "qvector.h"
#include "curl/curl.h"
class nanonetwork : public QObject
{
    Q_OBJECT
public:
    static nanonetwork *getinstance();
     bool json_finished;
signals:

public slots:
    void get_server_status();
    void Auth_require();
    void get_json();
    void logout();

    void make_request(QString token, int &method, QString url);

private:
    QNetworkReply *reply;
    QMap<QString, QString> map;
    void phraser_json(const QString &json);
    QString server_status;
    QString access_token;
    int expires_in;
    explicit nanonetwork(QObject *parent = 0);
    static nanonetwork *Instance;


public:
    QString server_status1() {return server_status;}
    QString access_token1() {return access_token;}
    int expires_in1(){return expires_in;}



};

#endif // NANONETWORK_H
