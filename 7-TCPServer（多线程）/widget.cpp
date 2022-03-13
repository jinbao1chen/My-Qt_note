#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    server = new QTcpServer;    //创建服务器对象
    //不需要绑定
    server->listen(QHostAddress::AnyIPv4, PORT);    //监听
    //客户端发起连接,server发出信号,创建槽函数接收到信号后进行处理
    connect(server, &QTcpServer::newConnection, this, &Widget::newTcpClientConnectSlot);
}

Widget::~Widget()
{
    delete ui;
}

//槽函数实现，处理接收到的客户端连接
void Widget::newTcpClientConnectSlot()
{
    //建立TCP连接
    QTcpSocket *socket = server->nextPendingConnection();
    //获取客户端地址(QHostAddress类型，显示出来需要转换成QString类型)和端口号(quint16类型，需要转换成QString类型)
    //socket->peerAddress();
    //socket->peerPort();

    ui->ipLineEdit->setText(socket->peerAddress().toString());
    ui->portLineEdit->setText(QString::number(socket->peerPort()));

    /*Qt启动新窗口 服务器端修改*/
    //服务器接收到客户端发送的信息，socket发出readyread信号，构建一个槽函数进行处理
    //connect(socket, &QTcpSocket::readyRead, this, &Widget::clientInfoSlot); /*Qt多线程*/


    /*Qt多线程*/
    //启动线程
    myThread *t = new myThread(socket);    //将widget类中的socket传递到myThread类中
    t->start();

    /*自定义信号*/
    //接受线程信号并创建槽函数处理
    connect(t, &myThread::sendToWidget, this, &Widget::threadSlot);
}

/*自定义信号*/
//处理线程信息的槽函数
void Widget::threadSlot(QByteArray b)
{
    ui->lineEdit->setText(QString(b));
}

/*Qt启动新窗口 服务器端修改*/
//槽函数实现，接收
/*Qt多线程 注释掉*/
//void Widget::clientInfoSlot()
//{
//    //获取信号的发出者
//    QTcpSocket *s = (QTcpSocket *)sender();

//    ui->lineEdit->setText(QString(s->readAll()));  //接收到的数据QByteArray类型，转成QString类型
//}
