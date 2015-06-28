#ifndef WIDGETGENERATIONSCRIPT_H
#define WIDGETGENERATIONSCRIPT_H

#include <QDialog>
#include <QPluginLoader>
#include <QMessageBox>
#include <QDir>
#include <QDebug>
#include <QVector>
//-- Классы хранения данных--//
#include "dbtable.h"
#include "maindata.h"
//-- Интерфейс плагина --//
#include "dbplugininterface.h"
//-------------------------//

namespace Ui {
class WidgetGenerationScript;
}

class WidgetGenerationScript : public QDialog
{
    Q_OBJECT

public:
    explicit WidgetGenerationScript(QWidget *parent = 0);
    ~WidgetGenerationScript();
    void loadPlugins(QString pathPlugin = "../libs");

private slots:
    void on_comboBoxPlugin_currentIndexChanged(const QString &arg1);
    void on_pushButtonGenerate_clicked();

private:
    Ui::WidgetGenerationScript *ui;
    QVector <DBPluginInterface*> plugins;
};

#endif // WIDGETGENERATIONSCRIPT_H
