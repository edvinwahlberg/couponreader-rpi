#ifndef SENSORREADINGSWIDGET_H
#define SENSORREADINGSWIDGET_H
#include <QWidget>

#include "sensor_reading.h"
#include "serialcom_handler.h"

class ReadingsModel;
extern template class Serialcom_handler<sensor_reading>;
namespace Ui {
class SensorReadingsWidget;
}

class SensorReadingsWidget : public QWidget
{
    Q_OBJECT

    enum TABS {
        MECH_TAB = 1
    };
public:
    explicit SensorReadingsWidget(QWidget *parent = nullptr);
    ~SensorReadingsWidget();
signals:
    void toggle_tab(int tab, bool enabled);
    void readings_started();
private slots:
    void start();
    void stop();
private:
    Ui::SensorReadingsWidget *ui;
    Serialcom_handler<sensor_reading> &handler;
    ReadingsModel *model;
};

#endif // SENSORREADINGSWIDGET_H
