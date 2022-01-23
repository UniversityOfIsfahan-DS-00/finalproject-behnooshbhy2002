#include "header.h"
QMap< QString , person_info > source_map;
QMap< QString , QVector<QString> > connections;
QMap< QString , int > level;
using namespace std;
void BSF(QString person_id, int maxDegree )
{

    QQueue <person_info> queue;
    person_info user = source_map.value(person_id);
    queue.enqueue(user);
    level.insert(user.id , 0);

        while(!queue.isEmpty())
        {

            person_info u = queue.dequeue();

            int degree = level.value(u.id);

            if(degree==maxDegree)
                 break;

             for (int s=0; s < connections.value(u.id).size(); s++) {
                 QString connect= connections.value(u.id).at(s);
                 person_info add = source_map.value(connect);
                  if(level.contains(connect))
                      continue;

                  level.insert(connect , degree + 1);
                  queue.enqueue(add);

             }


        }
        level.remove(user.id);

}
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
    while(1)
     {
         cout<<"1 ) Finding suggestions ";
         cout<<"\n2 ) Exit ";
         cout<<"\nInput : ";
         cin>>num;
         cin.ignore();
           if(num==1)
             {
                cout<<"Please Enter ID : ";
                string str;
                getline(cin, str);
                QString id(str.c_str());
                BSF(id , 5 );

              }

              else if(num==2)
                  break;

        }

    QCoreApplication a(argc, argv);
    return a.exec();
}
