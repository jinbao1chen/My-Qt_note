#ifndef CHART_H
#define CHART_H

#include <QWidget>
#include <QTcpSocket>

namespace Ui {
class chart;
}

class chart : public QWidget
{
    Q_OBJECT

public:
    //explicit chart(QWidget *parent = nullptr);
    /*修改chart构造函数，将socket传递给chart对象*/
    explicit chart(QTcpSocket *s, QWidget *parent = nullptr);
    ~chart();

private slots:
    void on_clearButton_clicked();
    void on_sendButton_clicked();

private:
    Ui::chart *ui;

    QTcpSocket *socket;
};

#endif // CHART_H
