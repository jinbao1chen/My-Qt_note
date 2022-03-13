#include "mythread.h"

myThread::myThread(QTcpSocket *s)//,QObject *parent) //: QObject(parent)
{
    socket = s;
}

void myThread::run()
{
    //在线程里处理客户端TCP连接
    connect(socket, &QTcpSocket::readyRead, this, &myThread::clientInfoSlot);
}

//不能在其他类里面操作界面，也就是不能再线程里操作widget类里的ui
void myThread::clientInfoSlot()
{
    //qDebug() << socket->readAll();  /*Qt多线程 打印接收到的内容*/

    /*自定义信号*/
    //将接收的数据读取
    QByteArray ba = socket->readAll();
    emit sendToWidget(ba);              //发送信号
}
