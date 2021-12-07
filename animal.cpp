#include "animal.h"

animal::animal()
{
    id="";
    nom="";
    classe="";
    date_ajout="";
    sexe="";
}
animal::animal(QString id, QString nom,QString classe,QString date_ajout,QString sexe)
{
    this->id=id;
    this->nom=nom;
    this->classe=classe;
    this->date_ajout=date_ajout;
    this->sexe = sexe;

}

void animal::setId(QString id){this->id=id ;}
void animal::setNom(QString nom){this->nom=nom ;}
void animal::setClasse(QString classe){this->classe=classe ;}
void animal::setDateajout(QString date_ajout ){this->date_ajout=date_ajout ;}
void animal::setSexe(QString sexe ){this->sexe=sexe ;}


bool animal::ajouter()
{
    QSqlQuery query;
    query.prepare("INSERT INTO animal (id, nom, classe, date_ajout,sexe) "
                  "VALUES (:id, :nom, :classe, :date_ajout, :sexe)");
    query.bindValue(":id",id);
  query.bindValue(":nom",nom);
  query.bindValue(":classe",classe);
  query.bindValue(":date_ajout",date_ajout);
  query.bindValue(":sexe",sexe);
  return query.exec();

}
bool animal::supprimer(QString ref)
{
     QSqlQuery query;
     query.prepare(" Delete from animal where id =:ref");
     query.bindValue(0, ref);
     return query.exec();

}
QSqlQueryModel* animal::afficher()
{
     QSqlQueryModel* model=new QSqlQueryModel();
     model->setQuery("SELECT* FROM animal");
     model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
     model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
     model->setHeaderData(2, Qt::Horizontal, QObject::tr("CLASSE"));
     model->setHeaderData(3, Qt::Horizontal, QObject::tr("ADD DATE"));
     model->setHeaderData(4, Qt::Horizontal, QObject::tr("SEXE"));

     return model;
}


bool animal :: modifier(QString ref)
{
    QSqlQuery query;
  query.prepare("update ANIMAL set nom=:nom,classe=:classe,sexe=:sexe where id=:id ");
  query.bindValue(":id",ref);
  query.bindValue(":nom",nom);
  query.bindValue(":classe",classe);
  query.bindValue(":sexe",sexe);


  return query.exec();

}
QSqlQueryModel * animal::recherche(QString res)
{
    QSqlQueryModel *model=new QSqlQueryModel();
  model->setQuery("SELECT* FROM animal where classe like'"+res+"%' OR ID like'"+res+"%' or nom like'"+res+"%'");
     model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
     model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
     model->setHeaderData(2, Qt::Horizontal, QObject::tr("CLASSE"));
     model->setHeaderData(3, Qt::Horizontal, QObject::tr("DATE AJOUT"));
     model->setHeaderData(5, Qt::Horizontal, QObject::tr("SEXE"));
    return model;
}
QSqlQueryModel* animal::afficherTri(int choix)
{
    QSqlQueryModel* model=new QSqlQueryModel();
    if(choix==1){
    model->setQuery("SELECT * from animal order by classe");
    }
    else if(choix==0){
    model->setQuery("SELECT * from animal order by classe desc");
    }
    return model;
}
QSqlQueryModel* animal::afficherStat()
{

     QSqlQueryModel* model=new QSqlQueryModel();
     model->setQuery("SELECT sexe, count(*) FROM animal group by sexe");
     model->setHeaderData(0, Qt::Horizontal, QObject::tr("SEXE"));
     model->setHeaderData(1, Qt::Horizontal, QObject::tr("TOTAL"));

     return model;
}
