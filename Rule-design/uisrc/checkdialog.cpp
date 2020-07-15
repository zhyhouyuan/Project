#include "checkdialog.h"
#include <QRegularExpression>
checkDialog::checkDialog()
{

}

checkDialog::~checkDialog()
{
}

/***
  *判断一个字符串是否为纯数字
  */
int checkDialog::isDigitStr(QString src)
{
    QByteArray ba = src.toLatin1();//QString 转换为 char*
     const char *s = ba.data();

    while((*s && *s>='0' && *s<='9')||*s=='.') s++;

    if (*s)
    { //不是纯数字
        return -1;
    }
    else
    { //纯数字
        return 0;
    }
}
int checkDialog::search_attribute(QString item){
//    if(item == "实体信息.本地实体列表.本地实体.状态变量列表.实体ID")
//        return 0;
//    else if(item =="实体信息.本地实体列表.本地实体.状态变量列表.名称")
//        return 1;
//    else if(item =="实体信息.本地实体列表.本地实体.状态变量列表.型号")
//        return 2;
//    else if(item =="实体信息.本地实体列表.本地实体.状态变量列表.发射平台ID")
//        return 3;
//    else if(item =="实体信息.本地实体列表.本地实体.状态变量列表.敌我属性")
//        return 4;
//    else if(item =="实体信息.本地实体列表.本地实体.状态变量列表.生存状态")
//        return 5;
//    else if(item =="实体信息.本地实体列表.本地实体.状态变量列表.工作时间")
//        return 6;
//    else if(item =="实体信息.本地实体列表.本地实体.状态变量列表.当前位置")
//        return 7;
//    else
//        return -1;

}

bool checkDialog::check_maxmin(QString type, QString maxvalue,QString minvalue,QString invalue){
    if(type=="double"){
        int flag=isDigitStr(invalue);
        if(flag==0){
            double inv=invalue.toDouble();
            if(!maxvalue.isEmpty()){
                double max_0=maxvalue.toDouble();
                if(inv>max_0) return 0;
            }
            if(!minvalue.isEmpty()){
                double min_0=minvalue.toDouble();
                if(inv<min_0) return 0;
            }
            return 1;
        }
        else return 0;
    }
    else if(type=="int"){
        int flag=isDigitStr(invalue);
        bool indoub=invalue.contains(".");
        if(flag==0&&indoub==0){
            int inv=invalue.toInt();
            if(!maxvalue.isEmpty()){
                int max_0=maxvalue.toInt();
                if(inv>max_0) return 0;
            }
            if(!minvalue.isEmpty()){
                int min_0=minvalue.toInt();
                if(inv<min_0) return 0;
            }
            return 1;
        }
        else return 0;
    }
    else{
        return 1;
    }

}

bool checkDialog::check_rule(QString rule){
    //bool flag =1;
    //int attri_num = -1;
    //根据空格换行等分割字符串
   // QStringList parts=rule.split(QRegularExpression("\\s+"));
//    for(int i=rule.size()-1;i>-0;i--){
//        if()
//    }

   /* C++ STL-style iteration */
//   for (QStringList::iterator it = parts.begin();it != parts.end(); ++it)
//   {
//       QString current = *it;   /* pointer-style dereference */
//        qDebug() << "[[" << current << "]]";
//       flag = 1;
//   }
//    for(int i=0; i<parts.size(); ++i){
//        if (parts.at(i) == "AND" ||parts.at(i) == "OR")
//            continue;
//        else{
//            QString tmp = parts.at(i);
//            QStringList parts2 = tmp.split("=");
//            attri_num = search_attribute(parts2.at(0));
//            //bool attri_flag = check_attribute(parts2.at(1),attri_num);
//            if(attri_flag != true){
//
//                flag = 0;
//                break;
//            }
//        }

//    }

//    if(flag){
//        //ui->checkAns->setText("合理性检验通过");
//        return true;
//    }
//    else{
//        //ui->checkAns->setText("合理性检验未通过");
//        return false;
//    }
}
