#ifndef UDPSERVER_H
#define UDPSERVER_H

#include <QtNetwork/QtNetwork>
#include <QMainWindow>


namespace Ui {
class udpserver;
}

class udpserver : public QMainWindow
{
    Q_OBJECT

public:
    explicit udpserver(QWidget *parent = 0);
    ~udpserver();

private:
    Ui::udpserver *ui;
    QUdpSocket *m_Server_udp;
    QString clientname;
    int port;
    QString Message,TempMessage;
    QHostAddress serverAddress;
    int Number;
    QString clientsIP[100];
    quint16  clientsPORT[100];
public slots:
    void dataReceive();
};

#endif // UDPSERVER_H
