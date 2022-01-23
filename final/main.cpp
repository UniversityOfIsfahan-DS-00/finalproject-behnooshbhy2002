#include "header.h"
QMap< QString , person_info > source_map;
QMap< QString , QVector<QString> > connections;
using namespace std;
void ParseClass::parseJsonFile()
{
    QFile file(QString::fromStdString("DATA.json"));
    if(!file.open(QIODevice::ReadOnly))
    {
        cout<<"fail to open the file";

    }

    QTextStream txs(&file);
    QByteArray array = file.readAll();
    QJsonDocument JsDoc = QJsonDocument::fromJson((array));
    QJsonArray arr = JsDoc.array();
    person_info info;

    foreach (const QJsonValue & value, arr) {
        QJsonObject object = value.toObject();
        info.id = object["id"].toString();
        info.name = object["name"].toString();
        info.birth = object["dateOfBirth"].toString();
        info.UniLocation = object["universityLocation"].toString();
        info.field = object["field"].toString();
        info.workplace = object["workplace"].toString();
        QJsonArray spec = object["specialties"].toArray();
          for(int i=0 ; i<spec.size(); i++)
          {
              info.specialties.append(spec[i].toString());
          }
        QJsonArray connect = object["connectionId"].toArray();
          for(int i=0 ; i<connect.size(); i++)
          {
              info.connectionId.append(connect[i].toString());
          }
          source_map.insert(object["id"].toString(),info);
          connections.insert(info.id , info.connectionId);
          info.specialties.clear();
          info.connectionId.clear();

     }

}
int main(int argc, char *argv[])
{
    int num;
    ParseClass obj;
    obj.parseJsonFile();

    QCoreApplication a(argc, argv);
    return a.exec();
}
