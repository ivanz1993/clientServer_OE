#ifndef TIMER_H
#define TIMER_H
#include <qtimer.h>

#include <QtNetwork>
#include <QTcpSocket>
#include <QObject>
#include <QByteArray>
#include <QDebug>
class Timer :public QTimer
{
    //We will count all the time, that passed in miliseconds
    long timePassed;

    Q_OBJECT
    QTcpSocket* Socket;
    QString Page;
    public:

    Timer(QObject *parent = 0) : QTimer(parent)
    {
        timePassed = 0;
        connect(this, SIGNAL(timeout()), this, SLOT(tick()));
    }

    void Set(QTcpSocket* socket,QString page)
    {
        Socket=socket;
        Page=page;
    }

    private slots:

    //this slot will be connected with the Timers timeout() signal.
    //after you start the timer, the timeout signal will be fired every time,
    //when the amount interval() time passed.
    void tick()
    {
        QTextStream os(Socket);
        os.setAutoDetectUnicode(true);
        QString pages;
        //os>>pages;
        os<<Page;
        Socket->close();
         qDebug()<<Page;
        qDebug()<<"ENDDDDDD!!!!"; //and debug our collected time
           qDebug()<<pages;
        this->stop();
    }
};

#endif // TIMER_H
