#ifndef RECEIVER_H
#define RECEIVER_H

#include "serial_port/serial_port.h"

namespace serialPort
{
    class Receiver : public SerialPort
    {
    public:
        void start();
        bool quit = false;
    };
}

#endif // RECEIVER_H