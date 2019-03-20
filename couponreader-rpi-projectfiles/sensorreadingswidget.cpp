#include "sensorreadingswidget.h"
#include "ui_sensorreadingswidget.h"
#include "serialcom_handler.h"

#include "mechanicaltestingwidget.h"

#include <QVector>

SensorReadingsWidget::SensorReadingsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SensorReadingsWidget), handler(Serialcom_handler<sensor_reading, QVector>::instance())
{
    ui->setupUi(this);
    handler.add_to_commands( {{"SENSOR_ON", 'c'}, {"SENSOR_OFF", 'x'}});
    connect(ui->start_sensor_btn, &QPushButton::clicked, this, &SensorReadingsWidget::start);
    connect(ui->stop_sensor_btn, &QPushButton::clicked, this, &SensorReadingsWidget::stop);
    ui->stop_sensor_btn->setEnabled(false);
}

SensorReadingsWidget::~SensorReadingsWidget()
{
    delete ui;
}

void SensorReadingsWidget::start()
{
    ui->start_sensor_btn->setEnabled(false);
    ui->stop_sensor_btn->setEnabled(true);
    emit toggle_tab(TABS::MECH_TAB, false);
    handler.start_readings("SENSOR_ON", "SENSOR_OFF", "[\\n]{1}[\\s]*([\\d]+)[\\s]+([\\d]+)[\\s]+([\\d]+)[\\s]+([\\d]+)[\\s]*[\\r]{1}");
}

void SensorReadingsWidget::stop(){
    handler.stop_readings();
    QVector<sensor_reading> lol;
    handler.read_available(lol);
    ui->start_sensor_btn->setEnabled(true);
    emit toggle_tab(TABS::MECH_TAB, true);
}
