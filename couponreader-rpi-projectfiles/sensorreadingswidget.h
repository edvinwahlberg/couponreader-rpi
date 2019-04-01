#ifndef SENSORREADINGSWIDGET_H
#define SENSORREADINGSWIDGET_H
#include <QWidget>

#include "sensor_reading.h"
#include "serialcomhandler.h"

class ReadingsModel;
class QTimer;
namespace Ui {
class SensorReadingsWidget;
}
extern const std::string g_PATTERN;
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
    void readings_stopped();
private slots:
    void start();
    void stop();
    void clear();
    void get_a_reading();
private:
    Ui::SensorReadingsWidget *ui;
    ReadingsModel* model;
    SerialcomHandler<sensor_reading> &handler;
    QTimer *readings_timer;
};

#endif // SENSORREADINGSWIDGET_H
