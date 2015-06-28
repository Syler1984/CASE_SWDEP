#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QScrollArea>
#include <QScrollBar>
#include <QCursor>
#include <QPoint>



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    ui->scrollArea->setBackgroundRole(QPalette::Dark);
    ui->scrollArea->setWidget(container);

    ui->scrollArea->setWidgetResizable(true);
    ui->scrollArea->setupViewport(container);

    connect(container,SIGNAL(sig()),this,SLOT(setgeometryscroll()));
    connect(container,SIGNAL(sigClose()),this,SLOT(closeallradio()));
    ui->scrollArea->installEventFilter(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setgeometryscroll()
{
    ui->tableRadio->setChecked(false);

    QSize containersize = container->size();
    QSize widgetSize = tableForm->size();

    QCursor *cur = new QCursor();
    QPoint pos = cur->pos();
//    qDebug()<<widgetSize;
//    qDebug()<<containersize;
//    qDebug()<<pos;

    if(pos.x()+widgetSize.width()>=containersize.width())
        container->setFixedWidth(widgetSize.width() + containersize.width());

    if(pos.y()+widgetSize.height()>=containersize.height())
        container->setFixedHeight(widgetSize.height() + containersize.height());

    if((pos.x()+widgetSize.width()>=containersize.width())&&(pos.y()+widgetSize.height()>=containersize.height()))
    {
        container->setFixedWidth(widgetSize.width() + containersize.width());
        container->setFixedHeight(widgetSize.height() + containersize.height());
    }
}

void MainWindow::closeallradio()
{
    ui->radioMause->setChecked(true);
    ui->tableRadio->setChecked(false);
    ui->one_to_one->setChecked(false);
    ui->one_to_N->setChecked(false);
    ui->Editing->setChecked(false);
}

bool MainWindow::eventFilter(QObject *o, QEvent *e)
{
    QPixmap picDel("./ico/DeleteCursor.png");
    QPixmap picAdd("./ico/AddSegment_To_ResizeSegmentListCursor.png");
    QPixmap picChain("./ico/Link-32.png");
    if(o == ui->scrollArea)
    {
        if(e->type() == QEvent::Enter)
        {
            if(container->trigTable == true)
            {
                QApplication::setOverrideCursor(QCursor(picAdd,0,0));
                return true;
            }
            if(container->trigConection1To1 == true)
            {
                QApplication::setOverrideCursor(QCursor(picChain,0,0));
                return true;
            }
            if(container->trigConection1ToM == true)
            {
                QApplication::setOverrideCursor(QCursor(picChain,0,0));
                return true;
            }
            if(container->trigEdit == true)
            {
                QApplication::setOverrideCursor(QCursor(Qt::OpenHandCursor));
                return true;
            }
            if(container->trigDelete == true)
            {
                QApplication::setOverrideCursor(QCursor(picDel,0,0));
                return true;
            }
            if(container->trigTable == false && container->trigConection1To1 == false && container->trigConection1ToM == false && container->trigEdit == false)
            {
                QApplication::setOverrideCursor(QCursor(Qt::ArrowCursor));
                return true;
            }
        }
        if(e->type() == QEvent::Leave)
            {
                QApplication::setOverrideCursor(QCursor(Qt::ArrowCursor));
                return true;
            }

    }
    return QMainWindow::eventFilter(o, e);
}

void MainWindow::on_tableRadio_clicked()
{
    container->trigTable = true;
    container->trigConection1To1 = false;
    container->trigConection1ToM = false;
    container->trigEdit = false;
    container->trigDelete = false;
}


void MainWindow::on_one_to_one_clicked()
{
    container->trigTable = false;
    container->trigConection1To1 = true;
    container->trigConection1ToM = false;
    container->trigEdit = false;
    container->trigDelete = false;
}

void MainWindow::on_one_to_N_clicked()
{
    container->trigTable = false;
    container->trigConection1To1 = false;
    container->trigConection1ToM = true;
    container->trigEdit = false;
    container->trigDelete = false;
}

void MainWindow::on_Editing_clicked()
{
    container->trigTable = false;
    container->trigConection1To1 = false;
    container->trigConection1ToM = false;
    container->trigEdit = true;
    container->trigDelete = false;
}

void MainWindow::on_radioMause_clicked()
{
    container->trigTable = false;
    container->trigConection1To1 = false;
    container->trigConection1ToM = false;
    container->trigEdit = false;
    container->trigDelete = false;
}

void MainWindow::on_radioButtonDelete_clicked()
{
    container->trigTable = false;
    container->trigConection1To1 = false;
    container->trigConection1ToM = false;
    container->trigEdit = false;
    container->trigDelete = true;
}
void MainWindow::on_close_triggered()
{
     close();
}

void MainWindow::on_createSript_triggered()
{
    ScriptForm = new WidgetGenerationScript();
    ScriptForm->loadPlugins();
    ScriptForm->show();

}




