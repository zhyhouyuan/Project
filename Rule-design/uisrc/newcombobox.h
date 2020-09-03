
#ifndef NEWCOMBOBOX_H
#define NEWCOMBOBOX_H

#include <QWidget>
#include <QComboBox>
#include <QMouseEvent>
#include <QListWidget>
class NewComboBox : public QComboBox
{
    Q_OBJECT
public:
    NewComboBox(QWidget*parent=0);
   // void mousePressEvent(QMouseEvent *event);
    QListWidget* getview();

//signals:
//    void clicked(bool);
private:
    QListWidget *view0;

};

#endif // NEWCOMBOBOX_H
