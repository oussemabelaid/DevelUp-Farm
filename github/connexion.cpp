#include "connexion.h"


connexion::connexion()
{

}

bool connexion::ouvrircnx()
{
    db= QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("test");
    db.setUserName("leila");
    db.setPassword("esprit2018");
    if(db.open())
        return true;

   return false;
}

void connexion::fermercnx()
{db.close();}
