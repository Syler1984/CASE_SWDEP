#ifndef MAINDATA_H
#define MAINDATA_H

#include "dbtable.h"
#include <QVector>

class MainData
{
public:
    MainData();

    static MainData *instance();
    static QVector<DBTable*> &getTables();
    static DBTable *getTableById(IdTable idTable);
    static DBTable *getTableByName(const QString &name);
    static void deleteTableByID(IdTable idTable);
private:
    QVector<DBTable*> tables;

};

#endif // MAINDATA_H
