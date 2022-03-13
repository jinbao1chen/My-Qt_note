#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTcpServer>
#include <QTcpSocket>

/*Qt多线程*/
#include <mythread.h>

#define PORT 8000

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void newTcpClientConnectSlot();

    /*Qt启动新窗口 服务器端修改*/
    //void clientInfoSlot();

    /*自定义信号*/
    void threadSlot(QByteArray b);

private:
    Ui::Widget *ui;

    QTcpServer *server;

};
#endif // WIDGET_H
