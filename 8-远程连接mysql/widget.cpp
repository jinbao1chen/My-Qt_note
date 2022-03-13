#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    //连接数据库
    db = QSqlDatabase::addDatabase("QMYSQL");    //加载MYSQL数据库驱动

    db.setDatabaseName("mydatabase");           //数据库名字，已提前在mysql中创建好的'create database mydatabase;'
    db.setHostName("localhost");                //连接数据库所在主机，此处是本地数据库本地连接
    db.setUserName("root");                     //数据库用户名
    //db.setPassword("123456");                   //数据库密码

    //打开数据库
    if(db.open())
    {
        //设置提示，需包含头文件 #include <QMessageBox>
        QMessageBox::information(this, "连接提示", "连接成功");
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


void Widget::on_insertPushButton_clicked()
{
    QString id = ui->idLineEdit->text();
    QString name = ui->nameLineEdit->text();
    QString birth = ui->lineEdit_2->text();

    //QString sql = QString("insert into student values (1, "Tom", "1999-9-9");")
    QString sql = QString("insert into student values (%1, '%2', '%3');").arg(id).arg(name).arg(birth);

    //插入，建立一个操作数据库的对象
    QSqlQuery query;
    if(query.exec(sql))
    {
        QMessageBox::information(this, "插入提示", "插入成功");
    }
    else
    {
        QMessageBox::information(this, "插入提示", "插入失败");
    }

}

void Widget::on_findPushButton_clicked()
{
    QSqlQuery query;
    query.exec("select * from student;");
    while (query.next())
    {
        //将查询的结果打印出来
        qDebug() << query.value(0);
        qDebug() << query.value(1);
        qDebug() << query.value(2);
    }
}
