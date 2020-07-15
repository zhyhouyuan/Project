#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>

class Scene : public QGraphicsScene
{
    Q_OBJECT

public:
    explicit Scene(qreal x, qreal y, qreal width, qreal height, QObject *parent = 0);
    ~Scene();

    QPointF getScenePos();
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

private:
    QPointF m_pos;

signals:
    void updateContextMenu();

};

#endif // SCENE_H
