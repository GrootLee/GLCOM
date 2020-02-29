
//设计状态栏label
//designer:geootLee

#ifndef NORMALMESS_H
#define NORMALMESS_H

#include <QWidget>

namespace Ui {
class NormalMess;
}

class NormalMess : public QWidget
{
    Q_OBJECT

public:
    explicit NormalMess(QWidget *parent = 0);
    ~NormalMess();
    static NormalMess *GetNorMessIns();

    void getMess(QString sIndex);

private:
    Ui::NormalMess *ui;

signals:
    void signalGetMess(QString sIndex);

private slots:
    void slotGetMess(QString sIndex);
};

#endif // NORMALMESS_H
