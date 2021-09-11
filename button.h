#ifndef BUTTON_H
#define BUTTON_H

#include <QWidget>
//#include"widget.h"


QT_BEGIN_NAMESPACE
namespace Ui { class Client; }
QT_END_NAMESPACE

class Button : public QWidget
{
    Q_OBJECT
public:
    explicit Button(/*QWidget *parent = nullptr*/);
    ~Button();

//signals:
//    void AddButton();
//    int getBulbCount();


private:
    //Ui::Client *ui;
    //int bulbCount=0;
    //QString str1;
    //void setBulbCount(int);
    QString name;
    Qstring

};

#endif // BUTTON_H
