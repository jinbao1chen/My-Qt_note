#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>
#include <QKeyEvent>
#include <QMouseEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    //重载虚函数
    void keyPressEvent(QKeyEvent *k);   //键盘事件
    void mousePressEvent(QMouseEvent *m);   //鼠标事件

//创建槽函数
private slots:
    void newActionSlot();   //新建
    void openActionSlot();  //打开
    void saveActionSlot();  //保存

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
