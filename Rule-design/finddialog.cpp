#include "finddialog.h"
#include "ui_finddialog.h"

findDialog::findDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::findDialog)
{
    ui->setupUi(this);
    QObject::connect(ui->buttonBox,SIGNAL(accepted()), this, SLOT(send()));
    ui->findname->setEnabled(0);
     ui->findname_2->setEnabled(0);
     ui->findname_3->setEnabled(0);
     ui->findname->setStyleSheet(QString("QLineEdit{border:1px solid rgb(180, 180, 180);border-radius: 4px;} QLineEdit::hover{color:green border-color:rgb(50,480,40);background-color:green;}QLineEdit::disabled{background-color:gray;}QLineEdit::Enabled{background-color:white;}"));
    //QObject::connect(ui->checkBox,SIGNAL(), this, SLOT(send()));
}

findDialog::~findDialog()
{
    delete ui;
}
QList<QString> findDialog::getfindtext(){
    QList<QString> findlist;
    //return this->ui->findname->text();
    if(ui->checkBox->isChecked()){
        findlist.append(this->ui->findname->text());
    }
    else{
        findlist.append(nullptr);
    }
    if(ui->checkBox_2->isChecked()){
        findlist.append(this->ui->findname_2->text());
    }
    else{
        findlist.append(nullptr);
    }
    if(ui->checkBox_3->isChecked()){
        findlist.append(this->ui->findname_3->text());
    }
    else{
        findlist.append(nullptr);
    }

    //emit sendflag(ui->buttonBox->button(QDialogButtonBox::Ok));
    //qDebug()<<findlist;
    return findlist;

}
void findDialog::send(){
    //if(ui->buttonBox->button(QDialogButtonBox::Ok)
    emit sendflag(true);
}
