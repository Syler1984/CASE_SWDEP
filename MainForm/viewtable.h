#ifndef VIEWTABLE_H
#define VIEWTABLE_H

#include <QObject>
#include <QStandardItem>
#include <QStandardItemModel>

class ViewTable : public QObject
{
    Q_OBJECT
public:
    explicit ViewTable(QObject *parent = 0);
    QStandardItemModel *createView();
    QStandardItemModel *createViewConection();

signals:

public slots:

};

#endif // VIEWTABLE_H
