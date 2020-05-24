#ifndef ABOUT_H
#define ABOUT_H
#include <QVBoxLayout>
#include <QWidget>
#include <QTextBrowser>

class About : public QWidget
{
    Q_OBJECT
    QTextBrowser *txt_browser;
public:
    explicit About(const QString& strPath, const QString& strFileName);
signals:

public slots:
};

#endif // ABOUT_H
