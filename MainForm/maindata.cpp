#include "maindata.h"

#include "containerwidget.h"

MainData::MainData()
{
}

MainData *MainData::instance()
{
    static MainData *shared = nullptr;
    if(shared == nullptr)
    {
        shared = new MainData;
    }

    return shared;
}

QVector<DBTable *> &MainData::getTables()
{
    return MainData::instance()->tables;
}

DBTable *MainData::getTableById(IdTable idTable)
{
    QVector<DBTable*> &tables = MainData::getTables();

    for(int i=0;i<tables.size();i++)
    {
        if(tables[i]->getIdTable() == idTable)
        {
            return tables[i];
        }
    }

    return NULL;
}

DBTable *MainData::getTableByName(const QString &name)
{
    QVector<DBTable*> &tables = MainData::getTables();

    for(int i=0;i<tables.size();i++)
    {
        if(tables[i]->getName() == name)
        {
            return tables[i];
        }
    }

    return NULL;
}

void MainData::deleteTableByID(IdTable idTable)
{
    QVector<DBTable*> &tables = MainData::getTables();

    for(int i=0;i<tables.size();i++)
    {
        if(tables[i]->getIdTable() == idTable)
        {
            for(int j=0;j<tables.size();j++)
            {
                tables[j]->deleteForeignById(idTable);
            }

            ContainerWidget::getShared()->deleteTableFormById(idTable);

            delete tables[i];

            //удалить из вектора таблицу
            tables.remove(i);
        }
    }
}
