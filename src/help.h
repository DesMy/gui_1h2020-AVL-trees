#ifndef HELP_H
#define HELP_H
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QWidget>
#include <QPushButton>
#include <QTextBrowser>

class Help : public QWidget
{
    Q_OBJECT
    QPushButton*  pcmdBack;
    QPushButton*  pcmdHome;
    QPushButton*  pcmdForward;
    QTextBrowser* ptxtBrowser;
public:
    explicit Help(const QString& strPath, const QString& strFileName);
signals:

public slots:
};

#endif // HELP_H
