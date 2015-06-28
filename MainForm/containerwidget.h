#ifndef CONTAINERWIDGET_H
#define CONTAINERWIDGET_H

#include <QWidget>
#include <QFormLayout>
#include <QMouseEvent>
#include <QLabel>
#include <QScrollArea>
#include <QApplication>
#include <QDebug>
#include <QGraphicsItem>
#include <QWheelEvent>
#include <QEvent>
#include <QPaintEvent>
#include <QVector>
#include <QColor>
#include <QPalette>

#include "tableformwidget.h"
#include "maindata.h"

class ContainerWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ContainerWidget(QWidget *parent = 0);

    bool trigTable;
    bool trigConection1To1;
    bool trigConection1ToM;
    bool trigEdit;
    bool trigDelete;

    static ContainerWidget *getShared();

    void deleteTableFormById(IdTable idTable);

protected:
    virtual void mousePressEvent( QMouseEvent *mouseEvent );
    virtual void mouseMoveEvent ( QMouseEvent *mouseEvent );
    virtual void mouseReleaseEvent ( QMouseEvent *mouseEvent );
    virtual void mouseDoubleClickEvent( QMouseEvent *mouseEvent );
    void paintEvent ( QPaintEvent * event );
    void wheelEvent ( QWheelEvent * event );

signals:
    void sig();
    void sigClose();

private:
    TableFormWidget *getTableFormById(IdTable idTable);

    QVector< TableFormWidget * > tableForms;
    TableFormWidget *pressedTableForm;
    TableFormWidget *pressed2TableForm;
    QWidget *wid;
    int countConection;
    qreal scale;
    DBTable *selectedTable;
    IdTable deleteTableId;

    QPoint offsetMove;

    IdTable selectedLine0 = -1;
    IdTable selectedLine1 = -1;

    QPoint mousePos;
};

#endif // CONTAINERWIDGET_H
