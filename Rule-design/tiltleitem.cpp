#include "tiltleitem.h"
#include"node.h"
#include<QtWidgets>
tiltleItem::tiltleItem(Node*referNode,int ypos)
{
    this->m_referNode=referNode;
    this->ypos_end=ypos-30;
    adjust();
}

tiltleItem::~tiltleItem()
{
    //delete this;

}


void tiltleItem::adjust()
{
    m_fromPoint.setX(m_referNode->pos().rx());
    m_fromPoint.setY(100);
    m_toPoint.setX(m_referNode->pos().rx());
    m_toPoint.setY(m_referNode->pos().ry()*2-120);
    prepareGeometryChange();
}

QRectF tiltleItem::boundingRect() const
{
    return QRectF(m_fromPoint, QSizeF(m_toPoint.x() - m_fromPoint.x(), m_toPoint.y() - m_fromPoint.y())).normalized();
}

void tiltleItem::paint(QPainter *painter, const QStyleOptionGraphicsItem */*option*/, QWidget */*widget*/)
{
    //画一条线
    //painter->begin(this);
    QPen pen(Qt::DotLine); //定义画笔，参数：虚线
    painter->setPen(pen); //设置画笔
    //for(int)
    QPointF from1,topoint;
    from1.setY(m_fromPoint.ry());
    topoint.setY(ypos_end+20);
    for(int i=0;i<4;i++){
        from1.setX(m_fromPoint.rx()+150+i*100);
        topoint.setX(m_fromPoint.rx()+150+i*100);
        //from1.setY(m_fromPoint.ry());
        painter->drawLine(from1,topoint); //画线，参数为起点和终点坐标
    }
    //painter->end();
    QFont mFont; //定义一个字体变量
    mFont.setFamily("宋体"); //设置字体格式
    mFont.setPointSize(12);//设置字体大小
    mFont.setItalic(true);  //斜体
    //painter->drawText()
    painter->setFont(mFont); //加入字体格式
    painter->setPen(QColor(0, 0, 0)); //设置画笔颜色
    QPointF point0;
    QStringList list0;
    list0<<"类型"<<"型号"<<"模式"<<"任务"<<"规则";
    point0.setY(m_fromPoint.ry());
    for(int i=0;i<5;i++){
        point0.setX(m_fromPoint.rx()+75+i*100);
        //topoint.setX(m_fromPoint.rx()+50+i*100);
        //from1.setY(m_fromPoint.ry());
        painter->drawText(point0, list0.at(i));
        QRectF rect;
        rect.setRect(point0.x()-25,point0.y()-30,100,50);
        //rect.adjust(-10, -10, +20, +10);
        //rect.translate(-rect.center());
        //rect.set
        painter->drawRect(rect);
        //painter->drawRect(0,0,200,200);
    }
    //参数：1.一个矩形区域存放文本 2.对齐方式 3.显示内容

}
