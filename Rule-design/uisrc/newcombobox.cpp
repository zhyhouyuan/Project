#include "newcombobox.h"
#include <QListView>
NewComboBox::NewComboBox(QWidget *parent):QComboBox(parent)
{
   view0=new QListWidget();
   this->setView(view0);

}
QListWidget* NewComboBox::getview(){
    return this->view0;
}
//void NewComboBox::mousePressEvent(QMouseEvent *event)
//{
//    if(event->button() == Qt::LeftButton)
//    {
//        emit clicked(this->currentIndex());
//    }
//    QComboBox::mousePressEvent(event);
//}
