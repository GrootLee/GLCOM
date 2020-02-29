
//主界面
//designer:geootLee

#ifndef SERIALUNION_H
#define SERIALUNION_H

#include <QMainWindow>
#include "widgettextdisplay.h"
#include "widgetsettings.h"
//#include "widgetsend.h"
#include "widgetsendcommon.h"
#include "normalmess.h"
#include <QDateTime>
#include <QTimer>
#include <QFileDialog>
#include <QDir>

namespace Ui {
class SerialUnion;
}

class SerialUnion : public QMainWindow
{
    Q_OBJECT

public:
    explicit SerialUnion(QWidget *parent = 0);
    ~SerialUnion();
    static SerialUnion *GetUnion();

private:
    Ui::SerialUnion *ui;
    WidgetTextDisplay *m_textdisplay;
    WidgetSettings *m_settings;
    WidgetSendCommon *m_sendcommon;
    NormalMess *m_norMessSend;
    NormalMess *m_norMessRec;
    NormalMess *m_norMessTime;
    NormalMess *m_permanUrl;


private:
    bool mbSaveFile(QString sFileName, QString sData);

private slots:
    void slotRecData(QString sData);
    void slotSenParameter(QSerialPort *serial);
    void slotClearRec();
    void slotRefreashtime();
    void slotRecNum(int nRecNum);
    void slotSendNum(int m_nBufferSize);
    void on_mbSaveRecData_triggered();
//    void on_mbMoreSettings_triggered();
};

#endif // SERIALUNION_H
