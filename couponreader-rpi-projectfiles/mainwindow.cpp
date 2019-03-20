#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "readingsmodel.h"
#include "serialcom_handler.h"
#include "sensor_reading.h"

template class Serialcom_handler<sensor_reading>;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //ui->tabWidget->setTabEnabled(SENS_TAB, false);
   // connect(ui->mech_tab, SIGNAL(toggle_tab(int,bool)), this, SLOT(setTab(int, bool)));
 //   connect(ui->sensor_tab, SIGNAL(toggle_tab(int,bool)), this, SLOT(setTab(int, bool)));
    connect(ui->mech_tab, &MechanicalTestingWidget::toggle_tab, this, &MainWindow::setTab);
    connect(ui->sensor_tab, &SensorReadingsWidget::toggle_tab, this, &MainWindow::setTab);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setTab(int t, bool b)
{
    ui->tabWidget->setTabEnabled(t, b);
}
