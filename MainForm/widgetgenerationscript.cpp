#include "widgetgenerationscript.h"
#include "ui_widgetgenerationscript.h"





WidgetGenerationScript::WidgetGenerationScript(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WidgetGenerationScript)
{
    ui->setupUi(this);
}

WidgetGenerationScript::~WidgetGenerationScript()
{
    delete ui;
}

void WidgetGenerationScript::loadPlugins(QString pathPlugin)
{
    #ifdef Q_OS_WIN32
        QString enlargement = ".dll";   // Для Windows
        QString prefix = "";
    #endif

    #ifdef Q_OS_LINUX
        QString enlargement = ".so";    // Для Linux
        QString prefix = "lib";         // В Linux добовляется приставка lib...
    #endif



    QStringList combo;
    combo<<"Выберите плагин";

        QDir findPlugin(pathPlugin);
        //qDebug()<<findPlugin.entryList().contains(prefix + readPluginsName.at(i) + enlargement);
        QStringList filesList = findPlugin.entryList();
        for(int i = 2;i < filesList.size(); i++)
        {               
            QPluginLoader loader(pathPlugin + "/" + filesList[i]);
            loader.load();
            if(loader.isLoaded() == false)
            {
                qDebug() << QString("Can't load a plugin");
                QMessageBox msgBoxError;
                msgBoxError.setWindowTitle("Ошибка");
                msgBoxError.setIcon(QMessageBox::Critical);
                msgBoxError.setText("Ошибка загрузки плагина "+ filesList[i]);
                msgBoxError.exec();
                continue;
            }
            QObject * obj = loader.instance();
            if(DBPluginInterface* plugin = qobject_cast<DBPluginInterface *>(obj))
            {
                combo<<plugin->getName();
                plugins.push_back(plugin);
            }
        }

ui->comboBoxPlugin->addItems(combo);
}

void WidgetGenerationScript::on_comboBoxPlugin_currentIndexChanged(const QString &arg1)
{
    QMessageBox msgBox;


    for(int i=0;i<plugins.size();i++)
    {
        if (plugins[i]->getName()==arg1)
        {
            msgBox.setWindowTitle("Версия плагина");
            msgBox.setIcon(QMessageBox::Information);
            msgBox.setText("Текущая версия плагина "+plugins[i]->getVersion());
            msgBox.exec();
        }
    }
    if(arg1=="Выберите плагин")
    {

    }
}

void WidgetGenerationScript::on_pushButtonGenerate_clicked()
{
    MainData data;
    QVector<DBTable*> tables = MainData::instance()->getTables();
    QString resscript;
    for(int i=0;i<plugins.size();i++)
    {
        if (plugins[i]->getName()==ui->comboBoxPlugin->currentText())
        {
            resscript = plugins[i]->getCreateScript(tables);
        }
    }
    ui->textEdit->setText(resscript);
}
