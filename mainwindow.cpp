#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtBluetooth>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(agent, SIGNAL(deviceDiscovered(QBluetoothDeviceInfo)), this, SLOT(deviceDiscovered(QBluetoothDeviceInfo)));
    agent->start();

    socket = new QBluetoothSocket(QBluetoothServiceInfo::RfcommProtocol);

}

MainWindow::~MainWindow()
{
    delete ui;

}

void MainWindow::on_btn_find_clicked()
{
    agent->stop();
    agent->start();
}


void MainWindow::on_btn_on_clicked()
{
    socket->write("turn_on");
}


void MainWindow::on_btn_off_clicked()
{
    socket->write("turn_off");
}

void MainWindow::deviceDiscovered(const QBluetoothDeviceInfo &device)
{
    ui->listWidget->addItem(device.address().toString());
}


void MainWindow::on_listWidget_itemClicked(QListWidgetItem *item)
{
    string = item->text();
    ui->listWidget->addItem(string);
    static const QString serviceUuid(QStringLiteral ("00001101-0000-1000-8000-00805F9B34FB"));
    socket->connectToService(QBluetoothAddress(string), QBluetoothUuid(serviceUuid), QIODevice::ReadWrite);
}

