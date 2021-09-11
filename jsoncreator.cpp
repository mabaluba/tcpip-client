#include "jsoncreator.h"

JsonCreator::JsonCreator(){}
JsonCreator::~JsonCreator(){}

QByteArray JsonCreator::CreateJson(int bulb_id, const QString &bulb_command)
{
    QJsonObject jsonObj;
    jsonObj["id"]=bulb_id;
    jsonObj["command"]=bulb_command;
    QJsonDocument jsonDoc(jsonObj);
    QString jsonData = jsonDoc.toJson( QJsonDocument::Compact );
    auto result = jsonData.toUtf8();
    return result;
}


