#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QObject>
#include <QThread>
/*Qt多线程*/
#include <QTcpSocket>
#include <QDebug>

class myThread : /*public QObject,*/ public QThread
{
    Q_OBJECT
public:
    explicit myThread(QTcpSocket *s);    //, QObject *parent = nullptr);    /*Qt多线程 传参*/
    /*Qt多线程 重写run()函数*/
    void run();

signals:
    /*自定义信号*/
    void sendToWidget(QByteArray b);    //自定义信号，信号也是函数

public slots:
    void clientInfoSlot();      /*Qt多线程 槽函数，收到客户端TCP连接信号之后处理*/

private:
    QTcpSocket *socket;
};

#endif // MYTHREAD_H
