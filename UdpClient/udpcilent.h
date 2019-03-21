#ifndef UDPCILENT_H
#define UDPCILENT_H

#include <QMainWindow>
#include <QtNetwork/QtNetwork>
#include <QTcpSocket>
#include <QHostAddress>
namespace Ui {
class udpcilent;

}

class udpcilent : public QMainWindow
{
    Q_OBJECT

public:
    explicit udpcilent(QWidget *parent = 0);
    ~udpcilent();

private:
   Ui::udpcilent *ui;
   QUdpSocket *m_Sever_udp;
   QUdpSocket  *m_Client_udp;
   QString username;
   int port;
   QString TempMessage,Message;
   QHostAddress serverAddress;
public slots:
   void slotEnter();
   void slotSend();
   void dataReceived();
};

#endif // UDPCILENT_H
