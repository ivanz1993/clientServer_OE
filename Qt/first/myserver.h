#ifndef MYSERVER_H
#define MYSERVER_H

#include <QtNetwork>
#include <QTcpSocket>
#include <QObject>
#include <QByteArray>
#include <QDebug>
class MyServer : public QObject
{
    Q_OBJECT
public:
    explicit MyServer(QObject *parent = 0);

signals:

public slots:
private slots:
     void newuser();
     void slotReadClient();
private:

    QTcpServer *tcpServer;
    QMap<int,QTcpSocket*> SClients;
};

#endif // MYSERVER_H
