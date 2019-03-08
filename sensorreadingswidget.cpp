#include "sensorreadingswidget.h"
#include "ui_sensorreadingswidget.h"

SensorReadingsWidget::SensorReadingsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SensorReadingsWidget)
{
    ui->setupUi(this);
}

SensorReadingsWidget::~SensorReadingsWidget()
{
    delete ui;
}
