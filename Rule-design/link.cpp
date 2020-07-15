#include <QtWidgets>
#include "link.h"
#include "node.h"

Link::Link(Node *fromNode, Node *toNode)
{
    m_fromNode = fromNode;
    m_toNode = toNode;
    m_fromNode->addLink(this);
    m_toNode->addLink(this);
    this->setZValue(-1);
    adjust();
}

Link::~Link()
{
    m_fromNode->removeLink(this);
    m_toNode->removeLink(this);
}

Node *Link::getFromNode() const
{
    return m_fromNode;
}

Node *Link::getToNode() const
{
    return m_toNode;
}

void Link::adjust()
{
    m_fromPoint = m_fromNode->pos();
    m_toPoint = m_toNode->pos();

    prepareGeometryChange();
}

QRectF Link::boundingRect() const
{
    return QRectF(m_fromPoint, QSizeF(m_toPoint.x() - m_fromPoint.x(), m_toPoint.y() - m_fromPoint.y())).normalized();
}

void Link::paint(QPainter *painter, const QStyleOptionGraphicsItem */*option*/, QWidget */*widget*/)
{
    QPointF midPoint,midP2;
    midPoint.setX((m_fromPoint.rx()+m_toPoint.rx())/2);
    midPoint.setY(m_fromPoint.ry());
    midP2.setX(midPoint.rx());
    midP2.setY(m_toPoint.ry());
    painter->setPen(QPen(Qt::black, 1.0, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    QLineF line(m_fromPoint, midPoint);
    QLineF line2(midPoint,midP2);
    QLineF line3(midP2,m_toPoint);
    painter->drawLine(line);
    painter->drawLine(line2);
    painter->drawLine(line3);
}
