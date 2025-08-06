#include "serial_port.h"
#include "../config/env_handler.h"

#include <fcntl.h>
#include <qglobal.h>
#include <stdexcept>
#include <unistd.h>
#include <termios.h>

#include <QDebug>

namespace serialPort
{
    SerialPort::SerialPort() : portfile_(config::getEnv("CLIENT_COM_PORT"))
    {
        openPort();
        qInfo() << "порт " + portfile_ + " открыт";
    }

    SerialPort::~SerialPort()
    {
        if (fd_ >= 0) {
            close(fd_);
        }
    }

    SerialPort& SerialPort::getInstance()
    {
        static SerialPort instance;
        return instance;
    }

    void SerialPort::openPort() {
        fd_ = open(portfile_.toUtf8().data(), O_RDWR | O_NOCTTY);
        if (fd_ < 0) {
            throw std::runtime_error("failed to open port: " + portfile_.toStdString());
        }

        termios tty;
        if (tcgetattr(fd_, &tty) != 0) {
            close(fd_);
            throw std::runtime_error("failed to get port attributes");
        }

        tty.c_iflag = 0;
        tty.c_oflag = 0;
        tty.c_lflag = 0;
        tty.c_cflag |= (CLOCAL | CREAD);
        tty.c_cc[VMIN] = 1;
        tty.c_cc[VTIME] = 0;

        if (tcsetattr(fd_, TCSANOW, &tty) != 0) {
            close(fd_);
            throw std::runtime_error("failed to set port attributes");
        }
    }

    QString SerialPort::readLine() const
    {
        QString line;
        char sy;
        while (read(fd_, &sy, 1) == 1) {
            if (sy == '\n') {
                break;
            }
            line += sy;
        }
        return line;
    }

    void SerialPort::writeLine(const QString& data) const
    {
        QByteArray message = data.toUtf8() + '\n';
        write(fd_, message.data(), message.size());
    }
}
