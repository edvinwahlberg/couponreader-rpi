#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "readingsmodel.h"
template class SerialcomHandler<sensor_reading>;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

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
