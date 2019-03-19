#include "sensorreadingswidget.h"
#include "ui_sensorreadingswidget.h"
#include "serialcom_handler.h"

SensorReadingsWidget::SensorReadingsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SensorReadingsWidget), handler(Serialcom_handler<sensor_reading>::instance())
{
    ui->setupUi(this);
    handler.add_to_commands( {{"SENSOR_ON", 'c'}, {"SENSOR_OFF", 'x'}});
    connect(ui->start_sensor_btn, &QPushButton::clicked, this, &SensorReadingsWidget::start);
    connect(ui->stop_sensor_btn, &QPushButton::clicked, this, &SensorReadingsWidget::stop);
}

SensorReadingsWidget::~SensorReadingsWidget()
{
    delete ui;
}

void SensorReadingsWidget::start()
{
    handler.write(std::string("SENSOR_ON"));
}

void SensorReadingsWidget::stop(){
    handler.write(std::string("SENSOR_OFF"));
}
