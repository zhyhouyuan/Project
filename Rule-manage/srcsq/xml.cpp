#include "xml.h"
#include <QCoreApplication>
#include<QFileDialog>
#include <QtXml> //也可以include <QDomDocument>
XML::XML()
{

}
void XML::WriteXml(QString dirPath){
     //QString dirPath;//创建文件夹路径
     //QString filePath;//存储保存路径
     //QString saveName="mydb.sql";//保存图片名字
     QDateTime time2 = QDateTime::currentDateTime();//获取系统现在的时间
     QString str = time2.toString("yyyyMMdd_hhmmss"); //设置显示格式

    //filePath = QFileDialog::getExistingDirectory("");//获取文件夹路径

    QFile file(dirPath); //相对路径、绝对路径、资源路径都可以
    if(!file.open(QFile::WriteOnly|QFile::Truncate)) //可以用QIODevice，Truncate表示清空原来的内容
        return;

    QDomDocument doc;
    //写入xml头部
    QDomProcessingInstruction instruction; //添加处理命令
    instruction=doc.createProcessingInstruction("xml","version=\"1.0\" encoding=\"UTF-8\"");
    doc.appendChild(instruction);
    //添加根节点
    QDomElement root=doc.createElement("rulebase");
    doc.appendChild(root);


    //添加第一个子节点及其子元素
    QDomElement rule=doc.createElement("rule");
    rule.setAttribute("id",1); //方式一：创建属性  其中键值对的值可以是各种类型
    QDomAttr time=doc.createAttribute("time"); //方式二：创建属性 值必须是字符串
    time.setValue("2013/6/13");
    rule.setAttributeNode(time);


    QDomElement Rule_if=doc.createElement("if"); //创建子元素
    QDomText text; //设置括号标签中间的值
    text=doc.createTextNode("这是条件");
    rule.appendChild(Rule_if);
    Rule_if.appendChild(text);
    QDomElement Rule_then=doc.createElement("then"); //创建子元素
    text=doc.createTextNode("这是结果");
    Rule_then.appendChild(text);
    rule.appendChild(Rule_then);

    QDomElement Rule_W=doc.createElement("then"); //创建子元素
    text=doc.createTextNode("这是权重");
    Rule_W.appendChild(text);
    rule.appendChild(Rule_W);

    root.appendChild(rule);


    //添加第二个子节点及其子元素，部分变量只需重新赋值
    rule=doc.createElement("book");
    rule.setAttribute("id",2);
    time=doc.createAttribute("time");
    time.setValue("2007/5/25");
    rule.setAttributeNode(time);
    Rule_if=doc.createElement("Rule_if");
    text=doc.createTextNode("Thinking in Java");
    rule.appendChild(Rule_if);
    Rule_if.appendChild(text);
    Rule_then=doc.createElement("Rule_then");
    text=doc.createTextNode("Bruce Eckel");
    Rule_then.appendChild(text);
    rule.appendChild(Rule_then);
    root.appendChild(rule);

    //输出到文件
    QTextStream out_stream(&file);
    doc.save(out_stream,4); //缩进4格
    file.close();
}
void ReadXml(QString dirfile)
{
    //打开或创建文件
    QFile file(dirfile); //相对路径、绝对路径、资源路径都行
    if(!file.open(QFile::ReadOnly))
        return;

    QDomDocument doc;
    if(!doc.setContent(&file))
    {
        file.close();
        return;
    }
    file.close();
    QDomElement root=doc.documentElement(); //返回根节点
    QDomNode node=root.firstChild(); //获得第一个子节点
    while(!node.isNull())  //如果节点不空
    {
        if(node.isElement()) //如果节点是元素
        {
            QDomElement e=node.toElement(); //转换为元素，注意元素和节点是两个数据结构，其实差不多
            //qDebug()<<e.tagName()<<" "<<e.attribute("id")<<" "<<e.attribute("time"); //打印键值对，tagName和nodeName是一个东西
            QDomNodeList list=e.childNodes();
            for(int i=0;i<list.count();i++) //遍历子元素，count和size都可以用,可用于标签数计数
            {
                QDomNode n=list.at(i);
                if(node.isElement())
                    qDebug()<<n.nodeName()<<":"<<n.toElement().text();
            }
        }
        node=node.nextSibling(); //下一个兄弟节点,nextSiblingElement()是下一个兄弟元素，都差不多
    }
}
