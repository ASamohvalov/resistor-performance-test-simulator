#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "serial_port/serial_port.h"

#include <QDebug>
#include <chrono>
#include <qglobal.h>
#include <qtablewidget.h>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <thread>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    setFixedSize(888, 576);
    ui->setupUi(this);

    ui->progressBar->setMinimum(-150); // минимальная температура
    ui->progressBar->setMaximum(150); // максимальная температура

    ui->progressBar->setValue(-45); // начальная температура

    QLabel *labelMin = new QLabel("-150", this);
    labelMin->setGeometry(ui->progressBar->x(), ui->progressBar->y() + ui->progressBar->height() + 5, 30, 20);

    QLabel *labelMid1 = new QLabel("0", this);
    labelMid1->setGeometry(ui->progressBar->x() + ui->progressBar->width() / 2 - 15, ui->progressBar->y() + ui->progressBar->height() + 5, 30, 20);

    QLabel *labelMax = new QLabel("150", this);
    labelMax->setGeometry(ui->progressBar->x() + ui->progressBar->width() - 30, ui->progressBar->y() + ui->progressBar->height() + 5, 30, 20);

    ui->progressBar->setStyleSheet(
        "QProgressBar {"
        "border: 2px solid grey;"
        "border-radius: 5px;"
        "text-align: center;"
        "}"
        "QProgressBar::chunk {"
        "background-color: qlineargradient(x1: 0, y1: 0, x2: 1, y2: 0,"
        "stop: 0 #00ff00, stop: 0.5 #ffff00, stop: 1 #ff0000);"
        "}"

        );

    ui->tableWidget->setRowCount(6);
}

MainWindow::~MainWindow()
{
    delete ui;
}

MainWindow& MainWindow::getInstance()
{
    static MainWindow w;
    return w;
}

void MainWindow::setResistance(const QString& res)
{
    QTableWidgetItem *item = new QTableWidgetItem(res + " (Ом)");
    item->setTextAlignment(Qt::AlignCenter);
    ui->tableWidget->setItem(0, 0, item);
}

void MainWindow::setVoltage(const QString& vol)
{
    QTableWidgetItem *item = new QTableWidgetItem(vol + " (B)");
    item->setTextAlignment(Qt::AlignCenter);
    ui->tableWidget->setItem(0, 1, item);
}

void MainWindow::setPower(const QString& power)
{
    QTableWidgetItem *item = new QTableWidgetItem(power + " (Вт)");
    item->setTextAlignment(Qt::AlignCenter);
    ui->tableWidget->setItem(0, 2, item);
}

void MainWindow::on_pushButton_clicked()
{
    bool ok;
    double res = ui->lineEdit->text().toDouble(&ok);
    double amp = ui->lineEdit_2->text().toDouble(&ok); 
    if (!ok) {
        return;
    }
    ui->progressBar->setValue(res);
    int index = ui->mainTemp->text().indexOf('=');
    ui->mainTemp->setText(ui->mainTemp->text().mid(0, index + 2) + " " + ui->lineEdit->text());

    qInfo() << ui->lineEdit->text();
    qInfo() << ui->lineEdit_2->text();
    serialPort::SerialPort::getInstance().writeLine("1/" + ui->lineEdit->text());
    serialPort::SerialPort::getInstance().writeLine("2/" + ui->lineEdit_2->text());
}
