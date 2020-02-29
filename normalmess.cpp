#include "normalmess.h"
#include "ui_normalmess.h"

NormalMess::NormalMess(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NormalMess)
{
    ui->setupUi(this);

    connect(this,SIGNAL(signalGetMess(QString)),this,SLOT(slotGetMess(QString)));
}

NormalMess::~NormalMess()
{
    delete ui;
}

NormalMess *NormalMess::GetNorMessIns()
{
    static NormalMess *normalmess;
    if(normalmess == nullptr)
    {
        normalmess = new NormalMess();
    }
    return normalmess;
}

void NormalMess::getMess(QString sIndex)
{
    emit signalGetMess(sIndex);
}

void NormalMess::slotGetMess(QString sIndex)
{
    ui->lblNormalMess->setText(sIndex);
    ui->lblNormalMess->setOpenExternalLinks(true);
}
