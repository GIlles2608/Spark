#include "client.h"
#include <QSqlQuery>
client::client()
{
     cin =0;
     nom ="";
     prenom="";
     datedenaissance="";
     numtel = 0;
     sexe="";

}

client::client(int cin,QString nom,QString prenom,int numtel,QString ddn,QString sexe){
    this->cin=cin;
    this->nom=nom;
    this->prenom=prenom;
    this->numtel = numtel;
    this->datedenaissance = ddn;
    this->sexe = sexe;

}
bool client::ajouter(){
    QSqlQuery query;
    query.prepare("INSERT INTO client (cin,nom,prenom,tel,DATE_NAISSANCE,sexe)"
                "Values(:cin,:nom,:prenom,:numtel,:datedenaissance,:sexe)");
    query.bindValue(":cin",cin);
    query.bindValue(":nom",nom);
    query.bindValue(":prenom",prenom);
    query.bindValue(":numtel",numtel);
    query.bindValue(":datedenaissance",datedenaissance);
    query.bindValue(":sexe",sexe);
    return  query.exec();
}


bool client::supprimer(int cin)
{
     QString res=QString::number(cin);
    QSqlQuery query;
    query.prepare("Delete from client where cin=:cin ");
    query.bindValue(":cin",res);
    return query.exec();
}
bool client::modifier(int cin){
    QString res=QString::number(cin);
    QSqlQuery query;
    query.prepare("update client set nom=:nom,prenom=:prenom,tel=:numtel,DATE_NAISSANCE=:datedenaissance,sexe=:sexe "
                    "  where cin=:cin");
    query.bindValue(":cin",res);
    query.bindValue(":nom",nom);
    query.bindValue(":prenom",prenom);
    query.bindValue(":numtel",numtel);
    query.bindValue(":datedenaissance",datedenaissance);
    query.bindValue(":sexe",sexe);
   return  query.exec();
}

QSqlQueryModel * client::afficher()
{QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("SELECT * FROM client order by cin ");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("NAISSANCE"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("CONTACT"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("SEXE"));
    return model;
}
QSqlQueryModel * client::Tri(int index)
{QSqlQueryModel * model= new QSqlQueryModel();
    switch(index){
    case 0 :
        model->setQuery("SELECT * FROM client order by cin ");
    break;
    case 1:
        model->setQuery("SELECT * FROM client order by cin ");
    break;
    case 2:
        model->setQuery("SELECT * FROM client order by cin desc ");
    break;
    case 3:
        model->setQuery("SELECT * FROM client order by nom ");
    break;
    case 4:
        model->setQuery("SELECT * FROM client order by nom desc ");
    break;
    case 5:
        model->setQuery("SELECT * FROM client order by prenom ");
        break;
    case 6:
        model->setQuery("SELECT * FROM client order by prenom desc ");
        break;
    case 7:
        model->setQuery("SELECT * FROM client order by tel ");
        break;
    case 8:
        model->setQuery("SELECT * FROM client order by tel desc ");
        break;
    case 9:
        model->setQuery("SELECT * FROM client order by sexe ");
        break;
    case 10:
        model->setQuery("SELECT * FROM client order by sexe desc ");
        break;


    }

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("NAISSANCE"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("CONTACT"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("SEXE"));
    return model;
}
QSqlQueryModel * client::afficherRech(QString res)
{
    QSqlQueryModel *model=new QSqlQueryModel();

    model->setQuery("select * from client where cin like'"+res+"%' or nom like'"+res+"%' or prenom like'"+res+"%' or tel like'"+res+"%'");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("NAISSANCE"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("TELEPHONE"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("SEXE"));
    return model;
}
QSqlQueryModel * client::afficher_2()
{QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("SELECT * FROM client order by cin ");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("F-NAME"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("L-NAME"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("B-DAY"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("CONTACT"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("GENDER"));
    return model;
}
QSqlQueryModel * client::Tri_2(int index)
{QSqlQueryModel * model= new QSqlQueryModel();
    switch(index){
    case 0 :
        model->setQuery("SELECT * FROM client order by cin ");
        break;
    case 1:
        model->setQuery("SELECT * FROM client order by cin ");
        break;
    case 2:
        model->setQuery("SELECT * FROM client order by cin desc ");
        break;
    case 3:
        model->setQuery("SELECT * FROM client order by nom ");
        break;
    case 4:
        model->setQuery("SELECT * FROM client order by nom desc ");
        break;
    case 5:
        model->setQuery("SELECT * FROM client order by prenom ");
        break;
    case 6:
        model->setQuery("SELECT * FROM client order by prenom desc ");
        break;
    case 7:
        model->setQuery("SELECT * FROM client order by tel ");
        break;
    case 8:
        model->setQuery("SELECT * FROM client order by tel desc ");
        break;
    case 9:
        model->setQuery("SELECT * FROM client order by sexe ");
        break;
    case 10:
        model->setQuery("SELECT * FROM client order by sexe desc ");
        break;


    }

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("F-NAME"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("L-NAME"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("B-DAY"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("CONTACT"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("GENDER"));
    return model;
}
QSqlQueryModel * client::afficherRech_2(QString res)
{
    QSqlQueryModel *model=new QSqlQueryModel();

    model->setQuery("select * from client where cin like'"+res+"%' or nom like'"+res+"%' or prenom like'"+res+"%' or tel like'"+res+"%'");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("F-NAME"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("L-NAME"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("B-DAY"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("CONTACT"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("GENDER"));
    return model;
}
