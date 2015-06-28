#include "tableformwidget.h"
#include "ui_TableForm.h"

#include "containerwidget.h"

TableFormWidget::TableFormWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TableForm)
{
        ui->setupUi(this);


        setBackgroundRole(QPalette::Light);

        ViewTable view;

        model= new QStandardItemModel;


        model=view.createView();

        ui->tableViewWidget->setModel(model);

        for (int i=2; i<model->columnCount();i++)
        {
        ui->tableViewWidget->horizontalHeader()->setSectionResizeMode(i,QHeaderView::ResizeToContents);
        }

        connect(ui->tableViewWidget,SIGNAL(activated(const QModelIndex &)),ui->tableViewWidget,SLOT(edit(const QModelIndex &)));

}

TableFormWidget::~TableFormWidget()
{

}

void TableFormWidget::setTable(DBTable *table)
{
    this->table = table;
}

void TableFormWidget::updateWidgetFromData()
{
    QVector<DBAttribute> &attributes = table->getAttributes();

    if(model->rowCount()>attributes.size())
    {
        while(model->rowCount()!=attributes.size())
        {
            model->removeRow(model->rowCount()-1);
        }
    }

    for(int i=0;i<attributes.size();i++)
    {
        DBAttribute &attribute = attributes[i];

        QStandardItem *itemName = new QStandardItem(attribute.name);
        QStandardItem *itemType = new QStandardItem(attribute.type);
        QStandardItem *itemPK = new QStandardItem(attribute.PK);
        QStandardItem *itemNN = new QStandardItem(attribute.NN);
        QStandardItem *itemU = new QStandardItem(attribute.UNIQ);

        //model->setRowCount(0);

        model->setItem(i,0,itemName);
        model->setItem(i,1,itemType);
        if(itemPK->text().toInt()==1)
        {
            model->setData(model->index(i,2,QModelIndex()),2,Qt::CheckStateRole);
        }
        else
        {
            model->setData(model->index(i,2,QModelIndex()),0,Qt::CheckStateRole );
        }
        if(itemNN->text().toInt()==1)
        {
            model->setData(model->index(i,3,QModelIndex()),2,Qt::CheckStateRole);
        }
        else
        {
            model->setData(model->index(i,3,QModelIndex()),0,Qt::CheckStateRole );
        }
        if(itemU->text().toInt()==1)
        {
            model->setData(model->index(i,4,QModelIndex()),2,Qt::CheckStateRole);
        }
        else
        {
            model->setData(model->index(i,4,QModelIndex()),0,Qt::CheckStateRole );
        }
    }
}

DBTable *TableFormWidget::getTable()
{
    return table;
}



void TableFormWidget::on_pushButtonSetting_clicked()
{
    TableSetting setting;

    setting.setTable(*table);

    setting.show();
    if(setting.exec() == QDialog::Accepted)
    {
        QString tabname;
        tabname = setting.tableName();
        ui->label->setText(tabname);

        *table = setting.getTable();

        updateWidgetFromData();
    }
}
