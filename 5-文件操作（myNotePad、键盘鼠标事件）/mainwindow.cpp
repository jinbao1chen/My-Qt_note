#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //创建连接 谁发出信号、发出什么信号、谁来处理、怎么处理（槽函数）
    connect(ui->newAction, &QAction::triggered, this, &MainWindow::newActionSlot);
    connect(ui->openAction, &QAction::triggered, this, &MainWindow::openActionSlot);
    connect(ui->saveAction, &QAction::triggered, this, &MainWindow::saveActionSlot);

}

MainWindow::~MainWindow()
{
    delete ui;
}

//新建 槽函数具体实现
void MainWindow::newActionSlot()
{
    ui->textEdit->clear();  //清空窗口
    this->setWindowTitle("新建文本文档.txt");     //修改窗口标题名字
}

//打开 槽函数具体实现
void MainWindow::openActionSlot()
{
    //跳出对话框(记住，使用了类 QFileDialog)
    //QFileDialog::getOpenFileName(this, tr("Open File"),
    //                                                  "/home",
    //                                                  tr("Images (*.png *.xpm *.jpg)"));

    QString fileName = QFileDialog::getOpenFileName(this, "选择一个文件",
                           QCoreApplication::applicationFilePath(), //获取当前路径
                                 "*.cpp");                          //只显示.cpp类型文件
    if(fileName.isEmpty())
    {
        //如果为空，弹出一个提示的对话框
        QMessageBox::warning(this, "警告", "请选择一个文件");
    }
    else
    {
        //如果不为空，将该文件的名字打印出来。Qt如何打印？类似与c++的cout 使用QDebug类
        //qDebug() << fileName;

        //打开该文件并显示内容
        QFile file(fileName);             //创建文件对象
        file.open(QIODevice::ReadOnly);    //如果文件比较少，可以用该方式。如果文件内容比较多，涉及效率问题，需采用其他方式
        QByteArray ba = file.readAll();         //返回值类型QByteArray
        //显示内容
        ui->textEdit->setText(QString(ba));            //将内容转为QString类型，并作为入参
        file.close();
    }
}

//保存 槽函数具体实现
void MainWindow::saveActionSlot()
{
    //跳转对话框，找到路径
    QString fileName = QFileDialog::getSaveFileName(this, "请选择一个文件", QCoreApplication::applicationFilePath());
    if(fileName.isEmpty())
    {
        QMessageBox::warning(this, "警告", "请选择一个文件");
    }
    else
    {
        QFile file(fileName);
        file.open(QIODevice::WriteOnly);    //写内容
        //ui->textEdit->toPlainText();        //显示内容
        QByteArray ba;                      //创建QByteArray对象
        ba.append(ui->textEdit->toPlainText());                        //将显示的内容追加到QByteArray对象后面
        file.write(ba);
        file.close();
    }
}


//重写虚函数，键盘事件
void MainWindow::keyPressEvent(QKeyEvent *k)
{
    //检测 CTRL + S 按键信号
    if(k->modifiers() == Qt::ControlModifier && k->key() == Qt::Key_S)
    {
        saveActionSlot();
    }
}

//重写虚函数，鼠标事件
void MainWindow::mousePressEvent(QMouseEvent *m)
{
    QPoint pt = m->pos();   //QPoint类，获取鼠标位置
    qDebug() << pt;         //打印鼠标位置

    //检测鼠标动作
    if(m->button() == Qt::LeftButton)
    {
        qDebug() << "左键被按下";
    }
    else if(m->button() == Qt::RightButton)
    {
        qDebug() << "右键被按下";
    }
}
