#include "personnel.h"


Personnel::Personnel()
{
    this->nom = " ";
    this->prenom = " ";
    this->cin = 0;
    this->date_naissance = QDate();
    this->ville = " ";
    this->adresse = " ";
    this->age = 0;
    this->tel = 0;
    this->admin = false;
   // this->cin_admin = 0;
}

Personnel::Personnel(QString n,QString p,int c,QDate d,QString v,QString ad,int ag,int t)
{
    this->nom = n;
    this->prenom = p;
    this->cin = c;
    this->date_naissance = d;
    this->ville = v;
    this->adresse = ad;
    this->age = ag;
    this->tel = t;
  //  this->cin_admin = ca;
}

Personnel::Personnel(QString n,QString p,int c,QDate d,QString v,QString ad,int ag,int t,int ca)
{
    this->nom = n;
    this->prenom = p;
    this->cin = c;
    this->date_naissance = d;
    this->ville = v;
    this->adresse = ad;
    this->age = ag;
    this->tel = t;
    this->cin_admin = ca;
}

bool Personnel::ajouter()
{
 QSqlQuery query;
 QString res = QString::number(cin);
 QString ag_res = QString::number(age);
 QString t_res = QString::number(tel);
 //prepare() prend la requete en parametre pour la preparer a l'execution;

   query.prepare("insert into gs_personnels(nom,prenom,cin,date_naissance,age,ville,adresse,telephone)""values(:nom,:prenom,:cin,:date_naissance,:age,:ville,:adresse,:tel)");
 //creation des variable liees;
   query.bindValue(":cin",res);
   query.bindValue(":nom",nom);
   query.bindValue(":prenom",prenom);
   query.bindValue(":date_naissance",date_naissance);
   query.bindValue(":age",ag_res);
   query.bindValue(":ville",ville);
   query.bindValue(":adresse",adresse);
   query.bindValue(":tel",t_res);

   return query.exec(); //envoi la requete pour l'executer
}

bool Personnel::ajouter_Admin()
{
 QSqlQuery query;
 QString res = QString::number(cin);
 QString res_a = QString::number(cin_admin);
 QString ag_res = QString::number(age);
 QString t_res = QString::number(tel);
 //prepare() prend la requete en parametre pour la preparer a l'execution;

   query.prepare("insert into gs_personnels(nom,prenom,cin,date_naissance,age,ville,adresse,telephone,cin_admin)""values(:nom,:prenom,:cin,:date_naissance,:age,:ville,:adresse,:tel,:cin_admin)");
 //creation des variable liees;
   query.bindValue(":cin",res);
   query.bindValue(":nom",nom);
   query.bindValue(":prenom",prenom);
   query.bindValue(":date_naissance",date_naissance);
   query.bindValue(":age",ag_res);
   query.bindValue(":ville",ville);
   query.bindValue(":adresse",adresse);
   query.bindValue(":tel",t_res);
   query.bindValue(":cin_admin",res_a);

   return query.exec(); //envoi la requete pour l'executer
}

QSqlQueryModel *Personnel::afficher()
{
  QSqlQueryModel * model = new QSqlQueryModel();
   model->setQuery("select cin,nom,prenom,date_naissance,age,telephone,adresse,ville,cin_admin from gs_personnels");
   model->setHeaderData(0,Qt::Horizontal,QObject::tr("CIN"));
   model->setHeaderData(1,Qt::Horizontal,QObject::tr("Nom"));
   model->setHeaderData(2,Qt::Horizontal,QObject::tr("Prenom"));
   model->setHeaderData(3,Qt::Horizontal,QObject::tr("DateNaissance"));
   model->setHeaderData(4,Qt::Horizontal,QObject::tr("Age"));
   model->setHeaderData(5,Qt::Horizontal,QObject::tr("Telephone"));
   model->setHeaderData(6,Qt::Horizontal,QObject::tr("Adresse"));
   model->setHeaderData(7,Qt::Horizontal,QObject::tr("Ville"));
   model->setHeaderData(8,Qt::Horizontal,QObject::tr("CIN_ADMIN"));
   return model;
}

//QString nom,QString prenom,int cin,QDate date_naissance,int age,QString ville,QString adresse,int tel)
bool Personnel::modifier(int cin)
{
  QSqlQuery query;
  QString res = QString::number(cin);
  QString ag_res = QString::number(age);
  QString t_res = QString::number(tel);
  query.prepare("Update gs_personnels set nom=:nom,prenom=:prenom,date_naissance=:date_naissance,age=:age,ville=:ville,adresse=:adresse,telephone=:tel where cin=:cin");
  query.bindValue(":cin",res);
  query.bindValue(":nom",nom);
  query.bindValue(":prenom",prenom);
  query.bindValue(":date_naissance",date_naissance);
  query.bindValue(":age",ag_res);
  query.bindValue(":ville",ville);
  query.bindValue(":adresse",adresse);
  query.bindValue(":tel",t_res);


  return query.exec();
}

bool Personnel::modifier_Admin(int cin)
{
  QSqlQuery query;
  QString res = QString::number(cin);
  QString res_a = QString::number(cin_admin);
  QString ag_res = QString::number(age);
  QString t_res = QString::number(tel);
  query.prepare("Update gs_personnels set nom=:nom,prenom=:prenom,date_naissance=:date_naissance,age=:age,ville=:ville,adresse=:adresse,telephone=:tel,cin_admin=:cin_admin where cin=:cin");
  query.bindValue(":cin",res);
  query.bindValue(":nom",nom);
  query.bindValue(":prenom",prenom);
  query.bindValue(":date_naissance",date_naissance);
  query.bindValue(":age",ag_res);
  query.bindValue(":ville",ville);
  query.bindValue(":adresse",adresse);
  query.bindValue(":tel",t_res);
  query.bindValue(":cin_admin",res_a);

  return query.exec();
}

bool Personnel::supprimer(int)
{
    QSqlQuery query;
    QString res = QString::number(cin);
    query.prepare("Delete from gs_personnels where cin = :cin");
    query.bindValue(":cin",res);

    return  query.exec();
}


QSqlQueryModel *Personnel::rechercher(QString q)
{
    QString res= QString::number(cin);
    QSqlQueryModel *model=new QSqlQueryModel();
     model->setQuery("SELECT cin,nom,prenom,date_naissance,age,telephone,adresse,ville,cin_admin FROM gs_personnels  WHERE nom like '%"+q+"%' or cin like '%"+q+"%' or prenom like '%"+q+"%' or ville like '%"+q+"%' ");

     return model;
}


QSqlQueryModel *Personnel::Trie_Nom_A()
{
    QSqlQueryModel * model = new QSqlQueryModel();
     model->setQuery("select * from gs_personnels order by nom ASC,prenom ASC");

     return model;
}

QSqlQueryModel *Personnel::Trie_age_A()
{
    QSqlQueryModel * model = new QSqlQueryModel();
     model->setQuery("select * from gs_personnels order by age ASC,date_naissance ASC");

     return model;
}

QSqlQueryModel *Personnel::Trie_cin_A()
{
    QSqlQueryModel * model = new QSqlQueryModel();
     model->setQuery("select * from gs_personnels order by cin ASC");

     return model;
}


QSqlQueryModel *Personnel::Trie_Nom_D()
{
    QSqlQueryModel * model = new QSqlQueryModel();
     model->setQuery("select * from gs_personnels order by nom DESC,prenom DESC");

     return model;
}

QSqlQueryModel *Personnel::Trie_age_D()
{
    QSqlQueryModel * model = new QSqlQueryModel();
     model->setQuery("select * from gs_personnels order by age DESC,date_naissance DESC");

     return model;
}

QSqlQueryModel *Personnel::Trie_cin_D()
{
    QSqlQueryModel * model = new QSqlQueryModel();
     model->setQuery("select * from gs_personnels order by cin DESC");

     return model;
}

void Personnel::stat(QCustomPlot *customPlot)
{
    QSqlQuery query,query1;
    // set dark background gradient:
    QLinearGradient gradient(255, 255, 255, 400);
    gradient.setColorAt(0, QColor(90, 90, 90));
    gradient.setColorAt(0.38, QColor(105, 105, 105));
    gradient.setColorAt(1, QColor(70, 70, 70));
    customPlot->clearPlottables();
    customPlot->clearGraphs();
    customPlot->replot();

    customPlot->setBackground(QBrush(gradient));


    QCPBars *fossil = new QCPBars(customPlot->xAxis, customPlot->yAxis);

    fossil->setAntialiased(false);

    fossil->setStackingGap(1);
    // set names and colors:
    fossil->setName("statistique des ages du personnel");
    fossil->setPen(QPen(QColor(200, 200, 50).lighter(170)));
    fossil->setBrush(QColor(200, 200, 50));

    QVector<double> ticks;
    QVector<QString> labels;
    query.prepare("SELECT COUNT(DISTINCT cin) FROM gs_personnel where age between 15 and 25");
    query.exec();
    int un;
    while(query.next())
    {
        un=query.value(0).toInt();
        qDebug()<<un;
    }
    query.prepare("SELECT COUNT(DISTINCT cin) FROM EMPLOYE where age between 26 and 36");
    query.exec();
    int deux;
    while(query.next())
    {
        deux=query.value(0).toInt();
    }

    query.prepare("SELECT COUNT(DISTINCT cin) FROM EMPLOYE where capacite between 37 and 47");
    query.exec();
    int trois;
    while(query.next())
    {
        trois=query.value(0).toInt();
    }
    query.prepare("SELECT COUNT(DISTINCT cin) FROM EMPLOYE where capacite between 48 and 58");
    query.exec();
    int quatre;
    while(query.next())
    {
        quatre=query.value(0).toInt();
    }

    query.prepare("SELECT COUNT(DISTINCT cin) FROM EMPLOYE where capacite between 59 and 65");
    query.exec();
    int cinq;
    while(query.next())
    {
        cinq=query.value(0).toInt();
    }

/*void Produit::statistique(QVector<double>* ticks,QVector<QString> *labels)
{
    QSqlQuery q;
    int i=0;
    q.exec("select QUANTITE from produit");
    while (q.next())
    {
        QString identifiant = q.value(0).toString();
        i++;
        *ticks<<i;
        *labels <<identifiant;
    }
}*/



    ticks << 1 << 2 << 3 << 4 << 5;
    labels << "[15,25]" << "[26,36]" << "[37,47]" << "[48,58]" << "[58,65]" ;
    QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
    textTicker->addTicks(ticks, labels);
    customPlot->xAxis->setTicker(textTicker);
    customPlot->xAxis->setLabel("Age");
    customPlot->xAxis->setTickLabelRotation(60);
    customPlot->xAxis->setSubTicks(false);
    customPlot->xAxis->setTickLength(0, 4);
    customPlot->xAxis->setRange(0, 8);
    customPlot->xAxis->setBasePen(QPen(Qt::white));
    customPlot->xAxis->setTickPen(QPen(Qt::white));
    customPlot->xAxis->grid()->setVisible(true);
    customPlot->xAxis->grid()->setPen(QPen(QColor(255, 20, 0), 0, Qt::DotLine));
    customPlot->xAxis->setTickLabelColor(Qt::white);
    customPlot->xAxis->setLabelColor(Qt::white);

    // prepare y axis:
    customPlot->yAxis->setRange(0, 20);
    customPlot->yAxis->setPadding(5); // a bit more space to the left border
    customPlot->yAxis->setLabel("Nombre du Personnel ");
    customPlot->yAxis->setBasePen(QPen(Qt::white));
    customPlot->yAxis->setTickPen(QPen(Qt::white));
    customPlot->yAxis->setSubTickPen(QPen(Qt::white));
    customPlot->yAxis->grid()->setSubGridVisible(true);
    customPlot->yAxis->setTickLabelColor(Qt::white);
    customPlot->yAxis->setLabelColor(Qt::white);
    customPlot->yAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::SolidLine));
    customPlot->yAxis->grid()->setSubGridPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));

    // Add data:
    /*QVector<double> fossilData, nuclearData, regenData;
    fossilData  << un << deux << trois << quatre << cinq;
   // nuclearData << 0.08*10.5 << 0.12*5.5 << 0.12*5.5 << 0.40*5.8 << 0.09*5.2 << 0.00*4.2 << 0.07*11.2;
    regenData   << 0.06*10.5 << 0.05*5.5 << 0.04*5.5 << 0.06*5.8 << 0.02*5.2 << 0.07*4.2<< 0.25*11.2;
    fossil->setData(ticks, fossilData);
  //  nuclear->setData(ticks, nuclearData);
 //   regen->setData(ticks, regenData);*/


   QVector<double> PlaceData;
              QSqlQuery q1("select age from gs_personnels");
              while (q1.next()) {
                            int  nbr_fautee = q1.value(0).toInt();
                            PlaceData<< nbr_fautee;
                              }
              fossil->setData(ticks, PlaceData);

    // setup legend:
    customPlot->legend->setVisible(true);
    customPlot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop|Qt::AlignHCenter);
    customPlot->legend->setBrush(QColor(255, 255, 255, 100));
    customPlot->legend->setBorderPen(Qt::NoPen);
    QFont legendFont = QFont();
    legendFont.setPointSize(10);
    customPlot->legend->setFont(legendFont);
    customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);

}
