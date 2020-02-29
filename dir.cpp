#include "dir.h"
#include <QDebug>

Dir *Dir::GetDirIns()
{
    static Dir *dirins = nullptr;
    if(dirins == nullptr)
    {
        dirins = new Dir();
    }
    return dirins;
}

Dir::Dir()
{

}

void Dir::saveParam()
{
    QSettings saveValue(CONFIGFILE,QSettings::IniFormat);

    saveValue.beginGroup("settings");
    saveValue.setValue("sPortName", WidgetSettings::GetSettingIns()->m_sPortName);
    saveValue.setValue("nBaudRate", WidgetSettings::GetSettingIns()->m_nBaudRate);
    saveValue.setValue("nStopBit", WidgetSettings::GetSettingIns()->m_nStopBit);
    saveValue.setValue("nDataBit", WidgetSettings::GetSettingIns()->m_nDataBit);
    saveValue.setValue("sParity", WidgetSettings::GetSettingIns()->m_sParity);
    saveValue.setValue("isHexRec", WidgetSettings::GetSettingIns()->m_isHexRec);
    saveValue.setValue("isDisTime", WidgetSettings::GetSettingIns()->m_isDisTime);
    saveValue.setValue("sOpenSerial", WidgetSettings::GetSettingIns()->m_sOpenSerial);
    saveValue.endGroup();

    saveValue.beginGroup("sendCommon");
    saveValue.setValue("isHexSend",WidgetSendCommon::GetSendCommonIns()->m_isHexSend);
    saveValue.setValue("isEnterSend",WidgetSendCommon::GetSendCommonIns()->m_isEnterSend);
    saveValue.setValue("isTimingSend",WidgetSendCommon::GetSendCommonIns()->m_isTimingSend);
    saveValue.setValue("letCycleTime",WidgetSendCommon::GetSendCommonIns()->m_letCycleTime);
    saveValue.setValue("sTextEdit",WidgetSendCommon::GetSendCommonIns()->m_sTextEdit);
    saveValue.endGroup();
}

void Dir::loadParam()
{
    QSettings loadValue(CONFIGFILE,QSettings::IniFormat);

    loadValue.beginGroup("settings");
    WidgetSettings::GetSettingIns()->m_sPortName = loadValue.value("sPortName","NULL").toString();
    WidgetSettings::GetSettingIns()->m_nBaudRate = loadValue.value("nBaudRate","NULL").toInt();
    WidgetSettings::GetSettingIns()->m_nStopBit = loadValue.value("nStopBit","NULL").toInt();
    WidgetSettings::GetSettingIns()->m_nDataBit = loadValue.value("nDataBit","NULL").toInt();
    WidgetSettings::GetSettingIns()->m_sParity = loadValue.value("sParity","NULL").toString();
    WidgetSettings::GetSettingIns()->m_isHexRec = loadValue.value("isHexRec","NULL").toBool();
    WidgetSettings::GetSettingIns()->m_isDisTime = loadValue.value("isDisTime","NULL").toBool();
    WidgetSettings::GetSettingIns()->m_sOpenSerial = loadValue.value("sOpenSerial","NULL").toString();
    loadValue.endGroup();

    loadValue.beginGroup("sendCommon");
    WidgetSendCommon::GetSendCommonIns()->m_isHexSend = loadValue.value("isHexSend","NULL").toBool();
    WidgetSendCommon::GetSendCommonIns()->m_isEnterSend = loadValue.value("isEnterSend","NULL").toBool();
    WidgetSendCommon::GetSendCommonIns()->m_isTimingSend = loadValue.value("isTimingSend","NULL").toBool();
    WidgetSendCommon::GetSendCommonIns()->m_letCycleTime = loadValue.value("letCycleTime","NULL").toInt();
    WidgetSendCommon::GetSendCommonIns()->m_sTextEdit = loadValue.value("sTextEdit","NULL").toString();
    loadValue.endGroup();

    WidgetSettings::GetSettingIns()->configData();
    WidgetSendCommon::GetSendCommonIns()->configData();
}
