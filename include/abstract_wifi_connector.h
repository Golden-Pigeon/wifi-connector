#ifndef ABSTRACT_WIFI_CONNECTOR
#define ABSTRACT_WIFI_CONNECTOR

#include <QVector>
#include <QObject>
#include "access_point.h"

class WifiConnector : public QObject  {
    Q_OBJECT
public:
    WifiConnector(QObject *parent) : QObject(parent) {}
    virtual QVector<AccessPoint> search() = 0;
    virtual bool connect(const AccessPoint& ap) = 0;

signals:
    void dispMessage(const QString &msg);
    void error(const QString &msg);
};


#endif