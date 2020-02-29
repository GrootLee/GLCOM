
//显示界面
//designer:geootLee

#ifndef WIDGETTEXTDISPLAY_H
#define WIDGETTEXTDISPLAY_H

#include <QWidget>

namespace Ui {
class WidgetTextDisplay;
}

class WidgetTextDisplay : public QWidget
{
    Q_OBJECT

public:
    explicit WidgetTextDisplay(QWidget *parent = 0);
    ~WidgetTextDisplay();
    static WidgetTextDisplay *GetTextDisplay();
    void getDisplayData(QString sData);
    void getClearTextBrower();
    QString displayData();

private:
    Ui::WidgetTextDisplay *ui;
};

#endif // WIDGETTEXTDISPLAY_H
