#ifndef HEADER_H
#define HEADER_H

#include <QObject>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonArray>
#include <QJsonObject>
#include <QFile>
#include <QIODevice>
#include <QStringList>
#include <QDebug>
#include <QList>
#include <QMap>
#include <QQueue>
#include <QHash>
#include <QCoreApplication>
#include <iostream>
#include <algorithm>
using namespace std;
class ParseClass : public QObject
{
    Q_OBJECT
public:
    //explicit ParseClass(QObject *parent = nullptr);
    void clearJsonObject(QJsonObject &object);
    void createJsonFile(const QString &fileName);

    void parseJsonObjectV(QJsonObject &object);
    void parseJsonObjectI(QJsonObject &object);
    void parseJsonObject(QJsonArray::const_iterator iter);
    void parseJsonFile();
    void initList();
private:

signals:

public slots:
};
class person_info
{
   public :

     QString name;
     QString birth;
     QString id;
     QString UniLocation;
     QString field;
     QString workplace;
     QVector <QString> connectionId;
     QVector <QString> specialties;


};


#endif // HEADER_H{


