#include "widgettextdisplay.h"
#include "ui_widgettextdisplay.h"

WidgetTextDisplay::WidgetTextDisplay(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WidgetTextDisplay)
{
    ui->setupUi(this);
}

WidgetTextDisplay::~WidgetTextDisplay()
{
    delete ui;
}

WidgetTextDisplay *WidgetTextDisplay::GetTextDisplay()
{
    static WidgetTextDisplay *textDispaly;
    if(textDispaly == nullptr)
    {
        textDispaly = new WidgetTextDisplay();
    }
    return textDispaly;
}

void WidgetTextDisplay::getDisplayData(QString sData)
{
    ui->textBrowser->append(sData);
    displayData();
}

void WidgetTextDisplay::getClearTextBrower()
{
    ui->textBrowser->clear();
}

QString WidgetTextDisplay::displayData()
{
    return ui->textBrowser->toPlainText();
}
