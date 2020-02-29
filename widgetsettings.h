
//设置界面
//designer:geootLee

#ifndef WIDGETSETTINGS_H
#define WIDGETSETTINGS_H

#include <QWidget>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QMessageBox>
#include <QDebug>
#include <QDateTime>

namespace Ui {
class WidgetSettings;
}

class WidgetSettings : public QWidget
{
    Q_OBJECT

public:
    explicit WidgetSettings(QWidget *parent = 0);
    ~WidgetSettings();
    static WidgetSettings *GetSettingIns();
    void configData();

public:
    QString m_sPortName;
    int m_nBaudRate;
    int m_nStopBit;
    int m_nDataBit;
    QString m_sParity;
    bool m_isHexRec;
    bool m_isDisTime;
    QString m_sOpenSerial;

private:
    Ui::WidgetSettings *ui;
    QSerialPort Serial;
    int m_nBufferSize;

private:
    bool openSerialPort(QSerialPort *serial, QString sPortName, int nBaudRate, int nStopBit, \
                        int nDataBit, QString sParity);
private slots:
    void on_btnSearchPort_clicked();
    void on_btnSerialPortOperation_clicked();
    void slotSerialRead();
    void on_btnClearRec_clicked();

signals:
    void signalRecData(QString sData);
    void signalSenParameter(QSerialPort *serial);
    void signalClearRec();
    void signalRecNum(int nRecNum);
};

#endif // WIDGETSETTINGS_H
