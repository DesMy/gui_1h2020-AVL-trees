#include "about.h"

About::About(const QString& strPath, const QString& strFileName) : QWidget()
{
    txt_browser = new QTextBrowser;
    txt_browser->setSearchPaths(QStringList() << strPath);
    txt_browser->setSource(strFileName);
    QVBoxLayout *vb = new QVBoxLayout;
    vb->addWidget(txt_browser);
    setLayout(vb);
}
