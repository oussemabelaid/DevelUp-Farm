#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "animaux.h"
#include "nourritures.h"
#include <QSystemTrayIcon>

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
    void on_pushButton_clicked(); //ajout animaux
    // void on_pb_supprimer_clicked();

    // void on_pushButton_ajouter_clicked();
       void on_pushButton_supp_clicked();  //supp animaux

       //void on_pushButton_2_clicked();


       
       void on_pushButton_5_clicked(); //modif animaux

       void on_ajout_nourr_clicked();

       void on_supp_nourr_clicked();

       void on_comboBox_currentIndexChanged(int index);

       void on_pushButton_2_clicked();

       //void on_comboBox_currentIndexChanged(const QString &arg1);

       void on_pushButton_3_clicked();

       void on_pushButton_6_clicked();

       void on_comboBox_2_currentIndexChanged(int index);

       void on_pushButton_7_clicked();

       void on_pushButton_4_clicked();

       void on_pushButton_8_clicked();

       void on_pushButton_9_clicked();

       void on_table_animaux_activated(const QModelIndex &index);

       void on_table_nourritures_activated(const QModelIndex &index);

private:
    Ui::MainWindow *ui;
    animaux tmp;
    animaux tmpanimaux;
    nourritures tmpn;
    nourritures tmpnourr;
    QSystemTrayIcon *mysystem;



};
#endif // MAINWINDOW_H
