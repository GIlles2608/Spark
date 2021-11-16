#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "animal.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_an_add_selected_clicked();

    void on_add_cancel_animal_clicked();

    void on_an_addBtn_clicked();
    void refresh();

    void on_tabAnimal_activated(const QModelIndex &index);

    void on_an_delete_clicked();

    void on_an_edit_clicked();

    void on_an_recherche_textChanged(const QString &arg1);

    void on_an_imprimer_clicked();

    void on_an_statTable_activated(const QModelIndex &index);

    void on_an_tri_asc_clicked();

    void on_an_tri_desc_clicked();

private:
    Ui::MainWindow *ui;
    animal an;
};
#endif // MAINWINDOW_H
