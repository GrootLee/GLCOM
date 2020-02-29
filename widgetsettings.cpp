#include "widgetsettings.h"
#include "ui_widgetsettings.h"

WidgetSettings::WidgetSettings(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WidgetSettings)
{
    ui->setupUi(this);

    m_nBufferSize = 0;

    connect(&Serial,&QSerialPort::readyRead,this,&WidgetSettings::slotSerialRead);
}

WidgetSettings::~WidgetSettings()
{
    delete ui;
}

WidgetSettings *WidgetSettings::GetSettingIns()
{
    static WidgetSettings *settings;
    if(settings == nullptr)
    {
        settings = new WidgetSettings();
    }
    return settings;
}

//检测可用串口
void WidgetSettings::on_btnSearchPort_clicked()
{
    ui->cbxPort->clear();

    foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        ui->cbxPort->addItem(info.portName());
    }
}

//读取内容并将内容以信号的形式转发出去
void WidgetSettings::slotSerialRead()
{
    QByteArray buffer;
    Serial.waitForReadyRead(10);
    buffer = Serial.readAll();

    m_nBufferSize += buffer.length();

    if(ui->isHexRec->isChecked() == true)
    {
        buffer = buffer.toHex();
    }
    QString receive = QString::fromLocal8Bit(buffer);//转为字符串
    if(ui->isDisTime->isChecked() == true)
    {
        QDateTime time = QDateTime::currentDateTime();
        QString str= time.toString("hh:mm:ss.zzz");
        receive = "["+str+"]"+">>>"+receive;
    }
    else
    {
        receive = receive;
    }
    emit signalRecNum(m_nBufferSize);
    emit signalRecData(receive);
}

//打开串口
void WidgetSettings::on_btnSerialPortOperation_clicked()
{
    m_sPortName = ui->cbxPort->currentText();
    m_nBaudRate = ui->cbxBaudRate->currentText().toInt();
    m_nStopBit = ui->cbxStopBit->currentText().toInt();
    m_nDataBit = ui->cbxDataBit->currentText().toInt();
    m_sParity = ui->cbxParityBit->currentText();
    m_isHexRec = ui->isHexRec->isChecked();
    m_isDisTime = ui->isDisTime->isChecked();
    m_sOpenSerial = ui->btnSerialPortOperation->text();
    if(m_sOpenSerial == "打开串口")
    {
        m_sOpenSerial = "关闭串口";
    }
    else
    {
        m_sOpenSerial = "打开串口";
    }

    if(ui->btnSerialPortOperation->text() == "打开串口")
    {
        if(ui->cbxPort->currentText() == "")
        {
            QMessageBox::critical(this,"Error","Serial port not found",QMessageBox::Ok);
            return;
        }

        //读取参数
        if(!openSerialPort(&Serial,m_sPortName,m_nBaudRate,m_nStopBit,m_nDataBit,m_sParity))//写入参数
        {
            QMessageBox::critical(this,"Error","Serial port open failed",QMessageBox::Ok);
            return;
        }

        //开启后设置为不可编辑
        ui->cbxPort->setEnabled(false);
        ui->cbxBaudRate->setEnabled(false);
        ui->cbxStopBit->setEnabled(false);
        ui->cbxDataBit->setEnabled(false);
        ui->cbxParityBit->setEnabled(false);
        ui->btnSerialPortOperation->setText("关闭串口");
    }
    else
    {
        Serial.close();

        ui->cbxPort->setEnabled(true);
        ui->cbxBaudRate->setEnabled(true);
        ui->cbxStopBit->setEnabled(true);
        ui->cbxDataBit->setEnabled(true);
        ui->cbxParityBit->setEnabled(true);
        ui->btnSerialPortOperation->setText("打开串口");
    }
    emit signalSenParameter(&Serial);
}

//设定串口参数
bool WidgetSettings::openSerialPort(QSerialPort *serial,QString sPortName, int nBaudRate, int nStopBit, int nDataBit, QString sParity)
{
    serial->setPortName(sPortName);//串口名
    serial->setBaudRate(nBaudRate);//波特率
    //停止位
    switch (nStopBit) {
    case 1:
        serial->setStopBits(QSerialPort::OneStop);
        break;
    case 2:
        serial->setStopBits(QSerialPort::TwoStop);
        break;
    default:
        break;
    }

    //数据位
    switch (nDataBit) {
    case 5:
        serial->setDataBits(QSerialPort::Data5);
        break;
    case 6:
        serial->setDataBits(QSerialPort::Data6);
        break;
    case 7:
        serial->setDataBits(QSerialPort::Data7);
        break;
    case 8:
        serial->setDataBits(QSerialPort::Data8);
        break;
    default:
        break;
    }

    //奇偶校验
    if(sParity == "No")
    {
        serial->setParity(QSerialPort::NoParity);//设置奇偶校验
    }
    else if(sParity == "Odd")
    {
        serial->setParity(QSerialPort::OddParity);
    }
    else
    {
        serial->setParity(QSerialPort::EvenParity);
    }

    serial->setFlowControl(QSerialPort::NoFlowControl);//设置流控制模式

    if(serial->open(QIODevice::ReadWrite)==false)//打开
    {
        return false;
    }
    return true;
}

void WidgetSettings::configData()
{
    if(m_sPortName == "NULL")
    {
        m_sPortName = "";
        m_sOpenSerial = "打开串口";
        m_isHexRec = false;
        m_isDisTime = false;
    }
    ui->cbxPort->addItem(m_sPortName);
    ui->cbxBaudRate->setCurrentText(QString("%1").arg(m_nBaudRate));
    ui->cbxStopBit->setCurrentText(QString("%1").arg(m_nStopBit));
    ui->cbxDataBit->setCurrentText(QString("%1").arg(m_nDataBit));
    ui->cbxParityBit->setCurrentText(m_sParity);
    ui->isHexRec->setChecked(m_isHexRec);
    ui->isDisTime->setChecked(m_isDisTime);
    ui->btnSerialPortOperation->setText(m_sOpenSerial);

    if(m_sOpenSerial == "关闭串口")
    {
        if(ui->cbxPort->currentText() == "")
        {
            QMessageBox::critical(this,"Error","Serial port not found",QMessageBox::Ok);
            return;
        }

        //读取参数
        if(!openSerialPort(&Serial,m_sPortName,m_nBaudRate,m_nStopBit,m_nDataBit,m_sParity))//写入参数
        {
            QMessageBox::critical(this,"Error","Serial port open failed",QMessageBox::Ok);
            return;
        }

        //开启后设置为不可编辑
        ui->cbxPort->setEnabled(false);
        ui->cbxBaudRate->setEnabled(false);
        ui->cbxStopBit->setEnabled(false);
        ui->cbxDataBit->setEnabled(false);
        ui->cbxParityBit->setEnabled(false);
        ui->btnSerialPortOperation->setText("关闭串口");
        emit signalSenParameter(&Serial);
    }
}

void WidgetSettings::on_btnClearRec_clicked()
{
    m_nBufferSize = 0;
    emit signalClearRec();
    emit signalRecNum(m_nBufferSize);
}
