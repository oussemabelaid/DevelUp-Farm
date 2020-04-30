#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "animaux.h"
#include "nourritures.h"
#include <QMessageBox>
#include <QCheckBox>
#include <QSpinBox>
#include <QSqlQuery>
#include <QDebug>
#include "vaccin.h"
#include "nermineV.h"




MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->table_animaux->setModel(tmp.afficher());
    ui->table_nourritures->setModel(tmpn.afficher());
    mysystem=new QSystemTrayIcon(this);
        mysystem->setIcon(QIcon(":/anim.ico"));
        mysystem->setVisible(true);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
  int id_animaux=ui->le_id->text().toInt();
  QString type=ui->le_type->currentText();
  QString sexe=ui->le_sexe->currentText();
  QDate datea=ui->la_date->date();
  //QString vaccin=ui->le_vaccin->currentText();
  int prix=ui->le_prix->text().toInt();
  animaux a(id_animaux, type, sexe, datea , prix);
  QMessageBox msg;
   bool test1=a.ajouter();
  if(a.ajouter())
  {

          if(test1)
        {

              ui->table_animaux->setModel(tmp.afficher());//refresh
               mysystem->showMessage(tr("notification"),tr("animal ajouté avec succes"));
              msg.setText("ajout avec succès");
              msg.exec();

        }
          else
          {
              msg.setText("echec d'ajout");
                    msg.exec();
      }



}

    }


void MainWindow::on_pushButton_supp_clicked()
{
animaux a;
       QItemSelectionModel *select = ui->table_animaux->selectionModel();
       QModelIndexList list;
       if(select->hasSelection())
       list=select->selectedRows();
       for(int i=0; i< list.count(); i++)
       {
           a.supprimer(list[i].data().toInt());
       }
  ui->table_animaux->setModel(a.afficher());

   mysystem->showMessage(tr("notification"),tr("animal supprimé avec succes"));

}

void MainWindow::on_pushButton_5_clicked()
{



    int id_animaux= ui->le_id->text().toInt();
          QString type= ui->le_type->currentText();
           QString sexe= ui->le_sexe->currentText();
          QDate datea= ui->la_date->date();
         int prix= ui->le_prix->text().toInt();


         animaux a(id_animaux, type, sexe, datea , prix);
        bool test=a.modifier(id_animaux);
  QMessageBox msg;
        if(test)
      {

            ui->table_animaux->setModel(tmp.afficher());//refresh

            msg.setText("animal modifié");
            msg.exec();

      }
        else
            QMessageBox::critical(nullptr, QObject::tr("modif dun animal"),
                        QObject::tr("Erreur !.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);





}
void MainWindow::on_pushButton_9_clicked()
{
    nermineV nermineV;
    nermineV.setWindowTitle(true);
    nermineV.exec();
}

void MainWindow::on_table_animaux_activated(const QModelIndex &index)
{
    QString id= ui->table_animaux->model()->data(index).toString();
           QSqlQuery query;
           query.prepare("select * from animaux where id_animaux= '"+id+"' ");
           if(query.exec())
           {
               while(query.next())
               {
                   ui->le_id->setText(query.value(0).toString());
                   ui->le_type->setCurrentText(query.value(1).toString());
                   ui->le_sexe->setCurrentText(query.value(2).toString());

                   ui->la_date->setDate(query.value(3).toDate());
                   ui->le_prix->setText(query.value(4).toString());


               }
           }
           else
               QMessageBox::information(nullptr, QObject::tr("Modifier un animal"),
                                 QObject::tr("erreur.\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);
}


void MainWindow::on_pushButton_7_clicked()
{
     ui->table_animaux->setModel(tmp.triee(0));
}
void MainWindow::on_pushButton_4_clicked()
{
    ui->table_animaux->setModel(tmp.triee(1));
}

void MainWindow::on_pushButton_8_clicked()
{
    QString type=ui->lineEdit->text();
    ui->table_animaux->setModel(tmpanimaux.cherchere(type));

}

//**************************************************nourritures***********************************************************

void MainWindow::on_ajout_nourr_clicked()
{
    int id_nourriture=ui->le_id_nourr->text().toInt();
    //int id_commande=ui->le_id_comm->text().toInt();
    QString nom=ui->le_nom->currentText();

    int quantite_nour=ui->la_qt->text().toInt();
    int prix_unitaire=ui->le_prix_un->text().toInt();
    nourritures n(id_nourriture,  nom, quantite_nour, prix_unitaire);
    QMessageBox msg;
    if(n.ajouter())
    {
        ui->table_nourritures->setModel(tmpn.afficher());//refresh
      msg.setText("ajout avec succès");
      msg.exec();
    }
    else
    { msg.setText("echec d'ajout");
        msg.exec();
    }

}



void MainWindow::on_supp_nourr_clicked()
{
    nourritures n;
           QItemSelectionModel *select = ui->table_nourritures->selectionModel();
           QModelIndexList list;
           if(select->hasSelection())
           list=select->selectedRows();
           for(int i=0; i< list.count(); i++)
           {
               n.supprimer(list[i].data().toInt());
           }
      ui->table_nourritures->setModel(tmpn.afficher());


}

void MainWindow::on_pushButton_3_clicked()
{

    int id_nourriture= ui->le_id_nourr->text().toInt();
          QString nom= ui->le_nom->currentText();
          int quantite_nour= ui->la_qt->text().toInt();
          int prix_unitaire= ui->le_prix_un->text().toInt();


         nourritures n(id_nourriture, nom, quantite_nour , prix_unitaire);
        bool test=n.modifier(id_nourriture);
  QMessageBox msg;
        if(test)
      {

            ui->table_nourritures->setModel(tmpn.afficher());//refresh

            msg.setText("nourriture modifié");
            msg.exec();

      }
        else
            QMessageBox::critical(nullptr, QObject::tr("modification des données"),
                        QObject::tr("Erreur !.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);


}

void MainWindow::on_table_nourritures_activated(const QModelIndex &index)
{
    QString id= ui->table_nourritures->model()->data(index).toString();
           QSqlQuery query;
           query.prepare("select * from nourritures where id_nourriture= '"+id+"' ");
           if(query.exec())
           {
               while(query.next())
               {
                   ui->le_id->setText(query.value(0).toString());
                   ui->le_nom->setCurrentText(query.value(2).toString());
                   ui->la_qt->setText(query.value(3).toString());
                   ui->le_prix_un->setText(query.value(4).toString());


               }
           }
           else
               QMessageBox::information(nullptr, QObject::tr("modifier un produit"),
                                 QObject::tr("erreur.\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);
}


