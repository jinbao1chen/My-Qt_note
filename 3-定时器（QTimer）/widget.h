#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTimer>       //包含定时器类头文件

#define TIMEOUT 1 * 1000   //定义定时器时间1s

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
    void on_pushButton_clicked();

    //发出超时信号后，如何处理，需要一个槽函数
    void timeoutSlot();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::Widget *ui;
    //创建一个QTimer对象
    QTimer *timer;

    //图片编号
    int pictureId;
};
#endif // WIDGET_H
