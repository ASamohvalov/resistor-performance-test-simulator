#ifndef RECEIVER_H
#define RECEIVER_H

#include <QThread>
#include <QObject>

namespace serialPort
{
    enum class Message { Temperature, Voltage, Power };

    class ReceiverThread : public QThread
    {
        Q_OBJECT
    public:
        ReceiverThread(QObject* parent = nullptr);
        bool quit = false;

    signals:
        void setResistance(const QString& resistance);
        void setVoltage(const QString& voltage);
        void setPower(const QString& power);

    protected:
        void run() override;

    private slots:
        void getMessage(const QString& data, Message message);
    };
}

#endif // RECEIVER_H
