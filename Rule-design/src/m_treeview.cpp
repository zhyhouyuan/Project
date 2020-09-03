#include "m_treeview.h"
#include"link.h"
#include<QtDebug>
#include<QFileDialog>
#include<QSqlRecord>
#include<QMessageBox>
M_TreeView::M_TreeView(QWidget *parent):QTreeView (parent)
{

   this->model=new QStandardItemModel(this);
   QObject::connect(this->model,SIGNAL(itemChanged(QStandardItem*)), this,SLOT(treeItemChanged(QStandardItem*)));
   // QObject::connect(this->model,SIGNAL(itemChanged(QStandardItem*)), this,SLOT(treeItemChanged(QStandardItem*)));
    this->setModel(model);
   a_flag=1;
    //initmodel();
}
QStandardItem* M_TreeView::addmodelItem(QStandardItem*item0,QStringList *list0){
    QStandardItem* item1 = new QStandardItem(list0->front());
    item1->setCheckable(true);
    item1->setTristate(true);
    QIcon icon1;
    icon1.addFile(QStringLiteral(":/image/itemicon.jpg"), QSize(), QIcon::Normal, QIcon::Off);
    item1->setIcon(icon1);
    item0->appendRow(item1);
    return item1;
}
/*QStandardItem* M_TreeView::findchilditem(QStandardItem *parent,QString text){
    if(parent->rowCount()==0){
        return this->addmodelItem(parent,&(QStringList()<<text));
    }
    else{
        for(int i=0;i<parent->rowCount();i++){
            if(parent->child(i)->text()==text)
                return parent->child(i);
        }
        return this->addmodelItem(parent,&(QStringList()<<text));;
    }
}*/
void M_TreeView::clealmodel(){
    this->model->clear();
    initmodel();
}
void M_TreeView::LoadScape(QSqlTableModel*modelroot){
    model_root=modelroot;
    QString filePath = QFileDialog::getOpenFileName(this,tr("加载场景文件")," ", tr("XML files (*.xml);;ALL files (*.*)"));
    QDomDocument doc0;
    QFile file(filePath); //相对路径、绝对路径、资源路径都行
    if(!file.open(QFile::ReadOnly))
        return;
    if(!doc0.setContent(&file))
    {
        file.close();
        QMessageBox::warning(this,QString("提示"),QString("打开文件失败!"));
        qWarning()<<"打开场景文件失败";
        return;
    }
   clealmodel();
   file.close();
   QDomElement root=doc0.documentElement(); //返回根节点
   QDomNode node=root.firstChild();//红方
   //编队解析
   rb_flg=0;
   QDomNode node1=node.lastChild();
   while(!node1.isNull())  //如果节点不空
    {
       if(node1.isElement()) //如果节点是元素
        {
          QDomElement e=node1.toElement(); //转换为元素，注意元素和节点是两个数据结构，其实差不多
          this->additem(e,model->item(0));
         }
         node1=node1.nextSibling();
      }
   QDomNode node0=node.firstChild().firstChild();//平台结点
   while (!node0.isNull()) {
       if(node0.isElement()){
           QDomElement e=node0.toElement();
           auto item0=name_item[e.attribute("编队名称")];

           if(item0!=nullptr){
               QStandardItem* item2;
               item2 = new QStandardItem(e.attribute("name"));
               item2->setCheckable(true);
               item2->setTristate(true);
               QIcon icon1;
               icon1.addFile(QStringLiteral(":/image/itemicon.jpg"), QSize(), QIcon::Normal, QIcon::Off);
               item2->setIcon(icon1);
               item0->appendRow(item2);

               this->additem(node0,item2);
           }
       }
       node0=node0.nextSibling();
   }

   node=root.firstChild().nextSibling();//蓝方
   //编队解析
   rb_flg=1;
   node1=node.lastChild();
   while(!node1.isNull())  //如果节点不空
    {
       if(node1.isElement()) //如果节点是元素
        {
          QDomElement e=node1.toElement(); //转换为元素，注意元素和节点是两个数据结构，其实差不多
          this->additem(e,model->item(1));
         }
         node1=node1.nextSibling();
    }
   node0=node.firstChild().firstChild();//蓝方平台结点
   while (!node0.isNull()) {
       if(node0.isElement()){
           QDomElement e=node0.toElement();
           auto item0=name_item[e.attribute("编队名称")];

           if(item0!=nullptr){
               QStandardItem* item2;
               item2 = new QStandardItem(e.attribute("name"));
               item2->setCheckable(true);
               item2->setTristate(true);
               QIcon icon1;
               icon1.addFile(QStringLiteral(":/image/itemicon.jpg"), QSize(), QIcon::Normal, QIcon::Off);
               item2->setIcon(icon1);
               item0->appendRow(item2);
               this->additem(node0,item2);
           }
       }
       node0=node0.nextSibling();
   }
   qDebug()<<QString("导入场景信息成功");
}
void M_TreeView::additem(QDomNode itemnode,QStandardItem *item0){
   QStringList checklist0;
   checklist0<<"类型"<<"型号"<<"模式"<<"任务";
    if(itemnode.isElement()) //如果节点是元素
    {
        QDomNodeList list=itemnode.childNodes();
        if(list.isEmpty()){
           QDomElement en=itemnode.toElement();
            if(itemnode.toElement().tagName()=="设备"){
                int ID=-1;
                QString tablename;
                 QStringList head;
                for(int row=0;row<model_root->rowCount();row++){
                    QSqlRecord list0=model_root->record(row);
                    if(list0.value(1).toString()==en.attribute(checklist0.at(0)) && list0.value(2).toString()==en.attribute(checklist0.at(1)) && list0.value(3).toString()==en.attribute(checklist0.at(2)) && list0.value(4).toString()==en.attribute(checklist0.at(3))){
                        ID=list0.value(0).toInt();
                        tablename=list0.value(5).toString();
                        head<<list0.value(5).toString()<<list0.value(4).toString()<<list0.value(3).toString()<<list0.value(2).toString()<<list0.value(1).toString();
                        break;
                    }
                }
                //item_table[item0].first()=tablename;
                item_table[item0]=ID;
                headnamelist[ID]=head;
                item_tablename[ID]=tablename;
                if(rb_flg)
                    IDlist_blue[ID]+=1;
                else
                    IDlist_red[ID]+=1;
            }
            if(itemnode.toElement().tagName()=="编队2"){
                name_item[en.attribute("name")]=item0;
            }
            return;
        }
        for(int i=0;i<list.count();i++) //遍历子元素，count和size都可以用,可用于标签数计数
        {
            QDomNode n=list.at(i);
            QDomElement en=n.toElement();
            if(en.attribute("name")!=""){
                QStandardItem* item2;
                item2 = new QStandardItem(en.attribute("name"));
                additem(n,item2);
                item2->setCheckable(true);
                item2->setTristate(true);
                QIcon icon1;
                icon1.addFile(QStringLiteral(":/image/itemicon.jpg"), QSize(), QIcon::Normal, QIcon::Off);
                item2->setIcon(icon1);
                item0->appendRow(item2);
            }
            else{
                QStandardItem* item2;
                item2 = new QStandardItem(en.tagName());
                item2->setCheckable(true);
                item2->setTristate(true);
                QIcon icon1;
                icon1.addFile(QStringLiteral(":/image/itemicon.jpg"), QSize(), QIcon::Normal, QIcon::Off);
                item2->setIcon(icon1);
                additem(n,item2);
                item0->appendRow(item2);
            }
        }
    }
}
void M_TreeView::initmodel(){
        model->setHorizontalHeaderLabels(QStringList()<<QStringLiteral("场景信息"));
        model->horizontalHeaderItem(0)->setFont(QFont(QString::fromUtf8("Microsoft YaHei"),12));
        QStandardItem* itemProject = new QStandardItem(QStringLiteral("红方"));
       // QIcon icon0();
        itemProject->setCheckable(true);
        itemProject->setTristate(true);
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/image/redIcon.jpg"), QSize(), QIcon::Normal, QIcon::Off);
        itemProject->setIcon(icon1);

        model->appendRow(itemProject);
       // model->setItem(model->indexFromItem(itemProject).row(),1,new QStandardItem(QStringLiteral("信息说明")));
        itemProject = new QStandardItem(QStringLiteral("蓝方"));
        itemProject->setCheckable(true);
        itemProject->setTristate(true);

        QIcon icon2;
        icon2.addFile(QStringLiteral(":/image/blueIcon.jpg"), QSize(), QIcon::Normal, QIcon::Off);
        itemProject->setIcon(icon2);
        model->appendRow(itemProject);
        //model->setItem(model->indexFromItem(itemProject).row(),1,new QStandardItem(QStringLiteral("信息说明")));
}
void M_TreeView::treeItemChanged(QStandardItem* item){

    if ( item == nullptr ||a_flag==0)
    return ;
    a_flag=0;
    if ( item->isCheckable())
    {
    //如果条目是存在复选框的，那么就进行下面的操作
        Qt::CheckState state = item->checkState (); //获取当前的选择状态
        int rowCount = item->rowCount();
//        if(rowCount<=0){
//            CheckList[item_table[item]]+=1*(state==Qt::Checked?1:-1);
//        }
        if(item->isTristate()){
        //如果条目是三态的，说明可以对子目录进行全选和全不选的设置
            if ( state != Qt::PartiallyChecked ){
            //当前是选中状态，需要对其子项目进行全选
                //if(state)
               // m_checkedList.append(item->index());
                treeItem_checkAllChild (item , state == Qt::Checked ? true : false );
                treeItem_CheckChildChanged (item);
            }
         }
        else
        {
            treeItem_CheckChildChanged ( item );
       }
    }
    a_flag=1;
    emit sendChange(true);
}
void M_TreeView::treeItem_checkAllChild(QStandardItem * item, bool check)
{
    if(item == nullptr)return;
    int rowCount = item->rowCount();
    if(rowCount<=0){
        CheckList[item_table[item]]+=1*(check?1:-1);
    }
    for(int i=0;i<rowCount;++i)
    {
        QStandardItem* childItems = item->child(i);
        treeItem_checkAllChild_recursion(childItems,check);
    }
    if(item->isCheckable()){
       // qDebug()<<check;
      //  item->setCheckState(check ? Qt::Checked : Qt::Unchecked);
        if(check==1)
            m_checkedList.append(item->index());
        else
            m_checkedList.removeOne(item->index());
    }
}
void M_TreeView::updata_node(){

    CheckList.clear();
    auto &&it=m_checkedList.begin();
    while(it!=m_checkedList.end()){
        if(model->itemFromIndex(*it)->rowCount()<=0)
            CheckList[item_table[model->itemFromIndex(*it)]]+=1;
    }
}

//void M_TreeView::getSelectID(QStandardItem *item){

//}
void M_TreeView::treeItem_checkAllChild_recursion(QStandardItem * item,bool check)
{
    if(item == nullptr)
        return;
    int rowCount = item->rowCount();
    if(rowCount<=0&&item->checkState()!=(check? Qt::Checked : Qt::Unchecked)){
        CheckList[item_table[item]]+=1*(check?1:-1);
    }
    for(int i=0;i<rowCount;++i)
    {
        QStandardItem* childItems = item->child(i);
        treeItem_checkAllChild_recursion(childItems,check);
    }
    if(item->isCheckable()){
        item->setCheckState(check ? Qt::Checked : Qt::Unchecked);
    if(check==1)
        m_checkedList.append(item->index());
    else
        m_checkedList.removeOne(item->index());
    }
}
void M_TreeView::treeItem_CheckChildChanged(QStandardItem * item){//父节点
    if(nullptr == item)
        return;
    Qt::CheckState siblingState = checkSibling(item);
    QStandardItem * parentItem = item->parent();

    if(nullptr == parentItem)
        return;
    if(Qt::PartiallyChecked == siblingState)
    {
        if(parentItem->isCheckable() && parentItem->isTristate())
            parentItem->setCheckState(Qt::PartiallyChecked);
    }
    else if(Qt::Checked == siblingState)
    {
        if(parentItem->isCheckable())
            parentItem->setCheckState(Qt::Checked);
    }
    else
    {
        if(parentItem->isCheckable())
            parentItem->setCheckState(Qt::Unchecked);
    }
    treeItem_CheckChildChanged(parentItem);
}

/// \brief 测量兄弟节点的情况，如果都选中返回Qt::Checked，都不选中Qt::Unchecked,不完全选中返回Qt::PartiallyChecked
/// \param item
/// \return 如果都选中返回Qt::Checked，都不选中Qt::Unchecked,不完全选中返回Qt::PartiallyChecked
///

Qt::CheckState M_TreeView::checkSibling(QStandardItem * item)
{
    //先通过父节点获取兄弟节点
    QStandardItem * parent = item->parent();
    if(nullptr == parent)
        return item->checkState();
    int brotherCount = parent->rowCount();
    int checkedCount(0),unCheckedCount(0);
    Qt::CheckState state;
    for(int i=0;i<brotherCount;++i){
        QStandardItem* siblingItem = parent->child(i);
        state = siblingItem->checkState();
        if(Qt::PartiallyChecked == state)
            return Qt::PartiallyChecked;
        else if(Qt::Unchecked == state)
            ++unCheckedCount;
        else
            ++checkedCount;
        if(checkedCount>0 && unCheckedCount>0)
            return Qt::PartiallyChecked;
    }
    if(unCheckedCount>0)
        return Qt::Unchecked;
    return Qt::Checked;
}

//bool Treemodel::setData(const QModelIndex &index, const QVariant &value, int role)
//{
//      if (role==Qt::CheckStateRole && index.column()==0)
//      {
//            TreeItem *item = static_cast<TreeItem*>(index.internalPointer());
//            if (value==Qt::Unchecked)
//            {
//                  //m_checkedList.removeOne(index);
//                  item->setCheckState(false);
//                  emit(dataChanged(index, index));
//            }
//            else if(value==Qt::Checked)
//            {
//                  //m_checkedList.append(index);
//                  item->setCheckState(true);
//                  emit(dataChanged(index, index));
//            }
//            int childCount = rowCount(index);
//            if (childCount > 0)
//            {
//                  //判断是否有子节点
//                  for (int i=0; i<childCount; i++)
//                  {
//                        //获得子节点的index
//                        QModelIndex child = this->index(i, 0, index);
//                        //递归，改变子节点的checkbox状态
//                        setData(child, value, Qt::CheckStateRole);
//                  }
//            }
//      }

//      return true;
//}
//QVariant Treemodel::data(const QModelIndex &index, int role) const
//{
//    if (!index.isValid())
//        return QVariant();

//      TreeItem *item = static_cast<TreeItem*>(index.internalPointer());

//      //判断显示的对象是checkbox，并且位于第一列
//      if (role==Qt::CheckStateRole && index.column()==0)
//            return static_cast<int>( item->isChecked() ? Qt::Checked : Qt::Unchecked );

//    if (role != Qt::DisplayRole)
//        return QVariant();

//    return item->data(index.column());
//}

//Qt::ItemFlags Treemodel::flags(const QModelIndex &index) const
//{
//    if (!index.isValid())
//        return 0;

//      if (index.column()==0)   //如果是第一列的结点，则使其有显示checkbox的能力
//            return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsUserCheckable;

//    return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
//}
