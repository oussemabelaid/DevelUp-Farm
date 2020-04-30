#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "equipement.h"
#include "panne.h"
#include <QMessageBox>
#include <QComboBox>
#include <QDebug>
#include <QPixmap>
#include <QPrinter>
#include <QDialog>
#include <QPrintDialog>
#include <QPainter>
#include <QPaintEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    QString windowTitle("DevelUp Farm");
    ui->setupUi(this);
    setWindowIcon(QIcon(":/main1/img/zvenden.png"));
    this->setWindowTitle(windowTitle);
    QPixmap pix2(":/main1/img/equipement.png");
    int w2 = ui->label_pic2->width();
    int h2 = ui->label_pic2->height();
    ui->label_pic2->setPixmap(pix2.scaled(w2,h2,Qt::KeepAspectRatio));
    QPixmap pix3(":/main1/img/panne.png");
    int w3 = ui->label_pic3->width();
    int h3 = ui->label_pic3->height();
    ui->label_pic3->setPixmap(pix3.scaled(w3,h3,Qt::KeepAspectRatio));
    ui->tabequipement->setModel(tmpequipement.afficher());
    ui->comboBox_3->setModel(tmpequipement.afficher());
    ui->comboBox_5->setModel(tmpequipement.afficherI());
    ui->comboBox_4->setModel(tmppanne.afficher());
    ui->tabpanne->setModel(tmppanne.afficher());
    ui->tabequipement->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tabpanne->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pb_ajouter_equipement_clicked()
{
    int numserie= ui->lineEdit_numserie->text().toInt();
        QString type= ui->comboBox_2->currentText();
        QString marque= ui->lineEdit_marque->text();
        QString disponibilite= ui->comboBox->currentText();
      Equipement e(numserie,type,marque,disponibilite);
      bool test=e.ajouter();
      if(test)
    {

    ui->tabequipement->setModel(tmpequipement.afficher());//refresh
    ui->comboBox_3->setModel(tmpequipement.afficher());//refresh
     ui->comboBox_5->setModel(tmpequipement.afficherI());//refresh
    QMessageBox::information(nullptr, QObject::tr("Ajouter un Equipement"),
                      QObject::tr("Equipement ajouté.\n"
                                  "Clicker sur Sortir pour quitter."), QMessageBox::Cancel);

    }
      else
          QMessageBox::critical(nullptr, QObject::tr("Ajouter un equipement"),
                      QObject::tr("Erreur !.\n"
                                  "Clicker sur Sortir pour quitter."), QMessageBox::Cancel);
}

void MainWindow::on_pb_supprimer_equipement_clicked()
{
    Equipement e;
           QItemSelectionModel *select = ui->tabequipement->selectionModel();
           QModelIndexList list;
           if(select->hasSelection())
           list=select->selectedRows();
            for(int i=0; i< list.count(); i++){

                QMessageBox::StandardButton reply;
            reply = QMessageBox::question(this, "Supprimer Equipement", "Vous etes sure?",
                                          QMessageBox::Yes|QMessageBox::No);
            if (reply == QMessageBox::Yes) {
              e.supprimer(list[i].data().toInt());
              ui->tabequipement->setModel(tmpequipement.afficher());//refresh
              ui->comboBox_3->setModel(tmpequipement.afficher());
              ui->comboBox_5->setModel(tmpequipement.afficherI());
              QMessageBox::information(nullptr, QObject::tr("Supprimer un Equipement"),
                                QObject::tr("Equipement supprimée.\n"
                                            "Click Cancel to exit."), QMessageBox::Cancel);}}}


void MainWindow::on_pb_ajouter_panne_clicked()
{
    // int numserie = ui->comboBox_5->currentIndex();
    int id = ui->lineEdit_ID->text().toInt();
       int numserie= ui->lineEdit_numseriep->text().toInt();

       int prix= ui->lineEdit_prix->text().toInt();
       int duree= ui->lineEdit_duree->text().toInt();
     Panne p(numserie,id,prix,duree);
     bool test=p.ajouter();
     if(test)
   {

   ui->tabpanne->setModel(tmppanne.afficher());//refresh
   ui->comboBox_4->setModel(tmppanne.afficher());
   QMessageBox::information(nullptr, QObject::tr("Ajouter une Panne"),
                     QObject::tr("Panne ajouté.\n"
                                 "Click Cancel to exit."), QMessageBox::Cancel);

   }
     else
         QMessageBox::critical(nullptr, QObject::tr("Ajouter une Panne"),
                     QObject::tr("Erreur !.\n"
                                 "Click Cancel to exit."), QMessageBox::Cancel);

}

void MainWindow::on_pb_supprimer_panne_clicked()
{
    Panne pp;
           QItemSelectionModel *select = ui->tabpanne->selectionModel();
           QModelIndexList list;
           if(select->hasSelection())
           list=select->selectedRows();
           for( int i=0; i< list.count(); i++)
             {  QMessageBox::StandardButton replyy;
           replyy = QMessageBox::question(this, "Supprimer Panne", "Vous etes sure?",
                                         QMessageBox::Yes|QMessageBox::No);
           if (replyy == QMessageBox::Yes) {
             pp.supprimer(list[i].data().toInt());
             ui->tabpanne->setModel(tmppanne.afficher());//refresh
             ui->comboBox_4->setModel(tmppanne.afficher());

             QMessageBox::information(nullptr, QObject::tr("Supprimer un Panne"),
                               QObject::tr("Panne supprimée.\n"
                                           "Click Cancel to exit."), QMessageBox::Cancel);}}}

void MainWindow::on_pb_modifier_equipement_clicked()
{
    int numserie= ui->lineEdit_numserie->text().toInt();
        QString type= ui->comboBox_2->currentText();
        QString marque= ui->lineEdit_marque->text();
        QString disponibilite= ui->comboBox->currentText();

    Equipement p;
    bool atout=p.modifier(numserie,type,marque,disponibilite);
    if(atout)
    {ui->tabequipement->setModel(tmpequipement.afficher());
         ui->comboBox_5->setModel(tmpequipement.afficherI());//refresh
        QMessageBox::information(nullptr, QObject::tr("Modifier un Equipement"),
                                 QObject::tr("Equipement modifié.\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);}
    else
        QMessageBox::critical(nullptr, QObject::tr("Modifier un Equipement"),
                              QObject::tr("Erreur !.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
}

void MainWindow::on_pb_modifier_panne_clicked()
{
    int id = ui->lineEdit_ID->text().toInt();
       double numserie= ui->lineEdit_numseriep->text().toInt();

       double prix= ui->lineEdit_prix->text().toInt();
       int duree= ui->lineEdit_duree->text().toInt();

    Panne p;
    bool atout=p.modifier(id,numserie,prix,duree);
    if(atout)
    {ui->tabpanne->setModel(tmppanne.afficher());
        QMessageBox::information(nullptr, QObject::tr("Modifier une Panne"),
                                 QObject::tr("Panne modifié.\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);}
    else
        QMessageBox::critical(nullptr, QObject::tr("Modifier une Panne"),
                              QObject::tr("Erreur !.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
}

void MainWindow::on_comboBox_3_currentIndexChanged(int index)
{
    QSqlQuery query;
    int numserie=ui->comboBox_3->currentText().toInt();
 query.prepare("select * from equipement where numserie = :numserie");
        query.bindValue(":numserie",numserie);
 if(query.exec()){
  while(query.next()){

            ui->lineEdit_numserie->setText(query.value(0).toString());
             qDebug()<<query.value(0).toString();
              ui->comboBox_2->clear();

             ui->comboBox_2->addItem(query.value(1).toString());

             if((query.value(1).toString())=="Transport")
             {

                         ui->comboBox_2->addItem("Agriculture");}
             else
             {
              ui->comboBox_2->addItem("Transport");}
 //qDebug ("here");
 ui->lineEdit_marque->setText(query.value(2).toString());
              ui->comboBox->clear();
              ui->comboBox->addItem(query.value(3).toString());
              if((query.value(3).toString())=="Disponible")
              {

                          ui->comboBox->addItem("non"); }
              else
              {
               ui->comboBox->addItem("Disponible");}}}}

void MainWindow::on_comboBox_4_currentIndexChanged(int ind)
{
    QSqlQuery query;
       int numserie=ui->comboBox_4->currentText().toInt();

    //ui->comboBox->currentText().toInt()
        query.prepare("select * from panne where numserie = :numserie");
            query.bindValue(":numserie",numserie);

       // qDebug("yomkn here");
        if(query.exec()){
            //qDebug("mech here");
            while(query.next()){
    //qDebug("erreur");

                 ui->lineEdit_ID->setText(query.value(1).toString());
                ui->lineEdit_numseriep->setText(query.value(0).toString());

                 qDebug()<<query.value(0).toString();

                 ui->lineEdit_prix->setText(query.value(2).toString());
ui->lineEdit_duree->setText(query.value(3).toString());



            }
        }
}
void MainWindow::on_pb_charger_equipement_clicked()

    {
    ui->tabequipement->setModel(tmpequipement.afficher());
    ui->comboBox_3->setModel(tmpequipement.afficher());
}



void MainWindow::on_pb_charger_panne_clicked()
{
    ui->tabpanne->setModel(tmppanne.afficher());
    ui->comboBox_4->setModel(tmppanne.afficher());
}

void MainWindow::on_comboBox_5_currentIndexChanged(int index)
{
    QSqlQuery query;
    int numserie=ui->comboBox_5->currentText().toInt();
    query.prepare("select * from equipement where numserie = :numserie");
        query.bindValue(":numserie",numserie);

   // qDebug("yomkn here");
    if(query.exec()){
        //qDebug("mech here");
        while(query.next()){
//qDebug("erreur");
           //ui->comboBox->addItem(query.value(0).toString());

            ui->lineEdit_numseriep->setText(query.value(0).toString());

}}}

void MainWindow::on_printe_clicked()
{
    QPrinter printer(QPrinter::HighResolution);
    QPrintDialog dlg(&printer, this);
    if (dlg.exec() == QDialog::Accepted)
    {
        // calculate the total width/height table would need without scaling
        const int rows = ui->tabequipement->model()->rowCount();
        const int cols = ui->tabequipement->model()->columnCount();
        double totalWidth = 0.0;
        for (int c = 0; c < cols; ++c)
        {
            totalWidth += ui->tabequipement->columnWidth(c);
        }
        double totalHeight = 0.0;
        for (int r = 0; r < rows; ++r)
        {
            totalHeight += ui->tabequipement->rowHeight(r);
        }


        // redirect table's painting on a pixmap
        QPixmap pixmap(totalWidth, totalHeight);
        QPainter::setRedirected(ui->tabequipement->viewport(), &pixmap);
        QPaintEvent event(QRect(0, 0, totalWidth, totalHeight));
        QApplication::sendEvent(ui->tabequipement->viewport(), &event);
        QPainter::restoreRedirected(ui->tabequipement->viewport());

        // print scaled pixmap
        QPainter painter(&printer);
        painter.drawPixmap(printer.pageRect(), pixmap, pixmap.rect());

}}

void MainWindow::on_printp_clicked()
{
    QPrinter printer(QPrinter::HighResolution);
    QPrintDialog dlg(&printer, this);
    if (dlg.exec() == QDialog::Accepted)
    {
        // calculate the total width/height table would need without scaling
        const int rows = ui->tabpanne->model()->rowCount();
        const int cols = ui->tabpanne->model()->columnCount();
        double totalWidth = 0.0;
        for (int c = 0; c < cols; ++c)
        {
            totalWidth += ui->tabpanne->columnWidth(c);
        }
        double totalHeight = 0.0;
        for (int r = 0; r < rows; ++r)
        {
            totalHeight += ui->tabpanne->rowHeight(r);
        }

        // redirect table's painting on a pixmap
        QPixmap pixmap(totalWidth, totalHeight);
        QPainter::setRedirected(ui->tabpanne->viewport(), &pixmap);
        QPaintEvent event(QRect(0, 0, totalWidth, totalHeight));
        QApplication::sendEvent(ui->tabpanne->viewport(), &event);
        QPainter::restoreRedirected(ui->tabpanne->viewport());

        // print scaled pixmap
        QPainter painter(&printer);
        painter.drawPixmap(printer.pageRect(), pixmap, pixmap.rect());


}
}

void MainWindow::on_radioButton_clicked()
{
    ui->tabequipement->setModel(tmpequipement.triee(0));
}

void MainWindow::on_radioButton_8_clicked()
{
    ui->tabequipement->setModel(tmpequipement.triee(1));
}

void MainWindow::on_radioButton_2_clicked()
{
    ui->tabpanne->setModel(tmppanne.triepn(0));
}

void MainWindow::on_radioButton_3_clicked()
{
    ui->tabpanne->setModel(tmppanne.triepn(1));
}

void MainWindow::on_radioButton_4_clicked()
{
    ui->tabpanne->setModel(tmppanne.triepp(0));
}

void MainWindow::on_radioButton_5_clicked()
{
    ui->tabpanne->setModel(tmppanne.triepp(1));
}

void MainWindow::on_radioButton_6_clicked()
{
    ui->tabpanne->setModel(tmppanne.triepd(0));
}

void MainWindow::on_radioButton_7_clicked()
{
    ui->tabpanne->setModel(tmppanne.triepd(1));
}

void MainWindow::on_lineEdit_textChanged(const QString &arg1)
{
    QString str=ui->lineEdit->text();

    ui->tabequipement->setModel(tmpequipement.cherchere(str));
}

void MainWindow::on_lineEdit_2_textChanged(const QString &arg1)
{

    QString str=ui->lineEdit_2->text();

    ui->tabpanne->setModel(tmppanne.chercherp(str));}
