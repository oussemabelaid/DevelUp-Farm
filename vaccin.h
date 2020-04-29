#ifndef VACCIN_H
#define VACCIN_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDate>
#include <QComboBox>

class Vaccin
{
public:
    Vaccin();
    Vaccin(QString,int,QDate,QDate);
    QString get_type();
    QDate get_datev();
    QDate get_datevv();
    int get_nb();
    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(int);
    bool modifier(int);
    QSqlQueryModel * triee(int index);
    QSqlQueryModel * rechercher(QString ch);
    QSqlQueryModel * rechercher2(QString ch);
private:
    QString type;
    int nb;
    QDate datev,datevv;
};

#endif // VACCIN_H
