#include "widget.h"
#include "ui_widget.h"
#include "chart.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    socket = new QTcpSocket; //创建socket对象
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_cancelButton_clicked()
{
    this->close();
}

//连接槽函数实现：点击"连接"时，先获取ip地址和端口号
void Widget::on_connectButton_clicked()
{
    //获取ip地址,获取QString类型，后面需转换为QHostAddress类型类型（如何转换？ QHostAddress(const QString &address)）
    QString IP = ui->ipLineEdit->text();
    //获取端口号
    QString Port = ui->portLineEdit->text();

    //连接服务器.connectToHost函数参数：主机名（QHostAddress类型）、端口号（quint16类型）
    socket->connectToHost(QHostAddress(IP), Port.toShort());

    //连接服务器成功，socket对象会发出信号
    connect(socket, &QTcpSocket::connected, [this]()
    {
       QMessageBox::information(this, "连接提示", "连接服务器成功");

       /*Qt启动新窗口*/
       this->hide();  //隐藏之前界面

       chart *c = new chart(socket);        //在对空间创建chart对象
       c->show();
    });

    //连接断开，socket也会发出信号
    connect(socket, &QTcpSocket::disconnected, [this]()
    {
        QMessageBox::warning(this, "连接提示", "连接异常 断开服务器");
    });

}
