#include "change_wdialog.h"
#include "ui_change_wdialog.h"

Change_WDialog::Change_WDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Change_WDialog)
{
    ui->setupUi(this);
    setWindowTitle(tr("修改权重"));
    //setWindowFlags(Qt::FramelessWindowHint);
    QObject::connect(ui->pushButton,SIGNAL(clicked()), this, SLOT(send_ch()));

}
void Change_WDialog::send_ch(){

    //if(ui->buttonBox->button(QDialogButtonBox::Ok)
    emit send_chflag(ui->spinBox->value());
}
Change_WDialog::~Change_WDialog()
{
    delete ui;
}
void Change_WDialog::set_wdata(int w){
    //if(ui->buttonBox->button(QDialogButtonBox::Ok)
    ui->spinBox->setValue(w);
}
