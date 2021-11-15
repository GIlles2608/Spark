#include "personnels.h"
#include "ui_personnels.h"
#include <QMessageBox>
#include "QIntValidator"

Personnels::Personnels(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Personnels)
{
    ui->setupUi(this);
      ui->tableView->setModel(P.afficher());
      ui->comboBox_supp->setModel(P.afficher());
      ui->comboBox_cin_modi->setModel(P.afficher());
      ui->cin->setValidator(new QIntValidator(0,9999999,this));
      ui->telephone->setValidator(new QIntValidator(0,99999999,this));
      ui->telephone_2->setValidator(new QIntValidator(0,99999999,this));
}

Personnels::~Personnels()
{
    delete ui;
}

void Personnels::on_pb_ajouter_clicked()
{
    int cin = ui->cin->text().toInt();
    QString nom = ui->nom->text();
    QString prenom = ui->prenom->text();
    QDate date_naissance = ui->date_naissance->date();
    int age = ui->age->text().toInt();
    QString ville = ui->ville->text();
    QString adresse = ui->adresse->text();
    int tel = ui->telephone->text().toInt();
    QDate d ;
    //d.currentDate().year(); date_naissance.year();

    Personnel P(nom,prenom,cin,date_naissance,ville,adresse,age,tel);

    if(ui->nom->text().isEmpty()||ui->nom->text().isEmpty()||ui->cin->text().isEmpty()||age!=(d.currentDate().year()-date_naissance.year()))
    {
        QMessageBox::warning(nullptr, QObject::tr("Error"),
                    QObject::tr("Ajout non effectué.\n" "Entrer le nom,le prenom,la cin ou verifier la cohesion entre la date de naissance et l'age \n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }
     bool test = P.ajouter();
   if(test)
    {
        QMessageBox::information(nullptr, QObject::tr("ok"),
                    QObject::tr("Ajout effectué.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
         ui->comboBox_supp->setModel(P.afficher());
         ui->comboBox_cin_modi->setModel(P.afficher());
         ui->tableView->setModel(P.afficher());
    }
    else
        QMessageBox::critical(nullptr,QObject::tr("Not ok"),
        QObject::tr("Ajout non effectué. \n"
                    "Click cancel to exit."),QMessageBox::Cancel);
}

void Personnels::on_pushButton_2_clicked()
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
  else
      QMessageBox::critical(nullptr,QObject::tr("Not ok"),
      QObject::tr("Suppresion non effectué. \n"
                  "Click cancel to exit."),QMessageBox::Cancel);

}



void Personnels::on_pb_modifier_clicked()
{
     P.setCin(ui->comboBox_cin_modi->currentText().toInt());
     QDate d;
     /* P.setNom(ui->nom_2->text());
     P.setPrenom(ui->prenom_2->text());*/
     P.setDate(ui->date_naissance_2->date());
     P.setAge(ui->age_2->text().toInt());
    /* P.setVille(ui->ville_2->text());
     P.setAdresse(ui->adresse_2->text());
     P.setTel(ui->telephone_2->text().toInt());*/

    //Personnel P(P.getNom(),P.getPrenom(),P.getCin(),P.getDate(),P.getAge(),P.getVille(),P.getAdresse(),P.getTel());

    //bool test = P.modifier(P.getNom(),P.getPrenom(),P.getCin(),P.getDate(),P.getAge(),P.getVille(),P.getAdresse(),P.getTel());

     bool test = P.modifier(P.getCin());
     if(P.getAge()!=(d.currentDate().year()-P.getDate().year()))
     {
         QMessageBox::warning(nullptr, QObject::tr("Error"),
                     QObject::tr("Ajout non effectué.\n" "verifier la cohesion entre la date de naissance et l'age \n"
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

void Personnels::on_tri_ageh_clicked()
{
    ui->tableView->setModel(P.Trie_age_A());
}

void Personnels::on_tri_ageb_clicked()
{
    ui->tableView->setModel(P.Trie_age_D());
}

void Personnels::on_tri_nomh_clicked()
{
     ui->tableView->setModel(P.Trie_Nom_A());
}

void Personnels::on_tri_nomb_clicked()
{
     ui->tableView->setModel(P.Trie_Nom_D());
}

/*void Personnels::on_nom_recherche_textEdited(const QString &arg1)
{

}*/

void Personnels::on_nom_recherche_textChanged(const QString &arg1)
{
    QString ch = arg1;

   /* if(ch == "")
    {
        ui->tableView_2->setModel(P.afficher());
    }
    else
    {*/
        ui->tableView_2->setModel(P.rechercher(ch));
    //}

}
