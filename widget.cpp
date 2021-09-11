#include "widget.h"
#include "ui_widget.h"
#include "jsoncreator.h"
#include "bulb.h"

WidgetClient::WidgetClient(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Client)
    , bulb_count(new int)
{
    ui->setupUi(this);
    client = new QTcpSocket(this);
    *bulb_count=0;
}

WidgetClient::~WidgetClient()
{
    delete ui;
}

void WidgetClient::on_pushButton_Connect_clicked()
{

    //client->connectToHost(QHostAddress("192.168.1.101"), 8080, QIODeviceBase::WriteOnly);

    client->connectToHost(QHostAddress(ui->lineEdit_IP->text()), ui->lineEdit_Port->text().toUShort(), QIODeviceBase::WriteOnly);// подключаемся к серверу по определеному адресу и порту в режиме только отсылки данных

    ui->comboBox_Bulbs->clear();//удалются все лампочки из списка при нажатии на кнопку Подключить
    *bulb_count=0;//обнуляется счетчик лампочек

    if(!client->waitForConnected())//если не можем соединиться с сервером в течение 3 секунд, закрываем сокет
    {
        ui->label_isConnected ->setText("Нет соединения");
        client->close();
    }
    else
    {
        connect(client,&QTcpSocket::connected,this,&WidgetClient::on_pushButton_Connect_clicked);
        ui->label_isConnected->setText("Соединение установлено");

        auto command = std::make_unique<JsonCreator>();//функция умного указателя вместо new
        auto sendClear =command->CreateJson(0,"clear");//создаем комманду clear в json формате, чтобы удалить все лампочки на сервере
        client->write(sendClear);//посылаем данные серверу
    }
}

void WidgetClient::on_pushButton_Add_clicked()
{
    if(!client->waitForConnected())//если не можем соединиться с сервером в течение 3 секунд, закрываем сокет и ничего не меняем на стороне клиента
    {
        ui->label_isConnected ->setText("Нет соединения");
        client->close();
    }
    else
    {
        auto newBulb = new Bulb(*bulb_count+1);//создаем экземпляр лампочки для добавления в конец списка и передаем в конструктор ее номер
        ui->comboBox_Bulbs->addItem(newBulb->getFullName());//добавляем название лампочки в список
        delete newBulb;//вызываем деструктор экземпляра объекта, если не используем умный указатель
        ui->comboBox_Bulbs->setCurrentText(ui->comboBox_Bulbs->itemText(ui->comboBox_Bulbs->count()-1));//помещаем название добавленной лампочки в заголовок списка

        auto command = std::make_unique<JsonCreator>();//функция умного указателя вместо new
            //отсылаем номер лампочки для добавления не текущий, а самый последний
        auto sendAdd =command->CreateJson(ui->comboBox_Bulbs->count()-1,"add");//записываем в json формат номер лампочки и комманду , которую к ней применить
        client->write(sendAdd);//посылаем данные серверу
        ++*bulb_count;//инкрементируем счетчик лампочек,чтобы после удаления любой лампочки добавлялись лампочки с новым следующим значением в конец
    }
}

void WidgetClient::on_pushButton_Delete_clicked()
{
    if(!client->waitForConnected())//если не можем соединиться с сервером в течение 3 секунд, закрываем сокет
    {
        ui->label_isConnected ->setText("Нет соединения");
        client->close();
    }
    else
    {
        //если лампочек нет, то никаких действий не происходит, отсылать сообщение на удаление не нужно,т.к. нечего удалять
        if(ui->comboBox_Bulbs->currentIndex()>=0)
        {
            auto command = std::make_unique<JsonCreator>();
            auto sendDelete =command->CreateJson(ui->comboBox_Bulbs->currentIndex(),"delete");
            client->write(sendDelete);
            ui->comboBox_Bulbs->removeItem(ui->comboBox_Bulbs->currentIndex());//удаляем запись о лампочке из выпадающего списка
        }
    }
}

void WidgetClient::on_pushButton_On_clicked()
{
    if(!client->waitForConnected())//если не можем соединиться с сервером в течение 3 секунд, закрываем сокет
    {
        ui->label_isConnected ->setText("Нет соединения");
        client->close();
    }
    else
    {
        if(ui->comboBox_Bulbs->currentIndex()>=0)
        {
            auto command = std::make_unique<JsonCreator>();
            auto sendOn =command->CreateJson(ui->comboBox_Bulbs->currentIndex(),"on");//отсылаем команду включить
            client->write(sendOn);
        }
    }
}

void WidgetClient::on_pushButton_Off_clicked()
{
    if(!client->waitForConnected())//если не можем соединиться с сервером в течение 3 секунд, закрываем сокет
    {
        ui->label_isConnected ->setText("Нет соединения");
        client->close();
    }
    else
    {
        if(ui->comboBox_Bulbs->currentIndex()>=0)
        {
            auto command = std::make_unique<JsonCreator>();
            auto sendOff =command->CreateJson(ui->comboBox_Bulbs->currentIndex(),"off");//выключить
            client->write(sendOff);
        }
    }
}
