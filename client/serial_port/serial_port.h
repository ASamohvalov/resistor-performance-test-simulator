#ifndef SERIAL_PORT_H
#define SERIAL_PORT_H

#include <QString>

namespace serialPort 
{
    class SerialPort
    {
    public:
        static SerialPort& getInstance();
        
        QString readLine() const;
        void writeLine(const QString& data) const;
    
    private:
        SerialPort();
        ~SerialPort();

        void openPort();

        int fd_ = 0;
        const QString portfile_;
    };
}

#endif
