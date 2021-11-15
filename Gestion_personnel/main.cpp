#include "mainwindow.h"
#include <QApplication>
#include <QMessageBox>
#include "connexion.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Connexion c;
       bool  test = c.createconnexion();
    MainWindow w;

      if(test)
      {
          w.show();
          QMessageBox::information(nullptr, QObject::tr("database is open"),
                      QObject::tr("connection successful.\n"
                                  "Click Cancel to exit."), QMessageBox::Cancel);
      }
      else
          QMessageBox::critical(nullptr,QObject::tr("database is open"),
          QObject::tr("Connection failed. \n"
                      "Click cancel to exit."),QMessageBox::Cancel);

    return a.exec();
}
