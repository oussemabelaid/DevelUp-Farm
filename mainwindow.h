#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "equipement.h"
#include "panne.h"
#include <QMainWindow>

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
    void on_pb_ajouter_equipement_clicked();

    void on_pb_supprimer_equipement_clicked();

    void on_pb_ajouter_panne_clicked();

    void on_pb_supprimer_panne_clicked();

    void on_pb_modifier_equipement_clicked();

    void on_pb_modifier_panne_clicked();

    void on_comboBox_3_currentIndexChanged(int index);

    void on_pb_charger_equipement_clicked();

    void on_pb_charger_panne_clicked();

    void on_comboBox_4_currentIndexChanged(int index);
    
    void on_comboBox_5_currentIndexChanged(int index);

    void on_printe_clicked();

    void on_printp_clicked();

    void on_radioButton_clicked();

    void on_radioButton_8_clicked();

    void on_radioButton_2_clicked();

    void on_radioButton_3_clicked();

    void on_radioButton_4_clicked();

    void on_radioButton_5_clicked();

    void on_radioButton_6_clicked();

    void on_radioButton_7_clicked();

    void on_lineEdit_textChanged(const QString &arg1);

    void on_lineEdit_2_textChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;
    Equipement tmpequipement;
    Panne tmppanne;

};
#endif // MAINWINDOW_H
