#ifndef NODE_H
#define NODE_H
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QStyleOption>
#include <QGraphicsItem>
#include <QList>
#include <QString>
#include <QFontMetrics>
#include "edge.h"
#include "graphwidget.h"

class Edge;
class GraphWidget;
class QGraphicsSceneMouseEvent;

class Node : public QGraphicsItem
{
public:
    Node(GraphWidget *graphWidget, QString* lst, char color);
    char left_c;
    void addEdge(Edge *edge);
    QList<Edge *> edges() const;

    enum { Type = UserType + 1 };
    int type() const { return Type; }

    void calculateForces();
    bool advance();

    QString* str;

    QRectF boundingRect() const;
    QPainterPath shape() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);

    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

private:
    QRectF* rect;
    QList<Edge *> edgeList;
    QPointF newPos;
    GraphWidget *graph;
};

#endif
