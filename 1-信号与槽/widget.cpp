#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    //第二种方法，把信号和槽连接起来 谁发出信号 发出什么信号 谁处理信号 怎么处理
    //returnPressed() 信号种类：按下键盘发出的信号
    //this处理
    //on_commitButton_clicked() 相当于点击 “确定”触发执行槽函数处理
    connect(ui->lineEdit, SIGNAL(returnPressed()), this, SLOT(on_commitButton_clicked()));

    //第三种方法：通过地址的形式实现。仿照点击“确定”，写“取消”操作
    connect(ui->cancelButton, &QPushButton::clicked, this, &Widget::on_cancelButton_clicked);

    //第四种方法：当槽函数处理的内容比较少时。以“浏览”按钮为例
    connect(ui->browseButton, &QPushButton::clicked, [this]()
    {
        //弹出一个子对话框进行提示
        QMessageBox::information(this, "信息", "点击浏览");
    });
}

Widget::~Widget()
{
    delete ui;
}


//第一种方法：右击转到槽
//点击"确定" 槽函数
void Widget::on_commitButton_clicked()
{
    //获取lineedit数据
    QString program = ui->lineEdit->text();

    //启动一个新的进程，包含类QProcess
    //创建一个process对象
    QProcess *myProcess = new QProcess(this);
    //myProcess->start(program, arguments);
    myProcess->start(program);
}

//第三种方法：仿写
void Widget::on_cancelButton_clicked()
{
    //点击下“取消”按钮时，关闭界面
    this->close();
}
