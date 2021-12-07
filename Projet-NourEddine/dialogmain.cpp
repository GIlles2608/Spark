#include "dialogmain.h"
#include "ui_dialogmain.h"
#include "dialogadmin.h"
#include "dialoguser.h"
Dialogmain::Dialogmain(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialogmain)
{
    ui->setupUi(this);
}

Dialogmain::~Dialogmain()
{
    delete ui;
}

void Dialogmain::on_openAdmin_clicked()
{
    Dialogadmin d;
    d.exec();
}

void Dialogmain::on_openClient_clicked()
{
    Dialoguser d;
    d.exec();
}
