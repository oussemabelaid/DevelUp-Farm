#include "vaccin.h"
#include <QDebug>
#include "connexion.h"
#include <QComboBox>

Vaccin::Vaccin()
{
type="";
nb=0;
}
Vaccin::Vaccin(QString type ,int nb,QDate datev,QDate datevv)
{
  this->type=type;
  this->nb=nb;
  this->datev=datev;
  this->datevv=datevv;

}
QString Vaccin::get_type(){return type;}
int Vaccin::get_nb(){return nb;}
QDate Vaccin::get_datev(){return datev;}
QDate Vaccin::get_datevv(){return datevv;}

//ajout
bool Vaccin::ajouter()
{
QSqlQuery query;

query.prepare("INSERT INTO vaccin (TYPE, NB, DATEV, IDV, DATEVV) "
                    "VALUES (:type, :nb, :datev, null, :datevv)");
query.bindValue(":nb", nb);
query.bindValue(":type", type);
query.bindValue(":datev", datev);
query.bindValue(":datevv", datevv);
return    query.exec();
}
//afficher
QSqlQueryModel * Vaccin::afficher()
{QSqlQueryModel * model= new QSqlQueryModel();
model->setQuery("select IDV, TYPE, NB, DATEV, DATEVV  from vaccin");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("Id Vaccin"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("Type de vaccin"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("Nombre "));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("Date 1"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("Date 2"));
    return model;
}
//suppression
bool Vaccin::supprimer(int idd)
{
QSqlQuery query;
QString res= QString::number(idd);
query.prepare("Delete from vaccin where IDV = :idv ");
query.bindValue(":idv", res);
return    query.exec();
}
//modifier
bool Vaccin::modifier(int idv)
{
    QSqlQuery query;
    query.prepare("update vaccin set  TYPE=:type,NB=:nb,DATEV=:datev,DATEVV=:datevv where IDV=:idv");

    query.bindValue(":idv",idv);
    query.bindValue(":type",type);
    query.bindValue(":nb",nb);
    query.bindValue(":datev",datev);
    query.bindValue(":datevv",datevv);

    return query.exec();

}
//tri
QSqlQueryModel* Vaccin::triee(int index)
{
    QSqlQueryModel* model = new QSqlQueryModel();
    if(index == 0)
    {
        model->setQuery("select IDV, TYPE, NB, DATEV, DATEVV FROM vaccin ORDER BY DATEV ASC");

    }
    else if(index == 1)
    {
        model->setQuery("select IDV, TYPE, NB, DATEV, DATEVV FROM vaccin ORDER BY DATEV DESC ");
    }
    else if(index == 2)
    {
        model->setQuery("select IDV, TYPE, NB, DATEV, DATEVV FROM vaccin ORDER BY DATEVV ASC ");
    }
    else
    {
        model->setQuery("select IDV, TYPE, NB, DATEV, DATEVV FROM vaccin ORDER BY DATEVV DESC ");
    }

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Id Vaccin"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Type de vaccin"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Nombre "));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Date 1"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Date 2"));

    return model;
}

//recherche
QSqlQueryModel * Vaccin :: rechercher(QString ch)
{
    QSqlQueryModel * model= new QSqlQueryModel();

    QString str="select IDV, TYPE, NB, DATEV, DATEVV FROM vaccin where IDV like '"+ch+"%'";
    model->setQuery(str);
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Id Vaccin"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Type de vaccin"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Nombre "));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Date 1"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Date 2"));
    return model;
}
QSqlQueryModel * Vaccin :: rechercher2(QString ch)
{
    QSqlQueryModel * model= new QSqlQueryModel();

    QString str="select IDV, TYPE, NB, DATEV, DATEVV FROM vaccin where TYPE like '"+ch+"%'";
    model->setQuery(str);
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Id Vaccin"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Type de vaccin"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Nombre "));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Date 1"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Date 2"));
    return model;
}
