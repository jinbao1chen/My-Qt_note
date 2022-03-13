#include "chart.h"
#include "ui_chart.h"

chart::chart(QTcpSocket *s, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::chart)
{
    ui->setupUi(this);

    socket = s;
}

chart::~chart()
{
    delete ui;
}

//“取消”槽函数实现
void chart::on_clearButton_clicked()
{
    ui->lineEdit->clear();
}
//“发送”槽函数实现
void chart::on_sendButton_clicked()
{
    QByteArray ba;
    ba.append(ui->lineEdit->text());    //将内容转成QByteArray类型发送（写入socket）
    socket->write(ba);
}
