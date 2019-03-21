#include "udpcilent.h"
#include "ui_udpcilent.h"
#include <iostream>

udpcilent::udpcilent(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::udpcilent)
{
    ui->setupUi(this);
    setWindowTitle(tr("TCP Client"));
    m_Client_udp = new QUdpSocket(this);

    QObject::connect(ui->enterBtn,SIGNAL(clicked()),this,SLOT(slotEnter()));
    QObject::connect(ui->sendButton,SIGNAL(clicked()),this,SLOT(slotSend()));
    QObject::connect(m_Client_udp,SIGNAL(readyRead()),this,SLOT(dataReceived()));
}

udpcilent::~udpcilent()
{
    delete ui;
}

void udpcilent::slotEnter(){
    ui->enterBtn->setEnabled(false);
    QString ip = ui->serverIPLineEdit->text();//get ip
    serverAddress=QHostAddress(ip);
    username = ui->userNameLineEdit->text();//get username
    username+=": ";
    port=ui->portLineEdit->text().toInt();//get port
    TempMessage="loading... please send imformation ";
    ui->contentListWidget->addItem(TempMessage);
}
void udpcilent::slotSend(){
    if(ui->sendLineEdit->text()==""){//get message
        return;
    }
    else{
        Message=username+ui->sendLineEdit->text();
        QByteArray TempArray=Message.toLatin1();
        m_Client_udp->writeDatagram(TempArray,serverAddress, port);//send message
    }
}
void udpcilent::dataReceived(){
    while(m_Client_udp->hasPendingDatagrams()){//拥有等待的数据报
        QByteArray TempArray2;//用于存放接受的数据报
        //让temparray2的大小为等待处理的数据报的大小，这样才能接收到完整的数据
        TempArray2.resize(m_Client_udp->pendingDatagramSize());
        //接受数据报，将其存放到temparray2中
        m_Client_udp->readDatagram(TempArray2.data(),TempArray2.size());//re
        //将数据报的内容显示出来
        TempMessage=TempArray2;
        //添加到界面上
        ui->contentListWidget->addItem(TempMessage);
    }
}
