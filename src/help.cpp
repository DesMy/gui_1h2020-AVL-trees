#include "help.h"

Help::Help(const QString& strPath, const QString& strFileName) : QWidget()
{
    pcmdBack    = new QPushButton("<<");
    pcmdHome    = new QPushButton("Home");
    pcmdForward = new QPushButton(">>");
    ptxtBrowser = new QTextBrowser;

    connect(pcmdBack, SIGNAL(clicked()),
            ptxtBrowser, SLOT(backward())
           );
    connect(pcmdHome, SIGNAL(clicked()),
            ptxtBrowser, SLOT(home())
           );
    connect(pcmdForward, SIGNAL(clicked()),
            ptxtBrowser, SLOT(forward())
           );

    connect(ptxtBrowser, SIGNAL(backwardAvailable(bool)),
            pcmdBack, SLOT(setEnabled(bool))
           );
    connect(ptxtBrowser, SIGNAL(forwardAvailable(bool)),
            pcmdForward, SLOT(setEnabled(bool))
           );

    ptxtBrowser->setSearchPaths(QStringList() << strPath);
    ptxtBrowser->setSource(QString(strFileName));

    //Layout setup
    QVBoxLayout* pvbxLayout = new QVBoxLayout;
    QHBoxLayout* phbxLayout = new QHBoxLayout;
    phbxLayout->addWidget(pcmdBack);
    phbxLayout->addWidget(pcmdHome);
    phbxLayout->addWidget(pcmdForward);
    pvbxLayout->addLayout(phbxLayout);
    pvbxLayout->addWidget(ptxtBrowser);
    setLayout(pvbxLayout);
}
