#ifndef DBATTRIBUTE_H
#define DBATTRIBUTE_H

#include <QObject>

class DBAttribute
{
public:

    QString name;
    QString type;
    QString PK;
    QString FK;
    QString NN;
    QString UNIQ;

};

#endif // DBATTRIBUTE_H
