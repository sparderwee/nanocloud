#ifndef OPENNANOYUN_H
#define OPENNANOYUN_H

#include <QMainWindow>
#include "nonoyun.h"
namespace Ui {
class opennanoyun;
}

class opennanoyun : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit opennanoyun(QWidget *parent = 0);
    ~opennanoyun();
    
private:
    Ui::opennanoyun *ui;
public slots:
    void xml_error();
    void setlbtext();
    void appkey_input(QString appkey);

};

#endif // OPENNANOYUN_H
