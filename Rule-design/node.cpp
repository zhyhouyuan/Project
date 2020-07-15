#include <QtWidgets>
#include "node.h"
#include "link.h"
#include "mainwindow.h"
#include "scene.h"

Node::Node(MainWindow *mindMapDlg)
{
    this->setFlags(ItemIsMovable | ItemIsSelectable | ItemSendsGeometryChanges);
    this->setAcceptHoverEvents(true);
    m_mindMapDlg = mindMapDlg;
    m_nodeScene = m_mindMapDlg->getruleScene();
    isselect=0;
}
Node::~Node()
{
    foreach (Link *link, m_links)
        delete link;
    //delete  this;
}
void Node::setText(const QString &text)
{
    m_text = text;
    prepareGeometryChange();
}
QString Node::getText()
{
    return m_text;
}
//.......
void Node::addLink(Link *link)
{
    m_links.append(link);
}

void Node::removeLink(Link *link)
{
    m_links.removeOne(link);
}

QList<Link *> Node::getLinks()
{
    return m_links;
}

Link *Node::getLinkFrom()
{
    for (int i = 0; i < m_links.size(); i++) {
        Link *link = m_links.at(i);
        if (link) {
            Node *fromNode = link->getFromNode();
            if (fromNode && fromNode != this) {
                return link;
            }
        }
    }
    return 0;
}

QList<Link *> Node::getLinksTo()
{
    QList<Link *> linkList;
    for (int i = 0; i < m_links.size(); i++) {
        Link *link = m_links.at(i);
        if (link) {
            Node *toNode = link->getToNode();
            if (toNode && toNode != this) {
                linkList << link;
            }
        }
    }

    return linkList;
}

void Node::setBasePoint(QPointF basePoint)
{
    m_basePoint = basePoint;
}

QPointF Node::getBasePoint()
{
    return m_basePoint;
}
QRectF Node::outlineRect() const
{
    QFontMetricsF metrics = (QFontMetricsF)qApp->font();
    QRectF rect = metrics.boundingRect(m_text);
    rect.adjust(-10, -10, +20, +10);
    rect.translate(-rect.center());
    return rect;
}
//QRectF Node::outlineRect2() const
//{
//    QFontMetricsF metrics = (QFontMetricsF)qApp->font();
//    QRectF rect = metrics.boundingRect("对");
//    rect.adjust(10, 10, 5, 5);
//    rect.translate(-rect.center().rx()-30,-rect.center().ry());
//    return rect;
//}
QRectF Node::boundingRect() const
{
    return outlineRect().adjusted(-1, -1, +1, +1);
}

QPainterPath Node::shape() const
{
    QRectF rect = outlineRect();

    QPainterPath path;
    path.addRect(rect);

    return path;
}
QVariant Node::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == ItemPositionHasChanged) {
            m_mindMapDlg->itemsMove(this);
           //setPos(m_basePoint.x(), m_basePoint.y());

    }
    return QGraphicsItem::itemChange(change, value);
}
void Node::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    //if (!getLinkFrom()) {
        //m_mindMapDlg->itemsMove(this);
    if(event->modifiers()==0){
        setBasePoint(QPointF(this->x(), this->y()));
        QGraphicsItem::mouseMoveEvent(event);
    }
    update(boundingRect());
    //
}
void Node::setcolornum(int colornum){
    nodecolor=colornum;

}
void Node::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget */*widget*/)
{
    if (option->state & QStyle::State_Selected) {
        painter->setPen(QPen(Qt::red, 1.0, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
        //isselect=1;
    }
    else {
        painter->setPen(QPen(Qt::black, 1.0, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
        isselect=0;
    }
    switch(nodecolor){
        case 0:painter->setBrush(QColor(255,205,250));break;
        case 1:painter->setBrush(QColor(255,255,50));break;
        case 2:painter->setBrush(QColor(55,255,250));break;
        case 3:painter->setBrush(QColor(200,200,200));break;
        case 4:painter->setBrush(QColor(100,100,255));break;
        case 233:painter->setBrush(QColor(255,48,48));break;
       default:painter->setBrush(QColor(255,255,255));break;
    }
    QRectF rect = outlineRect();
    painter->drawRect(rect);
    painter->drawText(rect, Qt::AlignCenter, m_text);
//    QRectF rect2 = outlineRect2();
//    painter->drawRect(rect2);
//    painter->drawText(rect2, Qt::Unchecked,"√");
}
//void Node::showNodeInfo()
//{
//    QRectF rect = outlineRect();
//    int rectW = rect.width();
//    int rectH = rect.height();

//    int nodeX = this->x();
//    int nodeY = this->y();

//    int moveX = nodeX - rectW / 2.0;
//    int moveY = nodeY + rectH / 2.0 + 5;

//    m_nodeInfoDlg = new NodeInfoDialog(this);
//    m_nodeScene->addWidget(m_nodeInfoDlg);

//    m_nodeInfoDlg->move(moveX, moveY);
//    m_nodeInfoDlg->show();
//}

//void Node::closeNodeInfo()
//{
//    if (m_nodeInfoDlg && m_nodeInfoDlg->isVisible()) {
//        m_nodeInfoDlg->deleteLater();
//        m_nodeInfoDlg = NULL;
//    }
//}
void Node::hoverEnterEvent(QGraphicsSceneHoverEvent */*event*/)
{
    //showNodeInfo();

    this->setCursor(Qt::PointingHandCursor);
}

void Node::hoverLeaveEvent(QGraphicsSceneHoverEvent */*event*/)
{
   // closeNodeInfo();

    this->setCursor(Qt::ArrowCursor);
}
void Node::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
//    if(this->getLinksTo().isEmpty()){
//     m_mindMapDlg->changeTable(this);}
//    if(this->getLinkFrom()==NULL){
//    if(event->modifiers() == Qt::CTRL){
//      isselect=!isselect;
    if(event->button() == Qt::LeftButton){
        if(event->modifiers()==0){
            m_mindMapDlg->changeTable(this);
            this->isselect=!this->isselect;
//            if(this->isselect){
//                this->nodeselet();
//            }
        QGraphicsItem::mousePressEvent(event);
        }
        if(event->modifiers()==Qt::CTRL){
            this->isselect=!this->isselect;
            this->nodeselet();
        }
     }
//    if(event->button()==Qt::RightButton){
//        QStringList list0=this->getheadname();
//        QStringList list1;
//        list1.append("0");
//        for(int i=0;i<list0.count();i++){
//            list1.append(list0.at(list0.count()-i-1));
//        }
    //    m_mindMapDlg->addwindowshow_node(list1);
//    }
}
void Node::nodeselet(){
    if(this->isselect){
        if(!this->getLinksTo().isEmpty()){
            for(int i=0;i<this->getLinksTo().count();i++){
                 this->getLinksTo().at(i)->getToNode()->setSelected(true);
                 this->getLinksTo().at(i)->getToNode()->isselect=1;
                 this->getLinksTo().at(i)->getToNode()->nodeselet();
            }
        }

    }
    else{
        if(this->getLinkFrom()){
            this->getLinkFrom()->getFromNode()->setSelected(false);
            this->getLinkFrom()->getFromNode()->isselect=0;
            this->getLinkFrom()->getFromNode()->nodeselet();
        }
    }
}
void Node::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
//    if(this->getLinksTo().isEmpty()){
//     m_mindMapDlg->changeTable(this);}
//    if(this->getLinkFrom()==NULL){
//    if(event->modifiers() == Qt::CTRL){
//      isselect=!isselect;
    if(event->button() == Qt::LeftButton){
        if(event->modifiers()==Qt::CTRL){
            m_mindMapDlg->chatables();
        }
     }
    QGraphicsItem::mouseReleaseEvent(event);
}
QList<QString> Node::getheadname(){
    QList<QString>list0;
    Node*node=this;
    while(node->getLinkFrom()!=nullptr){
         QString  value =node->getText();
         list0.append(value);
         node=node->getLinkFrom()->getFromNode();
         }
    return list0;

}
