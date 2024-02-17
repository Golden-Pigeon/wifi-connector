#ifndef ACCESS_POINT
#define ACCESS_POINT

#include <QString>

struct AccessPoint {
    QString SSID;
    QString password;
    AccessPoint(const QString &SSID, const QString &password) : SSID(SSID), password(password) {}
};

#endif