#ifndef DEBUG_WIFI_CONNECTOR
#define DEBUG_WIFI_CONNECTOR
#include <QObject>
#include "abstract_wifi_connector.h"
#include "common.h"
class DebugWifiConnector : public WifiConnector{
    Q_OBJECT
public:
    
    DebugWifiConnector(QObject *parent) : WifiConnector(parent) {

    }

    virtual QVector<AccessPoint> search(){
        emit dispMessage(SEARCH_CMD);
        return QVector<AccessPoint>();
    }

    virtual bool connect(const AccessPoint& ap) {
        emit dispMessage(QString(WIFI_CONNECT_CMD_TEMPLATE).arg(wifiDevice).arg("SSID").arg("pasword"));
        return true;
    }

private:
    QString wifiDevice = "en0";
};


#endif