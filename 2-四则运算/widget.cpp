#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    //设置界面的尺寸
    this->setMaximumSize(200,300);
    this->setMinimumSize(200,300);

    //设置title
    this->setWindowTitle("计算器");

    //设置字体
    QFont f("仿宋", 14);    //字体对象
    ui->lineEdit->setFont(f);

    //在按钮上放图片
    QIcon con("D:\\Qt_project\\calculator\\del.jpg");
    ui->delButton->setIcon(con);

    //改变按钮背景颜色
    ui->equalButton->setStyleSheet("background:pale green");

}

Widget::~Widget()
{
    delete ui;
}


//点击“1”按钮后，保存值，然后显示
void Widget::on_oneButton_clicked()
{
    expression += "1";
    ui->lineEdit->setText(expression);
}

void Widget::on_twoButton_clicked()
{
    expression += "2";
    ui->lineEdit->setText(expression);
}

void Widget::on_threeButton_clicked()
{
    expression += "3";
    ui->lineEdit->setText(expression);
}

void Widget::on_fourButton_clicked()
{
    expression += "4";
    ui->lineEdit->setText(expression);
}

void Widget::on_fiveButton_clicked()
{
    expression += "5";
    ui->lineEdit->setText(expression);
}

void Widget::on_sixButton_clicked()
{
    expression += "6";
    ui->lineEdit->setText(expression);
}

void Widget::on_sevenButton_clicked()
{
    expression += "7";
    ui->lineEdit->setText(expression);
}

void Widget::on_eightButton_clicked()
{
    expression += "8";
    ui->lineEdit->setText(expression);
}

void Widget::on_nineButton_clicked()
{
    expression += "9";
    ui->lineEdit->setText(expression);
}

void Widget::on_zeroButton_clicked()
{
    expression += "0";
    ui->lineEdit->setText(expression);
}

void Widget::on_leftButton_clicked()
{
    expression += "(";
    ui->lineEdit->setText(expression);
}

void Widget::on_rightButton_clicked()
{
    expression += ")";
    ui->lineEdit->setText(expression);
}

void Widget::on_addButton_clicked()
{
    expression += "+";
    ui->lineEdit->setText(expression);
}

void Widget::on_subButton_clicked()
{
    expression += "-";
    ui->lineEdit->setText(expression);
}

void Widget::on_mulButton_clicked()
{
    expression += "*";
    ui->lineEdit->setText(expression);
}

void Widget::on_diveButton_clicked()
{
    expression += "/";
    ui->lineEdit->setText(expression);
}

//清空
void Widget::on_clearButton_clicked()
{
    //清空字符串
    expression.clear();
    //清空显示
    ui->lineEdit->clear();
}

//删除
void Widget::on_delButton_clicked()
{
    //点击一下删除一个。chop成员函数是将字符串末尾的字符删除n个，n是入参数。
    expression.chop(1);
    //显示
    ui->lineEdit->setText(expression);
}

//关键位置，点击"="出数据。计算器算法
void Widget::on_equalButton_clicked()
{
    QStack<int> s_num, s_opt;

    char opt[128] = {0};
    int i=0, tmp=0, num1, num2;

    //把QString转换成char *
    QByteArray ba;
    ba.append(expression);      //把QString转换成QByteArray
    strcpy(opt, ba.data());     //data可以把QByteArray转换成const char *

    while(opt[i] != '\0' || s_opt.empty() != true)
    {
        if(opt[i] >= '0' && opt[i] <= '9')
        {
            tmp = tmp * 10 + opt[i] - '0';
            i++;
            if(opt[i]<'0' || opt[i]>'9')
            {
                s_num.push(tmp);
                tmp = 0;
            }
        }
        else        //操作符
        {
            if(s_opt.empty() == true || Priority(opt[i]) > Priority(s_opt.top()) ||
                    (s_opt.top() == '(' && opt[i] != ')'))
            {
                s_opt.push(opt[i]);
                i++;
                continue;
            }

            if(s_opt.top() == '(' && opt[i] == ')')
            {
                s_opt.pop();
                i++;
                continue;
            }

            if(Priority(opt[i]) <= Priority(s_opt.top()) || (opt[i] == ')' && s_opt.top() != '(') ||
                    (opt[i] == '\0' && s_opt.empty() != true))
            {
                char ch = s_opt.top();
                s_opt.pop();
                switch(ch)
                {
                    case '+':
                        num1 = s_num.top();
                        s_num.pop();
                        num2 = s_num.top();
                        s_num.pop();
                        s_num.push(num1 + num2);
                        break;
                    case '-':
                        num1 = s_num.top();
                        s_num.pop();
                        num2 = s_num.top();
                        s_num.pop();
                        s_num.push(num1 - num2);
                        break;
                    case '*':
                        num1 = s_num.top();
                        s_num.pop();
                        num2 = s_num.top();
                        s_num.pop();
                        s_num.push(num1 * num2);
                        break;
                    case '/':
                        num1 = s_num.top();
                        s_num.pop();
                        num2 = s_num.top();
                        s_num.pop();
                        s_num.push(num1 / num2);
                        break;

                }
            }
        }
    }

    //最后留在栈里的元素就是结果，显示出来
    ui->lineEdit->setText(QString::number(s_num.top()));
    expression.clear();

}

//写成成员函数
int Widget::Priority(char ch)
{
    switch (ch)
    {
        case '(':
            return 3;
        case '*':
        case '/':
            return 2;
        case '+':
        case '-':
            return 1;
        default:
            return 0;
    }
}




































