#include "sensorreadingswidget.h"
#include "ui_sensorreadingswidget.h"
#include "serialcom_handler.h"
#include "readingsmodel.h"
#include "mechanicaltestingwidget.h"

#include <QVector>

SensorReadingsWidget::SensorReadingsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SensorReadingsWidget), handler(Serialcom_handler<sensor_reading, QVector>::instance()),
    model(new ReadingsModel(this))
{
    ui->setupUi(this);

    ui->sensor_readings_tbl->setModel(model);
    ui->sensor_readings_tbl->setAlternatingRowColors(true);
    ui->sensor_readings_tbl->setMinimumWidth(550);
    handler.add_to_commands( {{"SENSOR_ON", 'c'}, {"SENSOR_OFF", 'x'}});
    connect(ui->start_sensor_btn, &QPushButton::clicked, this, &SensorReadingsWidget::start);
    connect(ui->stop_sensor_btn, &QPushButton::clicked, this, &SensorReadingsWidget::stop);
    ui->stop_sensor_btn->setEnabled(false);
}

SensorReadingsWidget::~SensorReadingsWidget()
{
    delete ui;
    delete model;
}

void SensorReadingsWidget::start()
{
    ui->start_sensor_btn->setEnabled(false);
    ui->stop_sensor_btn->setEnabled(true);
    emit toggle_tab(TABS::MECH_TAB, false);
    emit readings_started();
    handler.start_readings("SENSOR_ON", "SENSOR_OFF", "[\\n]{1}[\\s]*([\\d]+)[\\s]+([\\d]+)[\\s]+([\\d]+)[\\s]+([\\d]+)[\\s]*[\\r]{1}", model->get_results(), &QVector<sensor_reading>::push_back);
}

void SensorReadingsWidget::stop(){
    handler.stop_readings();
    QVector<sensor_reading> lol;
    //handler.read_available(lol);
    ui->start_sensor_btn->setEnabled(true);
    qDebug() << model->get_results()->size();
    emit toggle_tab(TABS::MECH_TAB, true);
}
