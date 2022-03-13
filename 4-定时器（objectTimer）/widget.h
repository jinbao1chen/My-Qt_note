#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

//定义超时时间
#define TIMEOUT 1* 1000

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);

    //触发定时事件,不同定时器可以通过编号区分
    virtual void timerEvent(QTimerEvent *event);


    ~Widget();

private slots:
    void on_startButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::Widget *ui;

    //定义保存定时器编号的变量
    int myTimerId;
    //记录当前显示的是第几张图片
    int pictureId;
};
#endif // WIDGET_H
