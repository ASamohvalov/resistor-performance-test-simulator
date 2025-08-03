#ifndef SERIAL_PORT_H
#define SERIAL_PORT_H

#include <string>

namespace serialPort 
{
    class SerialPort
    {
    public:
        SerialPort();
        ~SerialPort();

    protected:
        void openPort();

        std::string readLine();
        void writeLine(const std::string& data);
    
    private:
        int fd_ = 0;
        const std::string portfile_;
    };
}

#endif