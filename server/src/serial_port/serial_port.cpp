#include "serial_port.h"
#include "config/env_handler.h"

#include <fcntl.h>
#include <spdlog/spdlog.h>
#include <stdexcept>
#include <unistd.h>
#include <termios.h>

namespace serialPort
{
    SerialPort::SerialPort() : portfile_(config::getEnv("SERVER_COM_PORT"))
    {
        openPort();
    }

    SerialPort::~SerialPort()
    {
        if (fd_ >= 0) {
            close(fd_);
            spdlog::info("port " + portfile_ + " is closed");
        }
    }

    SerialPort& SerialPort::getInstance()
    {
        static SerialPort instance;
        return instance;
    }

    void SerialPort::openPort() {
        fd_ = open(portfile_.c_str(), O_RDWR | O_NOCTTY);
        if (fd_ < 0) {
            throw std::runtime_error("failed to open port: " + portfile_);
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
        spdlog::info("port " + portfile_ + " is open");
    }

    std::string SerialPort::readLine() const
    {
        std::string line;
        char sy;
        while (read(fd_, &sy, 1) == 1) {
            if (sy == '\n') {
                break;
            }
            line += sy;
        }
        return line;
    }

    void SerialPort::writeLine(const std::string& data) const
    {
        spdlog::info("set to client port - " + data);
        const std::string message = data + "\n";
        write(fd_, message.c_str(), message.length());
        tcdrain(fd_);
    }
}