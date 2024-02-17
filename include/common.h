#ifndef COMMON_H
#define COMMON_H

const char SEARCH_CMD[] = "/System/Library/PrivateFrameworks/Apple80211.framework/Versions/Current/Resources/airport -s";
const char CHECK_WIFI_NIC_CMD[] = "networksetup -listnetworkserviceorder";
const char WIFI_CONNECT_CMD_TEMPLATE[] = "networksetup -setairportnetwork %1 %2 %3";

#endif