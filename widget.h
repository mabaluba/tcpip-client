#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTcpSocket>
#include <QHostAddress>

QT_BEGIN_NAMESPACE
namespace Ui { class Client; }
QT_END_NAMESPACE

class WidgetClient : public QWidget
{
    Q_OBJECT

public:
    WidgetClient(QWidget *parent = nullptr);
    ~WidgetClient();

private slots:
    void on_pushButton_Connect_clicked();
    void on_pushButton_Add_clicked();
    void on_pushButton_Delete_clicked();
    void on_pushButton_On_clicked();
    void on_pushButton_Off_clicked();

private:
    Ui::Client *ui;
    QTcpSocket *client;
    int *bulb_count;
};
#endif // WIDGET_H
