#include "graphwidget.h"

#include <QApplication>
#include <QTime>
#include <QMainWindow>

int print()
{
    int i = 0;
    QApplication app(i, NULL);

    GraphWidget *widget = new GraphWidget;

    QMainWindow mainWindow;
    mainWindow.setCentralWidget(widget);

    mainWindow.show();
    return app.exec();
}
