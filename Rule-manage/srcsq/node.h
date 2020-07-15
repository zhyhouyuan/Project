#ifndef NODE_H
#define NODE_H

#include <QGraphicsItem>

class MainWindow;
class NodeInfoDialog;
class Scene;
class Link;
class Node : public QGraphicsItem
{
public:
    Node(MainWindow*mindMapDlg);
    ~Node();

    void setText(const QString &text);
    QString getText();
    void addLink(Link *link);
    void removeLink(Link *link);
    QList<Link *> getLinks();
    Link *getLinkFrom();
    QList<Link *> getLinksTo();

    void setBasePoint(QPointF basePoint);
    QPointF getBasePoint();
    QRectF outlineRect() const;
    //QRectF outlineRect2() const;
    void showNodeInfo();
    void closeNodeInfo();
    void setcolornum(int colornum);
    QList<QString> getheadname();

    void nodeselet();
    int            nodecolor;
    bool           isselect;
protected:
    QRectF boundingRect() const;
    QPainterPath shape() const;

    QVariant itemChange(GraphicsItemChange change, const QVariant &value);
    QGraphicsItem::GraphicsItemFlags flags() const;
//    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
     void mousePressEvent(QGraphicsSceneMouseEvent *event);
       void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
     void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
     void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
      void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    MainWindow  *m_mindMapDlg;
    Scene          *m_nodeScene;
    NodeInfoDialog *m_nodeInfoDlg;

    QString         m_text;
    QList<Link *>   m_links;
    QPointF         m_basePoint;


    //QList<QColor*> QColor

};

#endif // NODE_H
