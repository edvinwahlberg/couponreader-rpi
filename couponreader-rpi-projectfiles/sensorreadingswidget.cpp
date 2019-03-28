#include "sensorreadingswidget.h"
#include "ui_sensorreadingswidget.h"

#include "readingsmodel.h"
#include "mechanicaltestingwidget.h"
#include <utility>
#include <QVector>

extern template class SerialcomHandler<sensor_reading>;

const std::string g_PATTERN = "[\\n]{1}[\\s]*([\\d]+)[\\s]+([\\d]+)[\\s]+([\\d]+)[\\s]+([\\d]+)[\\s]*[\\r]{1}";

SensorReadingsWidget::SensorReadingsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SensorReadingsWidget),
    model(new ReadingsModel(this)),
    handler(SerialcomHandler<sensor_reading>::instance())
{
    ui->setupUi(this);
    if (!handler.valid_port())
    {
        handler.setPortName("/dev/ttyUSB0");
    }

    if (!handler.valid_regex_pattern())
        handler.setRegexPattern(g_PATTERN);
    ui->sensor_readings_tbl->setModel(model);
    ui->sensor_readings_tbl->setAlternatingRowColors(true);
    ui->sensor_readings_tbl->setMinimumWidth(550);
    handler.add_commands( {{"SENSOR_ON", 'c'}, {"SENSOR_OFF", 'x'}});
    connect(ui->start_sensor_btn, &QPushButton::clicked, this, &SensorReadingsWidget::start);
    connect(ui->stop_sensor_btn, &QPushButton::clicked, this, &SensorReadingsWidget::stop);
    //connect(this, &SensorReadingsWidget::readings_started, this &SensorReadingWidget::get_readings);
   // connect(this, &SensorReadingsWidget::readings_stopped, this &SensorReadingWidget::stop_readings);
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
    handler.start_sensors(std::make_pair("SENSOR_ON", "SENSOR_OFF"));
}

void SensorReadingsWidget::stop()
{
    ui->start_sensor_btn->setEnabled(true);
    qDebug() << model->get_results()->size();
    emit toggle_tab(TABS::MECH_TAB, true);
    emit readings_stopped();
    handler.stop_sensors();
}
