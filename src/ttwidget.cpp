#include "ttwidget.h"
#include <QDir>

namespace Ui {
class MenuBar;
}

class MenuBar : public TTWidget
{
    Q_OBJECT

public:
    void SetTitle(const QString Title) const;
    explicit MenuBar(TTWidget *parent = 0);
    ~MenuBar();

signals:
    void Minimized_Window();
    void Close_Window();

private:
    void Set_Textures();
    void Set_Connections();
    Ui::MenuBar *ui;
};
