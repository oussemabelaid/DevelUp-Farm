#ifndef VETERINAIRE_H
#define VETERINAIRE_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QComboBox>
class Veterinaire
{public:
    Veterinaire();
    Veterinaire(QString,QString,int,QString,QString,QString,QString);

    QString get_nom();
    QString get_prenom();
    int get_prix();
    QString get_numtele();
    QString get_adresse();
    QString get_email();
    QString get_dispo();
    bool ajoutervet();
    QSqlQueryModel * affichervet();
    bool supprimervet(int);
    bool modifiervet(int);
private:
    QString nom,prenom,adresse,email,dispo,numtele;
    int prix;

};

#endif // ETUDIANT_H
