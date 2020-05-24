#ifndef TTWIDGET_H
#define TTWIDGET_H

#include <QWidget>
#include <QGraphicsDropShadowEffect>

class TTWidget : public QWidget
{
    Q_OBJECT

public:
    virtual void Set_Connections() = 0;
    virtual void Set_Textures() = 0;
    void CreateShadow(QWidget *Widget, unsigned short XOffSet, unsigned short YOffSet, unsigned short int radius,unsigned short int acolor) const;
    explicit TTWidget(QWidget *parent = 0);

signals:

public slots:

};

#endif // TTWIDGET_H
