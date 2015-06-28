#ifndef TYPEATTREDITORDELEGATE_H
#define TYPEATTREDITORDELEGATE_H

#include <QItemDelegate>
#include <QVector>
#include <QTableView>
#include <QStringList>
#include <QPainter>
#include <QComboBox>
#include <QLineEdit>
#include <QCheckBox>

struct Combobox{
int r;
int c;
QStringList elemnt;
};

class TypeAttrEditorDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    explicit TypeAttrEditorDelegate(QObject *parent = 0);
    TypeAttrEditorDelegate(const QVector <Combobox> &V,QObject *parent=0): QItemDelegate(parent)
    {
        V1=V;
    }
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void setEditorData(QWidget *editor,const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model,const QModelIndex &index) const;
    void updateEditorGeometry(QWidget *editor,const QStyleOptionViewItem &option,const QModelIndex &index) const;

    QVector <Combobox> V1;
signals:

public slots:
    void commitAndCloseEditor();
};

#endif // TYPEATTREDITORDELEGATE_H
