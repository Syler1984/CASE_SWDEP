#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedLayout>
#include <QFormLayout>
#include <QGridLayout>
#include <QMouseEvent>

#include "containerwidget.h"
#include "tableformwidget.h"
#include "widgetgenerationscript.h"



namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    ContainerWidget *container = new ContainerWidget;
    TableFormWidget *tableForm = new TableFormWidget;
    WidgetGenerationScript *ScriptForm = new WidgetGenerationScript;

private slots:

    void on_tableRadio_clicked();
    void on_one_to_one_clicked();
    void on_one_to_N_clicked();
    void on_Editing_clicked();
    void on_radioButtonDelete_clicked();
    void on_radioMause_clicked();


    void on_close_triggered();
    void on_createSript_triggered();

    void setgeometryscroll();
    void closeallradio();





private:
    Ui::MainWindow *ui;
    bool eventFilter(QObject *o, QEvent *e);
};

#endif // MAINWINDOW_H
