#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    root = NULL;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_select_file_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, "OpenFile", "C:\\Users\\tosch\\Desktop\\CR", "*.txt");
    create_tree_by_file(&root, filename);
    QString record_tree;
    print_tree(root, record_tree, 0, false);
    ui->scrollArea->setWidget(new QLabel(record_tree));
    on_pushButton_clicked();
}

void MainWindow::on_delete_node_b_clicked()
{
  QString delete_key =  ui->delete_node_l->text();
  remove_key(&root, delete_key);
  QString record_tree;
  print_tree(root, record_tree, 0, false);
  ui->scrollArea->setWidget(new QLabel(record_tree));
  on_pushButton_clicked();
}

void MainWindow::on_add_node_b_clicked()
{
    QString new_key = ui->add_node_l->text();
    insert(&root, new_key);
    QString record_tree;
    print_tree(root, record_tree, 0, false);
    ui->scrollArea->setWidget(new QLabel(record_tree));
    on_pushButton_clicked();
}

void MainWindow::on_actionHelp_triggered()
{
    Help *help = new Help(":/doc/", "index.htm");
    help->resize(400, 400);
    help->show();
}

void MainWindow::on_pushButton_clicked()
{
    if(root){
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    QLayoutItem *child = this->centralWidget()->layout()->takeAt(5);
    if(child)
        delete child->widget();
    delete child;
    widget = new GraphWidget(this, root);
    this->centralWidget()->layout()->addWidget(widget);
    }
}

void MainWindow::on_actionAbout_triggered()
{
    About *about = new About(":/doc/", "about.htm");
    about->resize(520, 640);
    about->show();
}
void MainWindow::updateTime(){
    this->window()->setGeometry(400,300,400,300);
    tmr->stop();
}

void MainWindow::on_action_triggered()
{
    QLayoutItem *child = this->centralWidget()->layout()->takeAt(5);  
    if(child){
        delete child->widget();
        tmr = new QTimer();
        tmr->setInterval(100);
        connect(tmr, SIGNAL(timeout()), this, SLOT(updateTime()));
        tmr->start(100);
    }
    delete child;
    this->window()->repaint();
    while(root){
        QString delete_key = *(root->key);
        remove_key(&root, delete_key);
    }
    QString record_tree;
    print_tree(root, record_tree, 0, false);
    ui->scrollArea->setWidget(new QLabel(record_tree));
    this->window()->setGeometry(400,300,400,300);
}
