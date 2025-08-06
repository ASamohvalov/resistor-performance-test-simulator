#include "mainwindow.h"
#include "serial_port/receiver.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    serialPort::ReceiverThread receiver;
    receiver.start();

    MainWindow w;
    w.show();

    return a.exec();
}
