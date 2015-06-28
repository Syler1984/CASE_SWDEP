#include "sqlite.h"

DBTable *getTableFromId(QVector<DBTable *> &tables, IdTable idTable)
{
    for(int i=0;i<tables.size();i++)
    {
        if(tables[i]->getIdTable()==idTable)
        {
            return tables[i];
        }
    }

    return 0;
}

Sqlite::Sqlite()
{
}

QString Sqlite::getVersion()
{
    return "1.0";
}

QString Sqlite::getName()
{
    return "Sqlite";
}

QString Sqlite::getCreateScript(QVector<DBTable *> &tables)
{
    QString script="";
    if(tables.size()==0)
    {
        script="Не найдено ни одной таблицы.";
    }
    for(int i=0;i<tables.size();i++)
    {
        if (tables[i]->getAttributes().size()==0)
        {
            script = "В таблице "+ tables[i]->getName()+" не найденно ни одного атрибута.\n";
            return script;
        }
        script = script+"CREATE TABLE " + tables[i]->getName()+" (";
        for(int j=0;j<tables[i]->getAttributes().size();j++)
        {
            if (tables[i]->getAttributes()[j].name==" "||tables[i]->getAttributes()[j].type==" ")
            {
                script = "В таблице "+ tables[i]->getName()+" неправильно заполнен атрибут.\n";
                return script;
            }
            if(j==tables[i]->getAttributes().size()-1)
            {
                script =script+tables[i]->getAttributes()[j].name + " " + tables[i]->getAttributes()[j].type;
                if(tables[i]->getAttributes()[j].NN == "1")
                {
                    if(tables[i]->getAttributes()[j].PK == "0")
                        script =script + " NOT NULL";
                }
                if(tables[i]->getAttributes()[j].UNIQ == "1")
                {
                    if(tables[i]->getAttributes()[j].PK == "0")
                        script =script + " UNIQUE";
                }

            }

            else
            {
                script=script+tables[i]->getAttributes()[j].name + " " + tables[i]->getAttributes()[j].type;
                if(tables[i]->getAttributes()[j].NN == "1")
                {
                    if(tables[i]->getAttributes()[j].PK == "0")
                        script =script + " NOT NULL";
                }
                if(tables[i]->getAttributes()[j].UNIQ == "1")
                {
                    if(tables[i]->getAttributes()[j].PK == "0")
                        script =script + " UNIQUE";
                }
                script =script+ ",";
            }
        }

        bool foreignTablesEx = false;
        QVector<DBForeign> &foreignTables = tables[i]->getForeigns();

        for(int k=0;k<foreignTables.size();k++)
        {
            foreignTablesEx = true;

            DBTable *table = getTableFromId(tables, foreignTables[k].foreignTableId);

            QVector<DBAttribute> &attributes = table->getAttributes();

            QString nameAttr="";

            for(int attr=0;attr<attributes.size();attr++)
            {
                if(attributes[attr].PK=="1")
                {
                    nameAttr = attributes[attr].name;
                    break;
                }
            }

            script += ',' + nameAttr;
            script=script+" REFERENCES "+table->getName()+" ON DELETE CASCADE ON UPDATE CASCADE";
        }
        bool PKAdd = false;

        for(int attr=0;attr<tables[i]->getAttributes().size();attr++)
        {
            if(tables[i]->getAttributes()[attr].PK=="1")
            {
                script=script+",PRIMARY KEY(";
                PKAdd = true;
                break;
            }
        }
        if(PKAdd == true)
        {
            for(int attr=0;attr<tables[i]->getAttributes().size();attr++)
            {
                if(tables[i]->getAttributes()[attr].PK=="1")
                {
                    script=script+tables[i]->getAttributes()[attr].name+',';
                }
            }
            if(foreignTablesEx==true)
            {
                QVector<DBForeign> &foreignTablesforPK = tables[i]->getForeigns();

                for(int k=0;k<foreignTablesforPK.size();k++)
                {
                    DBTable *table = getTableFromId(tables, foreignTablesforPK[k].foreignTableId);

                    QVector<DBAttribute> &attributesforPK = table->getAttributes();

                    QString nameAttrforPK="";

                    for(int attr=0;attr<attributesforPK.size();attr++)
                    {
                        if(attributesforPK[attr].PK=="1")
                        {
                            nameAttrforPK = attributesforPK[attr].name;
                            break;
                        }
                    }

                    script += nameAttrforPK+',';
                }
            }

            script.resize(script.size()-1);
            script += ")";

        }
        script += ");\n";
    }

    return script;
}
