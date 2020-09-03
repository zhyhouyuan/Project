#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>

class Scene : public QGraphicsScene
{
    Q_OBJECT

public:
    explicit Scene(qreal x, qreal y, qreal width, qreal height, QObject *parent = 0);
    ~Scene();
    void clearitems(){
        QList<QGraphicsItem *> item_list_p = this->items();
            for(int i=0; i<item_list_p.size(); i++){
                this->removeItem(item_list_p[i]);  //从scene移除
                delete item_list_p[i];  //释放内存
            }
    }
    QPointF getScenePos();
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

private:
    QPointF m_pos;

signals:
    void updateContextMenu();

};

#endif // SCENE_H
