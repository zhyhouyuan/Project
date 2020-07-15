#include <QtWidgets>
#include "scene.h"

Scene::Scene(qreal x, qreal y, qreal width, qreal height, QObject *parent) :
    QGraphicsScene(x, y, width, height, parent)
{
    m_pos = QPointF(0.0, 0.0);
}
Scene::~Scene()
{

}
QPointF Scene::getScenePos()
{
    return m_pos;
}
void Scene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::RightButton)
        emit updateContextMenu();
    m_pos = event->scenePos();
    QGraphicsScene::mousePressEvent(event);
}
