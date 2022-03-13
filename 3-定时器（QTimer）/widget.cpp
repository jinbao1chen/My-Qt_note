#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    //QTimer定时器对象指针初始化
    timer = new QTimer;

    //图片编号初始化
    pictureId = 2;

    //显示图片，另一种方法，使用QImage对象
    QImage img;
    img.load("D:\\Qt_project\\QTimer\\1.jpg");
    ui->label->setPixmap(QPixmap::fromImage(img));

    //定时器时间到，发出timeout信号
    //谁发出信号 发出什么信号 谁来处理 怎么处理（槽函数）
    connect(timer, &QTimer::timeout, this, &Widget::timeoutSlot);
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_pushButton_clicked()
{
    timer->start(TIMEOUT);
}

//实现槽函数处理
void Widget::timeoutSlot()
{
    QString path("D:\\Qt_project\\QTimer\\");
    path += QString::number(pictureId);
    path += ".jpg";

    //创建图片对象
    QImage img;
    img.load(path);
    //显示图片
    ui->label->setPixmap(QPixmap::fromImage(img));

    pictureId++;
    if(6 == pictureId)
    {
        pictureId = 1;
    }

}


void Widget::on_pushButton_2_clicked()
{
    timer->stop();
}

//QTimer定时器设置一旦开始就不会停下来，所以设置一个单次的按钮，让定时器只设置一次
void Widget::on_pushButton_3_clicked()
{
    //单次定时器
    QTimer::singleShot(1000, this, SLOT(timeoutSlot()));
}
