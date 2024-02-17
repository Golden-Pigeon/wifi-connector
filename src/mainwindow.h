#ifndef mainwindow_h
#define mainwindow_h

#include <QMainWindow>
#include <QScopedPointer>
#include "abstract_wifi_connector.h"
#include <QThread>




namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow {
    friend class ConnectThread;
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    virtual ~MainWindow();

private:
    QScopedPointer<Ui::MainWindow> ui;
    WifiConnector *conn;

signals:
    void showMsg(const QString &msg);

private slots:
    void connectWifi();
    void showWarning(const QString &msg);
};

class ConnectThread : public QThread {
    Q_OBJECT;
public:
    ConnectThread(MainWindow *window) : QThread(window), window(window) {}
protected:
    void run();
private:
    MainWindow *window;
signals:
    void showMsg(const QString &msg);

};

#endif
