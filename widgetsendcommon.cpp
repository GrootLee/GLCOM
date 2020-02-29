#include "widgetsendcommon.h"
#include "ui_widgetsendcommon.h"
#include <QDebug>
#include <QByteArray>

WidgetSendCommon::WidgetSendCommon(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WidgetSendCommon)
{
    ui->setupUi(this);

    timer = nullptr;
    serialSend = nullptr;
    ui->letSendFilePath->setEnabled(false);
}

WidgetSendCommon::~WidgetSendCommon()
{
    delete ui;

    nSendLength = 0;
}

WidgetSendCommon *WidgetSendCommon::GetSendCommonIns()
{
    static WidgetSendCommon *sendCommon;
    if(sendCommon == nullptr)
    {
        sendCommon = new WidgetSendCommon();
    }
    return sendCommon;
}

void WidgetSendCommon::getSerialParam(QSerialPort *serial)
{
    serialSend = serial;

}

void WidgetSendCommon::on_btnSend_clicked()
{
    if(serialSend == nullptr)
    {
        QMessageBox::critical(this,"Error","Please open the Serial",QMessageBox::Yes);
        return;
    }
    else if(serialSend->isOpen() == true)
    {
        QString sSendBUffer = ui->textEdit->toPlainText();
        nSendLength += sSendBUffer.toLocal8Bit().length();
        m_isHexSend = ui->isHexSend->isChecked();
        m_isEnterSend = ui->isEnterSend->isChecked();
        m_isTimingSend = ui->isTimingSend->isChecked();
        m_letCycleTime = ui->letCyCleTime->text().toInt();
        m_sTextEdit = ui->textEdit->toPlainText();
        if(ui->isEnterSend->isChecked() == true)
        {
            sSendBUffer += "\n";
        }
        if(ui->isHexSend->isChecked() == false)
        {
            serialSend->write(sSendBUffer.toLocal8Bit());
        }
        else
        {
            serialSend->write(fronHexToDec(sSendBUffer.toLocal8Bit()).toLocal8Bit());
        }
//        qDebug()<<nSendLength;
        emit signalSendNum(nSendLength);
    }
    else
    {
        QMessageBox::critical(this,"Error","Please open the Serial",QMessageBox::Yes);
    }
}

void WidgetSendCommon::on_btnClearSend_clicked()
{
    ui->textEdit->clear();
    nSendLength = 0;
    emit signalSendNum(nSendLength);
}

void WidgetSendCommon::on_isHexSend_clicked(bool checked)
{
    QString sSendBUffer = ui->textEdit->toPlainText();
    if(checked == true)//转换为16进制
    {
//        qDebug()<<sSendBUffer.toLatin1().toHex();
        QByteArray sSendBUfferByte = sSendBUffer.toLocal8Bit();
        sSendBUffer = QString(sSendBUfferByte.toHex());
        ui->textEdit->setPlainText(sSendBUffer);
    }
    else//转换为十进制
    {
        ui->textEdit->setPlainText(fronHexToDec(sSendBUffer.toLocal8Bit()).toLocal8Bit());
    }
}

//十六进制转换为十进制
QString WidgetSendCommon::fronHexToDec(QString sData)
{
//    QList<QByteArray> signalHexBufferList;
//    QString sSignalHexBuffer = "";
//    QString sSendBUfferTmp = "";
//    int byteNum = 2;
//    int currentPose = 0;
//    for(int i=0; i<sData.length(); i++)
//    {
//        sSignalHexBuffer += sData.at(i);
//        currentPose++;
//        if(currentPose == 1)
//        {
//            if(sData.at(i).toLatin1() >= 'A')
//            {
//                byteNum = 4;
//            }
//        }
//        if(currentPose == byteNum)
//        {
//            signalHexBufferList.append(sSignalHexBuffer.toLocal8Bit());
//            sSignalHexBuffer = "";
//            byteNum = 2;
//            currentPose = 0;
//        }
//    }
//    for(int j=0; j<signalHexBufferList.length(); j++)
//    {
//        QString sTmp = "c0ee";
////        QByteArray sTmpBy = sTmp.toLocal8Bit();
////        QTextCodec *codeGbk = QTextCodec::codecForName("GBK");
////        QTextCodec *codeutf8 = QTextCodec::codecForName("UTF-8");
//        QString tmp = QTextCodec::codecForName("GBK")->toUnicode(signalHexBufferList.at(j));
////        QByteArray byteutf = codeutf8->fromUnicode(tmp);
////        char *utf = byteutf.data();
//        QByteArray sTmpBy = tmp.toLocal8Bit();
//        sSendBUfferTmp += QString(QByteArray::fromRawData(sTmpBy,4)).toLocal8Bit();
//        qDebug()<<tmp<<sTmpBy;
//    }
    QString sSendBUfferTmp = "";
    QByteArray sDataByte = sData.toLocal8Bit();
    sSendBUfferTmp = QString(QByteArray::fromHex(sDataByte)).toLocal8Bit();
    return sSendBUfferTmp;
}

void WidgetSendCommon::on_textEdit_textChanged()
{
    bool isNumChar = false;
    QString sSendBUffer = ui->textEdit->toPlainText();
    //当十六进制发送打开时，检测是否为十六进制的标准形式
    if(ui->isHexSend->isChecked() == true && sSendBUffer != "")
    {
        QByteArray sSendBUfferByte = sSendBUffer.right(1).toLatin1();
        for(int i=48; i<58; i++)
        {
            if((sSendBUfferByte.at(0) == i) || \
                    (sSendBUfferByte.at(0) == (i+17) && (i < 54)) || \
                    ((sSendBUfferByte.at(0) == (i+49)) && (i < 54)))
            {
                isNumChar = true;
                break;
            }
        }
        if(!isNumChar)
        {
            QMessageBox::critical(this,"Error","{0-9},{A-F},{a-f}",QMessageBox::Yes);
            sSendBUffer.resize(sSendBUffer.length()-1);
            ui->textEdit->setPlainText(sSendBUffer);
            ui->textEdit->moveCursor(QTextCursor::End,QTextCursor::MoveAnchor);
        }
    }
}

void WidgetSendCommon::on_isTimingSend_clicked(bool checked)
{
    if(checked == true)
    {
        ui->letCyCleTime->setEnabled(false);
        int nSendTime = ui->letCyCleTime->text().toInt();
        if(nSendTime == 0)
        {
            QMessageBox::critical(this,"Error","Please enter the right number",QMessageBox::Yes);
            ui->letCyCleTime->clear();
            ui->letCyCleTime->setEnabled(true);
            ui->isTimingSend->setChecked(false);
        }
        else
        {
            timer = new QTimer(this);
            timer->start(nSendTime);
            connect(timer,SIGNAL(timeout()),this,SLOT(slotTimeOut()));
        }
    }
    else
    {
        ui->letCyCleTime->setEnabled(true);
        if(timer != nullptr)
        {
            delete timer;
            timer = nullptr;
        }
    }
}

void WidgetSendCommon::slotTimeOut()
{
    if(serialSend == nullptr)
    {
        return;
    }
    else if(serialSend->isOpen() == true)
    {
        QString sSendBUffer = ui->textEdit->toPlainText();
        nSendLength += sSendBUffer.toLocal8Bit().length();
        if(ui->isEnterSend->isChecked() == true)
        {
            sSendBUffer += "\n";
        }
        if(ui->isHexSend->isChecked() == false)
        {
            serialSend->write(sSendBUffer.toLocal8Bit());
        }
        else
        {
            serialSend->write(fronHexToDec(sSendBUffer).toLocal8Bit());
        }
        emit signalSendNum(nSendLength);
    }
}

void WidgetSendCommon::on_btnSelectSendFile_clicked()
{
    QString sCurrentPath = QDir::currentPath();
    QString sFileName = QFileDialog::getOpenFileName(this,tr("Select the File"),sCurrentPath);
    ui->letSendFilePath->setText(sFileName);
}

void WidgetSendCommon::on_btnSendFile_clicked()
{
//    QFile file(ui->letSendFilePath->text());
//    char sDataBufferBin[file.size()/sizeof(char)];
//    readFileBin(ui->letSendFilePath->text(),sDataBufferBin);
    QString sDataBuffer[1];

    if(serialSend == nullptr)
    {
        QMessageBox::critical(this,"Error","Please open the Serial",QMessageBox::Yes);
        return;
    }
    else if(serialSend->isOpen())
    {
        if(!readFile(ui->letSendFilePath->text(),sDataBuffer))
        {
            QMessageBox::critical(this,"Error","File not found",QMessageBox::Yes);
        }
        else
        {
            serialSend->write(sDataBuffer[0].toLocal8Bit());
            nSendLength += sDataBuffer[0].toLocal8Bit().length();
            emit signalSendNum(nSendLength);
            QMessageBox::information(this,"Notice","File send succeed",QMessageBox::Yes);
        }
    }
    else
    {
        QMessageBox::critical(this,"Error","Please open the Serial",QMessageBox::Yes);
    }
}

void WidgetSendCommon::on_btnClearSendFilePath_clicked()
{
    ui->letSendFilePath->clear();
    nSendLength = 0;
    emit signalSendNum(nSendLength);
}

//读取文件
bool WidgetSendCommon::readFile(QString sFileName, QString *sDataBuffer)
{
    QFile file(sFileName);

    if(file.open(QIODevice::ReadOnly))
    {
        QTextStream stream(&file);
        while (!stream.atEnd())
        {
            sDataBuffer[0] = stream.readAll();
        }
        file.close();
        return true;
    }
    else
    {
        return false;
    }
}

//读取二进制文件
bool WidgetSendCommon::readFileBin(QString sFileName, char *sDataBufferBin)
{
    QFile file(sFileName);
    int i = 0;
    if(file.open(QIODevice::ReadOnly))
    {
//        QTextStream stream(&file);
        while (!file.atEnd())
        {
            file.read((char *)sDataBufferBin,sizeof(char));
//            qDebug()<<QString(sDataBufferBin[i]).toLatin1().toHex();
            i++;
        }
        file.close();
        return true;
    }
}

//初始化配置参数
void WidgetSendCommon::configData()
{
    if(m_sTextEdit == "NULL")
    {
        m_isHexSend = false;
        m_isEnterSend = false;
        m_isTimingSend = false;
        m_letCycleTime = 500;
        m_sTextEdit = "";
    }
    ui->isHexSend->setChecked(m_isHexSend);
    ui->isEnterSend->setChecked(m_isEnterSend);
    ui->isTimingSend->setChecked(m_isTimingSend);
    ui->letCyCleTime->setText(QString("%1").arg(m_letCycleTime));
    ui->textEdit->setPlainText(m_sTextEdit);
    if(m_isTimingSend == true)
    {
        ui->letCyCleTime->setEnabled(false);
    }
}

