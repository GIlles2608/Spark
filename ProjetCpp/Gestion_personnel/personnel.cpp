#include "personnel.h"


Personnel::Personnel()
{
    this->nom = " ";
    this->prenom = " ";
    this->cin = 0;
   // this->date = " ";
    this->ville = " ";
    this->adresse = " ";
    this->age = 0;
}

Personnel::Personnel(QString n,QString p,int c,QString v,QString ad,int ag)
{
    this->nom = n;
    this->prenom = p;
    this->cin = c;
    //this->date = d;
    this->ville = v;
    this->adresse = ad;
    this->age = ag;
}


bool Personnel::ajouter()
{
 QSqlQuery query;
 QString res = QString::number(cin);
 QString ag_res = QString::number(age);
 //prepare() prend la requete en parametre pour la preparer a l'execution;

   query.prepare("insert into personnel(nom,prenom,cin,age,ville,adresse)""values(:nom,:prenom,:cin,:age,:ville,:adresse)");
 //creation des variable liees;
   query.bindValue(":cin",res);
   query.bindValue(":nom",nom);
   query.bindValue(":prenom",prenom);
  // query.bindValue(":date",date);
   query.bindValue(":age",ag_res);
   query.bindValue(":ville",ville);
   query.bindValue(":adresse",adresse);

   return query.exec(); //envoi la requete pour l'executer
}

QSqlQueryModel *Personnel::afficher()
{
  QSqlQueryModel * model = new QSqlQueryModel();
   model->setQuery("select * from personnel");
   model->setHeaderData(0,Qt::Horizontal,QObject::tr("CIN"));
   model->setHeaderData(1,Qt::Horizontal,QObject::tr("Nom"));
   model->setHeaderData(2,Qt::Horizontal,QObject::tr("Prenom"));
  // model->setHeaderData(3,Qt::Horizontal,QObject::tr("DateNaissance"));
   model->setHeaderData(4,Qt::Horizontal,QObject::tr("Age"));
   model->setHeaderData(5,Qt::Horizontal,QObject::tr("Ville"));
   model->setHeaderData(6,Qt::Horizontal,QObject::tr("Adresse"));

   return model;
}

/*bool modifier(int)
{

}*/

bool Personnel::supprimer(int)
{
    QSqlQuery query;
    QString res = QString::number(cin);
    query.prepare("Delete from personnel where CIN = :cin");
    query.bindValue(":cin",cin);

    return  query.exec();
}
