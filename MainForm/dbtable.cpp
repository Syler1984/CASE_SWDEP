#include "dbtable.h"
#include "maindata.h"

DBTable::DBTable()
{
    static int globalIdTable = 0;

    idTable = globalIdTable++;
}

void DBTable::deleteForeignById(IdTable _idTable)
{
    for(int i = 0;i<foreigns.size();i++)
    {
        if(foreigns[i].foreignTableId==_idTable)
        {
            //удалить из вектора запись
            foreigns.remove(i);
        }
    }
}

void DBTable::deleteAtribute(int numberAtribute)
{
    if(attributes.size()==0)
        return;
    attributes.remove(numberAtribute);
}

void DBTable::addAttribute(DBAttribute &attribute)
{
    attributes.push_back(attribute);
}

void DBTable::addName(QString &name)
{
    this->name = name;
}

void DBTable::addConnection(DBForeign foreign)
{
    foreigns.push_back(foreign);
    foreigns.erase( std::unique(foreigns.begin(), foreigns.end() ), foreigns.end() );
}
