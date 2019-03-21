#include "udpserver.h"
#include "ui_udpserver.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <net/if.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <sys/ioctl.h>
#include <string>
using namespace std;

udpserver::udpserver(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::udpserver)
{
    ui->setupUi(this);
    setWindowTitle(tr("UDP Server"));
    m_Server_udp = new QUdpSocket(this);
    port=6000;
    QString ip="127.0.0.1";
    serverAddress=QHostAddress(ip);
    m_Server_udp -> bind(serverAddress,6000);
    connect(m_Server_udp,SIGNAL(readyRead()),this,SLOT(dataReceive()));

    //memset(clients,0,sizeof(clients));
    Number=0;
}

udpserver::~udpserver()
{
    delete ui;
}


void udpserver::dataReceive(){
    while(m_Server_udp->hasPendingDatagrams()){//拥有等待的数据报
        QByteArray TempArray2;//用于存放接受的数据报
        //让temparray2的大小为等待处理的数据报的大小，这样才能接收到完整的数据
        TempArray2.resize(m_Server_udp->pendingDatagramSize());
        //接受数据报，将其存放到temparray2中
        QHostAddress sender;
        quint16 senderPort;
        m_Server_udp->readDatagram(TempArray2.data(),TempArray2.size(),&sender,&senderPort);

        //看是否新用户
        if(Number==0){
            clientsPORT[Number]=senderPort;
            clientsIP[Number]=sender.toString();
            Number++;
        }
        else{
            for(int i=0;i<Number;i++){
                if(clientsPORT[i]==senderPort && clientsIP[i]==sender.toString()) goto L1;
            }
            clientsPORT[Number]=senderPort;
            clientsIP[Number]=sender.toString();
            Number++;
        }
        L1:
        for(int i=0;i<Number;i++){
            sender=(QHostAddress)clientsIP[i];
            senderPort=clientsPORT[i];
            m_Server_udp->writeDatagram(TempArray2,sender,senderPort);//send message
        }
//       QString temp=sender.toString();
//       ui->contentListWidget->addItem(temp);

        //将数据报的内容显示出来
        TempMessage=TempArray2;
        //添加到界面上
        ui->contentListWidget->addItem(TempMessage);
    }
}

