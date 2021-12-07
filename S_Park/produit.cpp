#include "produit.h"
#include <QString>
#include <QSqlQuery>
#include <QtDebug>
#include <QObject>

GS_ANIMAUX::GS_ANIMAUX()
{
ID_A=" ",NOM=" ",PRENOM=0,SEXE=" ",CLASSE=0;
}
GS_ANIMAUX::GS_ANIMAUX(QString ID_A,QString NOM ,int PRENOM,QString SEXE,int CLASSE)
{this->ID_A=ID_A ;this->NOM=NOM ;this->PRENOM=PRENOM ;this->SEXE=SEXE ; this->CLASSE=CLASSE;}

QString GS_ANIMAUX::getref(){return ID_A;}
 QString  GS_ANIMAUX::getintitule(){return NOM;}
 int  GS_ANIMAUX::getquantite(){return PRENOM;}
 QString  GS_ANIMAUX::getcategorie(){return SEXE;}
 int  GS_ANIMAUX::getprix(){return CLASSE;}
 void GS_ANIMAUX::setref(QString ID_A){this->ID_A=ID_A ;}
 void GS_ANIMAUX::setintitule(QString NOM){this->NOM=NOM ;}
 void GS_ANIMAUX::setquantite(int PRENOM){this->PRENOM=PRENOM ;}
 void GS_ANIMAUX::setcategorie(QString SEXE ){this->SEXE=SEXE ;}
 void GS_ANIMAUX::setprix(int CLASSE){ this->CLASSE=CLASSE;}
bool GS_ANIMAUX::ajouter()
{
    QSqlQuery query;
//QString ID_A_string= QString::ID_A;
         query.prepare("INSERT INTO PRODUIT (ID_A, NOM, PRENOM, SEXE,CLASSE) "
                       "VALUES (:ID_A, :NOM, :PRENOM, :SEXE, :CLASSE)");
         query.bindValue(":ID_A",ID_A);
         query.bindValue(":NOM", NOM);
         query.bindValue(":PRENOM", PRENOM);
         query.bindValue(":SEXE", SEXE);
         query.bindValue(":CLASSE", CLASSE);
         return query.exec();


}
bool GS_ANIMAUX::supprimer(QString ID_A)
{
    QSqlQuery query;
//QString ID_A_string= QString::ID_A;
         query.prepare(" Delete from GS_ANIMAUX where ID_A =:ID_A");
         query.bindValue(0, ID_A);

         return query.exec();

}
QSqlQueryModel* GS_ANIMAUX::afficher()
{
   QSqlQueryModel* model=new QSqlQueryModel();
         model->setQuery("SELECT* FROM GS_ANIAMUX");
         model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_A"));
         model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
         model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
         model->setHeaderData(3, Qt::Horizontal, QObject::tr("SEXE"));
          model->setHeaderData(3, Qt::Horizontal, QObject::tr("CLASSE"));
         return model;
}


bool GS_ANIMAUX :: modifier(QString ID_A)
{
     QSqlQuery query;



        //QString res= QString::getref;
        query.prepare("UPDATE GS_ANIMAUX SET ID_A=:ID_A,NOM=:NOM,PRENOM=:PRENOM ,SEXE=:SEXE ,CLASSE=:CLASSE WHERE ID_A=:ID_A");
        query.bindValue(":ID_A", ID_A);
        query.bindValue(":NOM", NOM);
        query.bindValue(":PRENOM", PRENOM);
        query.bindValue(":SEXE", SEXE);
        query.bindValue(":CLASSE", CLASSE);



           return    query.exec();

}
