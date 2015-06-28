#ifndef DBTABLE_H
#define DBTABLE_H

#include <QObject>
#include <QString>
#include <QVector>
#include <QStringList>

#include "dbattribute.h"

typedef int IdTable;

#include "dbforeign.h"

class DBTable
{
public:
    DBTable();

    QVector <DBAttribute> &getAttributes() { return attributes; }
    QString &getName() { return name; }
    IdTable getIdTable() { return idTable; }
    void setIdTable(IdTable _idTable) { idTable = _idTable; }
    QVector <DBForeign> &getForeigns() { return foreigns; }

    void deleteForeignById(IdTable _idTable);
    void deleteAtribute(int numberAtribute);

    void addAttribute(DBAttribute &attribute);
    void addName(QString &name);
    void addConnection(DBForeign foreig);

private:
    IdTable idTable;

    QString name;
    QVector <DBAttribute> attributes;
    QVector <DBForeign> foreigns;

signals:

public slots:

};

#endif // DBTABLE_H
