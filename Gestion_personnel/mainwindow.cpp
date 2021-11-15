#include <QMessageBox>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "personnels.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_pushButton_clicked()
{
  Personnels p;

   p.setModal(true);
   p.exec();
}
