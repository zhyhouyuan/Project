#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    //bool CreatCPP();
    bool getfilename();
    void get_checkstate();
    void creatINI();

private slots:
    bool CreatCPP();
    //bool openfile();
    void setfilename(QString);
    void get_path();
    void add_lib();
    void del_lib();
    void lib_copy();
    void get_model();
private:
    Ui::MainWindow *ui;
    QString h_name,cpp_name,path_name,class_name,rule_name,WME_name;
    QString modelfile;
    QList<QString> lib_name;
    QList<Qt::CheckState> checklist;

};

#endif // MAINWINDOW_H
