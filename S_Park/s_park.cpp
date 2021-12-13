#include "s_park.h"
#include "ui_s_park.h"

S_park::S_park(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::S_park)
{
    ui->setupUi(this);
    refresh();

    // Animaux
    QPieSeries *series = new QPieSeries();
       QSqlQuery q("select sexe,count(*) from animal group by sexe");


        while(q.next())
        {series->append(q.value(0).toString()+": "+q.value(1).toString(),q.value(1).toInt());}
       QChart *chart = new QChart();
       chart->addSeries(series);
       chart->setTitle("Statistiques");
       chart->setBackgroundBrush(Qt::transparent);
       QChartView *chartview = new QChartView(chart);
       chartview->setRenderHint(QPainter::Antialiasing);
       chartview->setParent(ui->horizontalFrame);
       chartview->resize(400,300);

       chart->setAnimationOptions(QChart::AllAnimations);
       chart->legend()->setVisible(true);
       chart->legend()->setAlignment(Qt::AlignRight);
       series->setLabelsVisible(true);
       /*int ret=a.connect_arduino();
             switch (ret) {
             case(0):qDebug()<<"arduino is available and connected to :"<<a.getarduino_port_name();
                 break;
             case(1):qDebug()<<"arduino is available but not connected to :"<<a.getarduino_port_name();
                 break;
             case(-1):qDebug()<<"arduino is not available";
             }
       QObject::connect(a.getserial(),SIGNAL(readyRead()),this,SLOT(update_label()));*/

     // guichet && ticket && achat
       // constructeur user interface ui -> setpUi(this dialog)

       // initialisation du programme
       // 1) remplissage des tableu guichet + ticket + achat
       ui->guichetList->setModel(g.afficher()); // / table guichetList va presenter le model guichet.afficher
       ui->ticketList_3->setModel(t.afficher()); // / table ticketList va presenter le model ticket.afficher
       ui->achatsList_3->setModel(a.afficher()); // table achatsList va presenter le model achat.afficher
       ui->ticketListFront->setModel(t.afficherParId(0));
       // 2) controle de saisie des lineEdits
       ui->g_categorie_edit->hide();
       ui->t_id_e_3->setValidator(new QIntValidator(0,9999999,this));
       ui->t_prix_e_3->setValidator(new QIntValidator(0,9999999,this));
       ui->t_quantite_e_3->setValidator(new QIntValidator(0,9999999,this));
       ui->g_id_add->setValidator(new QIntValidator(0,9999999,this)); // controle de saisie lineedit va accepter juste les nombre de 0 a 9999999
       ui->t_id_add_3->setValidator(new QIntValidator(0,9999999,this)); // controle de saisie
       ui->g_id_add->setValidator(new QIntValidator(0,9999999,this)); // controle de saisie
       ui->t_prix_add_3->setValidator(new QIntValidator(0,9999999,this)); // controle de saisie
       ui->t_quantite_add_3->setValidator(new QIntValidator(0,9999999,this)); // controle de saisie
       ui->g_nom_edit->setValidator(new QRegExpValidator( QRegExp("[A-Za-z ]*") , this ));// controle de saisie lineedit va accepter juste les lettres miniscules + majuscules
       ui->g_description_edit->setValidator(new QRegExpValidator( QRegExp("[A-Za-z ]*") , this ));
       ui->g_nom_add->setValidator(new QRegExpValidator( QRegExp("[A-Za-z ]*") , this ));
       // Remplissage du combobox guichet_id ( ajout du ticket au guichet X )
       ui->t_guichet_id_add_3->setModel(g.affichercatId());
       // Les lineEdit + buttons invisibles :
       hideElements();
       cin_hide();
       ui->tableView->setModel(P.afficher());
       ui->comboBox_supp->setModel(P.afficher());
       ui->comboBox_cin_modi->setModel(P.afficher());
       ui->cin->setValidator(new QIntValidator(0,9999999,this));

       ui->cin_A->setValidator(new QIntValidator(0,9999999,this));
       ui->telephone->setValidator(new QIntValidator(0,99999999,this));
       ui->telephone_2->setValidator(new QIntValidator(0,99999999,this));
       ui->nouveau_mot_de_passe->setEchoMode(QLineEdit::Password);
       ui->Nou_mot_de_passe_confirm->setEchoMode(QLineEdit::Password);
       ui->mot_de_passe_2->setEchoMode(QLineEdit::Password);


       initialisation_2(); // methode initialisation hide buttons + clear lineedits + hide lineedits + affichage des tableaux ENGLISH STYLE

       initialisation(); // methode initialisation hide buttons + clear lineedits + hide lineedits + affichage des tableaux

}

S_park::~S_park()
{
    delete ui;
}


/*-----------Navigaton ----------------------------*/

void S_park::on_employer_clicked()
{

  if(admin_active==false)
  {
      QMessageBox::warning(nullptr, QObject::tr("Error"),
                  QObject::tr("Aces refuser.\n" "Vous ne disposez pas des droit d'administrateur \n"
                              "Click Cancel to exit."), QMessageBox::Cancel);
  }
  else
     ui->stackedWidget_Park->setCurrentIndex(1);
}

void S_park::on_aniamaux_clicked()
{
   ui->stackedWidget_Park->setCurrentIndex(2);
}

void S_park::on_clients_clicked()
{
   ui->stackedWidget_Park->setCurrentIndex(3);
}

void S_park::on_Guichet_2_clicked()
{
    ui->stackedWidget_Park->setCurrentIndex(4);
}

void S_park::on_tickets_clicked()
{
    ui->stackedWidget_Park->setCurrentIndex(5);
}

void S_park::on_acahts_tickets_clicked()
{
    ui->stackedWidget_Park->setCurrentIndex(6);
}

void S_park::on_achats_clicked()
{
    ui->stackedWidget_Park->setCurrentIndex(7);
}


void S_park::on_approvisionement_clicked()
{
    ui->stackedWidget_Park->setCurrentIndex(8);
}



void S_park::on_pushButton_3_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(0);
}

void S_park::on_pushButton_8_clicked()
{
     ui->stackedWidget_2->setCurrentIndex(1);
}


/*--------------------------------------GESTION CLIENT------------------------------*/

/*void S_park::on_start_client_clicked()
{
     ui->clientStacked->setCurrentIndex(2);
}*/


/*----------------------------------------------------------------------------------------*/




/*--------------------------------------GESTION ANIMAUX------------------------------*/

void S_park::refresh(){



       // affichage table Animeaux
       ui->tabAnimal->setModel(an.afficher());

       // affichage statistiques dans tab stat
      // ui->an_statTable->setModel(an.afficherStat());

           //Controle saisie du formulaire ajout Animal :
       ui->an_id_add->setValidator(new QIntValidator(0,9999999,this));
       ui->an_nom_add->setValidator(new QRegExpValidator( QRegExp("[A-Za-z ]*") , this ));
       ui->an_classe_add->setValidator(new QRegExpValidator( QRegExp("[A-Za-z ]*") , this ));
       //Controle saisie du formulaire Modifier  Animal :
       ui->an_id_e->setValidator(new QIntValidator(0,9999999,this));
       ui->an_nom_e->setValidator(new QRegExpValidator( QRegExp("[A-Za-z ]*") , this ));
       ui->an_classe->setValidator(new QRegExpValidator( QRegExp("[A-Za-z ]*") , this ));
       // Controlse  saisie affichage du formulaire edit and delete
       ui->an_edit->hide();
       ui->an_delete->hide();
       ui->an_id_e->hide();
       ui->an_nom_e->hide();
       ui->an_classe->hide();
       ui->an_sexe_e->hide();
       ui->an_classe->clear();
       ui->an_nom_e->clear();
       ui->an_id_e->clear();

}






void S_park::on_an_addBtn_clicked()
{
    QString id = ui->an_id_add->text();
    QString nom  = ui->an_nom_add->text();
    QString classe = ui->an_classe_add->text();
    QDate test = QDate::currentDate();
    QString date_ajout = test.toString("yyyy/MM/dd");
    QString sexe = ui->an_sexe_add->currentText();
    if (id.toInt()<=0){
        QMessageBox::critical(nullptr, QObject::tr("Animal ajout"),
                                      QObject::tr("ID invalide! .\n"
                                                  "Click Ok to exit."), QMessageBox::Ok);

    }
    else if(nom.size()<=2){
        QMessageBox::critical(nullptr, QObject::tr("Animal ajout"),
                                      QObject::tr("Nom invalide! .\n"
                                                  "Click Ok to exit."), QMessageBox::Ok);
        }
    else if(classe.size()<=2) {
        QMessageBox::critical(nullptr, QObject::tr("Animal ajout"),
                                      QObject::tr("Classe invalide! .\n"
                                                  "Click Ok to exit."), QMessageBox::Ok);

    }
    else if(sexe=="SEXE"){
        QMessageBox::critical(nullptr, QObject::tr("Animal ajout"),
                                      QObject::tr("Choissir un Sexe! .\n"
                                                  "Click Ok to exit."), QMessageBox::Ok);

    }

    else{
    animal an(id,nom,classe,date_ajout,sexe);
    bool validation = an.ajouter();
    if (validation){
        refresh();
        QMessageBox::information(nullptr, QObject::tr("Animal ajout"),
                                      QObject::tr("Animal ajouté.\n"
                                                  "Click Ok to exit."), QMessageBox::Ok);

    }
    else{
        QMessageBox::critical(nullptr, QObject::tr("Animal ajout"),
                                      QObject::tr("ID est deja utiliser!! .\n"
                                                  "Click Ok to exit."), QMessageBox::Ok);

    }
    }
}

void S_park::on_tabAnimal_activated(const QModelIndex &index)
{
    ui->an_edit->show();
    ui->an_delete->show();
    ui->an_id_e->show();
    ui->an_id_e->setEnabled(0);
    ui->an_nom_e->show();
    ui->an_classe->show();
    ui->an_sexe_e->show();

    QString val=ui->tabAnimal->model()->data(index).toString();
        QSqlQuery qry;
        qry.prepare("Select nom,classe from animal where  id='"+val+"'");
        if(qry.exec())
        {
            while(qry.next())
                    {
                        ui->an_id_e->setText(val);
                        ui->an_nom_e->setText(qry.value(0).toString());
                        ui->an_classe->setText(qry.value(1).toString());
                    }
        }
}

void S_park::on_an_delete_clicked()
{
    QString ref = ui->an_id_e->text();
    bool test = an.supprimer(ref);
    if (test){
        refresh();
        QMessageBox::information(nullptr, QObject::tr("Animal Suppression"),
                                      QObject::tr("Animal supprimer!! .\n"
                                                  "Click Ok to exit."), QMessageBox::Ok);

    }
    else{
        refresh();
        QMessageBox::critical(nullptr, QObject::tr("Animal Suppression"),
                                      QObject::tr("Erreur ID!! .\n"
                                                  "Click Ok to exit."), QMessageBox::Ok);

    }
}

void S_park::on_an_edit_clicked()
{
    QString id = ui->an_id_e->text();
    QString nom  = ui->an_nom_e->text();
    QString classe = ui->an_classe->text();
    QDate test = QDate::currentDate();
    QString date_ajout = test.toString("yyyy/MM/dd");
    QString sexe = ui->an_sexe_e->currentText();
    if (id.toInt()<=0){
        QMessageBox::critical(nullptr, QObject::tr("Animal Modifier"),
                                      QObject::tr("ID invalide! .\n"
                                                  "Click Ok to exit."), QMessageBox::Ok);

    }
    else if(nom.size()<=2){
        QMessageBox::critical(nullptr, QObject::tr("Animal Modifier"),
                                      QObject::tr("Nom invalide! .\n"
                                                  "Click Ok to exit."), QMessageBox::Ok);
        }
    else if(classe.size()<=2) {
        QMessageBox::critical(nullptr, QObject::tr("Animal Modifier"),
                                      QObject::tr("Classe invalide! .\n"
                                                  "Click Ok to exit."), QMessageBox::Ok);

    }
    else if(sexe=="SEXE"){
        QMessageBox::critical(nullptr, QObject::tr("Animal Modifier"),
                                      QObject::tr("Choissir un Sexe! .\n"
                                                  "Click Ok to exit."), QMessageBox::Ok);

    }

    else{
    animal an(id,nom,classe,date_ajout,sexe);
    bool validation = an.modifier(id);
    if (validation){
        refresh();
        QMessageBox::information(nullptr, QObject::tr("Animal ajout"),
                                      QObject::tr("Animal ajouté.\n"
                                                  "Click Ok to exit."), QMessageBox::Ok);

    }
    else{
        QMessageBox::critical(nullptr, QObject::tr("Animal ajout"),
                                      QObject::tr("ID est deja utiliser!! .\n"
                                                  "Click Ok to exit."), QMessageBox::Ok);

    }
    }
}

void S_park::on_an_recherche_textChanged(const QString &arg1)
{
    if(arg1.size()<=0){
        refresh();
    }
    else{
        ui->tabAnimal->setModel(an.recherche(arg1));
     }
}

void S_park::on_an_imprimer_clicked()
{
    QString strStream;
                       QTextStream out(&strStream);

                        const int rowCount = ui->tabAnimal->model()->rowCount();
                        const int columnCount = ui->tabAnimal->model()->columnCount();
                       out <<  "<html>\n"
                       "<head>\n"
                                        "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                                        <<  QString("<title>%1</title>\n").arg("strTitle")
                                        <<  "</head>\n"
                                        "<body bgcolor=#ffffff link=#5000A0>\n"



                                        "<center> <H1>Liste des animaux</H1></br></br><table border=1 cellspacing=0 cellpadding=2>\n";

                                    // headers
                                    out << "<thead><tr bgcolor=#f0f0f0> <th>Numero</th>";
                                    out<<"<cellspacing=10 cellpadding=3>";
                                    for (int column = 0; column < columnCount; column++)
                                        if (!ui->tabAnimal->isColumnHidden(column))
                                            out << QString("<th>%1</th>").arg(ui->tabAnimal->model()->headerData(column, Qt::Horizontal).toString());
                                    out << "</tr></thead>\n";

                                    // data table
                                    for (int row = 0; row < rowCount; row++) {
                                        out << "<tr> <td bkcolor=0>" << row+1 <<"</td>";
                                        for (int column = 0; column < columnCount; column++) {
                                            if (!ui->tabAnimal->isColumnHidden(column)) {
                                                QString data = ui->tabAnimal->model()->data(ui->tabAnimal->model()->index(row, column)).toString().simplified();
                                                out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
                                            }
                                        }
                                        out << "</tr>\n";
                                    }
                                    out <<  "</table> </center>\n"
                                        "</body>\n"
                                        "</html>\n";

                              QString fileName = QFileDialog::getSaveFileName((QWidget* )0, "Sauvegarder en PDF", QString(), "*.pdf");
                                if (QFileInfo(fileName).suffix().isEmpty()) { fileName.append(".pdf"); }

                               QPrinter printer (QPrinter::PrinterResolution);
                                printer.setOutputFormat(QPrinter::PdfFormat);
                               printer.setPaperSize(QPrinter::A4);
                              printer.setOutputFileName(fileName);

                               QTextDocument doc;
                                doc.setHtml(strStream);
                                doc.setPageSize(printer.pageRect().size()); // This is necessary if you want to hide the page number
                                doc.print(&printer);

}

void S_park::on_an_statTable_activated(const QModelIndex &index)
{
    /*QString val=ui->an_statTable->model()->data(index).toString();
        QSqlQuery qry;
        qry.prepare("Select count(*) from animal where  sexe='"+val+"'");
        if(qry.exec())
        {
            while(qry.next())
                    {
                        ui->an_total->setText(qry.value(0).toString());
                        ui->an_sexe_stat->setText(val);

                    }
        }*/
}

void S_park::on_an_tri_asc_clicked()
{
    ui->tabAnimal->setModel(an.afficherTri(1));
}

void S_park::on_an_tri_desc_clicked()
{
    ui->tabAnimal->setModel(an.afficherTri(0));
    //ui->an_tri_asc->set

}


/*----------------------------------------------------------------------------------------*/





/*---------------------------------GESTION TICKET---------------------------------------------------*/

void S_park::on_g_add_clicked()
{
    int id = ui->g_id_add->text().toInt();
    QString nom = ui->g_nom_add->text();
    QString description = ui->g_description_add->toPlainText();
     QString categorie =ui->g_cat_combo->currentText();
    guichet s(id,nom,description,categorie);
    bool test = s.ajouter();
    if(test)
    {
        ui->ticketList_3->setModel(t.afficher());
        ui->t_guichet_id_add_3->setModel(g.affichercatId());
        ui->t_guichet_id_e_3->setModel(g.affichercatId());

        QMessageBox::information(nullptr, QObject::tr("GUICHET ADD "),
                                      QObject::tr("GUICHET ADDED SUCCESSFULLY.\n"), QMessageBox::Ok);
        ui->guichetList->setModel(g.afficher());
         ui->g_id_add->clear();
         ui->g_nom_add->clear();
        ui->g_description_add->clear();
        hideElements();


    }
    else{
        QMessageBox::information(nullptr, QObject::tr("GUICHET ADD "),
                                      QObject::tr("NOM ALREADY IN USE.\n"), QMessageBox::Ok);

        }

}

// selection d'un guichet pour modifer / supprimer
void S_park::on_guichetList_activated(const QModelIndex &index)
{
    QString val=ui->guichetList->model()->data(index).toString();
        QSqlQuery qry;
        qry.prepare("Select id,nom,description from guichet where  id='"+val+"'");
        if(qry.exec())
        {
            while(qry.next())
                    {
                        ui->g_id_edit->setText(qry.value(0).toString());
                        ui->g_nom_edit->setText(qry.value(1).toString());
                        ui->g_description_edit->setText(qry.value(2).toString());
                        ui->g_id_edit->show();
                        ui->t_guichet_id_e_3->setModel(g.affichercatId());
                        ui->g_id_edit->setEnabled(false);
                        ui->g_nom_edit->show();
                        ui->g_description_edit->show();
                        ui->edit_g->show();
                        ui->delete_g->show();
                        ui->g_categorie_edit->show();
                    }
        }
}
// modifier guichet

void S_park::on_edit_g_clicked()
{
    int id= ui->g_id_edit->text().toInt();
    QString nom = ui->g_nom_edit->text();
    QString description= ui->g_description_edit->text();
    QString cateogrie=ui->g_categorie_edit->currentText();
     bool test = false;
     if(cateogrie == "CATEGORIE"){
         QMessageBox::critical(nullptr, QObject::tr("GUICHET MODIFY"),
                                       QObject::tr("SELECT A CATEGORY !\n"), QMessageBox::Cancel);
     }
     else{


     guichet cp(id,nom,description,cateogrie);
    test = cp.modifier(id);
    if(test){
        ui->t_guichet_id_add_3->setModel(g.affichercatId()); // combobox  (guichet)  ajout ticket refresh
        hideElements();
        ui->guichetList->setModel(g.afficher());
        QMessageBox::information(nullptr, QObject::tr("GUICHET MODIFY"),
                                      QObject::tr("GUICHET MODIFIED SUCCESSFULY .\n"
                                                  "Click Ok to exit."), QMessageBox::Ok);

    }
    else{
        ui->guichetList->setModel(g.afficher());
        hideElements();

        QMessageBox::information(nullptr, QObject::tr("GUICHET MODIFY"),
                                      QObject::tr("ERROR !\n"), QMessageBox::Cancel);

    }
        }

}
// supp guichet + ( les ticket de cet guichet automatiquement )

void  S_park::on_delete_g_clicked()
{
    // suppression des guichet
    int id=ui->g_id_edit->text().toInt();

    bool test2=g.supprimer(id);
    if(test2){
        hideElements();
        //la constrainte foreign key (id_guichet dans ticket ) a un reglage on delete cascade si on sup un guichet leur ticket vont etres sup aussi
        ui->t_guichet_id_add_3->setModel(g.affichercatId());
        ui->guichetList->setModel(g.afficher());
        // refresh du table ticket list d'ils-ya des ticket supprimer after deleting the guichet
        ui->ticketList_3->setModel(t.afficher());
        QMessageBox::information(nullptr, QObject::tr("GUICHET DELETE"),
                                      QObject::tr("GUICHET DELETED SUCCESSFULY .\n" "Click Ok to exit."), QMessageBox::Ok);

    }
    else{
        ui->guichetList->setModel(g.afficher());
        hideElements();

        QMessageBox::information(nullptr, QObject::tr("GUICHET DELETE"),
                                      QObject::tr("ERROR !\n"), QMessageBox::Cancel);

    }
}
// //////////////////////////////////// menu /////////////////////////////////////
// menu page 1  gestion ticket

void S_park::on_t_add_3_clicked()
{
 // on va prendre les values saisies par l'utilisateur
    int id = ui->t_id_add_3->text().toInt();
    int guichet_id = ui->t_guichet_id_add_3->currentText().toInt();
    int prix = ui->t_prix_add_3->text().toInt();
    int quantite = ui->t_quantite_add_3->text().toInt();
 // creation d'un object avec ses valeurs
    ticket s(id,guichet_id,prix,quantite);
    // test ajout ticket s
    bool test =(s.ajouter());
    if(test)
    {
        // ticket ajouté
        QMessageBox::information(nullptr, QObject::tr("TICKET ADD "),
                                      QObject::tr("TICKET ADDED SUCCESSFULLY.\n"), QMessageBox::Ok);
        // refresh table + clear lineedits
        ui->ticketList_3->setModel(t.afficher());
        // back to ticket tableview
        //ui->user_management_stacked_2->setCurrentIndex(0);
         ui->t_id_add_3->clear();
         ui->t_prix_add_3->clear();
        ui->t_quantite_add_3->clear();


    }
    else{
        // ticket non ajouter
        QMessageBox::information(nullptr, QObject::tr("USER ADD "),
                                      QObject::tr("USERNAME OR EMAIL ARE ALREADY IN USE.\n"), QMessageBox::Ok);

}
}
// lorsque on double click sur un iD d'un ticket du tableau

void S_park::on_ticketList_activated(const QModelIndex &index)
{
    // val = id du ticket selectionée
    QString val=ui->ticketList_3->model()->data(index).toString();
        QSqlQuery qry;
        // recupérer les information de cet ticket du base de données
        qry.prepare("Select id,prix,quantite from ticket where  id='"+val+"'");
        if(qry.exec())
        {
            while(qry.next())
                    {

                        ui->t_id_e_3->setText(qry.value(0).toString());
                        ui->t_prix_e_3->setText(qry.value(1).toString());
                        ui->t_quantite_e_3->setText(qry.value(2).toString());
                        ui->t_id_e_3->show();
                        ui->t_id_e_3->setEnabled(false);
                        ui->t_quantite_e_3->show();
                        ui->t_prix_e_3->show();
                        ui->edit_g->show();
                        ui->delete_g->show();
                        ui->t_edit_3->show();
                        ui->t_delete_3->show();
                        ui->t_guichet_id_e_3->show();
                        ui->t_guichet_id_e_3->setModel(g.affichercatId());
                    }
        }
}

void S_park::on_t_edit_3_clicked()
{
    // on va prendre les values saisies par l'utilisateur
    int id= ui->t_id_e_3->text().toInt();
    int quantity= ui->t_quantite_e_3->text().toInt();
    int prix= ui->t_prix_e_3->text().toInt();
    // valeur du comobox ( choix du id categorie pour une ticket)
    int catID =ui->t_guichet_id_e_3->currentText().toInt();
     bool test = false;
     // creation d'un object du class ticket avec les valeurs saisie par l'user
     ticket cp(id,catID,prix,quantity);
     // test de modification du ticket qui a id = int id= ui->t_id_e->text().toInt();
    test = cp.modifier(id);
    if(test){
        //MOdification success
        // remplissage du table ticket aprees la modification ( refresh table)
        ui->ticketList_3->setModel(t.afficher());
        //  //Methode pour mettres des buttons , lineedits invisible dans des cas ...
        hideElements();
        QMessageBox::information(nullptr, QObject::tr("TICKET MODIFY"),
                                      QObject::tr("TICKET MODIFIED SUCCESSFULY .\n"
                                                  "Click Ok to exit."), QMessageBox::Ok);

    }
    else{
        //modification failed
        // refresh table ticketlist
        ui->ticketList_3->setModel(t.afficher());
          //Methode pour mettres des buttons , lineedits invisible dans des cas ...
        hideElements();
            //
        QMessageBox::critical(nullptr, QObject::tr("TICKET MODIFY"),
                                      QObject::tr("ERROR !\n"), QMessageBox::Cancel);

    }


}
void S_park::hideElements(){
    //Methode pour mettres des buttons , lineedits invisible dans des cas ...
    ui->g_id_edit->hide();
    ui->g_categorie_edit->hide();
    ui->g_nom_edit->hide();
    ui->g_description_edit->hide();
    ui->edit_g->hide();
    ui->delete_g->hide();
    ui->t_id_e_3->hide();
    ui->t_quantite_e_3->hide();
    ui->t_prix_e_3->hide();
    ui->edit_g->hide();
    ui->delete_g->hide();
    ui->t_edit_3->hide();
    ui->t_delete_3->hide();
    ui->t_guichet_id_e_3->hide();
    ui->t_id_achat->hide();
    ui->t_id_achat->setEnabled(false);
    ui->t_prix->hide();
    ui->t_quantite->hide();
    ui->t_quantite_achat->hide();
    ui->acheter_t->hide();
    ui->cancelBtn->hide();
    ui->a_id->hide();

}

void S_park::on_t_delete_3_clicked()
{
    int id = ui->t_id_e_3->text().toInt();
    bool test  = t.supprimer(id);
    if(test){
          //Methode pour mettres des buttons , lineedits invisible dans des cas ...
        hideElements();
        //refresh table ticketlist
        ui->ticketList_3->setModel(t.afficher());

        QMessageBox::information(nullptr, QObject::tr("TICKET Delete"),
                                      QObject::tr("TICKET deleted SUCCESSFULY .\n"
                                                  "Click Ok to exit."), QMessageBox::Ok);



    }
    else{
        //Methode pour mettres des buttons , lineedits invisible dans des cas ...
      hideElements();
      //refresh table ticketlist
        ui->ticketList_3->setModel(t.afficher());

        QMessageBox::critical(nullptr, QObject::tr("TICKET delete"),
                                      QObject::tr("ERROR .\n"
                                                  "Click Ok to exit."), QMessageBox::Ok);


    }
}

/*void S_park::on_stat_btn_clicked()
{
    dial = new statistiques();
    dial->start_stat();
    dial->exec();
}*/

void S_park::on_lineEdit_textChanged(const QString &arg1)
{
    ui->guichetList->setModel(g.recherche(arg1));
}

void S_park::on_t_recherche_textChanged(const QString &arg1)
{
    ui->ticketList_3->setModel(t.recherche(arg1));
}

void S_park::on_guichetPDF_clicked()
{
    QPdfWriter pdf("C:/Users/nourdine/Desktop/guichet.pdf");
                      QPainter painter(&pdf);
                     int i = 4000;
                          painter.setPen(Qt::blue);
                          painter.setFont(QFont("Arial", 30));
                          painter.drawText(2300,1200,"Liste Des guichet");
                          painter.setPen(Qt::black);
                          painter.setFont(QFont("Arial", 50));
                         // painter.drawText(1100,2000,afficheDC);
                          painter.drawRect(1500,200,7300,2600);
                          //painter.drawPixmap(QRect(7600,70,2000,2600),QPixmap("C:/Users/RH/Desktop/projecpp/image/logopdf.png"));
                          painter.drawRect(0,3000,9600,500);
                          painter.setFont(QFont("Arial", 9));
                          painter.drawText(300,3300,"ID");
                          painter.drawText(2300,3300,"NOM");
                          painter.drawText(4300,3300,"DESCRIPTION");
                          painter.drawText(6300,3300,"CATEGORIE");



                          QSqlQuery query;
                          query.prepare("select * from guichet");
                          query.exec();
                          while (query.next())
                          {
                              painter.drawText(300,i,query.value(0).toString());
                              painter.drawText(2300,i,query.value(1).toString());
                              painter.drawText(4300,i,query.value(2).toString());
                              painter.drawText(6300,i,query.value(3).toString());



                             i = i +500;
                          }
                          int reponse = QMessageBox::question(this, "CREATION PDF", "PDF SAVED OPEN PDF?", QMessageBox::Yes |  QMessageBox::No);
                              if (reponse == QMessageBox::Yes)
                              {
                                  QDesktopServices::openUrl(QUrl::fromLocalFile("C:/Users/nourdine/Desktop/guichet.pdf"));

                                  painter.end();
                              }
                              if (reponse == QMessageBox::No)
                              {
                                   painter.end();
                              }
}

void S_park::on_comboBox_currentIndexChanged(int index)
{
    ui->guichetList->setModel(g.Tri(index));
}

void S_park::on_pushButton_clicked()
{
    QPrinter printer;
    QPrintDialog dialog(&printer,this);
    dialog.setWindowTitle("Print Document");
    dialog.addEnabledOption(QAbstractPrintDialog::PrintSelection);
    if( dialog.exec() != QDialog::Accepted){
        return;
    }
}

// stat tickets

void S_park::start_stat()
{
QSqlQuery q1,q2,q3,q4;
qreal tot=0, c1=0,c2=0,c3=0;
q1.prepare("SELECT * FROM guichet");
q1.exec();
q2.prepare("SELECT * FROM guichet WHERE categorie='INDIVIDUEL'");
q2.exec();
q3.prepare("SELECT * FROM GUICHET WHERE categorie='COUPLE'");
q3.exec();
q4.prepare("SELECT * FROM GUICHET WHERE categorie='FAMILLE' ");
q4.exec();

while (q1.next()){tot++;}
while (q2.next()){c1++;}
while (q3.next()){c2++;}
while (q4.next()){c3++;}


c1=c1/tot;
c2=c2/tot;
c3=c3/tot;
// Assign names to the set of bars used
        QBarSet *set0 = new QBarSet("INDIVIDUELLE");
        QBarSet *set1 = new QBarSet("COUPLE");
        QBarSet *set2 = new QBarSet("FAMILLE");


        // Assign values for each bar
        *set0 << c1;
        *set1 << c2;
        *set2 << c3;
        // Add all sets of data to the chart as a whole
        // 1. Bar Chart
        QBarSeries *series = new QBarSeries();
        // 2. Stacked bar chart
        series->append(set0);
        series->append(set1);
        series->append(set2);
        // Used to define the bar chart to display, title
        // legend,
        QChart *chart = new QChart();
        // Add the chart
        chart->addSeries(series);
        // Adds categories to the axes
        QBarCategoryAxis *axis = new QBarCategoryAxis();
        // 1. Bar chart
        chart->setAxisX(axis, series);

        // Used to change the palette
        QPalette pal = qApp->palette();
        // Change the color around the chart widget and text
        pal.setColor(QPalette::Window, QRgb(0xffffff));
        pal.setColor(QPalette::WindowText, QRgb(0x404044));
        // Apply palette changes to the application
        qApp->setPalette(pal);

// Used to display the chart
chartView = new QChartView(chart,ui->stats);
chartView->setRenderHint(QPainter::Antialiasing);
chartView->setMinimumSize(400,400);

chartView->show();
}


/*----------------------------------------------------------------------------------------*/




/*--------------------------------------GESTION PERSONNEL------------------------------*/

void S_park::cin_hide()
{
    ui->cin_A->hide();
    ui->cin_A_2->hide();
    ui->label_Password->hide();
}

void S_park::on_pb_ajouter_clicked()
{
    int cin = ui->cin->text().toInt();
    int cin_A = ui->cin_A->text().toInt();
    QString nom = ui->nom->text();
    QString prenom = ui->prenom->text();
    QDate date_naissance = ui->date_naissance->date();
    int age = ui->age->text().toInt();
    QString ville = ui->ville->text();
    QString adresse = ui->adresse->text();
    int tel = ui->telephone->text().toInt();
    QDate d ;
    //d.currentDate().year(); date_naissance.year();

    if(P.getAdmin()==false)
    {
        Personnel P(nom,prenom,cin,date_naissance,ville,adresse,age,tel);

         bool test = P.ajouter();
        if(ui->nom->text().isEmpty()||ui->nom->text().isEmpty()||ui->cin->text().isEmpty()||age!=(d.currentDate().year()-date_naissance.year()))
        {
            QMessageBox::warning(nullptr, QObject::tr("Error"),
                        QObject::tr("Ajout non effectué.\n" "Entrer le nom,le prenom,la cin ou verifier la cohesion entre la date de naissance et l'age \n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
        }
        else if(admin_active==false)
        {
            QMessageBox::warning(nullptr, QObject::tr("Error"),
                        QObject::tr("Ajout non effectué.\n" "Vous ne disposez pas des droit pour cette ajout \n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
        }
       else if(test)
        {
            QMessageBox::information(nullptr, QObject::tr("ok"),
                        QObject::tr("Employé ajouter.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
        }
        else
            QMessageBox::critical(nullptr,QObject::tr("Not ok"),
            QObject::tr("Ajout non effectué. \n"
                        "Click cancel to exit."),QMessageBox::Cancel);
    }
    else
    {
        Personnel P(nom,prenom,cin,date_naissance,ville,adresse,age,tel,cin_A);

         bool test = P.ajouter_Admin();
        if(ui->nom->text().isEmpty()||ui->nom->text().isEmpty()||ui->cin->text().isEmpty()||age!=(d.currentDate().year()-date_naissance.year()))
        {
            QMessageBox::warning(nullptr, QObject::tr("Error"),
                        QObject::tr("Ajout non effectué.\n" "Entrer le nom,le prenom,la cin ou verifier la cohesion entre la date de naissance et l'age \n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
        }
        else if(admin_active==false)
        {
            QMessageBox::warning(nullptr, QObject::tr("Error"),
                        QObject::tr("Ajout non effectué.\n" "Vous ne disposez pas des droit pour cette ajout \n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
        }
       else if(test)
        {
            QMessageBox::information(nullptr, QObject::tr("ok"),
                        QObject::tr("administrateur ajouter.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
        }
        else
            QMessageBox::critical(nullptr,QObject::tr("Not ok"),
            QObject::tr("Ajout non effectué. \n"
                        "Click cancel to exit."),QMessageBox::Cancel);
    }


         ui->comboBox_supp->setModel(P.afficher());
         ui->comboBox_cin_modi->setModel(P.afficher());
         ui->tableView->setModel(P.afficher());

            ui->cin->clear();
            ui->cin_A->clear();
            ui->nom->clear();
            ui->prenom->clear();
            ui->date_naissance->clear();
            ui->age->clear();
            ui->ville->clear();
            ui->adresse->clear();
            ui->telephone->clear();

     cin_hide();
}

void S_park::on_Ajout_admin_clicked()
{
    P.setAdmin(true);
    ui->cin_A->show();
}

void S_park::on_Ajout_Employe_clicked()
{
    P.setAdmin(false);
    cin_hide();
}

void S_park::on_pushButton_7_clicked()
{
 P.setCin(ui->comboBox_supp->currentText().toInt());
  bool test = P.supprimer(P.getCin());

  if(test)
  {
      QMessageBox::information(nullptr, QObject::tr("ok"),
                  QObject::tr("Suppresion effectué.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);
      ui->comboBox_supp->setModel(P.afficher());
      ui->comboBox_cin_modi->setModel(P.afficher());
      ui->tableView->setModel(P.afficher());
  }
  else if(admin_active==false)
  {
      QMessageBox::warning(nullptr, QObject::tr("Error"),
                  QObject::tr("Suppression non effectué.\n" "Vous ne disposez pas des droit pour cette ajout \n"
                              "Click Cancel to exit."), QMessageBox::Cancel);
  }
  else
      QMessageBox::critical(nullptr,QObject::tr("Not ok"),
      QObject::tr("Suppresion non effectué. \n"
                  "Click cancel to exit."),QMessageBox::Cancel);

}

void S_park::on_Ajout_admin_2_clicked()
{

    P.setAdmin(true);
    ui->cin_A_2->show();
}

void S_park::on_Ajout_Employe_2_clicked()
{
    P.setAdmin(false);
    cin_hide();
}


void S_park::on_pb_modifier_clicked()
{
     P.setCin(ui->comboBox_cin_modi->currentText().toInt());
     ui->cin_A_2->text() = ui->comboBox_cin_modi->currentText().toInt();
     P.setAge(ui->age_2->text().toInt());
     QDate d;
     P.setNom(ui->nom_2->text());
     P.setPrenom(ui->prenom_2->text());
     P.setDate(ui->date_naissance_2->date());
     P.setVille(ui->ville_2->text());
     P.setAdresse(ui->adresse_2->text());
     P.setTel(ui->telephone_2->text().toInt());
     P.setCin_admin( ui->cin_A_2->text().toInt());

     if(P.getAdmin()==false)
     {
         bool test = P.modifier(P.getCin());
         if(P.getAge()!=(d.currentDate().year()-P.getDate().year()))
         {
             QMessageBox::warning(nullptr, QObject::tr("Error"),
                         QObject::tr("modification non effectué.\n" "verifier la cohesion entre la date de naissance et l'age \n"
                                     "Click Cancel to exit."), QMessageBox::Cancel);
         }
         else if(admin_active==false)
         {
             QMessageBox::warning(nullptr, QObject::tr("Error"),
                         QObject::tr("modification non effectué.\n" "Vous ne disposez pas des droit pour cette ajout \n"
                                     "Click Cancel to exit."), QMessageBox::Cancel);
         }
         else if(test)
        {
            QMessageBox::information(nullptr, QObject::tr("ok"),
                        QObject::tr("Modification effectué.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
            ui->comboBox_cin_modi->setModel(P.afficher());
            ui->comboBox_supp->setModel(P.afficher());
            ui->tableView->setModel(P.afficher());
        }
        else
            QMessageBox::critical(nullptr,QObject::tr("Not ok"),
            QObject::tr("Modification non effectué. \n"
                        "Click cancel to exit."),QMessageBox::Cancel);

     }
     else
     {
         bool test = P.modifier_Admin(P.getCin());

         if(P.getAge()!=(d.currentDate().year()-P.getDate().year()))
         {
             QMessageBox::warning(nullptr, QObject::tr("Error"),
                         QObject::tr("modification non effectué.\n" "verifier la cohesion entre la date de naissance et l'age \n"
                                     "Click Cancel to exit."), QMessageBox::Cancel);
         }
         else if(admin_active==false)
         {
             QMessageBox::warning(nullptr, QObject::tr("Error"),
                         QObject::tr("modification non effectué.\n" "Vous ne disposez pas des droit pour cette ajout \n"
                                     "Click Cancel to exit."), QMessageBox::Cancel);
         }
         else if(test)
        {
            QMessageBox::information(nullptr, QObject::tr("ok"),
                        QObject::tr("Modification effectué.\n" "Administrateur modifier"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
            ui->comboBox_cin_modi->setModel(P.afficher());
            ui->comboBox_supp->setModel(P.afficher());
            ui->tableView->setModel(P.afficher());
        }
        else
            QMessageBox::critical(nullptr,QObject::tr("Not ok"),
            QObject::tr("Modification non effectué. \n"
                        "Click cancel to exit."),QMessageBox::Cancel);
     }

     ui->cin_A_2->clear();
     ui->nom_2->clear();
     ui->prenom_2->clear();
     ui->age_2->clear();
     ui->ville_2->clear();
     ui->adresse_2->clear();
     ui->telephone_2->clear();
     cin_hide();

}

void S_park::on_tableView_activated(const QModelIndex &index)
{
    QString val=ui->ticketList_3->model()->data(index).toString();
        QSqlQuery qry;
        // recupérer les information de cet ticket du base de données
        qry.prepare("Select nom,prenom,date_naissance,age,ville,adresse,telephone from gs_personnels where cin ='"+val+"' ");
        if(qry.exec())
        {
            while(qry.next())
                    {
                        ui->comboBox_cin_modi->setCurrentText(val);
                        ui->nom_2->setText(qry.value(0).toString());
                        ui->prenom_2->setText(qry.value(1).toString());
                        ui->date_naissance_2->setDate(qry.value(2).toDate());
                        ui->age_2->setValue(qry.value(3).toInt());
                        ui->ville_2->setText(qry.value(4).toString());
                        ui->adresse_2->setText(qry.value(5).toString());
                        ui->telephone_2->setText(qry.value(6).toString());
                    }
        }
}

void S_park::on_comboBox_cin_modi_activated(const QString &arg1)
{
    QSqlQuery dry;
    QString val=arg1;

    dry.prepare("SELECT nom,prenom,date_naissance,age,ville,adresse,telephone FROM gs_personnels  WHERE cin='"+val+"'" );
    if(dry.exec())
    {
        while(dry.next())
                {
            ui->nom_2->setText(dry.value(0).toString());
            ui->prenom_2->setText(dry.value(1).toString());
            ui->date_naissance_2->setDate(dry.value(2).toDate());
            ui->age_2->setValue(dry.value(3).toInt());
            ui->ville_2->setText(dry.value(4).toString());
            ui->adresse_2->setText(dry.value(5).toString());
            ui->telephone_2->setText(dry.value(6).toString());
                }
    }
}

void S_park::on_tri_ageh_clicked()
{
    ui->tableView->setModel(P.Trie_age_A());
}

void S_park::on_tri_ageb_clicked()
{
    ui->tableView->setModel(P.Trie_age_D());
}

void S_park::on_tri_nomh_clicked()
{
     ui->tableView->setModel(P.Trie_Nom_A());
}

void S_park::on_tri_nomb_clicked()
{
     ui->tableView->setModel(P.Trie_Nom_D());
}

void S_park::on_tri_cinh_clicked()
{
 ui->tableView->setModel(P.Trie_cin_A());
}

void S_park::on_tri_cinb_clicked()
{
 ui->tableView->setModel(P.Trie_cin_D());
}




void S_park::on_nom_recherche_textChanged(const QString &arg1)
{
    QString ch = arg1;

        ui->tableView_2->setModel(P.rechercher(ch));


}


//statistique
void S_park::on_Statistique_clicked()
{
    ui->Gestion->setCurrentIndex(3);

        P.stat(ui->widget);
}

// mailing

/*void  MainWindow::browse()
{
    files.clear();

    QFileDialog dialog(this);
    dialog.setDirectory(QDir::homePath());
    dialog.setFileMode(QFileDialog::ExistingFiles);

    if (dialog.exec())
        files = dialog.selectedFiles();

    QString fileListString;
    foreach(QString file, files)
        fileListString.append( "\"" + QFileInfo(file).fileName() + "\" " );

    ui->file->setText( fileListString );*/

void S_park::on_browse_clicked()
{
    files.clear();

    QFileDialog dialog(this);
    dialog.setDirectory(QDir::homePath());
    dialog.setFileMode(QFileDialog::ExistingFiles);

    if (dialog.exec())
        files = dialog.selectedFiles();

    QString fileListString;
    foreach(QString file, files)
        fileListString.append( "\"" + QFileInfo(file).fileName() + "\" " );

    ui->file->setText( fileListString );
}

void S_park::on_Envoyer_Mail_clicked()
{
    Smtp* smtp = new Smtp(ui->e_mail->text(),ui->password->text(), "smtp.gmail.com");
    connect(smtp, SIGNAL(status(QString)), this, SLOT(Mail_Envoyer(QString)));

    if( !files.isEmpty() )
        smtp->sendMail(ui->e_mail->text() , ui->recipient->text() , ui->subject->text(),ui->message->toPlainText(), files );
    else
        smtp->sendMail(ui->e_mail->text() , ui->recipient->text() , ui->subject->text(),ui->message->toPlainText());
}

void S_park::Mail_Envoyer(QString status)
{
    if(status == "Message sent")
        QMessageBox::warning( nullptr, tr( "Qt Simple SMTP client" ), tr( "Message sent!\n\n" ) );
    ui->e_mail->clear();
    ui->recipient->clear();
    ui->password->clear();
    ui->message->clear();
    ui->subject->clear();
    ui->file->clear();
}


/*----------------------------------------------------------------------------------------*/




/*--------------------------------------GESTION CLIENT------------------------------*/

void S_park::initialisation(){
    ui->tabClient_2->setModel(f.afficher_2());
    ui->c_sexe_modifier->hide();
     ui->tabClient->setModel(f.afficher());
     ui->c_cin->clear();
     ui->c_nom->clear();
     ui->c_prenom->clear();
     ui->c_tel->clear();
     ui->stackedWidget->setCurrentIndex(0);
     ui->c_cin_e->setEnabled(false);
     ui->c_nom_e->clear();
     ui->c_prenom_e->clear();
     ui->c_tel_e->clear();
     ui->c_cin_e->hide();
     ui->c_nom_e->hide();
     ui->c_prenom_e->hide();
     ui->c_tel_e->hide();
     ui->c_daten_e->hide();
     ui->c_modifier->hide();
     ui->c_supprimer->hide();
     ui->c_cin->setValidator(new QIntValidator(0,9999999,this)); // ID AJOUT CONTROLE SAISIE
     ui->c_nom->setValidator(new QRegExpValidator( QRegExp("[A-Za-z ]*") , this )); // NOM AJOUT CONTROLE SAISIE
     ui->c_nom_e->setValidator(new QRegExpValidator( QRegExp("[A-Za-z ]*") , this )); // NOM MODIFIER CONTROLE SIAISE
     ui->c_prenom_e->setValidator(new QRegExpValidator( QRegExp("[A-Za-z ]*") , this )); // NOM MODIFIER CONTROLE SIAISE
     ui->c_prenom->setValidator(new QRegExpValidator( QRegExp("[A-Za-z ]*") , this )); // NOM MODIFIER CONTROLE SIAISE
     ui->c_tel->setValidator(new QIntValidator(0,99999999,this)); // PRIX MODIFICATION CONTROLE SAISIE
     ui->c_tel_e->setValidator(new QIntValidator(0,99999999,this)); // PRIX AJOUT CONTROLE SAISIE

}
void S_park::initialisation_2(){
    ui->stackedWidget_3->setCurrentIndex(0);
    ui->tabClient->setModel(f.afficher());
    ui->c_sexe_modifier_2->hide();
    ui->tabClient_2->setModel(f.afficher_2());
    ui->c_cin_2->clear();
    ui->c_nom_2->clear();
    ui->c_prenom_2->clear();
    ui->c_tel_2->clear();
    ui->clientStacked->setCurrentIndex(1);
    ui->c_cin_e_2->setEnabled(false);
    ui->c_nom_e_2->clear();
    ui->c_prenom_e_2->clear();
    ui->c_tel_e_2->clear();
    ui->c_cin_e_2->hide();
    ui->c_nom_e_2->hide();
    ui->c_prenom_e_2->hide();
    ui->c_tel_e_2->hide();
    ui->c_daten_e_2->hide();
    ui->c_modifier_2->hide();
    ui->c_supprimer_2->hide();
    ui->c_cin_2->setValidator(new QIntValidator(0,9999999,this)); // ID AJOUT CONTROLE SAISIE
    ui->c_nom_2->setValidator(new QRegExpValidator( QRegExp("[A-Za-z ]*") , this )); // NOM AJOUT CONTROLE SAISIE
    ui->c_nom_e_2->setValidator(new QRegExpValidator( QRegExp("[A-Za-z ]*") , this )); // NOM MODIFIER CONTROLE SIAISE
    ui->c_prenom_e_2->setValidator(new QRegExpValidator( QRegExp("[A-Za-z ]*") , this )); // NOM MODIFIER CONTROLE SIAISE
    ui->c_prenom_2->setValidator(new QRegExpValidator( QRegExp("[A-Za-z ]*") , this )); // NOM MODIFIER CONTROLE SIAISE
    ui->c_tel_2->setValidator(new QIntValidator(0,99999999,this)); // PRIX MODIFICATION CONTROLE SAISIE
    ui->c_tel_e_2->setValidator(new QIntValidator(0,99999999,this)); // PRIX AJOUT CONTROLE SAISIE

}

void S_park::on_ajoutForm_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}


void S_park::on_c_ajouterBtn_clicked()
{
    int cin = ui->c_cin->text().toInt();
    QString nom = ui->c_nom->text();
    QString prenom = ui->c_prenom->text();
    int tel = ui->c_tel->text().toInt();
    QString daten = ui->c_date->date().toString("dd/MM/yyyy");
    QString telf = QString::number(tel);
    QString sexe=ui->c_sexe_ajout->currentText();
    if (cin<=0){
        QMessageBox::critical(nullptr, QObject::tr("Client ajout"),
                                      QObject::tr("Verifier le champ Cin!! .\n"
                                                  "Click Ok to exit."), QMessageBox::Ok);

    }
    else if(nom.size()<=2){
        QMessageBox::critical(nullptr, QObject::tr("Client ajout"),
                                      QObject::tr("Le nom doit etre plus que 2 characteres!! .\n"
                                                  "Click Ok to exit."), QMessageBox::Ok);

    }
    else if(prenom.size()<=2){
        QMessageBox::critical(nullptr, QObject::tr("Client ajout"),
                                      QObject::tr("Le prenom doit etre plus que 2 characteres!! .\n"
                                                  "Click Ok to exit."), QMessageBox::Ok);

    }
    else if(telf.size()<8 or telf.size()>8  ){
        QMessageBox::critical(nullptr, QObject::tr("Client ajout"),
                                      QObject::tr("Le num tel doit etre 8 chiffres .\n"
                                                  "Click Ok to exit."), QMessageBox::Ok);

    }
    else if(sexe=="SEXE"){
        QMessageBox::critical(nullptr, QObject::tr("Client Modification"),
                              QObject::tr("CHOISIR SEXE .\n"
                                          "Click Ok to exit."), QMessageBox::Ok);

    }
    else{
    client c(cin,nom,prenom,tel,daten,sexe);
    bool validation = c.ajouter();
    if (validation){
        initialisation();
        QMessageBox::information(nullptr, QObject::tr("Client ajout"),
                                      QObject::tr("Client ajouté !! .\n"
                                                  "Click Ok to exit."), QMessageBox::Ok);

    }
    else{
        QMessageBox::critical(nullptr, QObject::tr("Client ajout"),
                                      QObject::tr("CIN/TEL deja utiliser!! .\n"
                                                  "Click Ok to exit."), QMessageBox::Ok);

    }
    }
}

/*void S_park::on_pushButton_clicked()
{

}
*/
void S_park::on_c_recherche_textChanged(const QString &arg1)
{
    ui->tabClient->setModel(f.afficherRech(arg1));
}

void S_park::on_tableFournisseur_activated(const QModelIndex &index)
{

}

void S_park::on_c_modifier_clicked()
{
    int cin = ui->c_cin_e->text().toInt();
    QString nom = ui->c_nom_e->text();
    QString prenom = ui->c_prenom_e->text();
    int tel = ui->c_tel_e->text().toInt();
    QString daten = ui->c_daten_e->date().toString("dd/MM/yyyy");
    QString telf = QString::number(tel);
    QString sexe= ui->c_sexe_modifier->currentText();
    if (cin<=0){
        QMessageBox::critical(nullptr, QObject::tr("Client Modification"),
                                      QObject::tr("Verifier le champ Cin!! .\n"
                                                  "Click Ok to exit."), QMessageBox::Ok);

    }
    else if(nom.size()<=2){
        QMessageBox::critical(nullptr, QObject::tr("Client Modification"),
                                      QObject::tr("Le nom doit etre plus que 2 characteres!! .\n"
                                                  "Click Ok to exit."), QMessageBox::Ok);

    }
    else if(prenom.size()<=2){
        QMessageBox::critical(nullptr, QObject::tr("Client Modification"),
                                      QObject::tr("Le prenom doit etre plus que 2 characteres!! .\n"
                                                  "Click Ok to exit."), QMessageBox::Ok);

    }
    else if(telf.size()<8 or telf.size()>8  ){
        QMessageBox::critical(nullptr, QObject::tr("Client Modification"),
                                      QObject::tr("Le num tel doit etre 8 chiffres .\n"
                                                  "Click Ok to exit."), QMessageBox::Ok);

    }
    else if(sexe=="SEXE"){
        QMessageBox::critical(nullptr, QObject::tr("Client Modification"),
                              QObject::tr("CHOISIR SEXE .\n"
                                          "Click Ok to exit."), QMessageBox::Ok);

    }
    else{
    client c(cin,nom,prenom,tel,daten,sexe);
    bool validation = c.modifier(cin);
    if (validation){
        initialisation();
        QMessageBox::information(nullptr, QObject::tr("Client Modification"),
                                      QObject::tr("Fournisseur modifié !! .\n"
                                                  "Click Ok to exit."), QMessageBox::Ok);

    }
    else{
        QMessageBox::critical(nullptr, QObject::tr("Client Modification"),
                                      QObject::tr("TEL deja utiliser!! .\n"
                                                  "Click Ok to exit."), QMessageBox::Ok);

    }
    }
}

void S_park::on_c_supprimer_clicked()
{
    int id=ui->c_cin_e->text().toInt();

    bool test2=f.supprimer(id);
    if(test2){
        initialisation();
        QMessageBox::information(nullptr, QObject::tr("Client Supprimer"),
                                      QObject::tr("Succés .\n" "Click Ok to exit."), QMessageBox::Ok);

    }
    else{
        initialisation();
        QMessageBox::critical(nullptr, QObject::tr("Client Supprimer"),
                                      QObject::tr("ERROR !\n"), QMessageBox::Cancel);

    }
}

void S_park::on_tabClient_activated(const QModelIndex &index)
{
    QString val=ui->tabClient->model()->data(index).toString();
        QSqlQuery qry;
        qry.prepare("Select * from client where  cin='"+val+"'");
        if(qry.exec())
        {
            while(qry.next())
                    {
                        ui->c_cin_e->setText(val);
                        ui->c_nom_e->setText(qry.value(1).toString());
                        ui->c_prenom_e->setText(qry.value(2).toString());
                        ui->c_tel_e->setText(qry.value(4).toString());

                        ui->c_cin_e->setEnabled(false);
                        ui->c_nom_e->show();
                        ui->c_cin_e->show();
                        ui->c_prenom_e->show();
                        ui->c_tel_e->show();
                        ui->c_daten_e->show();
                        ui->c_modifier->show();
                        ui->c_supprimer->show();
                        ui->c_sexe_modifier->show();
                    }
        }
}

/*void S_park::on_pushButton_2_clicked()
{
    statistiques s;
    s.exec();
}*/

void S_park::on_comboTri_currentIndexChanged(int index)
{
    ui->tabClient->setModel(f.Tri(index));
}

void S_park::on_c_ajouterBtn_2_clicked()
{
    int cin = ui->c_cin_2->text().toInt();
    QString nom = ui->c_nom_2->text();
    QString prenom = ui->c_prenom_2->text();
    int tel = ui->c_tel_2->text().toInt();
    QString daten = ui->c_date_2->date().toString("dd/MM/yyyy");
    QString telf = QString::number(tel);
    QString gender="";
           int genderIndex =  ui->c_sexe_ajout_2->currentIndex();




    if (cin<=0){
        QMessageBox::critical(nullptr, QObject::tr("CLIENT ADD"),
                                      QObject::tr("INVLAID CIN ! .\n"
                                                  "Click Ok to exit."), QMessageBox::Ok);

    }
    else if(nom.size()<=2){
        QMessageBox::critical(nullptr, QObject::tr("CLIENT ADD"),
                                      QObject::tr("INVALID FIRST NAME! .\n"
                                                  "Click Ok to exit."), QMessageBox::Ok);

    }
    else if(prenom.size()<=2){
        QMessageBox::critical(nullptr, QObject::tr("CLIENT ADD"),
                                      QObject::tr("INVALID LAST NAME! .\n"
                                                  "Click Ok to exit."), QMessageBox::Ok);

    }
    else if(telf.size()<8 or telf.size()>8  ){
        QMessageBox::critical(nullptr, QObject::tr("CLIENT ADD"),
                                      QObject::tr("PHONE NUMBER MUST BE 8 CHARACTERS ! \n"
                                                  "Click Ok to exit."), QMessageBox::Ok);

    }



    else{
        if(genderIndex == 0) {
            QMessageBox::critical(nullptr, QObject::tr("CLIENT ADD"),
                                  QObject::tr("SELECT GENDER .\n"
                                              "Click Ok to exit."), QMessageBox::Ok);
        }
        else if (genderIndex != 0){
    switch (genderIndex){
    case 1 :
        gender ="FEMININ";
        break;
    case 2 :
        gender ="MASCULIN";
        break;
        }
    client c(cin,nom,prenom,tel,daten,gender);
    bool validation = c.ajouter();
    if (validation){
        initialisation_2();
        QMessageBox::information(nullptr, QObject::tr("CLIENT ADD"),
                                      QObject::tr("CLIENT ADDED !! .\n"
                                                  "Click Ok to exit."), QMessageBox::Ok);

    }
    else if(!validation){
        QMessageBox::critical(nullptr, QObject::tr("CLIENT ADD"),
                                      QObject::tr("CIN OR PHONE ALREADY IN USE ! \n"
                                                  "Click Ok to exit."), QMessageBox::Ok);

    }
    }
}
}

void S_park::on_Switch_2_English_clicked()
{
    ui->clientStacked->setCurrentIndex(1);
}

/*void S_park::on_pushButton_5_clicked()
{
    statistiques s;
    s.exec();
}*/

void S_park::on_comboTri_2_currentIndexChanged(int index)
{
    ui->tabClient_2->setModel(f.Tri_2(index));
}

void S_park::on_c_recherche_2_textChanged(const QString &arg1)
{
    ui->tabClient_2->setModel(f.afficherRech_2(arg1));

}

void S_park::on_c_modifier_2_clicked()
{
    int cin = ui->c_cin_e_2->text().toInt();
    QString nom = ui->c_nom_e_2->text();
    QString prenom = ui->c_prenom_e_2->text();
    int tel = ui->c_tel_e_2->text().toInt();
    QString daten = ui->c_daten_e_2->date().toString("dd/MM/yyyy");
    QString telf = QString::number(tel);
    QString gender="";
           int genderIndex =  ui->c_sexe_modifier_2->currentIndex();




           if (cin<=0){
               QMessageBox::critical(nullptr, QObject::tr("CLIENT MODIFY"),
                                             QObject::tr("INVLAID CIN ! .\n"
                                                         "Click Ok to exit."), QMessageBox::Ok);

           }
           else if(nom.size()<=2){
               QMessageBox::critical(nullptr, QObject::tr("CLIENT MODIFY"),
                                             QObject::tr("INVALID FIRST NAME! .\n"
                                                         "Click Ok to exit."), QMessageBox::Ok);

           }
           else if(prenom.size()<=2){
               QMessageBox::critical(nullptr, QObject::tr("CLIENT MODIFY"),
                                             QObject::tr("INVALID LAST NAME! .\n"
                                                         "Click Ok to exit."), QMessageBox::Ok);

           }
           else if(telf.size()<8 or telf.size()>8  ){
               QMessageBox::critical(nullptr, QObject::tr("CLIENT MODIFY"),
                                             QObject::tr("PHONE NUMBER MUST BE 8 CHARACTERS ! \n"
                                                         "Click Ok to exit."), QMessageBox::Ok);

           }





    else{
        if(genderIndex == 0) {
            QMessageBox::critical(nullptr, QObject::tr("CLIENT MODIFY"),
                                  QObject::tr("SELECT GENDER .\n"
                                              "Click Ok to exit."), QMessageBox::Ok);
        }
        else if (genderIndex != 0){
    switch (genderIndex){
    case 1 :
        gender ="FEMININ";
        break;
    case 2 :
        gender ="MASCULIN";
        break;
        }
    client c(cin,nom,prenom,tel,daten,gender);
    bool validation = c.modifier(cin);
    if (validation){
        initialisation_2();
        QMessageBox::information(nullptr, QObject::tr("CLIENT MODIFY"),
                                      QObject::tr("CLIENT MODIFIED !! .\n"
                                                  "Click Ok to exit."), QMessageBox::Ok);

    }
    else if(!validation){
        QMessageBox::critical(nullptr, QObject::tr("CLIENT MODIFY"),
                                      QObject::tr("PHONE ALREADY IN USE ! \n"
                                                  "Click Ok to exit."), QMessageBox::Ok);

    }
    }
}}

void S_park::on_tabClient_2_activated(const QModelIndex &index)
{
    QString val=ui->tabClient_2->model()->data(index).toString();
        QSqlQuery qry;
        qry.prepare("Select * from client where  cin='"+val+"'");
        if(qry.exec())
        {
            while(qry.next())
                    {
                        ui->c_cin_e_2->setText(val);
                        ui->c_nom_e_2->setText(qry.value(1).toString());
                        ui->c_prenom_e_2->setText(qry.value(2).toString());
                        ui->c_tel_e_2->setText(qry.value(4).toString());

                        ui->c_cin_e_2->setEnabled(false);
                        ui->c_nom_e_2->show();
                        ui->c_cin_e_2->show();
                        ui->c_prenom_e_2->show();
                        ui->c_tel_e_2->show();
                        ui->c_daten_e_2->show();
                        ui->c_modifier_2->show();
                        ui->c_supprimer_2->show();
                        ui->c_sexe_modifier_2->show();
                    }
        }
}

void S_park::on_c_supprimer_2_clicked()
{
    int id=ui->c_cin_e_2->text().toInt();

    bool test2=f.supprimer(id);
    if(test2){
        initialisation_2();
        QMessageBox::information(nullptr, QObject::tr("CLIENT DELETE"),
                                      QObject::tr("CLIENT DELETED SUCCESSFULLY .\n" "Click Ok to exit."), QMessageBox::Ok);

    }
    else{
        initialisation_2();
        QMessageBox::critical(nullptr, QObject::tr("CLIENT DELETE"),
                                      QObject::tr("INVALID CIN !\n"), QMessageBox::Cancel);

    }
}

void S_park::on_pushButton_6_clicked()
{
    ui->clientStacked->setCurrentIndex(0);
}

void S_park::on_ajoutForm_2_clicked()
{
    ui->stackedWidget_3->setCurrentIndex(1);
}















void S_park::on_Ok_modi_password_clicked()
{

   QString username = ui->nom_utilateur_2->text();
   l.setPassword(ui->nouveau_mot_de_passe->text());
   l.setUsername(username);
   QString a_password;
    QSqlQuery q;

     q.prepare("select password from gs_personnels where username = '"+username+"'");

      if(q.exec())
      {
          while(q.next())
          a_password = q.value(0).toString();
      }

      if(a_password != ui->mot_de_passe_2->text())
      {
          QMessageBox::critical(nullptr, QObject::tr("Failure"),
                      QObject::tr("le mot de passe est incorrect .\n"
                                  "Click Cancel to exit."), QMessageBox::Cancel);
      }
      else
      {
           bool test = l.modifier_Compte();
        if(ui->nouveau_mot_de_passe->text()!=ui->Nou_mot_de_passe_confirm->text())
      {
          ui->label_Password->show();
          ui->label_Password->setText("le mot de passe n'est pas identique");
      }
      else if(test)
      {
          QMessageBox::information(nullptr, QObject::tr("Sucess"),
                      QObject::tr("mot de passe changé .\n"
                                  "Click Cancel to exit."), QMessageBox::Cancel);

      }
      else
      {
          QMessageBox::critical(nullptr, QObject::tr("Failure"),
                      QObject::tr("l'utilsateur n'existe pas.\n"
                                  "Click Cancel to exit."), QMessageBox::Cancel);
      }

      }
      cin_hide();

}

void S_park::on_modifier_password_clicked()
{
    ui->stackedWidget_4->setCurrentIndex(1);
}

void S_park::on_Ok_modi_password_2_clicked()
{
    ui->stackedWidget_4->setCurrentIndex(0);
}


