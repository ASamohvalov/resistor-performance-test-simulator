#include "sender.h"

namespace serialPort
{
    void Sender::send(const std::string& data)
    {
        openPort();
        writeLine(data);
    }
}