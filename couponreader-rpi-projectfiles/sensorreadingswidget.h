#ifndef SENSORREADINGSWIDGET_H
#define SENSORREADINGSWIDGET_H
#include <QWidget>

#include "sensor_reading.h"
namespace Ui {
class SensorReadingsWidget;
}

template <typename T>
class Serialcom_handler;

class SensorReadingsWidget : public QWidget
{
    Q_OBJECT

    enum TABS {
        MECH_TAB = 1
    };

public:
    explicit SensorReadingsWidget(QWidget *parent = nullptr);
    ~SensorReadingsWidget();
private slots:
    void start();
    void stop();
private:
    Ui::SensorReadingsWidget *ui;
    Serialcom_handler<sensor_reading> &handler;
};

#endif // SENSORREADINGSWIDGET_H
