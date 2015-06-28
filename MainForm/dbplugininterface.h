#ifndef DBPLUGININTERFACE_H
#define DBPLUGININTERFACE_H


#include <QString>
#include <QtCore/qplugin.h>
#include <QtPlugin>

#include "dbtable.h"

class DBPluginInterface : public QObject
{
public:

    virtual QString getName() =0;
    virtual QString getVersion() =0;
    virtual QString getCreateScript(QVector<DBTable*> &tables) = 0;

signals:

public slots:

};

QT_BEGIN_NAMESPACE

Q_DECLARE_INTERFACE(DBPluginInterface,"DBPluginInterface/Plugin/1.0")

QT_END_NAMESPACE

#endif // DBPLUGININTERFACE_H
