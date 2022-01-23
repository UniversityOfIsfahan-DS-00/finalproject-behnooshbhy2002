#include "header.h"
QMap< QString , person_info > source_map;
QMap< QString , QVector<QString> > connections;
QMap< QString , int > level;
QMap< QString , int > fri_score;
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
int final_scores(person_info user , person_info friend_user , int degree)
{
    int score = 0 ;


    //University Location
      if(user.UniLocation == friend_user.UniLocation)
      {
          score+=1;
          QString user_birth = user.birth.left(4);
          QString friend_birth = friend_user.birth.left(4);
          int dif = user_birth.toInt() - friend_birth.toInt();
          if(dif<=1 && dif>=-1)
              score+=1;
      }
    //field
      if(user.field == friend_user.field)
          score+=3;
    //work place
      if(user.workplace == friend_user.workplace)
          score+=2;
    //specialites
      for(int i = 0 ; i < user.specialties.size(); i++)
      {
          for(int j = 0; j<friend_user.specialties.size(); j++)
          {
              if(user.specialties[i]==friend_user.specialties[j])
                  score+=3;
          }
      }
     //Degree
      degree = 6 - degree;
      score+=degree;

    return score;
}
void suggestions(QString id)
{
    QVector <person_score> vec;
    person_score p;
    QMap< QString , int >::const_iterator e = level.constBegin();
    while(e != level.constEnd())
    {
       int score = final_scores( source_map.value(id) , source_map.value(e.key()), e.value());
        p.user=source_map.value(e.key());
        p.score = score;
        vec.push_back(p);
        ++e;
    }
    sort(vec.begin() , vec.end() , less_than_key());

    print(vec , id);

    vec.clear();
}

void print(QVector <person_score> vec , QString id)
{
    cout<<"\nrecommendation For "<<source_map.value(id).name.toStdString()<<" are "<<endl;
    cout<<"number\tID\tName\n";
    for(int y=0; y<vec.size(); y++)
    {
        cout<<y+1<<"\t|"<<vec[y].user.id.toStdString()<<"\t| "<<vec[y].user.name.toStdString()<<endl;

        if(y==19)
              break;
    }
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
void clear()
{
    level.clear();
    fri_score.clear();
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
                suggestions(id);
                clear();
                cout<<endl;

              }

              else if(num==2)
                  exit(0);

        }

    QCoreApplication a(argc, argv);
    return a.exec();
}
