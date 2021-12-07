#include "dialogmain.h"
#include <QApplication>
#include "connexionsql.h"
#include <QDialog>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    connexionSQL c;
    bool verifConnexion = c.ouvrirConnexion();
    Dialogmain w;
    if(verifConnexion){
    w.show();
    QMessageBox::information (nullptr, QObject::tr("CONNEXION"),
                QObject::tr("\n DATABASE IS OPEN  !\n"), QMessageBox::Ok);
    }
    else {
        QMessageBox::critical (nullptr, QObject::tr("CONNEXION"),
                    QObject::tr("\n DATABASE IS NOT OPEN  !\n"), QMessageBox::Ok);
    }
    return a.exec();
}
