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
class person_score
{
  public :
     person_info user;
     int score;

};
class less_than_key
{
    public:
    inline bool operator() (const person_score& u1, const person_score& u2)
    {
        return (u1.score >= u2.score);
    }
};
void print(QVector <person_score> vec , QString id);
void suggestions(QString id);
int final_scores(person_info user , person_info friend_user , int degree);
void BSF(QString person_id, int maxDegree );
void clear();
#endif // HEADER_H{


