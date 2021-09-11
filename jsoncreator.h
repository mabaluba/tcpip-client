#ifndef JSONCREATOR_H
#define JSONCREATOR_H
#include <QByteArray>
#include <QJsonObject>
#include <QJsonDocument>

class JsonCreator
{
public:
    explicit JsonCreator();
    ~JsonCreator();
    QByteArray CreateJson(int, const QString&);
};

#endif // JSONCREATOR_H
