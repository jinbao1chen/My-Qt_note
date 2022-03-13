#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QProcess>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT  //宏定义

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_commitButton_clicked();
    void on_cancelButton_clicked();     //第三种方法仿写

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
