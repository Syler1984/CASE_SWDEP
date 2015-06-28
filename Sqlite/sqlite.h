#ifndef SQLITE_H
#define SQLITE_H

#include <dbplugininterface.h>

class Sqlite : public DBPluginInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "com.devlab.Notifier.DBPluginInterface")
    Q_INTERFACES(DBPluginInterface)

public:
    Sqlite();

    QString getVersion();
    QString getName();
    QString getCreateScript(QVector<DBTable*> &tables);

    ~Sqlite() {}
};

#endif // SQLITE_H
