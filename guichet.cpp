#include "guichet.h"

guichet::guichet()
{

}
guichet::guichet(int id,QString nom,QString description,QString categorie){
    this->id=id;
    this->nom=nom;
    this->description=description;
    this->categorie=categorie;
}
int guichet::get_id(){return id;}
QString guichet::get_nom(){return nom;}
QString guichet::get_description(){return description;}
QString guichet::get_categorie(){return categorie;}

bool guichet::ajouter(){
    QSqlQuery q;
    q.prepare("insert into guichet values(:id,:nom,:description,:categorie)");
    q.bindValue(":id",id);
    q.bindValue(":nom",nom);
    q.bindValue(":description",description);
    q.bindValue(":categorie",categorie);
    return q.exec();
}
bool guichet::supprimer(int id)
{
    QSqlQuery q;
    QString res=QString::number(id);
    q.prepare("delete from guichet where id=:id");
    q.bindValue(":id",res);
    return q.exec();
}
bool guichet::modifier(int id)
{

    QSqlQuery q;
    q.prepare("update guichet set id=:id,nom=:nom,description=:description,categorie=:categorie where id=:id");
    q.bindValue(":id",id);
    q.bindValue(":nom",nom);
    q.bindValue(":description",description);
    q.bindValue(":categorie",categorie);

   return q.exec();


}
QSqlQueryModel * guichet::afficher()
{
    QSqlQueryModel *model=new QSqlQueryModel();
    model->setQuery("select * from guichet");

    return model;
}

QSqlQueryModel * guichet::affichercatId()
{
    QSqlQueryModel *model=new QSqlQueryModel();
    model->setQuery("select id from guichet");

    return model;
}
int guichet::nbr_aide(int id){
    QSqlQuery q;
    q.prepare("select sum(quantite) as total from ticket where guichet_id=:id");
    q.bindValue(":id",id);
    if(q.exec())
    {
       while(q.next()){
    int nbr = q.value(0).toInt();
    return nbr;
       }}
}

QSqlQueryModel * guichet::recherche(QString res)
{
    QSqlQueryModel *model=new QSqlQueryModel();
    model->setQuery("SELECT* FROM guichet where id like'"+res+"%' or nom like'"+res+"%' or description like'"+res+"%' or categorie like'"+res+"%' ");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("DESCRIPTION"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("CATEGORIE"));
    return model;
}
QSqlQueryModel * guichet::Tri(int index)
{
    QSqlQueryModel *model=new QSqlQueryModel();
    switch(index){
    case 0:
        model->setQuery("SELECT* FROM guichet order by id asc ");
        break;
    case 1:
        model->setQuery("SELECT* FROM guichet order by id asc ");
        break;
    case 2:
        model->setQuery("SELECT* FROM guichet order by id desc ");
        break;
    case 3:
        model->setQuery("SELECT* FROM guichet order by nom asc ");
        break;
    case 4:
        model->setQuery("SELECT* FROM guichet order by nom desc ");
        break;
    case 5:
        model->setQuery("SELECT* FROM guichet order by description asc ");
        break;
    case 6:
        model->setQuery("SELECT* FROM guichet order by description desc ");
        break;
    case 7:
        model->setQuery("SELECT* FROM guichet order by categorie asc ");
        break;
    case 8:
        model->setQuery("SELECT* FROM guichet order by categorie desc ");
        break;

    }
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("DESCRIPTION"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("CATEGORIE"));
    return model;
}
