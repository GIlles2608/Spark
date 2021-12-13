#include "mainwindow.h"
#include  "connexion.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Connexion c;

       bool  test = c.createconnexion();
    MainWindow w;

      if(test)
      {
          w.show();
      }
      else
          QMessageBox::critical(nullptr,QObject::tr("database is open"),
          QObject::tr("Connection failed. \n"
                      "Click cancel to exit."),QMessageBox::Cancel);
    return a.exec();
}
