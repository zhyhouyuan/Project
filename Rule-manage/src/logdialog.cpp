#include "logdialog.h"
#include "ui_logdialog.h"

logdialog::logdialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::logdialog)
{
    ui->setupUi(this);
    //this->setWindowFlags(Qt::FramelessWindowHint);
    QObject::connect(ui->btnLogin,SIGNAL(clicked()), this, SLOT(send()));
    QObject::connect(ui->btnClose,SIGNAL(clicked()), this, SLOT(on_btnClose_clicked()));
   //QObject::connect(ui->,SIGNAL(clicked()), this, SLOT(on_btnClose_clicked()));
}

logdialog::~logdialog()
{
    delete ui;
}
//QString logdialog::getnametext(){
//    //return this->ui->findname->text();
//    //emit sendflag(ui->buttonBox->button(QDialogButtonBox::Ok));
//    return this->ui->rulebasename->text();
//}
QString logdialog::getpassword(){
    //return this->ui->findname->text();
    //emit sendflag(ui->buttonBox->button(QDialogButtonBox::Ok));
    return this->ui->rulebasepwd->text();
}
QString logdialog::getusername(){
    //return this->ui->findname->text();
    //emit sendflag(ui->buttonBox->button(QDialogButtonBox::Ok));
    return this->ui->username->text();
}
void logdialog::send(){
    //if(ui->buttonBox->button(QDialogButtonBox::Ok)
    emit sendflag(true);
}
void logdialog::on_btnClose_clicked()
{
    this->close();
    emit sendclose_flag(true);
}
