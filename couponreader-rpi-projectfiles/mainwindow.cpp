#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "readingsmodel.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //ui->tabWidget->setTabEnabled(SENS_TAB, false);
    connect(ui->mech_tab, SIGNAL(alterTab(int,bool)), this, SLOT(setTab(int, bool)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setTab(int t, bool b)
{
    ui->tabWidget->setTabEnabled(t, b);
}
