#ifndef GRAPHWIDGET_H
#define GRAPHWIDGET_H
#include <QGraphicsView>
#include <QtGui>
#include <math.h>
#include "avltree.h"
#include "edge.h"
#include "node.h"

class Node;

class GraphWidget : public QGraphicsView
{
    Q_OBJECT

public:
    GraphWidget(QWidget *parent = 0, AvlTree* root = 0);
    void CreatePic(AvlTree* root, int posX, int posY, Node *center, QGraphicsScene *scene);
    void itemMoved();

protected:
    void keyPressEvent(QKeyEvent *event);
    void timerEvent(QTimerEvent *event);
    void wheelEvent(QWheelEvent *event);
    void drawBackground(QPainter *painter, const QRectF &rect);

    void scaleView(qreal scaleFactor);

private:
    int timerId;
    Node *centerNode;
};

#endif
