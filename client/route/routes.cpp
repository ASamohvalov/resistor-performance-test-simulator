#include "routes.h"
#include "../mainwindow.h"

#include <QDebug>

namespace route
{
    Router::Router(QObject* parent)
        : QObject(parent) {}

    void Router::setTemperature(const QString& data)
    {
        MainWindow::getInstance().setVoltage(data);
    }

    void Router::setAmperage(const QString& data)
    {
        int dividePos = data.indexOf('&');
        if (dividePos == -1) return;
        QString voltage = data.mid(0, dividePos - 1);
        QString power = data.mid(dividePos + 1);
        MainWindow::getInstance().setVoltage(voltage);
        MainWindow::getInstance().setPower(power);
    }
}
