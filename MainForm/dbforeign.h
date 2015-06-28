#ifndef DBFOREIGN_H
#define DBFOREIGN_H

typedef int IdTable;

class DBForeign
{
public:

    enum TypeForeign
    {
        ONE_TO_ONE,
        ONE_TO_MANY
    };

    DBForeign(IdTable forIdTable, TypeForeign typeFor):
        foreignTableId(forIdTable),
        typeForeign(typeFor)
    {}

    DBForeign(){}

    bool operator==(const DBForeign &two)
    {
        return foreignTableId == two.foreignTableId;
    }

    IdTable foreignTableId;
    TypeForeign typeForeign;

};

#endif // DBFOREIGN_H
