#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    pictureId = 2;

    //开始就会显示一张图片
    QPixmap pix("D:\\Qt_project\\objectTimer\\1.jpg");
    ui->label->setPixmap(pix);
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_startButton_clicked()
{
    //开启定时器，返回定时器编号
    myTimerId = this->startTimer(TIMEOUT);
}

//实现定时器事件，每个定时器都会调用该事件，所以需要通过定时器编号区分是哪个定时器触发的事件
void Widget::timerEvent(QTimerEvent *event)
{
    if(event->timerId() != myTimerId)
    {
        return;
    }

    //更新图片
    //整合路径
    QString path("D:\\Qt_project\\objectTimer\\");
    path += QString::number(pictureId);
    path += ".jpg";

    //创建对象并显示
    QPixmap pix(path);
    ui->label->setPixmap(pix);

    pictureId++;
    if(6 == pictureId)
    {
        pictureId = 1;
    }
}

void Widget::on_pushButton_2_clicked()
{
    //杀死指定的定时器
    this->killTimer(myTimerId);
}
