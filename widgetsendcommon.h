
//发送界面
//designer:geootLee

#ifndef WIDGETSENDCOMMON_H
#define WIDGETSENDCOMMON_H

#include <QWidget>
#include <QSerialPort>
#include <QByteArray>
#include <QMessageBox>
#include <QTimer>
#include <QFileDialog>
#include <QTextStream>
#include <QTextCodec>

namespace Ui {
class WidgetSendCommon;
}

class WidgetSendCommon : public QWidget
{
    Q_OBJECT

public:
    explicit WidgetSendCommon(QWidget *parent = 0);
    ~WidgetSendCommon();
    static WidgetSendCommon *GetSendCommonIns();
    void getSerialParam(QSerialPort *serial);
    void configData();

public:
    bool m_isHexSend;
    bool m_isEnterSend;
    bool m_isTimingSend;
    int m_letCycleTime;
    QString m_sTextEdit;

private slots:
    void on_btnSend_clicked();
    void on_btnClearSend_clicked();
    void on_isHexSend_clicked(bool checked);
    void on_textEdit_textChanged();
    void on_isTimingSend_clicked(bool checked);
    void slotTimeOut();
    void on_btnSelectSendFile_clicked();
    void on_btnSendFile_clicked();
    void on_btnClearSendFilePath_clicked();

private:
    Ui::WidgetSendCommon *ui;
    QSerialPort *serialSend;
    QTimer *timer;
    QString fronHexToDec(QString sData);
    int nSendLength;

private:
    bool readFile(QString sFileName, QString *sDataBuffer);
    bool readFileBin(QString sFileName, char *sDataBufferBin);

signals:
    void signalSendNum(int m_nBufferSize);
};

#endif // WIDGETSENDCOMMON_H
