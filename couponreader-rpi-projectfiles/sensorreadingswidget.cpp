#include "sensorreadingswidget.h"
#include "ui_sensorreadingswidget.h"

#include "readingsmodel.h"
#include "mechanicaltestingwidget.h"
#include <utility>
#include <QVector>
#include <QTimer>
#include <string>
#include <regex>

extern template class SerialcomHandler<sensor_reading>;

//const std::string g_PATTERN = "[\\n]{1}[\\s]*([\\d]+)[\\s]+([\\d]+)[\\s]+([\\d]+)[\\s]+([\\d]+)[\\s]*[\\r]{1}";
const std::string g_PATTERN = "[\\n]{1}[\\s]*([\\d]{1,3})[\\s]+([\\d]{1,3})[\\s]+([\\d]{1,3})[\\s]+([\\d]{1,3})[\\s]*[\\r]{1}";

SensorReadingsWidget::SensorReadingsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SensorReadingsWidget),
    model(new ReadingsModel(this)),
    handler(SerialcomHandler<sensor_reading>::instance()),
    readings_timer(new QTimer(this))
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
    connect(ui->clear_btn, &QPushButton::clicked, this, &SensorReadingsWidget::clear);
    connect(readings_timer, &QTimer::timeout, this, &SensorReadingsWidget::get_a_reading);
    //connect(this, &SensorReadingsWidget::readings_started, this &SensorReadingWidget::get_readings);
   // connect(this, &SensorReadingsWidget::readings_stopped, this &SensorReadingWidget::stop_readings);
    ui->stop_sensor_btn->setEnabled(false);
    ui->sensor_readings_tbl->horizontalHeader()->setMinimumWidth(100);
    ui->sensor_readings_tbl->horizontalHeader()->setStretchLastSection(true);
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
    emit readings_started();
    readings_timer->start(100);
    handler.start_sensors(std::make_pair("SENSOR_ON", "SENSOR_OFF"));
}

void SensorReadingsWidget::stop(){

    ui->start_sensor_btn->setEnabled(true);
    qDebug() << model->get_results()->size();
    emit toggle_tab(TABS::MECH_TAB, true);
    emit readings_stopped();
    handler.stop_sensors();
    readings_timer->stop();
}

void SensorReadingsWidget::clear()
{
    model->clear();
}
void SensorReadingsWidget::get_a_reading()
{
   // if (!handler.available_reads())
   //     return;
    while (handler.available_reads())
        model->addSensorReading(handler.read_available());
    ui->sensor_readings_tbl->scrollToBottom();
}
