#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QFileDialog>
#include <QLabel>
#include <QDebug>
#include <QMainWindow>
#include <QApplication>
#include <QTime>
#include <QMainWindow>
#include <QtGui>
#include "avltree.h"
#include "graphwidget.h"
#include "help.h"
#include "about.h"
#include "ui_mainwindow.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    AvlTree *root;
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_select_file_clicked();

    void on_delete_node_b_clicked();

    void on_add_node_b_clicked();

    void on_actionHelp_triggered();

    void on_actionAbout_triggered();

    void on_pushButton_clicked();

    void on_action_triggered();

private:
    Ui::MainWindow *ui;
    GraphWidget* widget = NULL;
    QTimer *tmr; //Адресная переменная таймера
    private slots:
        void updateTime();
};

#endif // MAINWINDOW_H
