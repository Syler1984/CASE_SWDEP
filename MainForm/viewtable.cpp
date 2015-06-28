#include "viewtable.h"

ViewTable::ViewTable(QObject *parent) :
    QObject(parent)
{
}

QStandardItemModel *ViewTable::createView()
{
    QStringList horizontalHeader;
    horizontalHeader.append("Attributs");
    horizontalHeader.append("Type");
    horizontalHeader.append("PK");
    horizontalHeader.append("NN");
    horizontalHeader.append("U");

    QStandardItemModel *model= new QStandardItemModel;
    model->setHorizontalHeaderLabels(horizontalHeader);

    return model;

}

QStandardItemModel *ViewTable::createViewConection()
{
    QStringList horizontalHeader;
    horizontalHeader.append("Table");
    horizontalHeader.append("Type");

    QStandardItemModel *model= new QStandardItemModel;
    model->setHorizontalHeaderLabels(horizontalHeader);

    return model;
}
