#ifndef TABLESETTING_H
#define TABLESETTING_H

#include <QDialog>
#include <QString>
#include <QModelIndex>
#include <QVector>
#include <QStringList>
#include <QStandardItem>
#include <QStandardItemModel>
#include <QAbstractTableModel>

#include "typeattreditordelegate.h"
#include "tableformwidget.h"
#include "viewtable.h"


#include "dbtable.h"

namespace Ui {
class TableSetting;
}
class TableSetting : public QDialog
{
    Q_OBJECT

public:
    explicit TableSetting(QWidget *parent = 0);
    ~TableSetting();
    QString tableName() const;
    void setTable(DBTable &table);
    DBTable getTable();

    QStandardItem *item;
    QStandardItem *itemConection;
    QVector <Combobox> V;

private slots:
    void on_PlusItem_clicked();
    void on_MinusItem_clicked();

private:
    void delegate();

    DBTable tableForDeleteAtribute;
    IdTable idTable;
    Ui::TableSetting *ui;
    QStandardItemModel *model;
    QStandardItemModel *modelConection;
    int count;

};

#endif // TABLESETTING_H
