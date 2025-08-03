#ifndef SENDER_H
#define SENDER_H

#include "serial_port/serial_port.h"

namespace serialPort
{
    class Sender : public SerialPort
    {
    public:
        void send(const std::string& data);
    };
}

#endif