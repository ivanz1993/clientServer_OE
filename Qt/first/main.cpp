#include <QCoreApplication>
#include "myserver.h"
#include <QtNetwork/qtcpsocket.h>
#include <QDebug>
#include <QtNetwork>
#include <QTcpSocket>
#include <QObject>
#include <QByteArray>
//#include <QtSql>
QTcpSocket* _pSocket;
int main(int argc, char *argv[])
{

    QCoreApplication a(argc, argv);

    MyServer mServer;

    return a.exec();
}

void readTcpData()
{
    QByteArray data = _pSocket->readAll();
    qDebug()<<data;
}
