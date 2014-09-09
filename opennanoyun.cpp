#include "ui_opennanoyun.h"
#include "api.h"
#include "opennanoyun.h"
#include "nanonetwork.h"
#include "qwidget.h"
opennanoyun::opennanoyun(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::opennanoyun)
{
    ui->setupUi(this);

   nonoyun *xml=new nonoyun(this);

  if(xml->xmlFile_exist)
 {
  ui->le_key->setText(xml->APPKEY1());
  ui->le_scert->setText(xml->APPSCRECT1());
 ui->le_space->setText(xml->APPSPACE1());
 nanonetwork *local1= nanonetwork::getinstance();
 connect(this,SIGNAL(destroyed()),local1,SLOT(logout()));
  return;
  }

ui->btn_connect->setAutoFillBackground(true);
ui->btn_connect->setAutoFillBackground(true);
ui->btn_del->setAutoFillBackground(true);
ui->btn_downland->setAutoFillBackground(true);
ui->lst_file->setAutoFillBackground(true);
ui->le_key->setAutoFillBackground(true);
ui->le_link->setAutoFillBackground(true);
ui->le_scert->setAutoFillBackground(true);
connect(ui->le_key,SIGNAL(textChanged(QString)),SLOT(appkey_input(QString)));

}

opennanoyun::~opennanoyun()
{
    delete ui;
}
void opennanoyun::xml_error()
{
    qDebug("test");
ui->btn_connect->setDisabled(true);
ui->le_key->setText(QString(tr("can't get the config.xml")));
ui->le_scert->setText(QString(tr("please visit http://www.overanchowee.ml")));

}
void opennanoyun::setlbtext()
{
    ui->le_link->clear();
    ui->le_link->setText("ok");
}
void
opennanoyun::appkey_input(QString appkey)
{
    Q_UNUSED(appkey);
    ui->btn_connect->setEnabled(true);
}
