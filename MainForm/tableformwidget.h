#ifndef TABLEFORMWIDGET_H
#define TABLEFORMWIDGET_H

#include <QWidget>
#include <QString>
#include <QVector>
#include <QMouseEvent>
#include <QDebug>
#include<QStandardItemModel>

#include "typeattreditordelegate.h"
#include "tablesetting.h"
#include "viewtable.h"
#include "dbtable.h"

namespace Ui {
class TableForm;
}

class TableFormWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TableFormWidget(QWidget *parent = 0);
    ~TableFormWidget();

    void setTable(DBTable *table);
    DBTable *getTable();   
    void updateWidgetFromData();

    QVector <Combobox> V;

private slots:
    void on_pushButtonSetting_clicked();

private:
    Ui::TableForm *ui;
    QStandardItemModel *model;
    DBTable *table;
};


#endif // TABLEFORMWIDGET_H
