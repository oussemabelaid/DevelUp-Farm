#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "vaccin.h"
#include "veterinaire.h"
#include <QMessageBox>
#include <QComboBox>
#include <QDebug>
#include <QSqlQuery>
#include <QDate>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
ui->setupUi(this);
    mysystem=new QSystemTrayIcon(this);
    mysystem->setIcon(QIcon(":/farmer.ico"));
    mysystem->setVisible(true);
    ui->tabvaccin->setModel(tmpvaccin.afficher());
    ui->tabvet->setModel(tmpvet.affichervet());
    ui->linee->setPlaceholderText("Type");
    ui->lineEdit_idd->setPlaceholderText(("Id "));

}

MainWindow::~MainWindow()
{
    delete ui;
}
//vaccin
//**************************************************************************************
//Ajout vaccin
void MainWindow::on_pb_ajouter_clicked()
{
    QString type= ui->comboBoxtype->currentText();
    QDate datev= ui->dateEdit->date();
    int nb= ui->box_nb->text().toInt();
    QDate datevv= ui->dateEdit2->date();


  Vaccin v(type,nb,datev,datevv);
  bool test=v.ajouter();

  if(test)
{

      ui->tabvaccin->setModel(tmpvaccin.afficher());//refresh
QMessageBox::information(nullptr, QObject::tr("Ajouter un vaccin"),
                  QObject::tr("Vaccin ajouté.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);
      mysystem->showMessage(tr("notification"),tr("Ajout avec succes"));


}
  else
      QMessageBox::critical(nullptr, QObject::tr("Ajouter un vaccin"),
                  QObject::tr("Erreur !.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);


}
//modif vaccin
void MainWindow::on_pb_modifier_clicked()
{
        int id= ui->lineEdit->text().toInt();
        QString type= ui->comboBoxtype->currentText();
        QDate datev= ui->dateEdit->date();
        int nb= ui->box_nb->text().toInt();
        QDate datevv= ui->dateEdit2->date();


      Vaccin v(type,nb,datev,datevv);
      bool test=v.modifier(id);

      if(test)
    {

          ui->tabvaccin->setModel(tmpvaccin.afficher());//refresh
    QMessageBox::information(nullptr, QObject::tr("Modifier un vaccin"),
                      QObject::tr("Vaccin Modifié.\n"
                                  "Click Cancel to exit."), QMessageBox::Cancel);


    }
      else
          QMessageBox::critical(nullptr, QObject::tr("Modifier un vaccin"),
                      QObject::tr("Erreur !.\n"
                                  "Click Cancel to exit."), QMessageBox::Cancel);




}

//supp vaccin
void MainWindow::on_pb_supprimer_clicked()
{
Vaccin v;
       QItemSelectionModel *select = ui->tabvaccin->selectionModel();
       QModelIndexList list;
       if(select->hasSelection())
       list=select->selectedRows();
       for(int i=0; i< list.count(); i++)
       {
       QMessageBox::StandardButton reply;
       reply = QMessageBox::question(this, "Supprimer Vaccin", "Vous etes sure?",
                                     QMessageBox::Yes|QMessageBox::No);
       if (reply == QMessageBox::Yes) {
           v.supprimer(list[i].data().toInt());
           ui->tabvaccin->setModel(v.afficher());
           QMessageBox::information(nullptr, QObject::tr("Supprimer un Vaccin"),
           QObject::tr("Vaccin supprimée.\n"
           "Click Cancel to exit."), QMessageBox::Cancel);}}}

//veterinaire
//****************************************************************
//Ajout vet
void MainWindow::on_pb_ajoutervet_clicked()
{

    QString nom= ui->lineEdit_nom->text();
    QString prenom= ui->lineEdit_prenom->text();
    int prix= ui->SpinBox_prix->text().toInt();
    QString numtele= ui->lineEdit_numtele->text();
    QString adresse= ui->lineEdit_adresse->text();
    QString email= ui->lineEdit_email->text();
    QString dispo=ui->comboBox_dispo->currentText();


  Veterinaire vet(nom,prenom,prix,numtele,adresse,email,dispo);

   if( numtele.length()==8)
      {
      if(vet.ajoutervet())
          {
                      ui->tabvet->setModel(tmpvet.affichervet());//refresh
                QMessageBox::information(nullptr, QObject::tr("Ajouter un veterinaire"),
                      QObject::tr("veterinaire ajouté.\n"
                                  "Click Cancel to exit."), QMessageBox::Cancel);
        }
      else
          QMessageBox::critical(nullptr, QObject::tr("Ajouter un veterinaire"),
                      QObject::tr("Erreur !.\n"
                                  "Click Cancel to exit."), QMessageBox::Cancel);
  }
  else
  {
      QMessageBox::critical(nullptr, QObject::tr("Nume telephone "),
                  QObject::tr("Erreur !.\n"
                              "Numéro de téléphone doit égale à 8 chiffres."), QMessageBox::Cancel);
  }

}


//supp vet
void MainWindow::on_pushButton_supp_clicked()
{
Veterinaire vet;
       QItemSelectionModel *select = ui->tabvet->selectionModel();
       QModelIndexList list;
       if(select->hasSelection())
       list=select->selectedRows();
       for(int i=0; i< list.count(); i++)
       {
           vet.supprimervet(list[i].data().toInt());
       }
  ui->tabvet->setModel(vet.affichervet());

}

//modif vet
void MainWindow::on_pushButton_2_clicked()
{
    QString nom= ui->lineEdit_nom->text();
    QString prenom= ui->lineEdit_prenom->text();
    int prix= ui->SpinBox_prix->text().toInt();
    QString numtele= ui->lineEdit_numtele->text();
    QString adresse= ui->lineEdit_adresse->text();
    QString email= ui->lineEdit_email->text();
    QString dispo=ui->comboBox_dispo->currentText();
bool test;

  Veterinaire vet(nom,prenom,prix,numtele,adresse,email,dispo);

           QItemSelectionModel *select = ui->tabvet->selectionModel();
           QModelIndexList list;
           if(select->hasSelection())
           list=select->selectedRows();
           for(int i=0; i< list.count(); i++)
           {
                test=vet.modifiervet(list[i].data().toInt());
                qDebug() << list[i].data().toInt();
           }

  if(test)
{

      ui->tabvet->setModel(tmpvet.affichervet());//refresh
QMessageBox::information(nullptr, QObject::tr("Modifier un vétérinaire"),
                  QObject::tr("Vétérinaire modifié.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);


}
  else
      QMessageBox::critical(nullptr, QObject::tr("modifier un vétérinaire"),
                  QObject::tr("Erreur !.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);
}




/*
void MainWindow::on_pb_supprimer_clicked()
{
int id = ui->lineEdit_id_2->text().toInt();
bool test=tmpvaccin.supprimer(id);
if(test)
{ui->tabvaccin->setModel(tmpvaccin.afficher());//refresh
    QMessageBox::information(nullptr, QObject::tr("Supprimer un vaccin"),
                QObject::tr("Vaccin supprimé.\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);

}
else
    QMessageBox::critical(nullptr, QObject::tr("Supprimer un vaccin"),
                QObject::tr("Erreur !.\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);


}*/



/*void MainWindow::on_pb_modifier_clicked()
{

    QString type= ui->comboBoxtype->currentText();
    QDate datev= ui->dateEdit->date();
    int nb= ui->box_nb->text().toInt();
    QDate datevv= ui->dateEdit2->date();
bool test;

  Vaccin v(type,nb,datev,datevv);

           QItemSelectionModel *select = ui->tabvaccin->selectionModel();
           QModelIndexList list;
           if(select->hasSelection())
           list=select->selectedRows();
           for(int i=0; i< list.count(); i++)
           {
                test=v.modifier(list[i].data().toInt());
           }

  if(test)
{

      ui->tabvaccin->setModel(tmpvaccin.afficher());//refresh
QMessageBox::information(nullptr, QObject::tr("Modifier un vaccin"),
                  QObject::tr("Vaccin modifié.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);


}
  else
      QMessageBox::critical(nullptr, QObject::tr("Ajouter un vaccin"),
                  QObject::tr("Erreur !.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);
}*/



//tris
void MainWindow::on_pb_ask_clicked()
{
     ui->tabvaccin->setModel(tmpvaccin.triee(0));
}

void MainWindow::on_pb_decr_clicked()
{
     ui->tabvaccin->setModel(tmpvaccin.triee(1));
}

void MainWindow::on_pb_d2desc_clicked()
{
    ui->tabvaccin->setModel(tmpvaccin.triee(3));

}

void MainWindow::on_pb_d2asc_clicked()
{
    ui->tabvaccin->setModel(tmpvaccin.triee(2));

}
//recherche
void MainWindow::on_rechercher_clicked()
{
    Vaccin v;
    QString arg1=ui->lineEdit_idd->text();
    QString arg2=ui->linee->text();

        if ((arg1=="")&&(arg2==""))
        ui->tabvaccin->setModel(v.afficher());
        else if((arg1=="")&&(arg2!=""))
        this->ui->tabvaccin->setModel(v.rechercher2(arg2));
        else
        this->ui->tabvaccin->setModel(v.rechercher(arg1));

}
//load
void MainWindow::on_pushButton_clicked()
{
    ui->tabvaccin->setModel(tmpvaccin.afficher());
}

//champs
void MainWindow::on_tabvaccin_activated(const QModelIndex &index)
{

    QString val= ui->tabvaccin->model()->data(index).toString();
        QSqlQuery query;
        query.prepare("select * from vaccin where IDV= '"+val+"' ");
        if(query.exec())
        {
            while(query.next())
            {
                ui->comboBoxtype->setCurrentText(query.value(0).toString());
                ui->box_nb->setValue(query.value(1).toString().toInt());
                ui->dateEdit->setDate(query.value(2).toDate());
                ui->dateEdit->setDate(query.value(4).toDate());
                ui->lineEdit->setText(query.value(3).toString());
                //ui->lineEdit_id_2->setText(query.value(0).toString());
            }
        }
        else
            QMessageBox::information(nullptr, QObject::tr("Modifier un compte"),
                              QObject::tr("erreur.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
  }
