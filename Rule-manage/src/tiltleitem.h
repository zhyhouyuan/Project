#ifndef TILTLEITEM_H
#define TILTLEITEM_H

#include<QGraphicsItem>

class Node;
class tiltleItem : public QGraphicsItem
{
public:
    tiltleItem(Node*referNode);
    ~tiltleItem();
    void adjust();
    //Node *getFromNode() const;
    //Node *getToNode() const;
protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
private:
    Node    *m_referNode;

    QPointF  m_fromPoint;
    QPointF  m_toPoint;

};
#endif // TILTLEITEM_H
