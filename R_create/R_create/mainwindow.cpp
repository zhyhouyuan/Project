#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <fstream>
#include <ctime>
#include <unistd.h>
#include<QMutex>
#include<QFileInfo>
#include<QTextStream>
#include<QTime>
#include<QMessageBox>
#include<QFileDialog>
#include<QDebug>
#include <QApplication>
#include "filecopy.h"
using namespace std;
static QMutex mutex;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->name_h->setEnabled(0);
    ui->name_cpp->setEnabled(0);
    this->h_name=nullptr;
    this->cpp_name=nullptr;
    connect(ui->createfile,SIGNAL(clicked()),this,SLOT(CreatCPP()));
    connect(ui->classname,SIGNAL(textChanged(QString)),this,SLOT(setfilename(QString)));
    connect(ui->choose_m,SIGNAL(clicked()),this,SLOT(get_path()));
    connect(ui->choose_p,SIGNAL(clicked()),this,SLOT(get_model()));
    connect(ui->add_lib,SIGNAL(clicked()),this,SLOT(add_lib()));
    connect(ui->del_lib,SIGNAL(clicked()),this,SLOT(del_lib()));
    connect(ui->addrule,SIGNAL(clicked()),this,SLOT(get_path()));
    connect(ui->addwme,SIGNAL(clicked()),this,SLOT(get_path()));
    // 设置窗口名称
    setWindowTitle(tr("代码自动化生成工具"));

}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::get_path(){

    if(sender()==ui->choose_m){
        path_name=QFileDialog::getExistingDirectory(this,QString("文件保存路径"),QString(""));
        QFileInfo file(path_name);
        if(file.isDir())
            ui->savePostion->setText(path_name);
    }
    else if(sender()==ui->addrule){
        rule_name=QFileDialog::getOpenFileName(this,QString("规则描述文件"),QString(""),tr("规则文件(*.xml)"));
        QFileInfo file(rule_name);
        if(file.isFile())
            ui->Rule_path->setText(rule_name);
    }
    else if(sender()==ui->addwme){
        WME_name=QFileDialog::getOpenFileName(this,QString("事实集文件"),QString(""),tr("事实集(*.xml)"));
        QFileInfo file(WME_name);
        if(file.isFile())
            ui->WME_path->setText(WME_name);
    }


}
void MainWindow::get_model(){
    modelfile=QFileDialog::getOpenFileName(this,QString("选择模板文件"),QString("/home"),tr("模板文件(*.txt)"));
    QFileInfo file(modelfile);
    if(file.isFile())
        ui->modelPostion->setText(modelfile);

}
void MainWindow::setfilename(QString classname){
    if(classname.isEmpty()){
        ui->name_cpp->clear();
        ui->name_h->clear();
        return;
    }
    ui->name_h->setText(classname+".h");
    ui->name_cpp->setText(classname+".cpp");
}
bool MainWindow::getfilename(){
    h_name=ui->name_h->text();
    cpp_name=ui->name_cpp->text();
    class_name=ui->classname->text();
    if(h_name.isEmpty()||cpp_name.isEmpty()){
        return 0;
    }
    return 1;
}
void MainWindow::add_lib(){
    QString libname=QFileDialog::getOpenFileName(this,QString("加载库文件"),this->path_name,
                                           tr("头文件(*.h)"));
    QFileInfo file(libname);
    if(!file.isFile()){

        return;
    }
    ui->listWidget->addItem(libname);
}
void MainWindow::del_lib(){
    auto&&it=ui->listWidget->currentItem();
    if(it!=nullptr){
        ui->listWidget->removeItemWidget(it);
    }
}
void MainWindow::lib_copy(){
    QString toDir=path_name+"/lib";
    QDir targetDir(toDir);
    if(!targetDir.exists()){    /**< 如果目标目录不存在，则进行创建 */
        if(!targetDir.mkdir(targetDir.absolutePath()))
            return ;
    }
    for(int i=0;i<ui->listWidget->count();i++){
        QString souceFile=ui->listWidget->item(0)->text();
        QString nameoflib=souceFile.right(souceFile.length()-souceFile.lastIndexOf("/"));
        lib_name.append(nameoflib);
        bool a=copyFileToPath(souceFile,path_name+"/lib"+nameoflib,1);
    }
    if(rule_name.isNull()){
        copyFileToPath(rule_name,path_name+"/rule_out.xml",1);
    }
    if(WME_name.isNull()){
        copyFileToPath(rule_name,path_name+"/wmes.xml",1);
    }
}
void MainWindow::get_checkstate(){
    checklist.clear();
    checklist.append(ui->checkBox_1->checkState());
    checklist.append(ui->checkBox_2->checkState());
    checklist.append(ui->checkBox_3->checkState());
    checklist.append(ui->checkBox->checkState());

}
bool MainWindow::CreatCPP(){
    mutex.lock();
    getfilename();
    get_checkstate();
    QFile file_m(modelfile);
    int ok;
    if(!file_m.open(QIODevice::ReadOnly)){
        QMessageBox::warning(this,QString("提示"),QString("模板文件打开失败"));
        return 0;
    }
    QTextStream in(&file_m);//模板文件读入流

    if(path_name.isNull()){
        QMessageBox::warning(this,QString("提示"),QString("未选择文件保存路径"));
        return 0;
    }
    QString filename=path_name+"/"+h_name;
    QString filename2=path_name+"/"+cpp_name;
   // QString filename_main=path_name+"/"+"main.cpp";

    QString current_date_time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss ddd");
    QFileInfo file0(filename);//判断文件是否存在；
    bool flag=1;
    if(file0.isFile()){
        ok =QMessageBox::warning(this,QString("提示"),QString("文件已存在,是否替换？"),QMessageBox::Yes,QMessageBox::No);
        flag=0;
    }
    in.setCodec("utf-8");
    lib_copy();
    if(flag||ok==QMessageBox::Yes){
        QFile file(filename);
        file.open(QIODevice::WriteOnly | QIODevice::Truncate);
        QTextStream out(&file);
         out.setCodec("utf-8");
        out << "#ifndef "+class_name.toUpper()+"_H"<<endl;
        out << "#define "+class_name.toUpper()+"_H" <<endl;
        for(int i=0;i<lib_name.count();i++){
             out << "#include \"/lib"+lib_name.at(i)+"\"" << endl;
        }
        while(1){
            QString wrt=in.readLine();
            out<<wrt<<endl;
            if(wrt.isNull()||wrt=="//@class_h"){
                break;
            }
        }
        out << "/******************************" << endl;
        out << " * author: zhy" << endl;//获取当前*nix系统的当前用户名
        out << " * time:"  << current_date_time << endl;
        out << " *" << endl;
        out << "*****************************/" << endl;
        out << "class "+ class_name<< endl;
        out << "{" << endl;
        out << endl;
        out <<"public:"<<endl;
        out <<"\t"+class_name+"::"+class_name+"();"<<endl;
        out <<"\t~"+class_name+"();"<<endl;
        QStringList list0;
        list0<<"Retetest();"<<"Treattest();"<<"Clipstest();";
        for(int i=0;i<3;i++){
            if(checklist.at(0)==Qt::Checked){
                out<<"\t"+list0.at(i)<<endl;
            }
        }
        out << "}" << endl;
        out << "#endif "+class_name.toUpper()+"_H" <<endl;
        file.flush();
        file.close();
    }
    QFileInfo file1(filename2);//判断.cpp文件是否存在；
    flag=1;
    if(file1.isFile()){
        ok =QMessageBox::warning(this,QString("提示"),QString("文件已存在,是否替换？"),QMessageBox::Yes,QMessageBox::No);
        flag=0;
    }
    if(flag||ok==QMessageBox::Yes){
        QFile file(filename2);
        file.open(QIODevice::WriteOnly | QIODevice::Truncate);
        QTextStream out(&file);
        out.setCodec("utf-8");
        while(!in.readLine().isNull()){
            if(in.readLine()=="//@class_cpp")
                break;
        }
        out << in.readLine().replace("@class_name",class_name) << endl;
        out << "/******************************" << endl;
        out << " * author: zhy" << endl;//获取当前*nix系统的当前用户名
        out << " * time:"  << current_date_time << endl;
        out << " *" << endl;
        out << "*****************************/" << endl;
        out << "using namespace std;" << endl;
        while(1){
            QString wrt=in.readLine();
            out<<wrt.replace("@class_name",class_name)<<endl;
            if(wrt.isNull()||wrt=="//@Rete"){
                break;
            }
        }
        if(checklist.at(0)==Qt::Checked){
            out<<in.readLine().replace("@class_name",class_name)<<endl;
            while(1){
                QString wrt=in.readLine();
                if(wrt.isNull()||wrt=="//@Treat"){
                    break;
                }
                out<<wrt<<endl;
            }
        }
        else{
            while(1){
                QString wrt=in.readLine();
                if(wrt.isNull()||wrt=="//@Treat"){
                    break;
                }
            }
        }
        if(checklist.at(1)==Qt::Checked){
            out<<in.readLine().replace("@class_name",class_name)<<endl;
            while(1){
                QString wrt=in.readLine();
                if(wrt.isNull()||wrt=="//@Clips"){
                    break;
                }
                out<<wrt<<endl;
            }
        }
        else{
            while(1){
                QString wrt=in.readLine();
                if(wrt.isNull()||wrt=="//@Clips"){
                    break;
                }
            }
        }
        if(checklist.at(2)==Qt::Checked){
            out<<in.readLine().replace("@class_name",class_name)<<endl;
            while(1){
                QString wrt=in.readLine();
                if(wrt.isNull()||wrt=="//@end"){
                    break;
                }
                out<<wrt<<endl;
            }
        }
        else{
            while(1){
                QString wrt=in.readLine();
                if(wrt.isNull()||wrt=="//@end"){
                    break;
                }
            }
        }
        if(checklist.at(3)==Qt::Checked){
            out << "int main()" << endl;
            out << "{" << endl;
            out <<"\t"+class_name+" *"+class_name+"0 //对象的实例";
            checklist.at(0)==Qt::Checked?out<<class_name+"0->"+"Retetest()"<<endl:out<<endl;
            checklist.at(1)==Qt::Checked?out<<class_name+"0->"+"Treattest()"<<endl:out<<endl;
            checklist.at(2)==Qt::Checked?out<<class_name+"0->"+"Clipstest()"<<endl:out<<endl;
            out <<"return 0;"<<endl;
            out << endl;
            out << "}" << endl;
        }
        file.flush();
        file.close();
    }
    creatINI();
    mutex.unlock();
}
void MainWindow::creatINI(){
   QString INIname=path_name+"/config.ini";
   QFile file(INIname);
   file.open(QIODevice::WriteOnly | QIODevice::Truncate);
   QTextStream out(&file);
   out<<"[algorithm]"<<endl;
   if(ui->checkBox_1->isChecked()){
       out<<"algo=rete";
   }
   if(ui->checkBox_2->isChecked()){
       out<<"algo=treat";
   }
   if(ui->checkBox_3->isChecked()){
       out<<"algo=clips";
   }
   file.flush();
   file.close();
}

