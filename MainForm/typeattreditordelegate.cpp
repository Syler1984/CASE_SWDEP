#include "typeattreditordelegate.h"

TypeAttrEditorDelegate::TypeAttrEditorDelegate(QObject *parent) :
    QItemDelegate(parent)
{

}

QWidget *TypeAttrEditorDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QComboBox *editor = new QComboBox(parent);
    editor->setCurrentIndex(0);
    for (int i=0;i<V1.size();i++)
    {
        if (index.column()==1)
        {
           if(V1[i].elemnt != index.data())
           editor->addItems(V1[i].elemnt);


           return editor;
        }
        if (index.column()>=2)
        {
            QCheckBox *editor = new QCheckBox(parent);
          //  editor->installEventFilter(const_cast<TypeAttrEditorDelegate*>(this));

            return editor;
        }

    }

    return QItemDelegate::createEditor(parent, option, index);

}

void TypeAttrEditorDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QStyleOptionViewItem o = option;
    //QPalette::ColorGroup cg = o.state & QStyle::State_FocusAtBorder ? QPalette::Normal : QPalette::Disabled;
    for (int i=0;i<V1.size();i++)
    {
        if (index.column()>=2)
        {
            drawCheck(painter, option, option.rect, index.data().toBool() ? Qt::Checked : Qt::Unchecked);
            drawFocus(painter, option, option.rect);

        }

    }
    QItemDelegate::paint(painter,o,index);
}

void TypeAttrEditorDelegate::setEditorData(QWidget *editor,const QModelIndex &index) const
{
    for (int i=0;i<V1.size();i++)
    {
        if (index.column()==1)
        {
            int value = index.model()->data(index, Qt::EditRole).toInt();
            QComboBox *comboBox = static_cast< QComboBox*>(editor);
            int ind=comboBox->findText(QString::number(value));
            comboBox->setCurrentIndex(ind);
        }
        if (index.column()>=2)
        {
            Qt::CheckState value = (Qt::CheckState)(index.model()->data(index, Qt::CheckStateRole).toInt());

                QCheckBox *checkBox = static_cast<QCheckBox*>(editor);
                checkBox->setCheckState(value);
        }
        if (index.column()==0)
        {
            return QItemDelegate::setEditorData(editor, index);

        }
    }


}


void TypeAttrEditorDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,const QModelIndex &index) const
{
    for (int i=0;i<V1.size();i++)
    {
        if (index.column()==1)
        {
            QComboBox *comboBox = static_cast< QComboBox*>(editor);
            QString value=comboBox->currentText();
            model->setData(index, value, Qt::EditRole);
        }

        if (index.column()>=2)
        {
            QCheckBox *checkBox = static_cast<QCheckBox*>(editor);
            int value = (int)(checkBox->checkState());

            model->setData(index, value, Qt::CheckStateRole);

            if(index.column() == 2)
            {
                 model->setData(model->index(index.row(), 3), 2, Qt::CheckStateRole);
                 model->setData(model->index(index.row(), 4), 2, Qt::CheckStateRole);
            }

            if(index.column() == 3)
            {
                int PK = index.model()->data(index.model()->index(index.row(), 2), Qt::CheckStateRole).toInt();
                if(PK==2)
                {
                    model->setData(index, 2, Qt::CheckStateRole);
                }
            }
            if(index.column() == 4)
            {
                int PK = index.model()->data(index.model()->index(index.row(), 2), Qt::CheckStateRole).toInt();
                if(PK==2)
                {
                    model->setData(index, 2, Qt::CheckStateRole);
                }
            }
        }
        if (index.column()==0)
        {
            model->setData(index, (static_cast<QLineEdit*>( editor ))->text(), Qt::EditRole);
        }
    }
}

void TypeAttrEditorDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if(index.column()>=2)
    {
        QRect r(option.rect.x() + option.rect.width()/2 - 7, option.rect.y() + option.rect.height()/2 - 7, 13, 13);
        editor->setGeometry(r);
    }
      else
        QItemDelegate::updateEditorGeometry(editor,option,index);
}




void TypeAttrEditorDelegate::commitAndCloseEditor()
{
    QCheckBox* editor = qobject_cast<QCheckBox*>(sender());
    emit commitData(editor);
    emit closeEditor(editor);
}
