#ifndef POSTGRESQL_H
#define POSTGRESQL_H

#include <dbplugininterface.h>

class Postgresql : public DBPluginInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "com.devlab.Notifier.DBPluginInterface")
    Q_INTERFACES(DBPluginInterface)

public:
    Postgresql();

    QString getVersion();
    QString getName();
    QString getCreateScript(QVector<DBTable*> &tables);

    ~Postgresql() {}
};

#endif // POSTGRESQL_H
