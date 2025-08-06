#include "receiver.h"
#include "serial_port.h"

#include <QDebug>

namespace serialPort
{
    void receiverLoop()
    {
        SerialPort& serialPort = SerialPort::getInstance();
        while (true) {
            QString data = serialPort.readLine();
            if (data.isEmpty() || data == "\n") continue;
            // route::call(data);
        }
    }

    void ReceiverThread::run()
    {
        qInfo() << "приемник открыт";
        SerialPort& serialPort = SerialPort::getInstance();
        while (!quit) {
            QString data = serialPort.readLine();
            qInfo() << data;
            if (data.isEmpty() || data == "\n") continue;
            // route::call(data);
        }
    }
}
