#include "tablesetting.h"
#include "ui_tablesetting.h"
#include "tableformwidget.h"
#include <QDebug>

#include "maindata.h"

TableSetting::TableSetting(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TableSetting)
{
    ui->setupUi(this);

    ViewTable view;
    model= new QStandardItemModel;
    model=view.createView();
    ui->tableViewSitting->setModel(model);
    for (int i=2; i<model->columnCount();i++)
    {
    ui->tableViewSitting->horizontalHeader()->setSectionResizeMode(i,QHeaderView::ResizeToContents);
    }
    connect(ui->tableViewSitting,SIGNAL(activated(const QModelIndex &)),ui->tableViewSitting,SLOT(edit(const QModelIndex &)));

    ViewTable vievConection;
    modelConection = new QStandardItemModel;
    modelConection = vievConection.createViewConection();
    ui->tableViewConection->setModel(modelConection);

}

TableSetting::~TableSetting()
{
    delete ui;
}

QString TableSetting::tableName() const
{
    QString name;
    name = ui->lineEdit->text();
    return name;
}

void TableSetting::setTable(DBTable &table)//доделать атрибуты
{
    idTable = table.getIdTable();
    tableForDeleteAtribute = table;



    item = new QStandardItem(" ");
    model->insertRow(count,item);
    ui->tableViewSitting->setModel(model);
    ui->lineEdit->setText(table.getName());

    QVector<DBAttribute> &attributes = table.getAttributes();

    count = attributes.size();
    delegate();
    qDebug()<<count;

    for(int i=0;i<attributes.size();i++)
    {
        DBAttribute &attribute = attributes[i];

        QStandardItem *itemName = new QStandardItem(attribute.name);
        QStandardItem *itemType = new QStandardItem(attribute.type);
        QStandardItem *itemPK = new QStandardItem(attribute.PK);
        QStandardItem *itemNN = new QStandardItem(attribute.NN);
        QStandardItem *itemU = new QStandardItem(attribute.UNIQ);

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

    QVector <DBForeign> &foreigns = table.getForeigns();

    int countConection = foreigns.size();

    if(countConection>0)
    {
        itemConection = new QStandardItem(" ");
        modelConection->insertRow(countConection,itemConection);
    }


    for(int i=0;i<countConection;i++)
    {
        DBTable *table = MainData::getTableById(foreigns[i].foreignTableId);

        modelConection->setItem(i,0,new QStandardItem(table->getName()));

        if(foreigns[i].typeForeign == DBForeign::ONE_TO_ONE)
        {
            modelConection->setItem(i,1,new QStandardItem("1:1"));
        }
        else
        {
            modelConection->setItem(i,1,new QStandardItem("1:N"));
        }
    }

}

DBTable TableSetting::getTable()//доделать атрибуты
{
    QModelIndex myInName,myInType,myInPK,myInNN,myInU;
    QVariant myDatName,myDatType,myDatPK,myDatNN,myDatU;

    DBTable table;

    table.setIdTable(idTable);

    for(int i = 0;i< model->rowCount();i++)
    {
        myInName=model->index(i,0,QModelIndex());
        myInType=model->index(i,1,QModelIndex());
        myInPK=model->index(i,2,QModelIndex());
        myInNN=model->index(i,3,QModelIndex());
        myInU=model->index(i,4,QModelIndex());

        myDatName=model->data(myInName,Qt::DisplayRole);
        myDatType=model->data(myInType,Qt::DisplayRole);
        myDatPK=model->data(myInPK,Qt::CheckStateRole);
        myDatNN=model->data(myInNN,Qt::CheckStateRole);
        myDatU=model->data(myInU,Qt::CheckStateRole);

        DBAttribute attribute;

        attribute.name = myDatName.toString();
        attribute.type = myDatType.toString();


        if(myDatNN.toInt()==2)
            attribute.NN = "1";
        else
            attribute.NN = "0";

        if(myDatU.toInt()==2)
            attribute.UNIQ = "1";
        else
            attribute.UNIQ = "0";

        if(myDatPK.toInt()==2)
        {
            attribute.PK = "1";
            attribute.NN = "1";
            attribute.UNIQ = "1";
        }
        else
            attribute.PK = "0";

        table.addAttribute(attribute);

    }

    QString tabname = ui->lineEdit->text();
    table.addName(tabname);
    for(int i = 0; i < modelConection->rowCount();i++)
    {
        auto indexTable=modelConection->index(i,0,QModelIndex());
        auto dataTable=modelConection->data(indexTable,Qt::DisplayRole);
        DBTable *ptable = MainData::getTableByName(dataTable.toString());

        indexTable=modelConection->index(i,1,QModelIndex());
        dataTable=modelConection->data(indexTable,Qt::DisplayRole);

        DBForeign::TypeForeign typeForeign = dataTable.toString() == "1:1" ? DBForeign::ONE_TO_ONE : DBForeign::ONE_TO_MANY;

        table.addConnection(DBForeign(ptable->getIdTable(), typeForeign));
    }

    return table;
}


void TableSetting::on_PlusItem_clicked()
{
    item = new QStandardItem(" ");
    model->insertRow(count,item);
    count++;

    qDebug()<<count;
    ui->tableViewSitting->setModel(model);
}

void TableSetting::on_MinusItem_clicked()
{
    tableForDeleteAtribute.deleteAtribute(ui->tableViewSitting->currentIndex().row());
    model->removeRow(ui->tableViewSitting->currentIndex().row());
}

void TableSetting::delegate()
{
    Combobox cb;
    cb.elemnt.push_back("INT");
    cb.elemnt.push_back("VARCHAR");
    cb.elemnt.push_back("BOOLEAN");
    cb.elemnt.push_back("REAL");
    cb.elemnt.push_back("DOUBLE");

    V.push_back(cb);

    TypeAttrEditorDelegate * cl = new TypeAttrEditorDelegate(V,ui->tableViewSitting);
    ui->tableViewSitting->setItemDelegate(cl);
}
