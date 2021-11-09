#include <QMessageBox>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "personnel.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableView->setModel(P.afficher());
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pb_ajouter_clicked()
{
    int cin = ui->cin->text().toInt();
    QString nom = ui->nom->text();
    QString prenom = ui->prenom->text();
   // QString date = ui->date_naissance->text();
    int age = ui->age->text().toInt();
    QString ville = ui->ville->text();
    QString adresse = ui->nom->text();

    Personnel P(nom,prenom,cin,ville,adresse,age);

    bool test = P.ajouter();
    if(test)
    {
        ui->tableView->setModel(P.afficher());
        QMessageBox::information(nullptr, QObject::tr("ok"),
                    QObject::tr("Ajout effectué.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }
    else
        QMessageBox::critical(nullptr,QObject::tr("Not ok"),
        QObject::tr("Ajout non effectué. \n"
                    "Click cancel to exit."),QMessageBox::Cancel);
}

void MainWindow::on_pushButton_2_clicked()
{
  Personnel P;
  P.setCin(ui->cin->text().toInt());
  bool test = P.supprimer(P.getCin());

  if(test)
  {
         ui->tableView->setModel(P.afficher());
      QMessageBox::information(nullptr, QObject::tr("ok"),
                  QObject::tr("Suppresion effectué.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);
  }
  else
      QMessageBox::critical(nullptr,QObject::tr("Not ok"),
      QObject::tr("Suppresion non effectué. \n"
                  "Click cancel to exit."),QMessageBox::Cancel);

}
