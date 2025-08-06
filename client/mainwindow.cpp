#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "serial_port/serial_port.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    setFixedSize(800, 600);
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    bool ok;
    double temperature = ui->setTemperatureEdit->toPlainText().toDouble(&ok);
    if (!ok) {
        ui->errorMessage->setText("некорректный формат");
        return;
    }
    serialPort::SerialPort::getInstance().writeLine("1/" + QString::number(temperature, 'f'));
    qInfo() << "температура занесена";
}
