#ifndef DEFAULT_WIFI_CONNECTOR
#define DEFAULT_WIFI_CONNECTOR

// #include <sstream>
#include <QTextStream>
#include <QDebug>
#include "abstract_wifi_connector.h"
#include "utils.h"

class DefaultWifiConnector : public WifiConnector{
    Q_OBJECT
public:
    
    DefaultWifiConnector(QObject *parent) : WifiConnector(parent) {
        QString buf;
        executeCMD(CHECK_WIFI_NIC_CMD, buf);
        if(!getWifiNic(&buf))
            emit error("未找到网卡");

    }

    virtual QVector<AccessPoint> search(){
        int retry = 5;
        QString buf;
        while(retry--){
            executeCMD(SEARCH_CMD, buf);
            if(buf.length() > 0)
                break;
        }
        if(buf.length() == 0){
            emit error("无法搜索网络");
            return QVector<AccessPoint>();
        }
        qDebug() << buf;
        QTextStream qts(&buf);
        QString line;
        qts.readLineInto(&line);
        int SSIDEnd = line.indexOf("SSID") + 4;
        QVector<AccessPoint> aps;
        while(qts.readLineInto(&line)){
            QString SSID = line.left(SSIDEnd).trimmed();
            qDebug() << "SSID: " << SSID;
            aps.emplace_back(SSID, "");
        }
        return aps;
    }

    virtual bool connect(const AccessPoint& ap) {
        QString buf;
        executeCMD(QString(WIFI_CONNECT_CMD_TEMPLATE).arg(wifiDevice).arg(ap.SSID).arg(ap.password), buf);
        return buf.indexOf("error") == -1;
    }

private:
    QString wifiDevice;
    bool getWifiNic(QString* netInfo) {
        QTextStream qts(netInfo);
        QString line;
        while(qts.readLineInto(&line)) {
            if(line.left(22) == "(Hardware Port: Wi-Fi,"){
                int begin = 31;
                int end = line.lastIndexOf(")");
                wifiDevice = line.mid(begin, end - begin);
                return true;
            }
        }
        return false;
    }
};

#endif