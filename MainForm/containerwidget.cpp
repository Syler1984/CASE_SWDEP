#include "containerwidget.h"
#include <QMessageBox>

#include "pointintersect.h"

ContainerWidget *shared;

ContainerWidget::ContainerWidget(QWidget *parent) :
    QWidget(parent)
{
    shared = this;

    trigTable = false;
    trigConection1To1 = false;
    trigConection1ToM = false;
    trigEdit = false;
    trigDelete = false;
    countConection = 0;
    pressedTableForm = NULL;

    setMouseTracking(true);
}

ContainerWidget *ContainerWidget::getShared()
{
    return shared;
}

void ContainerWidget::deleteTableFormById(IdTable idTable)
{
    for(int i=0;i<tableForms.size();i++)
    {
        if(tableForms[i]->getTable()->getIdTable() == idTable)
        {
            delete tableForms[i];
            tableForms.remove(i);
            update();
            return;
        }
    }
}


void ContainerWidget::mousePressEvent(QMouseEvent *mouseEvent)
{
    pressedTableForm =  dynamic_cast<TableFormWidget*>(childAt(mouseEvent->x(),mouseEvent->y()));

    wid = childAt(mouseEvent->x(),mouseEvent->y());
    if(wid != NULL)
    {
        //widgetName = wid->objectName();
//        qDebug()<<wid;
        if(wid->objectName()=="")
        {
            wid->setObjectName("connectLabels");
        }
    }

    if (mouseEvent->buttons() & Qt::RightButton)
    {
        trigTable = false;
        trigConection1To1 = false;
        trigConection1ToM = false;
        trigEdit = false;
        sigClose();
        QApplication::setOverrideCursor(QCursor(Qt::ArrowCursor));
    }

    if(trigTable == true && wid == NULL)
    {
        TableFormWidget *tableForm = new TableFormWidget(this);
        tableForm->move(mouseEvent->x(),mouseEvent->y());

        auto table = new DBTable;
        tableForm->setTable(table);


        MainData::instance()->getTables().push_back(table);

        tableForms.push_back(tableForm);

        tableForm->show();

        qDebug()<<table->getIdTable();

        emit sig();//вызываем MainWindow::setgeometryscroll() для отрисовки рабочей области
    }

    if(pressedTableForm == NULL)
        return;

    if(trigEdit==true  && wid != NULL)//если что-то есть - зажатая лапка, нужно узнавать что именно под курсором
    {
        QApplication::setOverrideCursor(QCursor(Qt::ClosedHandCursor));
        offsetMove.setX(pressedTableForm->geometry().x()-mouseEvent->x());
        offsetMove.setY(pressedTableForm->geometry().y()-mouseEvent->y());
    }

    if((trigConection1To1==true||trigConection1ToM==true) && pressedTableForm != NULL)
    { 
        selectedTable = pressedTableForm->getTable();
        bool ok = false;
        QVector<DBAttribute> tempattr =  selectedTable->getAttributes();
        for(int i = 0;i<tempattr.size();i++)
        {
            if(tempattr[i].PK=="1")
            {
                ok = true;
            }
        }
        if(ok==false)
        {
            QMessageBox msgBoxError;
            msgBoxError.setWindowTitle("Ошибка");
            msgBoxError.setIcon(QMessageBox::Critical);
            msgBoxError.setText("Отсутствует первичный ключ в таблице "+selectedTable->getName());
            msgBoxError.exec();
            return;
        }
    }

    if(trigDelete==true&&pressedTableForm!=NULL)
    {
        deleteTableId = pressedTableForm->getTable()->getIdTable();
        //labels[deleteTableId-1]->hide();
        MainData::deleteTableByID(deleteTableId);
    }
}

void ContainerWidget::mouseMoveEvent(QMouseEvent *mouseEvent)
{ 
    mousePos = mouseEvent->pos();
//    if(wid == NULL)
//        return;
    if(trigEdit==true && pressedTableForm != NULL && (mouseEvent->buttons() & Qt::LeftButton))
    {
        pressedTableForm->move(mouseEvent->x()+offsetMove.x(),mouseEvent->y() + offsetMove.y());
        pressedTableForm->show();
        update();
    }

    selectedLine0 = -1;

    for(int i=0;i<tableForms.size();i++)
    {
        QPoint pos = tableForms[i]->pos();

        pos = QPoint(pos.x()+tableForms[i]->width()/2, pos.y()+tableForms[i]->height()/2);

        QVector<DBForeign> &forTables = tableForms[i]->getTable()->getForeigns();

        for(int j=0;j<forTables.size();j++)
        {
            TableFormWidget *formWidget2 = getTableFormById(forTables[j].foreignTableId);

            QPoint pos2 = formWidget2->pos();
            pos2 = QPoint(pos2.x()+formWidget2->width()/2, pos2.y()+formWidget2->height()/2);

            if(PointIntersect::isIntersect(pos, pos2, 10, mouseEvent->pos()))
            {
                selectedLine0 = tableForms[i]->getTable()->getIdTable();
                selectedLine1 = formWidget2->getTable()->getIdTable();
            }
        }
    }

    update();

    emit sig();//вызываем MainWindow::setgeometryscroll() для отрисовки рабочей области
}

void ContainerWidget::mouseReleaseEvent(QMouseEvent *mouseEvent)
{
    emit sig();//вызываем MainWindow::setgeometryscroll() для отрисовки рабочей области
    pressed2TableForm =  dynamic_cast<TableFormWidget*>(childAt(mouseEvent->x(),mouseEvent->y()));

    if(trigEdit==true)
    {
        QApplication::setOverrideCursor(QCursor(Qt::OpenHandCursor));
    }

    if(pressed2TableForm==pressedTableForm||pressed2TableForm==NULL)
        return;


    if(trigConection1To1==true||trigConection1ToM==true)
    {

        if(selectedTable != NULL)
        {
            bool ok = false;
            QVector<DBAttribute> tempattr =  pressed2TableForm->getTable()->getAttributes();
            for(int i = 0;i<tempattr.size();i++)
            {
                if(tempattr[i].PK=="1")
                {
                    ok = true;
                }
            }
            if(ok==false)
            {
                trigTable = false;
                trigConection1To1 = false;
                trigConection1ToM = false;
                trigEdit = false;
                sigClose();
                QApplication::setOverrideCursor(QCursor(Qt::ArrowCursor));
                QMessageBox msgBoxError;
                msgBoxError.setWindowTitle("Ошибка");
                msgBoxError.setIcon(QMessageBox::Critical);
                msgBoxError.setText("Отсутствует первичный ключ в таблице "+pressed2TableForm->getTable()->getName());
                msgBoxError.exec();
                return;
            }
            DBForeign::TypeForeign typeForeign;

            if(trigConection1To1==true)
            {
                typeForeign = DBForeign::ONE_TO_ONE;
            }
            if(trigConection1ToM==true)
            {
                typeForeign = DBForeign::ONE_TO_MANY;
            }

            selectedTable->addConnection( DBForeign( pressed2TableForm->getTable()->getIdTable(), typeForeign) );
            update();
        }
        countConection++;
    }


//    if(pressed2TableForm == NULL)
//    {
//        QApplication::setOverrideCursor(QCursor(Qt::ArrowCursor));
//    }
    pressedTableForm = NULL;
}

void ContainerWidget::mouseDoubleClickEvent(QMouseEvent *mouseEvent)
{
    if (selectedLine0 != -1 && mouseEvent -> button() == Qt::LeftButton) {
      qDebug() << "selected " + QString::number(selectedLine0) + " " + QString::number(selectedLine1);
    }
}

void ContainerWidget::wheelEvent(QWheelEvent *event)
{
    scale+=(event->delta()/120);
}

TableFormWidget *ContainerWidget::getTableFormById(IdTable idTable)
{
    for(int i=0;i<tableForms.size();i++)
    {
        if(tableForms[i]->getTable()->getIdTable()==idTable)
            return tableForms[i];

    }

    return NULL;
}

void ContainerWidget::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    //p.begin(this);
   //p.scale(scale,scale);

    p.setRenderHint( QPainter::Antialiasing, true );
    p.setPen( QPen( Qt::black, 5 ) );


    if(pressedTableForm && (trigConection1To1==true||trigConection1ToM==true))
    {
        selectedTable = pressedTableForm->getTable();
        bool ok = false;
        QVector<DBAttribute> tempattr =  selectedTable->getAttributes();
        for(int i = 0;i<tempattr.size();i++)
        {
            if(tempattr[i].PK=="1")
            {
                ok = true;
            }
        }
        if(ok == true)
        {
            QPoint posStart = pressedTableForm->pos();
            posStart = QPoint(posStart.x()+pressedTableForm->width()/2, posStart.y()+pressedTableForm->height()/2);

            p.drawLine( mousePos, posStart );
        }

    }

    for(int i=0;i<tableForms.size();i++)
    {
        QPoint pos = tableForms[i]->pos();

        pos = QPoint(pos.x()+tableForms[i]->width()/2, pos.y()+tableForms[i]->height()/2);

        QVector<DBForeign> &forTables = tableForms[i]->getTable()->getForeigns();

        for(int j=0;j<forTables.size();j++)
        {
            TableFormWidget *formWidget2 = getTableFormById(forTables[j].foreignTableId);

            QPoint pos2 = formWidget2->pos();
            pos2 = QPoint(pos2.x()+formWidget2->width()/2, pos2.y()+formWidget2->height()/2);

            if(selectedLine0 == tableForms[i]->getTable()->getIdTable() &&
               selectedLine1 == formWidget2->getTable()->getIdTable())
                p.setPen(QPen(QBrush(QColor(0,255,0)), 10 ));

            p.drawLine( pos, pos2 );

            p.setPen(QPen( Qt::white, 10 ));



            p.drawText((pos2.x()+(pos.x()*0.7))/(1+0.7),(pos2.y()+(pos.y()*0.7))/(1+0.7),"FT");

            QString textForeign;


            if(forTables[j].typeForeign == DBForeign::ONE_TO_ONE)
            {
                textForeign = "1:1";
            }
            else
            {
                textForeign = "1:N";
            }

            p.drawText((pos.x()+pos2.x())/2,(pos.y()+pos2.y())/2, textForeign);



            p.setPen( QPen( Qt::black, 5 ) );
        }


    }
}



