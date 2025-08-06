#ifndef RECEIVER_H
#define RECEIVER_H

#include <QThread>
#include <QObject>

namespace serialPort
{
    void receiverLoop();

    class ReceiverThread : public QThread
    {
        Q_OBJECT

    public:
        bool quit = false;

    private:
        void run() override;
        
    };
}

#endif // RECEIVER_H