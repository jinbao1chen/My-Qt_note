#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    //连接远程数据库
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");

    //设置连接属性，数据库ip、用户名、密码
    db.setHostName("106.55.102.137");
    db.setDatabaseName("mydatabase");
    db.setUserName("test");
    db.setPassword("test");

    if(db.open())
    {
        QMessageBox::information(this, "连接提示", "连接成功");

        //新建模型对象
        m = new QSqlTableModel;
        m->setTable("student");
        ui->tableView->setModel(m);     //将数据模型m对象与ui界面模型tableView连接起来


    }
    else
    {
        QMessageBox::warning(this, "连接提示", "连接失败");
    }
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_pushButton_clicked()
{
    m->select();  //model模型对象的成员函数select查询
}
