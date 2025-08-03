#include "serial_port/receiver.h"

int main()
{
    serialPort::Receiver receiver;
    receiver.start();

    return 0; 
}
