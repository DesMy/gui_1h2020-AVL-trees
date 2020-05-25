#include "graphwidget.h"

 GraphWidget::GraphWidget(QWidget *parent, AvlTree *root)
     : QGraphicsView(parent), timerId(0)
 {
     QGraphicsScene *scene = new QGraphicsScene(this);
     scene->setItemIndexMethod(QGraphicsScene::NoIndex);
     scene->setSceneRect(0, 0, 0, 0);
     setScene(scene);
     setCacheMode(CacheBackground);
     setViewportUpdateMode(BoundingRectViewportUpdate);
     setRenderHint(QPainter::Antialiasing);
     setTransformationAnchor(AnchorUnderMouse);
     scale(qreal(0.8), qreal(0.8));
     setMinimumSize(400, 400);
     setWindowTitle(tr("Elastic Nodes"));
     Node* center = new Node(this, root->key, 1);
     scene->addItem(center);
     center->setPos(0, -150);
     center->setZValue(2);
     centerNode = center;
     CreatePic(root, 0, -150, center, scene);
 }

 void GraphWidget::CreatePic(AvlTree* root, int posX, int posY, Node* center, QGraphicsScene *scene){
     QString* left = new QString("");
     QString* right = new QString("");
     if(root->left)
         left = root->left->key;
     if(root->right)
         right = root->right->key;
     if(left->size() || right->size()){
     Node* nodeL = new Node(this, left, 2);
     Node* nodeR = new Node(this, right, 0);
     scene->addItem(nodeL);
     nodeL->setZValue(1);
     nodeR->setZValue(1);
         nodeL->setVisible(left->size());
         nodeR->setVisible(right->size());
     scene->addItem(nodeR);
     scene->addItem(new Edge(center, nodeL, left, left->size()));
     scene->addItem(new Edge(center, nodeR, right, right->size()));
     scene->addItem(new Edge(nodeL, nodeR, root->key, false));
     nodeL->setPos(posX - 15, posY + 85);
     nodeR->setPos(posX + 15, posY + 85);
     if(left->size())
         CreatePic(root->left, posX - 15, posY + 85, nodeL, scene);
     if(right->size())
         CreatePic(root->right, posX + 15, posY + 85, nodeR, scene);
     }
 }
 void GraphWidget::itemMoved()
 {
     if (!timerId)
         timerId = startTimer(1000 / 25);
 }

 void GraphWidget::keyPressEvent(QKeyEvent *event)
 {
     switch (event->key()) {
     case Qt::Key_Up:
         centerNode->moveBy(0, -20);
         break;
     case Qt::Key_Down:
         centerNode->moveBy(0, 20);
         break;
     case Qt::Key_Left:
         centerNode->moveBy(-20, 0);
         break;
     case Qt::Key_Right:
         centerNode->moveBy(20, 0);
         break;
     case Qt::Key_Plus:
         scaleView(qreal(1.2));
         break;
     case Qt::Key_Minus:
         scaleView(1 / qreal(1.2));
         break;
     case Qt::Key_Space:
     case Qt::Key_Enter:
         foreach (QGraphicsItem *item, scene()->items()) {
             if (qgraphicsitem_cast<Node *>(item))
                 item->setPos(-150 + qrand() % 300, -150 + qrand() % 300);
         }
         break;
     default:
         QGraphicsView::keyPressEvent(event);
     }
 }

 void GraphWidget::timerEvent(QTimerEvent *event)
 {
     Q_UNUSED(event);

     QList<Node *> nodes;
     foreach (QGraphicsItem *item, scene()->items()) {
         if (Node *node = qgraphicsitem_cast<Node *>(item))
             nodes << node;
     }

     foreach (Node *node, nodes)
         node->calculateForces();

     bool itemsMoved = false;
     foreach (Node *node, nodes) {
         if (node->advance())
             itemsMoved = true;
     }

     if (!itemsMoved) {
         killTimer(timerId);
         timerId = 0;
     }
 }

 void GraphWidget::wheelEvent(QWheelEvent *event)
 {
     scaleView(pow((double)2, -event->delta() / 240.0));
 }

 void GraphWidget::drawBackground(QPainter *painter, const QRectF &rect)
 {
     Q_UNUSED(rect);

     // Shadow
     QRectF sceneRect = this->sceneRect();
     QRectF rightShadow(sceneRect.right(), sceneRect.top() + 5, 5, sceneRect.height());
     QRectF bottomShadow(sceneRect.left() + 5, sceneRect.bottom(), sceneRect.width(), 5);
     if (rightShadow.intersects(rect) || rightShadow.contains(rect))
         painter->fillRect(rightShadow, Qt::darkGray);
     if (bottomShadow.intersects(rect) || bottomShadow.contains(rect))
         painter->fillRect(bottomShadow, Qt::darkGray);

     // Fill
     QLinearGradient gradient(sceneRect.topLeft(), sceneRect.bottomRight());
     gradient.setColorAt(0, Qt::white);
     gradient.setColorAt(1, Qt::lightGray);
     painter->fillRect(rect.intersected(sceneRect), gradient);
     painter->setBrush(Qt::NoBrush);
     painter->drawRect(sceneRect);
 }

 void GraphWidget::scaleView(qreal scaleFactor)
 {
     qreal factor = transform().scale(scaleFactor, scaleFactor).mapRect(QRectF(0, 0, 1, 1)).width();
     if (factor < 0.07 || factor > 100)
         return;

     scale(scaleFactor, scaleFactor);
 }
