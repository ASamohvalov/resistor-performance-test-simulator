#include "receiver.h"
#include "route/route_provider.h"
#include "serial_port/serial_port.h"

#include <spdlog/spdlog.h>

namespace serialPort
{
    void receiverLoop()
    {
        SerialPort& serialPort = SerialPort::getInstance();
        while (true) {
            std::string data = serialPort.readLine();
            if (data.empty() || data == "\n") continue;
            route::call(data);
        }
    }
}