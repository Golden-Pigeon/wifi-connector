#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "debug_wifi_connector.h"
#include "default_wifi_connector.h"
#include <QMessageBox>
#include <QThread>

void ConnectThread::run(){
    emit showMsg("连接中...");
    AccessPoint ap(window->ui->wifiDropDown->currentText(), window->ui->passwdInput->text());
    if(window->conn->connect(ap))
        emit showMsg("连接成功");
    else
        emit showMsg("连接失败");
}

MainWindow::MainWindow(QWidget *parent)
: QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    conn = new DefaultWifiConnector(this);
    connect(conn, &WifiConnector::dispMessage, ui->statusArea, &QTextEdit::setText);
    connect(this, &MainWindow::showMsg, ui->statusArea, &QTextEdit::setText);
    
    connect(ui->connectButton, &QPushButton::clicked, this, &MainWindow::connectWifi);
    connect(conn, &WifiConnector::error, this, &MainWindow::showWarning);
    auto aps = conn->search();
    for(auto &ap : aps) {
        ui->wifiDropDown->addItem(ap.SSID);
    }
}

void MainWindow::connectWifi(){
    ConnectThread *t = new ConnectThread(this);
    connect(t, &ConnectThread::showMsg, ui->statusArea, &QTextEdit::setText);
    t->start();
}

void MainWindow::showWarning(const QString &msg) {
    QMessageBox::warning(this, "警告", msg);
}

MainWindow::~MainWindow()
{
    delete conn;
}
