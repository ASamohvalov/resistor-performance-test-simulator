#include "receiver.h"
#include "serial_port.h"
#include "../route/route_provider.h"

#include <QDebug>

namespace serialPort
{
    ReceiverThread::ReceiverThread(QObject* parent)
        : QThread(parent) {}

    void ReceiverThread::run()
    {
        qInfo() << "приемник открыт";
        SerialPort& serialPort = SerialPort::getInstance();
        while (!quit) {
            QString data = serialPort.readLine();
            if (data.isEmpty() || data == "\n") continue;
            qInfo() << "получены данные -" << data;
            route::RouteProvider* provider = new route::RouteProvider(data);
            provider->router();
            connect(provider, &QThread::finished, provider, &QObject::deleteLater);
        }
    }

    void ReceiverThread::getMessage(const QString& data, Message message)
    {
        switch (message) {
        case Message::Temperature:
            emit setResistance(data);
            break;
        case Message::Voltage:
            emit setVoltage(data);
            break;
        case Message::Power:
            emit setPower(data);
            break;
        }
    }
}
