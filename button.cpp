#include "button.h"
#include "ui_widget.h"
#include "widget.h"

Button::Button(/*QWidget *parent) : QWidget(parent),*/ )
{
    //*bulbCount=*bulbCount+1;
    //str1 = "Лампочка№"+ QString::number(*bulb_count+1);
}

//int Button::getBulbCount()
//{
//    return bulbCount;
//}
//void Button::setBulbCount(int bulb)
//{
//    this->bulbCount=bulb+1;
//}


//void Button::AddButton()
//{
//    QString str1 = "Лампочка№"+ QString::number(getBulbCount()+1);
//    qDebug()<<str1;
//    Ui::Client *ui1= nullptr;
//    ui1->comboBox_Bulbs->addItem(str1);
//    //ui1->comboBox_Bulbs->addItem(str1);
//    //ui->comboBox_Bulbs->addItem(str1);
//    //ui->comboBox_Bulbs->setCurrentText(ui->comboBox_Bulbs->itemText(ui->comboBox_Bulbs->count()-1));
//    setBulbCount(bulbCount);
//}

Button::~Button(){}
